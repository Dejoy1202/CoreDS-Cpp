#pragma once
#include <cstddef>
#include <stdexcept>

namespace CoreDS {
	template <typename T>
	class ArrayQueue {
	private:
		T* m_data;
		size_t m_head;
		size_t m_tail;
		size_t m_size;
		size_t m_capacity;

		//扩容函数
		void reallocate(size_t new_capacity) {
			T* new_data = new T[new_capacity];
			for (size_t i = 0; i < m_size; i++) {
				new_data[i] = m_data[(m_head + i) % m_capacity];
			}
			delete[] m_data;
			m_data = new_data;
			m_capacity = new_capacity;
			m_head = 0;
			m_tail = m_size;
		}

	public:
		//构造函数
		ArrayQueue(size_t capacity = 10) : m_data(nullptr), m_head(0), m_tail(0), m_size(0), m_capacity(capacity == 0 ? 1 : capacity) {
			m_data = new T[m_capacity];
		}
		
		//析构函数
		~ArrayQueue() {
			delete[] m_data;
		}

		//入队
		void enqueue(const T& t) {
			if (m_size == m_capacity) {
				reallocate(2 * m_capacity);
			}
			m_data[m_tail] = t;
			m_tail = (m_tail + 1) % m_capacity;
			m_size++;
		}
		
		//出队
		void dequeue() {
			if (m_size == 0) {
				throw std::out_of_range("Queue is empty!");
			}
			m_head = (m_head + 1) % m_capacity;
			m_size--;
		}

		T& front() {
			if (m_size == 0) {
				throw std::out_of_range("Queue is empty");
			}
			return m_data[m_head];
		}
		T& back() {
			if (m_size == 0) {
				throw std::out_of_range("Queue is empty");
			}
			if (m_tail == 0) {
				return m_data[m_capacity - 1];
			}
			return m_data[m_tail - 1];
		}

	};
}