/**
니모닉에 대한 핸들러를 정의하는 Operate 객체를 생성합니다.
*/
function initOperate() {
  var operate = {};
  
  function mov(left, right) {
    if (Register.is_register(right) == true) { // 레지스터라면
      // 해당 레지스터의 값을 대입합니다.
      Register[left] = Register[right];
    }
    /* 후에 else if (is_memory(right))로 작성하여 메모리에도 대응할 수 있다 */
    else { // 레지스터가 아니라면
      // 정수로 간주하고, 정수로 변환하여 대입합니다.
      Register[left] = parseInt(right);
    }
  }
  function jmp(left) {
    var dest_addr = 0; // 점프할 목적지입니다.

    // 레지스터라면 해당 레지스터의 값으로 점프합니다.
    if (Register.is_register(left))
      dest_addr = Register[left];
    // 정수라면 해당 정수 값으로 점프합니다.
    else
      dest_addr = parseInt(left, 16);

    // 획득한 목적지로 바이트 포인터를 옮깁니다.
    Memory.bytePtr = dest_addr;
  }
  function push(left) {
    // esp의 값이 4만큼 줄었다.
    Register.esp -= 4;

    // esp가 가리키는 위치의 메모리에서 4바이트만큼을 ebp로 채웠다.
    Memory.set_dword(Register.ebp, Register.esp);
  }
  function pop(left) {
    // esp가 가리키는 메모리의 dword 값을 획득합니다.
    var popVal = Memory.get_dword(Register.esp);

    // esp를 레지스터 크기만큼 증가시킵니다.
    Register.esp += 4;

    // 목적지 레지스터에 획득한 값을 대입합니다.
    Register[left] = popVal;
  }
  
  operate.mov = mov;
  operate.jmp = jmp;
  
  operate.push = push;
  operate.pop = pop;
  
  window.Operate = operate;
}