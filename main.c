#include <stdio.h>
#include <time.h>


/* Doðum tarihi ile girilen tarih arasýnda ne kadar fark olduðunu gösteren uygulama*/


// Tarih ve saat bilgisi için struct
struct tarihSaat {
    int gun;
    int ay;
    int yil;
    int saat;
    int dakika;
    int saniye;
};

// Hem struct tarihSaat hem de time_t (epoch) deðerini tutabilen union
union zaman {
    struct tarihSaat t;  // Kullanýcýdan alýnan tarih ve saat
    time_t epoch;        // Epoch zamaný
};

// Fonksiyon: struct tarihSaat türünden epoch zamaný hesaplar
time_t tarihToEpoch(struct tarihSaat t) {
    struct tm zamanStruct = {0};

    zamanStruct.tm_mday = t.gun;
    zamanStruct.tm_mon = t.ay - 1;  // tm_mon 0-11 aralýðýnda olduðu için 1 çýkarýyoruz
    zamanStruct.tm_year = t.yil - 1900; 
    zamanStruct.tm_hour = t.saat;
    zamanStruct.tm_min = t.dakika;
    zamanStruct.tm_sec = t.saniye;

    return mktime(&zamanStruct); // Epoch zamanýný hesapla
}

// Fonksiyon: Ýki tarih arasýndaki farký yýl, ay, gün, saat, dakika, saniye cinsinden hesaplar
void zamanFarkiniHesapla(time_t epoch1, time_t epoch2) {
    int fark_saniye = epoch2 - epoch1;
    int fark_dakika = fark_saniye / 60;
    int fark_saat = fark_dakika / 60;
    int fark_gun = fark_saat / 24;
    
    int yil = fark_gun / 365;
    int ay = (fark_gun % 365) / 30; // Yaklaþýk hesap
    int gun = (fark_gun % 365) % 30;
    
    printf("Dogum tarihi ile girilen tarih arasindaki fark: %d yil, %d ay, %d gun, %d saat, %d dakika, %d saniye\n",
           yil, ay, gun, fark_saat % 24, fark_dakika % 60, fark_saniye % 60);
}

int main() {
    union zaman z1, z2;
    time_t epoch1, epoch2;
    
    printf("*Dogum Gununden itibaren Gecen Zamani Hesaplama Uygulamasi*\n\n");
    
    // Ýlk tarih ve saat bilgisi
    printf("Dogum tarihi ve saat bilgisini giriniz (GG AA YYYY SS DD SS): ");
    scanf("%d %d %d %d %d %d", &z1.t.gun, &z1.t.ay, &z1.t.yil, &z1.t.saat, &z1.t.dakika, &z1.t.saniye);
    
    // Ýkinci tarih ve saat bilgisi
    printf("Arasinda ne kadar fark oldugunu bilmek istediginiz tarih ve saat bilgisini giriniz (GG AA YYYY SS DD SS): ");
    scanf("%d %d %d %d %d %d", &z2.t.gun, &z2.t.ay, &z2.t.yil, &z2.t.saat, &z2.t.dakika, &z2.t.saniye);
    
    // Epoch zamanlarýný hesapla
    epoch1 = tarihToEpoch(z1.t);
    epoch2 = tarihToEpoch(z2.t);
    
    // Sonuçlarý ekrana yazdýr
    printf("\nDogum tarihinin Epoch zamani: %ld\n", epoch1);
    printf("Arasindaki farkin bilinmek istendigi tarihin Epoch zamani: %ld\n", epoch2);
    printf("Dogum tarihi ile girilen tarih arasindaki fark (saniye olarak): %ld saniye\n", (epoch2 - epoch1));
    
    // Ayrýntýlý zaman farkýný hesapla
    zamanFarkiniHesapla(epoch1, epoch2);

    return 0;
}

