/**
C의 수식을 분석합니다.
*/
function initProgramCompilerExpression(compiler, CompilerException) {
  var _Expression = {};
  
  // 속성 정의 이전에 정의되어야 하는 내용을 작성합니다.
  var AssignmentOperatorDict = {
    "=": true, "+=": true, "-=": true, "*=":true,
    "/=":true, "%=": true, "&=": true, "^=": true,
    "|=": true, "<<=": true, ">>=": true
  };
  var PrefixOperatorDict = {
    "sizeof": true, "++": true, "--": true,
    "+": true, "-": true, "*": true,
    "&": true, "~": true, "!": true
  };
  var BinaryOperatorDict = {
    "*": 1, "/": 1, "%": 1,
    "+": 2, "-": 2,
    "<<": 3, ">>": 3,
    "<": 4, "<=": 4, ">": 4, ">=": 4,
    "==": 5, "!=": 5,
    "&": 6,
    "^": 7,
    "|": 8,
    "&&": 9,
    "||": 10
  };
  
  // 형식 정의
  /**
  수식을 정의합니다.
  @param {Array.<AssignmentExpression>} assignExprList
  */
  function ExpressionInfo(assignExprList) {
    this.assignmentExprList = assignExprList;
  }
  ExpressionInfo.prototype.toString = function() {
    return Handy.format('[Expr %s]', this.assignmentExprList);
  };
  /**
  할당식을 정의합니다.
  @param {Array} exprTokenList
  */
  function AssignmentExpression(exprTokenList) {
    this.expressionTokenList = exprTokenList;
  }
  AssignmentExpression.prototype.toString = function() {
    return Handy.format('[AssignExpr %s]', this.expressionTokenList.join(NEWLINE));
  };
  /**
  단항식을 정의합니다.
  @param {Array} exprTokenList
  */
  function UnaryExpression(exprTokenList) {
    this.expressionTokenList = exprTokenList;
  }
  UnaryExpression.prototype.toString = function() {
    return Handy.format('[UnaryExpr %s]', this.expressionTokenList);
  };
  /**
  캐스트를 정의합니다.
  @param {DeclarationSpecifier} declspec
  @param {AbstractDeclarator} absdecl
  */
  function CastOperator(declspec, absdecl) {
    this.declarationSpecifier = declspec;
    this.abstractDeclarator = absdecl;
  }
  CastOperator.prototype.toString = function() {
    return Handy.format
      ('[Cast %s%s]', this.declarationSpecifier, this.abstractDeclarator);
  };
  /**
  접미 수식을 정의합니다.
  @param {Array} exprTokenList
  */
  function PostfixExpression(exprTokenList) {
    this.expressionTokenList = exprTokenList;
  }
  PostfixExpression.prototype.toString = function() {
    return Handy.format('[PostExpr %s]', this.expressionTokenList);
  };
  /**
  기본 수식을 정의합니다.
  @param {object} value
  */
  function PrimaryExpression(value) {
    this.value = value;
  }
  PrimaryExpression.prototype.toString = function() {
    return Handy.format('[PrimaryExpr %s]', this.value);
  };
  /**
  조건식을 정의합니다.
  @param {BinaryExpression} condExpr
  @param {Expression} trueExpr
  @param {ConditionalExpression} falseExpr
  */
  function ConditionalExpression(condExpr, trueExpr, falseExpr) {
    this.conditionExpression = condExpr;
    this.trueExpression = trueExpr;
    this.falseExpression = falseExpr;
  }
  ConditionalExpression.prototype.toString = function() {
    var caseExpr = '';
    if (this.trueExpression != undefined) {
      caseExpr = Handy.format('?%s:%s', this.trueExpression, this.falseExpression);
    }
    return Handy.format('[CondExpr %s%s]', this.conditionExpression, caseExpr);
  };
  /**
  이항식을 정의합니다.
  @param {Array} exprTokenList
  */
  function BinaryExpression(exprTokenList) {
    this.expressionTokenList = exprTokenList;
  }
  BinaryExpression.prototype.toString = function() {
    return Handy.format('[BinaryExpr %s]', this.expressionTokenList);
  };
  
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
        var condExpr = getConditionalExpression(buffer); // 조건식 획득을 시도합니다.
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
    return AssignmentOperatorDict[token] ? true : false;
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
    if (is_prefix_op(token))
      return token;
    else if (token == '(') { // 캐스트 연산의 시작인 경우
      var castOperator = getCastOperator(buffer); // 캐스트를 획득합니다.
      if (castOperator == null) { // 캐스트 연산자 획득에 실패한 경우
        // 버퍼 포인터를 복구하고 null을 반환합니다.
        buffer.idx = originIndex;
        return null;
      }
      
      // 다음 토큰이 닫는 소괄호라면 성공한 것으로 간주합니다.
      if (buffer.get_ctoken() == ')')
        return castOperator;
    }
    
    buffer.idx = originIndex;
    return null;
  }
  /**
  전위 연산자라면 true, 아니면 false를 반환합니다.
  @param {string} token
  @return {boolean}
  */
  function is_prefix_op(token) {
    return PrefixOperatorDict[token] ? true : false;
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
      if (ex instanceof CompilerException) {
        buffer.idx = originIndex;
        return null;
      }
      throw ex;
    }
  }
  /**
  접미 수식을 획득합니다. 실패시 포인터를 복구하고 null을 반환합니다.
  @param {StringBuffer} buffer
  */
  function getPostfixExpression(buffer) {
    // 수식 토큰 리스트를 생성합니다.
    var exprTokenList = [];
    // 기본 수식을 획득합니다.
    var primaryExpr = getPrimaryExpression(buffer);
    // 수식 토큰 리스트에 기본 수식을 넣습니다.
    exprTokenList.push(primaryExpr);
    // 획득한 정보를 바탕으로 기본 수식 객체를 생성하고 반환합니다.
    var postExpr = new PostfixExpression(exprTokenList);
    return postExpr;
  }
  /**
  기본 수식을 획득합니다. 실패시 포인터를 복구하고 null을 반환합니다.
  @param {StringBuffer} buffer
  */
  function getPrimaryExpression(buffer) {
    var originIndex = buffer.idx; // 최초 버퍼 포인터를 보관합니다.
    try {
      var primaryExpr = null; // 기본 수식에 대한 변수입니다.
      var token = buffer.get_ctoken(); // 토큰을 획득합니다.
      
      if (token == '(') { // 여는 소괄호라면 4번 정의에 해당합니다.
        var expr = getExpressionInfo(buffer); // 수식을 획득합니다.
        if (buffer.get_ctoken() != ')') // 닫는 소괄호가 없으면
          throw new CompilerException // 예외 처리합니다.
            ('cannot find small close bracket');
        // 기본 수식 객체를 생성합니다.
        primaryExpr = new PrimaryExpression(expr);
      }
      else {
        // 기본 수식 객체를 생성합니다.
        primaryExpr = new PrimaryExpression(token);
      }
      return primaryExpr;
    } catch (ex) { // 실패시 포인터를 복구하고 null을 반환합니다.
      if (ex instanceof CompilerException) {
        buffer.idx = originIndex;
        return null;
      }
      throw ex;
    }
  }
  /**
  조건식을 획득합니다. 실패시 포인터를 복구하고 null을 반환합니다.
  @param {StringBuffer} buffer
  @return {ConditionalExpression}
  */
  function getConditionalExpression(buffer) {
    var originIndex = buffer.idx; // 초기 버퍼 포인터를 보관합니다.
    
    try {
      // 이항 수식을 획득합니다.
      var binaryExpr = getBinaryExpression(buffer);
      buffer.trim(); // 다음 토큰의 시작 지점으로 버퍼 포인터를 옮깁니다.
      
      // 물음표 토큰이 존재한다면 식을 두 개 획득합니다.
      if (buffer.peekc() == '?') {
        buffer.getc(); // 분석한 물음표 기호를 지나갑니다.
        
        // 참일 경우의 식을 획득합니다.
        var trueExpr = getExpressionInfo(buffer);
        if (buffer.get_ctoken() != ':') // 조건식의 2번 정의에 맞지 않으면
          throw new CompilerException // 예외 처리합니다.
            ('cannot find colon of conditional expression');
        
        // 거짓일 경우의 식을 획득합니다.
        var falseExpr = getConditionalExpression(buffer);
        
        // 획득한 식 중 하나라도 잘못된 식이라면 예외 처리합니다.
        if (trueExpr == null || falseExpr == null)
          throw new CompilerException
            ('empty expression found in conditional expression');
        
        // 획득한 정보를 바탕으로 조건식을 생성합니다.
        var condExpr = new ConditionalExpression
          (binaryExpr, trueExpr, falseExpr);
      }
      else {
        // 획득한 정보를 바탕으로 조건식을 생성합니다.
        var condExpr = new ConditionalExpression(binaryExpr);
      }
      
      // 생성한 조건식 객체를 반환합니다.
      return condExpr;
    } catch (ex) { // 실패시 포인터를 복구하고 null을 반환한다.
      if (ex instanceof CompilerException) {
        buffer.idx = originIndex;
        return null;
      }
      throw ex;
    }
  }
  /**
  이항 수식을 획득합니다. 실패시 포인터를 복구하고 null을 반환합니다.
  @param {StringBuffer} buffer
  @return {BinaryExpression}
  */
  function getBinaryExpression(buffer) {
    var originIndex = buffer.idx; // 최초 버퍼 포인터를 보관합니다.
    try {
      // 수식 토큰 리스트를 생성합니다.
      var exprTokenList = [];

      // 버퍼에 데이터가 남아있는 동안
      while (buffer.is_empty() == false) {
        var prevIndex = buffer.idx; // 이전 버퍼 포인터를 보관합니다.

        // 단항식을 획득합니다.
        var unaryExpr = getUnaryExpression(buffer);
        if (unaryExpr == null) { // 단항식 획득에 실패한 경우
          // 버퍼 포인터를 복구하고 반복문을 탈출합니다.
          buffer.idx = prevIndex;
          break;
        }
        // 획득한 단항식을 수식 토큰 리스트에 넣습니다.
        exprTokenList.push(unaryExpr);

        // 버퍼 포인터를 보관하고 다음 토큰을 획득합니다.
        prevIndex = buffer.idx;
        var token = buffer.get_ctoken();

        // 획득한 토큰이 이항 연산자가 아니라면
        if (is_binary_op(token) == false) {
          //버퍼 포인터를 복구하고 반복문을 탈출합니다.
          buffer.idx = prevIndex;
          break;
        }
        // 획득한 이항 연산자를 수식 토큰 리스트에 넣습니다.
        exprTokenList.push(token);
      }
      // 획득한 토큰이 없는 경우 예외 처리합니다.
      if (exprTokenList.length == 0)
        throw new CompilerException
          ('cannot find binary expression');

      // 획득한 정보를 바탕으로 이항 수식 객체를 생성하고 반환합니다.
      var binaryExpr = new BinaryExpression(exprTokenList);
      return binaryExpr;
    } catch (ex) { // 실패시 버퍼 퐁니터를 복구하고 null을 반환합니다.
      if (ex instanceof CompilerException) {
        buffer.idx = originIndex;
        return null;
      }
      throw ex;
    }
  }
  /**
  이항 연산자라면 true, 아니면 false를 반환합니다.
  @param {string} token
  @return {boolean}
  */
  function is_binary_op(token) {
    return BinaryOperatorDict[token] ? true : false;
  }
  
  /* ... */
  
  // 등록
  _Expression.getExpressionInfo = getExpressionInfo;
  compiler.Expression = _Expression;
}