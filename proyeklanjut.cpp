/*
  Sistem Pemesanan Tiket - VERSI SEMPURNA (Vector & Linked List)
  Fitur Baru:
  - Menggunakan std::vector (Array Dinamis) untuk Rute dan User.
  - Menggunakan Linked List untuk Riwayat Pemesanan (Booking).
  - Penambahan fitur Pembatalan Pesanan (Delete Node Linked List).
  - Manajemen Transportasi disatukan dalam std::vector.

  Penulis: ChatGPT (Nadia request)
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <limits>
#include <vector> // Array Dinamis
#include <algorithm>

using namespace std;

// ======= CLASS Route =======
class Route {
private:
    string tujuan;
    int harga;
    bool aktif;
public:
    Route() : tujuan(""), harga(0), aktif(false) {}
    Route(const string &t, int h) : tujuan(t), harga(h), aktif(true) {}

    void setRoute(const string &t, int h) { tujuan = t; harga = h; aktif = true; }
    void deactivate() { aktif = false; }
    bool isActive() const { return aktif; }
    string getTujuan() const { return tujuan; }
    int getHarga() const { return harga; }
};

// ======= CLASS TransportasiManager (Menggunakan std::vector) =======
class TransportasiManager {
private:
    string jenis;
    // Array Dinamis untuk Rute
    std::vector<Route> routes; 
public:
    TransportasiManager() : jenis("") {}
    TransportasiManager(const string &j) : jenis(j) {}

    string getJenis() const { return jenis; }

    void addRoute(const string &tujuan, int harga) {
        routes.emplace_back(tujuan, harga); 
    }

    bool editRoute(int idx, const string &tujuan, int harga) {
        if (idx < 0 || idx >= routes.size() || !routes[idx].isActive()) return false;
        routes[idx].setRoute(tujuan, harga);
        return true;
    }

    bool removeRoute(int idx) {
        if (idx < 0 || idx >= routes.size() || !routes[idx].isActive()) return false;
        routes[idx].deactivate();
        return true;
    }

    void displayRoutes() const {
        cout << "\nDaftar Rute (" << jenis << "):\n";
        cout << "-------------------------------------------------\n";
        cout << setw(5) << "No" << setw(30) << "Tujuan" << setw(15) << "Harga (Rp)" << "\n";
        int shown = 0;
        for (size_t i = 0; i < routes.size(); i++) {
            if (routes[i].isActive()) {
                cout << setw(5) << (i + 1) << setw(30) << routes[i].getTujuan() << setw(15) << routes[i].getHarga() << "\n";
                shown++;
            }
        }
        if (shown == 0) cout << "(Tidak ada rute aktif)\n";
    }

    size_t getCount() const { return routes.size(); }
    const std::vector<Route>& getRouteArray() const { return routes; }

    bool isValidIndex(int idx) const {
        if (idx < 0 || idx >= routes.size()) return false;
        return routes[idx].isActive();
    }

    Route getRoute(int idx) const { return routes[idx]; }
};

// ======= CLASS User (Disimpan di vector) =======
class User {
private:
    string username;
    string password;
    bool aktif;
public:
    User() : username(""), password(""), aktif(false) {}
    User(const string &u, const string &p) : username(u), password(p), aktif(true) {}

    void setUser(const string &u, const string &p) { username = u; password = p; aktif = true; }
    bool isActive() const { return aktif; }
    string getUsername() const { return username; }
    bool checkPassword(const string &p) const { return password == p; }
};

// ======= CLASS Booking (Data) =======
class Booking {
private:
    static int nextBookingId;
    int id; // ID Unik untuk pembatalan
    string pemesan;
    string jenisTransport;
    string tujuan;
    int jumlahTiket;
    int hargaSatuan;
    int total;
public:
    Booking() : id(0), pemesan(""), jenisTransport(""), tujuan(""), jumlahTiket(0), hargaSatuan(0), total(0) {}

    void setBooking(const string &p, const string &j, const string &t, int jt, int hs) {
        id = nextBookingId++; // Set ID unik
        pemesan = p; jenisTransport = j; tujuan = t; jumlahTiket = jt; hargaSatuan = hs; total = jt * hs;
    }

    void showBooking() const {
        cout << "\n========================================" << "\n";
        cout << "ID Pesanan           : " << id << "\n"; // Tampilkan ID
        cout << "Nama Pemesan         : " << pemesan << "\n";
        cout << "Jenis Transportasi   : " << jenisTransport << "\n";
        cout << "Tujuan               : " << tujuan << "\n";
        cout << "Jumlah Tiket         : " << jumlahTiket << "\n";
        cout << "Harga Satuan         : Rp " << hargaSatuan << "\n";
        cout << "Total (sebelum diskon): Rp " << total << "\n";
    }

    int getId() const { return id; }
    int getTotal() const { return total; }
    int getJumlahTiket() const { return jumlahTiket; }
};
int Booking::nextBookingId = 1001; // Mulai ID dari 1001

// ======= CLASS BookingNode (Node Linked List) =======
class BookingNode {
public:
    Booking data;
    BookingNode* next;

    BookingNode(const Booking& b) : data(b), next(nullptr) {}
};


// ======= Helper: Input Utility & Diskon Rekursif =======
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string &prompt, int min = 0, int max = numeric_limits<int>::max()) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            if (x >= min && x <= max) break;
            cout << "Input harus antara " << min << " dan " << max << ".\n";
        } else {
            cout << "Input tidak valid, masukkan angka.\n";
            clearInput();
        }
        clearInput();
    }
    clearInput();
    return x;
}

string readLine(const string &prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}

// Diskon rekursif
int applyRecursiveDiscount(int total, int groups) {
    if (groups <= 0) return total;
    int discounted = total - (int)(total * 0.05);
    return applyRecursiveDiscount(discounted, groups - 1);
}

int calculateTotalAfterDiscount(int total, int jumlahTiket) {
    int groups = jumlahTiket / 3;
    if (groups <= 0) return total;
    return applyRecursiveDiscount(total, groups);
}

// ======= SISTEM UTAMA =======
class SistemPemesanan {
private:
    // Vector untuk menampung semua jenis transportasi (Perapian OOP)
    std::vector<TransportasiManager> managers;

    // Array Dinamis untuk User
    std::vector<User> users;

    // Linked List untuk Riwayat Pemesanan
    BookingNode* firstBooking; 
    int bookingCount; 

    const string adminUser = "admin";
    const string adminPass = "12345";

public:
    SistemPemesanan() {
        firstBooking = nullptr; 
        bookingCount = 0;
        seedData();
    }
    
    // Destructor untuk membersihkan Linked List
    ~SistemPemesanan() {
        BookingNode* current = firstBooking;
        while (current != nullptr) {
            BookingNode* next = current->next;
            delete current;
            current = next;
        }
    }


    void seedData() {
        // Inisialisasi managers (Perapian OOP)
        managers.emplace_back("Pesawat");
        managers.emplace_back("Kereta");
        managers.emplace_back("Bus");

        // Seed Rute
        managers[0].addRoute("Jakarta - Bali", 1500000);
        managers[0].addRoute("Jakarta - Surabaya", 1200000);
        managers[1].addRoute("Bandung - Yogyakarta", 350000);
        managers[1].addRoute("Jakarta - Surabaya", 500000);
        managers[2].addRoute("Jakarta - Bandung", 150000);
        managers[2].addRoute("Jakarta - Semarang", 250000);

        // Seed 1 user contoh (Vector)
        users.emplace_back("user1", "password"); 
    }

    void mainMenu() {
        int pilihan;
        do {
            system("cls");
            cout << "=========================================\n";
            cout << "    SISTEM PEMESANAN TIKET TRANSPORTASI    \n";
            cout << "=========================================\n";
            cout << "1. Login Admin\n";
            cout << "2. Login User\n";
            cout << "3. Register User\n";
            cout << "4. Lihat Semua Rute\n";
            cout << "5. Lihat Riwayat Pemesanan\n";
            cout << "6. Keluar\n";
            cout << "-----------------------------------------\n";
            pilihan = readInt("Pilih menu: ", 1, 6);

            switch (pilihan) {
                case 1: adminLogin(); break;
                case 2: userLogin(); break;
                case 3: registerUser(); break;
                case 4: displayAllRoutes(); getch(); break;
                case 5: displayAllBookings(true); getch(); break; // Tampilkan ID untuk Pembatalan
                case 6: cout << "Terima kasih!\n"; break;
                default: cout << "Pilihan tidak valid.\n"; getch();
            }
        } while (pilihan != 6);
    }

    // Fungsi utilitas untuk mendapatkan manager
    TransportasiManager* getManager(int t) {
        if (t < 1 || t > managers.size()) return nullptr;
        return &managers[t - 1];
    }
    
    // ===== Admin =====
    void adminLogin() {
        // ... (sama)
        system("cls");
        cout << "--- Login Admin ---\n";
        string u = readLine("Username: ");
        string p = readLine("Password: ");
        if (u == adminUser && p == adminPass) {
            cout << "Login admin berhasil.\n"; getch(); adminMenu();
        } else {
            cout << "Login admin gagal.\n"; getch();
        }
    }

    void adminMenu() {
        int pilihan;
        do {
            system("cls");
            cout << "--- Menu Admin ---\n";
            cout << "1. Tambah Rute\n";
            cout << "2. Edit Rute\n";
            cout << "3. Hapus Rute\n";
            cout << "4. Lihat Rute (per jenis)\n";
            cout << "5. Kembali\n";
            pilihan = readInt("Pilih: ", 1, 5);
            switch (pilihan) {
                case 1: adminAddRoute(); break;
                case 2: adminEditRoute(); break;
                case 3: adminRemoveRoute(); break;
                case 4: displayRoutesByTypeMenu(); getch(); break;
                case 5: break;
                default: cout << "Pilihan tidak valid."; getch();
            }
        } while (pilihan != 5);
    }

    void adminAddRoute() {
        system("cls");
        cout << "--- Tambah Rute ---\n";
        cout << "1. Pesawat\n2. Kereta\n3. Bus\n";
        int t = readInt("Pilih jenis: ", 1, 3);
        TransportasiManager *mgr = getManager(t);
        if (mgr == nullptr) { cout << "Jenis tidak valid.\n"; getch(); return; }

        string tujuan = readLine("Tujuan (contoh: Jakarta - Bali): ");
        int harga = readInt("Harga (Rp): ", 1);
        mgr->addRoute(tujuan, harga);
        cout << "Rute berhasil ditambahkan.\n";
        getch();
    }
    
    void adminEditRoute() {
        system("cls");
        cout << "--- Edit Rute ---\n";
        cout << "1. Pesawat\n2. Kereta\n3. Bus\n";
        int t = readInt("Pilih jenis: ", 1, 3);
        TransportasiManager *mgr = getManager(t);
        if (mgr == nullptr) { cout << "Jenis tidak valid."; getch(); return; }

        mgr->displayRoutes();
        int idx = readInt("Masukkan nomor rute yang ingin diubah: ", 1, mgr->getCount()) - 1;
        if (!mgr->isValidIndex(idx)) { cout << "Index tidak valid."; getch(); return; }
        string tujuan = readLine("Tujuan baru: ");
        int harga = readInt("Harga baru: ", 1);
        if (mgr->editRoute(idx, tujuan, harga)) cout << "Rute berhasil diubah.\n"; else cout << "Gagal mengubah rute.\n";
        getch();
    }

    void adminRemoveRoute() {
        system("cls");
        cout << "--- Hapus Rute ---\n";
        cout << "1. Pesawat\n2. Kereta\n3. Bus\n";
        int t = readInt("Pilih jenis: ", 1, 3);
        TransportasiManager *mgr = getManager(t);
        if (mgr == nullptr) { cout << "Jenis tidak valid."; getch(); return; }

        mgr->displayRoutes();
        int idx = readInt("Masukkan nomor rute yang ingin dihapus: ", 1, mgr->getCount()) - 1;
        if (!mgr->isValidIndex(idx)) { cout << "Index tidak valid."; getch(); return; }
        if (mgr->removeRoute(idx)) cout << "Rute berhasil dihapus (dinonaktifkan).\n"; else cout << "Gagal menghapus rute.\n";
        getch();
    }


    // ===== User & Booking Flow =====
    void registerUser() {
        system("cls");
        cout << "--- Register User ---\n";
        string u = readLine("Username: ");
        string p = readLine("Password: ");
        
        for (const auto& user : users) {
            if (user.getUsername() == u) { 
                cout << "Username sudah ada.\n"; getch(); return; 
            }
        }
        
        users.emplace_back(u, p);
        cout << "Pendaftaran berhasil. Silakan login.\n"; getch();
    }

    void userLogin() {
        system("cls");
        cout << "--- Login User ---\n";
        string u = readLine("Username: ");
        string p = readLine("Password: ");
        int idx = -1;
        
        for (size_t i = 0; i < users.size(); i++) {
            if (users[i].isActive() && users[i].getUsername() == u && users[i].checkPassword(p)) { 
                idx = i; break; 
            }
        }
        
        if (idx == -1) { cout << "Login gagal.\n"; getch(); return; }
        cout << "Login sukses.\n"; getch(); userMenu(users[idx].getUsername());
    }

    void userMenu(const string &username) {
        int pilihan;
        do {
            system("cls");
            cout << "--- Menu User (" << username << ") ---\n";
            cout << "1. Pesan Tiket\n";
            cout << "2. Batalkan Pesanan (Linked List)\n";
            cout << "3. Lihat Riwayat Pemesanan\n";
            cout << "4. Logout\n";
            pilihan = readInt("Pilih: ", 1, 4);
            switch (pilihan) {
                case 1: userBookFlow(username); break;
                case 2: cancelBookingFlow(); break; // Fitur Pembatalan
                case 3: displayAllBookings(false); getch(); break;
                case 4: break;
                default: cout << "Pilihan tidak valid."; getch();
            }
        } while (pilihan != 4);
    }
    
    // Flow pembatalan pesanan (menggunakan Linked List)
    void cancelBookingFlow() {
        system("cls");
        if (bookingCount == 0) {
            cout << "Tidak ada pesanan untuk dibatalkan.\n"; getch(); return;
        }
        displayAllBookings(true);
        int idToCancel = readInt("Masukkan ID Pesanan yang ingin dibatalkan: ", 1001);

        if (removeBookingNode(idToCancel)) {
            cout << "\nPesanan dengan ID " << idToCancel << " berhasil dibatalkan!\n";
        } else {
            cout << "\nError: ID Pesanan tidak ditemukan atau pembatalan gagal.\n";
        }
        getch();
    }

    // Fungsi penghapusan node pada Linked List
    bool removeBookingNode(int id) {
        if (firstBooking == nullptr) return false;

        // Kasus: Node yang dihapus adalah node pertama (head)
        if (firstBooking->data.getId() == id) {
            BookingNode* temp = firstBooking;
            firstBooking = firstBooking->next;
            delete temp;
            bookingCount--;
            return true;
        }

        // Kasus: Node yang dihapus di tengah atau akhir
        BookingNode* current = firstBooking;
        while (current->next != nullptr) {
            if (current->next->data.getId() == id) {
                BookingNode* temp = current->next;
                current->next = current->next->next; // Bypass node yang dihapus
                delete temp;
                bookingCount--;
                return true;
            }
            current = current->next;
        }
        return false; // ID tidak ditemukan
    }

    void userBookFlow(const string &username) {
        system("cls");
        cout << "--- Pemesanan Tiket ---\n";
        cout << "Pilih Jenis Transportasi:\n";
        cout << "1. Pesawat\n2. Kereta\n3. Bus\n";
        int t = readInt("Pilih: ", 1, 3);
        TransportasiManager *mgr = getManager(t);
        if (mgr == nullptr) { cout << "Jenis tidak valid."; getch(); return; }

        mgr->displayRoutes();
        int idx = readInt("Masukkan nomor rute: ", 1, mgr->getCount()) - 1;
        if (!mgr->isValidIndex(idx)) { cout << "Rute tidak valid."; getch(); return; }
        Route r = mgr->getRoute(idx);
        int jumlah = readInt("Jumlah tiket: ", 1);

        // Buat booking
        Booking b;
        string namaPemesan = readLine("Masukkan nama pemesan: ");
        b.setBooking(namaPemesan, mgr->getJenis(), r.getTujuan(), jumlah, r.getHarga());
        
        // ... (tampilkan struk, hitung diskon)
        system("cls");
        cout << "--- STRUK PEMESANAN ---\n";
        b.showBooking();
        int total = b.getTotal();
        int totalAfter = calculateTotalAfterDiscount(total, b.getJumlahTiket());
        if (totalAfter < total) {
            cout << "Anda mendapatkan diskon bertingkat berdasarkan jumlah tiket!\n";
            cout << "Total setelah diskon: Rp " << totalAfter << "\n";
        } else {
            cout << "Tidak ada diskon untuk pesanan ini.\n";
        }
        
        string konfirm = readLine("Konfirmasi pesanan? (y/n): ");
        if (konfirm == "y" || konfirm == "Y") {
            // Operasi penyisipan Linked List di akhir
            BookingNode* newNode = new BookingNode(b);
            if (firstBooking == nullptr) {
                firstBooking = newNode;
            } else {
                BookingNode* current = firstBooking;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }
            bookingCount++;
            cout << "Pemesanan berhasil! (Disimpan di Linked List)\n";
        } else {
            cout << "Pemesanan dibatalkan.\n";
        }
        getch();
    }

    // ===== Utility display/search =====
    void displayAllRoutes() {
        system("cls");
        cout << "--- Semua Rute Tersedia ---\n";
        for (const auto& mgr : managers) {
            mgr.displayRoutes();
        }
    }
    
    void displayRoutesByTypeMenu() {
        system("cls");
        cout << "1. Pesawat\n2. Kereta\n3. Bus\n";
        int t = readInt("Pilih jenis: ", 1, 3);
        TransportasiManager *mgr = getManager(t);
        if (mgr != nullptr) mgr->displayRoutes();
        else cout << "Jenis tidak valid.\n";
    }

    void displayAllBookings(bool showId) {
        system("cls");
        cout << "--- Riwayat Pemesanan (Total: " << bookingCount << ") ---\n";
        if (bookingCount == 0) { cout << "Belum ada pemesanan.\n"; return; }
        
        // Operasi traversi Linked List
        BookingNode* current = firstBooking;
        int i = 0;
        while (current != nullptr) {
            cout << "\nPesanan ke-" << (++i) << ":\n";
            Booking b = current->data;
            
            b.showBooking();
            int tot = b.getTotal();
            int totAfter = calculateTotalAfterDiscount(tot, b.getJumlahTiket());
            if (totAfter < tot) cout << "Total setelah diskon: Rp " << totAfter << "\n";
            
            current = current->next;
        }
    }
};

int main() {
    SistemPemesanan sys;
    sys.mainMenu();
    return 0;
}
