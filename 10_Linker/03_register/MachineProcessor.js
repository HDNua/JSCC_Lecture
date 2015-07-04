/**
Low Level Assembly를 해석하고 실행하는 프로세서입니다.
*/
function initMachineProcessor(machine) {
  var processor = {};
  
  // 프로세서에 레지스터 모듈을 등록합니다.
  initMachineProcessorRegister(proc);
  
  // 필드 정의
  
  
  // 메서드 정의
  /**
  진입점을 기준으로 프로그램을 실행합니다.
  @param {number} entrypoint
  */
  function run(entrypoint) {
    
  }
  
  // 등록
  processor.run = run;
  machine.Processor = processor;
}

function initMachineProcessorRegister(processor) {
  // Register 모듈을 정의합니다.
  var register = {};

  // 32비트 레지스터 목록입니다.
  var _reg32 = {
    eax: true, ebx: true, ecx: true, edx: true,
    ebp: true, esp: true, eip: true, eflags: true
  };
  // 16비트 레지스터 목록입니다.
  var _reg16 = {
    ax: true, bx: true, cx: true, dx: true,
    ds: true, ss: true, cs: true, es: true
  };
  // 8비트 레지스터 목록입니다.
  var _reg8 = {
    ah: true, al: true, bh: true, bl: true,
    ch: true, cl: true, dh: true, dl: true
  };
  
  /**
  주어진 인자가 레지스터라면 true를, 아니면 false를 반환합니다.
  @param {string} param
  @return {boolean}
  */
  function is_register(param) {
    return (is_reg32(param) || is_reg16(param) || is_reg8(param));
  }
  /**
  주어진 인자가 32비트 레지스터라면 true를, 아니면 false를 반환합니다.
  @param {string} param
  @return {boolean}
  */
  function is_reg32(param) {
    return Machine.Processor.Register._reg32[param] ? true : false;
  }
  /**
  주어진 인자가 16비트 레지스터라면 true를, 아니면 false를 반환합니다.
  @param {string} param
  @return {boolean}
  */
  function is_reg16(param) {
    return Machine.Processor.Register._reg16[param] ? true : false;
  }
  /**
  주어진 인자가 8비트 레지스터라면 true를, 아니면 false를 반환합니다.
  @param {string} param
  @return {boolean}
  */
  function is_reg8(param) {
    return Machine.Processor.Register._reg8[param] ? true : false;
  }
  
  // 등록
  register.is_register = is_register;
  register.is_reg32 = is_reg32;
  register.is_reg16 = is_reg16;
  register.is_reg8 = is_reg8;
  register._reg32 = _reg32;
  register._reg16 = _reg16;
  register._reg8 = _reg8;
  processor.Register = register;
}