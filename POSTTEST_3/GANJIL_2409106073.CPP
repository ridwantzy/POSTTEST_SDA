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
    Node *prev;
};

void tambahItemBaru(Node *&head, Node *&tail, int jumlahDefault, int &jumlahItem);
void sisipItem(Node *&head, Node *&tail, int jumlahDefault, int posisiSisip, int &jumlahItem);
void hapusItemTerakhir(Node *&head, Node *&tail, int &jumlahItem);
void gunakanItem(Node *&head, Node *&tail, string nama, int &jumlahItem);
void tampilkanInventory(Node *head, int jumlahItem);
void tampilkanInventoryBelakang(Node *tail, int jumlahItem);
void cariItem(Node *head, string nama);

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
    Node *head = nullptr, *tail = nullptr;
    int jumlahDefault = 73, posisiSisip = 4, jumlahItem = 0, pilihan;
    bool loop = true;

    while (loop)
    {
        cout << "\n+===================================================+\n";
        cout << "|           GAME INVENTORY MANAGEMENT               |\n";
        cout << "| [ Muhammad Ridwanansyah Rahman | 2409106073 ]     |\n";
        cout << "+---------------------------------------------------+\n";
        cout << "| 1. Tambah Item Baru                               |\n";
        cout << "| 2. Sisipkan Item                                  |\n";
        cout << "| 3. Hapus Item Terakhir                            |\n";
        cout << "| 4. Gunakan Item                                   |\n";
        cout << "| 5. Tampilkan Inventory (Depan -> Belakang)        |\n";
        cout << "| 6. Tampilkan Inventory (Belakang -> Depan)        |\n";
        cout << "| 7. Cari Item berdasarkan Nama                     |\n";
        cout << "| 0. Keluar                                         |\n";
        cout << "+===================================================+\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahItemBaru(head, tail, jumlahDefault, jumlahItem);
            break;
        case 2:
            sisipItem(head, tail, jumlahDefault, posisiSisip, jumlahItem);
            break;
        case 3:
            hapusItemTerakhir(head, tail, jumlahItem);
            break;
        case 4:
        {
            string nama;
            cout << "Masukkan nama item yang ingin digunakan: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nama);
            while (nama.empty())
            {
                getline(cin, nama);
            }
            gunakanItem(head, tail, nama, jumlahItem);
            break;
        }
        case 5:
            tampilkanInventory(head, jumlahItem);
            break;
        case 6:
            tampilkanInventoryBelakang(tail, jumlahItem);
            break;
        case 7:
        {
            string nama;
            cout << "Masukkan nama item yang ingin dicari: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nama);
            while (nama.empty())
            {
                getline(cin, nama);
            }
            cariItem(head, nama);
            break;
        }
        case 0:
            loop = false;
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }
    }
    return 0;
}

void tambahItemBaru(Node *&head, Node *&tail, int jumlahDefault, int &jumlahItem)
{
    Node *baru = new Node;
    baru->data = inputItem(jumlahDefault);
    baru->next = nullptr;
    baru->prev = tail;

    if (head == nullptr)
    {
        head = tail = baru;
    }
    else
    {
        tail->next = baru;
        tail = baru;
    }

    jumlahItem++;
    cout << "Item berhasil ditambahkan dengan jumlah default = " << jumlahDefault << endl;
}

void sisipItem(Node *&head, Node *&tail, int jumlahDefault, int posisiSisip, int &jumlahItem)
{
    Node *baru = new Node;
    baru->data = inputItem(jumlahDefault);
    baru->next = nullptr;
    baru->prev = nullptr;

    if (head == nullptr)
    {
        baru->next = head;
        if (head)
            head->prev = baru;
        head = baru;
        if (!tail)
            tail = baru;
    }
    else
    {
        Node *temp = head;
        for (int i = 1; temp->next && i < posisiSisip - 1; i++)
        {
            temp = temp->next;
        }
        baru->next = temp->next;
        baru->prev = temp;
        if (temp->next)
            temp->next->prev = baru;
        temp->next = baru;
        if (!baru->next)
            tail = baru;
    }

    jumlahItem++;
    cout << "Item berhasil disisipkan di posisi ke-" << posisiSisip << endl;
}

void hapusItemTerakhir(Node *&head, Node *&tail, int &jumlahItem)
{
    if (tail == nullptr)
    {
        cout << "Inventory kosong!\n";
        return;
    }

    Node *hapus = tail;
    if (head == tail)
    {
        head = tail = nullptr;
    }
    else
    {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete hapus;
    jumlahItem--;
    cout << "Item terakhir berhasil dihapus!\n";
}

void gunakanItem(Node *&head, Node *&tail, string nama, int &jumlahItem)
{
    if (!head)
    {
        cout << "Inventory kosong! Jumlah item = 0\n";
        return;
    }

    Node *temp = head;
    while (temp)
    {
        if (temp->data.namaItem == nama)
        {
            temp->data.jumlah--;
            cout << "Item " << nama << " digunakan! Sisa: " << temp->data.jumlah << endl;

            if (temp->data.jumlah <= 0)
            {
                cout << "Item " << nama << " habis dan dihapus dari inventory!\n";
                if (temp == head)
                {
                    head = temp->next;
                    if (head)
                        head->prev = nullptr;
                }
                else if (temp == tail)
                {
                    tail = temp->prev;
                    if (tail)
                        tail->next = nullptr;
                }
                else
                {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }
                delete temp;
                jumlahItem--;
            }
            return;
        }
        temp = temp->next;
    }
    cout << "Item tidak ditemukan!\n";
}

void tampilkanInventory(Node *head, int jumlahItem)
{
    if (head == nullptr)
    {
        cout << "Inventory kosong! Jumlah item = 0\n";
        return;
    }
    cout << "\n================= INVENTORY LIST (Depan -> Belakang) =================\n";
    cout << " Nama Item           | Jumlah  | Tipe\n";
    cout << "---------------------------------------------------------------------\n";
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

    cout << "---------------------------------------------------------------------\n";
    cout << "Total item dalam inventory: " << jumlahItem << endl;
    cout << "=====================================================================\n";
}

void tampilkanInventoryBelakang(Node *tail, int jumlahItem)
{
    if (!tail)
    {
        cout << "Inventory kosong! Jumlah item = 0\n";
        return;
    }
    cout << "\n================= INVENTORY LIST (Belakang -> Depan) =================\n";
    cout << " No | Nama Item           | Jumlah  | Tipe\n";
    cout << "---------------------------------------------------------------------\n";

    int i = 1;
    while (tail)
    {
        cout << " " << i++
             << "  | " << tail->data.namaItem
             << string(20 - tail->data.namaItem.length(), ' ')
             << "| " << tail->data.jumlah
             << string(7 - to_string(tail->data.jumlah).length(), ' ')
             << "| " << tail->data.tipe << endl;
        tail = tail->prev;
    }

    cout << "---------------------------------------------------------------------\n";
    cout << "Total item dalam inventory: " << jumlahItem << endl;
    cout << "=====================================================================\n";
}

void cariItem(Node *head, string nama)
{
    if (!head)
    {
        cout << "Inventory kosong!\n";
        return;
    }
    bool found = false;
    while (head)
    {
        if (head->data.namaItem == nama)
        {
            cout << "\n=============== DETAIL ITEM ===============\n";
            cout << "Nama   : " << head->data.namaItem << endl;
            cout << "Jumlah : " << head->data.jumlah << endl;
            cout << "Tipe   : " << head->data.tipe << endl;
            cout << "===========================================\n";
            found = true;
            break;
        }
        head = head->next;
    }
    if (!found)
        cout << "Item tidak ditemukan!\n";
}
