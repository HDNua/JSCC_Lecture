#include <iostream>
typedef std::string Exception;
// ���� �Լ�
inline void clear_input_buffer() { // �Է¹ޱ� ���� �Է� ���۸� ����
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}
inline bool is_digit(char ch) { return ('0' <= ch && ch <= '9'); }
// ���ڰ� �������� Ȯ���Ѵ�
inline bool is_space(char ch) { return (ch == ' ' || ch == '\t' || ch == '\n'); }
// ���� ����
template <typename Data> // ���Ŀ� �����ο� ������ ����� ���� ���ø� Ŭ������ ����
class Stack {
    static const int MAX_STACK_SIZ = 256;
    Data _list[MAX_STACK_SIZ];
    int _count;
private:
    inline bool is_full() const { return _count == MAX_STACK_SIZ; }
public:
    Stack() : _count(0) {}
    void push(const Data &data) {
        if (is_full()) throw Exception("Stack is full");
        _list[_count++] = data;
    }
    Data pop() {
        if (is_empty()) throw Exception("Stack is empty");
        return _list[--_count];
    }
    Data top() const {
        if (is_empty()) throw Exception("Stack is empty");
        return _list[_count - 1];
    }
    inline bool is_empty() const { return _count == 0; }
    inline int count() const { return _count; }
};
// ����� �Լ�
int calculate_postfix(const char *postfix); // calculate postfix expression
int main(void) {
    try {
        int loop;
        std::cin >> loop;
        const int MAX_EXPR_LEN = 256;
        char postfix[MAX_EXPR_LEN] = "";
        while (loop-- > 0) {
            std::cout << "Enter expression: ";
            clear_input_buffer();
            std::cin.getline(postfix, MAX_EXPR_LEN); // ������ ������ ���� �Է¹޴´�
            std::cout << postfix << " : " << calculate_postfix(postfix) << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}
// ����
int calculate_postfix(const char *postfix) {
    char ch;
    int digit;
    Stack<int> paramStack;
    for (ch = *postfix; (ch = *postfix) != '\0'; ++postfix) {
        if (is_space(ch)) { // �����̸� �����Ѵ�
            continue;
        }
        else if (is_digit(ch)) { // �ǿ����ڶ�� ���ÿ� Ǫ�� �Ѵ�
            int value = 0;
            while (is_digit(*postfix)) {
                digit = *postfix++ - '0';
                value = 10 * value + digit;
            }
            paramStack.push(value);
            --postfix; // �ݺ��� ������ ++postfix�� ����ǹǷ� �� ĭ �ǵ�����
        }
        else {
            // ���ÿ��� �� ���� �ǿ����ڸ� ������
            int right = paramStack.pop();
            int left = paramStack.pop();
            int value = 0;
            // ȹ���� �����ڷ� �����Ѵ�
            switch (ch) {
            case '+': value = left + right; break;
            case '-': value = left - right; break;
            case '*': value = left * right; break;
            case '/': value = left / right; break;
            default: throw Exception("Invalid operator");
            }
            // ���� ����� �ٽ� ���ÿ� �ִ´�
            paramStack.push(value);
        }
    }
    if (paramStack.count() != 1) { // ���ÿ� ���� �ǿ����ڰ� 1���� �ƴϸ� ����
        throw Exception("Unhandled operand found");
    }
    return paramStack.pop(); // �ϳ� ���� �ǿ����ڸ� ��ȯ�Ѵ�
}