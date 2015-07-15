/**
C의 문장을 분석합니다.
*/
function initProgramCompilerStatement(compiler, CompilerExpression) {
  var _Statement = {};
  
  /**
  문장을 분석합니다.
  @param {StringBuffer} buffer
  */
  function statement(buffer) {
    /* ... */
  }
  
  /**
  수식문을 분석합니다.
  @param {StringBuffer} buffer
  */
  function expressionStatement(buffer) {
    var Expr = Program.Compiler.Expression;
    
    // 수식을 획득합니다.
    var exprInfo = Expr.getExpressionInfo(buffer);
    
    // 수식 획득에 성공한 경우의 처리입니다.
    if (exprInfo != null) {
      /* ... */
    }
    
    // 다음 토큰의 시작 지점으로 버퍼 포인터를 옮깁니다.
    buffer.trim();
    // 세미콜론이 발견되지 않는다면 분명한 문법 위반입니다.
    if (buffer.peekc() != ';')
      throw new CompilerException
        ('cannot find end of expression');
    // 분석한 세미콜론은 지나갑니다.
    buffer.getc();
  }
  
  /* ... */
  
  // 등록
  _Statement.statement = statement;
  compiler.Statement = _Statement;
}