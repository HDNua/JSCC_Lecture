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
// 사용 함수
int get_square(const char *ns); // 문자열을 정수로 변환하고 그 제곱을 반환
int get_mul(const char *ns1, const char *ns2); // 두 문자열을 정수로 변환하고 그 곱을 반환
int get_volume(const char *x, const char *y, const char *z); // 부피 계산 후 반환
// 정수와 연산자 사이에 사이띄개를 넣어 출력하는 프로그램
int main(void) {
    try {
        char input1[MAX_EXPR_LEN], input2[MAX_EXPR_LEN], input3[MAX_EXPR_LEN];
        std::cout << "Enter number: ";
        std::cin >> input1;
        std::cout << "Enter number: ";
        std::cin >> input2;
        std::cout << "Enter number: ";
        std::cin >> input3;
        std::cout << get_square(input1) << std::endl;
        std::cout << get_mul(input1, input2) << std::endl;
        std::cout << get_volume(input1, input2, input3) << std::endl;
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}
// 구현
int get_square(const char *ns) { // 문자열을 정수로 변환하고 그 제곱을 반환
    int digit = 0;
    int value = 0;
    char ch;
    for (ch = *ns; (ch = *ns) != '\0'; ++ns) {
        if (is_digit(ch) == false) {
            throw Exception("Invalid number");
        }
        digit = ch - '0';
        value = 10 * value + digit;
    }
    return value * value;
}
int get_mul(const char *ns1, const char *ns2) { // 두 문자열을 정수로 변환하고 그 곱을 반환
    int digit = 0;
    int left = 0;
    char ch;
    for (ch = *ns1; (ch = *ns1) != '\0'; ++ns1) {
        if (is_digit(ch) == false) {
            throw Exception("Invalid number");
        }
        digit = ch - '0';
        left = 10 * left + digit;
    }
    int right = 0;
    for (ch = *ns2; (ch = *ns2) != '\0'; ++ns2) {
        if (is_digit(ch) == false) {
            throw Exception("Invalid number");
        }
        digit = ch - '0';
        right = 10 * right + digit;
    }
    return left * right;
}
int get_volume(const char *xs, const char *ys, const char *zs) { // 부피 계산 후 반환
    int digit = 0;
    int x = 0;
    char ch;
    for (ch = *xs; (ch = *xs) != '\0'; ++xs) {
        if (is_digit(ch) == false) {
            throw Exception("Invalid number");
        }
        digit = ch - '0';
        x = 10 * x + digit;
    }
    int y = 0;
    for (ch = *ys; (ch = *ys) != '\0'; ++ys) {
        if (is_digit(ch) == false) {
            throw Exception("Invalid number");
        }
        digit = ch - '0';
        y = 10 * y + digit;
    }
    int z = 0;
    for (ch = *zs; (ch = *zs) != '\0'; ++zs) {
        if (is_digit(ch) == false) {
            throw Exception("Invalid number");
        }
        digit = ch - '0';
        z = 10 * z + digit;
    }
    return x * y * z;
}
