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
            
            class Session
            {
                friend class Server;

                public:

                    Session(const Session&) = delete;
                    Session(const Session&&) = delete;
                    Session operator=(const Session&) = delete;
                    Session operator=(const Session&&) = delete;

                private:

                    Session(std::atomic<int>& n_sessions);
                    ~Session();
                    
                    std::atomic<int>* n_sessions;
            };

            Server(const unsigned short, int);
            ~Server();
            int getSessions();

        private:
         
            void add_resources();
            std::atomic<int> n_sessions{0};
    };
}
#endif /*SERVER_HPP*/
