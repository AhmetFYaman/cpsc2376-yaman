#include <iostream>
#include <vector>
#include "Validation.h"
int main(){
	std::vector<int> nums;
	std::cout << "Give num for my vector \n";

	nums.push_back(20);
	nums.push_back(12);
	nums.push_back(17);
	nums.push_back(90);
	int user_vector{0};

	int sum{0};
    
    std::cout << "Give num for my vector \n";
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
	std::cout << "the total of this new vector: " << sum << ": \n";
	
	
	int multiple{0};
    std::cout << "Give me num for me to create a times table for: " << std::endl;

	std::vector<int> multiples;
	multiple = getValidInteger();

	for (int i = 1; i < 11; i++){     // im asuming this assignment was about manupilating vectors so I will try to do it like this.
		multiples.push_back(multiple*i);
	}
	for (int num : multiples){
		std::cout << num << " \n";
		}
	

	return 0;
 }
