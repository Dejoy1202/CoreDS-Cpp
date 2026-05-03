#pragma once

#include<cstddef>
#include <stdexcept>

namespace CoreDS {
	template <typename T>
	class LinkedQueue {
	private:
		struct Node {
			T data;
			Node* next;
			Node(const T& t) : data(t), next(nullptr) {}
		};

		Node* m_head;
		Node* m_tail;
		size_t m_size;

	public:
		//构造函数
		LinkedQueue() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

		//析构函数
		~LinkedQueue() {
			while (m_head != nullptr) {
				Node* delete_node = m_head;
				m_head = m_head->next;
				delete delete_node;
			}
		}

		//入队
		void enqueue(const T& t) {
			Node* new_node = new Node(t);
			if (m_size == 0) {
				m_head = new_node;
				m_tail = new_node;
				m_size++;
				return;
			}
			m_tail->next = new_node;
			m_tail = new_node;
			m_size++;
		}

		//出队
		void dequeue() {
			if (m_size == 0) {
				throw std::out_of_range("Queue is empty!");
			}
			if (m_size == 1) {
				delete m_head;
				m_head = nullptr;
				m_tail = nullptr;
				m_size--;
				return;
			}
			Node* delete_node = m_head;
			m_head = m_head->next;
			delete delete_node;
			m_size--;
		}

		T& front() {
			if (m_size == 0) {
				throw std::out_of_range("Queue is empty!");
			}
			return m_head->data;
		}
		T& back() {
			if (m_size == 0) {
				throw std::out_of_range("Queue is empty!");
			}
			return m_tail->data;
		}
	};
}
