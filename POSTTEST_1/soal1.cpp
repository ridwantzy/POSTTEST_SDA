#include <iostream>
using namespace std;

void membalik_urutan(int *kelipatan_3, int angka)
{
    int temp;
    for (int i = 0; i < angka / 2; i++)
    {
        temp = kelipatan_3[i];
        kelipatan_3[i] = kelipatan_3[angka - 1 - i];
        kelipatan_3[angka - 1 - i] = temp;
    }
}

int main()
{
    const int angka = 7;
    int kelipatan_3[angka];

    for (int i = 0; i < angka; i++)
    {
        kelipatan_3[i] = (i + 1) * 3;
    }

    cout << "Array sebelum dibalik: ";
    for (int i = 0; i < angka; i++)
    {
        cout << kelipatan_3[i] << " ";
    }

    membalik_urutan(kelipatan_3, angka);
    cout << "\nArray sesudah dibalik: ";
    for (int i = 0; i < angka; i++)
    {
        cout << kelipatan_3[i] << " ";
    }

    return 0;
}
