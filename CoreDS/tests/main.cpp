#include <iostream>
#include <string>
#include "LinkedList.h" // 确保文件名一致

// 辅助函数：利用你写的 size() 和 operator[] 打印整个链表
template <typename T>
void printList(const CoreDS::LinkedList<T>& list, const std::string& name) {
    std::cout << name << " (size: " << list.size() << ") [ ";
    for (size_t i = 0; i < list.size(); i++) {
        std::cout << list[i] << (i < list.size() - 1 ? " -> " : "");
    }
    std::cout << " -> null ]\n";
}

int main() {
    std::cout << "========== LinkedList 暴力压测开始 ==========\n\n";

    // 1. 构造函数测试
    std::cout << "[1] 构造函数测试\n";
    CoreDS::LinkedList<int> list1;
    printList(list1, "默认构造 list1");

    CoreDS::LinkedList<int> list2(99);
    printList(list2, "带参构造 list2");
    std::cout << "------------------------------------------\n";

    // 2. 插入测试 (头插 & 尾插)
    std::cout << "[2] 插入功能测试\n";
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);
    printList(list1, "尾插 10,20,30后");

    list1.push_front(5);
    list1.push_front(1);
    printList(list1, "头插 5,1后     ");
    std::cout << "------------------------------------------\n";

    // 3. 下标修改测试 (operator[])
    std::cout << "[3] 下标修改测试\n";
    std::cout << "修改前 list1[2] 的值为: " << list1[2] << "\n";
    list1[2] = 888; // 触发非 const 版本的 []
    printList(list1, "将 list1[2] 改为888后");
    std::cout << "------------------------------------------\n";

    // 4. 删除测试 (头删 & 尾删)
    std::cout << "[4] 删除功能测试\n";
    list1.pop_front();
    printList(list1, "头删一次后     ");

    list1.pop_back();
    printList(list1, "尾删一次后     ");
    std::cout << "------------------------------------------\n";

    // 5. 极端边界与异常测试
    std::cout << "[5] 极端边界与异常测试\n";

    // 测试 5.1: 越界拦截
    try {
        std::cout << "尝试疯狂越界访问 list1[100]...\n";
        int boom = list1[100];
        std::cout << boom << "\n"; // 如果上一行没拦截住，这行就会打印
    }
    catch (const std::exception& e) {
        std::cout << ">> 成功拦截异常: " << e.what() << "\n";
    }

    // 测试 5.2: 空链表安全删除
    std::cout << "\n尝试对空链表进行删减...\n";
    CoreDS::LinkedList<int> emptyList;
    emptyList.pop_back();
    emptyList.pop_front();
    printList(emptyList, "空链表删除后状态");

    std::cout << "\n========== 所有测试通过，程序未崩溃！ ==========\n";

    return 0; // 此时所有的 LinkedList 都会触发析构函数，静默清理内存
}