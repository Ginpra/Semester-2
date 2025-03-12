#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Roti {
    string nama;
    string kode;
    int harga;
};

Roti roti[1000] = {
    {"Roti Tawar", "110", 12000},
    {"Roti Coklat", "111", 10000},
    {"Roti Keju", "117", 18000},
    {"Roti Pandan", "123", 6000},
    {"Roti Pisang", "121", 7000}
};

void tampilData() {
    cout << "====================" << endl;
    cout << "DATA ROTI" << endl;
    cout << "====================" << endl;

    cout << setfill('-') << setw(40) << " " << endl;
    cout << left << setfill(' ') << setw(6) << "Kode";
    cout << "| " << left << setw(15) << "Nama";
    cout << "| " << left << setw(7) << "Harga" << endl;
    cout << setiosflags(ios::right) << setfill('-') << setw(40) << " " << endl;

    for (int i = 0; i < 5; i++) {
        Roti* ptr = &roti[i];
        cout << setfill(' ') << left << setw(6) << ptr->kode;
        cout << "| " << left << setw(15) << ptr->nama;
        cout << "| " << left << setw(7) << ptr->harga << endl;
    }
    cout << setiosflags(ios::right) << setfill('-') << setw(40) << " " << endl;
}

void sequentialSearch() {
    cout << "SEQUENTIAL SEARCH" << endl;
    string cariKode;
    bool found = false;
    cout << "Ketikkan kode roti yang ingin dicari : ";
    cin >> cariKode;

    for (int i = 0; i < 5; i++) { // asumsi ada 5 data
        if (roti[i].kode == cariKode) {
            cout << "====================" << endl;
            cout << "Data ditemukan" << endl;
            cout << "====================" << endl;
            cout << "Kode : " << roti[i].kode << endl;
            cout << "Nama : " << roti[i].nama << endl;
            cout << "Harga : " << roti[i].harga << endl;
            cout << "\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "Data tidak ditemukan." << endl;
}

int partitionNama(int low, int high) {
    string pivot = roti[high].nama;
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (roti[j].nama < pivot) {
            i++;
            swap(roti[i], roti[j]);
        }
    }
    swap(roti[i + 1], roti[high]);
    return (i + 1);
}

void quickSortNama(int low, int high) {
    if (low < high) {
        int pi = partitionNama(low, high);
        quickSortNama(low, pi - 1);
        quickSortNama(pi + 1, high);
    }
}

void binarySearch() {
    cout << "BINARY SEARCH" << endl;
    string cariNama;
    bool found = false;
    cout << "Ketikkan nama roti yang ingin dicari : ";
    cin.ignore(); 
    getline(cin, cariNama);

    quickSortNama(0, 4);

    int left = 0, right = 5 - 1; // asumsi ada 5 data
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (roti[mid].nama == cariNama) {
            cout << "====================" << endl;
            cout << "Data ditemukan" << endl;
            cout << "====================" << endl;
            cout << "Kode : " << roti[mid].kode << endl;
            cout << "Nama : " << roti[mid].nama << endl;
            cout << "Harga : " << roti[mid].harga << endl;
            cout << "\n";
            found = true;
            break;
        }
        if (roti[mid].nama < cariNama) left = mid + 1;
        else right = mid - 1;
    }
    if (!found) cout << "Data tidak ditemukan." << endl;
}

int partitionHarga(int low, int high) {
    int pivot = roti[high].harga;
    int i = (low - 1);
    for (int j = low; j < high; j++) {
        if (roti[j].harga < pivot) {
            i++;
            swap(roti[i], roti[j]);
        }
    }
    swap(roti[i + 1], roti[high]);
    return (i + 1);
}

void quickSortHarga(int low, int high) {
    if (low < high) {
        int pi = partitionHarga(low, high);
        quickSortHarga(low, pi - 1);
        quickSortHarga(pi + 1, high);
    }
}

void bubbleSort() {
    int totalData = 5; // asumsi ada 5 data
    for (int i = 0; i < totalData - 1; i++) {
        for (int j = 0; j < totalData - i - 1; j++) {
            if (roti[j].harga < roti[j + 1].harga) { // ganti tanda < menjadi > untuk sorting ascending
                swap(roti[j], roti[j + 1]);
            }
        }
    }
    cout << "\nData telah diurutkan berdasarkan harga (descending):\n" << endl;
    tampilData();
}

void menuUtama() 
{
        int menu;
        char pilihan;
        do {
        cout << right << setfill(' ') << "Menu Pilihan : \n";
        cout << "1. Tampil Data"<<endl;
        cout << "2. Cari roti berdasarkan kode"<<endl;
        cout << "3. Cari roti berdasarkan nama"<<endl;
        cout << "4. Sorting roti (ascending)"<<endl;
        cout << "5. Sorting roti (descending)" <<endl;
        cout << "6. Exit" <<endl;
        cout << "pilihan : "; 
        cin >> menu;

        switch (menu) 
        {
            case 1:
                tampilData();
                break;
            case 2:
                sequentialSearch();
                break;
            case 3:
                binarySearch();
                break;
            case 4:
                quickSortHarga(0, 4);
                cout << "\nData telah diurutkan berdasarkan harga (ascending):\n" << endl;
                tampilData();
                break;
            case 5:
                bubbleSort();
                break;    
            case 6:
                cout << "Terima kasih telah menggunakan program ini!" << endl;
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

int main() 
{
    menuUtama(); 
    return 0; 
}
