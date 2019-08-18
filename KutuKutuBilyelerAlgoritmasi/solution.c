#include <stdio.h>
#include <stdlib.h>

int main()
{
    int sayac_kutu,sayac_farklilik,sayac_esitlik1,sayac_esitlik2;
    int sayac_hatali_kutu,sayac_hepsi_esit,sayac_bir_farkli_hafif,sayac_bir_farkli_agir;
    int hatali_bilye,dogru_bilye,max_agirlik_fark,max_yuzde_fark_degeri;
    int max_bilye_say,min_bilye_say,max_agirlik,min_agirlik;
    int i,agirlik_fark,agirlik_fark_top_agir,agirlik_fark_top_hafif;
    int bilye_say,bilye_agirlik,ilk_bilye,ikinci_bilye;
    float yuzde_hatali_kutu,yuzde_hepsi_esit,yuzde_bir_farkli_hafif,yuzde_bir_farkli_agir;
    float yuzde_agirlik_fark,agirlik_fark_ort_agir,agirlik_fark_ort_hafif;
    float yuzde_agirlik_fark_top_agir,yuzde_agirlik_fark_top_hafif,max_yuzde_fark;
    float yuzde_agirlik_fark_ort_agir,yuzde_agirlik_fark_ort_hafif,max_agirlik_fark_yuzdesi;
    char cevap;

    sayac_kutu=0;
    sayac_hatali_kutu=0;
    sayac_bir_farkli_agir=0;
    sayac_bir_farkli_hafif=0;
    sayac_hepsi_esit=0;
    max_bilye_say=0;
    min_bilye_say=0;
    min_agirlik=9999;
    max_agirlik=0;
    max_agirlik_fark=0;
    max_agirlik_fark_yuzdesi=0;
    max_yuzde_fark=0;
    max_yuzde_fark_degeri=0;
    hatali_bilye=0;
    dogru_bilye=0;
    agirlik_fark=0;
    agirlik_fark_top_agir=0;
    agirlik_fark_top_hafif=0;
    yuzde_agirlik_fark_top_agir=0;
    yuzde_agirlik_fark_top_hafif=0;
    agirlik_fark_ort_agir=0;
    yuzde_agirlik_fark_ort_agir=0;
    agirlik_fark_ort_hafif=0;
    yuzde_agirlik_fark_ort_hafif=0;

    do{
        sayac_kutu++;
        printf("%d. kutudaki bilye sayisini giriniz: ",sayac_kutu);
        scanf("%d",&bilye_say);
        while(bilye_say<10) {
            printf("Bilye sayisi 10 veya uzerinde olmalidir. Tekrar giriniz: ");
            scanf("%d",&bilye_say);
        }
        sayac_farklilik=0;
        sayac_esitlik1=0; //Kutudaki tum bilyelerin esit oldugu durum icin karsilastirma yapar.
        sayac_esitlik2=0; //Kutudaki 1 bilyenin farkli agirlikta oldugu durum icin karsilastirma yapar.
        i=1;
        printf("%d. bilyenin mg cinsinden agirligini giriniz: ",i);
        scanf("%d",&ilk_bilye);
        while(ilk_bilye<=0) {
            printf("Lutfen pozitif bir deger giriniz: ");
            scanf("%d",&ilk_bilye);
        }
        printf("%d. bilyenin mg cinsinden agirligini giriniz: ",i+1);
        scanf("%d",&ikinci_bilye);
        while(ikinci_bilye<=0) {
            printf("Lutfen pozitif bir deger giriniz: ");
            scanf("%d",&ikinci_bilye);
        }

        if(ilk_bilye<ikinci_bilye)
            sayac_farklilik++;
        else
            if(ilk_bilye>ikinci_bilye)
                sayac_farklilik++;
            else
                if(ilk_bilye==ikinci_bilye) {
                    sayac_esitlik1++;
                    sayac_esitlik2++;
                }

        for(i=3; i<=bilye_say; i++) {
            printf("%d. bilyenin mg cinsinden agirligini giriniz: ",i);
            scanf("%d",&bilye_agirlik);
            while(bilye_agirlik<=0) {
                printf("Lutfen pozitif bir deger giriniz: ");
                scanf("%d",&bilye_agirlik);
            }
            if(bilye_agirlik>ilk_bilye && bilye_agirlik>ikinci_bilye)
                sayac_farklilik++;
            else
                if(bilye_agirlik>ilk_bilye && bilye_agirlik<ikinci_bilye)
                    sayac_farklilik++;
            else
                if(bilye_agirlik<ilk_bilye && bilye_agirlik>ikinci_bilye)
                    sayac_farklilik++;
            else
                if(bilye_agirlik<ilk_bilye && bilye_agirlik<ikinci_bilye)
                    sayac_farklilik++;
            else
                if(bilye_agirlik==ilk_bilye && bilye_agirlik==ikinci_bilye) {
                    sayac_esitlik1++;
                    sayac_esitlik2++;
                }
            else
                if((bilye_agirlik!=ilk_bilye && bilye_agirlik==ikinci_bilye) || (bilye_agirlik==ilk_bilye && bilye_agirlik!=ikinci_bilye))
                    sayac_esitlik2++;

            if(sayac_farklilik>1) {
                printf("Kutu hatali uretilmistir.\n");
                sayac_hatali_kutu++;
                hatali_bilye=hatali_bilye+bilye_say;
                break;
            }
        }//end of for

        if(sayac_esitlik1==bilye_say-1) {
            printf("Kutudaki bilyelerin tumu birbiriyle esit agirliktadir.\n");
            sayac_hepsi_esit++;
            dogru_bilye=dogru_bilye+bilye_say;
            if(max_bilye_say<bilye_say) {
                max_bilye_say=bilye_say;
                max_agirlik=bilye_agirlik;
                }
                if(min_agirlik>bilye_agirlik) {
                    min_agirlik=bilye_agirlik;
                    min_bilye_say=bilye_say;
                }
            }
            if(sayac_esitlik2==bilye_say-2) {
                dogru_bilye=dogru_bilye+bilye_say;
                if(ilk_bilye==ikinci_bilye && ilk_bilye>bilye_agirlik) {
                    printf("Kutudaki bilyelerden biri digerlerine gore daha hafiftir.\n");
                    sayac_bir_farkli_hafif++;
                    agirlik_fark=ilk_bilye-bilye_agirlik;
                    yuzde_agirlik_fark=(float)agirlik_fark*100/bilye_agirlik;
                    agirlik_fark_top_hafif=agirlik_fark_top_hafif+agirlik_fark;
                    yuzde_agirlik_fark_top_hafif=(float)yuzde_agirlik_fark_top_hafif+yuzde_agirlik_fark;
                    printf("Bilyeler arasindaki agirlik farki ve yuzdesi: %d , %.2f\n",agirlik_fark,yuzde_agirlik_fark);
                }else
                    if(ilk_bilye==bilye_agirlik && ilk_bilye>ikinci_bilye) {
                        printf("Kutudaki bilyelerden biri digerlerine gore daha hafiftir.\n");
                        sayac_bir_farkli_hafif++;
                        agirlik_fark=ilk_bilye-ikinci_bilye;
                        yuzde_agirlik_fark=(float)agirlik_fark*100/ikinci_bilye;
                        agirlik_fark_top_hafif=agirlik_fark_top_hafif+agirlik_fark;
                        yuzde_agirlik_fark_top_hafif=(float)yuzde_agirlik_fark_top_hafif+yuzde_agirlik_fark;
                        printf("Bilyeler arasindaki agirlik farki ve yuzdesi: %d , %.2f\n",agirlik_fark,yuzde_agirlik_fark);
                    }else
                        if(ikinci_bilye==bilye_agirlik && ikinci_bilye>ilk_bilye) {
                            printf("Kutudaki bilyelerden biri digerlerine gore daha hafiftir.\n");
                            sayac_bir_farkli_hafif++;
                            agirlik_fark=ikinci_bilye-ilk_bilye;
                            yuzde_agirlik_fark=(float)agirlik_fark*100/ilk_bilye;
                            agirlik_fark_top_hafif=agirlik_fark_top_hafif+agirlik_fark;
                            yuzde_agirlik_fark_top_hafif=(float)yuzde_agirlik_fark_top_hafif+yuzde_agirlik_fark;
                            printf("Bilyeler arasindaki agirlik farki ve yuzdesi: %d , %.2f\n",agirlik_fark,yuzde_agirlik_fark);
                        }

                agirlik_fark_ort_hafif=(float)agirlik_fark_top_hafif/sayac_bir_farkli_hafif;
                yuzde_agirlik_fark_ort_hafif=(float)yuzde_agirlik_fark_top_hafif/sayac_bir_farkli_hafif;

                if(ilk_bilye==ikinci_bilye && ilk_bilye<bilye_agirlik) {
                    printf("Kutudaki bilyelerden biri digerlerine gore daha agirdir.\n");
                    sayac_bir_farkli_agir++;
                    agirlik_fark=bilye_agirlik-ilk_bilye;
                    yuzde_agirlik_fark=(float)agirlik_fark*100/ilk_bilye;
                    agirlik_fark_top_agir=agirlik_fark_top_agir+agirlik_fark;
                    yuzde_agirlik_fark_top_agir=(float)yuzde_agirlik_fark_top_agir+yuzde_agirlik_fark;
                    printf("Bilyeler arasindaki agirlik farki ve yuzdesi: %d , %.2f\n",agirlik_fark,yuzde_agirlik_fark);
                }else
                    if(ilk_bilye==bilye_agirlik && ilk_bilye<ikinci_bilye) {
                       printf("Kutudaki bilyelerden biri digerlerine gore daha agirdir.\n");
                       sayac_bir_farkli_agir++;
                       agirlik_fark=ikinci_bilye-ilk_bilye;
                       yuzde_agirlik_fark=(float)agirlik_fark*100/ilk_bilye;
                       agirlik_fark_top_agir=agirlik_fark_top_agir+agirlik_fark;
                       yuzde_agirlik_fark_top_agir=(float)yuzde_agirlik_fark_top_agir+yuzde_agirlik_fark;
                       printf("Bilyeler arasindaki agirlik farki ve yuzdesi: %d , %.2f\n",agirlik_fark,yuzde_agirlik_fark);
                    }else
                        if(ikinci_bilye==bilye_agirlik && ikinci_bilye<ilk_bilye) {
                           printf("Kutudaki bilyelerden biri digerlerine gore daha agirdir.\n");
                           sayac_bir_farkli_agir++;
                           agirlik_fark=ilk_bilye-ikinci_bilye;
                           yuzde_agirlik_fark=(float)agirlik_fark*100/ikinci_bilye;
                           agirlik_fark_top_agir=agirlik_fark_top_agir+agirlik_fark;
                           yuzde_agirlik_fark_top_agir=(float)yuzde_agirlik_fark_top_agir+yuzde_agirlik_fark;
                           printf("Bilyeler arasindaki agirlik farki ve yuzdesi: %d , %.2f\n",agirlik_fark,yuzde_agirlik_fark);
                        }

                agirlik_fark_ort_agir=(float)agirlik_fark_top_agir/sayac_bir_farkli_agir;
                yuzde_agirlik_fark_ort_agir=(float)yuzde_agirlik_fark_top_agir/sayac_bir_farkli_agir;

                if(max_agirlik_fark<agirlik_fark) {
                    max_agirlik_fark=agirlik_fark;
                    max_agirlik_fark_yuzdesi=yuzde_agirlik_fark;
                }

                if(max_yuzde_fark<yuzde_agirlik_fark) {
                    max_yuzde_fark=yuzde_agirlik_fark;
                    max_yuzde_fark_degeri=agirlik_fark;
                }
            }

        do{
            printf("\n");
            printf("Bilgilerini girmek istediginiz baska kutu var mi?\n");
            printf("Cevabiniz evet ise e veya E; hayir ise h veya H giriniz: ");
            fflush(stdin);
            cevap=getchar();
        }while(cevap!='e' && cevap!='E' && cevap!='h' && cevap!='H');
    }while(cevap=='e' || cevap=='E');

    yuzde_hatali_kutu=(float)sayac_hatali_kutu*100/sayac_kutu;
    yuzde_hepsi_esit=(float)sayac_hepsi_esit*100/(sayac_kutu-sayac_hatali_kutu);
    yuzde_bir_farkli_hafif=(float)sayac_bir_farkli_hafif*100/(sayac_kutu-sayac_hatali_kutu);
    yuzde_bir_farkli_agir=(float)sayac_bir_farkli_agir*100/(sayac_kutu-sayac_hatali_kutu);

    printf("\n");
    printf("Uretim hatasi olan kutu sayisi ve tum kutular icindeki yuzdesi: %d , %.2f\n",sayac_hatali_kutu,yuzde_hatali_kutu);
    printf("Iade edilen bilye sayisi: %d\n",hatali_bilye);
    printf("Kabul edilen bilye sayisi: %d\n",dogru_bilye);
    printf("Icindeki tum bilyelerin esit agirlikta oldugu kutularin sayisi ve uretim hatasi olmayan kutular icindeki yuzdesi: %d , %.2f\n",sayac_hepsi_esit,yuzde_hepsi_esit);
    printf("Icindeki 1 bilyenin digerlerinden daha hafif oldugu kutularin sayisi ve uretim hatasi olmayan kutular icindeki yuzdesi: %d , %.2f\n",sayac_bir_farkli_hafif,yuzde_bir_farkli_hafif);
    printf("Icindeki 1 bilyenin digerlerinden daha agir oldugu kutularin sayisi ve uretim hatasi olmayan kutular icindeki yuzdesi: %d , %.2f\n",sayac_bir_farkli_agir,yuzde_bir_farkli_agir);
    printf("Tum bilyelerin esit agirlikta oldugu kutular arasinda, icinde en cok bilye olan kutudaki bilye sayisi ve o kutudaki 1 bilyenin agirligi: %d , %d\n",max_bilye_say,max_agirlik);
    printf("Tum bilyelerin esit agirlikta oldugu kutular arasinda, icinde en hafif bilyeler olan kutudaki bilye sayisi ve o kutudaki 1 bilyenin agirligi: %d , %d\n",min_bilye_say,min_agirlik);
    printf("1 bilyenin digerlerinden daha agir oldugu kutulardaki agir olan bilyelerin agirlik farki degerlerinin ve yuzdelerinin ortalamalari: %.2f , %.2f\n",agirlik_fark_ort_agir,yuzde_agirlik_fark_ort_agir);
    printf("1 bilyenin digerlerinden daha hafif oldugu kutulardaki hafif olan bilyelerin agirlik farki degerlerinin ve yuzdelerinin ortalamalari: %.2f , %.2f\n",agirlik_fark_ort_hafif,yuzde_agirlik_fark_ort_hafif);
    printf("Farkli olan bilyenin agirliginin diger bilyelerin agirligiyla arasindaki farkin degerinin en buyuk oldugu farkin degeri ve yuzdesi: %d , %.2f\n",max_agirlik_fark,max_agirlik_fark_yuzdesi);
    printf("Farkli olan bilyenin agirliginin diger bilyelerin agirligiyla arasindaki farkin yuzdesinin en buyuk oldugu farkin degeri ve yuzdesi: %d , %.2f\n",max_yuzde_fark_degeri,max_yuzde_fark);

    return 0;
}
