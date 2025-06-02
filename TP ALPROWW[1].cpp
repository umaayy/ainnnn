#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

struct MenuItem {
    string nama;
    double harga;
};

struct PesananItem {
    MenuItem menu;
    int jumlah;
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
};

class SistemPemesananSoto {
private:
    vector<MenuItem> menu;
    vector<Transaksi> riwayatTransaksi;

    const double tarifDiskon = 0.10;
    const double batasDiskon = 50000.0;
    const int maxInputPercobaan = 3;

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

    Transaksi buatPesanan() {
        Transaksi trans;
        trans.daftarPesanan.clear();

        cout << "\n--- FORM PEMESANAN BARU ---\n";
        trans.namaPelanggan = inputString("Masukkan nama pelanggan (opsional, tekan Enter jika kosong): ");

        while (true) {
            tampilkanMenu();
            int pilihanMenu = inputAngkaDenganValidasi("Pilih nomor menu (0 untuk selesai): ", 0, (int)menu.size());
            if (pilihanMenu == 0) {
                break;
            }

            int jumlahPesan = inputAngkaDenganValidasi("Masukkan jumlah porsi/item (min 1): ", 1, 100);

            PesananItem itemBaru;
            itemBaru.menu = menu[pilihanMenu - 1];
            itemBaru.jumlah = jumlahPesan;

            bool sudahAda = false;
            for (auto &itemLama : trans.daftarPesanan) {
                if (itemLama.menu.nama == itemBaru.menu.nama) {
                    itemLama.jumlah += jumlahPesan;
                    sudahAda = true;
                    break;
                }
            }
            if (!sudahAda) {
                trans.daftarPesanan.push_back(itemBaru);
            }

            cout << "Berhasil menambahkan " << jumlahPesan << " x " << itemBaru.menu.nama << " ke pesanan.\n";

            int tambahLagi = inputAngkaDenganValidasi("Ingin memesan menu lain? (1=Ya, 0=Tidak): ", 0, 1);
            if (tambahLagi == 0) {
                break;
            }
        }

        double subtotal = 0.0;
        cout << "\n--- Rincian Pesanan Anda ---\n";
        cout << left << setw(25) << "Menu"
             << setw(10) << "Jumlah"
             << setw(15) << "Harga Satuan"
             << setw(15) << "Subtotal\n";
        cout << "------------------------------------------------------------\n";
        for (auto &item : trans.daftarPesanan) {
            double sub = item.subtotal();
            subtotal += sub;
            cout << left
                 << setw(25) << item.menu.nama
                 << setw(10) << item.jumlah
                 << "Rp " << setw(12) << fixed << setprecision(0) << item.menu.harga
                 << "Rp " << setw(12) << fixed << setprecision(0) << sub << "\n";
        }
        cout << "------------------------------------------------------------\n";
        cout << "Subtotal Keseluruhan: Rp " << fixed << setprecision(0) << subtotal << "\n";

        if (subtotal >= batasDiskon) {
            trans.diskonDiterapkan = true;
            trans.totalBayar = subtotal * (1 - tarifDiskon);
            cout << "Selamat! Anda mendapatkan diskon " << (tarifDiskon * 100) << "%!\n";
            cout << "Total Bayar (Setelah Diskon): Rp " << fixed << setprecision(0) << trans.totalBayar << "\n";
        } else {
            trans.totalBayar = subtotal;
            cout << "Total Bayar: Rp " << fixed << setprecision(0) << trans.totalBayar << "\n";
            cout << "Pesan minimal Rp " << fixed << setprecision(0) << batasDiskon << " untuk dapat diskon "
                 << (tarifDiskon * 100) << "%!\n";
        }

        return trans;
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
            cout << "[Simulasi QRIS] Silakan scan dan bayar Rp " << trans.totalBayar << "\n";
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Pembayaran berhasil via QRIS.\n";
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

    void notifikasiPesananSiap() {
        cout << "\n=========================================\n";
        cout << "     PESANAN ANDA SUDAH SIAP! TERIMA KASIH\n";
        cout << "=========================================\n";
        this_thread::sleep_for(chrono::seconds(2));
    }

    void cetakStruk(const Transaksi &trans) {
        cout << "\n=========== STRUK PEMESANAN ===========\n";
        cout << "Tanggal/Waktu: " << __DATE__ << " " << __TIME__ << "\n";
        if (!trans.namaPelanggan.empty()) {
            cout << "Nama Pelanggan : " << trans.namaPelanggan << "\n";
        }
        cout << "----------------------------------------\n";
        for (const auto &item : trans.daftarPesanan) {
            cout << item.jumlah << " x " << item.menu.nama
                 << " @Rp" << item.menu.harga << " = Rp" << item.subtotal() << "\n";
        }
        if (trans.diskonDiterapkan) {
            cout << "Diskon " << (tarifDiskon * 100) << "% diterapkan\n";
        }
        cout << "Total Bayar: Rp " << trans.totalBayar << "\n";
        cout << "Bayar via : " << trans.metodePembayaran << "\n";
        cout << "=========================================\n";
    }

    void simpanTransaksi(const Transaksi &trans) {
        riwayatTransaksi.push_back(trans);
    }

    void tampilkanLaporanHarian() {
        cout << "\n=== LAPORAN HARIAN ===\n";
        cout << "Jumlah Transaksi: " << riwayatTransaksi.size() << "\n";

        double bruto = 0, netto = 0;
        map<string, int> menuTerlaris;

        for (const auto &trans : riwayatTransaksi) {
            if (trans.metodePembayaran != "Dibatalkan") {
                netto += trans.totalBayar;
                for (const auto &item : trans.daftarPesanan) {
                    bruto += item.subtotal();
                    menuTerlaris[item.menu.nama] += item.jumlah;
                }
            }
        }

        cout << "Pendapatan Bruto: Rp " << bruto << "\n";
        cout << "Pendapatan Netto: Rp " << netto << "\n";

        cout << "--- Menu Terlaris ---\n";
        for (const auto &m : menuTerlaris) {
            cout << m.first << " : " << m.second << " porsi\n";
        }
        cout << "=========================\n";
    }

public:
    SistemPemesananSoto() {
        menu = {
            {"Soto Lenthok Reguler", 15000},
            {"Soto Lenthok Large", 20000},
            {"Soto Lenthok Spesial", 25000},
            {"Nasi Putih", 5000},
            {"Es Teh Manis", 5000},
            {"Es Jeruk", 7000},
            {"Kerupuk Udang", 3000},
            {"Sate Telur Puyuh", 4000}
        };
    }

    void jalankan() {
        cout << "===============================================\n";
        cout << "       SELAMAT DATANG DI SOTO LENTHOK PAK B!   \n";
        cout << "===============================================\n";

        while (true) {
            cout << "\n===== MENU UTAMA =====\n";
            cout << "1. Buat Pesanan Baru\n";
            cout << "2. Lihat Laporan Harian\n";
            cout << "0. Keluar\n";
            int pilih = inputAngkaDenganValidasi("Pilihan: ", 0, 2);

            if (pilih == 1) {
                Transaksi t = buatPesanan();
                if (t.daftarPesanan.empty()) {
                    cout << "Pesanan kosong.\n";
                    continue;
                }
                prosesPembayaran(t);
                if (t.metodePembayaran != "Dibatalkan") {
                    notifikasiPesananSiap();
                    if (inputAngkaDenganValidasi("Cetak struk? (1=Ya, 0=Tidak): ", 0, 1) == 1) {
                        cetakStruk(t);
                    }
                    simpanTransaksi(t);
                }
            } else if (pilih == 2) {
                tampilkanLaporanHarian();
            } else {
                cout << "Terima kasih! Sampai jumpa.\n";
                break;
            }
        }
    }
};

int main() {
    SistemPemesananSoto app;
    app.jalankan();
    return 0;
}

