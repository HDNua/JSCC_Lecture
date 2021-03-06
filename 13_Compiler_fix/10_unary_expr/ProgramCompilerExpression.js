/**
C의 수식을 분석합니다.
*/
function initProgramCompilerExpression(compiler, CompilerException) {
  var _Expression = {};
  
  // 형식 정의
  /**
  수식을 정의합니다.
  @param {Array.<AssignmentExpression>} assignExprList
  */
  function ExpressionInfo(assignExprList) {
    this.assignmentExprList = assignExprList;
  }
  /**
  할당식을 정의합니다.
  @param {Array} exprTokenList
  */
  function AssignmentExpression(exprTokenList) {
    this.expressionTokenList = exprTokenList;
  }
  /**
  단항식을 정의합니다.
  @param {Array} exprTokenList
  */
  function UnaryExpression(exprTokenList) {
    this.expressionTokenList = exprTokenList;
  }
  /**
  캐스트를 정의합니다.
  @param {DeclarationSpecifier} declspec
  @param {AbstractDeclarator} absdecl
  */
  function CastOperator(declspec, absdecl) {
    this.declarationSpecifier = declspec;
    this.abstractDeclarator = absdecl;
  }
  
  
  // 메서드 정의
  /**
  수식을 획득합니다. 실패시 포인터를 복구하고 null을 반환합니다.
  @param {StringBuffer} buffer
  @return {ExpressionInfo}
  */
  function getExpressionInfo(buffer) {
    // 수식 획득 전의 버퍼 포인터를 보관합니다.
    var originIndex = buffer.idx;
    
    // 반환할 수식 객체에 대한 변수를 생성합니다.
    var exprInfo = null;
    
    // 할당식 리스트를 획득합니다.
    var assignExprList = [];
    while (buffer.is_empty() == false) { // 버퍼에 데이터가 남아있는 동안
      // 할당식 객체를 획득합니다.
      var assignExprInfo = getAssignmentExpression(buffer);
      if (assignExprInfo == null) // 할당식 획득에 실패한 경우
        break; // 할당식 획득을 종료합니다.
      
      // 획득한 할당식을 리스트에 넣습니다.
      assignExprList.push(assignExprInfo);
      
      // 다음 토큰의 시작 지점으로 버퍼 포인터를 맞춥니다.
      buffer.trim();
      // 다음 토큰이 반점이 아니라면 탈출합니다.
      if (buffer.peekc() != ',')
        break;
      // 사용한 반점 토큰은 지나갑니다.
      buffer.getc();
    }
    // 획득한 할당식이 없으면 버퍼 포인터를 복구하고 null을 반환합니다.
    if (assignExprList.length == 0) {
      buffer.idx = originIndex;
      return null;
    }
    
    // 획득한 정보를 바탕으로 수식 객체를 생성합니다.
    exprInfo = new ExpressionInfo(assignExprList);
    // 수식 객체를 반환합니다.
    return exprInfo;
  }
  /**
  할당식을 획득합니다.
  @param {StringBuffer} buffer
  @return {AssignmentExpression}
  */
  function getAssignmentExpression(buffer) {
    var originIndex = buffer.idx; // 버퍼 포인터 위치를 보관합니다.
    var assignExpr = null; // 반환할 객체에 대한 변수를 생성합니다.

    // 할당식을 위한 수식 토큰 리스트를 만듭니다.
    var exprTokenList = [];

    while (buffer.is_empty() == false) { // 버퍼에 데이터가 남아있는 동안
      var prevIndex = buffer.idx; // 토큰 획득 이전의 버퍼 포인터를 보관합니다.
      var unaryExpr = getUnaryExpression(buffer); // 단항식 획득을 시도합니다.
      var assignOp = buffer.get_ctoken(buffer); // 다음 토큰을 획득합니다.

      if (unaryExpr && is_assign_op(assignOp)) { // 단항식과 할당 연산자 획득 성공 시
        // 획득한 요소를 리스트에 넣습니다.
        exprTokenList.push(unaryExpr);
        exprTokenList.push(assignOp);
      }
      else { // 실패한 경우 조건식을 획득하고 종료합니다.
        buffer.idx = prevIndex; // 단항식 획득 시도 전의 버퍼 포인터의 위치로 복구합니다.
        var condExpr = getConditionExpression(buffer); // 조건식 획득을 시도합니다.
        if (condExpr == null) { // 조건식 획득에 실패했다면
          // 버퍼 포인터를 가장 처음의 위치로 복구하고 null을 반환합니다.
          buffer.idx = originIndex;
          return null;
        }
        exprTokenList.push(condExpr); // 조건식을 리스트에 넣습니다.
        break; // 반복문을 탈출합니다.
      }
    }

    // 획득한 정보를 바탕으로 객체를 생성하고 반환합니다.
    assignExpr = new AssignmentExpression(exprTokenList);
    return assignExpr;
  }
  /**
  할당 연산자라면 true, 아니면 false를 반환합니다.
  @param {string} token
  @return {boolean}
  */
  function is_assign_op(token) {
    
  }
  /**
  단항식을 획득합니다.
  @param {StringBuffer} buffer
  @return {UnaryExpression}
  */
  function getUnaryExpression(buffer) {
    var originIndex = buffer.idx; // 최초 버퍼 포인터 위치를 보관합니다.
    var exprTokenList = []; // 단항식을 위한 수식 토큰 리스트를 만듭니다.
    
    while (buffer.is_empty() == false) { // 버퍼에 데이터가 남아있는 동안
      var prevIndex = buffer.idx; // 버퍼 포인터 위치를 보관합니다.
      var op = getPrefixOperator(buffer); // 전위 연산자 획득을 시도합니다.
      
      if (op == null) { // 토큰 획득 실패 시 접미 수식으로 간주합니다.
        buffer.idx = prevIndex; // 버퍼 포인터를 복구합니다.
        // 접미 수식을 획득합니다.
        var postExpr = getPostfixExpression(buffer);
        if (postExpr == null) { // 획득에 실패했다면
          // 버퍼 포인터를 최초 값으로 복구하고 null을 반환합니다.
          buffer.idx = originIndex;
          return null;
        }
        // 접미 수식을 수식 토큰 리스트에 넣고 종료합니다.
        exprTokenList.push(postExpr);
        break;
      }
      else if (op == 'sizeof') { // sizeof라면
        var cast = getCastOperator(buffer); // 캐스트 연산자 획득을 시도합니다.
        if (cast != null) { // 획득에 성공했다면
          // 정의에 의해 토큰 획득을 끝냅니다.
          exprTokenList.push(op);
          exprTokenList.push(cast);
          break;
        }
        // 단항식을 계속 획득합니다.
        exprTokenList.push(op);
      }
      else { // 그 외의 경우 전위 연산자로 처리합니다.
        exprTokenList.push(op);
      }
    }
    
    // 획득한 정보를 바탕으로 객체를 생성하고 반환합니다.
    var unaryExpr = new UnaryExpression(exprTokenList);
    return unaryExpr;
  }
  /**
  전위 연산자를 획득합니다. 실패시 포인터를 복구하고 null을 반환합니다.
  @param {StringBuffer} buffer
  */
  function getPrefixOperator(buffer) {
    var originIndex = buffer.idx; // 최초 버퍼 포인터를 보관합니다.
    var token = buffer.get_ctoken(); // 토큰을 획득합니다.
    
    // 일반 단항 연산자인 경우 그냥 반환합니다.
    if (token == 'sizeof'
        || token == '++' || token == '--'
        || ('+-*&~!'.indexOf(token) >= 0))
      return token;
    else if (token == '(') { // 캐스트 연산의 시작인 경우
      var castOperator = getCastOperator(buffer); // 캐스트를 획득합니다.
      if (castOperator == null) { // 캐스트 연산자 획득에 실패한 경우
        // 버퍼 포인터를 복구하고 null을 반환합니다.
        buffer.idx = originIndex;
        return null;
      }
      // 다음 토큰이 닫는 소괄호라면 성공한 것으로 간주합니다.
      if (buffer.get_ctoken() == ',')
        return castOperator;
    }
    
    buffer.idx = originIndex;
    return null;
  }
  /**
  캐스트 연산자를 획득합니다. 실패시 포인터를 복구하고 null을 반환합니다.
  @param {StringBuffer} buffer
  */
  function getCastOperator(buffer) {
    var Declaration = Program.Compiler.Declaration;
    var originIndex = buffer.idx; // 최초 버퍼 포인터를 보관합니다.
    
    try {
      // 선언 지정자를 획득합니다.
      var declspec = Declaration.getDeclarationSpecifier(buffer);
      if (declspec == null) // 획득에 실패한 경우 null을 반환합니다.
        throw new CompilerException
          ('cannot find declaration specifiers');
      // 캐스트 연산자에는 선언 지정자가 있을 수 없습니다.
      else if (declspec.storageClassSpecifier != null)
        throw new CompilerException
          ('storage class specifier found in cast operator');
      
      // 추상 선언자를 획득합니다.
      var absdecl = Declaration.getAbstractDeclarator(buffer);
      // 캐스트 연산자에서는 식별자가 발견되면 안 됩니다.
      if (absdecl.identifier != null)
        throw new CompilerException
          ('identifier found in cast operator');
      
      // 획득한 정보를 바탕으로 캐스트 연산자 객체를 생성하여 반환합니다.
      var castOperator = new CastOperator(declspec, absdecl);
      return castOperator;
    } catch (ex) {
      // 버퍼 포인터를 복구하고 null을 반환합니다.
      buffer.idx = originIndex;
      return null;
    }
  }
  
  /**
  조건식을 분석합니다.
  @param {StringBuffer} buffer
  @return {ConditionExpression}
  */
  function getConditionExpression(buffer) {
    
  }
  
  /* ... */
  
  // 등록
  _Expression.getExpressionInfo = getExpressionInfo;
  compiler.Expression = _Expression;
}