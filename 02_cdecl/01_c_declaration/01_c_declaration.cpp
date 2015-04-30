#include <iostream>
using namespace std;
// 함수의 선언
int sum(int a, int b);
int mul(int a, int b);
int main(void) {
    // int형 변수의 선언과 사용
    int int_var;
    int_var = 10;
    cout << "변수: " << int_var << endl;
    // int형 변수의 배열의 선언과 사용
    int int_arr[3];
    int_arr[0] = 5, int_arr[1] = 2, int_arr[2] = 3;
    cout << "배열: ";
    for (int i = 0; i < 3; ++i)
        cout << int_arr[i] << ' ';
    cout << endl;
    // int형 포인터 변수의 선언과 사용
    int *int_ptr;
    int_ptr = &int_var;
    *int_ptr = 20;
    cout << "포인터: " << *int_ptr << endl;
    // int형 변수의 2차원 배열의 선언과 사용
    int int_arr2d[2][3] = { // 2행 3열의 행렬로 생각하면 편하다
        { 1, 2, 3 },
        { 4, 5, 6 }
    };
    cout << "2차원 배열: " << endl;
    for (int r = 0; r < 2; ++r){
        for (int c = 0; c < 3; ++c) {
            cout << int_arr2d[r][c] << ' ';
        }
        cout << endl;
    }
    // int형 포인터 변수에 대한 포인터 변수
    // 즉 int형 더블 포인터의 선언과 사용
    int **dptr = &int_ptr;
    **dptr = 30;
    cout << "더블 포인터: " << **dptr << endl;
    // int형 변수 두 개를 인자로 받고
    // int형 값을 반환하는 함수에 대한 포인터 선언
    int(*fptr)(int, int);
    fptr = sum;
    cout << "fptr = sum; fptr(3, 5): " << fptr(3, 5) << endl;
    fptr = mul;
    cout << "fptr = mul; fptr(3, 5): " << fptr(3, 5) << endl;
    return 0;
}
int sum(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }