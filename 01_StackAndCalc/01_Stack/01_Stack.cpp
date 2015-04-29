#include <iostream>

typedef std::string Exception; // 임시; 예외로 string 객체를 던진다
class Stack {
    static const int MAX_STACK_SIZ = 10;
    int list[MAX_STACK_SIZ];
    int _count;
public:
    Stack() : _count(0) {} // 스택의 크기를 반드시 0으로 설정해야 한다
    void push(int data) { // 스택에 데이터를 넣는다
        if (is_full()) { // 스택이 가득차 데이터를 넣을 수 없다면 예외 처리한다
            throw Exception("스택이 가득 찼습니다.");
        }
        // 스택의 마지막에 데이터를 넣고 크기를 증가시킨다
        list[_count++] = data;
    }
    int pop() { // 스택에서 데이터를 꺼낸다
        if (is_empty()) { // 스택이 비어있다면 예외 처리한다
            throw Exception("스택이 비어있습니다.");
        }
        // 스택의 크기를 감소시킨 후 마지막 데이터를 반환한다
        return list[--_count];
    }
    int top() const { // 스택에 가장 최근에 추가된 데이터를 본다
        if (is_empty()) { // 스택이 비어있다면 예외 처리한다
            throw Exception("스택이 비어있습니다.");
        }
        return list[_count - 1]; // 스택의 마지막 데이터를 반환한다
    }
    // 스택이 가득 찼다면 true
    bool is_full() const { return _count == MAX_STACK_SIZ; }
    // 스택이 비어있다면 true
    bool is_empty() const { return _count == 0; }
    // 스택에 저장된 데이터의 수를 가져온다
    int count() const { return _count; }
};

int main(void) {
    try {
        Stack stack;
        stack.push(1);
        stack.push(2);
        stack.push(3);
        while (stack.is_empty() == false) {
            int value = stack.pop();
            std::cout << value << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}