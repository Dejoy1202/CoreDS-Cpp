#pragma once

#include<cstddef>
#include <stdexcept>

namespace CoreDS {
	template <typename T>
	class LinkedStack {
	private:
		struct Node {
			T data;
			Node* next;

			Node(const T& t) : data(t), next(nullptr) {}
		};

		Node* m_top;
		size_t m_size;

	public:
		//构造函数
		LinkedStack() : m_top(nullptr), m_size(0) {}
		//析构函数
		~LinkedStack() {
			Node* delete_node = m_top;
			while (delete_node != nullptr) {
				Node* next_node = delete_node->next;
				delete delete_node;
				delete_node = next_node;
			}
		}

		//压栈
		void push(const T& t) {
			Node* new_node = new Node(t);
			new_node->next = m_top;
			m_top = new_node;
			m_size++;
		}

		//出栈
		void pop() {
			if (m_size == 0) {
				throw std::out_of_range("Stack is empty!");
			}
			Node* delete_node = m_top;
			m_top = m_top->next;
			delete delete_node;
			m_size--;
		}

		//验栈
		T& top() {
			if (m_size == 0) {
				throw std::out_of_range("Stack is empty!");
			}
			return m_top->data;
		}

	};

}