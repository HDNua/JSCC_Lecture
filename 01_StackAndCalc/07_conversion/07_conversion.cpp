#include <iostream>
// 공용 정의
const int MAX_EXPR_LEN = 256;
typedef std::string Exception;
// 공용 함수
inline void clear_input_buffer() { // 입력받기 전에 입력 버퍼를 비운다
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}
inline bool is_digit(char ch) { return ('0' <= ch && ch <= '9'); }
inline bool is_space(char ch) { return (ch == ' ' || ch == '\t' || ch == '\n'); }
// 정수와 연산자 사이에 사이띄개를 넣어 출력하는 프로그램
int main(void) {
    try {
        char expression[MAX_EXPR_LEN] = "";
        std::cin >> expression;
        char ch;
        char *expr = expression;
        // 문자열의 모든 문자 탐색
        for (ch = *expr; (ch = *expr) != '\0'; ++expr) {
            if (is_digit(ch)) { // 수가 발견된다면 정수 획득
                int digit = 0; // 자리수를 임시로 저장할 변수
                int value = 0; // 최종적으로 획득할 정수를 저장할 변수
                while (is_digit(*expr)) { // 숫자를 획득하는 동안 value 갱신
                    digit = *expr++ - '0';
                    value = 10 * value + digit;
                }
                --expr; // 반복문 재실행 시 ++expr이 수행되므로 한 칸 되돌린다
                std::cout << value << ' '; // 획득한 정수를 출력하고 뒤에 공백을 추가
            }
            else { // 수가 아닌 문자의 경우 출력하고 공백으로 띄운다
                std::cout << ch << ' ';
            }
        }
        std::cout << std::endl;
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}