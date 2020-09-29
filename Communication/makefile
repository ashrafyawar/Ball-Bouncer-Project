all: main.o websocket_client.o http_server.o

main.o: main.cpp
	g++ -std=c++17 -I/usr/include/opencv4 -c main.cpp

websocket_client.o: websocket_client.cpp
	g++ -std=c++17 -I/usr/include/opencv4 -c websocket_client.cpp

http_server.o: http_server.cpp
	g++ -std=c++17 -I/usr/include/opencv4 -c http_server.cpp

clean:
	rm -f server *.o