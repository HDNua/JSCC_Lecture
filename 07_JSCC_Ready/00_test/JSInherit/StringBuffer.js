/* StringBuffer.js */

function StringBufferException(msg, data) {
  this.description = msg;
  this.data = data;
}
StringBufferException.prototype = new Exception();
StringBufferException.prototype.toString = function() {
  return 'StringBuffer' + Exception.prototype.toString.call(this);
}

/**
  StringBuffer 클래스를 정의합니다.
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
  if (this.idx >= this.str.length)
    throw StringBufferException('Buffer is empty');
  return this.str[this.idx++];
}
/**
  버퍼의 포인터가 가리키는 문자를 가져옵니다. 포인터는 이동하지 않습니다.
  @return {string}
*/
StringBuffer.prototype.peekc = function() {
  if (this.idx >= this.str.length)
    throw StringBufferException('Buffer is empty');
  return this.str[this.idx];
}
/**
  버퍼에서 읽었던 값을 되돌립니다. 되돌릴 수 없으면 false를 반환합니다.
  @return {boolean}
*/
StringBuffer.prototype.ungetc = function() {
  
}

/**
  버퍼의 끝에 문자열을 추가합니다.
  @param {string} s
*/
StringBuffer.prototype.add = function(s) {
  
}

/**
  버퍼가 비어있다면 true, 값을 더 읽을 수 있다면 false를 반환합니다.
  @return {boolean}
*/
StringBuffer.prototype.is_empty = function() {
  
}

/**
  버퍼로부터 정수를 획득합니다.
  @return {string}
*/
StringBuffer.prototype.get_number = function() {
  
}

/**
  버퍼로부터 식별자를 획득합니다.
  @return {string}
*/
StringBuffer.prototype.get_identifier = function() {
  
}

/**
  버퍼로부터 C 연산자를 획득합니다.
  @return {string}
*/
StringBuffer.prototype.get_operator = function() {
  
}

/**
  공백이 아닌 문자가 나올 때까지 포인터를 옮깁니다.
*/
StringBuffer.prototype.trim = function() {
  
}

/**
  현재 위치 다음에 존재하는 토큰을 획득합니다.
  @return {string}
*/
StringBuffer.prototype.get_number = function() {
  
}