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
  메모리로부터 명령 코드를 가져와 문자열로 반환합니다.
  @return {string}
  */
  function fetch() {
    var opcode = ''; // 획득할 명령 코드를 보관합니다.
    var MEMORY_END = Memory.MaxSize() - 1; // 메모리의 끝입니다.
    
    // 메모리의 끝이 나타나기 전까지 분석합니다.
    while (Memory.bytePtr <= MEMORY_END) {
      // 현재 바이트 포인터가 가리키는 바이트를 획득합니다.
      var byte = Memory.read_byte();
      if (byte == 0) // 널을 획득했다면 명령 코드 획득을 끝냅니다.
        break;
      
      // 획득한 바이트 코드에 해당하는 문자를 덧붙입니다.
      opcode += String.fromCharCode(byte);
    }
    
    // 획득한 명령 코드를 반환합니다.
    return opcode;
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
    if (mne == 'push') { // push 니모닉에 대한 처리
      if (left == null) // 피연산자가 없으면 예외 처리합니다.
        throw new RunnerException('invalid operand');
      
      // esp의 값이 4만큼 줄었다.
      Register.esp -= 4;
      
      // esp가 가리키는 위치의 메모리에서 4바이트만큼을 ebp로 채웠다.
      Memory.set_dword(Register.ebp, Register.esp);
    }
    else if (mne == 'mov') { // mov 니모닉에 대한 처리
      // right의 레지스터 값을 left에 대입합니다.
      Register[left] = Register[right];
    }
    else if (mne == 'pop') { // pop 니모닉에 대한 처리
      
      // esp가 가리키는 메모리의 dword 값을 획득합니다.
      var popVal = Memory.get_dword(Register.esp);
      
      // esp를 레지스터 크기만큼 증가시킵니다.
      Register.esp += 4;
      
      // 목적지 레지스터에 획득한 값을 대입합니다.
      Register[left] = popVal;
    }
    else if (mne == 'ret') { // ret 니모닉에 대한 처리
      /* ... */
    }
  }
  
  /**
  지정한 파일을 불러와 메모리에 올립니다.
  @param {string} filename
  */
  function load(filename) {
    // 파일로부터 텍스트를 획득합니다.
    var code = HandyFileSystem.load(filename);
    if (code == null) // 텍스트를 획득하지 못한 경우 예외를 발생합니다.
      throw new RunnerException('Cannot load file', filename);

    // 획득한 텍스트를 줄 단위로 나눈 배열을 획득합니다.
    var lines = String(code).split(NEWLINE);

    // 코드를 메모리에 기록하기 위해 바이트 포인터를 맞춥니다.
    Memory.bytePtr = 4;

    // 획득한 텍스트를 메모리에 기록합니다.
    var segment = null;
    for (var i=0, len=lines.length; i<len; ++i) {
      try {
        // i번째 줄에서 양 옆 공백이 제거된 문자열을 가져옵니다.
        var line = lines[i].trim();

        // 지시어 및 예외적 상황을 처리합니다.
        if (line == '') continue; // 빈 줄은 넘어갑니다.
        else if (line.charAt(0) == ';') continue; // 주석은 넘어갑니다.
        else if (line.charAt(0) == '.') { // 세그먼트를 처리합니다.
          // 세그먼트 정보를 보관합니다.
          // 이후에 나타나는 코드의 영역을 결정하기 위해 사용합니다.
          segment = line;
          continue;
        }

        // 코드를 메모리에 올립니다.
        if (segment == null) // 세그먼트가 정의되지 않았다면 예외 처리합니다.
          throw new RunnerException("segment is null");
        for (var j=0, lineLen=line.length; j<lineLen; ++j)
          Memory.write_byte(line.charCodeAt(j));

        // 명령을 구분하기 위해 널 문자를 삽입합니다.
        Memory.write_byte(0);

      } catch (ex) {
        if (ex instanceof RunnerException) {
          log('Runner.load: ');
          log(i + ': [' + lines[i] + '] ' + ex.description);
        }
        else {
          throw ex;
        }
      }
    }

    log('load complete');
  }
  
  /**
  분석한 프로그램을 실행합니다.
  */
  function run() {
    // 코드 영역의 시작 지점으로 바이트 포인터를 옮깁니다.
    Memory.bytePtr = 4;
    
    while (true) {
      // 메모리로부터 명령 코드를 획득합니다.
      var opcode = fetch();
      if (opcode == 'exit') // 명령 코드가 exit이면 프로그램을 종료합니다.
        break;
      
      // fetch를 통해 가져온 정보를 분석합니다.
      var info = decode(opcode);

      // decode를 통해 분석된 정보를 바탕으로 명령을 실행합니다.
      execute(info);

      // 식을 분석하고 실행한 결과를 스트림에 출력합니다.
      Runner.exp_write(opcode);
      Runner.reg_write('eax = %08x, ebx = %08x, ecx = %08x, edx = %08x',
                      Register.eax, Register.ebx, Register.ecx, Register.edx);
      Runner.reg_write('ebp = %02x, esp = %02x', Register.ebp, Register.esp);
    }
    log('run complete');
  }
  
  /**
  메모리 스트림에 문자열을 출력합니다.
  @param {string} fmt
  */
  function mem_write(fmt) {
    var result; // 로그 스트림에 출력할 문자열을 보관합니다.
    var args = mem_write.arguments;
    if (args.length == 0) { // 인자의 수가 0이라면
      result = ''; // 개행만 합니다.
    }
    else if (args.length > 1) { // 인자의 수가 1보다 크면 format을 호출합니다.
      var params = Handy.toArray(args, 1); // 인자 목록 배열을 획득합니다.
      result = Handy.vformat(fmt, params); // 형식 문자열과 인자 목록을 같이 넘깁니다.
    }
    else { // 인자의 수가 1이면 그냥 출력합니다.
      result = fmt;
    }
    // 스트림에 출력합니다.
    var stream = document.getElementById('memoryStream');
    stream.value += (result + NEWLINE);
  }
  /**
    출력 스트림에 문자열을 출력합니다.
    @param {string} fmt
  */
  function out_write(fmt) {
    var result; // 로그 스트림에 출력할 문자열을 보관합니다.
    var args = out_write.arguments;
    if (args.length == 0) { // 인자의 수가 0이라면
      result = ''; // 개행만 합니다.
    }
    else if (args.length > 1) { // 인자의 수가 1보다 크면 format을 호출합니다.
      var params = Handy.toArray(args, 1); // 인자 목록 배열을 획득합니다.
      result = Handy.vformat(fmt, params); // 형식 문자열과 인자 목록을 같이 넘깁니다.
    }
    else { // 인자의 수가 1이면 그냥 출력합니다.
      result = fmt;
    }
    // 스트림에 출력합니다.
    var stream = document.getElementById('outputStream');
    stream.value += (result + NEWLINE);
  }
  /**
    레지스터 스트림에 문자열을 출력합니다.
    @param {string} fmt
  */
  function reg_write(fmt) {
    var result; // 로그 스트림에 출력할 문자열을 보관합니다.
    var args = reg_write.arguments;
    if (args.length == 0) { // 인자의 수가 0이라면
      result = ''; // 개행만 합니다.
    }
    else if (args.length > 1) { // 인자의 수가 1보다 크면 format을 호출합니다.
      var params = Handy.toArray(args, 1); // 인자 목록 배열을 획득합니다.
      result = Handy.vformat(fmt, params); // 형식 문자열과 인자 목록을 같이 넘깁니다.
    }
    else { // 인자의 수가 1이면 그냥 출력합니다.
      result = fmt;
    }
    // 스트림에 출력합니다.
    var stream = document.getElementById('registerStream');
    stream.value += (result + NEWLINE);
  }
  /**
    식 스트림에 문자열을 출력합니다.
    @param {string} fmt
  */
  function exp_write(fmt) {
    var result; // 로그 스트림에 출력할 문자열을 보관합니다.
    var args = exp_write.arguments;
    if (args.length == 0) { // 인자의 수가 0이라면
      result = ''; // 개행만 합니다.
    }
    else if (args.length > 1) { // 인자의 수가 1보다 크면 format을 호출합니다.
      var params = Handy.toArray(args, 1); // 인자 목록 배열을 획득합니다.
      result = Handy.vformat(fmt, params); // 형식 문자열과 인자 목록을 같이 넘깁니다.
    }
    else { // 인자의 수가 1이면 그냥 출력합니다.
      result = fmt;
    }
    // 스트림에 출력합니다.
    var stream = document.getElementById('expressionStream');
    stream.value += (result + NEWLINE);
  }
  
  // 속성 등록
  runner.load = load;
  runner.run = run;
  
  runner.mem_write = mem_write;
  runner.out_write = out_write;
  runner.reg_write = reg_write;
  runner.exp_write = exp_write;
  
  // 전역에 등록
  window.RunnerException = RunnerException;
  window.Runner = runner;
}