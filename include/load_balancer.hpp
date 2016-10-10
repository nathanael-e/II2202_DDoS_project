#ifndef LOAD_BALANCER_HPP
#define LOAD_BALANCER_HPP

#include<vector>
#include<memory>
#include<thread>

#include "server_http.hpp"
#include "client_http.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

namespace II2202
{
    class LoadBalancer:
        public HttpServer
    {
        public:

           LoadBalancer(const unsigned short, int);

           ~LoadBalancer();

           void add_connection(const std::string);

           void start_server();

        private: 

           void add_resources();

           std::vector<std::unique_ptr<HttpClient>> connections; 

           std::thread server_thread;
           std::thread cms_updates;
   
    };
}

#endif /*LOAD_BALANCER_HPP*/
