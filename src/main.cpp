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
    LoadBalancer lb(8081, 1);

    CMS c(8082, 1);
    CMS c2(8083, 1);
    CMS c3(8084, 1);
    CMS c4(8085, 1);

    c.add_server(8086, 1);    
    c2.add_server(8087, 1);
    c3.add_server(8088, 1);
    c4.add_server(8089, 1);

    c.start_up();
    c2.start_up();
    c3.start_up();
    c4.start_up();
  
    lb.add_connection("localhost:8082");
    lb.add_connection("localhost:8083");
    lb.add_connection("localhost:8084");
    lb.add_connection("localhost:8085");

    lb.start_server();

    return 0;
}
