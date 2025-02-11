#include <stdio.h>
#include <time.h>


/* Do�um tarihi ile girilen tarih aras�nda ne kadar fark oldu�unu g�steren uygulama*/


// Tarih ve saat bilgisi i�in struct
struct tarihSaat {
    int gun;
    int ay;
    int yil;
    int saat;
    int dakika;
    int saniye;
};

// Hem struct tarihSaat hem de time_t (epoch) de�erini tutabilen union
union zaman {
    struct tarihSaat t;  // Kullan�c�dan al�nan tarih ve saat
    time_t epoch;        // Epoch zaman�
};

// Fonksiyon: struct tarihSaat t�r�nden epoch zaman� hesaplar
time_t tarihToEpoch(struct tarihSaat t) {
    struct tm zamanStruct = {0};

    zamanStruct.tm_mday = t.gun;
    zamanStruct.tm_mon = t.ay - 1;  // tm_mon 0-11 aral���nda oldu�u i�in 1 ��kar�yoruz
    zamanStruct.tm_year = t.yil - 1900; 
    zamanStruct.tm_hour = t.saat;
    zamanStruct.tm_min = t.dakika;
    zamanStruct.tm_sec = t.saniye;

    return mktime(&zamanStruct); // Epoch zaman�n� hesapla
}

// Fonksiyon: �ki tarih aras�ndaki fark� y�l, ay, g�n, saat, dakika, saniye cinsinden hesaplar
void zamanFarkiniHesapla(time_t epoch1, time_t epoch2) {
    int fark_saniye = epoch2 - epoch1;
    int fark_dakika = fark_saniye / 60;
    int fark_saat = fark_dakika / 60;
    int fark_gun = fark_saat / 24;
    
    int yil = fark_gun / 365;
    int ay = (fark_gun % 365) / 30; // Yakla��k hesap
    int gun = (fark_gun % 365) % 30;
    
    printf("Dogum tarihi ile girilen tarih arasindaki fark: %d yil, %d ay, %d gun, %d saat, %d dakika, %d saniye\n",
           yil, ay, gun, fark_saat % 24, fark_dakika % 60, fark_saniye % 60);
}

int main() {
    union zaman z1, z2;
    time_t epoch1, epoch2;
    
    printf("*Dogum Gununden itibaren Gecen Zamani Hesaplama Uygulamasi*\n\n");
    
    // �lk tarih ve saat bilgisi
    printf("Dogum tarihi ve saat bilgisini giriniz (GG AA YYYY SS DD SS): ");
    scanf("%d %d %d %d %d %d", &z1.t.gun, &z1.t.ay, &z1.t.yil, &z1.t.saat, &z1.t.dakika, &z1.t.saniye);
    
    // �kinci tarih ve saat bilgisi
    printf("Arasinda ne kadar fark oldugunu bilmek istediginiz tarih ve saat bilgisini giriniz (GG AA YYYY SS DD SS): ");
    scanf("%d %d %d %d %d %d", &z2.t.gun, &z2.t.ay, &z2.t.yil, &z2.t.saat, &z2.t.dakika, &z2.t.saniye);
    
    // Epoch zamanlar�n� hesapla
    epoch1 = tarihToEpoch(z1.t);
    epoch2 = tarihToEpoch(z2.t);
    
    // Sonu�lar� ekrana yazd�r
    printf("\nDogum tarihinin Epoch zamani: %ld\n", epoch1);
    printf("Arasindaki farkin bilinmek istendigi tarihin Epoch zamani: %ld\n", epoch2);
    printf("Dogum tarihi ile girilen tarih arasindaki fark (saniye olarak): %ld saniye\n", (epoch2 - epoch1));
    
    // Ayr�nt�l� zaman fark�n� hesapla
    zamanFarkiniHesapla(epoch1, epoch2);

    return 0;
}

