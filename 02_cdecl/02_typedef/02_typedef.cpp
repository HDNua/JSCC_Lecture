#include <iostream>
using namespace std;
int sum(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }
int main(void) {
    // Data�� int �������� �����Ѵ�
    typedef int Data;
    Data data = 10;
    cout << "����: " << data << endl;
    // DataPtr�� Data�� ���� ������ �������� �����Ѵ�
    typedef Data *DataPtr;
    DataPtr data_ptr = &data;
    cout << "������: " << *data_ptr << endl;
    // DataArr�� ũ�� 3�� Data ������ �迭 �������� �����Ѵ�
    typedef Data DataArr[5];
    DataArr data_arr = { 1, 2, 3 };
    cout << "�迭: ";
    for (int i = 0; i < 3; ++i) cout << data_arr[i] << ' ';
    cout << endl;
    // FuncPtr�� (int, int)�� ���� ���ڸ� �ް�
    // int�� ���� ��ȯ�ϴ� �Լ��� ���� ������ �������� �����Ѵ�
    typedef int(*FuncPtr)(int, int);
    FuncPtr fp = sum;
    cout << "fp(3, 5): " << fp(3, 5) << endl;
    fp = mul;
    cout << "fp(3, 5): " << fp(3, 5) << endl;
    return 0;
}