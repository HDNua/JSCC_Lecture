#include "common.h"
#include <iostream>

// �⺻ �Ǻ� �Լ��Դϴ�.
bool is_digit(char ch) { // ���ڰ� ���ڶ�� ���Դϴ�.
    return ('0' <= ch && ch <= '9'); 
}
bool is_lower(char ch) { // �ҹ��ڶ�� ���Դϴ�.
    return ('a' <= ch && ch <= 'z');
}
bool is_upper(char ch) { // �빮�ڶ�� ���Դϴ�.
    return ('A' <= ch && ch <= 'Z');
}
bool is_alpha(char ch) {  // ���ĺ��̶�� ���Դϴ�.
    return is_lower(ch) || is_upper(ch);
}
bool is_alnum(char ch) { // ���ĺ� �Ǵ� ���ڶ�� ���Դϴ�.
    return is_digit(ch) || is_alpha(ch);
}
bool is_space(char ch) { // �����̶�� ���Դϴ�.
    return (ch == ' ' || ch == '\t' || ch == '\n');
}

// �ĺ��ڷ� ������ �������� Ȯ���մϴ�.
bool is_namch(char ch) { // �ĺ��� ���ڶ�� ���Դϴ�.
    return is_alnum(ch) || (ch == '_');
}
bool is_fnamch(char ch) { // ù �ĺ��� ���ڶ�� ���Դϴ�.
    return is_alpha(ch) || (ch == '_');
}

void clear_input_buffer() { // �Է¹ޱ� ���� �Է� ���۸� ���ϴ�.
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
}
