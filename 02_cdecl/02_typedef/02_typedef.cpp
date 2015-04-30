#include <iostream>
using namespace std;
int sum(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }
int main(void) {
    // Data를 int 형식으로 정의한다
    typedef int Data;
    Data data = 10;
    cout << "변수: " << data << endl;
    // DataPtr를 Data에 대한 포인터 형식으로 정의한다
    typedef Data *DataPtr;
    DataPtr data_ptr = &data;
    cout << "포인터: " << *data_ptr << endl;
    // DataArr를 크기 3인 Data 변수의 배열 형식으로 정의한다
    typedef Data DataArr[5];
    DataArr data_arr = { 1, 2, 3 };
    cout << "배열: ";
    for (int i = 0; i < 3; ++i) cout << data_arr[i] << ' ';
    cout << endl;
    // FuncPtr를 (int, int)과 같이 인자를 받고
    // int형 값을 반환하는 함수에 대한 포인터 형식으로 정의한다
    typedef int(*FuncPtr)(int, int);
    FuncPtr fp = sum;
    cout << "fp(3, 5): " << fp(3, 5) << endl;
    fp = mul;
    cout << "fp(3, 5): " << fp(3, 5) << endl;
    return 0;
}