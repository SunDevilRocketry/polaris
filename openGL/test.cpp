#include <iostream>
#include <vector>

using namespace std;

void func(vector<int[3]> &vect){
    int buff[3];
    for (int i=0; i< 10; ++i){
	for (int j = 0; j<3; ++j){
	    buff[j] = i*j;
	}
        vect.push_back(buff);
    } 
}

int main(void){

    vector<vector<int>> myVector; 
    func(myVector);

    for (int i=0; i< 10; ++i){
	for (int j = 0; j<3; ++j){
	    cout << myVector[i][j] << " ";
	}
	cout << endl;
    } 

    return 0;
}
