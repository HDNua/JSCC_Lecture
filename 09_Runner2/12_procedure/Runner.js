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
    Operate[info.mnemonic](info.left, info.right);
  }
  
  /**
  레이블 정보를 표현하는 형식 LabelInfo를 정의합니다.
  @param {string} name
  */
  function LabelInfo(name) {
    this.name = name;
    this.address = 0;
    this.refered = [];
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
    var labelInfoDict = {}; // LabelInfo에 대한 딕셔너리 객체입니다.
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
        
        // 레이블에 대해 처리합니다.
        if (line.charAt(line.length-1) == ':') {
          // 레이블 이름을 획득합니다.
          var label = line.substr(0, line.length-1);
          
          // 레이블이 딕셔너리에 없는 경우 생성합니다.
          if (labelInfoDict[label] == undefined)
            labelInfoDict[label] = new LabelInfo(label);

          // 레이블 딕셔너리에 정보를 등록합니다.
          labelInfoDict[label].address = Memory.bytePtr;
          continue;
        }

        // 코드를 메모리에 올립니다.
        if (segment == null) // 세그먼트가 정의되지 않았다면 예외 처리합니다.
          throw new RunnerException("segment is null");
        
        /* 데이터 세그먼트는 나중에 처리합니다. */
        // 논리가 복잡해졌으므로 획득한 행을 분석합니다.
        var info = decode(line);
        
        // 메모리에 기록할 문자열을 생성합니다.
        var s = info.mnemonic; // 맨 처음은 니모닉입니다.
        if (info.left != null) { // 인자가 존재한다면
          s += ' '; // 분석할 수 있도록 니모닉과 간격을 만듭니다.
          
          // 레이블이라면 (맨 앞이 밑줄 기호라면)
          if (info.left.charAt(0) == '_') {
            
            // 참조 위치는 (현재 바이트 포인터 위치 + 니모닉의 길이 + 공백 한 칸)입니다.
            var refered_addr = Memory.bytePtr + s.length;
            s += '0x0000'; // 일단 0으로 대치합니다.
            
            var label = info.left; // 레이블 이름을 획득합니다.
            // 레이블이 딕셔너리에 등록되지 않았다면 등록합니다.
            if (labelInfoDict[label] == undefined)
              labelInfoDict[label] = new LabelInfo(label);
            
            // 참조하고 있는 위치를 보관합니다.
            labelInfoDict[label].refered.push(refered_addr);
            
          }
          // 레이블이 아니라면 그냥 피연산자로 취급합니다.
          else {
            s += info.left;
          }
          
          if (info.right != null) {
            s += ',';
            
            // 레이블이라면 (맨 앞이 밑줄 기호라면)
            if (info.right.charAt(0) == '_') {
              
              // 참조 위치는 (현재 바이트 포인터 위치 + 니모닉의 길이 + 공백 한 칸)입니다.
              var refered_addr = Memory.bytePtr + s.length;
              s += '0x0000'; // 일단 0으로 대치합니다.

              var label = info.right; // 레이블 이름을 획득합니다.
              // 레이블이 딕셔너리에 등록되지 않았다면 등록합니다.
              if (labelInfoDict[label] == undefined)
                labelInfoDict[label] = new LabelInfo(label);

              // 참조하고 있는 위치를 보관합니다.
              labelInfoDict[label].refered.push(refered_addr);
            }
            // 레이블이 아니라면 그냥 피연산자로 취급합니다.
            else {
              s += info.right;
            }
          }
        }
        
        // 생성한 문자열을 메모리에 올립니다.
        for (var j=0, slen=s.length; j<slen; ++j)
          Memory.write_byte(s.charCodeAt(j));
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
    
    // 모든 참조된 레이블을 정의로 대치합니다.
    // 실제로는 레이블의 정보를 로그 스트림에 출력해보기만 합니다.
    for (label in labelInfoDict) {
      // LabelInfo 정보를 가져옵니다.
      var info = labelInfoDict[label];
      
      // 레이블의 정보를 형식적으로 출력합니다.
      var s = Handy.format('%s: %04x [ ', info.name, info.address);
      var arr = info.refered;
      for (var i=0, len=arr.length; i<len; ++i)
        s += Handy.format('%04x ', arr[i]); // 16진수로 레이블 참조 위치를 출력합니다.
      
      // 획득한 문자열을 출력합니다.
      log(s + ']');
      
      // 참조된 레이블을 정의로 대치합니다.
      for (var i=0, len=arr.length; i<len; ++i) {
        // 대치해야 할 메모리 위치로 바이트 포인터를 이동합니다.
        Memory.bytePtr = arr[i];
        
        // 참조된 레이블의 정의를 16진수 문자열로 획득합니다.
        var refered_addr = Handy.format('0x%04x', info.address);
        
        // 해당 참조 위치에 정의 값을 덮어씌웁니다.
        for (var j=0, slen=refered_addr.length; j<slen; ++j)
          Memory.write_byte(refered_addr.charCodeAt(j));
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
      Stream.exp.writeln(opcode);
      Stream.reg.writeln('eax = %08x, ebx = %08x, ecx = %08x, edx = %08x',
                         Register.eax, Register.ebx, Register.ecx, Register.edx);
      Stream.reg.writeln('ebp = %02x, esp = %02x, eip = %08x, eflags = %08b',
                         Register.ebp, Register.esp, Register.eip, Register.eflags);
    }
    log('run complete');
  }
  
  // 속성 등록
  runner.load = load;
  runner.run = run;
  
  // 전역에 등록
  window.RunnerException = RunnerException;
  window.Runner = runner;
}