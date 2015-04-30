#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>

// ���� ���� Exception�� ���� �ӽ����� �����Դϴ�.
typedef std::string Exception;

// �⺻ �Ǻ� �Լ��Դϴ�.
bool is_digit(char ch); // ���ڰ� ���ڶ�� ���Դϴ�.
bool is_lower(char ch); // �ҹ��ڶ�� ���Դϴ�.
bool is_upper(char ch); // �빮�ڶ�� ���Դϴ�.
bool is_alpha(char ch); // ���ĺ��̶�� ���Դϴ�.
bool is_alnum(char ch); // ���ĺ� �Ǵ� ���ڶ�� ���Դϴ�.
bool is_space(char ch); // �����̶�� ���Դϴ�.

// �ĺ��ڷ� ������ �������� Ȯ���մϴ�.
bool is_namch(char ch); // �ĺ��� ���ڶ�� ���Դϴ�.
bool is_fnamch(char ch); // ù �ĺ��� ���ڶ�� ���Դϴ�.

void clear_input_buffer(); // �Է¹ޱ� ���� �Է� ���۸� ���ϴ�.

#endif