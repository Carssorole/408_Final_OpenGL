#!/bin/bash

	echo "helloWrold"
	#gcc -lglfw3 -lOpenGL -lX11 -lpthread -lXrandr -lXi -ldl src/main.c -o app
	gcc src/main.c -lglfw -lGL -lGLEW -o app
