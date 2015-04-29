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
    /* implement it */
    return 0;
}
int get_mul(const char *ns1, const char *ns2) { // 두 문자열을 정수로 변환하고 그 곱을 반환
    /* implement it */
    return 0;
}
int get_volume(const char *xs, const char *ys, const char *zs) { // 부피 계산 후 반환
    /* implement it */
    return 0;
}