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
    
    // 획득한 텍스트를 줄 단위로 나눈 배열을 획득합니다.
    var lines = String(code).split(NEWLINE);
    
    // 얻은 텍스트 줄 배열을 분석합니다.
    var segment = null;
    for (var i=0, len=lines.length; i<len; ++i) {
      // 줄 텍스트를 참조합니다.
      var line = lines[i];
      
      // 줄의 마지막 문자가 개행 문자라면 제거합니다.
      if (line.charAt(line.length - 1) == '\r')
        line = line.substr(0, line.length - 1);
      
      // 빈 줄이라면 무시합니다.
      if (line == '')
        continue;
      // 첫 문자가 세미콜론(;)이라면 주석이므로 무시합니다.
      else if (line.charAt(0) == ';')
        continue;
      // 첫 문자가 점(.)이라면 세그먼트로 간주합니다.
      else if (line.charAt(0) == '.') {
        log('segment found: [' + line + ']');
        segment = line; // 세그먼트를 보관합니다.
      }
      // 끝 문자가 콜론(:)이라면 레이블로 간주합니다.
      else if (line.charAt(line.length-1) == ':') {
        // 세그먼트가 정의되지 않았는데 텍스트가 먼저 발견되었다면 예외 처리합니다.
        if (segment == null)
          throw new RunnerException("segment is null", {
              lineNumber: i,
              lineString: line
          });
        log('label: ' + line);
      }
      // 코드를 분석합니다.
      else {
        
        // StringBuffer 객체를 생성합니다.
        var buffer = new StringBuffer(line);
        
        // 맨 처음 획득하는 토큰은 무조건 니모닉입니다.
        // (거기다 무조건 식별자여야 합니다.)
        var mne = buffer.get_identifier();
        
        // 식별자를 획득하지 못했다면 예외를 발생합니다.
        if (mne == null)
          // 예외에 대한 정보를 담는 객체를 생성하고 같이 전달합니다.
          throw new RunnerException('first word is not mnemonic', {
            lineNumber: i,      // 오류가 발생한 줄 번호
            lineString: line,   // 오류가 발생한 줄 텍스트
          });
        
        // 다음 토큰을 획득합니다.
        var left = buffer.get_token();
        
        // 다음 토큰이 없다면 단어가 한 개 존재하는 것이므로 획득이 끝납니다.
        if (left == null) {
          log('mnemonic: [' + mne + ']');
          continue;
        }
        
        // 획득한 다음 토큰이 식별자인 경우의 처리입니다.
        var operand_type = null;
        if (is_fnamch(String(left).charAt(0)) == true) {
          operand_type = 'identifier';
        }
        // 획득한 토큰이 숫자인 경우의 처리입니다.
        else if (is_digit(String(left).charAt(0)) == true) {
          operand_type = 'number';
        }
        // 이외의 경우 일단 예외 처리합니다.
        else {
          throw new RunnerException('invalid left operand', {
            lineNumber: i,
            lineString: line,
            operand: left
          });
        }
        
        // 다음 토큰을 획득합니다. 문법적으로 다음 토큰은 반점(,)이어야 합니다.
        var right = buffer.get_token();
        log(right);

        // 다음 토큰이 없다면 분석이 끝납니다.
        if (right == null) {
          log('mnemonic ' + operand_type + ': [' + mne + ' ' + left + ']');
          continue;
        }
        
        // 다음 토큰이 있는 경우의 처리입니다.
        // ...
      }
    }
    log('analyzing complete'); // 분석에 성공한 경우 출력되는 문장입니다.
  }
  
  // 속성 등록
  runner.run = run;
  // 전역에 등록
  window.RunnerException = RunnerException;
  window.Runner = runner;
}