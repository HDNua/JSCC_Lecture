/**
C의 문장을 분석합니다.
*/
function initProgramCompilerStatement(compiler, CompilerException) {
  var _Statement = {};
  
  /**
  문장을 정의합니다.
  */
  function StatementInfo(stmt) {
    this.statement = stmt;
  }
  StatementInfo.prototype.toString = function() {
    return Handy.format('%s', this.statement);
  };
  /**
  수식문을 정의합니다.
  @param {ExpressionInfo} exprInfo
  */
  function ExpressionStatementInfo(exprInfo) {
    this.expressionInfo = exprInfo;
  }
  ExpressionStatementInfo.prototype.toString = function() {
    return Handy.format('[%s]', this.expressionInfo);
  };
  
  /**
  문장을 분석합니다.
  @param {StringBuffer} buffer
  @return {StatementInfo}
  */
  function getStatementInfo(buffer) {
    var exprStmtInfo = getExpressionStatementInfo(buffer);
    var stmtInfo = new StatementInfo(exprStmtInfo);
    return stmtInfo;
  }
  /**
  수식문을 분석합니다.
  @param {StringBuffer} buffer
  */
  function getExpressionStatementInfo(buffer) {
    var Expr = Program.Compiler.Expression;
    
    // 수식을 획득합니다.
    var exprInfo = Expr.getExpressionInfo(buffer);
    
    // 다음 토큰의 시작 지점으로 버퍼 포인터를 맞춥니다.
    buffer.trim();
    // 세미콜론을 발견할 수 없으면 명백한 문법 위반입니다.
    if (buffer.peekc() != ';')
      throw new CompilerException('cannot find end of expression', buffer);
    
    // 확인한 세미콜론을 지나갑니다.
    buffer.getc();
    
    // 획득한 정보를 바탕으로 객체를 생성하고 반환합니다.
    var exprStmt = new ExpressionStatementInfo(exprInfo);
    return exprStmt;
  }
  
  // 등록
  _Statement.getStatementInfo = getStatementInfo;
  compiler.Statement = _Statement;
}