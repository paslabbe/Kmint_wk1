#pragma once
#include <queue>

template<typename T, typename priority_t>
struct PriorityQueue {
	typedef std::pair<priority_t, T> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>,
	                    std::greater<PQElement>> elements;
	// using iterator = T *;
	// using const_iterator = const T *;

	inline bool empty() const {
		return elements.empty();
	}

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	T get() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}

	// iterator begin() { return &elements[0]; }
	// const_iterator cbegin() const { return &elements[0]; }
	// iterator end() { return &elements[elements.size()]; }
	// const_iterator cend() const { return &elements[elements.size()]; }
};
