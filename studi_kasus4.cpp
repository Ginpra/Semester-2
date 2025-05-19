#include <iostream>
using namespace std;

struct Pesanan {
    string nama;
    string roti;
    int harga;
    Pesanan *next;
};

Pesanan *depan, *belakang; // Queue : antrean pembeli
Pesanan *awal, *top;       // Stack : history pesanan yang sudah dilayani

void buatstack() {
    awal = top = NULL;
}

bool stackkosong() {
    return awal == NULL;
}

void buatqueue() {
    depan = belakang = NULL;
}

bool queuekosong() {
    return depan == NULL;
}

void enqueue(string nama, string roti, int harga) {
    Pesanan *baru = new Pesanan();
    baru->nama = nama; 
    baru->roti = roti;
    baru->harga = harga;
    baru->next = NULL;

    if (queuekosong()) { // Jika antrean kosong
        depan = belakang = baru; // Pesanan pertama
    } else { // Jika antrean tidak kosong
        belakang->next = baru; // Pesanan baru ditambahkan di belakang
        belakang = baru; 
    }
    cout << "Pesanan berhasil ditambahkan ke antrean\n";
}

void tampilkanAntrean() {
    if (queuekosong()) {
        cout << "Antrean kosong\n";
        return;
    }
    Pesanan *bantu = depan; // Menunjuk ke depan antrean atau yang pertama
    cout << "\nDaftar Pesanan (Antrean) :\n";
    int i = 1; // Nomor urut antrean biar rapi aja sih
    while (bantu != NULL) {
        cout << i++ << ". " << bantu->nama << " - " << bantu->roti << " - Rp." << bantu->harga << endl;
        bantu = bantu->next;
    }
}

void batalkanTerakhir() {
    if (queuekosong()) {
        cout << "Tidak ada pesanan yang bisa dibatalkan\n";
    } else if (depan == belakang) { // Hanya satu pesanan/antrean
        delete depan; 
        depan = belakang = NULL;
        cout << "Pesanan terakhir dibatalkan\n";
    } else { // Lebih dari satu pesanan/antrean
        Pesanan *bantu = depan;
        while (bantu->next != belakang) {
            bantu = bantu->next;
        }
        delete belakang;
        belakang = bantu;
        belakang->next = NULL;
        cout << "Pesanan terakhir dibatalkan\n";
    }
}

void pushHistory(Pesanan *data) { // Menyimpan pesanan yang sudah dilayani ke stack
    Pesanan *baru = new Pesanan();
    baru->nama = data->nama;
    baru->roti = data->roti;
    baru->harga = data->harga;
    baru->next = NULL;

    if (stackkosong()) {
        awal = top = baru;
    } else {
        top->next = baru;
        top = baru;
    }
}

void layaniPesanan() {
    if (queuekosong()) {
        cout << "Tidak ada pesanan dalam antrean\n";
    } else {
        Pesanan *layani = depan;
        cout << "Melayani pesanan atas nama : " << layani->nama << endl;
        pushHistory(layani);
        depan = depan->next;
        delete layani;

        if (depan == NULL) {
            belakang = NULL;
        }
    }
}

void tampilkanHistory() {
    if (stackkosong()) {
        cout << "Belum ada history pesanan\n";
        return;
    }
    Pesanan *bantu = awal;
    cout << "\nRiwayat Pesanan :\n";
    int i = 1;
    while (bantu != NULL) {
        cout << i++ << ". " << bantu->nama << " - " << bantu->roti << " - Rp." << bantu->harga << endl;
        bantu = bantu->next;
    }
}

void menuPilihan() {
    string nama, roti;
    int harga;
    int pilihan;
    do {
        cout << "\n=== Menu Toko Roti Manis Lezat ===\n";
        cout << "1. Ambil Antrean\n";
        cout << "2. Layani Pembeli\n";
        cout << "3. Tampilkan Antrean\n";
        cout << "4. Batalkan Pesanan Terakhir\n";
        cout << "5. Tampilkan History\n";
        cout << "0. Keluar\n";
        cout << "Pilih : ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                    cout << "nama pembeli : ";
                    cin >> nama;
                    cout << "jenis roti : ";
                    cin >> roti;
                    cout << "harga : ";
                    cin >> harga;
                    cin.ignore();
                    enqueue(nama, roti, harga);
                break;
            }
            case 2:
                layaniPesanan();
                break;
            case 3:
                tampilkanAntrean();
                break;
            case 4:
                batalkanTerakhir();
                break;
            case 5:
                tampilkanHistory();
                break;
            case 0:
                cout << "Terima Kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid\n";
        }
    } while (pilihan != 0);
}

int main() {
    buatstack();
    buatqueue();
    menuPilihan();
    return 0;
}
