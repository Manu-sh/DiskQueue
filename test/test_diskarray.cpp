#include "DiskArray.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <array>
#include <cstdlib>
#include <limits>

#include "common.hpp"

using namespace std;
int main() {

	srand(time(0));
	std::array<std::string, 100> v;
	std::ifstream file{"nums.dat"};

	const char *filename = "unit_test_diskarray";
	unique_ptr<DiskArray, void(*)(DiskArray *)> arr{
		diskarray_open(filename),
		diskarray_close
	};

	const auto &assert_userdata_equals = [&v](const UserData &ref, uint32_t i) {
		assert(v[i] == ref);
		free(ref.data);
	};

	const auto &assert_no_userdata = [](const UserData &ref) {
		assert(ref.data == nullptr);
	};

	assert(arr);
	for (uint32_t i = 0; i < v.size(); i++) 
		assert_no_userdata(diskarray_access(arr.get(), 0));

	for (uint32_t i = 0; i < v.size(); i++) {
		file >> v[i];
		assert(diskarray_insert(arr.get(), i, Data(v[i])));
		assert_userdata_equals(diskarray_access(arr.get(), i), i);
	}

	for (uint32_t i = 0; i < v.size()*5; i++) {
		int x = rand() % v.size();
		assert_userdata_equals(diskarray_access(arr.get(), x), x);
	}

	for (uint32_t i = v.size(); i-- > 0;)
		assert_userdata_equals(diskarray_remove(arr.get(), i), i);

	for (uint32_t i = v.size(); i-- > 0;)
		assert_no_userdata(diskarray_remove(arr.get(), i));

	// TODO since the underlying structure of diskarray is dbm
	// and not a real array, v[MAX] is accessible

	assert_no_userdata(diskarray_remove(arr.get(), diskarray_max_elements()));
	assert_no_userdata(diskarray_access(arr.get(), diskarray_max_elements()));

	assert(diskarray_insert(arr.get(), diskarray_max_elements(), Data(v[3])));

	assert_userdata_equals(diskarray_access(arr.get(), diskarray_max_elements()), 3);
	assert_userdata_equals(diskarray_remove(arr.get(), diskarray_max_elements()), 3);

	assert_no_userdata(diskarray_remove(arr.get(), diskarray_max_elements()));
	assert_no_userdata(diskarray_access(arr.get(), diskarray_max_elements()));

	for (uint32_t i = 0; i < v.size(); i++) 
		assert_no_userdata(diskarray_access(arr.get(), 0));

	file.close();

}
