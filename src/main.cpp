#include "server_http.hpp"
#include "client_http.hpp"

#include "cms.hpp"
#include "server.hpp"
#include <iostream>
#include <thread>
#include<string>
#include<vector>

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;
using namespace II2202;

int main()
{

    CMS c(8080, 1);

    Server s(8081, 1);

    std::thread cms_thread([&c]()
            {
                c.start();
            });

     std::thread server_thread([&s]()
            {
                s.start();
            });

    c.add_server("localhost:8081");

    cms_thread.join();
    server_thread.join();

    return 0;
}
