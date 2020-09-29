all: image_processing.o

image_processing.o: image_processing.cpp
	g++ -std=c++17 -I/usr/include/opencv4 -c image_processing.cpp

clean:
	rm -f *.o