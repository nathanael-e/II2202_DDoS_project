#include "server_http.hpp"
#include "client_http.hpp"

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

    Server s(8080, 1);
   
    std::thread server_thread([&s]()
            {
                s.start();
            });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::thread sessions([]()
            {
                while(true)
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout<<"Concurrent sessions: "<<Server::Session::getSessions()<<std::endl;
                }
            });

    sessions.join();
    server_thread.join();

    return 0;
}
