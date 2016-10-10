#include "server_http.hpp"
#include "client_http.hpp"

#include "cms.hpp"
#include "server.hpp"
#include "load_balancer.hpp"
#include <iostream>
#include <thread>
#include<string>
#include<vector>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;
using namespace II2202;

int main()
{


    LoadBalancer lb(8080, 1);

    CMS c(8081, 1);
    c.add_server(8082, 1);    
    c.start_up();

    lb.add_connection("localhost:8081");

    lb.start_server();

    return 0;
}
