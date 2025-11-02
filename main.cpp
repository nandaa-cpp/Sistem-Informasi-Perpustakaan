#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>
using namespace std;

struct Anggota {
    string id_anggota;
    string kode_anggota;
    string nama;
    string alamat;
    string ttl;    
    string email;
    int status;    
};

struct Buku {
    string id_buku;
    string isbn;
    string judul;
    string pengarang;
    string penerbit;
    int tahun_terbit;
    int stok;
};

struct Petugas {
    string id_petugas;
    string username;
    string password;
    string nama;
};

struct Peminjaman {
    string id_peminjaman;
    string id_anggota;
    string id_buku;
    string tanggal_pinjam;
    string tanggal_kembali;
    int status;  
    int denda;
};

vector<Anggota> anggotaList;
vector<Buku> bukuList;
vector<Peminjaman> pinjamList;

string generateKodeAnggota(string ttl, int urutan) {
    string kode = ttl.substr(0,4) + ttl.substr(5,2) + ttl.substr(8,2);
    if (urutan < 10) kode += "00" + to_string(urutan);
    else if (urutan < 100) kode += "0" + to_string(urutan);
    else kode += to_string(urutan);
    return kode;
}

int hitungSelisihHari(string tgl1, string tgl2) {
    struct tm tm1 = {}, tm2 = {};
    sscanf(tgl1.c_str(), "%d-%d-%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    sscanf(tgl2.c_str(), "%d-%d-%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday);
    tm1.tm_year -= 1900; tm1.tm_mon -= 1;
    tm2.tm_year -= 1900; tm2.tm_mon -= 1;
    time_t waktu1 = mktime(&tm1);
    time_t waktu2 = mktime(&tm2);
    double selisih = difftime(waktu2, waktu1) / (60 * 60 * 24);
    return (int) selisih;
}

//nanda
void tambahAnggota() {
    Anggota a;
    cout << "\nNama: "; getline(cin >> ws, a.nama);
    cout << "Alamat: "; getline(cin, a.alamat);
    cout << "Tanggal Lahir (YYYY-MM-DD): "; cin >> a.ttl;
    cout << "Email: "; cin >> a.email;
    a.status = 1;
    a.id_anggota = "A" + to_string(anggotaList.size() + 1);
    a.kode_anggota = generateKodeAnggota(a.ttl, anggotaList.size() + 1);
    anggotaList.push_back(a);
    cout << "Anggota berhasil ditambahkan dengan kode: " << a.kode_anggota << endl;
}

void tampilAnggota() {
    sort(anggotaList.begin(), anggotaList.end(),
         [](Anggota a, Anggota b){ return a.nama < b.nama; });
    cout << "\n=== DAFTAR ANGGOTA (A-Z) ===\n";
    cout << left << setw(10) << "ID" << setw(25) << "Nama"
         << setw(15) << "Kode" << setw(10) << "Status" << endl;
    for (auto &a : anggotaList)
        cout << left << setw(10) << a.id_anggota << setw(25) << a.nama
             << setw(15) << a.kode_anggota
             << setw(10) << (a.status ? "Aktif" : "Nonaktif") << endl;
}

//naswa
void tambahBuku() {
    Buku b;
    cout << "\nJudul Buku: "; getline(cin >> ws, b.judul);
    cout << "ISBN: "; cin >> b.isbn;
    cout << "Pengarang: "; getline(cin >> ws, b.pengarang);
    cout << "Penerbit: "; getline(cin >> ws, b.penerbit);
    cout << "Tahun Terbit: "; cin >> b.tahun_terbit;
    cout << "Stok: "; cin >> b.stok;
    b.id_buku = "B" + to_string(bukuList.size() + 1);
    bukuList.push_back(b);
    cout << "Buku berhasil ditambahkan.\n";
}

void tampilBuku() {
    sort(bukuList.begin(), bukuList.end(),
         [](Buku a, Buku b){ return a.judul < b.judul; });
    cout << "\n=== DAFTAR BUKU (A-Z) ===\n";
    cout << left << setw(10) << "ID" << setw(30) << "Judul"
         << setw(20) << "Pengarang" << setw(10) << "Stok" << endl;
    for (auto &b : bukuList)
        cout << left << setw(10) << b.id_buku << setw(30) << b.judul
             << setw(20) << b.pengarang << setw(10) << b.stok << endl;
}

//reski
void tambahPeminjaman() {
    if (anggotaList.empty() || bukuList.empty()) {
        cout << "Data anggota atau buku belum ada!\n";
        return;
    }
    Peminjaman p;
    cout << "\nID Anggota: "; cin >> p.id_anggota;
    cout << "ID Buku: "; cin >> p.id_buku;
    cout << "Tanggal Pinjam (YYYY-MM-DD): "; cin >> p.tanggal_pinjam;
    cout << "Tanggal Kembali (YYYY-MM-DD): "; cin >> p.tanggal_kembali;
    p.id_peminjaman = "P" + to_string(pinjamList.size() + 1);
    p.status = 1;
    p.denda = 0;
    pinjamList.push_back(p);

    for (auto &b : bukuList)
        if (b.id_buku == p.id_buku && b.stok > 0) b.stok--;

    cout << "Peminjaman berhasil ditambahkan.\n";
}

void tampilPeminjaman() {
    cout << "\n=== DATA PEMINJAMAN ===\n";
    cout << left << setw(10) << "ID" << setw(10) << "Anggota"
         << setw(10) << "Buku" << setw(15) << "Status"
         << setw(10) << "Denda" << endl;
    for (auto &p : pinjamList)
        cout << left << setw(10) << p.id_peminjaman << setw(10) << p.id_anggota
             << setw(10) << p.id_buku
             << setw(15) << (p.status ? "Belum" : "Kembali")
             << setw(10) << p.denda << endl;
}

//marvel
void kembalikanBuku() {
    string idp, tglSekarang;
    cout << "\nMasukkan ID Peminjaman: "; cin >> idp;
    cout << "Tanggal Hari Ini (YYYY-MM-DD): "; cin >> tglSekarang;

    for (auto &p : pinjamList) {
        if (p.id_peminjaman == idp && p.status == 1) {
            int terlambat = hitungSelisihHari(p.tanggal_kembali, tglSekarang);
            p.denda = terlambat > 0 ? terlambat * 1000 : 0;
            p.status = 0;
            for (auto &b : bukuList)
                if (b.id_buku == p.id_buku) b.stok++;
            cout << "Buku berhasil dikembalikan. Denda: Rp " << p.denda << endl;
            return;
        }
    }
    cout << "Data peminjaman tidak ditemukan atau sudah dikembalikan.\n";
}

//naswa
void cariBuku() {
    string judul;
    cout << "\nMasukkan judul buku yang dicari: ";
    getline(cin >> ws, judul);
    for (auto &b : bukuList) {
        if (b.judul.find(judul) != string::npos) {
            cout << "Ditemukan: " << b.id_buku << " - " << b.judul << endl;
            return;
        }
    }
    cout << "Buku tidak ditemukan.\n";
}

//reski
void cariAnggota() {
    string kode;
    cout << "\nMasukkan kode anggota: ";
    cin >> kode;
    for (auto &a : anggotaList) {
        if (a.kode_anggota == kode) {
            cout << "Nama: " << a.nama << ", Status: "
                 << (a.status ? "Aktif" : "Nonaktif") << endl;
            return;
        }
    }
    cout << "Anggota tidak ditemukan.\n";
}

//marvel
void simpanData() {
    ofstream f("perpustakaan_data.txt");
    f << "=== DATA ANGGOTA ===\n";
    for (auto &a : anggotaList)
        f << a.id_anggota << "," << a.nama << "," << a.kode_anggota << "," << a.ttl << "," << a.status << "\n";
    f << "\n=== DATA BUKU ===\n";
    for (auto &b : bukuList)
        f << b.id_buku << "," << b.judul << "," << b.pengarang << "," << b.stok << "\n";
    f << "\n=== DATA PEMINJAMAN ===\n";
    for (auto &p : pinjamList)
        f << p.id_peminjaman << "," << p.id_anggota << "," << p.id_buku << "," << p.status << "," << p.denda << "\n";
    f.close();
    cout << "Data berhasil disimpan ke file 'perpustakaan_data.txt'.\n";
}

//nanda
int main() {
    int pilih;
    do {
        cout << "\n======= SISTEM INFORMASI PERPUSTAKAAN =======\n";
        cout << "1. Tambah Anggota\n";
        cout << "2. Tambah Buku\n";
        cout << "3. Tambah Peminjaman\n";
        cout << "4. Kembalikan Buku\n";
        cout << "5. Tampil Anggota\n";
        cout << "6. Tampil Buku\n";
        cout << "7. Tampil Peminjaman\n";
        cout << "8. Cari Buku\n";
        cout << "9. Cari Anggota\n";
        cout << "10. Simpan Data ke File\n";
        cout << "0. Keluar\n";
        cout << "Pilih: "; cin >> pilih;
        cin.ignore();

        switch (pilih) {
            case 1: tambahAnggota(); break;
            case 2: tambahBuku(); break;
            case 3: tambahPeminjaman(); break;
            case 4: kembalikanBuku(); break;
            case 5: tampilAnggota(); break;
            case 6: tampilBuku(); break;
            case 7: tampilPeminjaman(); break;
            case 8: cariBuku(); break;
            case 9: cariAnggota(); break;
            case 10: simpanData(); break;
            case 0: cout << "Keluar...\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 0);
}
