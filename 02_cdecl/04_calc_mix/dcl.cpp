#include <iostream>
#include "StringBuffer.h"
#include "common.h"

// ������ ȹ���Ͽ� ���ڿ��� ��ȯ�մϴ�.
std::string get_type(StringBuffer &buffer_input);
// �����ڸ� �м��ϰ� ����� ����մϴ�.
void dcl(StringBuffer &buffer_input);
// ���� �����ڸ� �м��ϰ� ����� ����մϴ�.
void dirdcl(StringBuffer &buffer_input);
int main_dcl(void) {
    try {
        const int MAX_INPUT_SIZ = 256;
        char input[MAX_INPUT_SIZ];
        while (true) {

            // �Է��� �ް� ���۸� �ʱ�ȭ�Ѵ�
            std::cin.getline(input, MAX_INPUT_SIZ);
            if (input[0] == ';') {
                break;
            }
            StringBuffer buffer(input);

            // ������ ȹ���Ѵ�
            std::string type = get_type(buffer);
            while (is_space(buffer.peekc())) { // ���İ� ������ ������ ������
                buffer.getc(); // �����ϰ� �����͸� ������ ������ �ű��
            }

            // �����ڸ� �м��Ѵ�
            dcl(buffer);
            if (buffer.peekc() != ';') // ���� ���� ��ȣ�� ������ ����
                throw Exception("���� ���� ��ȣ�� �����ϴ�.");
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
    char ch = bin.peekc(); // ������ ù ���ڸ� Ȯ���Ѵ�
    if (is_fnamch(ch) == false) // �ùٸ� ������ �ƴϸ� ����
        throw Exception("�߸��� �Է��Դϴ�.");
    std::string result = "";
    while (bin.is_empty() == false) { // ���ۿ� ���ڰ� �����ִ� ����
        ch = bin.getc(); // ���ڸ� ȹ���ϰ� Ȯ���Ѵ�
        if (is_namch(ch) == false) { // �� �̻� ���� ���ڰ� �ƴϸ�
            bin.ungetc(); // ���� �ؼ����� ���� ���ڸ� ���ۿ� �ǵ�����
            break; // ������ �������Ƿ� Ż���Ѵ�
        }
        result += ch; // ȹ���� ���ڸ� ��� ��ü�� �ִ´�
    }
    return result;
}
void dcl(StringBuffer &bin) { // �����ڸ� �м��ϰ� ��� ���
    // declarator: * direct-declarator (1)
    int pointer_count = 0;
    char ch;
    while (bin.is_empty() == false) { // ���ۿ� ���ڰ� �����ִ� ����
        ch = bin.getc(); // ���ڸ� ȹ���ϰ� Ȯ���Ѵ�
        if (ch == '*') { // *��� �׸�ŭ �����͸� ����ϱ� ����
            ++pointer_count; // ī���͸� ������Ų��
        }
        else { // *�� �ƴ϶�� �����͸� �ǵ����� Ż���Ѵ�
            bin.ungetc();
            break;
        }
    }
    // declarator: * direct-declarator (2)
    dirdcl(bin); // *�� ��� ȹ�������Ƿ� ���� �����ڸ� �м��Ѵ�
    while (pointer_count > 0) { // �������� �м��� �����ʿ��� ���� ����ǹǷ�
        std::cout << "pointer to "; // ���ʿ��� ȹ���� ��ȣ�� �������� �м���
        --pointer_count; // ����� �Ŀ� ����ؾ� �Ѵ�
    }
}
void dirdcl(StringBuffer &bin) { // ���� �����ڸ� �м��ϰ� ��� ���
    char ch = bin.peekc();
    if (is_fnamch(ch)) { // direct-declarator: �̸� (2)
        std::string identifier = "";
        while (bin.is_empty() == false) {
            ch = bin.getc();
            if (is_namch(ch) == false) {
                bin.ungetc();
                break;
            }
            identifier += ch;
        }
        if (identifier.empty()) // �ĺ��ڿ� �߰��� ���ڰ� ���ٸ� ����
            throw Exception("�ùٸ� �ĺ��� �̸��� �ƴմϴ�.");
        std::cout << identifier.c_str() << ": ";
    }
    else if (ch == '(') { // direct-declarator: (declarator) (3)
        bin.getc(); // ( ���ڸ� �ؼ��ؼ� ���������Ƿ� �������� �ѱ��
        dcl(bin);
        if (bin.peekc() != ')') // �ݴ� ��ȣ�� ������ ����
            throw Exception("�ݴ� ��ȣ�� �����ϴ�.");
        bin.getc(); // ) ��ȣ �˻縦 ���������Ƿ� �������� �ѱ��
    }
    // direct-declarator: direct-declarator() (4)
    // direct-declarator: direct-declarator[] (5)
    while (bin.is_empty() == false) {
        ch = bin.peekc();
        if (ch == '(') { // �Լ� ��ȣ ȹ��
            bin.getc(); // ( ��ȣ�� �ؼ��ؼ� ���������Ƿ� �ѱ��
            if (bin.peekc() != ')') // �ݴ� ��ȣ�� ������ ����
                throw Exception("�߸��� �Լ� ��ȣ�Դϴ�.");
            bin.getc(); // ) ��ȣ�� �ؼ������Ƿ� �������� �ѱ��
            std::cout << "function returning ";
        }
        else if (ch == '[') { // �迭 ��ȣ ȹ��
            bin.getc(); // [ ��ȣ�� �ؼ��ؼ� ���������Ƿ� �ѱ��
            if (bin.peekc() != ']') // �ݴ� ��ȣ�� ������ ����
                throw Exception("�߸��� �迭 ��ȣ�Դϴ�.");
            bin.getc(); // ] ��ȣ�� �ؼ������Ƿ� �������� �ѱ��
            std::cout << "array of ";
        }
        else { // �̿��� ��� �ݺ����� Ż���Ѵ�
            break;
        }
    }
}