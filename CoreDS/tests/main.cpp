#include"Vector.h"
#include<iostream>

using namespace CoreDS;



int main() {
	Vector<int> vector(2);

	for (int i = 0; i < 5; i++) {
		vector.push_back(i * 10);
		std::cout << "当前大小为：" << vector.size() << " 容量为：" << vector.capacity() << std::endl;
	}
	vector.pop_back();
	std::cout << "当前大小为：" << vector.size() << " 容量为：" << vector.capacity() << std::endl;

	std::cout << vector[3] << std::endl;

	return 0;
}