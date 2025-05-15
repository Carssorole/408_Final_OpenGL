#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#define vertexShaderPath "src/vertexShader.shader"
#define fragmentShaderPath "src/fragmentShader.shader"


GLuint loadShaders(char *, char *);

int main() {
	GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    
    //this creates an array that represents 3 3D vectors that represent vertices
    static const GLfloat vertices[] = {-1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
    

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //calling out shaders
    GLuint programID = loadShaders(vertexShaderPath, fragmentShaderPath);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0, 0.0, 0.4, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //shader call
        glUseProgram(programID);

        //draw stuff
        //this is the display loop of the program, this is where animation drawing will happen.
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

GLuint loadShaders(char * vertex_file_path, char * fragment_file_path) { 
//call from files and creates shaders for created objects to build from
    
    //create shader object IDs for GL workflow
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    
    //import files and read to "strings"
    FILE * vertexShaderFile = fopen(vertex_file_path, "r+"); //problem area right here!!
    FILE * fragmentShaderFile = fopen(fragment_file_path, "r+");

    if (vertexShaderFile == NULL) {
        printf("Vertex Shader file not loaded");
    }
    if (fragmentShaderFile == NULL) {
        printf("Fragment Shader file not loaded");
    }
    
    fseek(vertexShaderFile, 0, SEEK_END);
    int vertexShaderCodeSize = ftell(vertexShaderFile); //windows ass naming conventions
    fseek(vertexShaderFile, 0, SEEK_SET);
    char * vertexShaderCode = malloc(vertexShaderCodeSize * sizeof(char));
    fread(vertexShaderCode, sizeof(char), vertexShaderCodeSize, vertexShaderFile);
    
    fseek(fragmentShaderFile, 0, SEEK_END);
    int fragmentShaderCodeSize = ftell(fragmentShaderFile); 
    fseek(fragmentShaderFile, 0, SEEK_SET);
    char * fragmentShaderCode = malloc(fragmentShaderCodeSize * sizeof(char));
    fread(fragmentShaderCode, sizeof(char), fragmentShaderCodeSize, fragmentShaderFile);
    


    //compile and check the shaders
    GLint result = GL_FALSE;
    int infoLogLength;

    const char * vertexSourcePointer = vertexShaderCode; //vertex comp
    glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderID);

    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result); //vertex check
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        printf("ERROR--- err Loading compiling Vertex Shader");
    }

    const char * fragmentSourcePointer = fragmentShaderCode; //fragment comp
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderID);

    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result); // fragment check
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        printf("ERROR --- err Loading compiling Fragment Shaders");
    }


    //link and check the program
    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        printf("ERROR--- err Linking Program and Shaders");
    }    

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    fclose(vertexShaderFile);
    fclose(fragmentShaderFile);

    return programID;
}
