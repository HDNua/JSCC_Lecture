/**
레지스터 관리 모듈 Register를 초기화합니다.
*/
function initRegister() {
  var register = {}; // 싱글톤 객체 생성
  
  // 필드를 정의합니다.
  register.eax = 0;
  register.ebx = 0;
  register.ecx = 0;
  register.edx = 0;
  register.ebp = Memory.MaxSize();
  register.esp = Memory.MaxSize();
  register.eip = 4;
  
  // 메서드를 정의합니다.
  /**
  레지스터라면 true를, 아니라면 false를 반환합니다.
  @return {boolean}
  */
  function is_register(param) {
    return (param == 'eax'
           || param == 'ebx'
           || param == 'ecx'
           || param == 'edx'
           || param == 'ebp'
           || param == 'esp'
           || param == 'eip');
  }
  
  // 메서드를 등록합니다.
  register.is_register = is_register;
  
  // 전역에 등록
  window.Register = register; 
}