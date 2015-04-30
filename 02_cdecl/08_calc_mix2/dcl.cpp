#include "dcl.h"

#include <iostream>
#include "StringBuffer.h"
#include "common.h"

#include "Table.h"

typedef std::vector<std::string> StringList;

const int MAX_INPUT_SIZ = 256;
static char input[MAX_INPUT_SIZ];

// 선언을 분석하고 획득한 토큰의 벡터를 반환합니다.
std::vector<IdentifierInfo> get_dcl_info(const char *decl);

// 형식을 획득하여 문자열로 반환합니다.
std::string get_type(StringBuffer &buf_in);
// 선언자를 분석하고 결과를 출력합니다.
void dcl(StringBuffer &buf_in, StringList &vec_out);
// 직접 선언자를 분석하고 결과를 출력합니다.
void dirdcl(StringBuffer &buf_in, StringList &vec_out);

std::vector<IdentifierInfo> get_dcl_info(const char *decl) {
    std::vector<IdentifierInfo> identifiers;
    StringList tokens;
    StringBuffer bin(decl);
    std::string type = get_type(bin);

    while (bin.is_empty() == false) {
        tokens.clear();
        bin.trim();
        dcl(bin, tokens);
        if (bin.peekc() == ',') {
            bin.getc();
            std::string identifier = tokens[0];
            std::string datatype;
            for (int i = 1, len = tokens.size(); i < len; ++i) {
                datatype += tokens[i];
            }
            datatype += type;
            IdentifierInfo info(identifier, datatype);
            identifiers.push_back(info);
        }
        else if (bin.peekc() == ';') {
            break;
        }
        else {
            throw Exception("unknown character");
        }
    }
    std::string identifier = tokens[0];
    std::string datatype;
    for (int i = 1, len = tokens.size(); i < len; ++i) {
        datatype += tokens[i];
    }
    datatype += type;
    IdentifierInfo info(identifier, datatype);
    identifiers.push_back(info);
    return identifiers;
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
void dcl(StringBuffer &bin, StringList &vout) { // 선언자를 분석하고 결과 출력
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
    dirdcl(bin, vout); // *을 모두 획득했으므로 직접 선언자를 분석한다
    while (pointer_count > 0) { // 선언자의 분석이 오른쪽에서 먼저 진행되므로
        vout.push_back("*"); // 왼쪽에서 획득한 기호를 오른쪽의 분석이
        --pointer_count; // 종료된 후에 출력해야 한다
    }
}
void dirdcl(StringBuffer &bin, StringList &vout) { // 직접 선언자를 분석하고 결과 출력
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
        vout.push_back(identifier);
    }
    else if (ch == '(') { // direct-declarator: (declarator) (3)
        bin.getc(); // ( 문자를 해석해서 진입했으므로 다음으로 넘긴다
        dcl(bin, vout);
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
            vout.push_back("()");
        }
        else if (ch == '[') { // 배열 기호 획득
            bin.getc(); // [ 괄호를 해석해서 진입했으므로 넘긴다
            if (bin.peekc() != ']') // 닫는 괄호가 없으면 예외
                throw Exception("잘못된 배열 기호입니다.");
            bin.getc(); // ] 괄호를 해석했으므로 다음으로 넘긴다
            vout.push_back("[]");
        }
        else { // 이외의 경우 반복문을 탈출한다
            break;
        }
    }
}