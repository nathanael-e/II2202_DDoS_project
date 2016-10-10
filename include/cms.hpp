#ifndef CMS_HPP
#define CMS_HPP

#include<string>
#include<vector>
#include<memory>
#include "server_http.hpp"
#include "client_http.hpp"
#include "server.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

namespace II2202
{
    class CMS
        :public HttpServer
    {
        using server_base = std::vector<std::unique_ptr<II2202::Server>>;

        public:
            CMS(const unsigned short, int);
            ~CMS();
            void add_server(const unsigned short, int);
            void start_up();
            bool full_load() const;
        
        private:
            void add_reseources();
            server_base servers;
            std::thread server_thread;
    };
}
#endif
