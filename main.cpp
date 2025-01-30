#include <iostream>
#include <vector>
#include "Validation.h"
int main(){
	std::vector<int> nums;

	nums.push_back(20);
	nums.push_back(12);
	nums.push_back(17);
	nums.push_back(90);
	int user_vector{0};

	int sum{0};
    
    std::cout << "Gimme num for my vector \n";
	user_vector = getValidInteger();

	nums.push_back(user_vector);
	
	std::cout << "My nums in my vector: \n";


	for (int num : nums){
		std::cout << "original: " << num << " \n";
		num = num*2;
		}

	for (int num : nums){
		std::cout << "*new*: doubled: " << num << " \n";
		sum += num;
		}
		std::cout << "the total of this new vector: " << sum << ": ";
	
	std::cout << "GImme a number, I will find multiples and fiond vectors: " << std::endl; 
	int multiple{0};

	std::vector<int> multiples;
	multiple = getValidInteger();

	for (int i = 1; i < 11; i++){
		multiples.push_back(multiple*i);
		std::cout << multiples.at(i-1);
	}

	multiple = getValidInteger();
	

	return 0;
 }
