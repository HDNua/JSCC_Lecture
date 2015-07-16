/**
획득한 텍스트를 분석하고 어셈블리 언어로 번역하는 Translator 모듈을 초기화합니다.
*/
function initProgramCompilerTranslator(compiler, CompilerException) {
  var translator = {};
  
  // 필드 정의
  translator.segment = null;
  
  // 메서드 정의
  /**
  넘겨받은 코드 데이터를 분석하고 세그먼트 스트림에 번역 결과를 출력합니다.
  @param {string} filedata
  */
  function translate(filedata) {
    // 가져온 텍스트를 바탕으로 새 StringBuffer 인스턴스를 생성합니다.
    var buffer = new StringBuffer(String(filedata));
    
    // 세그먼트에 대한 문자열 스트림을 생성합니다.
    var dataseg = new Program.Stream.StringStream();
    var codeseg = new Program.Stream.StringStream();
    
    // 필드를 초기화합니다.
    Program.Compiler.Translator.segment = {
      data: dataseg, code: codeseg
    };
    
    // 번역 단위를 획득하고 어셈블리 언어로 번역합니다.
    translationUnit(buffer);
  }
  
  /**
  번역 단위를 획득하고 어셈블리 언어로의 변환을 수행합니다.
  @param {StringBuffer} buffer
  */
  function translationUnit(buffer) {
    buffer.trim(); // 다음 토큰까지의 공백을 모두 제거합니다.
    while (buffer.is_empty() == false) { // 번역 단위가 남아있다면
      externalDeclaration(buffer); // 외부 정의를 획득합니다.
      buffer.trim(); // 다음 토큰까지의 공백을 모두 제거합니다.
    }
  }
  
  /**
  현재 획득하려는 외부 정의가 함수 정의인지 판정합니다.
  함수 정의라면 true, 아니라면 false를 반환합니다.
  @param {StringBuffer} buffer
  @return {boolean}
  */
  function is_funcdef(buffer) {
    var Declaration = Program.Compiler.Declaration;

    // 토큰 획득 이전에 버퍼 포인터를 보관합니다.
    var originIndex = buffer.idx;

    // 선언 지정자 획득을 시도합니다.
    var declspec = Declaration.getDeclarationSpecifier(buffer);
    // 선언 지정자 획득에 실패하면 함수 정의로 간주합니다.
    if (declspec == null) {
      buffer.idx = originIndex; // 버퍼 포인터를 복구합니다.
      return true;
    }
    
    // 선언자 획득을 시도합니다.
    var declarator = Declaration.getDeclarator(buffer);
    // 선언자 획득에 실패하면 선언으로 간주합니다.
    if (declarator == null) {
      buffer.idx = originIndex; // 버퍼 포인터를 복구합니다.
      return false;
    }
    
    // 선언 획득을 시도합니다.
    var declInfo = Declaration.getDeclarationInfo(buffer);
    // 선언 획득에 성공하면 함수 정의로 간주합니다.
    if (declInfo != null) {
      buffer.idx = originIndex; // 버퍼 포인터를 복구합니다.
      return true;
    }

    buffer.trim(); // 버퍼 포인터를 다음 토큰의 시작 지점으로 옮깁니다.
    // 획득한 토큰이 여는 중괄호라면 함수 정의입니다.
    if (buffer.peekc() == '{') {
      buffer.idx = originIndex; // 버퍼 포인터를 복구합니다.
      return true;
    }
    // 그 외의 경우 함수 정의가 아닙니다.
    buffer.idx = originIndex; // 버퍼 포인터를 복구합니다.
    return false;
  }
  /**
  외부 정의를 획득하고 어셈블리 언어로의 변환을 수행합니다.
  @param {StringBuffer} buffer
  */
  function externalDeclaration(buffer) {
    if (is_funcdef(buffer)) // 함수 정의라면
      functionDefinition(buffer); // 함수 정의로 분석합니다.
    else // 함수 정의가 아니라면
      declaration(buffer); // 선언으로 간주하여 분석합니다.
  }
  /**
  선언을 획득하고 어셈블리 언어로의 변환을 수행합니다.
  @param {StringBuffer} buffer
  */
  function declaration(buffer) {
    var Declaration = Program.Compiler.Declaration;
    
    // 선언 지정자를 획득하고 정보를 출력합니다.
    var declspcf = Declaration.getDeclarationSpecifier(buffer);
    
    // 초기 선언자 리스트를 획득하고 정보를 출력합니다.
    var init_decl_list = Declaration.getInitDeclaratorList(buffer);
    for (var i=0, len=init_decl_list.length; i<len; ++i) {
      var initDeclarator = init_decl_list[i]; // 초기 선언자를 획득합니다.
      var decl = initDeclarator.declarator; // 선언자를 획득하고 출력합니다.
      log('%s: %s %s', decl.identifier, decl.descriptor, declspcf);
    }
    
    // 토큰을 구분하기 위해 추가한 세미콜론을 생략합니다.
    buffer.get_ctoken();
  }
  /**
  함수 정의를 획득하고 어셈블리 언어로의 변환을 수행합니다.
  @param {StringBuffer} buffer
  */
  function functionDefinition(buffer) {
    var Decl = Program.Compiler.Declaration;
    var Stmt = Program.Compiler.Statement;
    var segment = Program.Compiler.Translator.segment;
    var dataseg = segment.data;
    var codeseg = segment.code;
    
    // 선언 지정자 획득을 시도합니다.
    var declspec = Decl.getDeclarationSpecifier(buffer);
    
    // 선언자를 획득합니다.
    var declarator = Decl.getDeclarator(buffer);
    
    // 선언 리스트를 획득합니다.
    /* ... */
    
    // 복합문을 획득합니다.
    var compound = Stmt.getCompoundStatementInfo(buffer);
    
    // 프로시저를 시작합니다.
    var funcName = declarator.identifier;
    codeseg.writeln('global _%s', funcName);
    codeseg.writeln('_%s:', funcName);
    codeseg.writeln('push ebp');
    codeseg.writeln('mov ebp, esp');
    
    // 컴파일을 수행합니다.
    var decl_list = compound.declarationList;
    for (var i=0, len=decl_list.length; i<len; ++i) {
      var decl = decl_list[i];
      log(decl);
    }
    var stmt_list = compound.statementList;
    for (var i=0, len=stmt_list.length; i<len; ++i) {
      var stmt = stmt_list[i];
      log(stmt);
    }
    
    // 프로시저를 끝냅니다.
    codeseg.writeln('mov esp, ebp');
    codeseg.writeln('pop ebp');
    codeseg.writeln('ret');
  }
  
  // 등록
  translator.translate = translate;
  compiler.Translator = translator;
}