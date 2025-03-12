#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

struct Penduduk {
    string nik;
    string nama;
    string alamat;
    string jenisKelamin;
};

const int MAX_DATA = 100; // Menetapkan batas maksimum jumlah data penduduk yang dapat disimpan
Penduduk dataPenduduk[MAX_DATA]; // Array untuk menyimpan data penduduk dengan kapasitas maksimum 100
int jumlahData = 0; // Variabel untuk menghitung jumlah data yang saat ini tersimpan

// Fungsi membaca data dari file
void bacaData() {
    jumlahData = 0; // Reset jumlah data sebelum membaca file

    ifstream file("data_penduduk.txt"); // Membuka file untuk dibaca
    if (!file) {
        cout << "Error : File data_penduduk.txt tidak ditemukan!\n";
        return;
    }

    while (file >> dataPenduduk[jumlahData].nik) { // Membaca NIK terlebih dahulu
        if (jumlahData >= MAX_DATA) { // Cegah overflow jika data melebihi kapasitas array
            cout << "Peringatan: Data melebihi kapasitas penyimpanan!\n";
            break; // Hentikan proses baca jika kapasitas penuh
        }

        file.ignore(); // Mengabaikan newline setelah NIK agar getline() bisa membaca dengan benar
        getline(file, dataPenduduk[jumlahData].nama);    // Baca Nama (satu baris penuh)
        getline(file, dataPenduduk[jumlahData].alamat);  // Baca Alamat (satu baris penuh)
        getline(file, dataPenduduk[jumlahData].jenisKelamin); // Baca Jenis Kelamin (satu baris penuh)

        // Validasi apakah data kosong atau tidak
        if (dataPenduduk[jumlahData].nama.empty() || 
            dataPenduduk[jumlahData].alamat.empty() || 
            dataPenduduk[jumlahData].jenisKelamin.empty()) {
            cout << "Peringatan: Data pada baris ke-" << jumlahData + 1 << " tidak valid dan diabaikan!\n";
            continue; // Lewati data yang tidak valid
        }
        jumlahData++; // Tambah jumlah data jika valid
    }
    file.close(); // Menutup file setelah selesai membaca
}

// Fungsi menulis data ke file
void tulisData() {
    ofstream file("data_penduduk.txt"); // Membuka file untuk menulis (overwrite file lama)
    
    if (!file) { // Error handling jika file tidak bisa dibuka
        cout << "Error: Gagal membuka file untuk menulis data!\n";
        return;
    }

    for (int i = 0; i < jumlahData; i++) {
        file << dataPenduduk[i].nik << endl;          
        file << dataPenduduk[i].nama << endl;        
        file << dataPenduduk[i].alamat << endl;      
        file << dataPenduduk[i].jenisKelamin << endl;
    }

    file.close(); // Menutup file setelah selesai menulis
}

// Fungsi menambahkan data penduduk
void tambahData() {
    int input;
    cout << "Masukkan jumlah data yang ingin ditambahkan : ";
    cin >> input;
    cin.ignore();

    if (jumlahData + input > MAX_DATA) {
        cout << "Error : Kapasitas data penuh !\n";
        return;
    }

    for (int i = 0; i < input; i++) {
        Penduduk penduduk;
        cout << "\n====================" << endl;
        cout << "Data ke-" << (i + 1) << endl;
        cout << "====================" << endl;
        cout << "NIK : ";
        cin >> penduduk.nik;

        // Cek apakah NIK sudah ada ada dalam data sebelumnya
        bool duplikat = false;
        for (int j = 0; j < jumlahData; j++) {
            if (dataPenduduk[j].nik == penduduk.nik) {
                cout << "Error : NIK sudah ada!\n";
                duplikat = true;
                break;
            }
        }
        if (duplikat) {
            i--; // Kurangi iterasi agar pengguna bisa memasukkan data lagi
            continue;
        }

        cin.ignore();
        cout << "Nama : ";
        getline(cin, penduduk.nama);
        cout << "Alamat : ";
        getline(cin, penduduk.alamat);

        // Input jenis kelamin dengan validasi (hanya L atau P)
        cout << "Jenis Kelamin (L/P): ";
        while (true) {
            getline(cin, penduduk.jenisKelamin);
            if (penduduk.jenisKelamin == "L" || penduduk.jenisKelamin == "P") {
                break; // Input valid
            }
            cout << "Error: Jenis kelamin harus 'L' atau 'P'!\nJenis Kelamin (L/P): ";
        }

        dataPenduduk[jumlahData++] = penduduk; // Simpan data ke dalam array
    }
    tulisData(); // Simpan data ke file
    cout << "\nData berhasil ditambahkan !\n";
}

// Fungsi menampilkan data penduduk
void tampilData() {
    if (jumlahData == 0) {
        cout << "Tidak ada data! Silakan tambah data terlebih dahulu.\n";
        return;
    }

    // Bubble Sort menggunakan swap() untuk mengurutkan berdasarkan NIK (ascending)
    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = 0; j < jumlahData - i - 1; j++) {
            if (dataPenduduk[j].nik > dataPenduduk[j + 1].nik) {
                swap(dataPenduduk[j], dataPenduduk[j + 1]);
            }
        }
    }

    // Menampilkan data setelah diurutkan
    cout << "\n-----------------Data Penduduk (Diurutkan Berdasarkan NIK)-------------------\n";
    cout << setfill('-') << setw(78) << " " << endl;
    cout << left << setfill(' ') << setw(6) << "NIK";
    cout << "| " << left << setw(25) << "Nama";
    cout << "| " << left << setw(22) << "Alamat";
    cout << "| " << left << setw(10) << "Jenis Kelamin" << "    |" << endl;
    cout << setiosflags(ios::right) << setfill('-') << setw(78) << " " << endl;

    for (int i = 0; i < jumlahData; i++) {
        cout << setfill(' ') << left << setw(6) << dataPenduduk[i].nik;
        cout << "| " << left << setw(25) << dataPenduduk[i].nama;
        cout << "| " << left << setw(22) << dataPenduduk[i].alamat;
        cout << "| " << left << setw(10) << dataPenduduk[i].jenisKelamin << "       |" << endl;
    }
    cout << setiosflags(ios::right) << setfill('-') << setw(78) << " " << endl;
    cout << "Jumlah Data Penduduk : " << jumlahData << "\n" << endl;
}

// Fungsi mencari data berdasarkan NIK (Sequential Search)
void cariData() {
    string cariNik;
    bool found = false;

    cout << "Masukkan NIK yang dicari : ";
    cin >> cariNik;
    cout << "\n";

    // Cek apakah jumlahData kosong
    if (jumlahData == 0) {
        cout << "Tidak ada data! Silakan tambah data terlebih dahulu.\n" << endl;
        return;
    }

    for (int i = 0; i < jumlahData; i++) {
        if (dataPenduduk[i].nik == cariNik) {
            cout << "====================" << endl;
            cout << "Data Ditemukan" << endl;
            cout << "====================" << endl;
            cout << "NIK : " << dataPenduduk[i].nik << endl;
            cout << "Nama : " << dataPenduduk[i].nama << endl;
            cout << "Alamat : " << dataPenduduk[i].alamat << endl;
            cout << "Jenis Kelamin : " << dataPenduduk[i].jenisKelamin << endl; 
            cout << "\n";
            found = true;
            break; // Hentikan pencarian/loop jika data ditemukan
        }
    }
    if (!found) {
        cout << "Data tidak ditemukan!\n" << endl;
    }
}

// Fungsi mengedit alamat berdasarkan NIK
void editData() {
    string cariNik;
    cout << "Masukkan NIK yang mau diedit : ";
    cin >> cariNik;
    cin.ignore();
    cout << "\n";

      // Cek apakah jumlahData kosong
      if (jumlahData == 0) {
        cout << "Tidak ada data! Silakan tambah data terlebih dahulu.\n" << endl;
        return;
    }

    for (int i = 0; i < jumlahData; i++) {
        if (dataPenduduk[i].nik == cariNik) {
            cout << "====================" << endl;
            cout << "Data ditemukan!" << endl;
            cout << "====================" << endl;
            cout << "Nama : " << dataPenduduk[i].nama << endl;
            cout << "Alamat Lama : " << dataPenduduk[i].alamat << endl;
            cout << "Alamat Baru : ";
            getline(cin, dataPenduduk[i].alamat);

            tulisData();
            cout << "\nData berhasil diperbarui!\n" << endl;
            return;
        }
    }
    cout << "Data tidak ditemukan!\n" << endl;
}

// Fungsi menghapus data berdasarkan NIK
void hapusData() {
    string cariNik;
    cout << "Masukkan NIK yang akan dihapus : ";
    cin >> cariNik;

    // Cek apakah jumlahData kosong
    if (jumlahData == 0) {
        cout << "\nTidak ada data! Silakan tambah data terlebih dahulu.\n" << endl;
        return;
    }

    // Mencari indeks data yang memiliki NIK sesuai input
    int index = -1; // Variabel untuk menyimpan indeks data yang akan dihapus
    for (int i = 0; i < jumlahData; i++) {  
        if (dataPenduduk[i].nik == cariNik) { // Jika ditemukan NIK yang cocok
            index = i;  // Simpan indeks data yang ditemukan
            break;  // Hentikan pencarian (karena NIK bersifat unik)
        }
    }

    if (index == -1) {
        cout << "\nData tidak ditemukan!\n" << endl;
        return; // Keluar dari fungsi tanpa melakukan penghapusan
    }

    // Konfirmasi sebelum menghapus data
    char konfirmasi;
    cout << "Apakah Anda yakin ingin menghapus data ini ? (Y/N): ";
    cin >> konfirmasi;

    if (konfirmasi != 'Y' && konfirmasi != 'y') {
        cout << "\nPenghapusan dibatalkan.\n" << endl;
        return;
    }

    // Geser data ke kiri untuk menimpa data yang dihapus
    for (int i = index; i < jumlahData - 1; i++) {
        dataPenduduk[i] = dataPenduduk[i + 1]; // Menimpa data yang dihapus dengan data berikutnya
    }
    jumlahData--; // Mengurangi jumlah total data setelah penghapusan

    tulisData();
    cout << "\nData berhasil dihapus!\n" << endl;
}

// Fungsi menu utama
void menuUtama() 
{
    bacaData();
    cout << "========================================================\n";
    cout << "Selamat datang di Program Manajemen Data Kependudukan\n";
    cout << "========================================================\n";
    int menu;
    char pilihan;
    do {
        cout << right << setfill(' ') << "Menu Pilihan : \n";
        cout << "1. Input Data"<<endl;
        cout << "2. Tampilkan Data"<<endl;
        cout << "3. Cari Data"<<endl;
        cout << "4. Edit Data"<<endl;
        cout << "5. Hapus Data" <<endl;
        cout << "6. Exit" <<endl;
        cout << "pilihan : "; 
        cin >> menu;

        switch (menu) 
        {
            case 1:
                tambahData();
                break;
            case 2:
                tampilData();
                break;
            case 3:
                cariData();
                break;
            case 4:
                editData();
                break;
            case 5:
                hapusData();
                break;    
            case 6:
                cout << "\nTerima kasih telah menggunakan program ini!\n" << endl;
                return;
           default:
        {
            cout << "Maaf pilihan tidak tersedia" << endl;
            break;
        }
        }
            cout << "Apakah Anda ingin melanjutkan program? (y/n) : ";
            cin >> pilihan;
        } while (pilihan == 'y'  || pilihan == 'Y');
}

// Fungsi utama hanya memanggil menu
int main() {
    menuUtama();
    return 0;
}