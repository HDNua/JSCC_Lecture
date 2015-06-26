/* StringBuffer.js */

/**
  StringBuffer 생성자 함수를 정의합니다.
  @param {string} s
*/
function StringBuffer(s) {
  this.str = (s != undefined) ? s : '';
  this.idx = 0;
}

/**
  버퍼를 문자열로 초기화합니다.
  @param {string} s
*/
StringBuffer.prototype.init = function(s) {
  this.str = (s != undefined) ? s : '';
  this.idx = 0;
};

/**
  버퍼로부터 문자를 하나 읽습니다. 포인터가 이동합니다.
  @return {string}
*/
StringBuffer.prototype.getc = function() {
  // 필드에 접근하기 위해 this 키워드를 반드시 붙여야 합니다.
  if (this.idx >= this.str.length)
    
    // throw와 StringBufferException 사이에 new가 붙었습니다.
    throw new StringBufferException('Buffer is empty', this);
  
  // 사실 StringBufferException의 두 번째 인자로 this도 넘겼습니다.
  return this.str[this.idx++];
}
/**
  버퍼의 포인터가 가리키는 문자를 가져옵니다. 포인터는 이동하지 않습니다.
  @return {string}
*/
StringBuffer.prototype.peekc = function() {
  if (this.idx >= this.str.length)
    throw new StringBufferException('Buffer is empty', this);
  return this.str[this.idx];
}
/**
  버퍼에서 읽었던 값을 되돌립니다. 되돌릴 수 없으면 false를 반환합니다.
  @return {boolean}
*/
StringBuffer.prototype.ungetc = function() {
  if (this.idx > 0) {
    --this.idx;
    return true;
  }
  return false;
}

/**
  버퍼의 끝에 문자열을 추가합니다.
  @param {string} s
*/
StringBuffer.prototype.add = function(s) {
  this.str += s;
}

/**
  버퍼가 비어있다면 true, 값을 더 읽을 수 있다면 false를 반환합니다.
  @return {boolean}
*/
StringBuffer.prototype.is_empty = function() {
  return (this.idx >= this.str.length);
}

/**
  버퍼로부터 정수를 획득합니다.
  @return {string}
*/
StringBuffer.prototype.get_number = function() {
  this.trim(); // 공백 제거
  if (this.is_empty()) // 버퍼에 남은 문자가 없다면 예외
    throw new StringBufferException("Buffer is empty", this);
  else if (is_digit(this.str[this.idx]) == false) // 첫 문자가 숫자가 아니면 예외
    throw new StringBufferException("invalid number", this);
  var value = '';
  while (this.is_empty() == false) {
    if (is_digit(this.str[this.idx]) == false)
      break;
    value += this.str[this.idx];
    ++this.idx;
  }
  return value;
}

/**
  버퍼로부터 식별자를 획득합니다.
  @return {string}
*/
StringBuffer.prototype.get_identifier = function() {
  this.trim(); // 공백 제거
  if (this.is_empty()) // 버퍼에 남은 문자가 없다면 예외
    throw new StringBufferException("Buffer is empty", this);
  else if (is_fnamch(this.str[this.idx]) == false)
    throw new StringBufferException("invalid identifier", this);
  var identifier = '';
  while (this.is_empty() == false) {
    if (is_namch(this.str[this.idx]) == false) // 식별자 문자가 아니라면 탈출
      break;
    identifier += this.str[this.idx];
    ++this.idx;
  }
  return identifier;
}

/**
  버퍼로부터 C 연산자를 획득합니다.
  @return {string}
*/
StringBuffer.prototype.get_operator = function() {
  this.trim();
  if (this.is_empty())
    throw new StringBufferException("Buffer is empty", this);
  var ch = this.str[this.idx++]; // 현재 문자를 획득하고 포인터를 이동한다
  var op = '';
  switch (ch) {
  case '+': op = ch; break;
  case '-': op = ch; break;
  case '*': op = ch; break;
  case '/': op = ch; break;
  default: throw new StringBufferException("invalid operator", this);
  }
  return op;
}

/**
  공백이 아닌 문자가 나올 때까지 포인터를 옮깁니다.
*/
StringBuffer.prototype.trim = function() {
    while (this.is_empty() == false) { // 버퍼에 문자가 남아있는 동안
        if (is_space(this.str[this.idx]) == false) // 공백이 아닌 문자를 발견하면
            break; // 반복문을 탈출한다
        ++this.idx; // 공백이면 다음 문자로 포인터를 넘긴다
    }
}

/**
  현재 위치 다음에 존재하는 토큰을 획득합니다.
  토큰 획득에 실패하면 null을 반환합니다.
  @return {string}
*/
StringBuffer.prototype.get_token = function() {
  try {
    this.trim();
    if (this.is_empty())
        throw new StringBufferException("Buffer is empty", this);
  
    var ch = this.str[this.idx];
    var ss = ''; // 문자열 스트림 생성
    if (is_digit(ch)) { // 정수를 발견했다면 정수 획득
        ss += this.get_number(); // cout 출력 스트림처럼 사용하면 된다
    }
    else if (is_fnamch(ch)) { // 식별자 문자를 발견했다면 식별자 획득
        ss += this.get_identifier();
    }
    else { // 이외의 경우 일단 획득
        ss += this.get_operator();
    }
    return ss; // 획득한 문자열을 반환한다
  } catch (ex) {
    // 토큰 획득에 실패한 경우 null을 반환합니다.
    return null;
  }
}

/**
StringBuffer의 예외 형식인 StringBufferException을 정의합니다.
@param {string} msg
@param {StringBuffer} data
*/
function StringBufferException(msg, data) {
  this.description = msg;
  this.data = data;
}

// JavaScript에는 문법적으로 상속 기능이 없기 때문에
// prototype 객체를 이용하여 상속을 흉내냅니다.
StringBufferException.prototype = new Exception();

// toString 메서드를 오버라이드 합니다.
StringBufferException.prototype.toString = function() {
  // 상위 객체의 메서드를 호출하고 반환된 문자열 앞에 'StringBuffer'를 붙입니다.
  return 'StringBuffer' + Exception.prototype.toString.call(this);
}
