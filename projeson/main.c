#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//algoritma final proje ödevi

/*
1. Adým : baslat
2. Adým : ekrana "Ýþlem seçin: 8-Giriþ yap, 9-Üye ol" mesajýný yazdýr
3. Adým : kullanýcýnýn seçimini oku
4. Adým : eðer seçim 9 ise kullanýcýdan yeni isim (i) bilgisini al
5. Adým : isim alma iþlemi bitince kullanýcýyý tekrar en baþa giriþ ekranýna yönlendir
6. Adým : eðer seçim 8 ise kullanýcýdan sisteme kayýtlý ismini (w) girmesini iste
7. Adým : girilen ismin (w) sistemdeki kayýtla eþleþip eþleþmediðini kontrol et
8. Adým : eðer isim yanlýþsa ekrana "Çýkýþ: Yanlýþ isim" yazdýr ve programý durdur
9. Adým : eðer isim doðruysa "Ýþlem Geçmiþi" adýnda boþ bir dizi/liste tanýmla
10. Adým : kullanýcýdan hesabýndaki mevcut baþlangýç bakiyesini girmesini iste
11. Adým : kullanýcýnýn girdiði bakiye miktarýný "bakiye" deðiþkenine ata
12. Adým : ekrana 1-para yatýrma 2-para Çekme 3-iþlem Geçmiþi 4-bakiye Sorgulama ve 5-çýkýþ seçeneklerini bas
13. Adým : kullanýcýnýn yapmak istediði iþlem numarasýný (seçim) oku
14. Adým : eðer seçim 1 ise yatýrýlacak tutarý (k) kullanýcýdan iste
15. Adým : mevcut bakiyeye girilen tutarý ekle (bakiye = bakiye + k)
16. Adým : güncel bakiyeyi ekrana yazdýr ve bu yatýrma iþlemini "iþlem geçmiþi" dizisine kaydet
17. Adým : baþka iþlem yapýlýp yapýlmayacaðýný sor evet ise ana menüye dön
18. Adým : eðer seçim 2 ise çekilmek istenen tutarý (t) kullanýcýdan iste
19. Adým : istenen tutarýn (t) bakiyeden büyük olup olmadýðýný kontrol et
20. Adým : eðer bakiye yetersizse "yetersiz bakiye" uyarýsý ver ve tutar girme adýmýna geri dön
21. Adým : eðer bakiye yeterliyse tutarý bakiyeden düþ (bakiye = bakiye - t) ve iþlemi geçmiþe kaydet
22. Adým : eðer seçim 3 ise "iþlem geçmiþi" dizisinin içindeki tüm kayýtlarý ekrana yazdýr
23. Adým : eðer seçim 4 ise "mevcut bakiyeniz: bakiye" þeklinde güncel tutarý göster
24. Adým : eðer seçim 5 ise Çýkýþ iþlemini onayla ve programý sonlandýr
25. Adým : eðer 1-5 arasý dýþýnda bir rakam girilirse "geçersiz seçenek" uyarýsý vererek menüye yönlendir
26. adým : bitir
*/


//BANKA BÝSLESTÝRÝCÝ
//BU PROJEYÝ YAPMAKTAKÝ AMACIM BÜTÜN BANKALRDAKÝ PARALARI BÝR SÝSTEME TOPLAMAK BÖYLECE SAHISLAR GÜNCEL OLARAK NE KADAR PARAYA SAHÝP OLDUKLARINI BANKA BANKA GEZEMELERÝNE GEREK KALMADAN TEK BÝR SÝSTEM ÜZERÝNDEN GÖREBÝLÝRLER  
void dosyada_bakiye_guncelle(char *kullanici_adi, float yeni_bakiye) {
    FILE *dosya, *gecici_dosya;
    char dosya_isim[50];
    float dosya_bakiye;

    dosya = fopen("kullanicilar.txt", "r");
    gecici_dosya = fopen("temp.txt", "w");

    if (dosya == NULL || gecici_dosya == NULL) return;

    while (fscanf(dosya, "%s %f", dosya_isim, &dosya_bakiye) != EOF) {
        if (strcmp(dosya_isim, kullanici_adi) == 0) {
            fprintf(gecici_dosya, "%s %.2f\n", dosya_isim, yeni_bakiye);
        } else {
            fprintf(gecici_dosya, "%s %.2f\n", dosya_isim, dosya_bakiye);
        }
    }

    fclose(dosya);
    fclose(gecici_dosya);
    remove("kullanicilar.txt");
    rename("temp.txt", "kullanicilar.txt");
}



void islemi_kaydet(char *kullanici_adi, float miktar) {
    FILE *fp = fopen("islemler.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s %.2f\n", kullanici_adi, miktar);
        fclose(fp);
    }
}



void gecmisi_goster(char *kullanici_adi) {
    FILE *fp = fopen("islemler.txt", "r");
    char dosya_isim[50];
    float dosya_miktar;
    int sayac = 1;

    printf("\n--- %s ICIN TUM ISLEM GECMISI ---\n", kullanici_adi);
    if (fp == NULL) {
        printf("Kayit bulunamadi.\n");
        return;
    }

    while (fscanf(fp, "%s %f", dosya_isim, &dosya_miktar) != EOF) {
        if (strcmp(dosya_isim, kullanici_adi) == 0) {
            if (dosya_miktar > 0)
                printf("%d. +%.2f TL (Yatirma)\n", sayac, dosya_miktar);
            else
                printf("%d. %.2f TL (Cekme)\n", sayac, dosya_miktar);
            sayac++;
        }
    }
    fclose(fp);
}



int main() {
    int ana_secim;
    int program_calisiyor = 1;
    int i; 
    
    
    
    while (program_calisiyor) {
        printf("\n==========================\n");
        printf("\n[[[ BANKA BISLESTIRICI ]]]\n");
        printf("\n==========================\n");
        
        printf("1: Giris Yap\n2: Uye Ol\n0: Cikis\nSecim: ");
        scanf("%d", &ana_secim);

        if (ana_secim == 2) {
            char yeni_isim[50];
            float ilk_bakiye;
            printf("Isim: "); scanf("%s", yeni_isim);
            printf("Mevcut bakiyeniz?: "); scanf("%f", &ilk_bakiye);

            FILE *fp = fopen("kullanicilar.txt", "a");
            if (fp != NULL) {
                fprintf(fp, "%s %.2f\n", yeni_isim, ilk_bakiye);
                fclose(fp);
                printf("KAYIDINIZ OLUSTURULDU\n");
            }
        } 
        else if (ana_secim == 1) {
            char girilen_isim[50];
            char dosya_isim[50];
            float dosya_bakiye, mevcut_bakiye = 0;
            int bulundu = 0;

            printf("Kullanici adiniz?: "); scanf("%s", girilen_isim);

            FILE *fp = fopen("kullanicilar.txt", "r");
            if (fp != NULL) {
                while (fscanf(fp, "%s %f", dosya_isim, &dosya_bakiye) != EOF) {
                    if (strcmp(girilen_isim, dosya_isim) == 0) {
                        bulundu = 1;
                        mevcut_bakiye = dosya_bakiye;
                        break;
                    }
                }
                fclose(fp);
            }
            
            
            

            if (!bulundu) {
                printf("////---GECERSIZ KULLANICI---////\n");
            } else {
                int islem_menusu = 1;
                while (islem_menusu) {
                    printf("\n1:Para yatir 2:Para cek 3:islem gecmisi 4:bakiye sorgulama 5:Cikis\nSecim: ");
                    int sec; scanf("%d", &sec);

                    if (sec == 1) {
                        float k; printf("yatirilacak miktar: "); scanf("%f", &k);
                        mevcut_bakiye += k;
                        dosyada_bakiye_guncelle(girilen_isim, mevcut_bakiye);
                        islemi_kaydet(girilen_isim, k);
                    } 
                    else if (sec == 2) {
                        float t; printf("cekilecek miktar: "); scanf("%f", &t);
                        if (t > mevcut_bakiye) printf("yetersiz bakiye!!\n");
                        else {
                            mevcut_bakiye -= t;
                            dosyada_bakiye_guncelle(girilen_isim, mevcut_bakiye);
                            islemi_kaydet(girilen_isim, -t);
                        }
                    } 
                    else if (sec == 3) {
                        gecmisi_goster(girilen_isim);
                    } 
                    else if (sec == 4) {
                        printf("mevcut bakiyeniz: %.2f TL\n", mevcut_bakiye);
                    } 
                    else if (sec == 5) {
                        islem_menusu = 0;
                    }
                }
            }
            
            
        } 
        else if (ana_secim == 0) {
            program_calisiyor = 0;
        }
    }
    
    
    
    
    return 0;
}
