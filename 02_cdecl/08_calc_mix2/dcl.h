#ifndef __DECLARATION_H__
#define __DECLARATION_H__

#include <vector>
#include "IdentifierInfo.h"

// ������ �м��ϰ� ȹ���� ��ū�� ���͸� ��ȯ�մϴ�.
std::vector<IdentifierInfo> get_dcl_info(const char *decl);

#endif