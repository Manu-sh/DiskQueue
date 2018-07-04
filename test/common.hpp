#include "UserData.h"
#include <string>
#include <utility>

static bool operator==(const UserData &a, const UserData &b) {

	assert(a.data && a.size);
	assert(b.data && b.size);

	std::string s[] = {
		{(const char *)a.data, a.size},
		{(const char *)b.data, b.size}
	};

	return s[0] == s[1];
}

static bool operator==(const UserData &a, const std::string &b) {
	assert(a.data && a.size);

	std::string s{(const char *)a.data, a.size};
	// std::cout << "cmp: " << s << " with " << b << std::endl;
	return s == b;
}

static bool operator==(const std::string &a, const UserData &b) {
	return b == a;
}

struct Data: UserData {
	explicit Data(std::string &s) {
		this->data = (void *)s.c_str();
		this->size = s.length();
	}
};
