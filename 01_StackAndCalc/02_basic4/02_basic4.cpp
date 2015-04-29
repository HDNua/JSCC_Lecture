#include <iostream>
typedef std::string Exception;
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
int calculate(const char *expr) { // 넘겨받은 식을 계산하여 값을 반환한다
    char ch = *expr;
    if (ch < '0' || '9' < ch) { // 입력의 처음이 숫자가 아니라면 예외 처리
        throw Exception("타당하지 않은 입력입니다.");
    }
    int digit; // 자릿수를 저장할 임시 변수
    // 왼쪽에 나타나는 수 획득
    int left = 0;
    for (ch = *expr; (ch = *expr) != '\0'; ++expr) { // 입력의 끝이 나타나기 전까지
        if (ch < '0' || '9' < ch) { // 수가 아닌 문자가 나타나면 탈출
            break;
        }
        digit = ch - '0'; // 수를 올바른 정수로 바꾼다(문자 '0'은 정수 48과 같다)
        left = 10 * left + digit;
    }
    if (ch == '\0') { // 연산자가 나타나기 전에 입력이 끝났다면
        return left; // 문장의 끝으로 간주하고 획득한 수만 반환
    }
    // 연산자 획득: 사칙 연산에 대해서만 다루므로 연산자 길이는 반드시 1
    char op = *expr++; // 문자열 포인터가 가리키는 연산자를 획득 후 포인터 이동
    // 오른쪽에 나타나는 수 획득: 왼쪽의 경우와 같다
    int right = 0;
    for (ch = *expr; (ch = *expr) != '\0'; ++expr) { // 입력의 끝이 나타나기 전까지
        if (ch < '0' || '9' < ch) { // 수가 아닌 문자가 나타나면 탈출
            break;
        }
        digit = ch - '0'; // 수를 올바른 정수로 바꾼다(문자 '0'은 정수 48과 같다)
        right = 10 * right + digit;
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