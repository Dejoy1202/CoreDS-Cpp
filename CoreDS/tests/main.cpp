#include <iostream>
#include <cassert>
#include <stdexcept>
#include "Vector.h"
#include "LinkedList.h"
#include "DoublyLinkedList.h"
#include "ArrayStack.h"
#include "LinkedStack.h"
#include "LinkedQueue.h"
#include "ArrayQueue.h"


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

void test_LinkedQueue() {
    CoreDS::LinkedQueue<int> queue;

    // 1. 空队列异常拦截测试
    bool caught = false;
    try { queue.front(); }
    catch (const std::out_of_range&) { caught = true; }
    assert(caught);

    // 2. 入队测试 (先进)
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    assert(queue.front() == 10); // 队头应该是最早进来的 10
    assert(queue.back() == 30);  // 队尾应该是最后进来的 30

    // 3. 出队测试 (先出)
    queue.dequeue();
    assert(queue.front() == 20); // 10 走了，20 变成了新队头

    // 4. 独苗与清空测试
    queue.dequeue(); // 20 走
    queue.dequeue(); // 30 走 (独苗分支触发)

    caught = false;
    try { queue.dequeue(); }
    catch (const std::out_of_range&) { caught = true; }
    assert(caught); // 再次出队应该爆炸

    std::cout << "LinkedQueue (单链表队列) 测试完美通过！\n";
}

void test_ArrayQueue() {
    // 初始容量给 2，强制触发扩容
    CoreDS::ArrayQueue<int> queue(2);

    // 1. 空队列异常拦截测试
    bool caught = false;
    try { queue.front(); }
    catch (const std::out_of_range&) { caught = true; }
    assert(caught);

    // 2. 基本入队测试
    queue.enqueue(10);
    queue.enqueue(20);
    assert(queue.front() == 10);
    assert(queue.back() == 20);

    // 3. 环形游标与扩容联合测试
    // 先出一个，让 head 往后走，制造出环形状态
    queue.dequeue();
    // 此时队列里只有 20，head = 1, tail = 0 (如果没扩容的话)

    // 再入队两个，强制触发扩容拉直逻辑
    queue.enqueue(30);
    queue.enqueue(40);

    // 验证扩容后的顺序是否正确
    assert(queue.front() == 20); // 队头依然是 20
    assert(queue.back() == 40);  // 队尾是新来的 40

    // 4. 清空测试
    queue.dequeue(); // 出 20
    queue.dequeue(); // 出 30
    queue.dequeue(); // 出 40

    caught = false;
    try { queue.dequeue(); }
    catch (const std::out_of_range&) { caught = true; }
    assert(caught);

    std::cout << "ArrayQueue (动态环形数组队列) 测试完美通过!\n";
}
int main() {
    //test_Vector();
    //test_LinkedList();
    //test_DoublyLinkedList();
    //test_ArrayStack();
    //test_LinkedStack();
    //test_LinkedQueue();
    test_ArrayQueue();
    return 0;
}