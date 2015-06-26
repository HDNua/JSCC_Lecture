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
  
  // 싱글톤에 속성 등록
  memory.read_byte = read_byte;
  memory.write_byte = write_byte;
  memory.get_byte = get_byte;
  memory.set_byte = set_byte;
  
  // 전역에 싱글톤 등록
  window.Memory = memory;
}