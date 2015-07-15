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
    
    log('translation complete');
  }
  
  // 등록
  translator.translate = translate;
  compiler.Translator = translator;
}