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

using namespace std;

// checkVertices -- look for repeat vertices in vertex vector
//                  input is a vertex, and output is the index
//                  of the vertex in the vertex vector. Output is
//                  appended to the vertex vecotr if the vertex is not
//                  int the vector, and the output is to the index of the 
//                  newly appended vertex
// Inputs: 
//          vertices: vector vertex vectors
//          newVertex: vertex vector to look for in existing vertex list
//          numVertices: the current number of vertices in the list
//
// Output: index of newVertex in the vertex array
int checkVertices(vector<vector<float>> &vertices, vector<float> newVertex, int numVertices){
    // Output index as iterator type
    auto targetIndex_it = find(vertices.begin(), vertices.end(), newVertex);
    // cast to integer
    int targetIndex = distance(vertices.begin(), targetIndex_it);
    if (targetIndex == numVertices){
        vertices.push_back(newVertex);
    }
    return targetIndex;

}

// glVehicleData -- class to hold vertex data used to render 
//                using openGL
class glVehicleData {
    public:
	// Constructor
	glVehicleData(string stl_file){
	     // stl file source
             string source_stl_file = stl_file;

             // Vertex and index arrays
	     vector<float> vertices_vec;
	     vector<unsigned int> indices_vec;

	     // Number of primitives and vertices 
	     unsigned int num_Primitives, num_vertices; 
	}


	// Method to generate vertex and 
	// index arrays
	void genBaseVertexData(void){
	    // Open stl file

            // Loop over stl file words

		// look for "facet" >> primitive indicator
		// look for "vertex" >> vertex indicator  
		// load vertex into buffer
		// compare vertex with previous vertices
		// update vertices if needed, add new index vector
		// record number of primitives, vertices, and indices
        	
	}

	// Method to export data to base program in the 
	// format of C arrays
	voidExportVertexData(float* vertices, int vertices_len, int* indices, int indices_len){
	
	}
}
