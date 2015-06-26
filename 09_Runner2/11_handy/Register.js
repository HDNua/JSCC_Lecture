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
  register.eflags = 0;
  
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
  
  const BIT_CF = 1,
        BIT_PF = 1 << 2,
        BIT_AF = 1 << 4,
        BIT_ZF = 1 << 6,
        BIT_SF = 1 << 7,
        BIT_OF = 1 << 11;

  function getCF() { return (this.eflags & BIT_CF) ? 1 : 0 };
  function setCF(value) {
    if (value == 0) { // 0으로 설정
      this.eflags &= (~BIT_CF);
    } else { // 1로 설정
      this.eflags |= BIT_CF;
    }
  }
  function getPF() { return (this.eflags & BIT_PF) ? 1 : 0 };
  function setPF(value) {
    if (value == 0) { // 0으로 설정
      this.eflags &= (~BIT_PF);
    } else { // 1로 설정
      this.eflags |= BIT_PF;
    }
  }
  function getAF() { return (this.eflags & BIT_AF) ? 1 : 0 };
  function setAF(value) {
    if (value == 0) { // 0으로 설정
      this.eflags &= (~BIT_AF);
    } else { // 1로 설정
      this.eflags |= BIT_AF;
    }
  }
  function getZF() { return (this.eflags & BIT_ZF) ? 1 : 0 };
  function setZF(value) {
    if (value == 0) { // 0으로 설정
      this.eflags &= (~BIT_ZF);
    } else { // 1로 설정
      this.eflags |= BIT_ZF;
    }
  }
  function getSF() { return (this.eflags & BIT_ZF) ? 1 : 0 };
  function setSF(value) {
    if (value == 0) { // 0으로 설정
      this.eflags &= (~BIT_SF);
    } else { // 1로 설정
      this.eflags |= BIT_SF;
    }
  }
  function getOF() { return (this.eflags & BIT_OF) ? 1 : 0 };
  function setOF(value) {
    if (value == 0) { // 0으로 설정
      this.eflags &= (~BIT_OF);
    } else { // 1로 설정
      this.eflags |= BIT_OF;
    }
  }
  
  // 메서드를 등록합니다.
  register.is_register = is_register;
  register.getCF = getCF;
  register.setCF = setCF;
  register.getPF = getPF;
  register.setPF = setPF;
  register.getAF = getAF;
  register.setAF = setAF;
  register.getZF = getZF;
  register.setZF = setZF;
  register.getSF = getSF;
  register.setSF = setSF;
  register.getOF = getOF;
  register.setOF = setOF;
  
  // 전역에 등록
  window.Register = register; 
}