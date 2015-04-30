#include <iostream>
#include "StringBuffer.h"
typedef std::string Exception;
// 기본 판별 함수입니다.
bool is_digit(char ch) { // 문자가 숫자라면 참입니다.
    return ('0' <= ch && ch <= '9');
}
bool is_lower(char ch) { // 소문자라면 참입니다.
    return ('a' <= ch && ch <= 'z'); 
}
bool is_upper(char ch) { // 대문자라면 참입니다.
    return ('A' <= ch && ch <= 'Z'); 
}
bool is_alpha(char ch) {  // 알파벳이라면 참입니다.
    return is_lower(ch) || is_upper(ch); 
}
bool is_alnum(char ch) { // 알파벳 또는 숫자라면 참입니다.
    return is_digit(ch) || is_alpha(ch); 
}
bool is_space(char ch) { // 공백이라면 참입니다.
    return (ch == ' ' || ch == '\t' || ch == '\n'); 
}
// 식별자로 가능한 문자인지 확인합니다.
bool is_namch(char ch) { // 식별자 문자라면 참입니다.
    return is_alnum(ch) || (ch == '_'); 
}
bool is_fnamch(char ch) { // 첫 식별자 문자라면 참입니다.
    return is_alpha(ch) || (ch == '_'); 
}
// 형식을 획득하여 문자열로 반환합니다.
std::string get_type(StringBuffer &buffer_input);
// 선언자를 분석하고 결과를 출력합니다.
void dcl(StringBuffer &buffer_input);
// 직접 선언자를 분석하고 결과를 출력합니다.
void dirdcl(StringBuffer &buffer_input);
int main(void) {
    try {
        const int MAX_INPUT_SIZ = 256;
        char input[MAX_INPUT_SIZ];
        while (true) {

            // 입력을 받고 버퍼를 초기화한다
            std::cin.getline(input, MAX_INPUT_SIZ);
            if (input[0] == ';') {
                break;
            }
            StringBuffer buffer(input);

            // 형식을 획득한다
            std::string type = get_type(buffer);
            while (is_space(buffer.peekc())) { // 형식과 선언자 사이의 공백을
                buffer.getc(); // 무시하고 포인터를 선언자 앞으로 옮긴다
            }

            // 선언자를 분석한다
            dcl(buffer);
            if (buffer.peekc() != ';') // 문장 종료 기호가 없으면 예외
                throw Exception("문장 종료 기호가 없습니다.");
            std::cout << type.c_str() << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}
std::string get_type(StringBuffer &bin) {
    char ch = bin.peekc(); // 버퍼의 첫 문자를 확인한다
    if (is_fnamch(ch) == false) // 올바른 형식이 아니면 예외
        throw Exception("잘못된 입력입니다.");
    std::string result = "";
    while (bin.is_empty() == false) { // 버퍼에 문자가 남아있는 동안
        ch = bin.getc(); // 문자를 획득하고 확인한다
        if (is_namch(ch) == false) { // 더 이상 형식 문자가 아니면
            bin.ungetc(); // 아직 해석되지 않은 문자를 버퍼에 되돌리고
            break; // 형식이 끝났으므로 탈출한다
        }
        result += ch; // 획득한 문자를 결과 객체에 넣는다
    }
    return result;
}
void dcl(StringBuffer &bin) { // 선언자를 분석하고 결과 출력
    // declarator: * direct-declarator (1)
    int pointer_count = 0;
    char ch;
    while (bin.is_empty() == false) { // 버퍼에 문자가 남아있는 동안
        ch = bin.getc(); // 문자를 획득하고 확인한다
        if (ch == '*') { // *라면 그만큼 포인터를 출력하기 위해
            ++pointer_count; // 카운터를 증가시킨다
        }
        else { // *가 아니라면 포인터를 되돌리고 탈출한다
            bin.ungetc();
            break;
        }
    }
    // declarator: * direct-declarator (2)
    dirdcl(bin); // *을 모두 획득했으므로 직접 선언자를 분석한다
    while (pointer_count > 0) { // 선언자의 분석이 오른쪽에서 먼저 진행되므로
        std::cout << "pointer to "; // 왼쪽에서 획득한 기호를 오른쪽의 분석이
        --pointer_count; // 종료된 후에 출력해야 한다
    }
}
void dirdcl(StringBuffer &bin) { // 직접 선언자를 분석하고 결과 출력
    char ch = bin.peekc();
    if (is_fnamch(ch)) { // direct-declarator: 이름 (2)
        std::string identifier = "";
        while (bin.is_empty() == false) {
            ch = bin.getc();
            if (is_namch(ch) == false) {
                bin.ungetc();
                break;
            }
            identifier += ch;
        }
        if (identifier.empty()) // 식별자에 추가된 문자가 없다면 예외
            throw Exception("올바른 식별자 이름이 아닙니다.");
        std::cout << identifier.c_str() << ": ";
    }
    else if (ch == '(') { // direct-declarator: (declarator) (3)
        bin.getc(); // ( 문자를 해석해서 진입했으므로 다음으로 넘긴다
        dcl(bin);
        if (bin.peekc() != ')') // 닫는 괄호가 없으면 예외
            throw Exception("닫는 괄호가 없습니다.");
        bin.getc(); // ) 괄호 검사를 진행했으므로 다음으로 넘긴다
    }
    // direct-declarator: direct-declarator() (4)
    // direct-declarator: direct-declarator[] (5)
    while (bin.is_empty() == false) {
        ch = bin.peekc();
        if (ch == '(') { // 함수 기호 획득
            bin.getc(); // ( 괄호를 해석해서 진입했으므로 넘긴다
            if (bin.peekc() != ')') // 닫는 괄호가 없으면 예외
                throw Exception("잘못된 함수 기호입니다.");
            bin.getc(); // ) 괄호를 해석했으므로 다음으로 넘긴다
            std::cout << "function returning ";
        }
        else if (ch == '[') { // 배열 기호 획득
            bin.getc(); // [ 괄호를 해석해서 진입했으므로 넘긴다
            if (bin.peekc() != ']') // 닫는 괄호가 없으면 예외
                throw Exception("잘못된 배열 기호입니다.");
            bin.getc(); // ] 괄호를 해석했으므로 다음으로 넘긴다
            std::cout << "array of ";
        }
        else { // 이외의 경우 반복문을 탈출한다
            break;
        }
    }
}