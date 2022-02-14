main: main.cpp
	g++ -Wall main.cpp glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o main

genShaders: genShaders.cpp
	g++ -Wall genShaders.cpp -o genShaders

clean: 
	rm main 
