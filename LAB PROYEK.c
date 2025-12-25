#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <conio.h>
#include <windows.h> 
#include <ctype.h>

void Out();
void MenuUtama();
void MenuAwal();
void koordinat(int x, int y); 
void Menu_Shipment();
int input(char *temp, int panjang); 
int input_khusus(char *temp, int panjang); 
int input_digit(char *temp, int panjang); 
void view_all(); 
void sorting_barang(); 
void search();
void search_id();
void search_name();
void search_handling();
void registrasi();
void login();
int check_user(char userIn[]);
int check_pass(char passIn[]);
int Input_pass(char *temp, int panjang);
int Input_user(char *temp, int panjang);
int check_code(int pass);
int check_id(int pass);
void encrypt(char *text);
void decrypt(char *text);

char filename[50];

#define RED  "\003[0;31m"
#define RESET "\003[0m"

struct User{
    char username[20];
    char password[20]; 
};

struct Datacenter{
    int item_id; 
    char item_name[20];
    char item_type[30]; 
    int handling_code; 
}; 

int main() {
    MenuAwal();
    return 0;
}

void MenuAwal(){ 
    int posisi = 1; 
    char input;
    while(1){
        system("cls"); 
        printf("===========================================================\n");
        printf("  ____  _     _                        ___             \n");
        printf(" / ___|| |__ (_)_ __  _ __   _____  __ | |    ___   __ _ \n");
        printf(" \\___ \\| '_ \\| | '_ \\| '_ \\ / _ \\ \\/ / | |   / _ \\ / _` |\n");
        printf("  ___) | | | | | |_) | |_) |  __/>  <  | |__| (_) | (_| |\n");
        printf(" |____/|_| |_|_| .__/| .__/ \\___/_/\\_\\ |_____\\___/ \\__, |\n");
        printf("               |_|   |_|                           |___/ \n");
        printf("===========================================================\n\n");

        printf("Choose One Option : \n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf(">>> ");

        input = getch();

        switch(input){
        case '1':
            system("cls");
            login();
            break;
        case '2':
            system("cls");
            registrasi();
            break;
        case '3':
            system("cls");
            Out();
            exit(0);
            break;
        default:
            printf("Invalid Option");
            while ((input = getch()) != '\r'){}
            system("cls");
            break;
        }
    }
}
void encrypt(char *text){
	int i;
	for (i = 0; text[i] != '\0'; i++){
		text[i] = text[i] + 3;
	}
}
void decrypt(char *text){
	int i;
	for (i = 0; text[i] != '\0'; i++){
		text[i] = text[i] - 3;
	}
}

int check_user(char userIn[]){
     FILE *fw = fopen("login.txt", "r"); 
    
    if(fw == NULL){
        return 0; 
    }
    struct User Temp; 

    while(fscanf(fw, "%s %s ", Temp.username, Temp.password) != EOF) {
		decrypt(Temp.username);
        if(strcmp(userIn, Temp.username) == 0){
            fclose(fw);
            return 1; 
        }
    
    }
    
    fclose(fw); 
    return 0; 
}

int check_pass(char passIn[]){
    FILE *fw = fopen("login.txt", "r");  
    
    if(fw == NULL){
        return 0; 
    }
    struct User Temp; 

    while(fscanf(fw, "%s %s ", Temp.username, Temp.password) != EOF) {
		decrypt(Temp.password);
        if(strcmp(passIn, Temp.password) == 0){
            fclose(fw);
            return 1; 
        }
    
    }
    
    fclose(fw); 
    return 0; 
}

int Input_pass(char *temp, int panjang){

    int index = 0; 
    char input; 

    temp[0] = '\0'; 

    while(1){
        input = getch(); 

        if(input == '\033'){
            return 1; 
        } else if(input == '\r'){
            temp[index] = '\0';
            return 0; 
        }else if(input == '\b'){
            if (index > 0){
                index--; 
                printf("\b \b"); 
            }
        }else if(isalnum(input)){
            if(index < panjang){
                temp[index] = input;  
                index++;
                printf("*"); 
            }
           
        }
    }
}

int Input_user(char *temp, int panjang){

    int index = 0; 
    char input; 

    temp[0] = '\0'; 

    while(1){
        input = getch(); 

        if(input == '\033'){
            return 1; 
        } else if(input == '\r'){
            temp[index] = '\0';
            return 0; 
        }else if(input == '\b'){
            if (index > 0){
                index--; 
                printf("\b \b"); 
            }
        }else if(isalnum(input)){
            if(index < panjang){
                temp[index] = input;  
                index++;
                printf("%c", input); 
            }
           
        }
    }
}

void registrasi(){
    char user[20];
    char pass[12];
    char confirmPass[12];

    int valid = 0; 

    printf("__________              .__          __                 \n");
    printf("\\______   \\  ____   ___ |__| _______/  |_  ___________  \n");
    printf("|        _/ / __ \\ / __\\|  |/  ___/\\   __\\/ __ \\_  __ \\ \n");
    printf("|    |   \\    ___// /_/ >  |\\___ \\  |  | \\  ___/|  | /  \n");
    printf("|____|_  /\\___   >___ / |__/____  > |__|  \\___  >__|    \n");
    printf("       \\/     \\/_____/          \\/            \\/        \n") ;
    printf("============================================================\n\n");

    printf("Username (8-20 Character):\n");
    printf("Password (8-12 Character):\n");
    printf("Confirm Password: \n");
    
    do{
        koordinat(26,8);
        if(Input_user(user, 20) == 1){
            return;
        }else{
            if(check_user(user) == 1){
                valid = 0; 
                koordinat(26,8); printf("\033[0;31mUsername Telah Digunakan, Silahkan Coba Yang Lain\033[0m");
                getchar();
                koordinat(26,8); printf("                                                                   ");
                continue;
            }else if(strlen(user) < 8){
                valid = 0;
                 koordinat(26,8); printf("\033[0;31mUsername Harus Minimal 8 Character\033[0m"); 
                 getchar();
                 koordinat(26,8); printf("                                                 ");
            }else{
                valid = 1; 
            }
        }
    }while(!valid);
    
    valid = 0;
    do{
        koordinat(26,9);
        if(Input_pass(pass, 12) == 1){
            return;
        }else{
            if(check_pass(pass) == 1){
                valid = 0; 
                koordinat(26,9); printf("\033[0;31mPassword Telah Digunakan, Silahkan Coba Yang Lain\033[0m");
                getchar();
                koordinat(26,9); printf("                                                                   ");
                continue;
            }else if(strlen(pass) < 8){
                valid = 0;
                 koordinat(26,9); printf("\033[0;31mPassword Harus Minimal 8 Character\033[0m"); 
                 getchar();
                 koordinat(26,9); printf("                                                 ");
            }else{
                valid = 1; 
            }
        }
    }while(!valid); 

    valid = 0 ;

    do{
        koordinat(23,10);
        if(Input_pass(confirmPass, 12) == 1){
            return;
        }else{
            if(strlen(pass) < 8){
                valid = 0;
                 koordinat(26,9); printf("\033[0;31mPassword Harus Minimal 8 Character\033[0m"); 
                 getchar();
                 koordinat(26,9); printf("                                                   ");
            }else if(strcmp(confirmPass, pass) != 0){
                valid = 0;
                koordinat(23,10); printf("\033[0;31mPassword Tidak Satu Sama Lain\033[0m");
                getchar();
                koordinat(23,10); printf("                                                ");
            }else{
                valid = 1;  
            }
        }
    }while(!valid);

    encrypt(user);
	encrypt(pass);

    FILE *fw = fopen("login.txt","a"); 
    
    fprintf(fw, "%s %s\n\n", user, pass);
    fclose(fw); 

    printf("\n\n");
    printf("\nRegistrasi Berhasil!\n");
    printf("Tekan enter to keluar...\n");
    getchar();
}

void login(){
    char usernama[20];
    char passnama[12];
    int valid = 0; 
    int check = 0;
   
    do{
        system("cls");
        printf(".____                 .__         \n");
        printf("|    |    ____   ____ |__| ____   \n");
        printf("|    |   /  _ \\ / ___\\|  |/    \\  \n");
        printf("|    |__{  <_> } /_/  >  |   |  \\ \n");
        printf("|_______ \\____/\\___  /|__|___|  / \n");
        printf("        \\/    /_____/         \\/  \n");
        printf("======================================\n\n");

        printf("Username (8-20 Character):\n");
        printf("Password (8-12 Character):\n");
        do{
        koordinat(26,8);
        if(Input_user(usernama, 20) == 1){
        return;
        }else{
            if(strlen(usernama) < 8){
                valid = 0;
                koordinat(26,8); printf("\033[0;31mUsername Harus Minimal 8 Character\033[0m"); 
                 getchar();
                koordinat(26,8); printf("                                                   ");
            }else{
                valid= 1;
            }
        }
        }while(!valid);

        valid = 0; 

        do{
            koordinat(26,9);
            if(Input_pass(passnama, 12) == 1){
                return;
            }else{
                if(strlen(passnama) < 8){
                    valid = 0;
                    koordinat(26,9); printf("\033[0;31mPassword Harus Minimal 8 Character\033[0m"); 
                    getchar();
                    koordinat(26,9); printf("                                                   ");
                }else{
                    valid= 1;
                }
            }
        }while(!valid);

        FILE *fw = fopen("login.txt", "r"); 

        if(fw == NULL){
            printf("Database Tidak Ditemukan\n");
            return;
        }

        struct User temp; 
        check = 0; 

        while(fscanf(fw, "%s %s", temp.username, temp.password) != EOF) {
            decrypt(temp.username);
            decrypt(temp.password);
            if(strcmp(usernama, temp.username) == 0 && strcmp(passnama, temp.password) == 0){
                check = 1;
                break; 
            }
        }
        fclose(fw); 
        
        if(!check) {
            printf("\n\033[0;31mUsername atau Password Salah! Silahkan coba lagi\033[0m\n");
            getchar();
        }
        
    }while(!check);

    sprintf(filename, "%s.txt", usernama);

    printf("\nLogin Berhasil!\n");
    getchar();
    MenuUtama();
}

void MenuUtama(){
    int posisi = 1; 
    char B; 

    while(1){
        system("cls"); 
        
        printf("=====================================================\n");
        printf("      _________________          SHIPPEX LOGISTIC\n");
        printf("     |_|_|_|_|_|_|_|_|_|____     ----------------\n");
        printf("     |                      |    [  Fast      ]\n");
        printf("     |      SHIPPEX         |--_ [  Reliable  ]\n");
        printf("     |______________________|  | [  Global    ]\n");
        printf("      (O)                (O)   '-----------------\n");
        printf("=====================================================\n\n");
        printf("[1] New Shipment Item %s\n" , (posisi == 1) ? "<<" : "");
        printf("[2] View All Items    %s\n" , (posisi == 2) ? "<<" : ""); 
        printf("[3] Sort Item List    %s\n" , (posisi == 3) ? "<<" : "");
        printf("[4] Search Item Name  %s\n" , (posisi == 4) ? "<<" : "");
        printf("[5] Exit              %s\n" , (posisi == 5) ? "<<" : "");

        B = getch(); 

        if(B == 'w' || B == 'W'){
            posisi--; 
            if(posisi < 0){
                posisi = 5; 
            }
        }else if(B == 's' || B == 'S'){
            posisi++; 
            if(posisi > 5){
                posisi = 1; 
            }
        }else if(B == 13 ){
            switch(posisi) {
            case 1: 
            system("cls");
            Menu_Shipment(); 
            break;
            case 2:
            system("cls"); 
            view_all(); 
            break;
            case 3:
            system("cls"); 
            sorting_barang(); 
            break;
            case 4: 
            system("cls"); 
            search();
            break;
            case 5:
            return; 
            }
        }
    }

}
void koordinat(int x ,int y){
    COORD koordinat; 
    koordinat.X = x; 
    koordinat.Y = y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), koordinat);
}

int check_code(int pass){
    FILE *fp = fopen(filename, "r"); 
    
    if(fp == NULL){
        return 0; 
    }
    struct Datacenter Temp; 

    while(fscanf(fp, "%d %s %s %d", &Temp.item_id, Temp.item_name, Temp.item_type, &Temp.handling_code) != EOF) {
        if(pass == Temp.handling_code){
            fclose(fp);
            return 1; 
        }
    
    }
    
   fclose(fp); 
     return 0; 
}

int check_id(int pass){
    FILE *fp = fopen(filename, "r"); 
    
    if(fp == NULL){
        return 0; 
    }
    struct Datacenter Temp; 

    while(fscanf(fp, "%d %s %s %d", &Temp.item_id, Temp.item_name, Temp.item_type, &Temp.handling_code) != EOF) {
        if(pass == Temp.item_id){ 
            fclose(fp);
             return 1;
        }
    
    }
     
   fclose(fp); 
    return 0;
}
void Menu_Shipment(){

    char temp[50];
    int id; 
    char name[20]; 
    char type[30]; 
    int code; 
    int valid = 0; 
    
    printf("======================================================\n");
    printf("          SISTEM MANAJEMEN PENGIRIMAN (LOGISTIK)     \n");
    printf("======================================================\n\n");

    printf("|------- Tambah Barang Baru -------|     \n");
    printf("Masukan ITEM ID (0-9999)           :     \n");
    printf("Masukan Nama Barang(TulisanSambung):     \n");
    printf("Masukan Type Barang(FRG/STB/SPD)   :     \n");
    printf("Masukan Handling Number(1000-9999) :     \n");

    do{
        koordinat(37,5);  int status = input_digit(temp, 4);
        if(status == 1){
            return;
        }else{
            id = atoi(temp); 
            if(check_id(id) == 1){
                valid = 0; 
                koordinat(37,5); printf("Id Telah Dipakai Sebelumnya, Silahkan Buat Id Baru\n");
                getchar();
                koordinat(37,5); printf("                                                     ");
            }else{
                valid = 1; 
            }
        }
    }while(!valid);

    koordinat(37,6); 
    if(input(name, 20) == 1){
        return; 
    }

    koordinat(37,7);
    if(input_khusus(type, 3) == 1){
        return; 
    }

    
    do{
        koordinat(37,8); int check = input_digit(temp, 4);
        if(check == 1){
            return; 
        }else{
            code = atoi(temp); 
            if(check_code(code) == 1){
                valid = 0;
                koordinat(37,8); printf("Handling Code Telah Dipakai Sebelumnya, Silahkan Buat Handling Code Baru\n");
                getchar();
                koordinat(37,8); printf("                                                                          ");
            }else if(code < 1000){
                valid = 0;
                koordinat(37,8); printf("Handling Code Minimal 1000\n");
                getchar();
                koordinat(37,8); printf("                            ");
            } else{
                valid = 1;
            }
        }
    }while(!valid);
    
    FILE *fp = fopen(filename, "a"); 

    if(fp == NULL){ 
        printf("File Tidak Ditemukan"); 
        return; 
    }

    fprintf(fp, "%d %s %s %d", id, name, type, code);
    fprintf(fp,"\n");
    fclose(fp); 

    printf("\n");
    printf("Tekan enter to keluar...\n");
    getchar();
}


int input(char *temp, int panjang){
    int i = 0; 
    char B; 

    temp[0] = '\0'; 

    while(1){
        B = getch(); 

        if(B == 27 ){
            return 1; 
        }

        if(B == 13){
            temp[i] = '\0';
            return 0; 
        }

        if(B == 8 && i > 0 ){
            i--; 
            printf("\b \b"); 
        }

        if(i < panjang && isprint(B)){
            temp[i] = B; 
            i++;
            printf("%c", B); 
        }

    }
}

int input_digit(char *temp, int panjang){
    int i = 0; 
    char B; 

    temp[0] = '\0'; 

    while(1){
        B = getch(); 

        if(B == 27 ){
            return 1; 
        }

        if(B == 13){
            temp[i] = '\0';
            return 0; 
        }

        if(B == 8 && i > 0 ){
            i--; 
            printf("\b \b"); 
        }

        if(i < panjang && isdigit(B)){
            temp[i] = B; 
            i++;
            printf("%c", B);    
        }

    }
}

int input_khusus(char *temp, int panjang){
    int i = 0; 
    char B; 
    char kode[10];

    kode[0] = '\0'; 

    while(1){
        B = getch(); 

        if(B == 27 ){
            return 1; 
        }

        if(B == 13){
            kode[i] = '\0'; 
            if(strcmp(kode, "FRG") == 0){
                strcpy(temp,"Fragile"); 
                return 0; 
            } 
            if(strcmp(kode, "STB") == 0){
                strcpy(temp,"StandarHandling"); 
                return 0; 
            }
            if(strcmp(kode, "SPD") == 0){
                strcpy(temp, "SpecialHandling"); 
                return 0; 
            }
        }

        if(B == 8 && i > 0 ){
            i--; 
            printf("\b \b"); 
        }

        if(i < panjang && isprint(B)){
            char up = toupper(B); 
            kode[i] = up; 
            i++;
            printf("%c", up); 
        }
    }

}

void view_all(){

    printf("============================================================================\n");
    printf("                      SISTEM MANAJEMEN PENGIRIMAN LOGISTIK      \n");
    printf("============================================================================\n");

    printf("| %-20s | %-10s | %-20s | %-13s |\n", "Item Name", "Item ID", "Type Item", "Handling Code");
    printf("|--------------------------------------------------------------------------|\n");

    FILE *fp = fopen(filename, "r"); 

    if (fp == NULL){
        printf("|                            D A T A  K O S O N G                          |\n");
        printf("|--------------------------------------------------------------------------|\n");
        printf("\nPress Enter to exit...\n");
        getchar();
        return; 
    }

    struct Datacenter Temp; 

    while(fscanf(fp, "%d %s %s %d", &Temp.item_id, Temp.item_name, Temp.item_type, &Temp.handling_code) != EOF) {
        printf("| %-20s | %-10d | %-20s | %-13d |\n", Temp.item_name, Temp.item_id, Temp.item_type, Temp.handling_code);
    }
    printf("|==========================================================================|"); 

    fclose(fp);

    printf("\n\nTekan Enter to keluar...\n");
    getchar(); 
}

void swap(struct Datacenter *a, struct Datacenter *b) {
    struct Datacenter temp = *a;
    *a = *b;
    *b = temp;
}

int partition(struct Datacenter Data[], int low, int high) {
    int pivot = Data[high].item_id; 
    int i = (low - 1); 

    for (int j = low; j <= high - 1; j++) {
        if (Data[j].item_id < pivot) {
            i++;
            swap(&Data[i], &Data[j]);
        }
    }
    swap(&Data[i + 1], &Data[high]);
    return (i + 1);
}

void quickSort(struct Datacenter Data[], int low, int high) {
    if (low < high) {
        int pi = partition(Data, low, high);

        quickSort(Data, low, pi - 1);
        quickSort(Data, pi + 1, high);
    }
}


void sorting_barang(){
    struct Datacenter Data[100];
    int count = 0;

    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("|                D A T A   K O S O N G                |\n");
        printf("|------------------------------------------------------|\n");
        printf("\nPress Enter to exit...\n");
        getchar();
        return;
    }

    while(count < 100 && fscanf(fp, "%d %s %s %d", &Data[count].item_id, Data[count].item_name, 
                 Data[count].item_type, &Data[count].handling_code) != EOF) {
        count++;
    }
    fclose(fp);

    if (count > 0) {
        quickSort(Data, 0, count - 1);
    }

    printf("============================================================================\n");
    printf("              SISTEM SORTING PENGIRIMAN LOGISTIK (QUICK SORT)               \n");
    printf("============================================================================\n");
    printf("| %-10s | %-20s | %-20s | %-13s |\n", "Item ID", "Item Name", "Type Item", "Handling Code");
    printf("|--------------------------------------------------------------------------|\n");

    for(int i = 0; i < count; i++) {
        printf("| %-10d | %-20s | %-20s | %-13d |\n", 
               Data[i].item_id, Data[i].item_name, Data[i].item_type, Data[i].handling_code);
    }
    printf("============================================================================\n");

    printf("\nTekan Enter untuk keluar...\n");
    getchar();

}

void search(){
      int posisi = 1; 
    char B; 

    while(1){
        system("cls"); 
        printf("===========================================\n");
        printf("S H I P P E X  L O G I S T I C  S E A R C H\n");
        printf("===========================================\n\n");
        printf("[1] Search Dengan ID              %s\n" , (posisi == 1) ? "<<" : "");
        printf("[2] Search Dengan Nama            %s\n" , (posisi == 2) ? "<<" : ""); 
        printf("[3] Search Dengan Handling Code   %s\n" , (posisi == 3) ? "<<" : "");
        printf("[4] Exit                          %s\n" , (posisi == 4) ? "<<" : "");

        B = getch(); 

        if(B == 'w' || B == 'W'){
            posisi--; 
            if(posisi < 0){
                posisi = 4; 
            }
        }else if(B == 's' || B == 'S'){
            posisi++; 
            if(posisi > 4){
                posisi = 1; 
            }
        }else if(B == 13 ){
            switch(posisi) {
            case 1: 
            system("cls");
            search_id();
            break;
            case 2:
            system("cls"); 
            search_name(); 
            break;
            case 3: 
            system("cls"); 
            search_handling();
            break;
            case 4:
            return; 
            }
        }
    }
}

void search_id(){
    char temp[50];
    int id;
    int check = 0;

    do{
        system("cls");
        printf("Masukkan ID barang yang ingin dicari: ");

        koordinat(37,0);
        if(input_digit(temp,4) == 1){
            return;
        }
        id = atoi(temp);

        struct Datacenter Data[100]; 

        int count = 0; 

        FILE *fp = fopen(filename, "r"); 

        if (fp == NULL) {
            printf("|                            D A T A  K O S O N G                          |\n");
            printf("|--------------------------------------------------------------------------|\n");
            printf("\nPress Enter to exit...\n");
            getchar();
            return;
        }

        while(count < 100 && fscanf(fp, "%d %s %s %d", &Data[count].item_id, Data[count].item_name, Data[count].item_type, &Data[count].handling_code) != EOF) {
            count++;
        }

        fclose(fp);

        printf("\n============================================================================\n");
        printf("                       SISTEM SEARCHING PENGIRIMAN LOGISTIK              \n");
        printf("============================================================================\n");
        printf("| %-10s | %-20s | %-20s | %-13s |\n", "Item ID", "Item Name", "Type Item", "Handling Code");
        printf("|--------------------------------------------------------------------------|\n");    

        for(int i= 0; i < count; i++){
            if(Data[i].item_id==id){
                printf("| %-10d | %-20s | %-20s | %-13d |\n", Data[i].item_id, Data[i].item_name, Data[i].item_type, Data[i].handling_code);  
                check++;
            }
        }
        printf("============================================================================\n");

        if(check == 0){
            printf("|---------------------------Data tidak ditemukan---------------------------|\n");
            printf("============================================================================\n");
        }
        
        printf("\n\nTekan Enter...\n");
        getchar(); 
    }while(1);
}


void search_name(){
    int check = 0; 
    char search[20];
    do{
        system("cls");
        printf("Masukkan nama barang yang ingin dicari (Case-Sensitive): ");
    
        koordinat(58,0);
        if(input(search,20) == 1){
            return;
        }

        struct Datacenter Data[100]; 

        int count = 0; 

        FILE *fp = fopen(filename, "r"); 

        if (fp == NULL) {
            printf("|                            D A T A  K O S O N G                          |\n");
            printf("|--------------------------------------------------------------------------|\n");
            printf("\nPress Enter to exit...\n");
            getchar();
            return;
        }

        while(count < 100 && fscanf(fp, "%d %s %s %d", &Data[count].item_id, Data[count].item_name, Data[count].item_type, &Data[count].handling_code) != EOF) {
            count++;
        }

        fclose(fp);

        printf("\n============================================================================\n");
        printf("                       SISTEM SEARCHING PENGIRIMAN LOGISTIK              \n");
        printf("============================================================================\n");
        printf("| %-10s | %-20s | %-20s | %-13s |\n", "Item ID", "Item Name", "Type Item", "Handling Code");
        printf("|--------------------------------------------------------------------------|\n");    

        for(int i= 0; i < count; i++){
            if(strcmp(Data[i].item_name, search) == 0){
                printf("| %-10d | %-20s | %-20s | %-13d |\n", Data[i].item_id, Data[i].item_name, Data[i].item_type, Data[i].handling_code);   
                check++;
            }
        }
        printf("============================================================================\n");
        
        if(check == 0){
            printf("|---------------------------Data tidak ditemukan---------------------------|");
            printf("============================================================================\n");
        }
        
        printf("\n\nTekan Enter...\n");
        getchar();
    }while(1);
}

void search_handling(){
    char temp[50];
    int code;
    int check = 0;

    do{
        system("cls");
        printf("Masukkan Handling Code barang yang ingin dicari: ");
    
        koordinat(51,0);
        if(input_digit(temp,4) == 1){
            return;
        }
        code = atoi(temp);

        struct Datacenter Data[100]; 

        int count = 0; 

        FILE *fp = fopen(filename, "r"); 

        if (fp == NULL) {
            printf("|                            D A T A  K O S O N G                          |\n");
            printf("|--------------------------------------------------------------------------|\n");
            printf("\nPress Enter to exit...\n");
            getchar();
            return;
        }

        while(count < 100 && fscanf(fp, "%d %s %s %d", &Data[count].item_id, Data[count].item_name, Data[count].item_type, &Data[count].handling_code) != EOF) {
            count++;
        }

        fclose(fp);

        printf("\n============================================================================\n");
        printf("                      SISTEM SEARCHING PENGIRIMAN LOGISTIK              \n");
        printf("============================================================================\n");
        printf("| %-10s | %-20s | %-20s | %-13s |\n", "Item ID", "Item Name", "Type Item", "Handling Code");
        printf("|--------------------------------------------------------------------------|\n");    

        for(int i= 0; i < count; i++){
            if(Data[i].handling_code== code){
                printf("| %-10d | %-20s | %-20s | %-13d |\n", Data[i].item_id, Data[i].item_name, Data[i].item_type, Data[i].handling_code);  
                check++; 
            }
        }
        printf("============================================================================\n");

        if(check == 0){
            printf("|---------------------------Data tidak ditemukan---------------------------|");
            printf("============================================================================\n");
        }
        
        printf("\n\nTekan Enter...\n");
        getchar();
    }while(1);
    

}

void Out(){
    printf("             __________________ \n");
    printf("            /                 /| \n");
    printf("           /     SHIPPEX     / | \n");
    printf("          /_________________/  | \n");
    printf("          |                 |  | \n");
    printf("          |  [ THANK YOU ]  | /  \n");
    printf("          |_________________|/   \n\n");
    printf("=========================================\n");
    printf("   T H A N K  Y O U  F O R  U S I N G  \n");
    printf("=========================================\n\n"); 
    printf("Tekan enter untuk keluar...\n");         
    getchar();
}




