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
  
  /* ... */
  
  // 등록
  _Statement.statement = statement;
  compiler.Statement = _Statement;
}