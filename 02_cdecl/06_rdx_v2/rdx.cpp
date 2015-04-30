#include <iostream>
#include <sstream>
#include <vector>

#include "common.h"
#include "Stack.h"
#include "StringBuffer.h"
#include "Table.h"

const int MAX_INPUT_SIZ = 256;
static char input[MAX_INPUT_SIZ];

// ���� ����ϰ� ���� ������ ��ȯ�մϴ�.
int calculate(const char *expr);
// �������� �켱������ ������ ��ȯ�մϴ�.
int op_pri(const std::string &op);
// ���� ���� ǥ������� ��ȯ�մϴ�.
static std::vector<std::string> infix_to_postfix(const char *infix);
// ���� ǥ������� ǥ���� ���� ����ϰ� ���� ������ ��ȯ�մϴ�.
int calculate_postfix(const std::vector<std::string> &postfix);

int main_rdx(void) {
    try {
        std::string command;
        std::string identifier, value;
        std::cout << "Usage: " << std::endl;
        // auto�� �ĺ��ڿ� ���� ���� �����մϴ�.
        std::cout << "- auto <identifier> <value>" << std::endl;
        // calc�� ������ �м��ϰ� ���� ����մϴ�.
        std::cout << "- calc <expression>" << std::endl;
        // exit�� ���α׷��� �����մϴ�.
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

// ����
int calculate(const char *expr) { // calculate infix expression
    // ���� ǥ����� ���� ǥ������� ��ȯ�Ѵ�
    std::vector<std::string> postfix = infix_to_postfix(expr);
    return calculate_postfix(postfix); // ��ȯ�� ���� ǥ����� �м��ϰ� ��ȯ�Ѵ�
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
    std::vector<std::string> postfix; // ���� ǥ����� ��ū�� ������ ����
    while (bin.is_empty() == false) {
        bin.trim();
        char ch = bin.peekc();
        // ������� ȹ���ϰ� �ٷ� ����Ѵ� (�ǿ�����)
        if (is_digit(ch))
            postfix.push_back(bin.get_number());
        // �ĺ��ڶ�� ȹ���ϰ� �ٷ� ����Ѵ� (�ǿ�����)
        else if (is_fnamch(ch))
            postfix.push_back(bin.get_identifier());
        // �̿��� ��� �����ڷ� ȹ���Ѵ�
        else {
            std::string op = bin.get_operator();
            if (op == "(") // ���� ��ȣ��� �׳� �ִ´�
                opStack.push(op);
            else if (op == ")") { // �ݴ� ��ȣ�� �߰��� ����� ó��
                if (opStack.is_empty() == false) {
                    // get operator priority
                    while (opStack.is_empty() == false) {
                        std::string top = opStack.top();
                        if (top == "(") // ���� ��ȣ�� ã�Ҵٸ� ����
                            break;
                        else
                            // �켱������ ���� �����ڸ� ���ÿ��� ����
                            // ���� ǥ��Ŀ� �߰�
                            postfix.push_back(opStack.pop());
                    }
                    // �ùٸ� ��ȣ ���� �����ϴ��� Ȯ��
                    if (opStack.top() != "(")
                        throw Exception("Invalid parenthesis");
                    // ���ÿ� �ִ� ���� �Ұ�ȣ�� ������
                    opStack.pop();
                }
            }
            else {
                if (opStack.is_empty() == false) {
                    // get operator priority
                    int new_pri = op_pri(op);
                    while (opStack.is_empty() == false) {
                        std::string top = opStack.top();
                        if (top == "(") // ���� ��ȣ�� ã�Ҵٸ� ����
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
    // ���ÿ� ���� �����ڸ� ��� ����Ѵ�
    while (opStack.is_empty() == false) {
        std::string op = opStack.pop();
        if (op == "(") // ������ ó������ ���� �Ұ�ȣ�� �ִٸ� ���� ó��
            throw Exception("Invalid parenthesis");
        postfix.push_back(op);
    }
    return postfix;
}

int strtoi(const std::string &str) { // ���ڿ��� ������ ��ȯ�� ���� ��ȯ�մϴ�.
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
        if (is_digit(token[0])) { // ������� ��ȯ�ؼ� Ǫ��
            value = strtoi(token);
            paramStack.push(value);
        }
        else if (is_fnamch(token[0])) { // �ĺ��ڶ�� ���� �����ͼ� Ǫ��
            std::string ival = Table::instance()->get(token);
            value = strtoi(ival);
            paramStack.push(value);
        }
        else { // �̿��� ��� �����ڷ� ó���Ѵ�
            const std::string &op = token;
            // ���ÿ��� �� ���� �ǿ����ڸ� ������
            int right = paramStack.pop();
            int left = paramStack.pop();
            // ȹ���� �����ڷ� �����Ѵ�
            switch (op[0]) {
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
    if (paramStack.count() != 1) // ���ÿ� ���� �ǿ����ڰ� 1���� �ƴϸ� ����
        throw Exception("Unhandled operand found");
    return paramStack.pop(); // �ϳ� ���� �ǿ����ڸ� ��ȯ�Ѵ�
}