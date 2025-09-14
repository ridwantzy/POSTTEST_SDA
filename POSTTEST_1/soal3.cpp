#include <iostream>
using namespace std;

struct Mahasiswa
{
    string nama;
    int nim;
    float ipk;
};

int main()
{
    Mahasiswa mhs[5];

    cout << "Input data " << 5 << " mahasiswa:\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "\nMahasiswa ke-" << i + 1 << ":\n";
        cout << "Nama : ";
        cin >> mhs[i].nama;
        cout << "NIM  : ";
        cin >> mhs[i].nim;
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
    }

    int ipk_tertinggi = 0;
    for (int i = 1; i < 5; i++)
    {
        if (mhs[i].ipk > mhs[ipk_tertinggi].ipk)
        {
            ipk_tertinggi = i;
        }
    }

    cout << "\nMahasiswa dengan IPK tertinggi:\n";
    cout << "Nama : " << mhs[ipk_tertinggi].nama << endl;
    cout << "NIM  : " << mhs[ipk_tertinggi].nim << endl;
    cout << "IPK  : " << mhs[ipk_tertinggi].ipk << endl;

    return 0;
}
