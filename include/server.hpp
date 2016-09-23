#ifndef SERVER_HPP
#define SERVER_HPP

#include<string>
#include<mutex>
#include<atomic>
#include "server_http.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

namespace II2202
{

    class Server:public HttpServer 
    {
        public:
            
            Server(const unsigned short, int);
            ~Server();
        
        public:
            
            class Session
            {
                friend class Server;

                public: 
                static int getSessions();

                private:
                Session();
                ~Session();
                static std::atomic<int> n_sessions;
            };
            
            void add_resources();
    };
}
#endif /*server.hpp*/