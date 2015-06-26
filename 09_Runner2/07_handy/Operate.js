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
  
  function jnz(left) {
    // 0이 아니면, 즉 영 플래그가 1이 아니면 점프합니다.
    if (Register.getZF() != 1)
      jmp(left);
  }
  function cmp(left, right) {
    if (Register.is_register(left)) { // left가 레지스터라면
      var same; // 두 값이 같은지를 보관하는 변수입니다.
      
      if (Register.is_register(right)) { // right 또한 레지스터라면 둘을 비교합니다.
        // 두 값의 차이가 0인지 확인합니다. 0이라면 true, 아니면 false입니다.
        same = ((Register[left] - Register[right]) == 0);
      }
      else { // right가 즉시 값이라면 둘을 비교합니다.
        same = ((Register[left] - right) == 0);
      }

      // 두 값이 같은지에 대한 결과를 반영합니다. 같다면 1, 아니면 0입니다.
      var value = same ? 1 : 0;
      Register.setZF(value);
    }
  }
  
  function print_number(left) {
    var value;
    
    // 레지스터라면 레지스터의 값을 얻는다.
    if (Register.is_register(left)) {
      value = Register[left];
    }
    // 레지스터가 아니라면 인자를 정수로 변환한다.
    else {
      value = parseInt(left);
    }
    
    // 획득한 값을 출력한다.
    Runner.out_write(value);
  }
  function print_letter(left) {
    var value;
    
    // 레지스터라면 레지스터의 값을 얻는다.
    if (Register.is_register(left)) {
      value = Register[left];
    }
    // 레지스터가 아니라면 인자를 정수로 변환한다.
    else {
      value = parseInt(left);
    }
    
    // 획득한 값으로부터 문자를 획득하고 이를 출력한다.
    Runner.out_write(String.fromCharCode(value));
  }
  operate.print_number = print_number;
  operate.print_letter = print_letter;
  
  operate.mov = mov;
  operate.jmp = jmp;
  
  operate.push = push;
  operate.pop = pop;
  
  operate.jnz = jnz;
  operate.cmp = cmp;
  
  window.Operate = operate;
}