/**
Machine에 프로그램 실행을 요청합니다.
*/
function initProgramRunner(program) {
  var runner = {};
  
  function load(filename) { }
  function run() { }
  
  runner.load = load;
  runner.run = run;
  program.Runner = runner;
}