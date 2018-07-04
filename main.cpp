#include "OpenQueue.hpp"
#include <iostream>

using namespace std;
int main() {

	OpenQueue<std::string> test{"hello"};

	test.push("Hello");
	test.push("World");

	test.push("Hello");
	test.push("World");

	cout << "front: " << test.front() << endl;

	while (!test.empty())
		cout << test.pop() << endl;


}
