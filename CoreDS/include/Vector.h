#pragma once
#include <cstddef>
#include <stdexcept>

namespace CoreDS {
	template <typename T>
	class Vector {
	private:
		T* m_data; //数据存放地址
		size_t m_size; //数组实际大小
		size_t m_capacity; //数组容量

		//1.扩容函数
		void reallocate(size_t newCapacity) {
			if (newCapacity > m_capacity) {
				T* newdata = new T[newCapacity];
				for (size_t i = 0; i < m_size; i++) {
					newdata[i] = m_data[i];
				}
				delete[] m_data; //释放旧内存
				m_data = newdata;
				m_capacity = newCapacity;
			}
		}


	public:
		//1.默认构造函数
		Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

		//2.带参构造函数
		explicit Vector(size_t initialCapacity)
			: m_data(nullptr), m_size(0), m_capacity(initialCapacity)
		{
			if (initialCapacity > 0) {
				m_data = new T[initialCapacity];
			}
		}

		//3.析构函数
		~Vector() {
			delete[] m_data;
		}

		//4.尾部插入函数
		void push_back(const T& value) {
			if (m_size == m_capacity) {
				if (m_capacity == 0) {
					reallocate(1);
				}
				else {
					reallocate(2 * m_size);
				}
			}
			m_data[m_size++] = value;
		}

		//返回大小
		size_t size() const {
			return m_size;
		}

		//返回容量
		size_t capacity() const {
			return m_capacity;
		}

		//删除最后一个元素
		void pop_back() {
			if (m_size > 0) m_size--;
		}

		//下标访问运算符
		//1.可修改
		T& operator[](size_t index) {
			if (index >= 0 && index < m_size) {
				return m_data[index];
			}
			else {
				throw std::out_of_range("Vector index out of bounds!");
			}
		}
		//2.不可修改
		const T& operator[](size_t index) const {
			if (index >= 0 && index < m_size) {
				return m_data[index];
			}
			else {
				throw std::out_of_range("Vector index out of bounds!");
			}
		}

		//拷贝函数
		Vector(const Vector& other)
			: m_data(nullptr), m_size(other.m_size), m_capacity(other.m_capacity)
		{
			if (m_capacity > 0) {
				m_data = new T[m_capacity];
				for (size_t i = 0; i < m_size; i++) {
					m_data[i] = other.m_data[i];
				}
			}
		}

		//操作符=重载
		Vector& operator=(const Vector& other) {
			if (this != &other) {
				delete[] this->m_data;
				this->m_size = other.m_size;
				this->m_capacity = other.m_capacity;
				if (m_capacity > 0) {
					this->m_data = new T[other.m_capacity];
					for (size_t i = 0; i < m_size; i++) {
						this->m_data[i] = other.m_data[i];
					}
				}
				else {
					m_data = nullptr;
				}
				
			}
			return *this;
		}
	};


}