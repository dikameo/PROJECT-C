#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct Akun {
    int noRekening;
    int pin;
    char username[200];
    int saldo ;
};

int cekAkun(int noRekening, int pin);
int cekAkunGanda(int noRekening);
void loginAccount();
void registerAccount();
void menu(int noRekening, int pin);
void tambahSaldo(int noRekening, int pin);
void tarikTunai(int noRekening, int pin);
void transferSaldo(int noRekening, int pin);

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int main() {
    int pil;
    system("cls");
    do {
        printf("SELAMAT DATANG DI APLIKASI BANKDIKA\n");
        printf("Gunakan Menu dibawah ini :\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Pilih Pilihan Anda :");
        scanf("%d", &pil);

        switch (pil) {
            case 1:
                loginAccount();
                break;
            case 2:
                registerAccount();
                break;
            case 3:
                printf("Terima kasih menggunakan layanan kami");
                return 0;
            default:
                printf("Pilihan tidak Tersedia\n\n");
                break;
        }
    } while (!(pil==1)||pil==2);

    return 0;
}

int cekAkun(int noRekening, int pin) {
    FILE *file = fopen("akun.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    struct Akun data;

    while (fscanf(file, "%s %d %d %d",  data.username, &data.noRekening, &data.pin, &data.saldo) != EOF) {
        if (data.noRekening == noRekening && data.pin == pin) {

            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
// LOGIN
void loginAccount() {
    struct Akun data;
    printf("Silahkan masuk dengan menggunakan No Rekening dan PIN anda\n");
    printf("No Rekening: ");
    
    while (scanf("%d", &data.noRekening) != 1) {
        clearInputBuffer();
        printf("Input tidak valid. \nMasukkan kembali No Rekening Anda: ");
    }

    printf("PIN: ");
    while (scanf("%d", &data.pin) != 1) {
        clearInputBuffer();
        printf("Input tidak valid. \nMasukkan kembali PIN Anda: ");
    }

    int validasi = 1;
    while (!cekAkun(data.noRekening, data.pin)) {
        if (validasi < 3) {
            printf("AKUN TIDAK DITEMUKAN\n");
            printf("Masukkan No Rekening dan PIN yang valid\n");
            printf("No Rekening: ");
            while (scanf("%d", &data.noRekening) != 1) {
                clearInputBuffer();
                printf("Input tidak valid. \nMasukkan kembali No Rekening Anda: ");
            }

            printf("PIN: ");
            while (scanf("%d", &data.pin) != 1) {
                clearInputBuffer();
                printf("Input tidak valid. \nMasukkan kembali PIN Anda: ");
            }
        } else {
            printf("Anda Salah Memasukkan Sebanyak 3 Kali\n\n");
            sleep(3);
            main();
        }
        validasi++;
    }

    printf("Selamat Datang\n");
    menu(data.noRekening, data.pin);
}

// REGISTER
void registerAccount() {
    FILE *file = fopen("akun.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    struct Akun data;

    printf("SILAHKAN DAFTAR TERLEBIH DAHULU\n");
    printf("Masukkan Nama Anda: ");
    scanf("%s", data.username);

    printf("Masukkan No Rekening Anda: ");
    while (scanf("%d", &data.noRekening) != 1 || cekAkunGanda(data.noRekening)) {
        clearInputBuffer();
        if (cekAkunGanda(data.noRekening)) {
            printf("No Rekening %d telah digunakan.\n", data.noRekening);
            printf("Masukkan No Rekening Anda Lagi: ");
        } else {
            printf("Input tidak valid. Masukkan kembali No Rekening Anda: ");
        }
    }

    printf("Masukkan PIN Anda: ");
    while (scanf("%d", &data.pin) != 1) {
        clearInputBuffer();
        printf("Input tidak valid. Masukkan kembali PIN Anda: ");
    }

    data.saldo = 0;

    fprintf(file, "%s %d %d %d\n", data.username, data.noRekening, data.pin, data.saldo);
    fclose(file);
    
    system("cls"); // Assuming you are using Windows. Use "clear" for Linux/macOS.
    printf("Data berhasil ditambahkan.\n");
}

// CEK AKUN GANDA
int cekAkunGanda(int noRekening){
    FILE *file = fopen("akun.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    struct Akun data;

    while (fscanf(file, "%s %d %d %d",  data.username, &data.noRekening, &data.pin, &data.saldo) != EOF) {
        if (data.noRekening == noRekening) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

// MENU
void menu(int noRekening, int pin){
    int pil;
    system("cls");
    FILE *file = fopen("akun.txt","r");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        exit(1);
    }

    struct Akun data;

    printf("Selamat Datang di Mbanking:\n");
    printf("=================================\n");
    while (fscanf(file, "%s %d %d %d",  data.username, &data.noRekening, &data.pin, &data.saldo) != EOF) {
        if (data.noRekening == noRekening && data.pin == pin) {
            printf("Pengguna: %s\n", data.username);
            printf("No Rekening: %d\n", data.noRekening);
            printf("Saldo: %d\n", data.saldo);
            break;
        }
    }
    printf("=================================\n");
    printf("Masukkan Menu yang Akan Anda Pilih :\n");
    printf("1. Tambah Saldo \n");
    printf("2. Tarik Tunai \n");
    printf("3. Transfer \n");
    printf("4. Logout \n");
    printf("Pilihan Anda (1/2/3/4) :");
    scanf("%d",&pil);
    switch (pil)
    {
    case 1:
        fclose(file);
        tambahSaldo(data.noRekening,data.pin);
        break;
    case 2:
        fclose(file);
        tarikTunai(data.noRekening,data.pin);
        break;
    case 3:
        fclose(file);
        transferSaldo(data.noRekening,data.pin);
        break;
    case 4:
        fclose(file);
        main();
        break;
    
    default:
        printf("pilihan tidak Tersedia");
        break;
    }


    fclose(file);
}
// TAMBAH SALDO
void tambahSaldo(int noRekening, int pin){
    int saldo;
    int backupNoRek = noRekening;
    int backupPin = pin;
    struct Akun data;
       FILE *file = fopen("akun.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }


    while (fscanf(file, "%s %d %d %d",  data.username, &data.noRekening, &data.pin, &data.saldo) != EOF) {
        if (data.noRekening == noRekening && data.pin == pin) {
            printf("Menambahkan Saldo Anda dari : %d\n",data.saldo);
            printf("Masukkan Saldo Yang ingin Anda tambahkan :");

            while (scanf("%d", &saldo) != 1 || saldo < 0) {
                printf("Input tidak valid. \nMasukkan kembali saldo Anda: ");
                fflush(stdin);
            }
                data.saldo += saldo;
                printf("===========================\nSaldo Anda Berhasil ditambahkan sebesar : %d\n",saldo);
                printf("Saldo Anda Sekarang : %d\n===========================",data.saldo);
                sleep(5);
            
        }
        fprintf(tempFile,"%s %d %d %d\n",data.username, data.noRekening, data.pin, data.saldo);
    }

   fclose(file);
    fclose(tempFile);

    remove("akun.txt");
    rename("temp.txt", "akun.txt");
    menu(backupNoRek,backupPin);
}

// TARIK
void tarikTunai(int noRekening, int pin){
    int saldo;
    int backupNoRek = noRekening;
    int backupPin = pin;
    struct Akun data;
    FILE *file = fopen("akun.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }


    while (fscanf(file, "%s %d %d %d",  data.username, &data.noRekening, &data.pin, &data.saldo) != EOF) {
        if (data.noRekening == noRekening && data.pin == pin) {
            printf("Menarik Saldo Anda dari : %d\n",data.saldo);
            printf("Masukkan Saldo Yang ingin Anda Tarik :");
            while (scanf("%d", &saldo) != 1 || saldo < 0 || data.saldo < saldo) {
                printf("Input tidak valid. \nMasukkan kembali saldo Anda: ");
                while (getchar() != '\n');
            }

                data.saldo -= saldo;
                printf("===========================\nSaldo Anda Berhasil ditarik sebesar : %d\n", saldo);
                printf("Saldo Anda Sekarang : %d\n===========================",data.saldo);
                sleep(5);
            
        }
        fprintf(tempFile,"%s %d %d %d\n",data.username, data.noRekening, data.pin, data.saldo);
    }

   fclose(file);
    fclose(tempFile);

    remove("akun.txt");
    rename("temp.txt", "akun.txt");
    menu(backupNoRek,backupPin);
}



// TRANSFER

void transferSaldo(int noRekening, int pin) {
    struct Akun data;
    FILE *file = fopen("akun.txt", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

        FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }

    char penerima[200];
    int rekeningOrang, saldo = 0, backupNoRek = noRekening, backupPin = pin;

    printf("Masukan No Rekening yang ingin anda Transfer :");
    if (scanf("%d", &rekeningOrang) != 1) {
        printf("Input tidak valid.\n");
        fclose(file);
        return;
    }

    printf("Masukan penerima Transfer :");
    scanf("%s", penerima);

    int pengirimDitemukan = 0;
    int saldoTransfer = 0;

    while (fscanf(file, "%s %d %d %d", data.username, &data.noRekening, &data.pin, &data.saldo) != EOF) {
        if (data.noRekening == noRekening && data.pin == pin) {
            pengirimDitemukan = 1;
            printf("Saldo yang ingin Anda Transfer : ");
            while (scanf("%d", &saldoTransfer) != 1 || saldoTransfer < 0) {
                printf("Input tidak valid. \nMasukkan kembali saldo Anda: ");
            }

            if (data.saldo >= saldoTransfer) {
                data.saldo -= saldoTransfer;
                printf("Berhasil Melakukan transaksi ke %s sebesar Rp %d\n", penerima, saldoTransfer);
                sleep(5);
            } else {
                printf("Saldo tidak mencukupi untuk transfer.\n");
            }
        }

        fprintf(tempFile, "%s %d %d %d\n", data.username, data.noRekening, data.pin, data.saldo);
    }
    fclose(file);
    fclose(tempFile);
    remove("akun.txt");
    rename("temp.txt", "akun.txt");


    file = fopen("akun.txt", "r+");
    tempFile = fopen("temp.txt", "w");
    rewind(file);  // Kembali ke awal file untuk mencari penerima
    while (fscanf(file, "%s %d %d %d", data.username, &data.noRekening, &data.pin, &data.saldo) != EOF) {
        if (data.noRekening == rekeningOrang && strcmp(data.username, penerima) == 0) {
            printf("BERHASIL DITEMUKAN (PENERIMA)\n");

            data.saldo += saldoTransfer;
            printf("Berhasil Menerima transfer dari %d sebesar Rp %d\n", noRekening, saldoTransfer);
            sleep(2);
        }

        fprintf(tempFile, "%s %d %d %d\n", data.username, data.noRekening, data.pin, data.saldo);
    }

    if (!pengirimDitemukan) {
        printf("Pengirim dengan No Rekening %d tidak ditemukan.\n", noRekening);
    }

    fclose(file);
    fclose(tempFile);
    remove("akun.txt");
    rename("temp.txt", "akun.txt");
    menu(backupNoRek, backupPin);
}
