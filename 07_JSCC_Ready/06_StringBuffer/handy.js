/**
  @param {string} msg
  @param {object} data
*/
function Exception(msg, data) {
  this.description = msg;
  this.data = (data != undefined) ? data : null;
}
Exception.prototype.toString = function() {
  var type = 'Exception: ';
  var message = this.description;
  var data = (this.data != undefined) ? this.data.toString() : '';
  return type + message + ' [' + data + ']';
}

/**
  로그 스트림에 문자열을 출력합니다.
  @param {string} message
*/
function log(message) {
  var logStream = document.getElementById('HandyLogStream');
  logStream.value += (message + '\n');
}

/**
  value가 undefined라면 기본 값을, 아니면 그대로 반환합니다.
*/
function getValid(value, defaultValue) {
  return (value != undefined) ? value : defaultValue;
}