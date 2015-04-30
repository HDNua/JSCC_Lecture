#ifndef __HANDY_STRINGBUFFER_H__
#define __HANDY_STRINGBUFFER_H__

#include <string>
class StringBuffer {
    std::string str;
    unsigned len;
    unsigned idx;

public:
    StringBuffer(const char *s = "");
    StringBuffer(const std::string &str);
    ~StringBuffer();

    // ���۸� ���ڿ��� �ʱ�ȭ�մϴ�.
    void init(const char *str);
    void init(const std::string &str);

    // ���۷κ��� ���ڸ� �ϳ� �н��ϴ�. �����Ͱ� �̵��մϴ�.
    char getc();
    // ������ �����Ͱ� ����Ű�� ���ڸ� �����ɴϴ�. �����ʹ� �̵����� �ʽ��ϴ�.
    char peekc() const;
    // ���ۿ��� �о��� ���� �ǵ����ϴ�. �ǵ��� �� ������ false�� ��ȯ�մϴ�.
    bool ungetc();

    // ������ ���� ���� �Ǵ� ���ڿ��� �߰��մϴ�.
    void add(char c);
    void add(const char *s);
    void add(const std::string &str);

    // ���۰� ����ִٸ� true, ���� �� ���� �� �ִٸ� false�� ��ȯ�մϴ�.
    bool is_empty() const;
};

#endif