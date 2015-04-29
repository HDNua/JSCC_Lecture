#include <iostream>

typedef std::string Exception; // �ӽ�; ���ܷ� string ��ü�� ������
class Stack {
    static const int MAX_STACK_SIZ = 10;
    int list[MAX_STACK_SIZ];
    int _count;
public:
    Stack() : _count(0) {} // ������ ũ�⸦ �ݵ�� 0���� �����ؾ� �Ѵ�
    void push(int data) { // ���ÿ� �����͸� �ִ´�
        if (is_full()) { // ������ ������ �����͸� ���� �� ���ٸ� ���� ó���Ѵ�
            throw Exception("������ ���� á���ϴ�.");
        }
        // ������ �������� �����͸� �ְ� ũ�⸦ ������Ų��
        list[_count++] = data;
    }
    int pop() { // ���ÿ��� �����͸� ������
        if (is_empty()) { // ������ ����ִٸ� ���� ó���Ѵ�
            throw Exception("������ ����ֽ��ϴ�.");
        }
        // ������ ũ�⸦ ���ҽ�Ų �� ������ �����͸� ��ȯ�Ѵ�
        return list[--_count];
    }
    int top() const { // ���ÿ� ���� �ֱٿ� �߰��� �����͸� ����
        if (is_empty()) { // ������ ����ִٸ� ���� ó���Ѵ�
            throw Exception("������ ����ֽ��ϴ�.");
        }
        return list[_count - 1]; // ������ ������ �����͸� ��ȯ�Ѵ�
    }
    // ������ ���� á�ٸ� true
    bool is_full() const { return _count == MAX_STACK_SIZ; }
    // ������ ����ִٸ� true
    bool is_empty() const { return _count == 0; }
    // ���ÿ� ����� �������� ���� �����´�
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