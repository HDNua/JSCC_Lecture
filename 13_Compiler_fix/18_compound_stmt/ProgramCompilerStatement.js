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
  복합문을 정의합니다.
  @param {Array.<DeclarationInfo>} decl_list
  @param {Array.<StatementInfo>} stmt_list
  */
  function CompoundStatementInfo(decl_list, stmt_list) {
    this.declarationList = decl_list;
    this.statementList = stmt_list;
  }
  CompoundStatementInfo.prototype.toString = function() {
    return Handy.format('[%s | %s]', this.declarationList, this.statementList);
  };
  
  /**
  문장을 분석합니다.
  @param {StringBuffer} buffer
  @return {StatementInfo}
  */
  function getStatementInfo(buffer) {
    buffer.trim(); // 다음 토큰의 시작 지점으로 버퍼 포인터를 옮깁니다.
    
    var stmtInfo = null; // 문장 객체에 대한 변수입니다.
    if (buffer.peekc() == '{') { // 복합문의 시작이면 복합문을 획득합니다.
      var compoundStmtInfo = getCompoundStatementInfo(buffer);
      stmtInfo = new StatementInfo(compoundStmtInfo);
    }
    else if (buffer.peekc() == '}') { // 복합문의 끝이면 null을 반환합니다.
      return null;
    }
    else { // 그 외의 경우 수식문으로 간주합니다.
      var exprStmtInfo = getExpressionStatementInfo(buffer);
      stmtInfo = new StatementInfo(exprStmtInfo);
    }
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
  /**
  복합문을 분석합니다.
  @param {StringBuffer} buffer
  */
  function getCompoundStatementInfo(buffer) {
    buffer.trim(); // 다음 토큰의 시작 지점으로 버퍼 포인터를 맞춥니다.
    if (buffer.peekc() != '{')
      throw new CompilerException
        ('cannot find start of compound statement', buffer.str);
    buffer.getc(); // 여는 중괄호를 지나갑니다.
    
    var Decl = Program.Compiler.Declaration;
    
    // 선언 리스트를 생성합니다.
    var decl_list = [];
    while (buffer.is_empty() == false) { // 버퍼에 데이터가 남아있는 동안
      var declInfo = Decl.getDeclarationInfo(buffer); // 선언 정보를 획득합니다.
      if (declInfo == null) // 선언 획득 실패 시 이후를 문장으로 간주합니다.
        break;
      decl_list.push(declInfo); // 선언 리스트에 선언 정보를 넣습니다.
    }
    
    // 문장 리스트를 생성합니다.
    var stmt_list = [];
    while (buffer.is_empty() == false) { // 버퍼에 데이터가 남아있는 동안
      var stmtInfo = getStatementInfo(buffer); // 문장 정보를 획득합니다.
      if (stmtInfo == null) // 문장 획득 실패 시 종료합니다.
        break;
      stmt_list.push(stmtInfo); // 문장 리스트에 문장 정보를 넣습니다.
    }
    
    buffer.trim(); // 다음 토큰의 시작 지점으로 버퍼 포인터를 맞춥니다.
    if (buffer.peekc() != '}')
      throw new CompilerException
        ('cannot find end of compound statement', buffer);
    buffer.getc(); // 닫는 중괄호를 지나갑니다.
    
    // 획득한 정보를 바탕으로 객체를 생성하고 반환합니다.
    var compoundInfo = new CompoundStatementInfo(decl_list, stmt_list);
    return compoundInfo;
  }
  
  // 등록
  _Statement.getCompoundStatementInfo = getCompoundStatementInfo;
  _Statement.getStatementInfo = getStatementInfo;
  compiler.Statement = _Statement;
}