
#include <string>
using namespace std;

string caterpillar(int n)
{
	// [TO-DO] Complete the function below
	string temp = "<";
	while (n) {
		temp += "Q";
		n -= 1;
	}
	temp += "6";
	return temp;
}