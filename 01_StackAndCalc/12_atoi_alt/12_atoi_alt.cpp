#include <iostream>
typedef std::string Exception;
inline bool is_digit(char ch) { return ('0' <= ch && ch <= '9'); }

int calculate(const char *expr); // 넘겨받은 식을 계산하여 값을 반환한다
int main(void) {
    try {
        // 입력의 길이가 MAX_EXPR_LEN보다 큰 경우가
        // 발생하지 않는다고 가정한다
        const int MAX_EXPR_LEN = 256;
        char expression[MAX_EXPR_LEN] = "";
        int loop;
        std::cin >> loop;
        // loop 회수만큼 반복문을 수행한다
        while (loop-- > 0) {
            std::cout << "Enter expression: ";
            std::cin >> expression;
            std::cout << calculate(expression) << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}

int ascii_to_int_adr(const char **ns_src) { // 문자열 포인터의 주소를 넘긴다
    const char *ns = *ns_src; // 문자열 포인터가 가리키는 값을 획득한다
    int digit = 0;
    int value = 0;
    char ch;
    for (ch = *ns; (ch = *ns) != '\0'; ++ns) {
        if (is_digit(ch) == false) {
            break;
        }
        digit = ch - '0';
        value = 10 * value + digit;
    }
    *ns_src = ns; // 분석이 끝나면 문자열 포인터 변수에 값을 대입한다
    return value;
}
int ascii_to_int_ref(const char *&ns) { // 문자열 포인터의 참조를 넘긴다
    int digit = 0;
    int value = 0;
    char ch;
    for (ch = *ns; (ch = *ns) != '\0'; ++ns) {
        if (is_digit(ch) == false) {
            break;
        }
        digit = ch - '0';
        value = 10 * value + digit;
    }
    return value;
}
int calculate(const char *expr) { // 넘겨받은 식을 계산하여 값을 반환한다
    if (is_digit(*expr) == false) { // 입력의 처음이 숫자가 아니라면 예외 처리
        throw Exception("타당하지 않은 입력입니다.");
    }
    int left = ascii_to_int_adr(&expr); // 왼쪽에 나타나는 수 획득 (주소)
    if (*expr == '\0') { // 입력이 끝났다면 획득한 정수를 반환하고 종료
        return left;
    }
    // 연산자 획득: 사칙 연산에 대해서만 다루므로 연산자 길이는 반드시 1
    char op = *expr++; // 문자열 포인터가 가리키는 연산자를 획득 후 포인터 이동
    int right = ascii_to_int_ref(expr); // 오른쪽에 나타나는 수 획득 (참조)
    if (*expr != '\0') { // 입력이 아직 끝나지 않았다면 예외 발생
        throw Exception("두 개의 피연산자로만 연산할 수 있습니다.");
    }
    // 획득한 값과 연산자를 이용하여 연산
    int retVal = 0;
    switch (op) {
    case '+': retVal = left + right; break;
    case '-': retVal = left - right; break;
    case '*': retVal = left * right; break;
    case '/': retVal = left / right; break;
    default: throw Exception("올바른 연산자가 아닙니다.");
    }
    return retVal;
}