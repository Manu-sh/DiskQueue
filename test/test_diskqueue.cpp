#include "DiskQueue.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <queue>
#include <cstdlib>
#include <limits>

#include "common.hpp"

using namespace std;
int main() {

	srand(time(0));
	queue<std::string> mq;
	std::ifstream file{"nums.dat"};

	const char *filename = "unit_test_diskqueue";
	unique_ptr<DiskQueue, void(*)(DiskQueue *)> mqueue {
		diskqueue_open(filename),
		diskqueue_close,
	};

	const auto &assert_userdata_pop_equals = [&mq](const UserData &ref) {
		assert(mq.front() == ref);
		mq.pop();
		free(ref.data);
	};

	const auto &assert_userdata_front_equals = [&mq](const UserData &ref) {
		assert(mq.front() == ref);
		free(ref.data);
	};

	assert(mqueue);
	assert(diskqueue_empty(mqueue.get()));

	std::string str = "test front";
	mq.emplace(str);

	assert(diskqueue_push(mqueue.get(), Data(str)));
	assert_userdata_front_equals(diskqueue_front(mqueue.get()));
	assert_userdata_pop_equals(diskqueue_pop(mqueue.get()));
	assert(diskqueue_empty(mqueue.get()));

	while (file >> str) {
		mq.emplace(str);
		assert(diskqueue_push(mqueue.get(), Data(str)));
	}

	while (!diskqueue_empty(mqueue.get())) {
		assert_userdata_front_equals(diskqueue_front(mqueue.get()));
		assert_userdata_pop_equals(diskqueue_pop(mqueue.get()));
	}

	assert(mq.empty());

}
