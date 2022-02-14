/*****************************************************************************
 * genShaders -- produce code from .glsl files that converts the contents of *
 *               the file into a constant string. The program either prints  *
 *               the output to the console or to an output file              *
 *                                                                           *
 * Author -- Colton Acosta                                                   *
 *                                                                           *
 * Date -- 2/12/2022                                                         *
*****************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>

using namespace std;

// File names
const char* vertexShader = "shaders/vertexShader.glsl";
const char* fragmentShader = "shaders/fragmentShader.glsl";
const char* shadersHeader = "shaders/shaders.h";

int main(int argc, char *argv[]){

    // Parse command line arguments
    bool console, file;
    if(argc < 2){
        cout << "Error: No command line arguments given" << endl;
	return -1;
    } else if (!strcmp(argv[1], "console")){
        console = true;
	file = false;
    } else if(!strcmp(argv[1], "file")){
	console = false;
	file = true;
    } else{
        cout << "Error: invalid command line argument" << endl;    
    }

    // Input File objects
    ifstream vertexShaderFile(vertexShader);
    ifstream fragmentShaderFile(fragmentShader);
    if(!vertexShaderFile.is_open()){
        cout << "Error: Failed to open file \"" << vertexShader << endl; 
	cout << "Check that file is in the working directory" << endl;
	return -1;
    }
    if(!fragmentShaderFile.is_open()){
        cout << "Error: Failed to open file \"" << fragmentShader << endl; 
	cout << "Check that file is in the working directory" << endl;
	return -1;
    }

    // Read data from file
    string linedata;
    string vertexShaderData, fragmentShaderData;
    vertexShaderData.append("const char *vertexShaderSource = ");
    while(!vertexShaderFile.eof()){
        getline(vertexShaderFile, linedata);
	if (linedata.length()){ // skips empty lines
	    vertexShaderData.append("\"");
	    vertexShaderData.append(linedata);
      	    vertexShaderData.append("\\n\"\n");
	}
    }
    vertexShaderData.append("\"\\0\";");
    fragmentShaderData.append("const char *fragmentShaderSource = ");
    while(!fragmentShaderFile.eof()){
        getline(fragmentShaderFile, linedata);
	if (linedata.length()){ // skips empty lines
	    fragmentShaderData.append("\"");
	    fragmentShaderData.append(linedata);
            fragmentShaderData.append("\\n\"\n");
	}
    }
    fragmentShaderData.append("\"\\0\";");

    // Export Data
    if (console){
	cout << endl;
	cout << "Vertex Shader Code: " << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << vertexShaderData << endl;
	cout << endl;

	cout << "Fragment Shader Code: " << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << fragmentShaderData << endl;
	cout << endl;
	} else if(file){
	     
        // Output file objects 
	ofstream shadersHeaderFile(shadersHeader);

	// Export Data
	shadersHeaderFile << "// ******************************AUTOMATICALLY GENERATED CODE**************************************** " << endl;
	shadersHeaderFile << vertexShaderData;
	shadersHeaderFile << endl;
	shadersHeaderFile << fragmentShaderData << endl;
	shadersHeaderFile << "// ************************END OF AUTOMATICALLY GENERATED CODE*************************************** " << endl;

	// Close output file objects
	shadersHeaderFile.close();
    }

    // Close all file objects
    vertexShaderFile.close();
    fragmentShaderFile.close();

    return 0;
}
