#include "OpenQueue.hpp"

#include <cassert>
#include <string>

/* instantiation point */
template class OpenQueue<std::string>;

template <typename T>
OpenQueue<T>::OpenQueue(const char *file) {
	assert((queue = diskqueue_open(file)));
}

template <typename T>
OpenQueue<T>::~OpenQueue() {
	diskqueue_close(queue);
}

template <typename T>
uint32_t OpenQueue<T>::max_elements() const noexcept {
	return diskqueue_max_elements();
}

template <typename T>
bool OpenQueue<T>::empty() const noexcept {
	return diskqueue_empty(queue);
}

template <>
bool OpenQueue<std::string>::push(const std::string &o) {
	UserData data{(void *)o.c_str(), (uint32_t)o.length()};
	return diskqueue_push(queue, data);
}

template <>
std::string OpenQueue<std::string>::front() const {
	UserData data{diskqueue_front(queue)};
	std::string ret{(const char *)data.data, (uint32_t)data.size};
	free(data.data);
	return ret;
}

template <>
std::string OpenQueue<std::string>::pop() {
	UserData data{diskqueue_pop(queue)};
	std::string ret{(const char *)data.data, (uint32_t)data.size};
	free(data.data);
	return ret;
}

