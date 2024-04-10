
//#include <iostream>
//using namespace std;
//
//int superFib(int n) {
//	// TODO: implement this
//	int first = 1;
//	int second = 1;
//	int prev_sum = 2;
//	int number = 0;
//	if (n == 1 || n == 2) {
//		return 1;
//	}
//	else {
//		while (n - 2) {
//			number += prev_sum;
//			prev_sum += number;
//			n -= 1;
//		}
//	}
//	return number;
//
//};


#include <iostream>
using namespace std;

int superFib(int n) {
	// TODO: implement this
	int prev_sum = 2;
	int current_number = 1;
	int count = 1;
	if (n == 0 || n == 1) {
		return current_number;
	}
	else if (n < 0) {
		throw std::out_of_range("Cannot be a negative number!");
	}
	else {
		while (count != n) {
			current_number = prev_sum;
			prev_sum += current_number;
			count += 1;
		}
	}
	return current_number;

};

//#include <iostream>
//using namespace std;
//
//int superFib(int n) {
//	// TODO: implement this
//	if (n < 0) {
//		throw std::out_of_range("Cannot be negative number!");
//	}
//
//	if (n == 0 || n == 1) {
//		return 1;
//	}
//
//	if (n == 2) {
//		return 2;
//	}
//
//	return superFib(n-1) + superFib(n - 2) + superFib(n - 3);
//
//};

