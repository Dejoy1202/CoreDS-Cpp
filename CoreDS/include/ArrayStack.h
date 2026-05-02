#pragma once

#include<cstddef>
#include <stdexcept>

namespace CoreDS {
	template <typename T>
	class ArrayStack {
	private:
		T* m_data;
		size_t m_capacity;
		size_t m_top;

	public:
		//构造函数
		ArrayStack(size_t capacity = 10) : m_data(new T[capacity]), m_capacity(capacity), m_top(0) {}

		//析构函数
		~ArrayStack() {
			delete[] m_data;
		}

		//压栈
		void push(const T& t) {
			if (m_top == m_capacity) {
				size_t newcapacity = m_capacity == 0 ? 1 : 2 * m_capacity;
				T* newdata = new T[newcapacity];
				for (size_t i = 0; i < m_top; i++) {
					newdata[i] = m_data[i];
				}
				delete[] m_data;
				m_data = newdata;
				m_capacity = newcapacity;
			}
			m_data[m_top++] = t;
		}

		//验栈
		T& top() {
			if (m_top == 0) {
				throw std::out_of_range("Stack is empty!");
			}
			return m_data[m_top - 1];
		}

		//出栈
		void pop() {
			if (m_top == 0) {
				throw std::out_of_range("Stack is empty!");
			}
			m_top--;
		}

	};
}
