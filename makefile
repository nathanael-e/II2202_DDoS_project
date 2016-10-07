OBJS = 
CC = g++ -std=c++11
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
SERVER_FLAGS = -rdynamic -lboost_regex -lboost_system -lboost_thread -lboost_filesystem -lboost_date_time -lboost_chrono -lboost_atomic -lpthread -lpthread

default: server

server: simple_web_server.cpp $(OBJS)
	$(CC) $(LFLAGS) simple_web_server.cpp $(SERVER_FLAGS) $(OBJS) -o simple_web_server.out

ddos: ddos_client.cpp $(OBJS)
	$(CC) $(LFLAGS) ddos_client.cpp $(SERVER_FLAGS) $(OBJS) -o ddos_client.out

clean:
	\rm *.o *~ simple_web_server
