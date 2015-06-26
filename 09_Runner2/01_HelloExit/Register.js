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
  
  // 전역에 등록
  window.Register = register; 
}