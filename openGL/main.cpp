#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/****************************CALLBACK FUNCTIONS***************************/

// glfw callbacks -- display glfw errors on console
void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

// close window call back -- destroys window when window
// x is clicked by user
void closeWindow_callback(GLFWwindow* window){
    glfwDestroyWindow(window);
}

// window resize call back -- resizes the openGL rendering window when 
// the user resizes the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
/************************************************************************/

/************************MAIN CODE**************************************/

// Auto-generated shader code
#include "shaders/shaders.h"

int main(void){

    // Setup error callbacks to print glfw error 
    // messages to the console
    glfwSetErrorCallback(error_callback);

    // GLFW Initialization
    if (!glfwInit()){ 
        // Initialization Falied
	cout << "GLFW Initialization Failed" << endl;
	glfwTerminate();
	return -1;
    }
    // Force GLFW version 3 and Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Create window and openGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Rocket Visualization", NULL, NULL);
    if(!window){
        // Window or OpenGL context failure
    }
    glfwMakeContextCurrent(window); 
    glfwSetWindowCloseCallback(window, closeWindow_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GlAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    cout << "Failed to initialize GLAD" << endl;
    return -1;
    }

    // Set window coordinates
    glViewport(0, 0, 640, 480);

    // Vertex Shader Compilation
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success; // check if vertex shader compilation failed
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); 
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	cout << "Error: Vertex Shader Compilation Failed" << endl;
	return -1;
    }

    // OpenGL fragment shader compilation
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); // check if fragment shader compilation failed
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	cout << "Error: Fragment Shader Compilation Failed" << endl;
	return -1;
    }

    // Create the linked shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); // check if shader linking failed
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	cout << "Error: Shader linker failed" << endl;
	return -1;
    }

    // Use shader and delete vertex and fragment shaders
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Initial Draw Data
    float vertices[] = {
	0.5, 0.5, 0.0,
	0.5, -0.5, 0.0,
	-0.5, -0.5, 0,
        -0.5, 0.5, 0,	
    };
    unsigned int num_vertices = 6;
    unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
    };

    // Buffer Objects
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind Vertex Array Object
    glBindVertexArray(VAO);

    // Copy vertices to vertex Buffer for rendering
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // Copy Index array to element buffer for rendering
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
  
    // Event Loop
    while(!glfwWindowShouldClose(window)){

	// Background Color
	glClearColor(0.85, 0.9, 0.96, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Copy Data to buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	// Render Object
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, num_vertices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Update
	glfwSwapBuffers(window);
	glfwPollEvents();
	
    }

    // GLFW Termination
    glfwTerminate();

    return 0;
}
