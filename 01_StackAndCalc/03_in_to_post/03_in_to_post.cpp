#include <iostream>

typedef std::string Exception;

// 공용 함수
inline bool is_digit(char ch) { return ('0' <= ch && ch <= '9'); }

// 스택 정의
typedef char Data;
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

// 사용할 함수
int op_pri(char ch); // get operator's priority
// convert infix notation expression
//  to postfix notation expression
void infix_to_postfix(char *postfix, const char *infix);

int main(void) {
    try {
        int loop;
        std::cin >> loop;
        const int MAX_EXPR_LEN = 256;
        char infix[MAX_EXPR_LEN] = "";
        char postfix[MAX_EXPR_LEN] = "";
        while (loop-- > 0) {
            std::cout << "Enter expression: ";
            std::cin >> infix;
            infix_to_postfix(postfix, infix);
            std::cout << infix << " : " << postfix << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}

// 구현
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
    // convert infix notation expression
    //  to postfix notation expression

    if (is_digit(*infix) == false)
        throw Exception("Invalid infix notation expression");

    char ch;
    Stack opStack; // operator stack
    for (ch = *infix; (ch = *infix) != '\0'; ++infix) {
        if (is_digit(ch)) {
            while (is_digit(*infix)) {
                *postfix++ = *infix++;
            }
            --infix; // 반복문 재실행시 ++infix가 실행되므로 한 칸 되돌린다
        }
        else { // is_operator
            if (opStack.is_empty() == false) {
                // get operator priority
                int new_pri = op_pri(ch);
                while (opStack.is_empty() == false) {
                    if (new_pri <= op_pri(opStack.top())) {
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

    // 스택에 남은 연산자를 
    while (opStack.is_empty() == false) {
        char op = opStack.pop();
        *postfix++ = op;
    }
    *postfix = '\0';
}