/**
C의 선언을 분석합니다.
*/
function initProgramCompilerDeclaration(compiler, CompilerException) {
  var _Declaration = {};
  
  // 형식 정의
  /**
  선언 지정자 형식입니다.
  */
  function DeclarationSpecifier(sc_spec, type_spec, type_qlif) {
    this.storageClassSpecifier = sc_spec;
    this.typeSpecifier = type_spec;
    this.typeQualifier = type_qlif;
  }
  var StorageClassSpecifierDict = {
    auto: true, register: true, static: true, extern: true, typedef: true
  };
  var TypeQualifierDict = {
    const: true, volatile: true,
  };
  var TypeSpecifierDict = {
    void: true, char: true, short: true, int: true,
    long: true, float: true, double: true, signed: true,
    unsigned: true, struct: true, union: true, enum: true
  };
  
  // 메서드 정의
  /**
  선언 지정자를 획득합니다. 실패시 포인터를 복구하고 null을 반환합니다.
  @param {StringBuffer} buffer
  @return {DeclarationSpecifier}
  */
  function getDeclarationSpecifier(buffer) {
    // 선언 지정자 획득에 실패하면 획득 이전으로 포인터를 복구합니다.
    var originIndex = buffer.idx;
    try {
      // 토큰을 획득하기 직전의 인덱스를 보존합니다.
      var prevIndex = buffer.idx;
      // 선언 지정자 정보를 담을 변수입니다.
      var sc_spec = null, type_spec = [], type_qlif = [];
      
      // 선언 지정자 정보를 획득하는 반복문입니다.
      while (buffer.is_empty() == false) { // 버퍼가 비어있는 동안
        prevIndex = buffer.idx; // 토큰 획득 이전의 위치를 보존합니다.
        var token = buffer.get_ctoken(); // 토큰을 획득합니다.
        
        // 기억 형태 지정자 토큰인 경우에 대해 처리합니다.
        if (isStorageClassSpecifierToken(token)) {
          if (sc_spec != null) { // 기억 형태 지정자는 두 개 이상 지정될 수 없습니다.
            throw new CompilerException
              ('cannot declare object with 2 or more storage class specifiers');
          }
          // 획득한 기억 형태 지정자를 기억합니다.
          sc_spec = token;
        }
        // 형식 한정자 토큰인 경우에 대해 처리합니다.
        else if (isTypeQualifierToken(token)) {
          // 획득한 형식 한정자를 기억합니다.
          type_qlif.push(token);
        }
        // 형식 지정자 토큰인 경우에 대해 처리합니다.
        else if (isTypeSpecifierToken(token)) {
          // 획득한 형식 지정자를 기억합니다.
          type_spec.push(token);
        }
        // 그 외의 경우 선언 지정자가 아니므로 획득하면 안 됩니다.
        else {
          buffer.idx = prevIndex; // 토큰 위치를 복구합니다.
          break; // 선언 지정자 획득 반복문을 탈출합니다.
        }
      }
      
      // 획득한 정보를 바탕으로 선언 지정자 정보 객체를 생성합니다.
      var declspcf = new DeclarationSpecifier
        (sc_spec, type_spec, type_qlif);
      // 생성한 선언 지정자 정보 객체를 반환합니다.
      return declspcf;
      
    } catch (ex) {
      // 선언 지정자 획득에 실패했으므로 획득 이전으로 포인터를 복구합니다.
      buffer.idx = originIndex;
      return null;
    }
  }
  /**
  기억 형태 지정자 토큰이라면 true, 아니라면 false를 반환합니다.
  @param {string} token
  @return {boolean}
  */
  function isStorageClassSpecifierToken(token) {
    return (StorageClassSpecifierDict[token] != undefined);
  }
  /**
  형식 지정자 토큰이라면 true, 아니라면 false를 반환합니다.
  @param {string} token
  @return {boolean}
  */
  function isTypeSpecifierToken(token) {
    return (TypeSpecifierDict[token] != undefined);
  }
  /**
  형식 한정자 토큰이라면 true, 아니라면 false를 반환합니다.
  @param {string} token
  @return {boolean}
  */
  function isTypeQualifierToken(token) {
    return (TypeQualifierDict[token] != undefined);
  }
  
  _Declaration.getDeclarationSpecifier = getDeclarationSpecifier;
  compiler.Declaration = _Declaration;
}