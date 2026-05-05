#pragma once

#include<cstddef>
#include <stdexcept>

namespace CoreDS {
	template <typename T>
	class MaxHeap {
	private:
		T* m_data;
		size_t m_capacity;
		size_t m_size;

		//扩容
		void reallocate(size_t new_capacity) {
			T* new_data = new T[new_capacity];
			for (size_t i = 0; i < m_size; i++) {
				new_data[i] = m_data[i];
			}
			delete[] m_data;
			m_data = new_data;
			m_capacity = new_capacity;
		}

		//上浮
		void shiftUp(size_t index) {
			while (index > 0) {
				if (m_data[(index - 1) / 2] >= m_data[index]) {
					return;
				}
				else {
					T temp = m_data[(index - 1) / 2];
					m_data[(index - 1) / 2] = m_data[index];
					m_data[index] = temp;
					index = (index - 1) / 2;
				}
			}
		}
		//下沉
		void shiftDown(size_t index) {
			while (2 * index + 1 < m_size) {
				size_t max_index = 2 * index + 1;
				if (2 * index + 2 < m_size) {
					if (m_data[2 * index + 2] > m_data[max_index]) {
						max_index++;
					}
				}
				if (m_data[index] >= m_data[max_index]) {
					return;
				}
				else {
					T temp = m_data[index];
					m_data[index] = m_data[max_index];
					m_data[max_index] = temp;
					index = max_index;
				}
			}
		}

	public:
		
		//构造函数
		MaxHeap(size_t init_capacity = 10) : m_capacity(init_capacity == 0 ? 1 : init_capacity), m_size(0) {
			m_data = new T[m_capacity];
		}
		
		//析构函数
		~MaxHeap() {
			delete[] m_data;
		}

		//拿走最大值
		T pop() {
			if (m_size == 0) {
				throw std::out_of_range("MaxHeap is empty!");
			}
			T max_val = m_data[0];
			m_data[0] = m_data[m_size - 1];
			m_size--;
			shiftDown(0);
			return max_val;
		}

		//插入
		void insert(const T& t) {
			if (m_size == m_capacity) {
				reallocate(2 * m_capacity);
			}
			m_data[m_size++] = t;
			shiftUp(m_size - 1);
		}

		//查看最大值
		T top() const {
			if (m_size == 0) {
				throw std::out_of_range("MaxHeap is empty!");
			}
			return m_data[0];
		}

		//判断是否为空
		bool empty() const {
			return m_size == 0;
		}

		//返回大小
		size_t size() const {
			return m_size;
		}
	};
}
