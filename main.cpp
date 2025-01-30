#include <iostream>
#include <vector>
#include "Validation.h"
int main(){
	std::vector<int> nums;

	nums.push_back(20);
	nums.push_back(12);
	nums.push_back(17);
	nums.push_back(90);
	int x{ 0 };
    
    std::cout << "Gimme num for my vector \n";
	x = getValidInteger();

	nums.push_back(x);
	
	std::cout << "My nums in my vector: \n";


	for (int num : nums){
		std::cout << num << " \n";
	}


	return 0;
 }
