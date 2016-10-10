#include "load_balancer.hpp"

using namespace II2202;

LoadBalancer::LoadBalancer(const unsigned short port, int n_threads)
    :HttpServer(port, n_threads)
{
    add_resources();
}

LoadBalancer::~LoadBalancer()
{
    if(server_thread.joinable())
        server_thread.join();
}

void LoadBalancer::add_resources()
{
    
    resource["^/work$"]["GET"]=[&](std::shared_ptr<Response> response, std::shared_ptr<Request> request)
    {
        
        std::thread new_connection = std::thread([response, request]()
                {
                        std::cout<<"Im here"<<std::endl;

                        HttpClient c("localhost:8081");
                         
                        c.request("GET", request->path);
                            
                        *response << "HTTP/1.1 200 OK\r\nContent-Length: " << 2  << "\r\n\r\n" << "Ok";  
                });

        new_connection.detach();;
    };
}

void LoadBalancer::start_server()
{
    server_thread = std::thread([this](){this->start();});
}

void LoadBalancer::add_connection(const std::string ip)
{
    try{
//            connections.push_back(std::make_unique<HttpClient>(ip));
    }catch(...){
        std::cout<<"Cant establish connection"<<std::endl;
    }
}
