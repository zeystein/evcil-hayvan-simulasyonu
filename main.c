#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define NEED_COUNT 10

#define TOKLUK 0
#define UYKU 1
#define SEVGI 2
#define SOSYALLESME 3
#define SAGLIK 4
#define EGITIM 5
#define HIJYEN 6
#define TUVALET 7
#define EGLENCE 8
#define KONFOR 9



#define FOOD_COUNT 4
#define MAX_NEED_ENTRY_SIZE 20
#define MAX_NAME_ENTRY_SIZE 100
#define MAX_CHOICE_ENTRY_SIZE 100

#define NEED_PAIR_SIGNATURE char** needs, int* levels



void allocNeeds(NEED_PAIR_SIGNATURE);
void freeNeeds(NEED_PAIR_SIGNATURE);

void resetNeeds(NEED_PAIR_SIGNATURE);

void printNeedLevels(NEED_PAIR_SIGNATURE);
void printChoices();

void checkLevels(NEED_PAIR_SIGNATURE);

void yemekYe(NEED_PAIR_SIGNATURE);
void uyu(NEED_PAIR_SIGNATURE);
void _uyu(NEED_PAIR_SIGNATURE, int, int);
void sev(NEED_PAIR_SIGNATURE);
void sosyalles(NEED_PAIR_SIGNATURE);
void iyilestir(NEED_PAIR_SIGNATURE);
void egit(NEED_PAIR_SIGNATURE);
void temizle(NEED_PAIR_SIGNATURE);
void tuvaleteCikar(NEED_PAIR_SIGNATURE);
void eglendir(NEED_PAIR_SIGNATURE);
void rahatEttir(NEED_PAIR_SIGNATURE);


int checkFatals(NEED_PAIR_SIGNATURE);

int main() {

    char** needs = (char**)malloc(sizeof(char*)*NEED_COUNT);
    int* levels = (int*) malloc(sizeof(int)*NEED_COUNT);
    int choice = 0;
    allocNeeds(needs, levels);

    printf("SANAL BEBEK UYGULAMASINA HOS GELDINIZ !!!\n");
    printf("Bebegin ismi:EMILY \n");


    while (1){


        fseek(stdin, 0, SEEK_END);
        printNeedLevels(needs, levels);
        printChoices();
        printf("Seciminizi giriniz: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                yemekYe(needs, levels);
                break;
            case 2:
                uyu(needs, levels);
                break;
            case 3:
                sev(needs, levels);
                break;
            case 4:
                sosyalles(needs, levels);
                break;
            case 5:
                iyilestir(needs, levels);
                break;
            case 6:
                egit(needs, levels);
                break;
            case 7:
                temizle(needs, levels);
                break;
            case 8:
                tuvaleteCikar(needs, levels);
                break;
            case 9:
                eglendir(needs, levels);
                break;
            case 10:
                rahatEttir(needs, levels);
                break;
            default:
                printf("Farkli bir secenek girdiginiz icin oyun sonlaniyor...\n");

                freeNeeds(needs, levels);
                return 0;
        }

        checkLevels(needs, levels);
        if(checkFatals(needs, levels)){
            printf("Tekrar oynamak ister misiniz? (Y/N):");
            char c;
            fseek(stdin, 0, SEEK_END);
            scanf("%c", &c);
            if(tolower(c) == 'y'){
                choice = 0;
                resetNeeds(needs, levels);
                continue;
            }else{
                printf("Iyi gunler. Oyun sonlaniyor...\n");

                freeNeeds(needs, levels);
                return 0;
            }
        }



    }
 return 0;
}



void allocNeeds(char** needs, int* levels){

    char NEEDS[NEED_COUNT][MAX_NEED_ENTRY_SIZE] = {"Tokluk", "Uyku", "Sevgi", "Sosyallesme", "Saglik", "Egitim", "Hijyen", "Tuvalet", "Eglence", "Konfor"};

    for(int i = 0; i < NEED_COUNT; i++) {
        needs[i] = (char *) malloc(sizeof(char) * MAX_NEED_ENTRY_SIZE);
        strcpy(needs[i], NEEDS[i]);
    }

    for(int i = 0; i < NEED_COUNT; i++){
        levels[i] = 5;
    }

}

void freeNeeds(char** needs, int* levels){

    for(int i = 0; i < NEED_COUNT; i++)
        free(needs[i]);

    free(needs);

    free(levels);

}

void printNeedLevels(char** needs, int* levels){

    printf("|");
    for(int i = 0; i < NEED_COUNT; i++){
        printf("%s: %d | ", needs[i], levels[i]);
    }

    printf("\n");

}

void printChoices(){
    printf("-------------------------------\n");
    printf("1- Yemek ye \n");
    printf("2- Uyut \n");
    printf("3- Sevgi goster \n");
    printf("4- Sosyallestir \n");
    printf("5- Iyilestir \n");
    printf("6- Egitim ver \n");
    printf("7- Temizle \n");
    printf("8- Tuvalete cikar \n");
    printf("9- Eglendir \n");
    printf("10- Konforunu sagla \n");
    printf("-------------------------------\n");
}

//------------------- main functions -----------------------

void yemekYe(NEED_PAIR_SIGNATURE){
    char foods[FOOD_COUNT][MAX_NAME_ENTRY_SIZE] = {"Elma", "Cici Bebe", "Cekirdek", "Sut"};

    printf("----------------YIYECEKLER----------------\n");
    for(int i = 0; i < FOOD_COUNT; i++){
        printf("%d- %s\n", i+1, foods[i]);
    }
    printf("------------------------------------------\n");



    printf("Yedirmek istediginiz yiyecegi ve miktarini yaziniz(Orn. 2 elma): ");
    char choice[MAX_CHOICE_ENTRY_SIZE];
    fseek(stdin, 0, SEEK_END);
    fgets(choice, MAX_CHOICE_ENTRY_SIZE, stdin);
    printf("%s", choice);


    int count = atoi((const char *) &choice[0]);
    char foodChoice[MAX_CHOICE_ENTRY_SIZE];
    strncpy(foodChoice, choice+2, MAX_CHOICE_ENTRY_SIZE-2);

    for(int i = 0; foodChoice[i]; i++){
        foodChoice[i] = tolower(foodChoice[i]);
    }

    if(strncmp(foodChoice, "elma", 4) == 0){
        printf("-Bebek elmayi çok sevdi, fakat elmanin suyu biraz ustune akti :)\n");
        printf("*Tokluk +%d\n", 1*count);
        levels[TOKLUK] += 1*count +1;
    }else if(strncmp(foodChoice, "cici bebe", 9) == 0){
        printf("-Cici Bebe cok lezzetli ve doyurucuydu fakat bebek sutu uzerine doktu :(\n");
        printf("*Tokluk +%d, Hijyen -%d\n", 3*count, 1*count);
        levels[TOKLUK] += 3*count +1;
        levels[HIJYEN] -= 1*count +1;
    }else if(strncmp(foodChoice, "cekirdek", 8) == 0){
        printf("-Ne kadar sorumsuz bir ebeveynsin !!! Cekirdek bebegin bogazina kacti.\n");
        printf("*Saglik -%d\n", 4*count);
        levels[SAGLIK] -= 4*count;
    }else if(strncmp(foodChoice, "sut", 3)== 0){
        printf("-Sut bebegin kemik gelisimine katkida bulundu!!\n");
        printf("*Tokluk +%d, Saglik +%d\n", 2*count, 1*count);
        levels[TOKLUK] += 2*count +1;
        levels[SAGLIK] += 1*count;
    }else{
        printf("Gecersiz secim!! Hicbir sey yapmadiniz.\n");
    }



}

void uyu(NEED_PAIR_SIGNATURE){

    printf("Kac saat ve nasil uyutmak istersin? (Orn. 2 besikte)\n");
    printf("1- Besikte\n");
    printf("2- Kucakta\n");
    printf("3- Yerde\n");

    char choice[MAX_CHOICE_ENTRY_SIZE];
    fseek(stdin, 0, SEEK_END);
    fgets(choice, MAX_CHOICE_ENTRY_SIZE, stdin);
    printf("%s", choice);


    int count = atoi((const char *) &choice[0]);
    char sleepChoice[MAX_CHOICE_ENTRY_SIZE];
    strncpy(sleepChoice, choice+2, MAX_CHOICE_ENTRY_SIZE-2);

    for(int i = 0; sleepChoice[i]; i++){
        sleepChoice[i] = tolower(sleepChoice[i]);
    }

    if(strncmp(sleepChoice, "besikte", 7) == 0) {
        printf("-Besik yeni galiba, baya rahat gozukuyor :)\n");
        printf("*Uyku +%d, Saglik +%d\n", 2*count, 1);
        levels[SAGLIK] += 1 ;
        _uyu(needs, levels, 0, count);
        levels[UYKU] += 1 ;
    }
    else if(strncmp(sleepChoice, "kucakta", 7) == 0) {
        printf("-Besigin yerini tutmasa da bebek kucakta da mutlu.\n");
        printf("*Uyku +%d, Sevgi +%d\n", 1*count, 1);
        _uyu(needs, levels, 1, count);
        levels[UYKU] += 1 ;
        levels[SEVGI] += 1 ;
    }
    else if(strncmp(sleepChoice, "yerde", 5) == 0) {
        printf("-Bebek buz gibi yerde yatinca usuttu!!! \n");
        printf("*Uyku +%d, Saglik -%d, Konfor -%d\n", 1 * count, 1, 1);
        levels[SAGLIK] -= 1;
        levels[KONFOR] -= 1;
        _uyu(needs, levels, 2, count);
        levels[UYKU] += 1 ;
    }else{
        printf("Gecersiz secim!! Hicbir sey yapmadiniz.\n");
    }
}

void _uyu(NEED_PAIR_SIGNATURE, int choice, int count){


    if(choice == 0){
        levels[UYKU] += 2 ;
    }else if(choice == 1){
        levels[UYKU] += 1;
    }else if(choice == 2){
        levels[UYKU] += 1;
    }

    if(count-- > 1 ){

        _uyu(needs, levels, choice, count);
    }
}

void sev(NEED_PAIR_SIGNATURE){

    printf("1- Op\n");
    printf("2- Sacini oksa\n");
    printf("3- Guzel sozler soyle\n");

    printf("Nasil sevmek istersiniz? (Sira numarasi giriniz)\n");
    int choice = 0;
    fseek(stdin, 0, SEEK_END);
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("-Bebegin tombul yanaklarini isirasin geldi.\n");
            printf("*Sevgi +%d\n", 2);
            levels[SEVGI] += 2 + 1;
            break;
        case 2:
            printf("-Ipek gibi saclarini oksadin.\n");
            printf("*Sevgi +%d\n", 1);
            levels[SEVGI] += 1 + 1;
            break;
        case 3:
            printf("-Bebek dediklerini anlamiyor olabilir ama senin guzel enerjini kesinlikle anliyor!!.\n");
            printf("*Sevgi +%d, Egitim +%d\n", 2, 1);
            levels[SEVGI] += 2 + 1;
            levels[EGITIM] += 1 + 1;
            break;
        default:
            printf("Gecersiz secim!! Hicbir sey yapmadiniz.\n");

    }


}

void sosyalles(NEED_PAIR_SIGNATURE){

    printf("1- Parka gotur\n");
    printf("2- Komsuya birak\n");
    printf("3- Birlikte okul oncesi zoom toplantisina katilin\n");

    printf("Nasil sosyallesmek istersiniz? (Sira numarasi giriniz)\n");
    int choice = 0;
    fseek(stdin, 0, SEEK_END);
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("-Bebegin yeni arkadaslar edindi fakat her yeri pas kir icinde.\n");
            printf("*Sosyallesme +%d, Hijyen -%d\n", 2, 1);
            levels[SOSYALLESME] += 2 + 1;
            levels[HIJYEN] -= 1;
            break;
        case 2:
            printf("-Tum gun komsunun cocuguyla oynadilar, fakat ayse teyze sanki fazla tatli yedirmis.\n");
            printf("*Sosyallesme +%d, Tokluk +%d, Saglik -%d\n", 1, 1, 1);
            levels[SOSYALLESME] += 1 + 1;
            levels[TOKLUK] += 1 + 1;
            levels[SAGLIK] -= 1 ;

            break;
        case 3:
            printf("-Bebek toplantiya katilmak yerine oyun acmis!!!\n");
            printf("*Sosyallesme -%d, Egitim -%d\n", 1, 1);
            levels[SOSYALLESME] -= 1;
            levels[EGITIM] -=  1;
            break;
        default:
            printf("Gecersiz secim!! Hicbir sey yapmadiniz.\n");

    }


}

void iyilestir(NEED_PAIR_SIGNATURE){

    printf("1- Doktora gotur\n");
    printf("2- Surub icir\n");
    printf("3- Nanelimon kaynat\n");

    printf("Nasil iyilestir istersiniz? (Sira numarasi giriniz)\n");
    int choice = 0;
    fseek(stdin, 0, SEEK_END);
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("-Doktor bebegine iyi bakti\n");
            printf("*Saglik +%d\n", 3);
            levels[SAGLIK] += 3;
            break;
        case 2:
            printf("-Bebegin surubu begenmedi sanki ?\n");
            printf("*Konfor -%d, Saglik +%d\n", 1, 3);
            levels[KONFOR] -= 1;
            levels[SAGLIK] += 1 ;

            break;
        case 3:
            printf("-Bebegine dogal yollarla bakmayi tercih ettin.\n");
            printf("*Saglik +%d, Tokluk +%d\n", 2, 1);
            levels[SAGLIK] += 2;
            levels[TOKLUK] += 1 + 1;
            break;
        default:
            printf("Gecersiz secim!! Hicbir sey yapmadiniz.\n");

    }


}

void egit(NEED_PAIR_SIGNATURE){

    printf("1- Ona kitap oku\n");
    printf("2- Egitici oyun oynat\n");
    printf("3- Cizgi film izlet\n");

    printf("Nasil egitmek istersiniz? (Sira numarasi giriniz)\n");
    int choice = 0;
    fseek(stdin, 0, SEEK_END);
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("-Bebek okudugun masali sevmis gorunuyor.\n");
            printf("*Egitim +%d\n", 3);
            levels[EGITIM] += 3 + 1;
            break;
        case 2:
            printf("-Bebek oyundan pek memnun.\n");
            printf("*Egitim +%d, Eglence +%d\n", 3, 2);
            levels[EGITIM] += 3 + 1;
            levels[EGLENCE] += 2 + 1 ;

            break;
        case 3:
            printf("-Bebeginin oturmaktan sirti agridi.\n");
            printf("*Egitim +%d, Konfor -%d\n", 2, 1);
            levels[EGITIM] += 2 + 1;
            levels[KONFOR] -= 1;
            break;
        default:
            printf("Gecersiz secim!! Hicbir sey yapmadiniz.\n");

    }


}

void temizle(NEED_PAIR_SIGNATURE){

    printf("1- Altini degistir\n");
    printf("2- Legende yika\n");
    printf("3- Kiyafetlerini degistir\n");

    printf("Nasil temizlemek istersiniz? (Sira numarasi giriniz)\n");
    int choice = 0;
    fseek(stdin, 0, SEEK_END);
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("-Bebek yeni bezi ile gülüyor.\n");
            printf("*Hijyen +%d, Konfor +%d\n", 3, 2);
            levels[HIJYEN] += 3 + 1;
            levels[KONFOR] += 2 + 1;
            break;
        case 2:
            printf("-Bebek tertemiz oldu fakat su sicak oldugu icin agliyor.\n");
            printf("*Hijyen +%d, Eglence -%d\n", 3, 1);
            levels[HIJYEN] += 3 + 1;
            levels[EGLENCE] -= 1 ;

            break;
        case 3:
            printf("-Kiyafetlerini degistirdin ama koku gitmedi :(\n");
            printf("*Hijyen +%d, Konfor +%d\n", 2, 1);
            levels[HIJYEN] += 2 + 1;
            levels[KONFOR] += 1 + 1;
            break;
        default:
            printf("Gecersiz secim!! Hicbir sey yapmadiniz.\n");

    }


}

void tuvaleteCikar(NEED_PAIR_SIGNATURE){

    printf("1- Klozete yaptir\n");
    printf("2- Oldugu gibi birak\n");

    printf("Nasil tuvalete cikarmak istersiniz? (Sira numarasi giriniz)\n");
    int choice = 0;
    fseek(stdin, 0, SEEK_END);
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("-Bebek rahatlamis gorunuyor.\n");
            printf("*Tuvalet +%d\n", 3);
            levels[TUVALET] += 3 + 1;
            break;
        case 2:
            printf("-Bebek altina yapti, ve sen buna izin verdin!!!\n");
            printf("*Tuvalet +%d, Hijyen -%d\n", 3, 2);
            levels[HIJYEN] -= 2;
            levels[TUVALET] += 3 + 1 ;
            break;
        default:
            printf("Gecersiz secim!! Hicbir sey yapmadiniz.\n");

    }
}

void eglendir(NEED_PAIR_SIGNATURE){

    printf("1- Futbol oyna\n");
    printf("2- Parkta kumdan kale yap\n");
    printf("3- Telefondan oyun ac\n");

    printf("Nasil eglendirmek istersiniz? (Sira numarasi giriniz)\n");
    int choice = 0;
    fseek(stdin, 0, SEEK_END);
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("-Spor yapmak bebeginin kemik gelisimine iyi geldi.\n");
            printf("*Saglik +%d, Eglence +%d\n", 2, 3);
            levels[SAGLIK] += 2;
            levels[EGLENCE] += 3 + 1;

            break;
        case 2:
            printf("-Bebegin cok egleniyor ama ustundeki kumlari gorunce senin moralin bozuluyor :p\n");
            printf("*Hijyen -%d, Eglence +%d\n", 1, 3);
            levels[HIJYEN] -= 1;
            levels[EGLENCE] += 3 + 1 ;

            break;
        case 3:
            printf("-Tembellik etmeyi tercih ettin. Kotu bir ebeveynsin -.-\n");
            printf("*Saglik -%d, Eglence +%d, Sosyallik -%d\n", 1, 2, 1);
            levels[SAGLIK] -= 1;
            levels[EGLENCE] += 2 + 1;
            levels[SOSYALLESME] -= 1;

            break;
        default:
            printf("Gecersiz secim!! Hicbir sey yapmadiniz.\n");

    }


}

void rahatEttir(NEED_PAIR_SIGNATURE){

    printf("1- Sirtina minder koy\n");
    printf("2- Masaj yap\n");
    printf("3- Gazini cikar\n");

    printf("Nasil rahatlatmak istersiniz? (Sira numarasi giriniz)\n");
    int choice = 0;
    fseek(stdin, 0, SEEK_END);
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("-Bebeginin duzgun bir iskelet gelisimine yardimci oldun.\n");
            printf("*Konfor +%d, Saglik +%d\n", 3, 1);
            levels[KONFOR] += 3 + 1;
            levels[SAGLIK] += 1;

            break;
        case 2:
            printf("-Bebek sana her aksam masaj yaptiricagini soyluyor.\n");
            printf("*Konfor +%d\n", 3);
            levels[KONFOR] += 3 + 1;

            break;
        case 3:
            printf("-Pufff.\n");
            printf("*Konfor +%d, Tuvalet +%d\n", 2, 1);
            levels[KONFOR] += 2 + 1;
            levels[TUVALET] += 1 + 1;

            break;
        default:
            printf("Gecersiz secim!! Hicbir sey yapmadiniz.\n");

    }


}


void checkLevels(NEED_PAIR_SIGNATURE){
    for(int i = 0; i < NEED_COUNT; i++){
        if(levels[i] >= 0 && i != SAGLIK){
            levels[i]--;
        }
    }
}

void resetNeeds(NEED_PAIR_SIGNATURE){
    for(int i = 0; i < NEED_COUNT; i++){
        levels[i] = 5;
    }

}

int checkFatals(NEED_PAIR_SIGNATURE){
    if(levels[SAGLIK] <= 0){
        printf("[SAGLIK]Bebegin beti benzi atti, oldu sanirim :X\n");
        return 1;
    }else if(levels[SAGLIK] > 10){
        printf("[SAGLIK]Bebek kendini cok guclu ve saglikli hissettiginden sobayi sirtlayanilecegini dusundu. Sonu iyi olmadi!!\n");
        return 1;
    }

    if(levels[TOKLUK] <= 0){
        printf("[TOKLUK]Bebek bir deri bir kemik kalmis, bir daha bebegin olursa azicik besle lutfen !!\n");
        return 1;
    }else if(levels[TOKLUK] > 10){
        printf("[TOKLUK]Diyete girmek icin cok gec, bebek patladi!!!\n");
        return 1;
    }

    if(levels[UYKU] <= 0){
        printf("[UYKU]Bebegin gozunden uyku akiyor, gelisimi icin uyumasi gerek!! (Saglik -2)\n");
        levels[SAGLIK] -=2;
        return 0;
    }else if(levels[UYKU] > 10){
        printf("[UYKU]Bebek cok uyuyor ve hantallasti. Spor yapmasý gerek yoksa obez olacak !!(Saglik -1)\n");
        levels[SAGLIK] -= 1;
        return 0;
    }

    if(levels[SEVGI] <= 0){
        printf("[SEVGI]Bebegin sevgiye ihtiyaci var, nesin sen odun mu!! (Eglence -2)/(Sosyallesme -1)\n");
        levels[EGLENCE] -= 2;
        levels[SOSYALLESME] -= 1;
        return 0;
    }else if(levels[SEVGI] > 10){
        printf("[SEVGI]Bebegi cok sevdin ve simardi!! (Egitim -1)/(Sosyallesme -2)\n");
        levels[SOSYALLESME] -= 2;
        levels[EGITIM] -= 1;
        return 0;
    }

    if(levels[SOSYALLESME] <= 0){
        printf("[SOSYALLESME]Bebegi az disari cikar gezdir!! (Eglence -1)/(Egitim -2)\n");
        levels[EGLENCE] -= 1;
        levels[EGITIM] -= 2;
        return 0;
    }else if(levels[SOSYALLESME] > 10){
        printf("[SOSYALLESME]Bebegin eve girdigi yok, az evinde oturmali!! (Hijyen -2)/(Konfor -1)\n");
        levels[HIJYEN] -= 2;
        levels[KONFOR] -= 1;
        return 0;
    }

    if(levels[EGITIM] <= 0){
        printf("[EGITIM]Bebek kor kutuk cahil!! (Sosyallesme -2)\n");
        levels[SOSYALLESME] -= 2;
        return 0;
    }else if(levels[EGITIM] > 10){
        printf("[EGITIM]Bebek kendini cok bilmis!! Insanlar artik ona katlanamiyor (Sosyallesme -1)/(Sevgi -1)\n");
        levels[SOSYALLESME] -= 1;
        levels[SEVGI] -= 1;
        return 0;
    }

    if(levels[HIJYEN] <= 0){
        printf("[HIJYEN]Bebekten cok kotu koku geliyor!! (Saglik -2)/(Sosyallesme -1)\n");
        levels[SOSYALLESME] -= 1;
        levels[SAGLIK] -= 2;
        return 0;
    }else if(levels[HIJYEN] > 10){
        printf("[HIJYEN]Bebek temizlik hastasý oldu!! Herseye kafayi takmaktan temel islerini aksatiyor. (Uyku -1)/(Egitim -1)/(Konfor -2)\n");
        levels[UYKU] -= 1;
        levels[EGITIM] -= 1;
        levels[KONFOR] -= 2;
        return 0;
    }

    if(levels[TUVALET] <= 0){
        printf("[TUVALET]Bebek altina isicek!! (Saglik -3)\n");
        levels[SAGLIK] -= 3;
        return 0;
    }else if(levels[TUVALET] > 10){
        printf("[TUVALET]Su bebegi tuvaletten cikarir misin artik ?? (Hijyen -1)\n");
        levels[HIJYEN] -= 1;
        return 0;
    }

    if(levels[EGLENCE] <= 0){
        printf("[EGLENCE]Bebegin cani sikildi. Depresyona girmek uzere!! (Konfor -2)/(Saglik -1)\n");
        levels[SAGLIK] -= 1;
        levels[KONFOR] -= 2;
        return 0;
    }else if(levels[EGLENCE] > 10){
        printf("[EGLENCE]DUR COCUGUM YAPMA!!(bebek vazoyu kirdi)  (Saglik -2)/(Uyku -1)\n");
        levels[SAGLIK] -= 2;
        levels[UYKU] -= 1;
        return 0;
    }

    if(levels[KONFOR] <= 0){
        printf("[KONFOR]Bebegin beli agridan koptu!! (Hijyen -1)/(Saglik -2)\n");
        levels[SAGLIK] -= 2;
        levels[HIJYEN] -= 1;
        return 0;
    }else if(levels[KONFOR] > 10){
        printf("[KONFOR]Bebek yataginda o kadar rahat ki kalkmak istemiyor. (Saglik -2)/(Sosyallesme -1)/(Egitim -1)\n");
        levels[SAGLIK] -= 2;
        levels[SOSYALLESME] -= 1;
        levels[EGITIM] -= 1;
        return 0;
    }

    return 0;
}
