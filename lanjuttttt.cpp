#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>

using namespace std;

struct MenuItem {
    string nama;
    double harga;
    string kategori;
    string subkategori;
};

struct PesananItem {
    MenuItem menu;
    int jumlah;
    string catatan;
    double subtotal() const {
        return menu.harga * jumlah;
    }
};

struct Transaksi {
    string namaPelanggan;
    vector<PesananItem> daftarPesanan;
    double totalBayar = 0.0;
    string metodePembayaran;
    bool diskonDiterapkan = false;
    string tanggal;
};

struct Ulasan {
    string namaPelanggan;
    string komentar;
    int rating; // 1 sampai 5
};

struct User {
    string username;
    string password;
    string role; // "admin" atau "pegawai"
};

vector<User> daftarUser = {
    {"admin", "admin123", "admin"},
    {"pegawai", "pegawai123", "pegawai"}
};

string login() {
    string username, password;
    int percobaan = 0;
    while (percobaan < 3) {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        for (const auto& user : daftarUser) {
            if (user.username == username && user.password == password) {
            	
            	cout<<endl;
                cout << "Login berhasil sebagai " << user.role << "\n";
                return user.role;
            }
        }
        
		cout<<endl;
        cout << "Login gagal. Coba lagi.\n";
        percobaan++;
    }
    
	cout<<endl;
    cout << "Terlalu banyak percobaan . Keluar dari program.\n";
    exit(0);
    
}

class SistemPemesananSoto {
private:
    vector<MenuItem> menu;
    vector<Transaksi> riwayatTransaksi;
    vector<Ulasan> daftarUlasan;
    map<string, int> stokHarian;
    map<string, map<string, int>> penjualanPerHari;


    const double tarifDiskon = 0.10;
    const double batasDiskon = 50000.0;
    const int maxInputPercobaan = 3;
    
	string getTanggalHariIni() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
        return string(buffer);
    }
    
	vector<MenuItem> getMenuByKategori(const string& kategori) {
    vector<MenuItem> hasil;
    for (const auto& item : menu) {
        if (item.kategori == kategori) {
            hasil.push_back(item);
        }
    }
    
    return hasil;
    
}

vector<MenuItem> getMenuByKategoriDanSub(const string& kategori, const string& subkategori) {
    vector<MenuItem> hasil;
    for (const auto& item : menu) {
        if (item.kategori == kategori && item.subkategori == subkategori) {
            hasil.push_back(item);
        }
    }
    
    return hasil;
    
}

    void tampilkanMenu() {
        cout << "\n========================================\n";
        cout << "         MENU Soto Lenthok Pak B        \n";
        cout << "========================================\n";
        for (size_t i = 0; i < menu.size(); ++i) {
            cout << (i + 1) << ". " << left << setw(25) << menu[i].nama
                 << " - Rp " << fixed << setprecision(0) << menu[i].harga << "\n";
        }
        cout << "0. Selesai Memesan\n";
        cout << "========================================\n";
    }

    int inputAngkaDenganValidasi(string pesan, int minVal, int maxVal) {
        int angka;
        int percobaan = 0;
        while (true) {
            if (percobaan >= maxInputPercobaan) {
                cout << "Terlalu banyak input salah. Mengulang proses input...\n";
                percobaan = 0;
            }
            cout << pesan;
            if (cin >> angka) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (angka >= minVal && angka <= maxVal) {
                    return angka;
                } else {
                    cout << "Input harus antara " << minVal << " dan " << maxVal << ". Coba lagi.\n";
                }
            } else {
                cout << "Input tidak valid (bukan angka). Coba lagi.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            percobaan++;
        }
    }

    string inputString(string pesan) {
        string hasil;
        cout << pesan;
        if (cin.peek() == '\n') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        getline(cin, hasil);
        return hasil;
    }
    double hitungTotalBayar(Transaksi &trans) {
    double subtotal = 0.0;
    for (auto &item : trans.daftarPesanan) {
        subtotal += item.subtotal();
    }

    // Simpan total awal
    double total = subtotal;

    // Terapkan diskon jika memenuhi
    if (total >= batasDiskon) {
        trans.diskonDiterapkan = true;
        total = total * (1 - tarifDiskon);
    } else {
        trans.diskonDiterapkan = false;
    }

    trans.totalBayar = total;
    return total;
    
}


Transaksi buatPesanan(){
        Transaksi trans;
        trans.daftarPesanan.clear();

        cout << "\n--- FORM PEMESANAN BARU ---\n";
        trans.namaPelanggan = inputString("Masukkan nama pelanggan (opsional, tekan Enter jika kosong): ");

        vector<string> kategori = {"Makanan Berat", "Lauk Tambahan", "Aneka Sambal", "Paket Hemat", "Paket Menu Anak", "Minuman", "Pencuci Mulut"};
        

while (true) {
    cout << "\nPilih kategori:\n";
    for (int i = 0; i < kategori.size(); ++i) {
        cout << i + 1 << ". " << kategori[i] << "\n";
    }
    cout << "0. Selesai memilih\n";
    int pilihKat = inputAngkaDenganValidasi("Pilihan: ", 0, 3);
    if (pilihKat == 0) break;

    string katTerpilih = kategori[pilihKat - 1];

    vector<MenuItem> menuKategori;


    if (katTerpilih == "Minuman") {
        cout << "\nPilih subkategori minuman:\n";
        cout << "1. Non-Kafein\n2. Kafein\n0. Kembali\n";
        int sub = inputAngkaDenganValidasi("Pilihan: ", 0, 2);
        if (sub == 0) continue;
        string subkat = (sub == 1) ? "Non-Kafein" : "Kafein";

        for (const auto& item : menu) {
            if (item.kategori == katTerpilih && item.subkategori == subkat) {
                menuKategori.push_back(item);
            }
        }
    } else {
        for (const auto& item : menu) {
            if (item.kategori == katTerpilih) {
                menuKategori.push_back(item);
            }
        }
    }

    if (menuKategori.empty()) {
        cout << "Menu kosong dalam kategori ini.\n";
        continue;
    }

    cout << "\n========================================\n";
    cout << "           " << katTerpilih << "           \n";
    cout << "========================================\n";
    for (size_t i = 0; i < menuKategori.size(); ++i) {
        cout << (i + 1) << ". " << left << setw(25) << menuKategori[i].nama
             << " - Rp" << fixed << setprecision(0) << menuKategori[i].harga << "\n";
    }
    cout << "0. Kembali ke kategori\n";

    int pilihMenu = inputAngkaDenganValidasi("Pilih menu: ", 0, menuKategori.size());
    if (pilihMenu == 0) continue;

    int jumlah = inputAngkaDenganValidasi("Masukkan jumlah porsi: ", 1, 100);

    PesananItem item;
    item.menu = menuKategori[pilihMenu - 1];
    item.jumlah = jumlah;
    trans.daftarPesanan.push_back(item);
}
		kelolaPesananSementara(trans);
		return trans;
}
	void cetakStruk(const Transaksi &trans) {
    // STRUK PEMESANAN
    cout << "\n=========== STRUK PEMESANAN ===========\n";
    cout << "Tanggal/Waktu: " << __DATE__ << " " << __TIME__ << "\n";
    if (!trans.namaPelanggan.empty()) {
        cout << "Nama Pelanggan : " << trans.namaPelanggan << "\n";
    }
    cout << "----------------------------------------\n";
    for (const auto &item : trans.daftarPesanan) {
        cout << item.jumlah << " x " << item.menu.nama
             << " @Rp" << item.menu.harga << " = Rp" << item.subtotal();
        if (!item.catatan.empty()) {
            cout << " (Catatan: " << item.catatan << ")";
        }
        cout << "\n";
    }
    cout << "Total Bayar: Rp " << trans.totalBayar << "\n";
    cout << "Bayar via : " << trans.metodePembayaran << "\n";
    cout << "=========================================\n";
    
}

    void prosesPembayaran(Transaksi &trans) {
        cout << "\n--- PILIHAN METODE PEMBAYARAN ---\n";
        cout << "Total yang harus dibayar: Rp " << fixed << setprecision(0) << trans.totalBayar << "\n";
        cout << "1. Cash\n2. QRIS\n3. E-wallet\n4. Transfer Bank\n";
        int metode = inputAngkaDenganValidasi("Pilih metode pembayaran (1-4): ", 1, 4);

        switch (metode) {
        case 1: {
            trans.metodePembayaran = "Cash";
            double uangDiterima;
            int percobaan = 0;
            while (true) {
                if (percobaan >= maxInputPercobaan) {
                    cout << "Terlalu banyak input uang tunai salah. Pembayaran dibatalkan.\n";
                    trans.metodePembayaran = "Dibatalkan";
                    return;
                }
                cout << "Masukkan jumlah uang tunai diterima (Rp): ";
                if (!(cin >> uangDiterima)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid (bukan angka).\n";
                    percobaan++;
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (uangDiterima < trans.totalBayar) {
                    cout << "Uang tunai tidak cukup. Coba lagi.\n";
                    percobaan++;
                    continue;
                }
                cout << "Pembayaran berhasil! Kembalian: Rp " << fixed << setprecision(0) << (uangDiterima - trans.totalBayar) << "\n";
                break;
            }
            break;
        }
        case 2:
            trans.metodePembayaran = "QRIS";
            cout << "\n[=== QR CODE PEMBAYARAN ===]\n";
            cout << R"(
¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦
¦¦ _____ ¦¦ ¦¦¦ ¦¦ _____ ¦¦
¦¦ ¦   ¦ ¦¦ ¯¯¯ ¦¦ ¦   ¦ ¦¦
¦¦ ¦___¦ ¦¦ ¦¦¦ ¦¦ ¦___¦ ¦¦
¦¦_____¦ ¦¦ __¦ ¦¦_____¦ ¦¦
¦¦ __¯_  ¯¯ ¯¯ ¯ __¯_ ¯¯ ¦¦
¦¦ ¯_¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ __ ¦¦
¦¦ ¯¯_¦ _¯_¯ ¯_ _ ¯¦ ¯¯ ¦¦
¦¦ ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯ ¦¦
¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦

          (^?^)
     Bayar pakai QRIS
    Total: Rp )" << fixed << setprecision(0) << trans.totalBayar << R"(

  Silakan scan QR wajah lucu ini ??
 Tekan ENTER setelah pembayaran...
)";
            cin.ignore();
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Pembayaran berhasil via QRIS.\n";
            break;
    break;
        case 3:
            trans.metodePembayaran = "E-wallet";
            cout << "[Simulasi E-wallet] Silakan bayar melalui GoPay/OVO Rp " << trans.totalBayar << "\n";
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Pembayaran berhasil via E-wallet.\n";
            break;
        case 4:
            trans.metodePembayaran = "Transfer Bank";
            cout << "Transfer ke BCA 1234567890 (Soto Lenthok Pak B), sebesar Rp " << trans.totalBayar << "\n";
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Transfer akan diverifikasi manual.\n";
            break;
        }
    }
    
	void mintaRating(Transaksi& trans) {
    cout << "\n=== ULASAN PELANGGAN ===\n";
    int rating = inputAngkaDenganValidasi("Beri rating (1–5): ", 1, 5);
    string ulasan = inputString("Tulis ulasanmu: ");
    
    cout << "\nTerima kasih atas ulasannya!\n";
    cout << "Rating: " << rating << "/5\n";
    cout << "Ulasan: " << ulasan << "\n";
}

    void notifikasiPesananSiap() {
        cout << "\n=========================================\n";
        cout << "     PESANAN ANDA SUDAH SIAP! TERIMA KASIH\n";
        cout << "=========================================\n";
        this_thread::sleep_for(chrono::seconds(2));
    }

void cariTransaksiByNama() {
    string nama = inputString("Masukkan nama pelanggan: ");
    cout << "\n=== HASIL PENCARIAN BERDASARKAN NAMA ===\n";
    for (const auto& trans : riwayatTransaksi) {
        if (trans.namaPelanggan.find(nama) != string::npos) {
            cetakStruk(trans);
        }
    }
}

void kelolaPesananSementara(Transaksi& trans){
    while (true) {
        cout << "\n--- Daftar Pesanan Sementara ---\n";
        for (size_t i = 0; i < trans.daftarPesanan.size(); ++i) {
            const auto& item = trans.daftarPesanan[i];
            cout << i + 1 << ". " << item.menu.nama << " - " << item.jumlah << " porsi"
                 << " | Catatan: " << (item.catatan.empty() ? "-" : item.catatan) << "\n";
        }
        cout << "0. Selesai dan lanjutkan ke pembayaran\n";
        cout << "Pilih nomor item untuk ubah/hapus/tambah catatan: ";
        int pilih = inputAngkaDenganValidasi("", 0, (int)trans.daftarPesanan.size());

        if (pilih == 0) break;

        auto& itemDipilih = trans.daftarPesanan[pilih - 1];
        cout << "\n1. Ubah jumlah\n2. Hapus item\n3. Tambah/Ubah catatan\nPilih tindakan: ";
        int aksi = inputAngkaDenganValidasi("", 1, 3);

        if (aksi == 1) {
            int jml = inputAngkaDenganValidasi("Masukkan jumlah baru: ", 1, 100);
            itemDipilih.jumlah = jml;
        } else if (aksi == 2) {
            trans.daftarPesanan.erase(trans.daftarPesanan.begin() + (pilih - 1));
        } else if (aksi == 3) {
            string note = inputString("Masukkan catatan khusus: ");
            itemDipilih.catatan = note;
        }
    }
};

void tampilkanRingkasanPesanan(const Transaksi &trans) {
    double subtotal = 0.0;
    cout << "\n--- Rincian Pesanan Anda ---\n";
    cout << left << setw(25) << "Menu"
         << setw(10) << "Jumlah"
         << setw(15) << "Harga Satuan"
         << setw(15) << "Subtotal\n";
    cout << "------------------------------------------------------------\n";
    for (const auto &item : trans.daftarPesanan) {
        double sub = item.subtotal();
        subtotal += sub;
        cout << left
             << setw(25) << item.menu.nama
             << setw(10) << item.jumlah
             << "Rp " << setw(12) << item.menu.harga
             << "Rp " << setw(12) << sub << "\n";
    }
    cout << "------------------------------------------------------------\n";
    cout << "Subtotal Keseluruhan: Rp " << fixed << setprecision(0) << subtotal << "\n";

    if (trans.diskonDiterapkan) {
        cout << "Diskon " << (tarifDiskon * 100) << "% diterapkan\n";
        cout << "Total Bayar (Setelah Diskon): Rp " << fixed << setprecision(0) << trans.totalBayar << "\n";
    } else {
        cout << "Total Bayar: Rp " << fixed << setprecision(0) << trans.totalBayar << "\n";
        cout << "Pesan minimal Rp " << fixed << setprecision(0) << batasDiskon
             << " untuk dapat diskon " << (tarifDiskon * 100) << "%!\n";
    }
}

void cariTransaksiByKeyword() {
    string keyword = inputString("Masukkan kata kunci (nama pelanggan / menu): ");
    cout << "\n=== HASIL PENCARIAN BERDASARKAN KATA KUNCI ===\n";
    for (const auto& trans : riwayatTransaksi) {
        bool ditemukan = false;
        if (trans.namaPelanggan.find(keyword) != string::npos) {
            ditemukan = true;
        } else {
            for (const auto& item : trans.daftarPesanan) {
                if (item.menu.nama.find(keyword) != string::npos) {
                    ditemukan = true;
                    break;
                }
            }
        }
        if (ditemukan) {
            cetakStruk(trans);
        }
    }
}
    void simpanTransaksi(Transaksi &trans) {
    string tgl = getTanggalHariIni();
    trans.tanggal = tgl;
    for (const auto& item : trans.daftarPesanan) {
        kurangiStok(item.menu.nama, item.jumlah);
        catatPenjualanHarian(tgl, item.menu.nama, item.jumlah);
    }
    riwayatTransaksi.push_back(trans);
}

void simpanUlasan(const string& nama) {
    Ulasan u;
    cout << "\n--- ULASAN PELANGGAN ---\n";
    u.namaPelanggan = nama;
    u.rating = inputAngkaDenganValidasi("Rating (1–5): ", 1, 5);
    u.komentar = inputString("Komentar/Review: ");
    daftarUlasan.push_back(u);
    cout << "Terima kasih atas ulasannya!\n";
}

    void tampilkanLaporanHarian() {
    cout << "\n=== LAPORAN HARIAN ===\n";
    cout << "Jumlah Transaksi: " << riwayatTransaksi.size() << "\n";

    double bruto = 0, netto = 0;
    map<string, int> menuTerlaris;
    map<string, double> totalPerMetode;

    for (const auto &trans : riwayatTransaksi) {
        if (trans.metodePembayaran != "Dibatalkan") {
            netto += trans.totalBayar;
            totalPerMetode[trans.metodePembayaran] += trans.totalBayar;
            for (const auto &item : trans.daftarPesanan) {
                bruto += item.subtotal();
                menuTerlaris[item.menu.nama] += item.jumlah;
            }
        }
    }

    cout << "Pendapatan Bruto: Rp " << fixed << setprecision(0) << bruto << "\n";
    cout << "Pendapatan Netto: Rp " << fixed << setprecision(0) << netto << "\n";

    cout << "\n--- Pendapatan Per Metode Pembayaran ---\n";
    for (const auto& metode : totalPerMetode) {
        cout << metode.first << " : Rp " << fixed << setprecision(0) << metode.second << "\n";
    }

    cout << "\n--- Menu Terlaris Hari Ini ---\n";
    for (const auto &m : menuTerlaris) {
        cout << m.first << " : " << m.second << " porsi\n";
    }

    tampilkanStokHarian();
    tampilkanLaporanPenjualanPerMenu();
    simpanLaporanHarianKeFile();
	cout << "Laporan juga disimpan di file: laporan_harian_" << getTanggalHariIni() << ".txt\n";


    cout << "===========================================\n";
}

void tampilkanPendapatanPerMetode() {
    map<string, double> totalPerMetode;
    for (const auto& trans : riwayatTransaksi) {
        if (trans.metodePembayaran != "Dibatalkan") {
            totalPerMetode[trans.metodePembayaran] += trans.totalBayar;
        }
    }

    cout << "\n=== PENDAPATAN PER METODE PEMBAYARAN ===\n";
    for (const auto& metode : totalPerMetode) {
        cout << metode.first << " : Rp " << fixed << setprecision(0) << metode.second << "\n";
    }
}
void tampilkanMenuTerlarisHariIniSorted() {
    string tgl = getTanggalHariIni();
    cout << "\n=== MENU TERLARIS HARI INI (DIURUTKAN) ===\n";

    if (penjualanPerHari.count(tgl) == 0) {
        cout << "Belum ada penjualan hari ini.\n";
        return;
    }

    vector<pair<string, int>> dataSorted;
    for (const auto& item : penjualanPerHari[tgl]) {
        dataSorted.push_back(item);
    }

    // Bubble Sort descending berdasarkan jumlah penjualan
    for (size_t i = 0; i < dataSorted.size(); ++i) {
        for (size_t j = 0; j < dataSorted.size() - 1 - i; ++j) {
            if (dataSorted[j].second < dataSorted[j + 1].second) {
                swap(dataSorted[j], dataSorted[j + 1]);
            }
        }
    }

    for (const auto& item : dataSorted) {
        cout << item.first << " : " << item.second << " porsi\n";
    }
}

void tampilkanMenuTerlarisHariIni() {
    string tgl = getTanggalHariIni();
    cout << "\n=== MENU TERLARIS HARI INI (" << tgl << ") ===\n";
    if (penjualanPerHari.count(tgl) == 0) {
        cout << "Belum ada penjualan hari ini.\n";
        return;
    }

    const auto& dataHariIni = penjualanPerHari[tgl];
    for (const auto& item : dataHariIni) {
        cout << item.first << " : " << item.second << " porsi\n";
    }
}


    void kurangiStok(const string& namaMenu, int jumlah) {
    stokHarian[namaMenu] -= jumlah;
    }

    bool stokCukup(const string& namaMenu, int jumlah) {
        return stokHarian[namaMenu] >= jumlah;
    }

    void catatPenjualanHarian(const string& tanggal, const string& namaMenu, int jumlah) {
        penjualanPerHari[tanggal][namaMenu] += jumlah;
    }

    void inisialisasiStok() {
        for (const auto& item : menu) {
            stokHarian[item.nama] = 500; // default stok harian tiap menu
        }
    }

    // ... (fungsi lain tetap seperti sebelumnya)

    void tampilkanStokHarian() {
        cout << "\n=== SISA STOK HARIAN ===\n";
        for (const auto& s : stokHarian) {
            cout << s.first << " : " << s.second << " porsi tersisa\n";
        }
    }

    void tampilkanLaporanPenjualanPerMenu() {
        cout << "\n=== PENJUALAN PER MENU PER HARI ===\n";
        for (const auto& hari : penjualanPerHari) {
            cout << "Tanggal: " << hari.first << "\n";
            for (const auto& menu : hari.second) {
                cout << " - " << menu.first << " : " << menu.second << " porsi\n";
            }
            cout << "-----------------------------\n";
        }
    }
    
    void simpanLaporanHarianKeFile() {
    string tgl = getTanggalHariIni();
    string namaFile = "laporan_harian_" + tgl + ".txt";
    ofstream file(namaFile);

    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menulis laporan.\n";
        return;
    }

    file << "=== LAPORAN HARIAN (" << tgl << ") ===\n";
    file << "Jumlah Transaksi: " << riwayatTransaksi.size() << "\n";

    double bruto = 0, netto = 0;
    map<string, int> menuTerlaris;
    map<string, double> totalPerMetode;

    for (const auto &trans : riwayatTransaksi) {
        if (trans.metodePembayaran != "Dibatalkan") {
            netto += trans.totalBayar;
            totalPerMetode[trans.metodePembayaran] += trans.totalBayar;
            for (const auto &item : trans.daftarPesanan) {
                bruto += item.subtotal();
                menuTerlaris[item.menu.nama] += item.jumlah;
            }
        }
    }

    file << "Pendapatan Bruto: Rp " << bruto << "\n";
    file << "Pendapatan Netto: Rp " << netto << "\n\n";

    file << "--- Pendapatan Per Metode Pembayaran ---\n";
    for (const auto& metode : totalPerMetode) {
        file << metode.first << " : Rp " << metode.second << "\n";
    }

    file << "\n--- Menu Terlaris ---\n";
    for (const auto &m : menuTerlaris) {
        file << m.first << " : " << m.second << " porsi\n";
    }

    file << "\n--- Sisa Stok Harian ---\n";
    for (const auto& s : stokHarian) {
        file << s.first << " : " << s.second << " porsi tersisa\n";
    }

    file << "\n--- Penjualan Per Menu Per Hari ---\n";
    for (const auto& hari : penjualanPerHari) {
        file << "Tanggal: " << hari.first << "\n";
        for (const auto& menu : hari.second) {
            file << " - " << menu.first << " : " << menu.second << " porsi\n";
        }
        file << "-----------------------------\n";
    }

    file.close();
}


public:
	SistemPemesananSoto (){
    menu = {
    {"Soto Lenthok Reguler", 15000, "Makanan Berat", ""},
    {"Soto Lenthok Large", 20000, "Makanan Berat", ""},
    {"Soto Ayam", 15000, "Makanan Berat"},
	{"Soto Daging", 20000, "Makanan Berat"},
	{"Rawon", 20000, "Makanan Berat"},
	{"Pecel Komplit", 13000, "Makanan Berat"},
	{"Nasi Rames", 12000, "Makanan Berat"},
	{"Nasi Goreng Ayam", 15000, "Makanan Berat"},
	{"Nasi Goreng Spesial", 18000, "Makanan Berat"},
	{"Mie Ayam", 12000, "Makanan Berat"},
	{"Mie Ayam Bakso", 15000, "Makanan Berat"},
	{"Bakso Komplit", 15000, "Makanan Berat"},
	{"Bakso Urat", 17000, "Makanan Berat"},
	{"Ayam Goreng + Nasi + Sambal", 18000, "Makanan Berat"},
	{"Lele Goreng + Nasi + Lalapan", 15000, "Makanan Berat"},
	{"Gudeg Komplit", 17000, "Makanan Berat"},
	{"Ayam Bakar + Nasi + Lalapan", 20000, "Makanan Berat"},
	{"Nasi Lodeh + Tempe/Tahu", 13000, "Makanan Berat"},
	{"Tongseng Daging", 22000, "Makanan Berat"},
	{"Rica-rica Ayam Pedas", 18000, "Makanan Berat"},
	{"Oseng Mercon Daging", 22000, "Makanan Berat"},
	{"Nasi Campur Bali", 20000, "Makanan Berat"},

   {"Telur Puyuh Tusuk", 4000, "Lauk Tambahan"},
{"Usus Goreng", 5000, "Lauk Tambahan"},
{"Tempe Goreng", 3000, "Lauk Tambahan"},
{"Tahu Goreng", 3000, "Lauk Tambahan"},
{"Telur Dadar", 5000, "Lauk Tambahan"},
{"Telur Ceplok", 5000, "Lauk Tambahan"},
{"Ayam Suwir", 6000, "Lauk Tambahan"},
{"Paru Goreng", 8000, "Lauk Tambahan"},
{"Babat Goreng", 8000, "Lauk Tambahan"},
{"Empal Daging", 10000, "Lauk Tambahan"},
{"Perkedel Kentang", 4000, "Lauk Tambahan"},
{"Mendoan", 3000, "Lauk Tambahan"},
{"Kerupuk Udang", 2000, "Lauk Tambahan"},
{"Kerupuk Putih", 1000, "Lauk Tambahan"},
{"Sambal Goreng Kentang Ati", 7000, "Lauk Tambahan"},
{"Ikan Asin", 4000, "Lauk Tambahan"},

    
{"Kopi Tubruk", 8000, "Minuman", "Kafein"},
{"Kopi Hitam", 9000, "Minuman", "Kafein"},
{"Kopi Susu", 10000, "Minuman", "Kafein"},
{"Cappuccino", 12000, "Minuman", "Kafein"},
{"Kopi Espresso", 11000, "Minuman", "Kafein"},
{"Kopi Latte", 13000, "Minuman", "Kafein"},
{"Dalgona Coffee", 12000, "Minuman", "Kafein"},
{"Vietnam Drip", 12000, "Minuman", "Kafein"},
{"Americano", 11000, "Minuman", "Kafein"},
{"Affogato", 14000, "Minuman", "Kafein"},
{"Kopi Arabica", 10000, "Minuman", "Kafein"},
{"Kopi Robusta", 9000, "Minuman", "Kafein"},
{"Kopi Jahe", 10000, "Minuman", "Kafein"},
{"Kopi Susu Gula Aren", 12000, "Minuman", "Kafein"},
{"Es Kopi Susu", 11000, "Minuman", "Kafein"},
{"Kopi Mocha", 13000, "Minuman", "Kafein"},
{"Kopi Hazelnut", 13000, "Minuman", "Kafein"},
{"Caramel Macchiato", 14000, "Minuman", "Kafein"},
{"Flat White", 12000, "Minuman", "Kafein"},
{"Cold Brew Coffee", 12000, "Minuman", "Kafein"},
{"Kopi Aren Creamy", 13000, "Minuman", "Kafein"},
{"Iced Americano", 11000, "Minuman", "Kafein"},
{"Kopi Rum Butter", 15000, "Minuman", "Kafein"},
{"Espresso Double Shot", 13000, "Minuman", "Kafein"},

{"Es Jeruk", 6000, "Minuman", "Non-Kafein"},
{"Jeruk Hangat", 6000, "Minuman", "Non-Kafein"},
{"Susu Murni", 8000, "Minuman", "Non-Kafein"},
{"Susu Jahe", 9000, "Minuman", "Non-Kafein"},
{"Susu Coklat", 9000, "Minuman", "Non-Kafein"},
{"Susu Putih", 8000, "Minuman", "Non-Kafein"},
{"Susu Kedelai", 7000, "Minuman", "Non-Kafein"},
{"Susu Kurma", 10000, "Minuman", "Non-Kafein"},
{"Susu Soda", 10000, "Minuman", "Non-Kafein"},
{"Soda Gembira", 11000, "Minuman", "Non-Kafein"},
{"Susu Gula Aren", 9000, "Minuman", "Non-Kafein"},
{"Susu Jelly", 8000, "Minuman", "Non-Kafein"},
{"Susu Pandan", 8000, "Minuman", "Non-Kafein"},
{"Susu Melon", 8000, "Minuman", "Non-Kafein"},
{"Air Mineral", 4000, "Minuman", "Non-Kafein"},
{"Infused Water", 7000, "Minuman", "Non-Kafein"},
{"Es Kelapa Muda", 10000, "Minuman", "Non-Kafein"},
{"Kelapa Muda Hangat", 10000, "Minuman", "Non-Kafein"},
{"Es Campur", 11000, "Minuman", "Non-Kafein"},
{"Es Buah", 10000, "Minuman", "Non-Kafein"},
{"Es Doger", 10000, "Minuman", "Non-Kafein"},
{"Es Teler", 11000, "Minuman", "Non-Kafein"},
{"Es Alpukat", 12000, "Minuman", "Non-Kafein"},
{"Es Timun Serut", 8000, "Minuman", "Non-Kafein"},
{"Es Cincau", 8000, "Minuman", "Non-Kafein"},
{"Cincau Susu", 9000, "Minuman", "Non-Kafein"},
{"Es Blewah", 8000, "Minuman", "Non-Kafein"},
{"Es Kolang Kaling", 9000, "Minuman", "Non-Kafein"},
{"Es Kopyor", 10000, "Minuman", "Non-Kafein"},
{"Es Pisang Ijo", 11000, "Minuman", "Non-Kafein"},
{"Es Cendol", 8000, "Minuman", "Non-Kafein"},
{"Cendol Dawet", 9000, "Minuman", "Non-Kafein"},
{"Es Goyobod", 10000, "Minuman", "Non-Kafein"},
{"Es Serut", 7000, "Minuman", "Non-Kafein"},
{"Es Serut Buah", 8000, "Minuman", "Non-Kafein"},
{"Es Loli Buah", 5000, "Minuman", "Non-Kafein"},
{"Es Soda Buah", 10000, "Minuman", "Non-Kafein"},
{"Bajigur", 8000, "Minuman", "Non-Kafein"},
{"Bandrek", 8000, "Minuman", "Non-Kafein"},
{"Wedang Jahe", 7000, "Minuman", "Non-Kafein"},
{"Wedang Uwuh", 8000, "Minuman", "Non-Kafein"},
{"Wedang Secang", 8000, "Minuman", "Non-Kafein"},
{"Sarabba", 9000, "Minuman", "Non-Kafein"},
{"STMJ", 10000, "Minuman", "Non-Kafein"},
{"Jahe Susu", 9000, "Minuman", "Non-Kafein"},
{"Kunyit Asam", 8000, "Minuman", "Non-Kafein"},
{"Beras Kencur", 8000, "Minuman", "Non-Kafein"},
{"Temulawak", 8000, "Minuman", "Non-Kafein"},
{"Jus Alpukat", 11000, "Minuman", "Non-Kafein"},
{"Jus Mangga", 10000, "Minuman", "Non-Kafein"},
{"Jus Jeruk", 9000, "Minuman", "Non-Kafein"},
{"Jus Jambu", 9000, "Minuman", "Non-Kafein"},
{"Jus Melon", 9000, "Minuman", "Non-Kafein"},
{"Jus Buah Naga", 10000, "Minuman", "Non-Kafein"},
{"Jus Stroberi", 11000, "Minuman", "Non-Kafein"},
{"Jus Sirsak", 9000, "Minuman", "Non-Kafein"},
{"Jus Apel", 10000, "Minuman", "Non-Kafein"},
{"Jus Wortel", 9000, "Minuman", "Non-Kafein"},
{"Jus Tomat", 9000, "Minuman", "Non-Kafein"},
{"Jus Seledri", 9000, "Minuman", "Non-Kafein"},
{"Smoothie Pisang", 11000, "Minuman", "Non-Kafein"},
{"Smoothie Mangga", 11000, "Minuman", "Non-Kafein"},
{"Smoothie Stroberi", 12000, "Minuman", "Non-Kafein"},

{"Klepon", 5000, "Makanan", "Pencuci Mulut"},
{"Lemper", 5000, "Makanan", "Pencuci Mulut"},
{"Dadar Gulung", 5000, "Makanan", "Pencuci Mulut"},
{"Kue Lumpur", 6000, "Makanan", "Pencuci Mulut"},
{"Kue Cubit", 7000, "Makanan", "Pencuci Mulut"},
{"Kue Apem", 5000, "Makanan", "Pencuci Mulut"},
{"Kue Putu", 5000, "Makanan", "Pencuci Mulut"},
{"Serabi Kuah", 7000, "Makanan", "Pencuci Mulut"},
{"Serabi Solo", 7000, "Makanan", "Pencuci Mulut"},
{"Bolu Kukus", 6000, "Makanan", "Pencuci Mulut"},
{"Bolu Panggang", 7000, "Makanan", "Pencuci Mulut"},
{"Brownies Kukus", 8000, "Makanan", "Pencuci Mulut"},
{"Brownies Panggang", 9000, "Makanan", "Pencuci Mulut"},
{"Donat Coklat", 7000, "Makanan", "Pencuci Mulut"},
{"Donat Keju", 7000, "Makanan", "Pencuci Mulut"},
{"Donat Meses", 7000, "Makanan", "Pencuci Mulut"},
{"Martabak Mini", 8000, "Makanan", "Pencuci Mulut"},
{"Martabak Manis Keju", 12000, "Makanan", "Pencuci Mulut"},
{"Martabak Manis Coklat", 12000, "Makanan", "Pencuci Mulut"},
{"Martabak Manis Campur", 13000, "Makanan", "Pencuci Mulut"},
{"Pisang Coklat", 7000, "Makanan", "Pencuci Mulut"},
{"Pisang Keju", 8000, "Makanan", "Pencuci Mulut"},
{"Pisang Bakar Coklat Keju", 9000, "Makanan", "Pencuci Mulut"},
{"Roti Bakar Coklat", 9000, "Makanan", "Pencuci Mulut"},
{"Roti Bakar Keju", 9000, "Makanan", "Pencuci Mulut"},
{"Roti Bakar Coklat Keju", 10000, "Makanan", "Pencuci Mulut"},
{"Roti Bakar Green Tea", 10000, "Makanan", "Pencuci Mulut"},
{"Roti Maryam Coklat", 10000, "Makanan", "Pencuci Mulut"},
{"Roti Maryam Susu", 10000, "Makanan", "Pencuci Mulut"},
{"Roti Bakar Nutella", 13000, "Makanan", "Pencuci Mulut"},
{"Puding Coklat", 6000, "Makanan", "Pencuci Mulut"},
{"Puding Mangga", 6000, "Makanan", "Pencuci Mulut"},
{"Puding Buah Naga", 7000, "Makanan", "Pencuci Mulut"},
{"Puding Susu", 6000, "Makanan", "Pencuci Mulut"},
{"Jelly Buah", 7000, "Makanan", "Pencuci Mulut"},
{"Agar-agar Santan", 6000, "Makanan", "Pencuci Mulut"},
{"Salad Buah", 10000, "Makanan", "Pencuci Mulut"},
{"Salad Buah Keju", 11000, "Makanan", "Pencuci Mulut"},
{"Smoothie Bowl", 12000, "Makanan", "Pencuci Mulut"},
{"Es Krim Vanila", 8000, "Makanan", "Pencuci Mulut"},
{"Es Krim Stroberi", 8000, "Makanan", "Pencuci Mulut"},
{"Es Krim Coklat", 8000, "Makanan", "Pencuci Mulut"},
{"Es Pisang Ijo", 11000, "Makanan", "Pencuci Mulut"},
{"Es Campur", 11000, "Makanan", "Pencuci Mulut"},
{"Es Doger", 10000, "Makanan", "Pencuci Mulut"},
{"Es Teler", 11000, "Makanan", "Pencuci Mulut"},
{"Es Buah", 10000, "Makanan", "Pencuci Mulut"},
{"Es Cendol", 8000, "Makanan", "Pencuci Mulut"},
{"Cendol Dawet", 9000, "Makanan", "Pencuci Mulut"},
{"Es Goyobod", 10000, "Makanan", "Pencuci Mulut"},
{"Es Kopyor", 10000, "Makanan", "Pencuci Mulut"},
{"Es Kolang Kaling", 9000, "Makanan", "Pencuci Mulut"},
{"Kolak Pisang", 8000, "Makanan", "Pencuci Mulut"},
{"Kolak Ubi", 8000, "Makanan", "Pencuci Mulut"},
{"Kolak Campur", 9000, "Makanan", "Pencuci Mulut"},
{"Bubur Kacang Hijau", 7000, "Makanan", "Pencuci Mulut"},
{"Bubur Candil", 7000, "Makanan", "Pencuci Mulut"},
{"Bubur Sumsum", 7000, "Makanan", "Pencuci Mulut"},
{"Bubur Mutiara", 7000, "Makanan", "Pencuci Mulut"},
{"Bubur Kampiun", 9000, "Makanan", "Pencuci Mulut"},
{"Tape Ketan", 6000, "Makanan", "Pencuci Mulut"},
{"Tape Singkong", 6000, "Makanan", "Pencuci Mulut"},
{"Tape Goreng", 7000, "Makanan", "Pencuci Mulut"},
{"Singkong Thailand", 9000, "Makanan", "Pencuci Mulut"},
{"Singkong Keju", 8000, "Makanan", "Pencuci Mulut"},
{"Ubi Ungu Lumer", 8000, "Makanan", "Pencuci Mulut"},
{"Churros Coklat", 10000, "Makanan", "Pencuci Mulut"},
{"Banana Nugget", 9000, "Makanan", "Pencuci Mulut"},
{"Cheese Cake Slice", 12000, "Makanan", "Pencuci Mulut"},
{"Rainbow Cake Slice", 11000, "Makanan", "Pencuci Mulut"},
{"Red Velvet Slice", 11000, "Makanan", "Pencuci Mulut"},
{"Lava Cake", 13000, "Makanan", "Pencuci Mulut"},
{"Tiramisu Slice", 12000, "Makanan", "Pencuci Mulut"},

{"Sambal Terasi", 2000, "Aneka Sambal"},
{"Sambal Ijo", 2000, "Aneka Sambal"},
{"Sambal Bawang", 2000, "Aneka Sambal"},
{"Sambal Matah", 3000, "Aneka Sambal"},
{"Sambal Korek", 2000, "Aneka Sambal"},
{"Sambal Tumpang", 2500, "Aneka Sambal"},
{"Sambal Cibiuk", 2500, "Aneka Sambal"},
{"Sambal Pecel", 3000, "Aneka Sambal"},
{"Sambal Dabu-dabu", 3000, "Aneka Sambal"},
{"Sambal Kacang", 2000, "Aneka Sambal"},
{"Sambal Mangga", 3000, "Aneka Sambal"},
{"Sambal Pete", 3500, "Aneka Sambal"},
{"Sambal Tomat", 2000, "Aneka Sambal"},
{"Sambal Rica-rica", 3000, "Aneka Sambal"},
{"Sambal Oncom", 2500, "Aneka Sambal"},
{"Sambal Bajak", 2000, "Aneka Sambal"},
{"Sambal Belut", 4000, "Aneka Sambal"},
{"Sambal Kencur", 2500, "Aneka Sambal"},
{"Sambal Teri", 3500, "Aneka Sambal"},
{"Sambal Udang", 4000, "Aneka Sambal"},

{"Paket 1 - Nasi + Ayam Goreng + Es Teh", 17000, "Paket Hemat"},
{"Paket 2 - Nasi + Lele Goreng + Lalapan", 15000, "Paket Hemat"},
{"Paket 3 - Nasi + Telur Balado + Sayur Asem", 13000, "Paket Hemat"},
{"Paket 4 - Nasi + Ayam Geprek + Es Jeruk", 18000, "Paket Hemat"},
{"Paket 5 - Nasi + Ikan Nila Bakar + Sambal", 19000, "Paket Hemat"},
{"Paket 6 - Nasi + Tempe Tahu + Urap", 12000, "Paket Hemat"},
{"Paket 7 - Nasi Goreng + Telur Ceplok + Kerupuk", 16000, "Paket Hemat"},
{"Paket 8 - Mie Goreng + Ayam Suwir + Es Teh", 15000, "Paket Hemat"},
{"Paket 9 - Nasi + Ayam Kremes + Sambal", 17000, "Paket Hemat"},
{"Paket 10 - Nasi + Cumi Goreng Tepung + Sayur", 20000, "Paket Hemat"},
{"Paket 11 - Nasi + Sate Usus + Tahu Bacem", 13000, "Paket Hemat"},
{"Paket 12 - Nasi + Ati Ampela + Sayur Lodeh", 15000, "Paket Hemat"},
{"Paket 13 - Nasi + Dada Ayam Bakar + Sambal Matah", 18500, "Paket Hemat"},
{"Paket 14 - Nasi + Bebek Goreng + Lalapan", 22000, "Paket Hemat"},
{"Paket 15 - Nasi + Perkedel + Telur Puyuh", 14000, "Paket Hemat"},
{"Paket 16 - Nasi + Ayam Rica-Rica + Lalapan", 19000, "Paket Hemat"},
{"Paket 17 - Nasi + Pepes Ikan + Sayur Asem", 17000, "Paket Hemat"},
{"Paket 18 - Nasi + Rendang + Sayur Daun Singkong", 20000, "Paket Hemat"},
{"Paket 19 - Nasi + Daging Lada Hitam + Es Teh", 21000, "Paket Hemat"},
{"Paket 20 - Nasi + Telur Dadar + Oseng Tempe", 13000, "Paket Hemat"},
{"Paket 21 - Nasi + Sambal Goreng Kentang + Tahu", 12500, "Paket Hemat"},
{"Paket 22 - Nasi + Tahu Bacem + Kering Tempe", 12000, "Paket Hemat"},
{"Paket 23 - Nasi + Ayam Teriyaki + Es Lemon Tea", 20000, "Paket Hemat"},
{"Paket 24 - Nasi + Cumi Asin + Tumis Kangkung", 19000, "Paket Hemat"},
{"Paket 25 - Nasi + Ayam Bumbu Rujak + Urap", 18000, "Paket Hemat"},
{"Paket 26 - Nasi + Sate Ayam 5 tusuk + Kerupuk", 16000, "Paket Hemat"},
{"Paket 27 - Nasi + Tongseng Ayam + Teh Hangat", 19000, "Paket Hemat"},
{"Paket 28 - Nasi + Sosis Goreng + Telur Ceplok", 14000, "Paket Hemat"},
{"Paket 29 - Nasi + Mie Goreng + Nugget", 13000, "Paket Hemat"},
{"Paket 30 - Nasi + Ayam Kalasan + Es Teh", 17500, "Paket Hemat"},
{"Paket 31 - Nasi + Ayam Cabe Ijo + Tahu", 18500, "Paket Hemat"},
{"Paket 32 - Nasi + Bebek Bakar + Sambal Ijo", 23000, "Paket Hemat"},
{"Paket 33 - Nasi + Tahu Telur + Lontong", 15000, "Paket Hemat"},
{"Paket 34 - Nasi + Ayam Mentega + Acar", 19000, "Paket Hemat"},
{"Paket 35 - Nasi + Ikan Kembung Goreng + Sambal", 17000, "Paket Hemat"},
{"Paket 36 - Nasi + Ayam Saus Padang + Kerupuk", 20000, "Paket Hemat"},
{"Paket 37 - Nasi + Ayam Penyet + Sayur Urap", 18000, "Paket Hemat"},
{"Paket 38 - Nasi + Empal + Sambal Terasi", 22000, "Paket Hemat"},
{"Paket 39 - Nasi + Dendeng Balado + Tumis Buncis", 23000, "Paket Hemat"},
{"Paket 40 - Nasi + Ayam Pop + Lalapan", 18500, "Paket Hemat"},
{"Paket 41 - Nasi + Ayam Bakar Madu + Es Teh", 20000, "Paket Hemat"},
{"Paket 42 - Nasi + Telur Ceplok + Tumis Tauge", 12000, "Paket Hemat"},
{"Paket 43 - Nasi + Ayam Crispy + Sambal Matah", 18500, "Paket Hemat"},
{"Paket 44 - Nasi + Ikan Asin + Sambal Tomat", 13000, "Paket Hemat"},
{"Paket 45 - Nasi + Tahu Isi + Sayur Lodeh", 12500, "Paket Hemat"},
{"Paket 46 - Nasi + Ayam Katsu + Saus Teriyaki", 19500, "Paket Hemat"},
{"Paket 47 - Nasi + Telur Balado + Terong Goreng", 13500, "Paket Hemat"},
{"Paket 48 - Nasi + Ayam Serundeng + Es Teh", 17500, "Paket Hemat"},
{"Paket 49 - Nasi + Sate Telur Puyuh + Sayur Urap", 14000, "Paket Hemat"},
{"Paket 50 - Nasi + Ayam Kecap + Tumis Bayam", 18000, "Paket Hemat"},

{"Kids 1 - Nasi + Chicken Katsu Mini + Mayones", 14500, "Paket Menu Anak"},
{"Kids 2 - Nasi + Tahu Bakso + Saus Tomat", 13500, "Paket Menu Anak"},
{"Kids 3 - Nasi + Ayam Krispi Mini + Kentang", 15000, "Paket Menu Anak"},
{"Kids 4 - Nasi + Sate Ayam Mini + Kecap Manis", 14000, "Paket Menu Anak"},
{"Kids 5 - Nasi + Tumis Telur + Wortel Buncis", 12000, "Paket Menu Anak"},
{"Kids 6 - Nasi + Sosis Panggang + Jagung Rebus", 13000, "Paket Menu Anak"},
{"Kids 7 - Nasi + Tahu Isi Mini + Sayur Bening", 12000, "Paket Menu Anak"},
{"Kids 8 - Nasi + Ayam Saus Keju + Tumis Brokoli", 15000, "Paket Menu Anak"},
{"Kids 9 - Nasi + Abon Ayam + Kerupuk", 11500, "Paket Menu Anak"},
{"Kids 10 - Nasi + Kentang Goreng + Telur Dadar", 13000, "Paket Menu Anak"},
{"Kids 11 - Nasi + Bakwan Mini + Saus Pedas Manis", 12000, "Paket Menu Anak"},
{"Kids 12 - Nasi + Rolade Ayam + Sayur Sop", 14000, "Paket Menu Anak"},
{"Kids 13 - Nasi + Bola-Bola Tahu + Saus", 12500, "Paket Menu Anak"},
{"Kids 14 - Nasi + Kering Tempe Manis + Timun", 11500, "Paket Menu Anak"},
{"Kids 15 - Nasi + Ayam Bumbu Madu + Jagung Manis", 14500, "Paket Menu Anak"},
{"Kids 16 - Nasi + Mie Goreng Mini + Sosis Iris", 12000, "Paket Menu Anak"},
{"Kids 17 - Nasi + Bakso Goreng Mini + Saus Tomat", 13000, "Paket Menu Anak"},
{"Kids 18 - Nasi + Omelet Mini + Wortel Rebus", 12000, "Paket Menu Anak"},
{"Kids 19 - Nasi + Semur Telur + Kentang Kecil", 13000, "Paket Menu Anak"},
{"Kids 20 - Nasi + Tahu Goreng Kecap + Krupuk", 11500, "Paket Menu Anak"},
{"Kids 21 - Nasi + Chicken Nugget + Saus Pedas Manis", 14000, "Paket Menu Anak"},
{"Kids 22 - Nasi + Kari Ayam Mini + Wortel Kentang", 15000, "Paket Menu Anak"},
{"Kids 23 - Nasi + Terik Tahu + Sayur Bayam", 12500, "Paket Menu Anak"},
{"Kids 24 - Nasi + Perkedel Jagung + Tahu Kecap", 12000, "Paket Menu Anak"},
{"Kids 25 - Nasi + Nasi Kuning Mini + Telur Iris", 13000, "Paket Menu Anak"},
{"Kids 26 - Nasi + Bola Daging Mini + Saus BBQ", 14500, "Paket Menu Anak"},
{"Kids 27 - Nasi + Telur Puyuh Kecap + Tumis Sayur", 13500, "Paket Menu Anak"},
{"Kids 28 - Nasi + Kroket Kentang + Salad Mini", 13000, "Paket Menu Anak"},
{"Kids 29 - Nasi + Ayam Kukus Kecap + Timun", 14000, "Paket Menu Anak"},
{"Kids 30 - Nasi + Tahu Telur Mini + Sayur Bening", 12500, "Paket Menu Anak"},
{"Kids 31 - Nasi + Makaroni Saus Manis + Kerupuk", 13000, "Paket Menu Anak"},
{"Kids 32 - Nasi + Ayam Mini Sambal Tomat Manis", 14000, "Paket Menu Anak"},
{"Kids 33 - Nasi + Ikan Fillet Saus Tiram + Jagung", 15000, "Paket Menu Anak"},
{"Kids 34 - Nasi + Sosis Balut Telur + Acar", 13500, "Paket Menu Anak"},
{"Kids 35 - Nasi + Telur Kukus Mini + Sayur Sop", 13000, "Paket Menu Anak"},
{"Kids 36 - Nasi + Nugget Sayur + Kentang Rebus", 12500, "Paket Menu Anak"},
{"Kids 37 - Nasi + Bakso Sapi Mini + Saus Kecap", 13000, "Paket Menu Anak"},
{"Kids 38 - Nasi + Tahu Crispy + Saus Keju", 13500, "Paket Menu Anak"},
{"Kids 39 - Nasi + Ayam Mentega Mini + Krupuk", 14000, "Paket Menu Anak"},
{"Kids 40 - Nasi + Sate Telur Puyuh + Tumis Toge", 13500, "Paket Menu Anak"},
{"Kids 41 - Nasi + Ayam Opor Mini + Kering Kentang", 14500, "Paket Menu Anak"},
{"Kids 42 - Nasi + Sosis Crispy + Jagung Saus Mentega", 14000, "Paket Menu Anak"},
{"Kids 43 - Nasi + Pepes Tahu Mini + Lalapan", 12500, "Paket Menu Anak"},
{"Kids 44 - Nasi + Tumis Kacang Panjang + Telur Iris", 12000, "Paket Menu Anak"},
{"Kids 45 - Nasi + Udang Goreng Mini + Sambal Manis", 15000, "Paket Menu Anak"},
{"Kids 46 - Nasi + Ayam Bumbu Kecap + Sayur Sawi", 14000, "Paket Menu Anak"},
{"Kids 47 - Nasi + Kroket Sayur + Acar Mini", 13000, "Paket Menu Anak"},
{"Kids 48 - Nasi + Tumis Buncis + Ayam Suwir Mini", 13500, "Paket Menu Anak"},
{"Kids 49 - Nasi + Rolade Tahu + Tumis Labu", 13000, "Paket Menu Anak"},
{"Kids 50 - Nasi + Tahu Katsu + Mayones", 14000, "Paket Menu Anak"},


	};
	inisialisasiStok();
}

    void jalankan(const string& role) {
        cout << "===============================================\n";
        cout << "       SELAMAT DATANG DI SOTO LENTHOK PAK B!   \n";
        cout << "===============================================\n";

        while (true) {
            cout << "\n===== MENU UTAMA =====\n";
            cout << "1. Buat Pesanan Baru\n";
           if (role == "admin") {
   			 cout << "2. Lihat Laporan Harian\n";
    		cout << "3. Lihat Ulasan Pelanggan\n";
}

            cout << "0. Keluar\n";
            
            int maxOpsi = (role == "admin") ? 3 : 1;
            int pilih = inputAngkaDenganValidasi("Pilihan: ", 0, maxOpsi);

            if (pilih == 1) {
                Transaksi t = buatPesanan();
				if (t.daftarPesanan.empty()) {
    				cout << "Pesanan kosong.\n";
    				continue;
				}

				hitungTotalBayar(t); // hitung total dan simpan ke totalBayar
				tampilkanRingkasanPesanan(t); 
				cout <<"\n";// tampilkan detail pesanan ke user

				prosesPembayaran(t);

                if (t.metodePembayaran != "Dibatalkan") {
                	mintaRating(t);
                    notifikasiPesananSiap();
                    cout <<"\n";
                    if (inputAngkaDenganValidasi("Cetak struk? (1=Ya, 0=Tidak): ", 0, 1) == 1) {
                        cetakStruk(t);
                    }
                    simpanTransaksi(t);
					if (inputAngkaDenganValidasi("Ingin memberikan ulasan? (1=Ya, 0=Tidak): ", 0, 1) == 1) {
    				simpanUlasan(t.namaPelanggan.empty() ? "Anonim" : t.namaPelanggan);

			}

                }
            } else if (pilih == 2 && role == "admin" ){
    			cout << "\n=== MENU LAPORAN HARIAN ===\n";
    			cout << "1. Tampilkan semua transaksi\n";
    			cout << "2. Cari berdasarkan nama pelanggan\n";
    			cout << "3. Cari berdasarkan kata kunci (nama/menu)\n";
    			cout << "4. Lihat sisa stok harian\n";
    			cout << "5. Lihat pendapatan per metode pembayaran\n";
    			cout << "6. Lihat menu terlaris hari ini\n";
    			int subPilih = inputAngkaDenganValidasi("Pilih opsi: ", 1, 6);

    			if (subPilih == 1) {
        			for (const auto& trans : riwayatTransaksi) {
            		cetakStruk(trans);
            	}
        	} else if (subPilih == 2) {
        		cariTransaksiByNama();
    		} else if (subPilih == 3) {
        		cariTransaksiByKeyword();
    		} else if (subPilih == 4) {
        		tampilkanStokHarian();
    		} else if (subPilih == 5) {
       			 tampilkanPendapatanPerMetode();
    		} else if (subPilih == 6) {
        		tampilkanMenuTerlarisHariIniSorted();
    }
    } else if (pilih == 3 && role == "admin") {
    			cout << "\n=== ULASAN PELANGGAN ===\n";
    			if (daftarUlasan.empty()) {
        		cout << "Belum ada ulasan.\n";
    		} else {
        		for (const auto& u : daftarUlasan) {
            	cout << "Nama: " << u.namaPelanggan << "\n";
            	cout << "Rating: " << string(u.rating, '*') << " (" << u.rating << "/5)\n";
            	cout << "Komentar: " << u.komentar << "\n";
            	cout << "-----------------------------\n";
        }
    }
			} else if (pilih == 0) {
    		cout << "Terima kasih telah menggunakan sistem pemesanan!\n";
    		break;
			}
}
}
};

void registrasiUser() {
    string username, password;
    cout << "=== REGISTRASI USER BARU ===\n";
    cout << "Masukkan username baru: ";
    cin >> username;

    // Cek apakah username sudah ada
    for (const auto& user : daftarUser) {
        if (user.username == username) {
            cout << "Username sudah digunakan. Silakan coba lagi.\n";
            return;
        }
    }

    cout << "Masukkan password: ";
    cin >> password;

    daftarUser.push_back({username, password, "pelanggan"});
    cout << "Registrasi berhasil! Silakan login.\n";
}

int main() {
    SistemPemesananSoto app;

    string role;
    int pilih;
    do {
        cout << "\n=== SELAMAT DATANG DI SOTO LENTHOK PAK B ===\n";
        cout << "1. Login\n";
        cout << "2. Registrasi\n";
        cout << "0. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> pilih;

        if (pilih == 1) {
            role = login();
            app.jalankan(role);
        } else if (pilih == 2) {
            registrasiUser();
        } else if (pilih == 0) {
            cout << "Sampai jumpa!\n";
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 0);

    return 0;
    
}
