#pragma once

#include<cstddef>
#include <stdexcept>
#include<iostream>

namespace CoreDS {
	template <typename T>
	class BST {
	private:
		struct Node {
			T data;
			Node* left;
			Node* right;
			Node(const T& t) : data(t), left(nullptr), right(nullptr) {}
		};

		Node* m_root;

		//辅助析构函数
		void destroy(Node* node) {
			if (node == nullptr) {
				return;
			}
			destroy(node->left);
			destroy(node->right);
			delete node;
		}

		void InOrderHelper(Node* node) const {
			if (node == nullptr) {
				return;
			}
			InOrderHelper(node->left);
			std::cout << node->data << " ";
			InOrderHelper(node->right);
		}

		//辅助删除函数递归版本
		Node* removeHelper(Node* node, const T& t) {
			if (node == nullptr) {
				return nullptr;
			}
			if (node->data < t) {
				node->right = removeHelper(node->right, t);
			}
			else if (node->data > t) {
				node->left = removeHelper(node->left, t);
			}
			else {
				if (node->left == nullptr) {
					Node* temp = node->right;
					delete node;
					return temp;
				}
				else if (node->right == nullptr) {
					Node* temp = node->left;
					delete node;
					return temp;
				}
				else {
					Node* replace_node = node->right;
					while (replace_node->left != nullptr) {
						replace_node = replace_node->left;
					}
					node->data = replace_node->data;
					node->right = removeHelper(node->right, replace_node->data);
				}
			}
			return node;
		}

	public:
		//构造函数
		BST() : m_root(nullptr) {}
		//析构函数
		~BST() {
			destroy(m_root);
		}
		

		//插入操作
		void insert(const T& t) {
			if (m_root == nullptr) {
				m_root = new Node(t);
				return;
			}
			Node* new_node = new Node(t);
			Node* current = m_root;
			while (true) {
				if (t < current->data) {
					if (current->left == nullptr) {
						current->left = new_node;
						return;
					}
					current = current->left;
				}
				else {
					if (current->right == nullptr) {
						current->right = new_node;
						return;
					}
					current = current->right;
				}
			}
		}

		//查找函数
		bool contains(const T& t) const {
			Node* current = m_root;
			while (current != nullptr) {
				if (current->data == t) {
					return true;
				}
				else if (current->data < t) {
					current = current->right;
				}
				else {
					current = current->left;
				}
			}
			return false;
		}

		//中序遍历打印
		void printInOrder() const {
			InOrderHelper(m_root);
			std::cout << std::endl;
		}

		//删除节点迭代版本
		void remove(const T& t) {
			Node* prev = nullptr;
			Node* curr = m_root;
			while (curr != nullptr) {
				if (curr->data == t) {
					break;
				}
				else if (curr->data < t) {
					prev = curr;
					curr = curr->right;
				}
				else {
					prev = curr;
					curr = curr->left;
				}
			}
			if (curr == nullptr) {
				return;
			}
			if (curr->right == nullptr && curr->left == nullptr) {
				if (prev != nullptr) {
					if (prev->right == curr) {
						prev->right = nullptr;
					}
					else {
						prev->left = nullptr;
					}
					delete curr;
					return;
				}
				else {
					delete curr;
					m_root = nullptr;
					return;
				}
			}
			if (curr->left == nullptr) {
				if (prev != nullptr) {
					if (prev->right == curr) {
						prev->right = curr->right;
					}
					else {
						prev->left = curr->right;
					}
					delete curr;
					return;
				}
				else {
					m_root = m_root->right;
					delete curr;
					return;
				}
			}
			if (curr->right == nullptr) {
				if (prev != nullptr) {
					if (prev->right == curr) {
						prev->right = curr->left;
					}
					else {
						prev->left = curr->left;
					}
					delete curr;
					return;
				}
				else {
					m_root = m_root->left;
					delete curr;
					return;
				}
			}
			Node* replace_node = curr->right;
			Node* pre_node = curr;
			while (replace_node->left != nullptr) {
				pre_node = replace_node;
				replace_node = replace_node->left;
			}
			curr->data = replace_node->data;
			if (pre_node->left == replace_node) {
				pre_node->left = replace_node->right;
				delete replace_node;
			}
			else {
				pre_node->right = replace_node->right;
				delete replace_node;
			}
		}

		//删除节点递归版本
		void remove_recursive(const T& t) {
			m_root = removeHelper(m_root, t);
		}
		
	};
}