#pragma once
#include <cstddef>
#include <stdexcept>

namespace CoreDS {
	template <typename T>
	class LinkedList {
	private:
		//Node节点
		struct Node {
		T data;
		Node* next;

		Node(const T& t) : data(t), next(nullptr) {} //Node构造函数
	};

	//成员变量
	Node* m_head;
	size_t m_size;


	public:
		//默认构造函数
		LinkedList() : m_head(nullptr), m_size(0) {}

		//带参构造函数
		LinkedList(const T& t) : m_head(new Node(t)), m_size(1) {}

		//析构函数
		~LinkedList() {
			Node* current = m_head;
			while (current != nullptr) {
				Node* next_node = current->next;
				delete current;
				current = next_node;
			}
		}

		//头部插入
		void push_front(const T& t) {
			Node* new_node = new Node(t);
			new_node->next = m_head;
			m_head = new_node;
			m_size++;
		}
		
		//尾部插入
		void push_back(const T& t) {
			Node* new_node = new Node(t);
			if (m_head == nullptr) {
				m_head = new_node;
				m_size++;
				return;
			}
			Node* current = m_head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = new_node;
			m_size++;
		}

		//头部删除
		void pop_front() {
			if (m_head == nullptr) {
				return;
			}
			Node* delete_node = m_head;
			m_head = m_head->next;
			delete delete_node;
			m_size--;
		}

		//尾部删除
		void pop_back() {
			if (m_head == nullptr) {
				return;
			 }
			if (m_head->next == nullptr) {
				delete m_head;
				m_head = nullptr;
				m_size--;
				return;
			}
			Node* delete_node = m_head;
			Node* pre_node = nullptr;
			while (delete_node->next != nullptr) {
				pre_node = delete_node;
				delete_node = delete_node->next;
			}
			pre_node->next = nullptr;
			delete delete_node;
			m_size--;
		}

		//下标[]访问
		//可修改版本
		T& operator[](size_t index) {
			if (index >= m_size) {
				throw std::out_of_range("LinkedList index out of bounds!");
			}
			Node* current_node = m_head;
			while (index--) {
				current_node = current_node->next;
			}
			return current_node->data;
		}
		//不可修改版本
		const T& operator[](size_t index) const {
			if (index >= m_size) {
				throw std::out_of_range("LinkedList index out of bounds!");
			}
			Node* current_node = m_head;
			while (index--) {
				current_node = current_node->next;
			}
			return current_node->data;
		}

		//返回大小
		size_t size() const {
			return m_size;
		}
	};
}