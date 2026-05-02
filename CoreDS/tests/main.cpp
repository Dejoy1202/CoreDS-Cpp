#include <iostream>
#include <cassert>
#include <stdexcept>
#include "Vector.h"
#include "LinkedList.h"
#include "DoublyLinkedList.h"
#include "ArrayStack.h"
#include "LinkedStack.h"


void test_Vector() {
    // 1. 测试初始状态
    CoreDS::Vector<int> vec;
    assert(vec.size() == 0);

    // 2. 测试插入与动态扩容
    for (int i = 0; i < 100; i++) {
        vec.push_back(i);
    }
    assert(vec.size() == 100);
    assert(vec[0] == 0);
    assert(vec[50] == 50);
    assert(vec[99] == 99);

    // 3. 测试修改
    vec[0] = 999;
    assert(vec[0] == 999);

    // 4. 测试尾部删除
    vec.pop_back();
    assert(vec.size() == 99);
    assert(vec[98] == 98); // 原来的最后一个是99，被删了，现在最后一个是98

    // 5. 测试越界异常拦截
    bool is_caught = false;
    try {
        int boom = vec[9999]; // 故意越界
    }
    catch (const std::out_of_range& e) {
        is_caught = true; // 如果成功捕获异常，把标志位置为 true
    }
    assert(is_caught == true); // 断言：必须成功抛出并捕获异常！

    std::cout << "Vector 所有核心功能与扩容机制单元测试通过！\n";
}


void test_LinkedList() {
    CoreDS::LinkedList<int> list;

    // 1. 测试初始状态
    assert(list.size() == 0);

    // 2. 测试尾部插入
    list.push_back(10);
    list.push_back(20);
    assert(list.size() == 2);
    assert(list[0] == 10);
    assert(list[1] == 20);

    // 3. 测试头部插入
    list.push_front(5);
    assert(list.size() == 3);
    assert(list[0] == 5);   // 头插后，5 变成了第一个
    assert(list[1] == 10);

    // 4. 测试删除
    list.pop_back();
    assert(list.size() == 2);
    assert(list[1] == 10); // 20 被删了，现在第二个应该是 10

    std::cout << "LinkedList 所有核心功能单元测试通过！\n";
}

void test_DoublyLinkedList() {
    CoreDS::DoublyLinkedList<int> list;

    // 1. 初始状态
    assert(list.size() == 0);

    // 2. 尾部极速插入 (O(1))
    list.push_back(10);
    list.push_back(20);
    assert(list.size() == 2);
    assert(list.front() == 10);
    assert(list.back() == 20);

    // 3. 头部极速插入 (O(1))
    list.push_front(5);
    assert(list.size() == 3);
    assert(list.front() == 5);
    assert(list.back() == 20);

    // 4. 尾部极速删除
    list.pop_back();
    assert(list.size() == 2);
    assert(list.back() == 10); // 20被删了，现在尾巴变成了10

    // 5. 头部极速删除 (O(1))
    list.pop_front();
    assert(list.size() == 1);
    assert(list.front() == 10);
    assert(list.back() == 10);

    // 6. 清空链表测试
    list.pop_front();
    assert(list.size() == 0);

    // 7. 异常拦截测试
    bool caught = false;
    try {
        int boom = list.front();
    }
    catch (const std::out_of_range& e) {
        caught = true;
    }
    assert(caught == true);

    std::cout << "DoublyLinkedList 所有O(1)操作单元测试通过！\n";
}

void test_ArrayStack() {
    // 传入较小的初始容量 2，强制在第三次 push 时触发底层的扩容逻辑
    CoreDS::ArrayStack<int> stack(2);

    // 1. 空栈异常测试
    bool caught = false;
    try {
        stack.top();
    }
    catch (const std::out_of_range&) {
        caught = true;
    }
    assert(caught);

    // 2. 压栈与扩容测试
    stack.push(10);
    stack.push(20);
    stack.push(30); // 此时应当触发扩容
    assert(stack.top() == 30);

    // 3. 出栈测试
    stack.pop();
    assert(stack.top() == 20);

    // 4. 清空与越界出栈测试
    stack.pop();
    stack.pop();
    caught = false;
    try {
        stack.pop();
    }
    catch (const std::out_of_range&) {
        caught = true;
    }
    assert(caught);

    std::cout << "ArrayStack 测试通过\n";
}

void test_LinkedStack() {
    CoreDS::LinkedStack<int> stack;

    // 1. 空栈异常测试
    bool caught = false;
    try { stack.top(); }
    catch (const std::out_of_range&) { caught = true; }
    assert(caught);

    // 2. 压栈测试
    stack.push(100);
    stack.push(200);
    assert(stack.top() == 200);

    // 3. 出栈测试
    stack.pop();
    assert(stack.top() == 100);

    // 4. 清空与越界出栈测试
    stack.pop();
    caught = false;
    try { stack.pop(); }
    catch (const std::out_of_range&) { caught = true; }
    assert(caught);

    std::cout << "LinkedStack 测试通过\n";
}
int main() {
    //test_Vector();
    //test_LinkedList();
    //test_DoublyLinkedList();
   test_ArrayStack();
   test_LinkedStack();
    return 0;
}