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
            
            class Session
            {
                friend class Server;

                public:

                    Session(const Session&) = delete;
                    Session(const Session&&) = delete;
                    Session operator=(const Session&) = delete;
                    Session operator=(const Session&&) = delete;
                    static int getSessions();

                private:

                    Session();
                    ~Session();
                    
                    static std::atomic<int> n_sessions;
            };

        private:
 
            void add_resources();
    };
}
#endif /*SERVER_HPP*/
