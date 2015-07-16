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
  선택문을 정의합니다.
  @param {string} selectionType
  @param {ExpressionInfo} condition
  @param {StatementInfo} stmt
  @param {StatementInfo} elseStmt
  */
  function SelectionStatementInfo(selectionType, condition, stmt, elseStmt) {
    this.selectionType = selectionType;
    this.condition = condition;
    this.statement = stmt;
    this.elseStatement = elseStmt;
  }
  SelectionStatementInfo.prototype.toString = function() {
    var selType = this.selectionType;
    var condExpr = this.condition;
    var stmt = this.statement;
    var elseStmt = this.elseStatement;
    var after = Handy.format
      ('%s%s', stmt, elseStmt ? (' else ' + elseStmt) : '');
    return Handy.format('%s (%s) %s', selType, condExpr, after);
  };
  
  /**
  문장을 분석합니다.
  @param {StringBuffer} buffer
  @return {StatementInfo}
  */
  function getStatementInfo(buffer) {
    buffer.trim(); // 다음 토큰의 시작 지점으로 버퍼 포인터를 옮깁니다.
    var prevIndex = buffer.idx; // 버퍼 포인터를 보관합니다.
    var token = buffer.get_ctoken(); // 토큰을 획득합니다.
    buffer.idx = prevIndex; // 버퍼 포인터를 복구합니다.
    
    // 획득한 토큰을 기준으로 조건 분기합니다.
    var stmtInfo = null; // 문장 객체에 대한 변수입니다.
    switch (token) {
      // 복합문 토큰
      case '{': // 복합문을 분석하고 객체를 생성합니다.
        var compoundStmtInfo = getCompoundStatementInfo(buffer);
        stmtInfo = new StatementInfo(compoundStmtInfo);
        break;
      case '}': // 복합문의 마지막을 발견하면 null을 반환합니다.
        stmtInfo = null;
        break;
        
      // 선택문 토큰
      case 'if':
      case 'switch':
        var selectionStmtInfo = getSelectionStatementInfo(buffer);
        stmtInfo = new StatementInfo(selectionStmtInfo);
        break;
      
      // 그 외의 경우 수식문으로 간주합니다.
      default:
        var exprStmtInfo = getExpressionStatementInfo(buffer);
        stmtInfo = new StatementInfo(exprStmtInfo);
    }
    
    // 생성한 토큰을 반환합니다.
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
  /**
  선택문을 분석합니다.
  @param {StringBuffer} buffer
  @return {SelectionStatementInfo}
  */
  function getSelectionStatementInfo(buffer) {
    var Expr = Program.Compiler.Expression;
    
    var selectionStmt = null; // 선택문 객체에 대한 변수입니다.    
    var token = buffer.get_ctoken(); // 첫 토큰을 획득합니다.
    if (token == 'if') { // if 문자열인 경우
      var selectionType = token; // 선택문의 형식은 if입니다.
      
      // 여는 소괄호를 발견하지 못하면 예외 처리합니다.
      if (buffer.get_ctoken() != '(')
        throw new CompilerException('cannot find start of conditional expression');
      
      // 조건식을 획득합니다.
      var condExpr = Expr.getExpressionInfo(buffer);
      if (condExpr == null)
        throw new CompilerException('cannot find expression');
      
      // 닫는 소괄호를 발견하지 못하면 예외 처리합니다.
      if (buffer.get_ctoken() != ')')
        throw new CompilerException('cannot find end of conditional expression');
      
      // 조건식 이후에 나타나는 문장을 획득합니다.
      var trueStmt = getStatementInfo(buffer);
      if (trueStmt == null)
        throw new CompilerException('cannot find true case statement');
      
      // else 구문이 존재하는지 확인합니다.
      var falseStmt = null;
      var prevIndex = buffer.idx; // 버퍼 포인터를 임시로 보관합니다.
      token = buffer.get_ctoken(); // 토큰 획득을 시도합니다.
      if (token == 'else') { // else인 경우의 처리입니다.
        // 거짓인 경우의 문장을 획득합니다.
        falseStmt = getStatementInfo(buffer);
        if (falseStmt == null)
          throw new CompilerException('cannot find false case statement');
      }
      else { // else가 아니면 버퍼 포인터를 되돌립니다.
        buffer.idx = prevIndex;
      }
      
      // 획득한 정보를 바탕으로 객체를 생성합니다.
      selectionStmt = new SelectionStatementInfo
        (selectionType, condExpr, trueStmt, falseStmt);
    }
    else if (token == 'switch') { // switch 문자열인 경우
      var selectionType = token; // 선택문의 형식은 switch입니다.
      
      // 여는 소괄호를 발견하지 못하면 예외 처리합니다.
      if (buffer.get_ctoken() != '(')
        throw new CompilerException('cannot find start of conditional expression');
      
      // 조건식을 획득합니다.
      var condExpr = Expr.getExpressionInfo(buffer);
      if (condExpr == null)
        throw new CompilerException('cannot find expression');
      
      // 닫는 소괄호를 발견하지 못하면 예외 처리합니다.
      if (buffer.get_ctoken() != ')')
        throw new CompilerException('cannot find end of conditional expression');
      
      // 조건식 이후에 나타나는 문장을 획득합니다.
      var trueStmt = getStatementInfo(buffer);
      if (trueStmt == null)
        throw new CompilerException('cannot find true case statement');
      
      // 획득한 정보를 바탕으로 객체를 생성합니다.
      selectionStmt = new SelectionStatementInfo
        (selectionType, condExpr, trueStmt);
    }
    else { // 그 외의 경우 예외 처리합니다.
      throw new CompilerException
        ('invalid selection statement token', token);
    }
    
    // 생성한 객체를 반환합니다.
    return selectionStmt;
  }
  
  
  // 등록
  _Statement.getCompoundStatementInfo = getCompoundStatementInfo;
  _Statement.getStatementInfo = getStatementInfo;
  compiler.Statement = _Statement;
}