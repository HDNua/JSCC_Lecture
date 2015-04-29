#include <iostream>
typedef std::string Exception;
int calculate(const char *expr); // �Ѱܹ��� ���� ����Ͽ� ���� ��ȯ�Ѵ�
int main(void) {
    try {
        // �Է��� ���̰� MAX_EXPR_LEN���� ū ��찡
        // �߻����� �ʴ´ٰ� �����Ѵ�
        const int MAX_EXPR_LEN = 256;
        char expression[MAX_EXPR_LEN] = "";
        int loop;
        std::cin >> loop;
        // loop ȸ����ŭ �ݺ����� �����Ѵ�
        while (loop-- > 0) {
            std::cout << "Enter expression: ";
            std::cin >> expression;
            std::cout << calculate(expression) << std::endl;
        }
        return 0;
    }
    catch (Exception &ex) {
        std::cerr << ex.c_str() << std::endl;
        return 1;
    }
}
int calculate(const char *expr) { // �Ѱܹ��� ���� ����Ͽ� ���� ��ȯ�Ѵ�
    char ch = *expr;
    if (ch < '0' || '9' < ch) { // �Է��� ó���� ���ڰ� �ƴ϶�� ���� ó��
        throw Exception("Ÿ������ ���� �Է��Դϴ�.");
    }
    int digit; // �ڸ����� ������ �ӽ� ����
    // ���ʿ� ��Ÿ���� �� ȹ��
    int left = 0;
    for (ch = *expr; (ch = *expr) != '\0'; ++expr) { // �Է��� ���� ��Ÿ���� ������
        if (ch < '0' || '9' < ch) { // ���� �ƴ� ���ڰ� ��Ÿ���� Ż��
            break;
        }
        digit = ch - '0'; // ���� �ùٸ� ������ �ٲ۴�(���� '0'�� ���� 48�� ����)
        left = 10 * left + digit;
    }
    if (ch == '\0') { // �����ڰ� ��Ÿ���� ���� �Է��� �����ٸ�
        return left; // ������ ������ �����ϰ� ȹ���� ���� ��ȯ
    }
    // ������ ȹ��: ��Ģ ���꿡 ���ؼ��� �ٷ�Ƿ� ������ ���̴� �ݵ�� 1
    char op = *expr++; // ���ڿ� �����Ͱ� ����Ű�� �����ڸ� ȹ�� �� ������ �̵�
    // �����ʿ� ��Ÿ���� �� ȹ��: ������ ���� ����
    int right = 0;
    for (ch = *expr; (ch = *expr) != '\0'; ++expr) { // �Է��� ���� ��Ÿ���� ������
        if (ch < '0' || '9' < ch) { // ���� �ƴ� ���ڰ� ��Ÿ���� Ż��
            break;
        }
        digit = ch - '0'; // ���� �ùٸ� ������ �ٲ۴�(���� '0'�� ���� 48�� ����)
        right = 10 * right + digit;
    }
    // ȹ���� ���� �����ڸ� �̿��Ͽ� ����
    int retVal = 0;
    switch (op) {
    case '+': retVal = left + right; break;
    case '-': retVal = left - right; break;
    case '*': retVal = left * right; break;
    case '/': retVal = left / right; break;
    default: throw Exception("�ùٸ� �����ڰ� �ƴմϴ�.");
    }
    return retVal;
}