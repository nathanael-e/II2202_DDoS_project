#ifndef SERVER_HPP
#define SERVER_HPP

#define MAX_THREADS 10

#include<string>
#include<mutex>
#include<atomic>

#include "server_http.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

namespace II2202
{
    class Server
        :public HttpServer 
    {

        public:
            
            class Thread_counter
            {
                friend class Server;

                public:

                    Thread_counter(const Thread_counter&) = delete;
                    Thread_counter(const Thread_counter&&) = delete;
                    Thread_counter operator=(const Thread_counter&) = delete;
                    Thread_counter operator=(const Thread_counter&&) = delete;

                private:

                    Thread_counter(std::atomic<int>& n_sessions);
                    ~Thread_counter();
                    
                    std::atomic<int>* n_threads;
            };


            Server(const unsigned short, int);
            ~Server();

            void do_work(std::shared_ptr<HttpServer::Response>&, std::shared_ptr<Request>&);
            int getSessions();
            bool isFull() const;
            float server_load() const;
            void start_server();

        private:
             
            std::atomic<int> n_threads{0};
            std::thread server_thread;
            mutable std::mutex m_tex;
    };
}
#endif /*SERVER_HPP*/
