#include<vector>
#include<iostream>
#include<algorithm>
//For a google test problem to find the # of students
std::vector<int> nearestStores(std::vector<int> &stores, std::vector<int> &houses){

	//sort the stores
	std::sort(stores.begin(), stores.end());

	for(int i = 0 ; i <stores.size(); i++){
		std::cout<< stores[i] << ", ";
	}
	std::vector<int> distances;
	for(int h = 0; h < houses.size(); h++){
		int current_closest_dist = abs(houses[h] - stores[0]);
		int closest_store = 0;
		bool getting_closer = true;
		for(int s = 0; s < stores.size(); s++){
			int trial_dist = abs(houses[h] - stores[s]);
			if (trial_dist < current_closest_dist){
				current_closest_dist = trial_dist;
				closest_store = s;
			}
		}
		distances.push_back(stores[closest_store]);
	}
	return distances;

}

int main(){
	std::vector<int> stores = {48,45,0,11,11,12,15,65,2,92};
	std::vector<int> houses = {10, 15, 15, 200, 9,20};
	std::vector<int> ans = nearestStores(stores, houses);

	std::cout << "ANS = {";
	for(int i = 0; i < ans.size(); i++){
		std::cout << ans[i] << ", ";
	}
	std::cout << "}\n";
}
