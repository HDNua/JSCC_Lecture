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

/**
  HandyFileSystem 싱글톤 객체를 생성하고 초기화합니다.
*/
function initHandyFileSystem() {
  
  // HandyFileSystem 싱글톤 객체를 정의합니다.
  // 빈 객체를 먼저 생성함에 주의합니다.
  var hfs = {};
  
  // 파일 시스템 객체를 획득합니다.
  var fso = require('fs');
  
  // 현재 작업중인 파일의 디렉터리를 획득합니다.
  var gui = require('nw.gui');
  var dir = gui.App.argv[0];
  
  /**
  // 파일에 기록된 텍스트를 모두 불러와 문자열로 반환합니다.
  // 성공하면 획득한 문자열, 실패하면 null을 반환합니다.
  @param {string} filename
  @return {string}
  */
  function load(filename) {
    try {
      var filepath = this.dir + '\\' + filename;
      return this.fso.readFileSync(filepath);
    } catch (ex) {
      return null;
    }
  }
  /**
  // 파일에 텍스트를 기록합니다.
  // 기록에 성공하면 true, 실패하면 false를 반환합니다.
  @param {string} filename
  @return {Boolean}
  */
  function save(filename, data) {
    try {
      var filepath = this.dir + '\\' + filename;
      this.fso.writeFileSync(filepath, data);
      return true;
    } catch (ex) {
      return false;
    }
  }
  /**
  // 파일이 디스크에 존재하는지 확인합니다.
  @param {string} filepath
  @return {Boolean}
  */
  function exists(filepath) {
    return this.fso.exists(filepath);
  }
  
  // 정의한 속성을 HandyFileSystem 싱글톤 객체의 멤버로 정의합니다.
  hfs.fso = fso;
  hfs.dir = dir;
  hfs.load = load;
  hfs.save = save;
  hfs.exists = exists;
  
  // 전역 객체를 의미하는 window 객체에 HandyFileSystem 속성을 추가하고
  // 생성한 HandyFileSystem 싱글톤 객체를 대입합니다.
  window['HandyFileSystem'] = hfs;
}