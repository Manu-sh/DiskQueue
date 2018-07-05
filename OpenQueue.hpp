#pragma once
#include "DiskQueue.h"
#include <memory>
#include <cstdlib>

template <typename T>
class OpenQueue {

	public:
		OpenQueue(const char *file);
		~OpenQueue();

		uint32_t max_elements() const noexcept;
		bool empty() const noexcept;
		bool push(const T &o);
		T front() const; /* calls to front have a cost so don't abuse */
		T pop();

	private:
		DiskQueue *queue;
};
