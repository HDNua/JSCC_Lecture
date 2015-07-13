/**
C 프로그래밍 언어 컴파일러입니다.
*/
function initProgramCompiler(program) {
  var compiler = {};
  
  // 속성 정의 이전에 정의해야 하는 내용 작성
  /**
  Compiler 모듈의 메서드를 수행할 때 발생하는 예외를 정의합니다.
  @param {string} msg
  */
  function CompilerException(msg, data) {
    this.description = msg;
    this.data = data;
  }
  CompilerException.prototype = new Exception();
  CompilerException.prototype.toString = function() {
    return 'Compiler' + Exception.prototype.toString.call(this);
  };
  
  /**
  C언어로 작성된 파일을 목적 파일로 변환합니다.
  @param {string} filename
  */
  function compile(filename) {
    // 파일 텍스트를 가져옵니다. 실패하면 예외 처리합니다.
    var filedata = HandyFileSystem.load(filename);
    if (filedata == null)
      throw new CompilerException('cannot open file ', filename);
    
    // 가져온 텍스트를 바탕으로 새 StringBuffer 인스턴스를 생성합니다.
    var buffer = new StringBuffer(filedata);
    
    
    // 컴파일이 성공했음을 알립니다.
    log('Compiler: compile complete');
    return 0; // 반환하는 값이 0이 아니면 프로그램을 중단합니다.    
  }
  
  compiler.compile = compile;
  program.Compiler = compiler;
}