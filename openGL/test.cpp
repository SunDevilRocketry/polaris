#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void func(vector<vector<int>> &vect){
    vector<int> buff;
    for (int i=0; i< 10; ++i){
	for (int j = 0; j<3; ++j){
	    buff.push_back(i*j);
	}
        vect.push_back(buff);
	buff.clear();
    } 
} 

int main(void){

    vector<vector<int>> myVector; 
    func(myVector);

    cout << "Target: " << endl;
    // Look for [0, 5, 10]
    vector<int> targetVec;
    targetVec.push_back(1);
    targetVec.push_back(1);
    targetVec.push_back(1);
    for (int i = 0; i < 3; ++i){
        cout << targetVec[i] << "," << " ";
    }
    cout << endl << endl;

    cout << "Vertices: " << endl;
    for (int i=0; i< 10; ++i){
	for (int j = 0; j<3; ++j){
            cout << myVector[i][j] << ", ";
	}
	cout << endl;
    } 
    cout << endl << endl;
    cout << "Result:";

    auto it = find(myVector.begin(), myVector.end(), targetVec);
    int index = distance(myVector.begin(), it);

    cout << index << endl;

    return 0;
}
