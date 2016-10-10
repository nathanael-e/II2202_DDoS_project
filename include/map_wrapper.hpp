#ifndef MAP_WARPPER_HPP
#define MAP_WRAPPER_HPP

#include<map>
#include<shared_mutex>

namespace II2202
{
    template<class T, class V>
    class map_wrapper
    {
        public:
           map_wrapper(){}

           void insert(const std::pair<T,V>& my_pair)
           {
               std::unique_lock<std::shared_timed_mutex> lock(my_mutex);
               my_map.insert(my_pair);
           }  

           auto begin() const
           {
                std::shared_lock<std::shared_timed_mutex> lock(my_mutex);         
                return my_map.begin();
           }

           auto end() const
           {
                std::shared_lock<std::shared_timed_mutex> lock(my_mutex);
                return my_map.end();
           }

           auto find(const T& t)
           {
                return my_map.find(t);
           }

           auto size() const
           {
                return my_map.size();
           }

           auto empty() const
           {
                return my_map.empty();
           }
        private:
           mutable std::shared_timed_mutex my_mutex;
           std::map<T, V> my_map; 
    };
}

#endif /*MAP_WRAPPER_HPP*/
