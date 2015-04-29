#include <iostream>

// ���� ����
const int MAX_EXPR_LEN = 256;
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
int calculate(const char *expr); // calculate infix expression
int calculate_postfix(const char *postfix); // calculate postfix expression
int op_pri(char ch); // get operator's priority
// convert infix notation expression
//  to postfix notation expression
void infix_to_postfix(char *postfix, const char *infix);

int main(void) {
    try {
        int loop;
        std::cin >> loop;
        char expression[MAX_EXPR_LEN] = "";
        while (loop-- > 0) {
            std::cout << "Enter expression: ";
            clear_input_buffer();
            std::cin.getline(expression, MAX_EXPR_LEN); // ������ ������ ���� �Է¹޴´�
            std::cout << expression << " : " << calculate(expression) << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}

// ����
int calculate(const char *expr) { // calculate infix expression
    char postfix[MAX_EXPR_LEN] = "";
    infix_to_postfix(postfix, expr); // ���� ǥ����� ���� ǥ������� ��ȯ�Ѵ�
    return calculate_postfix(postfix); // ��ȯ�� ���� ǥ����� �м��ϰ� ��ȯ�Ѵ�
}
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
int op_pri(char ch) { // get operator's priority
    int priority = 0;
    switch (ch) {
    case '+': priority = 1; break;
    case '-': priority = 1; break;
    case '*': priority = 2; break;
    case '/': priority = 2; break;
    default: throw Exception("Invalid operator");
    }
    return priority;
}
void infix_to_postfix(char *postfix, const char *infix) {
    // ù ���ڰ� ������ Ȯ���ϴ� �ڵ� ����
    char ch;
    Stack<char> opStack; // operator stack
    for (ch = *infix; (ch = *infix) != '\0'; ++infix) {
        if (is_digit(ch)) {
            while (is_digit(*infix)) {
                *postfix++ = *infix++;
            }
            --infix; // �ݺ��� ������ ++infix�� ����ǹǷ� �� ĭ �ǵ�����
            *postfix++ = ' '; // calculate_postfix�� ������ ����ϹǷ� �߰�
        }
        else { // is_operator
            if (ch == '(') { // ���� ��ȣ��� �׳� �ִ´�
                opStack.push(ch);
            }
            else if (ch == ')') { // �ݴ� ��ȣ�� �߰��� ����� ó��
                if (opStack.is_empty() == false) {
                    // get operator priority
                    while (opStack.is_empty() == false) {
                        char top = opStack.top();
                        if (top == '(') { // ���� ��ȣ�� ã�Ҵٸ� ����
                            break;
                        }
                        else {
                            // �켱������ ���� �����ڸ� ���ÿ��� ����
                            // ���� ǥ��Ŀ� �߰�
                            *postfix++ = opStack.pop();
                        }
                    }
                    // �ùٸ� ��ȣ ���� �����ϴ��� Ȯ��
                    if (opStack.top() != '(') {
                        throw Exception("Invalid parenthesis");
                    }
                    // ���ÿ� �ִ� ���� �Ұ�ȣ�� ������
                    opStack.pop();
                }
            }
            else {
                if (opStack.is_empty() == false) {
                    // get operator priority
                    int new_pri = op_pri(ch);
                    while (opStack.is_empty() == false) {
                        char top = opStack.top();
                        if (top == '(') { // ���� ��ȣ�� ã�Ҵٸ� ����
                            break;
                        }
                        else if (new_pri <= op_pri(top)) {
                            *postfix++ = opStack.pop();
                        }
                        else {
                            break;
                        }
                    }
                }
                opStack.push(ch);
            }
        }
    }
    // ���ÿ� ���� �����ڸ� 
    while (opStack.is_empty() == false) {
        char op = opStack.pop();
        if (op == '(') { // ������ ó������ ���� �Ұ�ȣ�� �ִٸ� ����
            throw Exception("Invalid parenthesis");
        }
        *postfix++ = op;
    }
    *postfix = '\0';
}