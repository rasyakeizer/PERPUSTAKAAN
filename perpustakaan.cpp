#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Buku {
public:
    int id;
    string judul;
    string penulis;

    Buku() {}

    Buku(int i, string j, string p) {
        id = i;
        judul = j;
        penulis = p;
    }
};

Buku daftarBuku[5] = {
    Buku(101, "Algoritma", "Andi"),
    Buku(102, "Struktur Data", "Budi"),
    Buku(103, "Pemrograman C++", "Citra"),
    Buku(104, "Basis Data", "Dina"),
    Buku(105, "Jaringan Komputer", "Eko")
};

int jumlahBukuTersedia = 5;

struct Peminjam {
    int id;
    string nama;
    string bukuDipinjam[10];
    int jumlahPinjam;
};

struct Node {
    Peminjam data;
    Node* next;
};

Node* head = NULL;

int inputAngka() {
    int nilai;

    if (!(cin >> nilai)) {
        cout << "\nPilihan tidak valid!\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        return -1;
    }

    cin.ignore();
    return nilai;
}

void tambahPeminjam(Peminjam p) {

    Node* baru = new Node;

    baru->data = p;
    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    }
    else {

        Node* bantu = head;

        while (bantu->next != NULL) {
            bantu = bantu->next;
        }

        bantu->next = baru;
    }
}

void selectionSort(string data[], int jumlah) {

    for (int i = 0; i < jumlah - 1; i++) {

        int min = i;

        for (int j = i + 1; j < jumlah; j++) {

            if (data[j] < data[min]) {
                min = j;
            }
        }

        string temp = data[i];
        data[i] = data[min];
        data[min] = temp;
    }
}

void tampilPeminjam() {

    Node* bantu = head;

    if (head == NULL) {

        cout << "\nBelum ada data peminjam.\n";
        return;
    }

    cout << "\n===== DATA PEMINJAM =====\n";

    while (bantu != NULL) {

        cout << "ID Peminjam : "
             << bantu->data.id << endl;

        cout << "Nama        : "
             << bantu->data.nama << endl;

        cout << "Buku Pinjam : " << endl;

        for (int i = 0; i < bantu->data.jumlahPinjam; i++) {

            cout << i + 1 << ". "
                 << bantu->data.bukuDipinjam[i]
                 << endl;
        }

        cout << "----------------------\n";

        bantu = bantu->next;
    }
}

void hapusPeminjam(int idCari) {

    if (head == NULL) {

        cout << "\nData kosong.\n";
        return;
    }

    Node* bantu = head;
    Node* hapus = NULL;

    if (head->data.id == idCari) {

        hapus = head;
        head = head->next;

        delete hapus;

        cout << "\nData peminjam berhasil dihapus.\n";
        return;
    }

    while (bantu->next != NULL &&
           bantu->next->data.id != idCari) {

        bantu = bantu->next;
    }

    if (bantu->next == NULL) {

        cout << "\nID peminjam tidak ditemukan.\n";
        return;
    }

    hapus = bantu->next;

    bantu->next = hapus->next;

    delete hapus;

    cout << "\nBuku berhasil dikembalikan.\n";
}

void tampilBuku() {

    cout << "\n===== DAFTAR BUKU =====\n";

    for (int i = 0; i < jumlahBukuTersedia; i++) {

        cout << i + 1 << ". "
             << daftarBuku[i].judul
             << " - "
             << daftarBuku[i].penulis
             << endl;
    }
}

void pinjamBuku() {

    int jumlahPeminjam;

    cout << "\nJumlah peminjam : ";
    jumlahPeminjam = inputAngka();

    if (jumlahPeminjam == -1)
        return;

    for (int i = 0; i < jumlahPeminjam; i++) {

        Peminjam p;

        p.id = i + 1;

        cout << "\nNama peminjam : ";
        getline(cin, p.nama);

        while (true) {

            cout << "Jumlah buku dipinjam : ";
            p.jumlahPinjam = inputAngka();

            if (p.jumlahPinjam == -1)
                return;

            if (p.jumlahPinjam > jumlahBukuTersedia) {

                cout << "\nMaaf hanya tersedia "
                     << jumlahBukuTersedia
                     << " buku.\n";
            }
            else {
                break;
            }
        }

        tampilBuku();

        for (int j = 0; j < p.jumlahPinjam; j++) {

            int pilih;

            cout << "\nPilih buku (berdasarkan nomor) ke-"
                 << j + 1
                 << " : ";

            pilih = inputAngka();

            if (pilih == -1)
                return;

            if (pilih < 1 || pilih > jumlahBukuTersedia) {
                cout << "\nPilihan tidak valid!\n";
                return;
            }

            p.bukuDipinjam[j] =
                daftarBuku[pilih - 1].judul;
        }

        selectionSort(
            p.bukuDipinjam,
            p.jumlahPinjam
        );

        tambahPeminjam(p);
    }

    tampilPeminjam();
}

void kembalikanBuku() {

    if (head == NULL) {
        cout << "\nBelum ada data peminjam.\n";
        return;
    }

    tampilPeminjam();

    int id;

    cout << "\nMasukkan ID peminjam : ";
    id = inputAngka();

    if (id == -1)
        return;

    hapusPeminjam(id);

    tampilPeminjam();
}

void clsScreen() {
    system("cls");
}

int main() {

    int menu;

    do {

        cout << "\n===== MENU PERPUSTAKAAN =====\n";
        cout << "1. Pinjam Buku\n";
        cout << "2. Kembalikan Buku\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu : ";

        menu = inputAngka();

        if (menu == -1)
            continue;

        switch (menu) {

        case 1:
            pinjamBuku();
            clsScreen();
            break;

        case 2:
            kembalikanBuku();
            clsScreen();
            break;

        case 3:
            cout << "\nProgram selesai.\n";
            break;

        default:
            cout << "\nPilihan tidak valid!\n";
        }

    } while (menu != 3);

    return 0;
}