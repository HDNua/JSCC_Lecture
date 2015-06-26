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
  텍스트를 가져옵니다.
  @param {Array} lines
  @param {Number} lineNumber
  @return {string}
  */
  function fetch(lines, lineNumber) {
    var line = lines[lineNumber]; // 줄 번호에 해당하는 줄을 획득합니다.
    return line.trim(); // 양 끝에 공백을 없애 정리한 줄을 반환합니다.
  }
  
  /**
  코드를 분석합니다.
  @param {string} line
  @return {InstructionInfo}
  */
  function decode(line) {
    // StringBuffer 객체를 생성하고 line으로 초기화합니다.
    var buffer = new StringBuffer(line);
    
    // 가장 처음에 획득하는 단어는 반드시 니모닉입니다.
    var mne = buffer.get_token();
    // 니모닉 획득에 실패한 경우 예외 처리합니다.
    if (is_fnamch(mne) == false)
      throw new RunnerException('invalid mnemonic');
    
    // 다음 토큰 획득을 시도합니다.
    var left = buffer.get_token();
    var right = null;
    if (left != null) { // 다음 토큰이 있는 경우의 처리
      
      // 피연산자가 두 개인지 확인하기 위해 토큰 획득을 시도합니다.
      right = buffer.get_token();
      if (right != null) { // 다음 토큰이 있는 경우
        if (right != ',') // 반점이 아니라면 HASM 문법 위반입니다.
          throw new RunnerException
            ('syntax error; right operand must be after comma(,)');
        
        // 오른쪽 피연산자 획득
        right = buffer.get_token();
        if (right == null) // 획득 실패 시 문법을 위반한 것으로 간주합니다.
          throw new RunnerException
            ('syntax error; cannot find right operand');
      }
      
      // 다음 토큰이 없다면 right는 null이고
      // 그렇지 않으면 다음 토큰 문자열이 된다
    }
    
    // 획득한 코드 정보를 담는 객체를 생성하고 반환합니다.
    var info = { mnemonic: mne, left: left, right: right };
    return info;
  }
  
/**
분석된 코드를 실행합니다.
@param {InstructionInfo}
*/
function execute(info) {
  var mne = info.mnemonic, left = info.left, right = info.right;
  log('instruction: [' + mne + '][' + left + '][' + right + ']');
}
  
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
    var segment = null;
    var lines = String(code).split(NEWLINE);
    for (var i=0, len=lines.length; i<len; ++i) {
      try {
        // 분석할 i번째 줄을 가져옵니다.
        var line = fetch(lines, i);

        // Runner에 보내는 지시어(directive)를 처리합니다.
        if (line == '') continue; // 빈 줄이라면 무시합니다.
        else if (line.charAt(0) == ';') continue; // 주석을 무시합니다.
        else if (line.charAt(0) == '.') { // 세그먼트를 처리합니다.
          segment = line; // 세그먼트를 보관합니다.
          log('segment found: [' + line + ']');
          continue;
        }
        
        // 지시어가 아닌 일반 명령으로 확인되면 분석합니다.
        if (line.charAt(line.length-1) == ':') { // 레이블을 처리합니다.
          // 세그먼트가 정의되지 않았는데 텍스트가 먼저 발견되었다면 예외 처리합니다.
          if (segment == null) // 같이 넘기던 인자가 사라졌습니다!
            throw new RunnerException("segment is null");
          log('label: ' + line);
          continue; // 레이블은 처리가 끝나면 지나갑니다.
        }
        
        // fetch를 통해 가져온 정보를 분석합니다.
        var info = decode(line);
        
        // decode를 통해 분석된 정보를 바탕으로 명령을 실행합니다.
        execute(info);
      }
      catch (ex) {
        if (ex instanceof RunnerException) {
          log('RunnerException occurred');
          log(i + ': [' + lines[i] + '] ' + ex.description);
        }
        else {
          throw ex;
        }
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