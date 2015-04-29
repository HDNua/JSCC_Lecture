#include <iostream>
typedef std::string Exception;
// 공용 함수
inline void clear_input_buffer() { // 입력받기 전에 입력 버퍼를 비운다
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}
inline bool is_digit(char ch) { return ('0' <= ch && ch <= '9'); }
// 문자가 공백인지 확인한다
inline bool is_space(char ch) { return (ch == ' ' || ch == '\t' || ch == '\n'); }
// 스택 정의
template <typename Data> // 형식에 자유로운 스택을 만들기 위해 템플릿 클래스로 변경
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
            std::cin.getline(postfix, MAX_EXPR_LEN); // 공백을 포함한 줄을 입력받는다
            std::cout << postfix << " : " << calculate_postfix(postfix) << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}
// 구현
int calculate_postfix(const char *postfix) {
    char ch;
    int digit;
    Stack<int> paramStack;
    for (ch = *postfix; (ch = *postfix) != '\0'; ++postfix) {
        if (is_space(ch)) { // 공백이면 무시한다
            continue;
        }
        else if (is_digit(ch)) { // 피연산자라면 스택에 푸시 한다
            int value = 0;
            while (is_digit(*postfix)) {
                digit = *postfix++ - '0';
                value = 10 * value + digit;
            }
            paramStack.push(value);
            --postfix; // 반복문 재실행시 ++postfix가 실행되므로 한 칸 되돌린다
        }
        else {
            // 스택에서 두 개의 피연산자를 꺼낸다
            int right = paramStack.pop();
            int left = paramStack.pop();
            int value = 0;
            // 획득한 연산자로 연산한다
            switch (ch) {
            case '+': value = left + right; break;
            case '-': value = left - right; break;
            case '*': value = left * right; break;
            case '/': value = left / right; break;
            default: throw Exception("Invalid operator");
            }
            // 연산 결과를 다시 스택에 넣는다
            paramStack.push(value);
        }
    }
    if (paramStack.count() != 1) { // 스택에 남은 피연산자가 1개가 아니면 예외
        throw Exception("Unhandled operand found");
    }
    return paramStack.pop(); // 하나 남은 피연산자를 반환한다
}