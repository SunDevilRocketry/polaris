main: main.o glad.o stl_read.o

ifeq ($(shell uname -s),Darwin)
	g++ main.o glad.o stl_read.o -lglfw -lpthread -ldl -o main
else
	g++ main.o glad.o stl_read.o -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o main
endif

main.o: main.cpp
	g++ -c -Wall main.cpp 

glad.o: glad.c
	g++ -c -Wall glad.c

stl_read.o: stl_read.cpp
	g++ -c -Wall stl_read.cpp

genShaders: genShaders.cpp
	g++ -Wall genShaders.cpp -o genShaders

clean: 
	rm main 
	rm *.o
