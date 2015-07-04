/**
실행 가능한 목적 파일을 생성합니다.
*/
function initProgramLinker(program) {
  var linker = {};
  
  // 필드 정의
  
  
  // 메서드 정의
  /**
  파일 시스템으로부터 목적 파일을 불러옵니다.
  @param {string} filename
  */
  function load(filename) {
    
  }
  /**
  불러온 목적 파일을 링크합니다.
  @param {string} output
  */
  function link(filename) {
    
    
  }
  
  linker.load = load;
  linker.link = link;
  program.Linker = linker;
}