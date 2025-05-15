# Start Here!!!
Here's how to start this project up for yourself.  First, dowload the repo, and give `chmod 777` to both shell scripts.  Then, run the simpler starter, next the build.sh.  There should then be a compiled "app" in the project folder.  run that executable, and you should have a window! and a red triangle.

## Starter Script
Dowloads and installs all the required packages to your LINUX machine.

## Build.sh
Compiles main.c and links it to the required libraries downloaded by the Starter script.  Outputs that to the "app" executible.

## Main.c
This, of course, is the main workspace, this is where the context and window creation happen.  As well, the render loop and loadShader function live here too.  In this file, there is code for creating a vertex group, buffer, and shader to create a red triangle in the window.

## The .shader Files
These files are the documents that are imported and compiled at run time to create the shaders in our program.  These files are written in a special type of C specifically for OpenGL shaders.  Vertex Shaders, describes the positions of the vertexes to the shader renderer.  Fragment Shaders is what creates the color of the shape created by the vertexes.
Those both are compiled and linked to the program in the main.c file.
