/**
C의 문장을 분석합니다.
*/
function initProgramCompilerStatement(compiler, CompilerException) {
  var _Statement = {};
  
  /**
  
  */
  function StatementInfo() {
    
  }
  /**
  
  */
  function ExpressionStatementInfo() {
    
  }
  function IterationStatementInfo() {
    
  }
  function SelectionStatementInfo() {
    
  }
  function CompoundStatementInfo() {
    
  }
  function LabeledStatementInfo() {
    
  }
  function JumpStatementInfo() {
    
  }
  
  /**
  문장을 분석합니다.
  @param {StringBuffer} buffer
  @return {StatementInfo}
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
  /**
  복합문을 분석합니다.
  @param {StringBuffer} buffer
  */
  function compoundStatement(buffer) {
    var Decl = Program.Compiler.Declaration;
    
    // 여는 중괄호가 발견되지 않는다면 명백한 문법 위반입니다.
    if (buffer.get_ctoken() != '{')
      throw new CompilerException
        ('cannot find start of block');
    
    // 선언 리스트를 획득합니다.
    while (buffer.is_empty() == false) {
      // 선언을 획득합니다.
      var declaration = Decl.getDeclarationInfo(buffer);
      
      // 선언 획득에 실패했다면 이후부터 문장으로 간주합니다.
      if (declaration == null)
        break;
      
      // 획득한 선언을 처리합니다.
      /* ... */
    }
    
    // 문장 리스트를 획득합니다.
    while (buffer.is_empty() == false) {
      // 문장을 분석합니다.
      statement(buffer);
    }
    
    // 닫는 중괄호가 발견되지 않는다면 명백한 문법 위반입니다.
    if (buffer.get_ctoken() != '}')
      throw new CompilerException
        ('cannot find end of block');
  }
  
  /* ... */
  
  // 등록
  _Statement.compound = compoundStatement;
  _Statement.statement = statement;
  compiler.Statement = _Statement;
}