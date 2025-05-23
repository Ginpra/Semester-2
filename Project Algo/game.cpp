#include <iostream>
#include <string>
#include <iomanip>
#include <cstdio>
using namespace std;

struct Game {
    int id;
    char nama[100];
    float harga;
    int stok;
    char genre[20];
};

struct Node {
    Game data;
    Node* prev;
    Node* next;
};

Node* head = nullptr;

void bacafile() {
    FILE* file = fopen("data_game.txt", "r");
    if (!file) {
        cout << "File tidak ditemukan!\n";
        return;
    }

    while (true) {
        Game g;
        if (fscanf(file, "%d", &g.id) != 1) break;
        fscanf(file, " %99[^\n]", g.nama); // Baca nama hingga newline
        fscanf(file, "%f", &g.harga);
        fscanf(file, "%d", &g.stok);
        fscanf(file, " %19[^\n]", g.genre);

        // buat node baru
        Node* baru = new Node{g, nullptr, nullptr};
        if (!head) {
            head = baru; // Jika list masih kosong, node ini menjadi head
        } else { // Jika list sudah ada, sisip di akhir (tail)
            Node* bantu = head;
            while (bantu->next) {
                bantu = bantu->next; // Cari node terakhir
            }
            bantu->next = baru; // Hubungkan node terakhir ke node baru
            baru->prev = bantu; // Hubungkan node baru ke node terakhir
        }
    }
    fclose(file);
}

// Menyimpan satu data Game ke file (append)
void simpanFile(const Game& g) {
    FILE* file = fopen("data_game.txt", "a");
    if (!file) {
        cout << "Gagal membuka file untuk menyimpan data!\n";
        return;
    }
    fprintf(file, "%d\n%s\n%f\n%d\n%s\n",
            g.id, g.nama, g.harga, g.stok, g.genre);
    fclose(file);
}

void sortingGame() {
    if (!head || !head->next) return; // Tidak perlu sorting jika list kosong atau hanya satu elemen

    bool swapped; // untuk menandakan apakah ada pertukaran
    do {
        swapped = false; // Reset swapped flag
        Node* bantu = head; // mulai dari head

        while (bantu->next) { 
            if (bantu->data.id > bantu->next->data.id) { // bandingkan ID
                // Tukar data antara node saat ini dan node berikutnya
                Game temp = bantu->data; // simpan data node saat ini ke temp
                bantu->data = bantu->next->data; // Salin data node berikutnya ke node saat ini
                bantu->next->data = temp; // salin data temp ke node berikutnya
                
                swapped = true; // tandakan bahwa ada pertukaran
            }
            bantu = bantu->next;
        }
    } while (swapped); // ulangi hingga tidak ada pertukaran
}


void tampilGame() {
    if (!head) {
        cout << "\nData kosong!\n";
        return;
    }

    sortingGame(); 

    cout << "\nData Game:\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout << setw(15) << "ID"
         << setw(20) << "Nama"
         << setw(15) << "Harga"
         << setw(10) << "Stok"
         << setw(15) << "Genre" << "\n";
    cout << "--------------------------------------------------------------------------------\n";

    Node* bantu = head;
    while (bantu) {
        cout << setw(15) << bantu->data.id
             << setw(20) << bantu->data.nama
             << setw(15) << bantu->data.harga
             << setw(10) << bantu->data.stok
             << setw(15) << bantu->data.genre << "\n";
        bantu = bantu->next; // Pindah ke node berikutnya
    }
}

void inputGame() {
    int input;
    cout << "Masukkan jumlah game : ";
    cin >> input;

    for (int i = 0; i < input; i++) {
        Game g;
        cout << "\n=====================\n";
        cout << "Data ke- " << (i + 1) << "\n";

        cout << "Masukkan ID : ";
        cin >> g.id;
        cin.ignore();

        // cek duplikat
        Node* bantu = head;
        while (bantu) {
            if (bantu->data.id == g.id) {
                cout << "ID sudah terdaftar!\n";
                return;
            }
            bantu = bantu->next;
        }

        cout << "Masukkan Nama : ";
        cin.getline(g.nama, sizeof(g.nama));
        cout << "Masukkan Harga : ";
        cin >> g.harga;
        cout << "Masukkan Stok : ";
        cin >> g.stok;
        cout << "Masukkan Genre : ";
        cin >> g.genre;

        // buat node baru dan sisip di belakang / akhir list (tail)
        Node* baru = new Node{g, nullptr, nullptr};
        if (!head) {
            head = baru;
        } else {
            bantu = head;
            while (bantu->next) bantu = bantu->next;
            bantu->next = baru;
            baru->prev = bantu;
        }
        simpanFile(g);
        cout << "Data berhasil ditambahkan!\n";
    }
}

void searchGame() {
    if (!head) {
        cout << "\nData kosong!\n";
        return;
    }

    int ID;
    cout << "\nMasukkan ID yang dicari : ";
    cin >> ID;

    Node* bantu = head;
    while (bantu) {
        if (bantu->data.id == ID) {
            cout << "\nData ditemukan :\n";
            cout << "ID     : " << bantu->data.id << "\n";
            cout << "Nama   : " << bantu->data.nama << "\n";
            cout << "Harga  : " << bantu->data.harga << "\n";
            cout << "Stok   : " << bantu->data.stok << "\n";
            cout << "Genre  : " << bantu->data.genre << "\n";
            return;
        }
        bantu = bantu->next;
    }
    cout << "\nData dengan ID : " << ID << " tidak ditemukan.\n";
}

void editGame() {
    if (!head) {
        cout << "\nData kosong!\n";
        return;
    }

    int ID;
    cout << "\nMasukkan ID game yang ingin diedit : ";
    cin >> ID;
    cin.ignore();

    Node* bantu = head;
    while (bantu) {
        if (bantu->data.id == ID) {
            cout << "\nData ditemukan, masukkan data baru :\n";
            cout << "Nama   [" << bantu->data.nama << "] : ";
            cin.getline(bantu->data.nama, sizeof(bantu->data.nama));
            cout << "Harga  [" << bantu->data.harga << "] : ";
            cin >> bantu->data.harga;
            cout << "Stok   [" << bantu->data.stok << "] : ";
            cin >> bantu->data.stok;
            cout << "Genre  [" << bantu->data.genre << "] : ";
            cin >> bantu->data.genre;

            // Simpan ulang seluruh linked list ke file (overwrite)
            FILE* file = fopen("data_game.txt", "w");

            if (!file) {
                cout << "\nGagal membuka file untuk menyimpan perubahan!\n";
                return;
            }

            Node* temp = head;
            while (temp) {
                fprintf(file, "%d\n%s\n%f\n%d\n%s\n",
                        temp->data.id, temp->data.nama,
                        temp->data.harga, temp->data.stok,
                        temp->data.genre);
                temp = temp->next;
            }
            fclose(file);
            cout << "Data berhasil diperbarui!\n";
            return;
        }
        bantu = bantu->next;
    }
    cout << "\nData dengan ID " << ID << " tidak ditemukan.\n";
}

void hapusGame() {
    if (!head) {
        cout << "\nData kosong!\n";
        return;
    }

    int ID;
    cout << "\nMasukkan ID yang akan dihapus : ";
    cin >> ID;

    Node* bantu = head;
    while (bantu && bantu->data.id != ID) {
        bantu = bantu->next;
    }

    if (!bantu) {
        cout << "\nData dengan ID : " << ID << " tidak ditemukan.\n";
        return;
    }

    // relink / sambungkan node kembali
    if (bantu->prev) { // jika node yang dihapus bukan head
        bantu->prev->next = bantu->next;
    } else {  // jika node yang dihapus adalah head
        head = bantu->next;
    }
    if (bantu->next) { // jika node yang dihapus bukan terakhir 
        bantu->next->prev = bantu->prev;
    } else { // jika node yang dihapus adalah terakhir / tail biasanya
        bantu->prev->next = nullptr; //tidak pakai ini juga bisa 
    }
    delete bantu;
    cout << "\nData berhasil dihapus!\n";

    // simpan ulang semua ke file
    FILE* file = fopen("data_game.txt", "w");

    if (!file) {
        cout << "Gagal membuka file untuk menyimpan perubahan!\n";
        return;
    }

    Node* temp = head;
    while (temp) {
        fprintf(file, "%d\n%s\n%f\n%d\n%s\n",
                temp->data.id, temp->data.nama,
                temp->data.harga, temp->data.stok,
                temp->data.genre);
        temp = temp->next;
    }
    fclose(file);
}

void menuUtama() {
    int menu;
    do {
        cout << "\n===== MENU UTAMA =====\n";
        cout << "1. Input Game\n"
             << "2. Tampilkan Game\n"
             << "3. Search Game\n"
             << "4. Edit Game\n"
             << "5. Hapus Game\n"
             << "6. Exit\n";
        cout << "Pilihan: ";
        cin >> menu;

        switch (menu) {
            case 1: inputGame();   break;
            case 2: tampilGame();  break;
            case 3: searchGame();  break;
            case 4: editGame();    break;
            case 5: hapusGame();   break;
            case 6: cout << "\nTerima kasih!\n"; return;
            default: cout << "\nPilihan tidak tersedia!\n";
        }
    } while (true);
}

int main() {
    bacafile();
    menuUtama();
    return 0;
}
