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

    Server s1(8080, 1);
    Server s2(8081, 1);
   
    std::thread s1_thread([&s1]()
            {
                s1.start();
            });

    std::thread s2_thread([&s2]()
            {
                s2.start();
            });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::thread sessions([&s1, &s2]()
            {
                while(true)
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout<<"Concurrent sessions in s1: "<<s1.getSessions()<<std::endl;
                    std::cout<<"Concurrent sessions in s2: "<<s2.getSessions()<<std::endl;
                    std::cout<<" "<<std::endl;
                }
            });

    sessions.join();
    s1_thread.join();
    s2_thread.join();

    return 0;
}
