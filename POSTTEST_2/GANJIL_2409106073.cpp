#include <iostream>
#include <limits>
#include <string>
using namespace std;

struct Item
{
    string namaItem;
    int jumlah;
    string tipe;
};

struct Node
{
    Item data;
    Node *next;
};

void tambahItemBaru(Node *&head, int jumlahDefault, int &jumlahItem);
void sisipItem(Node *&head, int jumlahDefault, int posisiSisip, int &jumlahItem);
void hapusItemTerakhir(Node *&head, int &jumlahItem);
void gunakanItem(Node *&head, string nama, int &jumlahItem);
void tampilkanInventory(Node *head, int jumlahItem);

Item inputItem(int jumlahDefault)
{
    Item itemBaru;
    cout << "Nama Item : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, itemBaru.namaItem);
    while (itemBaru.namaItem.empty())
    {
        getline(cin, itemBaru.namaItem);
    }
    cout << "Tipe Item : ";
    getline(cin, itemBaru.tipe);
    while (itemBaru.tipe.empty())
    {
        getline(cin, itemBaru.tipe);
    }
    itemBaru.jumlah = jumlahDefault;
    return itemBaru;
}

int main()
{
    Node *head = nullptr;
    int jumlahDefault = 73, posisiSisip = 4, jumlahItem = 0, pilihan;
    bool loop = true;

    while (loop)
    {
        cout << "\n+===================================================+\n";
        cout << "|        GAME INVENTORY MANAGEMENT                  |\n";
        cout << "| [ Muhammad Ridwanansyah Rahman | 2409106073 ]     |\n";
        cout << "+---------------------------------------------------+\n";
        cout << "| 1. Tambah Item Baru                               |\n";
        cout << "| 2. Sisipkan Item                                  |\n";
        cout << "| 3. Hapus Item Terakhir                            |\n";
        cout << "| 4. Gunakan Item                                   |\n";
        cout << "| 5. Tampilkan Inventory                            |\n";
        cout << "| 0. Keluar                                         |\n";
        cout << "+===================================================+\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahItemBaru(head, jumlahDefault, jumlahItem);
            break;
        case 2:
            sisipItem(head, jumlahDefault, posisiSisip, jumlahItem);
            break;
        case 3:
            hapusItemTerakhir(head, jumlahItem);
            break;
        case 4:
        {
            string nama;
            cout << "Masukkan nama item yang ingin digunakan: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nama);
            gunakanItem(head, nama, jumlahItem);
            break;
        }
        case 5:
            tampilkanInventory(head, jumlahItem);
            break;
        case 0:
            loop = false;
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    }
    return 0;
}

void tambahItemBaru(Node *&head, int jumlahDefault, int &jumlahItem)
{
    Node *baru = new Node;
    baru->data = inputItem(jumlahDefault);
    baru->next = nullptr;

    if (head == nullptr)
    {
        head = baru;
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = baru;
    }

    jumlahItem++;
    cout << "Item berhasil ditambahkan dengan jumlah default = " << jumlahDefault << endl;
}

void sisipItem(Node *&head, int jumlahDefault, int posisiSisip, int &jumlahItem)
{
    Node *baru = new Node;
    baru->data = inputItem(jumlahDefault);
    baru->next = nullptr;

    if (head == nullptr)
    {
        baru->next = head;
        head = baru;
        posisiSisip = 1;
    }
    else
    {
        Node *temp = head;
        for (int i = 1; temp->next && i < posisiSisip - 1; i++)
        {
            temp = temp->next;
        }
        baru->next = temp->next;
        temp->next = baru;
    }

    jumlahItem++;
    cout << "Item berhasil disisipkan di posisi ke-" << posisiSisip << endl;
}

void hapusItemTerakhir(Node *&head, int &jumlahItem)
{
    if (head == nullptr)
    {
        cout << "Inventory kosong!\n";
        return;
    }

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        jumlahItem--;
        cout << "Item terakhir berhasil dihapus!\n";
        return;
    }

    Node *temp = head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }

    Node *cur = temp->next;
    temp->next = nullptr;
    delete cur;
    jumlahItem--;

    cout << "Item terakhir berhasil dihapus!\n";
}

void gunakanItem(Node *&head, string nama, int &jumlahItem)
{
    if (head == nullptr)
    {
        cout << "Inventory kosong! Jumlah item = 0\n";
        return;
    }

    Node *temp = head;
    Node *prev = nullptr;

    while (temp)
    {
        if (temp->data.namaItem == nama)
        {
            temp->data.jumlah -= 1;
            cout << "Item " << nama << " digunakan! Sisa: " << temp->data.jumlah << endl;

            if (temp->data.jumlah <= 0)
            {
                cout << "Item " << nama << " habis dan dihapus dari inventory!\n";
                if (prev == nullptr)
                {
                    head = temp->next;
                    delete temp;
                }
                else
                {
                    prev->next = temp->next;
                    delete temp;
                }
                jumlahItem--;
            }
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Item tidak ditemukan!\n";
}

void tampilkanInventory(Node *head, int jumlahItem)
{
    if (!head)
    {
        cout << "Inventory kosong! Jumlah item = 0\n";
        return;
    }
    cout << "\n================= INVENTORY LIST =================\n";
    cout << " No | Nama Item           | Jumlah  | Tipe\n";
    cout << "--------------------------------------------------\n";

    int i = 1;
    while (head)
    {
        cout << " " << i++
             << "  | " << head->data.namaItem
             << string(20 - head->data.namaItem.length(), ' ')
             << "| " << head->data.jumlah
             << string(7 - to_string(head->data.jumlah).length(), ' ')
             << "| " << head->data.tipe << endl;
        head = head->next;
    }

    cout << "--------------------------------------------------\n";
    cout << "Total item dalam inventory: " << jumlahItem << endl;
    cout << "==================================================\n";
}
