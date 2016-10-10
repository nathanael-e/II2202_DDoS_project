#include "load_balancer.hpp"

using namespace II2202;

LoadBalancer::LoadBalancer(const unsigned short port, int n_threads)
    :HttpServer(port, n_threads)
{
    add_resources();
    client = std::make_unique<HttpClient>("localhost:8081");
}

LoadBalancer::~LoadBalancer()
{
    if(server_thread.joinable())
        server_thread.join();
}

void LoadBalancer::update()
{ 
    if(get_system_load() > 0.80)
        scale_system();
}

void LoadBalancer::scale_system()
{
    for(auto it = total_connections.begin(); it != active_connections.end(); it++)
    {
        auto cms = active_connections.find(it->first);

        if(cms == active_connections.end())
        {
            active_connections.insert(std::pair<std::string, float>(it->first, 0));
            break;
        }
    }
}

float LoadBalancer::get_system_load()
{
    float total_load = 0;

    for(auto it = active_connections.begin(); it != active_connections.end();)
    {
        std::stringstream ss;
//        std::cout<<it->first<<std::endl;
    try{ 
        HttpClient c(it->first);
        ss << c.request("GET", "/get_status")->content.rdbuf();
        total_load += std::stof(ss.str());
    }catch(...) {
        
    }
    }

    return total_load / active_connections.size();
}

void LoadBalancer::add_resources()
{
    resource["^/get_status$"]["GET"]=[&](std::shared_ptr<Response> response, std::shared_ptr<Request> request)
    {
    };

    resource["^/work$"]["GET"]=[&](std::shared_ptr<Response> response, std::shared_ptr<Request> request)
    {
        std::thread new_connection = std::thread([response, request, this]()
                { 

                    std::stringstream ss; 
              
                    for(auto it = active_connections.begin(); it!=active_connections.end();)
                    {
                        try{
                            HttpClient c(it->first);  
                            ss<<c.request("GET", "/work")->content.rdbuf();
                            std::string load = ss.str();
                            
                            if(load == "FULL")
                                ++it;
                            else
                            {
                                *response << "HTTP/1.1 200 OK\r\nContent-Length: " << load.length()  << "\r\n\r\n" << load;
                                return;
                            }   
   
                        }catch(...)
                        {   
                            //++it;                            
                        }
                    }         
                });

        new_connection.detach();
    };
}

void LoadBalancer::start_server()
{
    server_thread = std::thread([this](){this->start();});
    cms_updates = std::thread([this](){
            while(true){
            update(); 
            std::cout<<"Updating"<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(10));}});
}

void LoadBalancer::add_connection(const std::string ip)
{   
    if(active_connections.empty())
        active_connections.insert(std::pair<std::string, float>(ip, 0));
    
    total_connections.insert(std::pair<std::string, float>(ip, 0));
}
