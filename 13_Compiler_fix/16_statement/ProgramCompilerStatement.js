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
  
  /**
  문장을 분석합니다.
  @param {StringBuffer} buffer
  @return {StatementInfo}
  */
  function getStatementInfo(buffer) {
    /* ... */
  }
  
  // 등록
  _Statement.getStatementInfo = getStatementInfo;
  compiler.Statement = _Statement;
}