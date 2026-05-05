#pragma once

#include<cstddef>
#include<stdexcept>
#include<string>

namespace CoreDS {

	template <typename K>
	struct MyHash;

	template <>
	struct MyHash<int> {
		size_t operator()(const int& key) const {
			return static_cast<size_t>(key);
		}
	};

	template <>
	struct MyHash<std::string> {
		size_t operator()(const std::string& key) const {
			size_t hash = 5381;
			for (char c : key) {
				hash = ((hash << 5) + hash) + c;
			}
			return hash;
		}
	};

	template<typename K, typename V>
	class HashMap {
	private:
		struct Node {
			K key;
			V val;
			Node* next;

			Node(const K& k, const V& v) : key(k), val(v), next(nullptr) {}
		};

		Node** m_buckets;
		size_t m_capacity;
		size_t m_size;

		size_t hash(const K& key) const {
			return MyHash<K>{}(key) % m_capacity;
		}

	public:
		
		//构造函数
		HashMap(size_t init_capacity = 16) : m_capacity(init_capacity), m_size(0) {
			m_buckets = new Node * [m_capacity];
			for (size_t i = 0; i < m_capacity; i++) {
				m_buckets[i] = nullptr;
			}
		}

		//析构函数
		~HashMap() {
			for (size_t i = 0; i < m_capacity; i++) {
				while (m_buckets[i] != nullptr) {
					Node* delete_node = m_buckets[i];
					m_buckets[i] = m_buckets[i]->next;
					delete delete_node;
				}
			}
			delete[] m_buckets;
		}

		//put
		void put(const K& key, const V& val) {
			size_t index = hash(key);
			Node* current = m_buckets[index];
			while (current != nullptr) {
				if (current->key == key) {
					current->val = val;
					return;
				}
				current = current->next;
			}
			Node* new_node = new Node(key, val);
			new_node->next = m_buckets[index];
			m_buckets[index] = new_node;
			m_size++;
		}

		//get
		V get(const K& key) const {
			size_t index = hash(key);
			Node* current = m_buckets[index];
			while (current != nullptr) {
				if (current->key == key) {
					return current->val;
				}
				current = current->next;
			}
			throw std::out_of_range("Key not found!");
		}

		//remove
		void remove(const K& key) {
			size_t index = hash(key);
			Node* prev_node = nullptr;
			Node* curr_node = m_buckets[index];
			while (curr_node != nullptr && curr_node->key != key) {
				prev_node = curr_node;
				curr_node = curr_node->next;
			}
			if (curr_node == nullptr) {
				return;
			}
			else if (prev_node == nullptr) {
				m_buckets[index] = m_buckets[index]->next;
				delete curr_node;
				m_size--;
			}
			else {
				prev_node->next = curr_node->next;
				delete curr_node;
				m_size--;
			}
		}

		size_t size() const { return m_size; }
		bool empty() const { return m_size == 0; }


	};


}