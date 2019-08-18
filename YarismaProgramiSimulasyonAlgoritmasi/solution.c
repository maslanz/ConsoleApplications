#include <stdio.h>
#include <stdlib.h>

#define MIN_YARISMACI_SAY 5
#define MAX_YARISMACI_SAY 20
#define MIN_HAFTA_SAY 3
#define MAX_HAFTA_SAY 10

void ana_menu();
void istatistik_alt_menu();
int sayi_al(int, int);
void hafta_siralamasi(int [], int [], int[], int[], int);
void seyirci_koc_siralamasi(int [], int [], int);
void yer_degistir(int *, int *);
void hata_nedenleri();

int main()
{
    int yarismaci_no1_seyirciler,yarismaci_no2_seyirciler,yarismaci_no3_seyirciler;
    int yarismaci_no1_koclar,yarismaci_no2_koclar,yarismaci_no3_koclar;
    int i,j,k,x,y,z,a,b,c,d;
    char cikis='h';
    int secim_ana_menu,secim_alt_menu,yarismaci_say,hafta_say;
    int yarismaci_puan_seyirci[MAX_YARISMACI_SAY]={0};
    int yarismaci_numaralari[MAX_YARISMACI_SAY]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};//siralama islemi icin
    int yarismaci_puan_koc[MAX_YARISMACI_SAY]={0};
    int yarismaci_koc_matrisi[MAX_YARISMACI_SAY][MAX_YARISMACI_SAY]={{0}}; //Yarismacilarin her koctan aldiklari toplam puan icin
    int toplam_puan[MAX_YARISMACI_SAY];

    do{
        ana_menu();
        printf("Seciminizi giriniz [1-3]: ");
        secim_ana_menu=sayi_al(1,3);

        switch(secim_ana_menu) {
            case 1:
                printf("Yarismaci sayisini giriniz [5-20]: ");
                yarismaci_say=sayi_al(MIN_YARISMACI_SAY,MAX_YARISMACI_SAY);
                printf("Yarismanin kac hafta surecegini giriniz [3-10]: ");
                hafta_say=sayi_al(MIN_HAFTA_SAY,MAX_HAFTA_SAY);
                for(i=0; i<hafta_say; i++) {
                    for(j=0; j<yarismaci_say; j++) {
                        printf("%d.kocun 1 puan verdigi yarismacinin numarasini giriniz: ",j+1);
                        scanf("%d",&yarismaci_no1_koclar);
                        while(yarismaci_no1_koclar==j+1 || yarismaci_no1_koclar>yarismaci_say) {
                            hata_nedenleri();
                            scanf("%d",&yarismaci_no1_koclar);
                        }
                        yarismaci_puan_koc[yarismaci_no1_koclar-1]++;
                        yarismaci_koc_matrisi[yarismaci_no1_koclar-1][j]++;
                        printf("%d.kocun 2 puan verdigi yarismacinin numarasini giriniz: ",j+1);
                        scanf("%d",&yarismaci_no2_koclar);
                        while(yarismaci_no2_koclar==j+1 || yarismaci_no2_koclar>yarismaci_say || yarismaci_no2_koclar==yarismaci_no1_koclar) {
                            hata_nedenleri();
                            scanf("%d",&yarismaci_no2_koclar);
                        }
                        yarismaci_puan_koc[yarismaci_no2_koclar-1]=yarismaci_puan_koc[yarismaci_no2_koclar-1]+2;
                        yarismaci_koc_matrisi[yarismaci_no2_koclar-1][j]=yarismaci_koc_matrisi[yarismaci_no2_koclar-1][j]+2;
                        printf("%d.kocun 3 puan verdigi yarismacinin numarasini giriniz: ",j+1);
                        scanf("%d",&yarismaci_no3_koclar);
                        while(yarismaci_no3_koclar==j+1 || yarismaci_no3_koclar>yarismaci_say || yarismaci_no3_koclar==yarismaci_no2_koclar || yarismaci_no3_koclar==yarismaci_no1_koclar) {
                            hata_nedenleri();
                            scanf("%d",&yarismaci_no3_koclar);
                        }
                        yarismaci_puan_koc[yarismaci_no3_koclar-1]=yarismaci_puan_koc[yarismaci_no3_koclar-1]+3;
                        yarismaci_koc_matrisi[yarismaci_no3_koclar-1][j]=yarismaci_koc_matrisi[yarismaci_no3_koclar-1][j]+3;
                    }

                    printf("Seyircinin 1 puan verdigi yarismacinin numarasini giriniz: ");
                    scanf("%d",&yarismaci_no1_seyirciler);
                    while(yarismaci_no1_seyirciler>yarismaci_say) {
                        hata_nedenleri();
                        scanf("%d",&yarismaci_no1_seyirciler);
                    }
                    yarismaci_puan_seyirci[yarismaci_no1_seyirciler-1]++;
                    printf("Seyircinin 2 puan verdigi yarismacinin numarasini giriniz: ");
                    scanf("%d",&yarismaci_no2_seyirciler);
                    while(yarismaci_no2_seyirciler>yarismaci_say || yarismaci_no2_seyirciler==yarismaci_no1_seyirciler) {
                        hata_nedenleri();
                        scanf("%d",&yarismaci_no2_seyirciler);
                    }
                    yarismaci_puan_seyirci[yarismaci_no2_seyirciler-1]=yarismaci_puan_seyirci[yarismaci_no2_seyirciler-1]+2;
                    printf("Seyircinin 3 puan verdigi yarismacinin numarasini giriniz: ");
                    scanf("%d",&yarismaci_no3_seyirciler);
                    while(yarismaci_no3_seyirciler>yarismaci_say || yarismaci_no3_seyirciler==yarismaci_no1_seyirciler || yarismaci_no3_seyirciler==yarismaci_no2_seyirciler) {
                        hata_nedenleri();
                        scanf("%d",&yarismaci_no3_seyirciler);
                    }
                    yarismaci_puan_seyirci[yarismaci_no3_seyirciler-1]=yarismaci_puan_seyirci[yarismaci_no3_seyirciler-1]+3;

                    for(x=0; x<yarismaci_say; x++)
                        toplam_puan[x]=yarismaci_puan_koc[x]+yarismaci_puan_seyirci[x]*(yarismaci_say-1);

                    hafta_siralamasi(toplam_puan,yarismaci_numaralari,yarismaci_puan_koc,yarismaci_puan_seyirci,yarismaci_say);

                    printf("%d. hafta sonunda olusan genel durum:\n",i+1);
                    printf("Sira No Yarismaci No Koc Puani Seyirci Puani Toplam Puan\n");
                    printf("------- ------------ --------- ------------- -----------\n");

                    for(k=0; k<yarismaci_say; k++)
                        printf("%4d%10d%12d%12d%13d\n",k+1,yarismaci_numaralari[k],yarismaci_puan_koc[k],yarismaci_puan_seyirci[k]*(yarismaci_say-1),toplam_puan[k]);
                }
                break;
            case 2:
                istatistik_alt_menu();
                printf("Seciminizi giriniz [1-5]: ");
                secim_alt_menu=sayi_al(1,5);

                switch(secim_alt_menu) {
                    case 1:
                        seyirci_koc_siralamasi(yarismaci_puan_koc,yarismaci_numaralari,yarismaci_say);

                        printf("Sadece koclarin puanlamasina gore genel durum:\n");
                        printf("Sira No Yarismaci No Puan\n");
                        printf("------- ------------ ----\n");

                        for(y=0; y<yarismaci_say; y++)
                            printf("%4d%10d%10d\n",y+1,yarismaci_numaralari[y],yarismaci_puan_koc[y]);
                        break;
                    case 2:
                        seyirci_koc_siralamasi(yarismaci_puan_seyirci,yarismaci_numaralari,yarismaci_say);

                        printf("Sadece seyircilerin puanlamasina gore genel durum:\n");
                        printf("Sira No Yarismaci No Puan\n");
                        printf("------- ------------ ----\n");

                        for(z=0; z<yarismaci_say; z++)
                            printf("%4d%10d%10d\n",z+1,yarismaci_numaralari[z],yarismaci_puan_seyirci[z]*(yarismaci_say-1));
                        break;
                    case 3:
                        break;
                    case 4:
                        printf("Yarismacilarin her koctan aldiklari toplam puanlar:\n");
                        printf("Yarismaci No ");
                        for(a=0; a<yarismaci_say; a++)
                            printf("Koc %d ",a+1);
                        printf("\n");
                        printf("------------ ");
                        for(b=0; b<yarismaci_say; b++)
                            printf("----- ");
                        printf("\n");

                        for(c=0; c<yarismaci_say; c++) {
                            printf("%6d",c+1);
                            printf("    ");
                            for(d=0; d<yarismaci_say; d++)
                                printf("%6d",yarismaci_koc_matrisi[c][d]);
                            printf("\n");
                        }
                        break;
                    case 5:
                        ana_menu();
                        printf("Seciminizi giriniz [1-3]: ");
                        secim_ana_menu=sayi_al(1,3);
                        break;
                }
                break;
            case 3:
                do{
                    printf("Cikmak istediginize emin misiniz? (e/E/h/H): ");
                    fflush(stdin);
                    cikis=getchar();
                }while(cikis!='e' && cikis!='E' && cikis!='h' && cikis!='H');
                break;
        }
    }while(cikis=='h' || cikis=='H');

    return 0;
}

void ana_menu()
{
    printf("        ANA MENU        \n");
    printf("        --------        \n");
    printf("1. Yeni Yarisma Duzenleme\n");
    printf("2. Son Duzenlenen Yarismanin Istatistiklerini Goruntuleme\n");
    printf("3. Cikis\n");
}

void istatistik_alt_menu()
{
    printf("        ISTATISTIK ALT MENUSU       \n");
    printf("        ---------------------       \n");
    printf("1. Sadece koclarin puanlamasi dikkate alindiginda genel durumun listelenmesi\n");
    printf("2. Sadece seyircilerin puanlamasi dikkate alindiginda genel durumun listelenmesi\n");
    printf("3. Yarismacilarin her hafta aldiklari toplam puanlarin listelenmesi\n");
    printf("4. Yarismacilarin her koctan aldiklari toplam puanlarin listelenmesi\n");
    printf("5. Ana Menu\n");
}

int sayi_al(int alt_limit, int ust_limit)
{
    int sayi;

    scanf("%d",&sayi);

    while(sayi<alt_limit || sayi>ust_limit) {
        printf("Lutfen belirtilen araliklarda bir sayi giriniz: ");
        scanf("%d",&sayi);
    }

    return sayi;
}

void hafta_siralamasi(int v1[], int v2[], int v3[], int v4[], int eleman_say)
{
    int i;
    int gecis_say=0;
    int yer_degisti;

    do{
        gecis_say++;
        yer_degisti=0;
        for(i=0;i<eleman_say-gecis_say;i++){
            if(v1[i]<v1[i+1]) {
                yer_degistir(&v1[i],&v1[i+1]);
                yer_degistir(&v2[i],&v2[i+1]);
                yer_degistir(&v3[i],&v3[i+1]);
                yer_degistir(&v4[i],&v4[i+1]);
                yer_degisti=1;
            }
            else if (v1[i]==v1[i+1] && (v2[i]>v2[i+1])) {
                    yer_degistir(&v2[i],&v2[i+1]);
                    yer_degistir(&v3[i],&v3[i+1]);
                    yer_degistir(&v4[i],&v4[i+1]);
                    yer_degisti=1;
                 }
        }
    }while(yer_degisti==1);

    return;
}

void seyirci_koc_siralamasi(int v1[], int v2[], int eleman_say)
{
    int i;
    int gecis_say=0;
    int yer_degisti;

    do{
        gecis_say++;
        yer_degisti=0;
        for(i=0;i<eleman_say-gecis_say;i++){
            if(v1[i]<v1[i+1]) {
                yer_degistir(&v1[i],&v1[i+1]);
                yer_degistir(&v2[i],&v2[i+1]);
                yer_degisti=1;
            }
            else if (v1[i]==v1[i+1] && (v2[i]>v2[i+1])) {
                    yer_degistir(&v2[i],&v2[i+1]);
                    yer_degisti=1;
                 }
        }
    }while(yer_degisti==1);

    return;
}

void yer_degistir(int *sayi1, int *sayi2)
{
    int gecici_sayi;

    gecici_sayi=*sayi1;
    *sayi1=*sayi2;
    *sayi2=gecici_sayi;

    return;
}

void hata_nedenleri()
{
    printf("Hatali giris. Hata nedenleri sunlar olabilir;\n");
    printf("-Kocun kendi yarismacisina oy vermesi\n");
    printf("-Yarismaci numarasinin yarismaci sayisindan buyuk olmasi\n");
    printf("-Puan verilen yarismacinin onceden bir puana sahip olmasi\n");
    printf("Tekrar giriniz: ");
}
