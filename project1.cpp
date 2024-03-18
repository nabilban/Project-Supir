#include <iostream>
#include <string>

using namespace std;
// Model data construct
struct Date
{
    int tanggal;
    int bulan;
    int tahun;
};
struct DataSupir
{
    string platnomor;
    string id;
    string nama;
    string alamat;
    Date tanggalLahir;
    char jenisKelamin;
    string noHp;
    DataSupir *next;
    DataSupir *prev;
};
struct Order
{
    string id;
    string nama;
    string supir;
    string platNomor;
    string tujuan;
    Order *pNext;
};

// Global variable to store the driver data
DataSupir *kepala;
DataSupir *ekor;
DataSupir *head = nullptr; // saat ini

Order *proses = nullptr;
Order *front = nullptr;
Order *rear = nullptr;

// Function prototype
void membersihkanConsole();
void hapusSemuaSopir(DataSupir *head);
string IdGenerator(const string &nama, char jenisKelamin, const Date &tanggalLahir);
bool isIdExist(const string &id);
void TambahDataSupir();
void LihatDataSupir();
void EditDataSupir();
void HapusDataSupir();
void AdminPriviliage();
void UserPrivilage();
void membersihkanConsole();

string generateId(const string &nama,
                  char jenisKelamin,
                  const Date &tanggalLahir);

bool isIdExist(const string &id);

void enqueueOrder(const string &id,
                  const string &nama,
                  const string &supir,
                  const string &platNomor,
                  const string &tujuan);

void dequeueOrder();
int hitungTotalSopir();
void orderTaxi();
void prosesPesanan();

// Function to clear the console
void membersihkanConsole()
{
    cout << "\033[2J\033[1;1H"; // Clears the console
}
//**PRAKTIKUM 3**//

//**PRAKTIKUM 2**//

void prosesPesanan()
{
    membersihkanConsole();

    // Tampilkan semua pesanan yang ada
    Order *current = front;

    while (current != nullptr)
    {
        cout << "<==============================>" << endl;
        cout << "- Pesanan ID: " << current->id << endl;
        cout << "- Nama Pelanggan: " << current->nama << endl;
        cout << "- Nama Sopir: " << current->supir << endl;
        cout << "- Tujuan: " << current->tujuan << endl;

        current = current->pNext;
    }

    if (front == nullptr)
    {
        cout << "<==============================>" << endl;
        cout << " Tidak ada pesanan yang tersedia " << endl;
        return;
    }

    // Meminta admin untuk memasukkan ID pesanan yang ingin diproses
    string idPesanan;
    cout << "<==============================>" << endl;
    cout << "> Masukkan ID Pesanan yang Ingin Diproses: ";
    cin >> idPesanan;

    // Mencari pesanan berdasarkan ID yang dimasukkan oleh admin
    current = front;
    Order *prevPesanan = nullptr;

    while (current != nullptr && current->id != idPesanan)
    {
        prevPesanan = current;
        current = current->pNext;
    }

    // Memeriksa apakah pesanan dengan ID yang dimasukkan ditemukan
    if (current == nullptr)
    {
        membersihkanConsole();
        cout << "<==============================>" << endl;
        cout << " Pesanan dengan ID " << idPesanan << " tidak ditemukan " << endl;
        return;
    }

    // Menampilkan detail pesanan yang akan diproses
    membersihkanConsole();

    cout << "<==============================>" << endl;
    cout << "- Pesanan ID: " << current->id << endl;
    cout << "- Nama Pelanggan: " << current->nama << endl;
    cout << "- Supir: " << current->supir << endl;
    cout << "- Plat Nomor: " << current->platNomor << endl;
    cout << "- Tujuan: " << current->tujuan << endl;
    cout << "<==============================>" << endl;

    // Menampilkan opsi untuk admin
    cout << "<==============================>" << endl;
    cout << "Pilihan Yang Tersedia : " << endl;
    cout << "(1) Terima Pesanan" << endl;
    cout << "(2) Tolak Pesanan" << endl;
    cout << "(3) Batal" << endl;
    cout << "<==============================>" << endl;

    int choice;
    cout << "> ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        membersihkanConsole();
        cout << "<==============================>" << endl;
        cout << "Pesanan Diterima" << endl;
        // Implementasi untuk memproses pesanan diterima

        // Temukan pesanan yang sesuai di dalam antrian
        if (prevPesanan != nullptr)
        {
            prevPesanan->pNext = current->pNext;
        }
        else
        {
            front = current->pNext;
        }

        delete current;
        // Hapus pesanan dari antrian
        dequeueOrder();
        break;
    case 2:
        membersihkanConsole();
        cout << "<==============================>" << endl;
        cout << "Pesanan ditolak" << endl;

        // Temukan pesanan yang sesuai di dalam antrian
        if (prevPesanan != nullptr)
        {
            prevPesanan->pNext = current->pNext;
        }
        else
        {
            front = current->pNext;
        }
        delete current;

        // Hapus pesanan dari antrian
        dequeueOrder();
        break;
    case 3:
        membersihkanConsole();
        cout << "<==============================>" << endl;
        cout << "Pemrosesan Pesanan Dibatalkan" << endl;

        return;
        break;
    default:
        membersihkanConsole();
        cout << "Opsi tidak valid" << endl;
    }
}

void enqueueOrder(const string &id,
                  const string &nama,
                  const string &supir,
                  const string &platNomor,
                  const string &tujuan)
{
    Order *newOrder = new Order;
    newOrder->id = id;
    newOrder->nama = nama;
    newOrder->supir = supir;
    newOrder->platNomor = platNomor;
    newOrder->tujuan = tujuan;
    newOrder->pNext = nullptr;

    if (front == nullptr && rear == nullptr)
    {
        front = rear = newOrder;
        return;
    }

    rear->pNext = newOrder;
    rear = newOrder;
}

void dequeueOrder()
{
    if (front == nullptr)
    {
        return;
    }

    Order *temp = front;
    front = front->pNext;

    if (front == nullptr)
        rear = nullptr;

    delete temp;
}

int hitungTotalSopir()
{
    int total = 0;
    DataSupir *temp = head;
    while (temp != nullptr)
    {
        total++;
        temp = temp->next;
    }
    return total;
}

DataSupir supirSekarang()
{
    DataSupir *temp = head;
    while (temp != nullptr)
    {
        if (temp->id == proses->supir)
        {
            return *temp;
        }
        temp = temp->next;
    }
    return DataSupir();
}

void orderTaxi()
{
    DataSupir *sopirYangDipesan;
    if (sopirYangDipesan == nullptr)
    {
        membersihkanConsole();
        cout << "Tidak ada sopir yang tersedia." << endl;
        return;
    }
    string tujuan;
    string namaPelanggan;

    cout << "Nama Penumpang : ";
    cin.ignore();
    getline(cin, namaPelanggan);

    cout << "Masukkan tujuan Anda : ";
    cin >> tujuan;

    string namaSopir = sopirYangDipesan->nama;
    string platNomor = "L 1996 YZ."; // Misalnya untuk sementara di set kosong

    // Menambahkan order ke dalam queue
    enqueueOrder(IdGenerator("order", 'O', Date{0, 0, 0}), namaPelanggan, namaSopir,
                 platNomor, tujuan);

    membersihkanConsole();
    cout << "<==============================>" << endl;
    cout << "Pesanan Anda Telah Diterima" << endl;
    cout << "<==============================>" << endl;
    cout << "Nama Sopir: " << namaSopir << endl;
    cout << "Plat Nomor: " << platNomor << endl;
    cout << "Tujuan: " << tujuan << endl;
    cout << "<==============================>" << endl;
    return;
}

void cetakSupirSekarang()
{
    if (head == nullptr)
    {
        membersihkanConsole();
        cout << "Tidak ada pesanan yang sedang diproses." << endl;
        return;
    }
    else
    {
        cout << "<==============================>" << endl;
        cout << "Nama Sopir: " << head->nama << endl;
        cout << "ID Sopir: " << head->id << endl;
        cout << "Jenis Kelamin: " << ((head->jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
        cout << "Tanggal Lahir: " << head->tanggalLahir.tanggal << "-" << head->tanggalLahir.bulan << "-" << head->tanggalLahir.tahun << endl;
        cout << "Alamat: " << head->alamat << endl;
        cout << "No HP: " << head->noHp << endl;
        cout << " Plat Nomor: " << head->id << endl;
        cout << "<==============================>" << endl;
    }
}

void supirSelanjutnya()
{
    if (head == nullptr)
    {
        membersihkanConsole();
        cout << "Tidak ada Data supir tersedia" << endl;
        return;
    }
    if (head != nullptr && head->next != nullptr)
    {
        head = head->next;
        cetakSupirSekarang();
    }
    else
    {
        membersihkanConsole();
        cout << "Tidak ada data supir berikutnya. Kembali ke awal." << endl;
        head = kepala;

        cetakSupirSekarang();
    }
}

void supiSebelumnya()
{
    if (kepala == nullptr)
    {
        membersihkanConsole();
        cout << "Tidak ada Data supir tersedia" << endl;
        return;
    }
    if (head == kepala)
    {
        while (head->next != nullptr)
        {
            head = head->next;
        }
    }
    else
    {
        DataSupir *temp = kepala;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        head = temp;
    }
    cetakSupirSekarang();
}

//**PRAKTIKUM 1**//
// Function to generate ID
string IdGenerator(const string &nama, char jenisKelamin, const Date &tanggalLahir)
{
    int firstDigits = abs(nama.front() - 'A' + 1) + abs(nama.back() - 'A' + 1);
    firstDigits = (firstDigits < 10) ? firstDigits : firstDigits % 10;

    int thirdDigit = (jenisKelamin == 'L') ? 1 : 0;

    int lastDigitDay = tanggalLahir.tanggal % 10;
    int lastDigitMonth = tanggalLahir.bulan % 10;
    int lastDigitYear = (tanggalLahir.tahun % 100) % 10;
    int fourthDigit = (lastDigitDay + lastDigitMonth + lastDigitYear) % 9;

    bool isIdExist(const string &id);

    string finalFirstDigits = to_string(firstDigits);
    if (finalFirstDigits.length() < 3)
    {
        finalFirstDigits = "0" + finalFirstDigits;
    }

    int lastDigit = 0;
    string id;
    do
    {
        id = finalFirstDigits + to_string(thirdDigit) +
             to_string(fourthDigit) + to_string(lastDigit);
        lastDigit++;
    } while (isIdExist(id));

    return id;
}

bool isIdExist(const string &id)
{
    DataSupir *temp = head;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Function to add new driver data
void TambahDataSupir()
{
    DataSupir *supirBaru = new DataSupir;

    cout << "Nama                      : ";
    cin.ignore();
    getline(cin, supirBaru->nama);

    cout << "Kelamin (L/P)             : ";
    cin >> supirBaru->jenisKelamin;

    cout << "Tanggal Lahir (dd-mm-yyyy): ";
    cin >> supirBaru->tanggalLahir.tanggal >> supirBaru->tanggalLahir.bulan >> supirBaru->tanggalLahir.tahun;

    cout << "Alamat                    : ";
    cin.ignore();
    getline(cin, supirBaru->alamat);

    cout << "No HP                     : ";
    cin.ignore();
    getline(cin, supirBaru->noHp);

    supirBaru->id = IdGenerator(supirBaru->nama, supirBaru->jenisKelamin, supirBaru->tanggalLahir);

    supirBaru->next = nullptr;

    if (head == nullptr)
    {
        head = supirBaru;
    }
    else
    {
        DataSupir *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = supirBaru;
    }

    membersihkanConsole();
    cout << "Data supir berhasil ditambahkan." << endl;
    return AdminPriviliage();
}

// Function to view driver data one by one with previous and next options
void LihatDataSupir()
{
    if (head == nullptr)
    {
        cout << "Tidak ada data supir." << endl;
        return;
    }

    DataSupir *temp = head;
    while (temp != nullptr)
    {
        cout << "<==============================>" << endl;
        cout << "ID       : " << temp->id << endl;
        cout << "Nama     : " << temp->nama << endl;
        cout << "Kelamin  : " << ((temp->jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
        cout << "Tgl Lahir: " << temp->tanggalLahir.tanggal << "-" << temp->tanggalLahir.bulan << "-" << temp->tanggalLahir.tahun << endl;
        cout << "Alamat   : " << temp->alamat << endl;
        cout << "No HP    : " << temp->noHp << endl;
        temp = temp->next;
    }
}
// Function to search driver data by ID

DataSupir CariDataSupirById()
{
    if (head == nullptr)
    {
        cout << "Tidak ada data supir." << endl;
        return DataSupir();
    }

    cout << "Masukkan ID Supir yang ingin dicari: ";

    string inputId;
    cin >> inputId;

    DataSupir *current = head;
    while (current != nullptr)
    {
        if (current->id == inputId)
        {
            cout << "<==============================>" << endl;
            cout << "ID       : " << current->id << endl;
            cout << "Nama     : " << current->nama << endl;
            cout << "Kelamin  : " << ((current->jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
            cout << "Tgl Lahir: " << current->tanggalLahir.tanggal << "-" << current->tanggalLahir.bulan << "-" << current->tanggalLahir.tahun << endl;
            cout << "Alamat   : " << current->alamat << endl;
            cout << "No HP    : " << current->noHp << endl;
            current = current->next;
        }
        else
        {
            cout << "Data supir dengan ID " << inputId << " tidak ditemukan." << endl;
            return DataSupir();
        }
    }
    return DataSupir();
}

// Function to edit driver data
void EditDataSupir()
{
    if (head == nullptr)
    {
        cout << "Tidak ada data supir." << endl;
        return;
    }

    cout << "Masukkan ID Supir yang ingin diubah: ";
    string inputId;
    cin >> inputId;
    DataSupir *supirYangDiubah = head;
    while (supirYangDiubah != nullptr)
    {
        if (supirYangDiubah->id == inputId)
        {
            cout << "- Mengubah supir dengan Id " << inputId << " -" << endl;
            cout << "<==============================>" << endl;
            cout << "ID       : " << supirYangDiubah->id << endl;
            cout << "Nama     : " << supirYangDiubah->nama << endl;
            cout << "Kelamin  : " << ((supirYangDiubah->jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
            cout << "Tgl Lahir: " << supirYangDiubah->tanggalLahir.tanggal << "-" << supirYangDiubah->tanggalLahir.bulan << "-" << supirYangDiubah->tanggalLahir.tahun << endl;
            cout << "Alamat   : " << supirYangDiubah->alamat << endl;
            cout << "No HP    : " << supirYangDiubah->noHp << endl;
            cout << "<==============================>" << endl;
            cout << "1. Ubah Nama" << endl;
            cout << "2. Ubah Kelamin" << endl;
            cout << "3. Ubah Alamat" << endl;
            cout << "4. Ubah Tanggal Lahir" << endl;
            cout << "5. Kembali" << endl;
            cout << "<==============================>" << endl;
            cout << ">  ";
            int inputOpsi;
            cin >> inputOpsi;

            switch (inputOpsi)
            {
            case 1:
                cout << "Masukkan Nama yang baru: ";
                cin.ignore();
                getline(cin, supirYangDiubah->nama);
                break;
            case 2:
                cout << "Masukkan Kelamin yang baru (L/P): ";
                cin >> supirYangDiubah->jenisKelamin;
                break;
            case 3:
                cout << "Masukkan Alamat yang baru: ";
                cin.ignore();
                getline(cin, supirYangDiubah->alamat);
                break;
            case 4:
                cout << "Masukkan Tanggal Lahir yang baru (dd-mm-yyyy): ";
                cin >> supirYangDiubah->tanggalLahir.tanggal >> supirYangDiubah->tanggalLahir.bulan >> supirYangDiubah->tanggalLahir.tahun;
                break;
            case 5:
                membersihkanConsole();
                cout << "Kembali ke menu utama" << endl;
                return;
            default:
                cout << "Opsi tidak valid." << endl;
                break;
            }
            membersihkanConsole();
            cout << "Data supir dengan ID " << inputId << " telah diubah." << endl;
            return;
        }
        supirYangDiubah = supirYangDiubah->next;
    }
    cout << "Data supir dengan ID " << inputId << " tidak ditemukan." << endl;
}

// Function to delete driver data
void HapusDataSupir()
{
    if (head == nullptr)
    {
        cout << "Tidak ada data supir yang tersedia." << endl;
        return;
    }

    cout << "Masukkan ID Supir yang ingin dihapus: ";
    string inputId;
    cin >> inputId;

    DataSupir *current = head;
    DataSupir *previous = nullptr;

    while (current != nullptr)
    {
        if (current->id == inputId)
        {
            membersihkanConsole();
            cout << "<==============================>" << endl;
            cout << "\nSupir dengan data berikut akan dihapus :" << endl;
            cout << "Nama     : " << current->nama << endl;
            cout << "ID       : " << current->id << endl;
            cout << "Kelamin  : " << ((current->jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
            cout << "Tgl Lahir: " << current->tanggalLahir.tanggal << "-" << current->tanggalLahir.bulan << "-" << current->tanggalLahir.tahun << endl;
            cout << "Alamat   : " << current->alamat << endl;
            cout << "No HP    : " << current->noHp << endl;
            cout << "<==============================>" << endl;

            cout << "apakah supir dengan id " << inputId << " yang dihapus? (y/n) : ";
            char opsi;
            cin >> opsi;
            if (opsi == 'n' || opsi == 'N')
            {
                membersihkanConsole();
                cout << "Penghapusan data supir dibatalkan." << endl;
                return;
            }
            else if (previous == nullptr)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            delete current;
            membersihkanConsole();
            cout << "| Data sopir dengan ID " << inputId << " berhasil dihapus |\n";
            return;
        }

        previous = current;
        current = current->next;
    }
    cout << "Data supir dengan ID " << inputId << " tidak ditemukan." << endl;
}

// admin role
void AdminPriviliage()
{
    int pilihanAdmin;
    do
    {
        cout << "<==============================>" << endl;
        cout << "Admin Menu:" << endl;
        cout << "1) Mencari Data Supir " << endl;
        cout << "2) Lihat Semua Data Supir" << endl;
        cout << "3) Menghapus Data Supir " << endl;
        cout << "4) Edit Data Supir " << endl;
        cout << "5) Menambah Data Supir " << endl;
        cout << "6) Proses Pesanan " << endl;
        cout << "7) Kembali" << endl;
        cout << "<==============================>" << endl;
        cout << "> ";
        cin >> pilihanAdmin;

        switch (pilihanAdmin)
        {
        case 1:
            membersihkanConsole();
            cout << "Cari Data Supir BY ID" << endl;
            CariDataSupirById();
            break;
        case 2:
            membersihkanConsole();
            cout << "Lihat Semua Data" << endl;
            LihatDataSupir();
            break;
        case 3:
            membersihkanConsole();
            cout << "Hapus Data Supir" << endl;
            HapusDataSupir();
            break;
        case 4:
            membersihkanConsole();
            cout << "Edit Data Supir" << endl;
            EditDataSupir();
            break;
        case 5:
            membersihkanConsole();
            cout << "Tambah Data Supir" << endl;
            TambahDataSupir();
            break;
        case 6:
            membersihkanConsole();
            cout << "Proses Pesanan" << endl;
            prosesPesanan();
            break;
        case 7:
            membersihkanConsole();
            cout << "Kembali ke menu utama" << endl;
            return;
        default:
            membersihkanConsole();
            cout << "Pilihan tidak valid" << endl;
            cin.clear();
            cin.ignore();
        }

    } while (pilihanAdmin != 5);
}

// user role
void UserPrivilage()
{
    int pilihan;
    while (true)
    {
        cout << "<==============================>" << endl;
        cout << "User Menu:" << endl;
        cout << "1) Order By Id " << endl;
        cout << "2) Supir Selanjutnya" << endl;
        cout << "3) Supir sebelumnya" << endl;
        cout << "4) Kembali" << endl;
        cout << "<==============================>" << endl;
        cout << "> ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            membersihkanConsole();
            cout << "Order By Id" << endl;
            orderTaxi();
            break;
        case 2:
            supirSelanjutnya();
            cout << "Supir Selanjutnya" << endl;
            break;
        case 3:
            supiSebelumnya();
            cout << "Supir Sebelumnya" << endl;
            break;
        case 4:
            membersihkanConsole();
            cout << "Kembali ke menu utama" << endl;
            return;

        default:
            membersihkanConsole();
            cout << " Opsi Tidak Valid                  " << endl;
            cout << " Mohon Masukkan Opsi Yang Tersedia " << endl;
            cin.ignore();
        }
    }
}

// Function to delete all driver data
void hapusSemuaSopir(DataSupir *head)
{
    DataSupir *current = head;
    while (current != nullptr)
    {
        DataSupir *next = current->next;
        delete current;
        current = next;
    }
}

// Function to initialize dummy data
void InitializeDummyData()
{
    DataSupir *supir1 = new DataSupir;
    supir1->id = "02130";
    supir1->nama = "Sugeng Pangestu";
    supir1->jenisKelamin = 'L';
    supir1->tanggalLahir.tanggal = 19;
    supir1->tanggalLahir.bulan = 2;
    supir1->tanggalLahir.tahun = 1999;
    supir1->alamat = "Surabaya";
    supir1->noHp = "1234567890";
    supir1->next = nullptr;

    DataSupir *supir2 = new DataSupir;
    supir2->id = "07180";
    supir2->nama = "M Farhan Nabil";
    supir2->jenisKelamin = 'L';
    supir2->tanggalLahir.tanggal = 20;
    supir2->tanggalLahir.bulan = 3;
    supir2->tanggalLahir.tahun = 2005;
    supir2->alamat = "Palembang";
    supir2->noHp = "082178332767";
    supir2->next = nullptr;

    // Add dummy data to the linked list
    if (head == nullptr)
    {
        head = supir1;
        supir1->next = supir2;
    }
    else
    {
        DataSupir *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = supir1;   // Connect supir1 to the existing list
        supir1->next = supir2; // Connect supir2 after supir1
    }
}
int main()
{
    InitializeDummyData();
    membersihkanConsole();
    cout << " Selamat Datang " << endl;
    cout << " di Project Supir " << endl;

    int pilihan;

    while (true)
    {
        cout << "<==============================>" << endl;
        cout << "Menu:" << endl;
        cout << "1) Admin " << endl;
        cout << "2) User" << endl;
        cout << "3) Keluar" << endl;
        cout << "<==============================>" << endl;
        cout << "> ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            membersihkanConsole();
            AdminPriviliage();
            break;
        case 2:
            membersihkanConsole();
            cetakSupirSekarang();
            UserPrivilage();
            break;
        case 3:
        {
            membersihkanConsole();
            char opsi_keluar;

            cout << "<==============================>" << endl;
            cout << " Apakah Anda Yakin Keluar dari Program? " << endl;
            cout << " (y/Y) Untuk keluar dari program        " << endl;
            cout << " (n/N) Untuk tetap berada di program    " << endl;
            cout << "<==============================>" << endl;
            cout << "> Input: ";
            cin >> opsi_keluar;

            if (opsi_keluar == 'y' || opsi_keluar == 'Y')
            {
                membersihkanConsole();
                hapusSemuaSopir(head);
                return 0;
            }
            else if (opsi_keluar == 'n' || opsi_keluar == 'N')
            {
                membersihkanConsole();
                cout << " Selamat Datang " << endl;
                cout << " di Project Supir " << endl;
            }
            else
            {
                membersihkanConsole();
                cout << " Opsi Tidak Valid                  " << endl;
                cout << " Mohon Masukkan Opsi Yang Tersedia " << endl;
            }
        }
        default:
            membersihkanConsole();
            cout << " Opsi Tidak Valid                  " << endl;
            cout << " Mohon Masukkan Opsi Yang Tersedia " << endl;
            cin.ignore();
            break;
        }
    }
    hapusSemuaSopir(head);
    return 0;
}
