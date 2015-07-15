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
    /* ... */
  }
  /**
  단항식을 획득합니다.
  @param {StringBuffer} buffer
  @return {UnaryExpression}
  */
  function getUnaryExpression(buffer) {
    /* ... */
  }
  /**
  조건식을 획득합니다.
  @param {StringBuffer} buffer
  @return {ConditionExpression}
  */
  function getConditionExpression(buffer) {
    /* ... */
  }
  
  /* ... */
  
  // 등록
  _Expression.getExpressionInfo = getExpressionInfo;
  compiler.Expression = _Expression;
}