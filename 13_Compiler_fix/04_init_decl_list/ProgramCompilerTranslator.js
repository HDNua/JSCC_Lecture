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
    log('sc_spec: %s', declspcf.storageClassSpecifier);
    log('type_spec: %s', declspcf.typeSpecifier);
    log('type_qlif: %s', declspcf.typeQualifier);
    log();

    // 초기 선언자 리스트를 획득하고 정보를 출력합니다.
    var init_decl_list = Declaration.getInitDeclaratorList(buffer);
    
    // 토큰을 구분하기 위해 추가한 세미콜론을 생략합니다.
    buffer.get_ctoken();
  }
  /**
  함수 정의를 획득하고 어셈블리 언어로의 변환을 수행합니다.
  @param {StringBuffer} buffer
  */
  function functionDefinition(buffer) {
    buffer.get_ctoken();
  }
  
  // 등록
  translator.translate = translate;
  compiler.Translator = translator;
}