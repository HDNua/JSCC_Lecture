#include <iostream>
#include <sstream>
#include <vector>

#include "common.h"
#include "Stack.h"
#include "StringBuffer.h"
#include "Table.h"

const int MAX_INPUT_SIZ = 256;
static char input[MAX_INPUT_SIZ];

// 식을 계산하고 값을 정수로 반환합니다.
int calculate(const char *expr);
// 연산자의 우선순위를 정수로 반환합니다.
int op_pri(const std::string &op);
// 식을 후위 표기법으로 변환합니다.
static std::vector<std::string> infix_to_postfix(const char *infix);
// 후위 표기법으로 표현된 식을 계산하고 값을 정수로 반환합니다.
int calculate_postfix(const std::vector<std::string> &postfix);

int main_rdx(void) {
    try {
        std::string command;
        std::string identifier, value;
        std::cout << "Usage: " << std::endl;
        // auto로 식별자에 대한 값을 설정합니다.
        std::cout << "- auto <identifier> <value>" << std::endl;
        // calc로 수식을 분석하고 값을 계산합니다.
        std::cout << "- calc <expression>" << std::endl;
        // exit로 프로그램을 종료합니다.
        std::cout << "- exit" << std::endl;
        while (true) {
            clear_input_buffer();
            std::cout << "> ";
            std::cin >> command;
            if (command == "auto") {
                std::cin >> identifier >> value;
                Table::instance()->set(identifier, value);
            }
            else if (command == "calc") {
                std::cin.ignore(1);
                std::cin.getline(input, MAX_INPUT_SIZ);
                std::cout << calculate(input) << std::endl;
            }
            else if (command == "exit") {
                break;
            }
            else {
                std::cout << "unknown command; try again" << std::endl;
            }
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
    // 중위 표기식을 후위 표기식으로 변환한다
    std::vector<std::string> postfix = infix_to_postfix(expr);
    return calculate_postfix(postfix); // 변환된 후위 표기식을 분석하고 반환한다
}

int op_pri(const std::string &op) { // get operator's priority
    int priority = 0;
    switch (op[0]) {
    case '+': priority = 1; break;
    case '-': priority = 1; break;
    case '*': priority = 2; break;
    case '/': priority = 2; break;
    default: throw Exception("Invalid operator");
    }
    return priority;
}
static std::vector<std::string> infix_to_postfix(const char *infix) {
    StringBuffer bin(infix);
    Stack<std::string> opStack;
    std::vector<std::string> postfix; // 후위 표기식의 토큰을 저장할 벡터
    while (bin.is_empty() == false) {
        bin.trim();
        char ch = bin.peekc();
        // 정수라면 획득하고 바로 출력한다 (피연산자)
        if (is_digit(ch))
            postfix.push_back(bin.get_number());
        // 식별자라면 획득하고 바로 출력한다 (피연산자)
        else if (is_fnamch(ch))
            postfix.push_back(bin.get_identifier());
        // 이외의 경우 연산자로 획득한다
        else {
            std::string op = bin.get_operator();
            if (op == "(") // 여는 괄호라면 그냥 넣는다
                opStack.push(op);
            else if (op == ")") { // 닫는 괄호를 발견한 경우의 처리
                if (opStack.is_empty() == false) {
                    // get operator priority
                    while (opStack.is_empty() == false) {
                        std::string top = opStack.top();
                        if (top == "(") // 여는 괄호를 찾았다면 종료
                            break;
                        else
                            // 우선순위가 낮은 연산자를 스택에서 꺼내
                            // 후위 표기식에 추가
                            postfix.push_back(opStack.pop());
                    }
                    // 올바른 괄호 쌍이 존재하는지 확인
                    if (opStack.top() != "(")
                        throw Exception("Invalid parenthesis");
                    // 스택에 있는 여는 소괄호를 버린다
                    opStack.pop();
                }
            }
            else {
                if (opStack.is_empty() == false) {
                    // get operator priority
                    int new_pri = op_pri(op);
                    while (opStack.is_empty() == false) {
                        std::string top = opStack.top();
                        if (top == "(") // 여는 괄호를 찾았다면 종료
                            break;
                        else if (new_pri <= op_pri(top))
                            postfix.push_back(opStack.pop());
                        else
                            break;
                    }
                }
                opStack.push(op);
            }
        }
    }
    // 스택에 남은 연산자를 모두 출력한다
    while (opStack.is_empty() == false) {
        std::string op = opStack.pop();
        if (op == "(") // 위에서 처리되지 않은 소괄호가 있다면 예외 처리
            throw Exception("Invalid parenthesis");
        postfix.push_back(op);
    }
    return postfix;
}

int strtoi(const std::string &str) { // 문자열을 정수로 변환한 값을 반환합니다.
    int digit, value = 0;
    for (int i = 0, len = str.length(); i < len; ++i) {
        digit = str[i] - '0';
        value = 10 * value + digit;
    }
    return value;
}
int calculate_postfix(const std::vector<std::string> &postfix) {
    int value;
    Stack<int> paramStack;
    for (int i = 0, len = postfix.size(); i < len; ++i) {
        const std::string &token = postfix[i];
        if (is_digit(token[0])) { // 정수라면 변환해서 푸시
            value = strtoi(token);
            paramStack.push(value);
        }
        else if (is_fnamch(token[0])) { // 식별자라면 값을 가져와서 푸시
            std::string ival = Table::instance()->get(token);
            value = strtoi(ival);
            paramStack.push(value);
        }
        else { // 이외의 경우 연산자로 처리한다
            const std::string &op = token;
            // 스택에서 두 개의 피연산자를 꺼낸다
            int right = paramStack.pop();
            int left = paramStack.pop();
            // 획득한 연산자로 연산한다
            switch (op[0]) {
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
    if (paramStack.count() != 1) // 스택에 남은 피연산자가 1개가 아니면 예외
        throw Exception("Unhandled operand found");
    return paramStack.pop(); // 하나 남은 피연산자를 반환한다
}