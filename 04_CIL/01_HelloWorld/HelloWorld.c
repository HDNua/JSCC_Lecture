#include "CIL.h"

STRING sHelloWorld = "Hello, world!"; // ���α׷��� ����� ���ڿ��� �����մϴ�.

PROC(main) // main ���ν����� ���� �����Դϴ�. PROC�� procedure�� ���Ӹ��Դϴ�.

PUSH(sHelloWorld) // �ֿܼ� ���ڿ��� ����ϱ� ���� ���ڸ� �����մϴ�.
INVOKE(print_str) // �ֿܼ� ���ڿ��� ����ϴ� ���ν����� ȣ���մϴ�.

ENDP // ���ν����� ���ǰ� ����Ǵ� �����Դϴ�.