/**
어셈블리 실행기 모듈 Runner를 초기화합니다.
*/
function initRunner() {
  var runner = {}; // 싱글톤 객체 생성
  
  // 속성 정의 이전에 정의해야 하는 내용 작성
  /**
  Runner 모듈의 메서드를 수행할 때 발생하는 예외를 정의합니다.
  @param {string} msg
  */
  function RunnerException(msg, data) {
    this.description = msg;
    this.data = data;
  }
  RunnerException.prototype = new Exception();
  RunnerException.prototype.toString = function() {
    return 'Runner' + Exception.prototype.toString.call(this);
  };
  
  // 필드 및 메서드 정의
  /**
  지정한 파일을 실행합니다.
  @param {string} filename
  */
  function run(filename) {
    
    // 파일로부터 텍스트를 획득합니다.
    var code = HandyFileSystem.load(filename);
    if (code == null) // 텍스트를 획득하지 못한 경우 예외를 발생합니다.
      throw new RunnerException("Cannot load file", filename);
    
    // 코드를 더 작성하기 전에 일단 동작하는지 확인합니다.
    log(code);
  }
  
  // 속성 등록
  runner.run = run;
  // 전역에 등록
  window.RunnerException = RunnerException;
  window.Runner = runner;
}