#include <iostream>
#include "common.h"
#include "Stack.h"

// 공용 정의
const int MAX_EXPR_LEN = 256;

// 사용할 함수
int calculate(const char *expr); // calculate infix expression
int calculate_postfix(const char *postfix); // calculate postfix expression
int op_pri(char ch); // get operator's priority
// convert infix notation expression
//  to postfix notation expression
void infix_to_postfix(char *postfix, const char *infix);

int main_rdx(void) {
    try {
        int loop;
        std::cin >> loop;
        char expression[MAX_EXPR_LEN] = "";
        while (loop-- > 0) {
            std::cout << "Enter expression: ";
            clear_input_buffer();
            std::cin.getline(expression, MAX_EXPR_LEN); // 공백을 포함한 줄을 입력받는다
            std::cout << expression << " : " << calculate(expression) << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}

// 구현
int calculate(const char *expr) { // calculate infix expression
    char postfix[MAX_EXPR_LEN] = "";
    infix_to_postfix(postfix, expr); // 중위 표기식을 후위 표기식으로 변환한다
    return calculate_postfix(postfix); // 변환된 후위 표기식을 분석하고 반환한다
}
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
    // 첫 문자가 수인지 확인하는 코드 삭제
    char ch;
    Stack<char> opStack; // operator stack
    for (ch = *infix; (ch = *infix) != '\0'; ++infix) {
        if (is_digit(ch)) {
            while (is_digit(*infix)) {
                *postfix++ = *infix++;
            }
            --infix; // 반복문 재실행시 ++infix가 실행되므로 한 칸 되돌린다
            *postfix++ = ' '; // calculate_postfix가 공백을 사용하므로 추가
        }
        else { // is_operator
            if (ch == '(') { // 여는 괄호라면 그냥 넣는다
                opStack.push(ch);
            }
            else if (ch == ')') { // 닫는 괄호를 발견한 경우의 처리
                if (opStack.is_empty() == false) {
                    // get operator priority
                    while (opStack.is_empty() == false) {
                        char top = opStack.top();
                        if (top == '(') { // 여는 괄호를 찾았다면 종료
                            break;
                        }
                        else {
                            // 우선순위가 낮은 연산자를 스택에서 꺼내
                            // 후위 표기식에 추가
                            *postfix++ = opStack.pop();
                        }
                    }
                    // 올바른 괄호 쌍이 존재하는지 확인
                    if (opStack.top() != '(') {
                        throw Exception("Invalid parenthesis");
                    }
                    // 스택에 있는 여는 소괄호를 버린다
                    opStack.pop();
                }
            }
            else {
                if (opStack.is_empty() == false) {
                    // get operator priority
                    int new_pri = op_pri(ch);
                    while (opStack.is_empty() == false) {
                        char top = opStack.top();
                        if (top == '(') { // 여는 괄호를 찾았다면 종료
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
    // 스택에 남은 연산자를 
    while (opStack.is_empty() == false) {
        char op = opStack.pop();
        if (op == '(') { // 위에서 처리되지 않은 소괄호가 있다면 예외
            throw Exception("Invalid parenthesis");
        }
        *postfix++ = op;
    }
    *postfix = '\0';
}