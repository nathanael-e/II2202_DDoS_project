#include "cms.hpp"

using namespace II2202;

CMS::CMS(const unsigned short port, int n_threads)
    :HttpServer(port, n_threads)
{
    add_reseources();
}

CMS::~CMS()
{
    if(server_thread.joinable())
        server_thread.join();
}

void CMS::add_reseources()
{
    resource["^/get_status$"]["GET"] = [&](std::shared_ptr<Response> response, std::shared_ptr<Request> /*request*/)
    { 
       
       m_tex.lock();
       
       float total_load = 0; 

       for(auto& server: servers)
           total_load += server->server_load();

       std::string load  = std::to_string(total_load/servers.size());

       std::cout<<"Tot: "<<load<<std::endl;

       *response << "HTTP/1.1 200 OK\r\nContent-Length: " << load.size() << "\r\n\r\n" << load;
       
        m_tex.unlock();
    };
    
    resource["^/work$"]["GET"] = [&](std::shared_ptr<Response> response, std::shared_ptr<Request> request)
    {
        for(auto& server:servers)
            if(!server->isFull())
            {
                server->do_work(response, request);
                return;
            }

        *response << "HTTP/1.1 200 OK\r\nContent-Length: " << 4 << "\r\n\r\n" << "FULL";
    }; 
}

bool CMS::full_load() const
{
    for(auto& server:servers)
        if(!server->isFull())
            return false;
    
    return true;
}

void CMS::add_server(const unsigned short port, int n_threads)
{
    servers.push_back(std::make_unique<II2202::Server>(port, n_threads));
}

void CMS::start_up()
{
    for(auto& server:servers)
        server->start_server();

    server_thread = std::thread([this](){this->start();});
}
