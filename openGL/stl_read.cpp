/***********************************************************
 *  stl_read.cpp -- contains code to read vertex data from *
 *                  an ascii stl file and generate the     *
 *                  vertex and element index arrays        *
 *                                                         *
 *  Author: Colton Acosta                                  *
 *                                                         *
 *  Date: 2/13/2022                                        *
***********************************************************/
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// stl_read header file
#include "stl_read.h"

// checkVertices -- look for repeat vertices in vertex vector
//                  input is a vertex, and output is the index
//                  of the vertex in the vertex vector. Output is
//                  appended to the vertex vector if the vertex is not
//                  int the vector, and the output is to the index of the 
//                  newly appended vertex
// Inputs: 
//          vertices: vector vertex vectors
//          newVertex: vertex vector to look for in existing vertex list
//
// Output: index of newVertex in the vertex array
int checkVertices(vector<vector<float>> &vertices, vector<float> newVertex){
    // Output index as iterator type
    auto targetIndex_it = find(vertices.begin(), vertices.end(), newVertex);
    // cast to integer
    int targetIndex = distance(vertices.begin(), targetIndex_it);

    // Determine vertex array length
    int numVertices = distance(vertices.begin(), vertices.end());

    // Append new vertices
    if (targetIndex == numVertices){
        vertices.push_back(newVertex);
    }
    return targetIndex;

}

// glVehicleData -- class to hold vertex data used to render 
//                using openGL

// Constructor
glVehicleData::glVehicleData(string filename){

    // Set filename
    stl_file = filename; 

    // set number of vertices to zero
    num_vertices = 0; 

}

// Method to generate vertex and 
// index arrays
void glVehicleData::genBaseVertexData(void){
    // Open stl file
    ifstream stl_sourceFile(stl_file);

    // Loop over stl file lines 
    string lineBuffer; // buffer to temporarily store file data
    vector<float> vertexBuffer; // buffer to temporarily store vertices 
    int existingIndex;
    while(getline(stl_sourceFile, lineBuffer)){
        // Look for "vertex"
	size_t vertexInd = lineBuffer.find("vertex");
	int vertexStringIndex = static_cast<int>(vertexInd);
	if (vertexStringIndex >=0){ // line contains a vertex
	    // load vertex into buffer
	    vertexBuffer.push_back(stof(lineBuffer.substr(16,12)));
	    vertexBuffer.push_back(stof(lineBuffer.substr(29,12)));
	    vertexBuffer.push_back(stof(lineBuffer.substr(42,12)));

            // compare vertex with previous vertices
 	    existingIndex = checkVertices(vertices, vertexBuffer); 
            indices.push_back(existingIndex);
		   
            // update vertices if needed, add new index vector
            if(existingIndex == num_vertices){
                // last vertex was new, update vertex count 
		num_vertices++;
	    } 
        }
	// Clear Buffers 
	vertexBuffer.clear();
	lineBuffer.clear();

	// determine number of primitives
        num_indices = distance(indices.begin(), indices.end()); 	
	num_primitives = num_indices/3;
    }
	   
    // Close source file 
    stl_sourceFile.close();	    

}

void glVehicleData::ExportVertexData(float* verticesArrayPtr, unsigned int* indicesArrayPtr){
    
    // Export vertices
    for (int i = 0; i < num_vertices; ++i){
        for (int j = 0; j < 3; ++j){
	    *(verticesArrayPtr + 3*i + j) = vertices[i][j];
	}
    }

    // Export indices
    for (int i = 0; i < num_indices; ++ i){
        *(indicesArrayPtr + i) = indices[i];
    }
}

void glVehicleData::printVertexData(void){

    // Check to see if data has been extracted from stl file
    if (num_vertices == 0){
        cout << "Error printing vertex data: no vertex data has been generated. Check that the stl file has been read." << endl;
	return ;
    }

    // loop over vertices in vector 
    for (int i = 0; i < num_vertices; ++i){
        cout << "Vertex " << i+1 << ": " << endl; 
        cout << "x: " << vertices[i][0] << " y: " << vertices[i][1] << " z: " << vertices[i][2] << endl; 	
    }

}

void glVehicleData::printIndexData(void){
	
    // Check to see if data has been extracted from stl file
    if (num_vertices == 0){
        cout << "Error printing index data: no vertex data has been generated. Check that the stl file has been read." << endl;
	return ;
    }

    // loop over indices in vector 
    for (int i = 0; i < num_primitives; ++i){
        cout << "Primitive " << i+1 << ": " << endl; 
        cout << indices[3*i] << ", " << indices[3*i+1] << ", " << indices[3*i+2] << endl; 	
    }

}

void glVehicleData::normalizeVertexData(float scale){

    // Find the maximum vertex entry
    float maxVal = 0.0;
    for (int i = 0; i < num_vertices; ++i){
        for (int j = 0; j < 3; ++j){
	    if (vertices[i][j] > maxVal){
	        maxVal = vertices[i][j];
	    }
	}
    }

    // Normailize all the vertex entries
    for (int i = 0; i < num_vertices; ++i){
        for (int j = 0; j < 3; ++j){
	    vertices[i][j] /= maxVal;
	    vertices[i][j] *= scale;
	}
    }
    cout << "Max Value: " << maxVal <<  endl;
}

void glVehicleData::centerVertexData(void){

    // Find the vertices' center of gravity
    float cgx = 0.0;
    float cgy = 0.0;
    float cgz = 0.0;
    for (int i = 0; i < num_indices; ++i){
        cgx += vertices[indices[i]][0];
	cgy += vertices[indices[i]][1];
	cgz += vertices[indices[i]][2];
    }
    cgx /= num_indices;
    cgy /= num_indices;
    cgz /= num_indices;
    
    // Center the vertices around the cg
    for (int i = 0; i < num_vertices; ++i){
        vertices[i][0] -= cgx;
	vertices[i][1] -= cgy;
	vertices[i][2] -= cgz;
    }

    cout << "average x: " << cgx << endl;
    cout << "average y: " << cgy << endl;
    cout << "average z: " << cgz << endl;

}
