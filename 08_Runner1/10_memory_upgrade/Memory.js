/**
메모리 관리 모듈 Memory를 초기화합니다.
*/
function initMemory() {
  var memory = {}; // 싱글톤 객체 생성

  // 상수 정의
  var MAX_MEMORY_SIZ = 100;

  // 속성 정의 이전에 정의해야 하는 내용 작성
  /**
  Memory 모듈의 메서드를 수행할 때 발생하는 예외를 정의합니다.
  @param {string} msg
  */
  function MemoryException(msg, data) {
    this.description = msg;
    this.data = data;
  }
  MemoryException.prototype = new Exception();
  MemoryException.prototype.toString = function() {
    return 'Memory' + Exception.prototype.toString.call(this);
  };
  
  // 필드 정의
  memory.byteArr = new Array(MAX_MEMORY_SIZ); // 메모리 바이트 배열 정의
  memory.bytePtr = 0; // 메모리를 가리키는 바이트 포인터 정의
  
  /**
  바이트 배열에서 바이트를 획득합니다.
  @return {number}
  */
  function read_byte() {
    return this.byteArr[this.bytePtr++];
  }
  /**
  value를 바이트로 변환한 값을 기록합니다.
  @param {number} value
  */
  function write_byte(value) {
    this.byteArr[this.bytePtr++] = (value & 0xFF);
  }
  /**
  바이트 배열에서 index 주소에 있는 바이트를 획득합니다.
  @param {number} index
  @return {number}
  */
  function get_byte(index) {
    return this.byteArr[index];
  }
  /**
  value를 바이트로 변환한 값을 index 주소에 기록합니다.
  @param {number} value
  @param {number} index
  */
  function set_byte(value, index) {
    this.byteArr[index] = (value & 0xFF);
  }
  
  /**
  바이트 배열에서 워드를 획득합니다.
  @return {number}
  */
  function read_word() {
    var byte1 = this.read_byte(); // 첫 번째 바이트 XY을 획득합니다.
    var byte2 = this.read_byte(); // 두 번째 바이트 ZW를 획득합니다.
//    var word = ((byte2 << 8) | byte1); // 결과 값은 ZWXY입니다.
//    return word;
    return ((byte2 << 8) | byte1);
  }
  /**
  value를 워드로 변환한 값을 기록합니다.
  @param {number} value
  */
  function write_word(value) {
    this.write_byte(value & 0xFF);  // 첫 번째 바이트를 기록합니다.
    value >>= 8;                    // 다음에 기록할 바이트로 value 값을 옮깁니다.
    this.write_byte(value & 0xFF);  // 두 번째 바이트를 기록합니다.
  }
  /**
  바이트 배열에서 index 주소에 있는 워드를 획득합니다.
  @param {number} index
  @return {number}
  */
  function get_word(index) {
    var byte1 = this.get_byte(index); // 첫 번째 바이트를 획득합니다.
    var byte2 = this.get_byte(index+1); // 두 번째 바이트를 획득합니다.
    return ((byte2 << 8) | byte1); // 워드를 반환합니다.
  }
  /**
  value를 워드로 변환한 값을 index 주소에 기록합니다.
  @param {number} value
  @param {number} index
  */
  function set_word(value, index) {
    this.set_byte(value & 0xFF, index); // 첫 번째 바이트를 기록합니다.
    value >>= 8; // 다음에 기록할 바이트로 value 값을 옮깁니다.
    this.set_byte(value & 0xFF, index+1); // 두 번째 바이트를 기록합니다.
  }
  
  /**
  더블 워드를 획득합니다.
  @return {number}
  */
  function read_dword() {
    var byte1 = this.read_byte();
    var byte2 = this.read_byte();
    var byte3 = this.read_byte();
    var byte4 = this.read_byte();
    var dword = (
      (byte4 << 24)
      | (byte3 << 16)
      | (byte2 << 8)
      | byte1);
    return dword;
  }
  /**
  더블 워드를 기록합니다.
  @param {number} value
  */
  function write_dword(value) {
    this.write_byte(value); value >>= 8;
    this.write_byte(value); value >>= 8;
    this.write_byte(value); value >>= 8;
    this.write_byte(value);
  }
  /**
  index에서 더블 워드를 획득합니다.
  @param {number} index
  @return {number}
  */
  function get_dword(index) {
    var byte1 = this.get_byte(index);
    var byte2 = this.get_byte(index+1);
    var byte3 = this.get_byte(index+2);
    var byte4 = this.get_byte(index+3);
    var dword = (
      (byte4 << 24)
      | (byte3 << 16)
      | (byte2 << 8)
      | byte1);
    return dword;
  }
  /**
  index에 더블 워드를 기록합니다.
  @param {number} value
  @param {number} index
  */
  function set_dword(value, index) {
    this.set_byte(value, index); value >>= 8;
    this.set_byte(value, index+1); value >>= 8;
    this.set_byte(value, index+2); value >>= 8;
    this.set_byte(value, index+3);
  }
  
  // 싱글톤에 속성 등록
  memory.read_byte = read_byte;
  memory.write_byte = write_byte;
  memory.get_byte = get_byte;
  memory.set_byte = set_byte;
  memory.read_word = read_word;
  memory.write_word = write_word;
  memory.get_word = get_word;
  memory.set_word = set_word;
  memory.read_dword = read_dword;
  memory.write_dword = write_dword;
  memory.get_dword = get_dword;
  memory.set_dword = set_dword;
  
  // 전역에 싱글톤 등록
  window.Memory = memory;
}