#pragma once
#include<cstddef>


namespace CoreDS {
	template <typename T>
	class DoublyLinkedList {
	private:
		//节点定义
		struct Node {
			T data;
			Node* pre;
			Node* next;

			Node(const T& t) : data(t), pre(nullptr), next(nullptr) {}
		};

		Node* m_head;
		Node* m_tail;
		size_t m_size;


	public:
		//无参构造函数
		DoublyLinkedList() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

		//有参构造函数
		explicit DoublyLinkedList(const T& t) : m_head(new Node(t)), m_tail(m_head), m_size(1) {}

		//析构函数
		~DoublyLinkedList() {
			Node* current = m_head;
			while (current != nullptr) {
				Node* delete_node = current;
				current = current->next;
				delete delete_node;
			}
		}

		//头部插入
		void push_front(const T& t) {
			if (m_head == nullptr) {
				m_head = new Node(t);
				m_tail = m_head;
				m_size++;
				return;
			}
			Node* new_node = new Node(t);
			new_node->next = m_head;
			m_head->pre = new_node;
			m_head = new_node;
			m_size++;
		}

		//尾部插入
		void push_back(const T& t) {
			if (m_head == nullptr) {
				m_head = new Node(t);
				m_tail = m_head;
				m_size++;
				return;
			}
			Node* new_node = new Node(t);
			new_node->pre = m_tail;
			m_tail->next = new_node;
			m_tail = new_node;
			m_size++;
		}

		//头部删除
		void pop_front() {
			if (m_head == nullptr) {
				return;
			}
			if (m_head == m_tail) {
				delete m_head;
				m_head = nullptr;
				m_tail = nullptr;
				m_size--;
				return;
			}
			Node* delete_node = m_head;
			m_head = m_head->next;
			m_head->pre = nullptr;
			delete delete_node;
			m_size--;
		}

		//尾部删除
		void pop_back() {
			if (m_head == nullptr) {
				return;
			}
			if (m_head == m_tail) {
				delete m_head;
				m_head = nullptr;
				m_tail = nullptr;
				m_size--;
				return;
			}
			Node* delete_node = m_tail;
			m_tail = m_tail->pre;
			m_tail->next = nullptr;
			delete delete_node;
			m_size--;
		}
		//获取链表大小
		size_t size() const {
			return m_size;
		}

		//头部数据 
		T& front() {
			if (m_head == nullptr) {
				throw std::out_of_range("DoublyLinkedList is empty!");
			}
			return m_head->data;
		}

		//尾部数据
		T& back() {
			if (m_tail == nullptr) {
				throw std::out_of_range("DoublyLinkedList is empty!");
			}
			return m_tail->data;
		}
	};
}
