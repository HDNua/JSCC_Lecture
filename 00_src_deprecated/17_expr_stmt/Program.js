/**
JSCC 및 그 테스트 모듈을 관리하는 Program을 생성합니다.
*/
function initProgram() {
  var program = {};
  initProgramStream(program);
  initProgramRunner(program);
  initProgramLinker(program);
  initProgramCompiler(program);
  // 등록
  window.Program = program;
}