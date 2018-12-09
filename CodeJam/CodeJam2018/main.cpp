#include<vector>
#include<iostream>
//For a google test problem to find the # of students 
int rowFind(std::vector<int> &A){
	std::vector<int> rows;
	bool placed = false;
	rows.push_back(A[0]);
	for (int i = 1; i < A.size(); i++){
		placed = false;
		for (int j = 0; j < rows.size() && !placed; j++){
			if (A[i] < rows[j]){
				rows[j] = A[i];
				placed = true;
			}
		}
		if(!placed){
			rows.push_back(A[i]);
		}
		std::cout << '\n';
	}
	return rows.size();
}

int main(){
	std::vector<int> v = {15,10,9,8,8,7,6,7,10,2,6,3,8,15,0,22,1,12,2};
	std::cout << rowFind(v) << std::endl;
}
