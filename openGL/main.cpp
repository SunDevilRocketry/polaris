#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// stl file read classes/functions
#include "stl_read.h"

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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

    // Read base vertex data from stl file
    glVehicleData rocket("CAD/rocket.stl");
    rocket.genBaseVertexData();
    rocket.centerVertexData();
    rocket.normalizeVertexData(0.8);
    int num_vertices = rocket.num_vertices;
    int num_indices = rocket.num_indices;

    // Initial Draw Data
    float vertices[num_vertices*3];
    unsigned int indices[num_indices];
    rocket.ExportVertexData(&vertices[0], &indices[0]);

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
