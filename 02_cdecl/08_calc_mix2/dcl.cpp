#include "dcl.h"

#include <iostream>
#include "StringBuffer.h"
#include "common.h"

#include "Table.h"

typedef std::vector<std::string> StringList;

const int MAX_INPUT_SIZ = 256;
static char input[MAX_INPUT_SIZ];

// ������ �м��ϰ� ȹ���� ��ū�� ���͸� ��ȯ�մϴ�.
std::vector<IdentifierInfo> get_dcl_info(const char *decl);

// ������ ȹ���Ͽ� ���ڿ��� ��ȯ�մϴ�.
std::string get_type(StringBuffer &buf_in);
// �����ڸ� �м��ϰ� ����� ����մϴ�.
void dcl(StringBuffer &buf_in, StringList &vec_out);
// ���� �����ڸ� �м��ϰ� ����� ����մϴ�.
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
void dcl(StringBuffer &bin, StringList &vout) { // �����ڸ� �м��ϰ� ��� ���
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
    dirdcl(bin, vout); // *�� ��� ȹ�������Ƿ� ���� �����ڸ� �м��Ѵ�
    while (pointer_count > 0) { // �������� �м��� �����ʿ��� ���� ����ǹǷ�
        vout.push_back("*"); // ���ʿ��� ȹ���� ��ȣ�� �������� �м���
        --pointer_count; // ����� �Ŀ� ����ؾ� �Ѵ�
    }
}
void dirdcl(StringBuffer &bin, StringList &vout) { // ���� �����ڸ� �м��ϰ� ��� ���
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
        vout.push_back(identifier);
    }
    else if (ch == '(') { // direct-declarator: (declarator) (3)
        bin.getc(); // ( ���ڸ� �ؼ��ؼ� ���������Ƿ� �������� �ѱ��
        dcl(bin, vout);
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
            vout.push_back("()");
        }
        else if (ch == '[') { // �迭 ��ȣ ȹ��
            bin.getc(); // [ ��ȣ�� �ؼ��ؼ� ���������Ƿ� �ѱ��
            if (bin.peekc() != ']') // �ݴ� ��ȣ�� ������ ����
                throw Exception("�߸��� �迭 ��ȣ�Դϴ�.");
            bin.getc(); // ] ��ȣ�� �ؼ������Ƿ� �������� �ѱ��
            vout.push_back("[]");
        }
        else { // �̿��� ��� �ݺ����� Ż���Ѵ�
            break;
        }
    }
}