#include <iostream>
using namespace std;
// �Լ��� ����
int sum(int a, int b);
int mul(int a, int b);
int main(void) {
    // int�� ������ ����� ���
    int int_var;
    int_var = 10;
    cout << "����: " << int_var << endl;
    // int�� ������ �迭�� ����� ���
    int int_arr[3];
    int_arr[0] = 5, int_arr[1] = 2, int_arr[2] = 3;
    cout << "�迭: ";
    for (int i = 0; i < 3; ++i)
        cout << int_arr[i] << ' ';
    cout << endl;
    // int�� ������ ������ ����� ���
    int *int_ptr;
    int_ptr = &int_var;
    *int_ptr = 20;
    cout << "������: " << *int_ptr << endl;
    // int�� ������ 2���� �迭�� ����� ���
    int int_arr2d[2][3] = { // 2�� 3���� ��ķ� �����ϸ� ���ϴ�
        { 1, 2, 3 },
        { 4, 5, 6 }
    };
    cout << "2���� �迭: " << endl;
    for (int r = 0; r < 2; ++r){
        for (int c = 0; c < 3; ++c) {
            cout << int_arr2d[r][c] << ' ';
        }
        cout << endl;
    }
    // int�� ������ ������ ���� ������ ����
    // �� int�� ���� �������� ����� ���
    int **dptr = &int_ptr;
    **dptr = 30;
    cout << "���� ������: " << **dptr << endl;
    // int�� ���� �� ���� ���ڷ� �ް�
    // int�� ���� ��ȯ�ϴ� �Լ��� ���� ������ ����
    int(*fptr)(int, int);
    fptr = sum;
    cout << "fptr = sum; fptr(3, 5): " << fptr(3, 5) << endl;
    fptr = mul;
    cout << "fptr = mul; fptr(3, 5): " << fptr(3, 5) << endl;
    return 0;
}
int sum(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }