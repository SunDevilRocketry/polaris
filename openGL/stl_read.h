#ifndef STL_READ_H
#define STL_READ_H
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
//
// Output: index of newVertex in the vertex array
int checkVertices(vector<vector<float>> &vertices, vector<float> newVertex);

// glVehicleData -- class to hold vertex data used to render 
//                using openGL
class glVehicleData {
    public:
	
        // stl file source
        string stl_file;

        // Vertex and index arrays
	vector<vector<float>> vertices;
	vector<unsigned int> indices;

	// Number of primitives and vertices 
	int num_vertices; 
	int num_indices;
	int num_primitives;
	
	// Constructor
	glVehicleData(string filename);

	// Method to generate vertex and 
	// index arrays
	void genBaseVertexData(void);

	// Method to export data to base program in the 
	// format of C arrays
	void ExportVertexData(float* verticesArrayPtr, int* indicesArrayPtr);

	// Method to print vertex data to the console
	void printVertexData(void);

	// Method to print the indices of each primitives vertices
	void printIndexData(void);
};
#endif
