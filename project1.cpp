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
struct Mobil
{
    string platNomor;
    string jenisMobil;
    string brandMobil;
};

struct DataSupir
{
    string id;
    string nama;
    string alamat;
    Date tanggalLahir;
    char jenisKelamin;
    string noHp;
};

const int MAX_SIZE = 100; // Ukuran maksimum stack
struct StackMobil
{
    Mobil data[MAX_SIZE];
    int top;
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

struct Node
{
    DataSupir data;
    Node *next;
};

// Global variable to store the driver data
Node *firstDriver = nullptr;
Node *prevDriver = nullptr;
Node *currentDriver = nullptr;

Order *proses = nullptr;
Order *front = nullptr;
Order *rear = nullptr;

int top; // Indeks elemen teratas stack
int dataMobil[MAX_SIZE];

// Function prototype
void membersihkanConsole();
void TambahDataSupir();
void LihatDataSupir();
Node CariDataSupirById();
void EditDataSupir();
void HapusDataSupir();
void AdminPriviliage();
void UserPrivilage();
void hapusSemuaSopir(DataSupir *saatIni);
bool isIdExist(const string &id);

string IdGenerator(const string &nama, char jenisKelamin, const Date &tanggalLahir);
void enqueueOrder(const string &id,
                  const string &nama,
                  const string &supir,
                  const string &platNomor,
                  const string &tujuan);

void dequeueOrder();
int hitungTotalSopir();
Node *pilihSopirSecaraAcak();
void prosesPesanan();
void push(StackMobil &stack,
          const std::string &platNomor,
          const std::string &jenis,
          const std::string &merk);
void pop(StackMobil &stack);
void orderTaxi();
void tambahUnitMobil(StackMobil &stack);

// Function to clear the console
void membersihkanConsole()
{
    cout << "\033[2J\033[1;1H"; // Clears the console
}
//**PRAKTIKUM 3**//
// Fungsi untuk menambah unit mobil ke stack

void push(
    StackMobil &stack, const string &platNomor,
    const string &jenis,
    const string &merk)
{
    if (stack.top == MAX_SIZE - 1)
    {
        cout << "Stack penuh." << endl;
        return;
    }
    stack.top++;
    stack.data[stack.top].platNomor = platNomor;
    stack.data[stack.top].jenisMobil = jenis;
    stack.data[stack.top].brandMobil = merk;
    cout << "Unit mobil berhasil ditambahkan ke dalam stack." << endl;
}

// Fungsi untuk menghapus unit mobil dari stack
void pop(StackMobil &stack)
{
    if (stack.top == -1)
    {
        cout << "Stack kosong." << endl;
        return;
    }
    stack.top--;
    cout << "Unit mobil berhasil dihapus dari stack." << endl;
}

void display(const StackMobil &stack)
{
    if (stack.top == -1)
    {
        cout << "Stack kosong." << endl;
        return;
    }
    cout << "Daftar Unit Mobil dalam Stack:" << endl;

    for (int i = stack.top; i >= 0; i--)
    {
        cout << "Plat Nomor: " << stack.data[i].platNomor
             << ", Jenis: " << stack.data[i].jenisMobil
             << ", Merk: " << stack.data[i].brandMobil << endl;
    }
}
void tambahUnitMobil(StackMobil &stack)
{
    string platNomor;
    string jenisMobil;
    string brandMobil;

    cout << "Plat Nomor (ex: A XXXX AA ): ";
    cin.ignore();
    getline(cin, platNomor);

    cout << "Jenis Mobil                : ";
    cin.ignore();
    getline(cin, jenisMobil);

    cout << "Brand Mobil                : ";
    cin.ignore();
    getline(cin, brandMobil);

    push(stack, platNomor, jenisMobil, brandMobil);
    membersihkanConsole();
}
//**PRAKTIKUM 2**//

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
    Node *temp = currentDriver;
    while (temp != nullptr)
    {
        total++;
        temp = temp->next;
    }
    return total;
}

Node supirSekarang()
{
    Node *temp = currentDriver;
    while (temp != nullptr)
    {
        if (temp->data.id == proses->supir)
        {
            return *temp;
        }
        temp = temp->next;
    }
    return Node();
}
void prosesPesanan(StackMobil &stack)
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
        cout << "- Plat Nomor: " << current->platNomor << endl;
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
Node *pilihSopirSecaraAcak()
{
    if (currentDriver == nullptr)
        return nullptr;

    int totalSopir = hitungTotalSopir();
    int indeksSopirAcak = rand() % totalSopir;

    Node *temp = currentDriver;
    for (int i = 0; i < indeksSopirAcak; ++i)
        temp = temp->next;

    return temp;
}
void orderTaxi(StackMobil &stack)
{
    Node *sopirYangDipesan = pilihSopirSecaraAcak();
    if (sopirYangDipesan == nullptr)
    {
        membersihkanConsole();
        cout << "Tidak ada sopir yang tersedia." << endl;
        return;
    }

    if (stack.top == -1)
    {
        membersihkanConsole();
        cout << "Tidak ada unit mobil yang tersedia." << endl;
        cout << "Unit mobil sedang kosong harap menunggu..." << endl;

        return;
    }

    string tujuan;
    string namaPelanggan;

    cout << "Nama Penumpang : ";
    cin.ignore();
    getline(cin, namaPelanggan);

    cout << "Masukkan tujuan Anda : ";
    cin >> tujuan;

    string namaSopir = sopirYangDipesan->data.nama;
    string platNomor = stack.data->platNomor;

    // Menambahkan order ke dalam queue
    enqueueOrder(IdGenerator("order", 'O', Date{0, 0, 0}), namaPelanggan, namaSopir, platNomor, tujuan);
    membersihkanConsole();
    cout << "<==============================>" << endl;
    cout << "Pesanan Anda Telah Diterima" << endl;
    cout << "<==============================>" << endl;
    cout << "Nama Penumpang: " << namaPelanggan << endl;
    cout << "Nama Sopir    : " << namaSopir << endl;
    cout << "Plat Nomor    : " << stack.data->platNomor << endl;
    cout << "Tujuan        : " << tujuan << endl;
    return;
    cout << "ingin melakukan order lagi? (y/n)" << endl;
    char opsi;
    cin >> opsi;
    if (opsi == 'y' || opsi == 'Y')
    {
        orderTaxi();
    }
    else if (opsi == 'n' || opsi == 'N')
    {
        membersihkanConsole();
        cout << "Kembali ke menu utama" << endl;
        return UserPrivilage();
    }
    else
    {
        membersihkanConsole();
        cout << "Opsi tidak valid" << endl;
    }
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
    Node *temp = currentDriver;
    while (temp != nullptr)
    {
        if (temp->data.id == id)
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
    Node *supirBaru = new Node;

    cout << "Nama                      : ";
    cin.ignore();
    getline(cin, supirBaru->data.nama);

    cout << "Kelamin (L/P)             : ";
    cin >> supirBaru->data.jenisKelamin;

    cout << "Tanggal Lahir (dd-mm-yyyy): ";
    cin >> supirBaru->data.tanggalLahir.tanggal >> supirBaru->data.tanggalLahir.bulan >> supirBaru->data.tanggalLahir.tahun;

    cout << "Alamat                    : ";
    cin.ignore();
    getline(cin, supirBaru->data.alamat);

    cout << "No HP                     : ";
    cin.ignore();
    getline(cin, supirBaru->data.noHp);

    supirBaru->data.id = IdGenerator(supirBaru->data.nama, supirBaru->data.jenisKelamin, supirBaru->data.tanggalLahir);

    supirBaru->next = nullptr;

    if (currentDriver == nullptr)
    {
        currentDriver = supirBaru;
    }
    else
    {
        Node *temp = currentDriver;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = supirBaru;
    }

    membersihkanConsole();
    cout << "Data supir berhasil ditambahkan." << endl;
}

void cetakSupirSekarang()
{
    if (currentDriver == nullptr)
    {
        membersihkanConsole();
        cout << "Tidak ada pesanan yang sedang diproses." << endl;
        return;
    }
    else
    {
        cout << "<==============================>" << endl;
        cout << "Nama Sopir: " << currentDriver->data.nama << endl;
        cout << "ID Sopir: " << currentDriver->data.id << endl;
        cout << "Jenis Kelamin: " << ((currentDriver->data.jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
        cout << "Tanggal Lahir: " << currentDriver->data.tanggalLahir.tanggal << "-" << currentDriver->data.tanggalLahir.bulan << "-" << currentDriver->data.tanggalLahir.tahun << endl;
        cout << "Alamat: " << currentDriver->data.alamat << endl;
        cout << "No HP: " << currentDriver->data.noHp << endl;
    }
}

void supirSelanjutnya()
{
    if (currentDriver == nullptr)
    {
        membersihkanConsole();
        cout << "Tidak ada Data supir tersedia" << endl;
        return;
    }

    if (currentDriver != nullptr && currentDriver->next != nullptr)
    {
        currentDriver = currentDriver->next;
        membersihkanConsole();
        cetakSupirSekarang();
    }
    else
    {
        membersihkanConsole();
        cout << "Tidak ada data sopir berikutnya" << endl;
        cetakSupirSekarang();
    }
}

void supirSebelumnya()
{

    if (currentDriver == nullptr)
    {
        membersihkanConsole();
        cout << "Tidak ada data sopir yang tersedia." << endl;
        return;
    }

    if (currentDriver == firstDriver)
    {
        membersihkanConsole();
        cout << "Tidak ada data sopir sebelumnya." << endl;
        cetakSupirSekarang();
        return;
    }

    Node *temp = firstDriver;
    while (temp->next != currentDriver)
    {
        temp = temp->next;
    }
    currentDriver = temp;
    membersihkanConsole();
    cetakSupirSekarang();
}

// Function to view driver data one by one with previous and next options
void LihatDataSupir()
{
    if (currentDriver == nullptr)
    {
        cout << "Tidak ada data supir." << endl;
        return;
    }

    Node *temp = currentDriver;
    while (temp != nullptr)
    {
        cout << "<==============================>" << endl;
        cout << "ID       : " << temp->data.id << endl;
        cout << "Nama     : " << temp->data.nama << endl;
        cout << "Kelamin  : " << ((temp->data.jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
        cout << "Tgl Lahir: " << temp->data.tanggalLahir.tanggal << "-" << temp->data.tanggalLahir.bulan << "-" << temp->data.tanggalLahir.tahun << endl;
        cout << "Alamat   : " << temp->data.alamat << endl;
        cout << "No HP    : " << temp->data.noHp << endl;
        temp = temp->next;
    }
}
// Function to search driver data by ID

Node CariDataSupirById()
{
    if (currentDriver == nullptr)
    {
        cout << "Tidak ada data supir." << endl;
        return Node();
    }

    cout << "Masukkan ID Supir yang ingin dicari: ";

    string inputId;
    cin >> inputId;

    Node *current = currentDriver;
    while (current != nullptr)
    {
        if (current->data.id == inputId)
        {
            cout << "<==============================>" << endl;
            cout << "ID       : " << current->data.id << endl;
            cout << "Nama     : " << current->data.nama << endl;
            cout << "Kelamin  : " << ((current->data.jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
            cout << "Tgl Lahir: " << current->data.tanggalLahir.tanggal << "-" << current->data.tanggalLahir.bulan << "-" << current->data.tanggalLahir.tahun << endl;
            cout << "Alamat   : " << current->data.alamat << endl;
            cout << "No HP    : " << current->data.noHp << endl;
            current = current->next;
        }
        else
        {
            cout << "Data supir dengan ID " << inputId << " tidak ditemukan." << endl;
            return Node();
        }
    }
    return Node();
}

// Function to edit driver data
void EditDataSupir()
{
    if (currentDriver == nullptr)
    {
        cout << "Tidak ada data supir." << endl;
        return;
    }

    cout << "Masukkan ID Supir yang ingin diubah: ";
    string inputId;
    cin >> inputId;
    Node *supirYangDiubah = currentDriver;
    while (supirYangDiubah != nullptr)
    {
        if (supirYangDiubah->data.id == inputId)
        {
            cout << "- Mengubah supir dengan Id " << inputId << " -" << endl;
            cout << "<==============================>" << endl;
            cout << "ID       : " << supirYangDiubah->data.id << endl;
            cout << "Nama     : " << supirYangDiubah->data.nama << endl;
            cout << "Kelamin  : " << ((supirYangDiubah->data.jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
            cout << "Tgl Lahir: " << supirYangDiubah->data.tanggalLahir.tanggal << "-" << supirYangDiubah->data.tanggalLahir.bulan << "-" << supirYangDiubah->data.tanggalLahir.tahun << endl;
            cout << "Alamat   : " << supirYangDiubah->data.alamat << endl;
            cout << "No HP    : " << supirYangDiubah->data.noHp << endl;
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
                getline(cin, supirYangDiubah->data.nama);
                break;
            case 2:
                cout << "Masukkan Kelamin yang baru (L/P): ";
                cin >> supirYangDiubah->data.jenisKelamin;
                break;
            case 3:
                cout << "Masukkan Alamat yang baru: ";
                cin.ignore();
                getline(cin, supirYangDiubah->data.alamat);
                break;
            case 4:
                cout << "Masukkan Tanggal Lahir yang baru (dd-mm-yyyy): ";
                cin >> supirYangDiubah->data.tanggalLahir.tanggal >> supirYangDiubah->data.tanggalLahir.bulan >> supirYangDiubah->data.tanggalLahir.tahun;
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
    if (currentDriver == nullptr)
    {
        cout << "Tidak ada data supir yang tersedia." << endl;
        return;
    }

    cout << "Masukkan ID Supir yang ingin dihapus: ";
    string inputId;
    cin >> inputId;

    Node *current = currentDriver;
    Node *previous = nullptr;

    while (current != nullptr)
    {
        if (current->data.id == inputId)
        {
            membersihkanConsole();
            cout << "<==============================>" << endl;
            cout << "\nSupir dengan data berikut akan dihapus :" << endl;
            cout << "Nama     : " << current->data.nama << endl;
            cout << "ID       : " << current->data.id << endl;
            cout << "Kelamin  : " << ((current->data.jenisKelamin == 'L') ? "Laki-laki" : "Perempuan") << endl;
            cout << "Tgl Lahir: " << current->data.tanggalLahir.tanggal << "-" << current->data.tanggalLahir.bulan << "-" << current->data.tanggalLahir.tahun << endl;
            cout << "Alamat   : " << current->data.alamat << endl;
            cout << "No HP    : " << current->data.noHp << endl;
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
                currentDriver = current->next;
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
void AdminPriviliage(StackMobil &stack)
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
        cout << "7) Tambah Unit Mobil " << endl;
        cout << "8) Kembali" << endl;
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
            prosesPesanan(stack);
            break;

        case 7:
            membersihkanConsole();
            cout << "Tambah Unit Mobil" << endl;
            tambahUnitMobil(stack);
        case 8:
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
void UserPrivilage(StackMobil &stack)
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
            orderTaxi(stack);
            break;
        case 2:
            supirSelanjutnya();
            cout << "Supir Selanjutnya" << endl;
            break;
        case 3:
            supirSebelumnya();
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
void hapusSemuaSopir(Node *saatIni)
{
    Node *current = saatIni;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

// Function to initialize dummy data
void InitializeDummyData()
{
    DataSupir supir1 = {"02130", "Sugeng Pangestu", "Surabaya", {19, 2, 1999}, 'L', "123456789"};
    DataSupir supir2 = {"07180", "M Farhan Nabil", "Palembang", {20, 3, 2005}, 'P', "987654321"};
    // Initialize the first driver
    Node *newDriver1 = new Node;
    newDriver1->data = supir1;
    newDriver1->next = nullptr;
    firstDriver = newDriver1;

    // Initialize the second driver
    Node *newDriver2 = new Node;
    newDriver2->data = supir2;
    newDriver2->next = nullptr;
    firstDriver->next = newDriver2;

    StackMobil stack;
}
int main()
{
    StackMobil stack;
    stack.top = -1;
    Node *head = nullptr;
    InitializeDummyData();
    currentDriver = firstDriver;
    prevDriver = nullptr;

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
            AdminPriviliage(stack);
            break;
        case 2:
            membersihkanConsole();
            cetakSupirSekarang();

            UserPrivilage(stack);
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
                hapusSemuaSopir(currentDriver);
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
    hapusSemuaSopir(currentDriver);
    return 0;
}
