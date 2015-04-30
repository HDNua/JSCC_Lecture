#ifndef __DECLARATION_H__
#define __DECLARATION_H__

#include <vector>
#include "IdentifierInfo.h"

// 선언을 분석하고 획득한 토큰의 벡터를 반환합니다.
std::vector<IdentifierInfo> get_dcl_info(const char *decl);

#endif