#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOS_KAYIT_KODU 0
#define MAX_KAYIT_SAY 900

struct aboneler{
    char ad_soyad[26];
    char birim_adi[31];
    int abone_tipi;
    int odenmis_kontor_say;
};

struct gorusme_verileri{
    int dahili_tel_no;
    char aranan_dis_hat[11];
    int gun_no;//tarih
    int baslangic_sa;
    int baslangic_dk;
    int sure;
};

void abone_bilgileri(FILE *);
void abone_bilgileri_ve_gorusmeleri(FILE *, FILE *);
void birime_gore_listele(FILE *);
void abone_tipine_gore_sayi_ve_yuzdeler(FILE *);
void bir_gundeki_gorusmeler(FILE *, FILE *);
void gune_gore_gorusme_sayilari_sureleri(FILE *, FILE *);
void dis_hat_gorusmesi_yapamayan_aboneler(FILE *);
void abone_kontor_yukleme(FILE *);
void dis_hat_gorusme_kaydi_ekle(FILE *, FILE *);
void abone_ekle(FILE *);
void abone_sil(FILE *, FILE *);
int menu();
int sayi_al(int, int);
int kontor_miktari_bulma(int, int, int);
int diziye_ekle(int);

int main()
{
    FILE *dosya1;//aboneler.dat
    FILE *dosya2;//gorusmeler.txt
    int secenek;

    if((dosya1=fopen("aboneler.dat","rb+"))==NULL) {
        printf("Aboneler dosyasi acilamadi.\n");
        return 0;
    }

    if((dosya2=fopen("gorusmeler.txt","r+"))==NULL) {
        printf("Gorusmeler dosyasi acilamadi.\n");
        return 0;
    }

    do{
        secenek=menu();
        switch(secenek) {
            case 1:
                abone_bilgileri(dosya1);
                break;
            case 2:
                abone_bilgileri_ve_gorusmeleri(dosya1,dosya2);
                break;
            case 3:
                birime_gore_listele(dosya1);
                break;
            case 4:
                abone_tipine_gore_sayi_ve_yuzdeler(dosya1);
                break;
            case 5:
                bir_gundeki_gorusmeler(dosya1,dosya2);
                break;
            case 6:
                gune_gore_gorusme_sayilari_sureleri(dosya1,dosya2);
                break;
            case 7:
                dis_hat_gorusmesi_yapamayan_aboneler(dosya1);
                break;
            case 8:
                abone_kontor_yukleme(dosya1);
                break;
            case 9:
                dis_hat_gorusme_kaydi_ekle(dosya1,dosya2);
                break;
            case 10:
                abone_ekle(dosya1);
                break;
            case 11:
                abone_sil(dosya1,dosya2);
                break;
        }
    }while(secenek!=12);

    fclose(dosya1);
    fclose(dosya2);

    return 0;
}

void abone_bilgileri(FILE *dosya1)//case1
{
    char *abone_tipleri[]={"","Akademik","Idari","Yonetici","Diger"};
    struct aboneler bir_abone;
    int dahili_tel_no;
    int dosya_kayit_no;

    printf("Bilgilerini gormek istediginiz abonenin dahili telefon numarasini giriniz: ");
    dahili_tel_no=sayi_al(100,999);
    dosya_kayit_no=dahili_tel_no-99;

    fseek(dosya1,(dosya_kayit_no-1)*sizeof(struct aboneler),SEEK_SET);
    fread(&bir_abone,sizeof(struct aboneler),1,dosya1);

    if(bir_abone.abone_tipi==BOS_KAYIT_KODU)
        printf("Girdiginiz dahili telefon numarasina sahip abone bulunmamaktadir.\n");
    else {
        printf("Tel No  Ad Soyad           Birimi                          Tip       Kontor\n");
        printf("------  -----------------  ------------------------------  --------  ------\n");
        printf("%-8d%-19s%-32s%-10s%d\n",dahili_tel_no,bir_abone.ad_soyad,bir_abone.birim_adi,abone_tipleri[bir_abone.abone_tipi],bir_abone.odenmis_kontor_say);
    }

    return;
}

void abone_bilgileri_ve_gorusmeleri(FILE *dosya1, FILE *dosya2)//case2
{
    char *abone_tipleri[]={"","Akademik","Idari","Yonetici","Diger"};
    struct aboneler bir_abone;
    struct gorusme_verileri bir_gorusme;
    int dahili_tel_no,dosya_kayit_no;
    int gecici_dakika,gecici_saat;
    int gorusme_toplam=0,gece_toplam_sure=0,gunduz_toplam_sure=0,harcanan_kontor=0;

    printf("Bilgilerini gormek istediginiz abonenin dahili telefon numarasini giriniz: ");
    dahili_tel_no=sayi_al(100,999);
    dosya_kayit_no=dahili_tel_no-99;

    rewind(dosya2);
    while(!feof(dosya2)) {
        fseek(dosya1,(dosya_kayit_no-1)*sizeof(struct aboneler),SEEK_SET);
        fread(&bir_abone,sizeof(struct aboneler),1,dosya1);

        if(bir_abone.abone_tipi==BOS_KAYIT_KODU) {
            printf("Girdiginiz dahili telefon numarasina sahip abone bulunmamaktadir.\n");
            return;
        }
        else {
            printf("Tel No  Ad Soyad           Birimi                          Tip       Kontor\n");
            printf("------  -----------------  ------------------------------  --------  ------\n");
            printf("%-8d%-19s%-32s%-10s%d\n",dahili_tel_no,bir_abone.ad_soyad,bir_abone.birim_adi,abone_tipleri[bir_abone.abone_tipi],bir_abone.odenmis_kontor_say);
        }
        break;
    }
    printf("\n");
    printf("Dis Hat Gorusmeleri:\n");
    printf("Aranan Tel No  Gun No  Baslangic   Bitis\n");
    printf("-------------  ------  ---------   -----\n");

    rewind(dosya2);
    while(!feof(dosya2)) {
        fscanf(dosya2,"%d %s %d %d %d %d\n",&bir_gorusme.dahili_tel_no,bir_gorusme.aranan_dis_hat,&bir_gorusme.gun_no,&bir_gorusme.baslangic_sa,&bir_gorusme.baslangic_dk,&bir_gorusme.sure);
        gecici_saat=bir_gorusme.baslangic_sa+(int)(bir_gorusme.sure+bir_gorusme.baslangic_dk)/60;
        gecici_dakika=(int)(bir_gorusme.sure+bir_gorusme.baslangic_dk)%60;
        if(gecici_saat>23)
            gecici_saat-=24;
        if(gecici_dakika==0)
            gecici_saat++;

        if(bir_gorusme.dahili_tel_no==dahili_tel_no) {
            printf("%-15s%-8d%02d:%02d       %02d:%02d\n",bir_gorusme.aranan_dis_hat,bir_gorusme.gun_no,bir_gorusme.baslangic_sa,bir_gorusme.baslangic_dk,gecici_saat,gecici_dakika);
            harcanan_kontor+=kontor_miktari_bulma(bir_gorusme.baslangic_sa,bir_gorusme.baslangic_dk,bir_gorusme.sure);
            if(bir_gorusme.baslangic_sa>7 && bir_gorusme.baslangic_sa<20) {
                gorusme_toplam++;
                gunduz_toplam_sure+=bir_gorusme.sure;
            }
            else {
                gorusme_toplam++;
                gece_toplam_sure+=bir_gorusme.sure;
            }
        }
    }//end of while

    printf("----------------------------------------\n");
    printf("Toplam gorusme sayisi: %d\n",gorusme_toplam);
    printf("Gunduz toplam gorusme suresi: %d dk\n",gunduz_toplam_sure);
    printf("Gece toplam gorusme suresi: %d dk\n",gece_toplam_sure);
    printf("Toplam harcanan kontor miktari: %d\n",harcanan_kontor);

    return ;
}

void birime_gore_listele(FILE *dosya1)//case3
{
    char *abone_tipleri[]={"","Akademik","Idari","Yonetici","Diger"};
    struct aboneler bir_abone;
    char birim_adi[31];
    int dahili_tel_no=0;

    printf("Abonelerinin bilgilerini gormek istediginiz birimin adini giriniz: ");
    fflush(stdin);
    gets(birim_adi);

    printf("Tel No  Ad Soyad          Birimi                           Tip       Kontor\n");
    printf("------  ----------------  -------------------------------  --------  ------\n");

    rewind(dosya1);

    while (!feof(dosya1)) {
        dahili_tel_no++;
        fread(&bir_abone,sizeof(struct aboneler),1,dosya1);
        if(strcmp(birim_adi,bir_abone.birim_adi)==0)
            printf("%-8d%-18s%-33s%-10s%d\n",dahili_tel_no+99,bir_abone.ad_soyad,bir_abone.birim_adi,abone_tipleri[bir_abone.abone_tipi],bir_abone.odenmis_kontor_say);
    }

    return;
}

void abone_tipine_gore_sayi_ve_yuzdeler(FILE *dosya1)//case4
{
    struct aboneler bir_abone;
    int akademik_say=0,idari_say=0,diger_say=0,yonetici_say=0,bos_say=0;

    rewind(dosya1);
    while(!feof(dosya1)) {
        fread(&bir_abone,sizeof(struct aboneler),1,dosya1);
        if(bir_abone.abone_tipi==1)
            akademik_say++;
        else if(bir_abone.abone_tipi==2)
                idari_say++;
            else if(bir_abone.abone_tipi==3)
                    diger_say++;
                else if(bir_abone.abone_tipi==4)
                        yonetici_say++;
    }
    bos_say=900-akademik_say-idari_say-diger_say-yonetici_say;

    printf("Abone Tipi  Abone Sayisi  Yuzde\n");
    printf("----------  ------------  -----\n");
    printf("Akademik    %d             %.2f\n",akademik_say,((float)akademik_say/9));
    printf("Idari       %d             %.2f\n",idari_say,((float)idari_say/9));
    printf("Diger       %d             %.2f\n",diger_say,((float)diger_say/9));
    printf("Yonetici    %d             %.2f\n",yonetici_say,((float)yonetici_say/9));
    printf("-------------------------------\n");
    printf("Bos         %d           %.2f\n",bos_say,((float)bos_say/9));

    return;
}

void bir_gundeki_gorusmeler(FILE *dosya1, FILE *dosya2)//case5
{
    struct aboneler bir_abone;
    struct gorusme_verileri bir_gorusme;
    int gun;

    rewind(dosya2);
    printf("Gormek istediginiz kayitlarin gun numarasini giriniz: ");
    scanf("%d",&gun);
    printf("Arayan Tel No  Arayan Ad Soyad  Aranan Tel No  Baslangic  Sure (dk)\n");
    printf("-------------  ---------------  -------------  ---------  ---------\n");

    while(!feof(dosya2)) {
        fscanf(dosya2,"%d %s %d %d %d %d\n",&bir_gorusme.dahili_tel_no,bir_gorusme.aranan_dis_hat,&bir_gorusme.gun_no,&bir_gorusme.baslangic_sa,&bir_gorusme.baslangic_dk,&bir_gorusme.sure);
        if(bir_gorusme.gun_no==gun) {
            fseek(dosya1,sizeof(struct aboneler)*(bir_gorusme.dahili_tel_no-100),SEEK_SET);
            fread(&bir_abone,sizeof(struct aboneler),1,dosya1);
            if(bir_abone.abone_tipi!=0)
                printf("%-15d%-17s%-15s%02d:%02d%8d\n",bir_gorusme.dahili_tel_no,bir_abone.ad_soyad,bir_gorusme.aranan_dis_hat,bir_gorusme.baslangic_sa,bir_gorusme.baslangic_dk,bir_gorusme.sure);
        }
    }

    return;
}

void gune_gore_gorusme_sayilari_sureleri(FILE *dosya1, FILE *dosya2)//case6
{
    struct aboneler bir_abone;
    struct gorusme_verileri bir_gorusme;
    int i;
    int gunluk_gorusme_sayisi[31];
    int gunluk_gorusme_suresi[31];
    int aylik_gorusme_sayisi=0;
    int aylik_gorusme_suresi=0;

    for(i=0; i<31; i++) {
        gunluk_gorusme_sayisi[i]=0;
        gunluk_gorusme_suresi[i]=0;
    }

    rewind(dosya2);
    while(!feof(dosya2)) {
        fscanf(dosya2,"%d %s %d %d %d %d\n",&bir_gorusme.dahili_tel_no,bir_gorusme.aranan_dis_hat,&bir_gorusme.gun_no,&bir_gorusme.baslangic_sa,&bir_gorusme.baslangic_dk,&bir_gorusme.sure);
        rewind(dosya1);
        fseek(dosya1,(bir_gorusme.dahili_tel_no-100)*sizeof(struct aboneler),SEEK_SET);
        fread(&bir_abone,sizeof(struct aboneler),1,dosya1);

        if(bir_abone.abone_tipi!=BOS_KAYIT_KODU) {
            gunluk_gorusme_sayisi[bir_gorusme.gun_no-1]++;
            gunluk_gorusme_suresi[bir_gorusme.gun_no-1]+=bir_gorusme.sure;

            aylik_gorusme_sayisi++;
            aylik_gorusme_suresi+=bir_gorusme.sure;
        }
    }
    printf("Gun  Top Gor Sayisi  Top Gor Suresi(dk)  Ortalama\n");
    printf("---  --------------  ------------------  --------\n");

    for(i=0; i<31; i++) {
        if(gunluk_gorusme_sayisi[i]!=0)
            printf("%-5d%-16d%-20d%.2f\n",i+1,gunluk_gorusme_sayisi[i],gunluk_gorusme_suresi[i],((float)gunluk_gorusme_suresi[i]/gunluk_gorusme_sayisi[i]));
    }

    printf("-------------------------------------------------\n");
    printf("Aylik toplam gorusme sayisi: %d\n",aylik_gorusme_sayisi);
    printf("Aylik toplam gorusme suresi: %d dk\n",aylik_gorusme_suresi);

    return;
}

void dis_hat_gorusmesi_yapamayan_aboneler(FILE *dosya1)//case7
{
    char *abone_tipleri[]={"","Akademik","Idari","Yonetici","Diger"};
    struct aboneler bir_abone;
    int dahili_tel_no=0;

    printf("Tel No  Ad Soyad           Birimi                          Tip       Kontor\n");
    printf("------  -----------------  ------------------------------  --------  ------\n");

    rewind(dosya1);
    while(!feof(dosya1)) {
        dahili_tel_no++;
        fread(&bir_abone,sizeof(struct aboneler),1,dosya1);
        if(bir_abone.odenmis_kontor_say<-100)
            printf("%-8d%-19s%-32s%-10s%d\n",dahili_tel_no+99,bir_abone.ad_soyad,bir_abone.birim_adi,abone_tipleri[bir_abone.abone_tipi],bir_abone.odenmis_kontor_say);
    }

    return;
}

void abone_kontor_yukleme(FILE *dosya1)//case8
{
    struct aboneler bir_abone;
    int dahili_tel_no,yuklenecek_kontor;

    printf("Kontor yuklemek istediginiz abonenin dahili telefon numarasini giriniz: ");
    dahili_tel_no=sayi_al(100,999);

    fseek(dosya1,sizeof(struct aboneler)*(dahili_tel_no-100),SEEK_SET);
    fread(&bir_abone,sizeof(struct aboneler),1,dosya1);

    if(bir_abone.abone_tipi==BOS_KAYIT_KODU)
        printf("Girdiginiz dahili telefon numarasina sahip abone bulunmamaktadir.\n");
    else {
        printf("Yuklenecek kontor miktarini giriniz: ");
        scanf("%d",&yuklenecek_kontor);
        bir_abone.odenmis_kontor_say+=yuklenecek_kontor;
        fseek(dosya1,sizeof(struct aboneler)*(dahili_tel_no-100),SEEK_SET);
        fwrite(&bir_abone,sizeof(struct aboneler),1,dosya1);
        printf("Yukleme basariyla gerceklestirildi.\n");
    }

    return;
}

void dis_hat_gorusme_kaydi_ekle(FILE *dosya1,FILE *dosya2)//case9
{
    struct aboneler bir_abone;
    struct gorusme_verileri bir_gorusme;
    int dahili_tel_no,dosya_kayit_no,gun_no,baslangic_sa,baslangic_dk,sure,harcanan_kontor=0;
    char aranan_dis_hat[11];
    char secim='E';

    do{
        printf("Gorusme kaydi eklemek istediginiz abonenin dahili telefon numarasini giriniz: ");
        dahili_tel_no=sayi_al(100,999);
        dosya_kayit_no=dahili_tel_no-99;

        fseek(dosya1,sizeof(struct aboneler)*(dosya_kayit_no-1),SEEK_SET);
        fread(&bir_abone,sizeof(struct aboneler),1,dosya1);

        if((bir_abone.abone_tipi!=BOS_KAYIT_KODU)&&(bir_abone.odenmis_kontor_say>=-100)) {
            fscanf(dosya2,"%d %s %d %d %d %d",&bir_gorusme.dahili_tel_no,bir_gorusme.aranan_dis_hat,&bir_gorusme.gun_no,&bir_gorusme.baslangic_sa,&bir_gorusme.baslangic_dk,&bir_gorusme.sure);
            bir_gorusme.dahili_tel_no=dahili_tel_no;

            printf("Aranan telefon numarasini giriniz : ");
            fflush(stdin);
            gets(aranan_dis_hat);
            strcpy(bir_gorusme.aranan_dis_hat,aranan_dis_hat);
            printf("Gorusmenin gun numarasini giriniz: ");
            scanf("%d",&gun_no);
            bir_gorusme.gun_no=gun_no;
            printf("Gorusmenin baslangic saatini giriniz: ");
            scanf("%d",&baslangic_sa);
            bir_gorusme.baslangic_sa=baslangic_sa;
            printf("Gorusmenin baslangic dakikasini giriniz: ");
            scanf("%d",&baslangic_dk);
            bir_gorusme.baslangic_dk=baslangic_dk;
            printf("Gorusmenin suresini giriniz: ");
            scanf("%d",&sure);
            bir_gorusme.sure=sure;

            FILE *dosya2 = fopen("gorusmeler.txt","a+");
            fprintf(dosya2,"%d %s %d %d %d %d\n",bir_gorusme.dahili_tel_no,bir_gorusme.aranan_dis_hat,bir_gorusme.gun_no,bir_gorusme.baslangic_sa,bir_gorusme.baslangic_dk,bir_gorusme.sure);

            harcanan_kontor=kontor_miktari_bulma(bir_gorusme.baslangic_sa,bir_gorusme.baslangic_dk,bir_gorusme.sure);
            bir_abone.odenmis_kontor_say=bir_abone.odenmis_kontor_say-harcanan_kontor;

            fseek(dosya1,sizeof(struct aboneler)*(dosya_kayit_no-1),SEEK_SET);
            fwrite(&bir_abone,sizeof(struct aboneler),1,dosya1);

            printf("Gorusme kaydi basariyla eklendi!\n");
            fclose(dosya2);
        }
        else
            printf("Bu numaraya sahip bir abone yok veya abonenin kontoru yetersiz.\n");


        printf("Baska kayit eklemek icin 'E' veya 'e' ye, menuye donmek icin herhangi bir tusa basiniz: ");
        fflush(stdin);
        gets(&secim);
    }while(secim == 'E' || secim == 'e');

    return;
}

void abone_ekle(FILE *dosya1)//case10
{
    struct aboneler bir_abone;
    int dahili_tel_no;
    int dosya_kayit_no;

    printf("Eklemek istediginiz yeni abonenin dahili telefon numarasini giriniz: ");
    dahili_tel_no=sayi_al(100,999);
    dosya_kayit_no=dahili_tel_no-99;

    fseek(dosya1,(dosya_kayit_no-1)*sizeof(struct aboneler),SEEK_SET);
    fread(&bir_abone,sizeof(struct aboneler),1,dosya1);

    if(bir_abone.abone_tipi!=BOS_KAYIT_KODU)
        printf("Girdiginiz dahili telefon numarasina sahip abone bulunmaktadir.\n");
    else {
        printf("Abonenin adini ve soyadini giriniz: ");
        fflush(stdin);
        gets(bir_abone.ad_soyad);
        printf("Abonenin bulundugu birimin adini giriniz: ");
        fflush(stdin);
        gets(bir_abone.birim_adi);
        printf("Abone tipini giriniz [1:Akademik, 2:Idari, 3:Yonetici, 4:Diger]: ");
        bir_abone.abone_tipi=sayi_al(1,4);
        printf("Abonenin on odenmis kontor sayisini giriniz: ");
        scanf("%d",&bir_abone.odenmis_kontor_say);

        fseek(dosya1,(dosya_kayit_no-1)*sizeof(struct aboneler),SEEK_SET);
        fwrite(&bir_abone,sizeof(struct aboneler),1,dosya1);
        printf("Ekleme islemi basariyla gerceklestirildi.\n");
    }

    return;
}

void abone_sil(FILE *dosya1, FILE*dosya2)//case11
{
    struct aboneler bir_abone,bos_abone={"","",0,0};
    struct gorusme_verileri bir_gorusme;
    int dahili_tel_no;
    int dosya_kayit_no;

    printf("Silmek istediginiz abonenin dahili telefon numarasini giriniz: ");
    dahili_tel_no=sayi_al(100,999);
    dosya_kayit_no=dahili_tel_no-99;

    fseek(dosya1,sizeof(struct aboneler)*(dosya_kayit_no-1),SEEK_SET);
    fread(&bir_abone,sizeof(struct aboneler),1,dosya1);

    if(bir_abone.abone_tipi!=BOS_KAYIT_KODU) {
       fseek(dosya1,sizeof(struct aboneler)*(dosya_kayit_no-1),SEEK_SET);
       fwrite(&bos_abone,sizeof(struct aboneler),1,dosya1);

       diziye_ekle(bir_gorusme.dahili_tel_no);
       printf("Silme islemi basariyla gerceklestirildi.\n");
    }
    else
        printf("Girdiginiz dahili telefon numarasina sahip abone bulunmamaktadir.\n");

    return;
}

int menu()
{
    int secim;

    printf("\n");
    printf("                  MENU                 \n");
    printf("                  ----                 \n");
    printf("1. Bir abonenin bilgilerinin listelenmesi\n");
    printf("2. Bir abonenin bilgilerinin ve o ay yapmis oldugu dis hat gorusmelerinin listelenmesi\n");
    printf("3. Bir birimdeki abonelerin bilgilerinin listelenmesi\n");
    printf("4. Abone tipine gore abone sayilarinin ve yuzdelerinin listelenmesi\n");
    printf("5. Bir gun yapilan gorusmelerin listelenmesi\n");
    printf("6. Gune gore gorusme sayilarinin ve surelerinin listelenmesi\n");
    printf("7. Dis hat gorusmesi yapabilmek icin kontor yuklemesi gereken abonelerin listelenmesi\n");
    printf("8. Bir abonenin kontor yuklemesi\n");
    printf("9. Yapilan dis hat gorusmelerine iliskin kayitlarin eklenmesi\n");
    printf("10. Yeni bir abonenin eklenmesi\n");
    printf("11. Bir abonenin kaydinin silinmesi\n");
    printf("12. Cikis\n");
    printf("\n");

    printf("Seciminizi giriniz [1,12]: ");
    secim=sayi_al(1,12);

    return secim;
}

int sayi_al(int alt_limit, int ust_limit)
{
    int sayi;

    scanf("%d",&sayi);

    while(sayi<alt_limit || sayi>ust_limit) {
        printf("Lutfen belirtilen araliklarda bir sayi giriniz [%d,%d]: ",alt_limit,ust_limit);
        scanf("%d",&sayi);
    }

    return sayi;
}

int kontor_miktari_bulma(int saat, int dakika, int sure)
{
    int harcanan_kontor;
    int gunun_bitmesine_kalan;

    if(saat>7 && saat<20) {
        gunun_bitmesine_kalan=60*(20-saat)-dakika;
        if(gunun_bitmesine_kalan>sure)
            return harcanan_kontor=3+3*sure;
        else
            return harcanan_kontor=3+3*gunun_bitmesine_kalan+2*(sure-gunun_bitmesine_kalan);
    }
    else {
        if(saat>19 && saat<=23) {
            gunun_bitmesine_kalan=60*(32-saat)-dakika;
            if(gunun_bitmesine_kalan>sure)
                return harcanan_kontor=3+2*sure;
            else
                return harcanan_kontor=3+2*gunun_bitmesine_kalan+3*(sure-gunun_bitmesine_kalan);
        }
        else {
            gunun_bitmesine_kalan=60*(8-saat)-dakika;
            if(gunun_bitmesine_kalan>sure)
                return harcanan_kontor=3+2*sure;
            else
                return harcanan_kontor=3+2*gunun_bitmesine_kalan+3*(sure-gunun_bitmesine_kalan);
        }
    }
}

int diziye_ekle(int eklenecek)
{
   int i,dizi[MAX_KAYIT_SAY];

   for(i=0;i<MAX_KAYIT_SAY;i++) {
      if(0==dizi[i]) {
         dizi[i]=eklenecek;
         return 1;
      }
   }
   return 0;
}
