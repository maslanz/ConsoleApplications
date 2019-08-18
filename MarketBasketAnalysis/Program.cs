using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace market_basket_analysis
{
    class Market
    {
        public int[][] musteriler = new int[5][];
        public string[] urunler = { "Ekmek", "Simit", "Peynir", "Tereyağı", "Zeytin", "Çay", "Makarna", "Bal", "Reçel", "Yumurta" };
        public int[] urunler_id = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        public int[,] ikili_tablo;
        public Market()
        {
            Random sayi = new Random();
            int urun;
            int urun_say;
            ikili_tablo = ikili_tablo_olusturma(urunler_id, 3);
            for (int i = 0; i < 5; i++)
            {
                urun_say = sayi.Next(1, 6);
                musteriler[i] = new int[urun_say];
                for (int j = 0; j < urun_say; j++)
                {
                    musteriler[i][j] = -1;

                    do
                    {
                        urun = sayi.Next(0, 10);
                    } while (bulundu(musteriler[i], urun));
                    musteriler[i][j] = urun;
                }
                Array.Sort(musteriler[i]);
                musteri_ikili_isleme(i);
            }
        }

        private int satir_say_hesaplama(int x)
        {
            return (x * (x - 1)) / 2;
        }

        private int[,] ikili_tablo_olusturma(int[] dizi, int sutun_say)
        {
            int[,] tablo = new int[satir_say_hesaplama(dizi.Length), sutun_say];
            int satir_no = 0;
            for (int i = 0; i < dizi.Length - 1; i++)
            {
                for (int j = i + 1; j < dizi.Length; j++)
                {
                    tablo[satir_no, 0] = dizi[i];
                    tablo[satir_no, 1] = dizi[j];
                    satir_no++;
                }
            }
            return tablo;
        }

        private void ikili_tablo_arttirma(int[,] ikililer)
        {
            for (int i = 0; i < ikililer.GetLength(0); i++)
            {
                if (ikililer[i, 0] == 0 && ikililer[i, 1] == 0)
                    continue;
                ikili_tablo[satir_bulma(ikililer[i, 0], ikililer[i, 1]), 2]++;
            }
        }

        private void musteri_ikili_isleme(int musteri_id)
        {
            int[] satin_alinanlar = musteriler[musteri_id];
            int[,] musteri_ikili_tablo = ikili_tablo_olusturma(satin_alinanlar, 2);
            ikili_tablo_arttirma(musteri_ikili_tablo);
        }

        private int satir_bulma(int a, int b)
        {
            int indeks = 0;
            for (int i = 0; i < a; i++)
            {
                indeks += 9 - i;
            }
            if (indeks == -1)
                return 0;
            return indeks + b - a - 1;
        }

        private bool bulundu(int[] dizi, int parametre)
        {

            foreach (int eleman in dizi)
            {
                if (eleman == parametre)

                    return true;
            }

            return false;
        }

        public void kisi_sepeti_yazma(int musteri_id)
        {

            int[] kisi_urunleri = musteriler[musteri_id];
            Console.Write(" |    {0,-5}||", musteri_id + 1);

            foreach (int urun in kisi_urunleri)
            {

                Console.Write(" {0}", urunler[urun]);

            }
            Console.Write("\n |---------||------------------------------------------------|");
            Console.WriteLine();
        }

        public void market_sepeti_yazma()
        {
            for (int i = 0; i < musteriler.Length; i++)
            {
                kisi_sepeti_yazma(i);
            }
        }

        public void ikili_tablo_yazdirma()
        {
            Console.WriteLine("  ________________________________");
            Console.WriteLine(" |   Ürün     |    Ürün    | Sayı |");
            Console.WriteLine(" |     1      |      2     |      |");
            for (int i = 0; i < ikili_tablo.GetLength(0); i++)
            {
                if (ikili_tablo[i, 2] == 0)
                    continue;
                Console.WriteLine(" |------------|------------|------|");
                Console.WriteLine(" |{0,-12}|{1,-12}|   {2,-3}|", urunler[ikili_tablo[i, 0]], urunler[ikili_tablo[i, 1]], ikili_tablo[i, 2]);

            }
            Console.WriteLine(" ----------------------------------");
        }

        public void urun_alip_oneri_dondurme(int birinci, int ikinci)
        {
            int[] dizi = new int[5];


            for (int i = 0; i < 5; i++) //Kullanıcıdan alınan iki ürünün müşteri sepetleri içinde aranması
            {
                foreach (int o in musteriler[i])
                {
                    if (birinci == o)
                    {
                        dizi[i]++;
                    }
                }
            }
            for (int i = 0; i < 5; i++)
            {
                foreach (int o in musteriler[i])
                {
                    if (ikinci == o)
                    {
                        dizi[i]++;
                    }
                }
            }

            int k = 0;
            for (int i = 0; i < 5; i++)
            {
                if (dizi[i] == 2)
                {
                    k++;
                }
            }

            int[] urun_kesisim = new int[k]; //Kullanıcıdan alınan iki ürünü hangi müşterilerin aldığı 

            int j = 0;
            for (int i = 0; i < 5; i++)
            {
                if (dizi[i] == 2)
                {
                    urun_kesisim[j] = i;
                    j++;
                }
            }

            Array.Sort(urun_kesisim);

            int[,] onerilecekler = new int[k, 3]; //Kullanıcıdan alınan iki ürünün yanında başka hangi ürünlerin satın alındığı bulunması
            for (int a = 0; a < k; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    onerilecekler[a, b] = -1;
                }
            }

            for (int kişi = 0; kişi < k; kişi++)
            {
                j = 0;
                foreach (int ürün in musteriler[urun_kesisim[kişi]])
                {
                    if (ürün != birinci && ürün != ikinci)
                    {
                        onerilecekler[kişi, j] = ürün;
                        j++;
                    }
                }
            }

            int[] onerilecek_dizi_miktari = new int[10]; //Önerilecek ürünün kaç kez (alışverişte) alındığını hesaplamak için bu dizi kullanıldı.
            for (int a = 0; a < k; a++)
            {
                for (int b = 0; b < 3; b++)
                {
                    if (onerilecekler[a, b] != -1)
                    {
                        onerilecek_dizi_miktari[onerilecekler[a, b]]++;
                    }
                }
            }
            int guven_yuzdesi = 0; //Güven yüzdesi hesaplama
            for (int i = 0; i < 10; i++)
            {
                if (onerilecek_dizi_miktari[i] != 0)
                {
                    guven_yuzdesi= 100 * onerilecek_dizi_miktari[i] / k;
                    Console.WriteLine("\nBu iki ürünle beraber {0} alabilirsiniz. \n{1} alışverişte {2} kez alınmıştır. \nGüven Yüzdesi: %{3}", urunler[i], k, onerilecek_dizi_miktari[i], guven_yuzdesi);

                }
            }
        }

    }//end of Market

    class Program
    {
        static void Main(string[] args)
        {
            Market yeni = new Market();
            Console.WriteLine("___________________ALIŞVERİŞ ÖNERİ PROGRAMI___________________________\n");
            Console.WriteLine("a) Rastgele 5 müşterinin alışveriş sepetini görmek için bir tuşa basınız...");
            Console.ReadKey();
            Console.WriteLine(" ____________________________________________________________");
            Console.WriteLine(" | Müşteri ||                 Ürünler                        |");
            Console.WriteLine(" |---------||------------------------------------------------|");
            yeni.market_sepeti_yazma();
            Console.WriteLine("\nb) Tüm ikili ürün gruplarını ve birlikte geçme sayılarını görmek için bir tuşa basınız...");
            Console.ReadKey();
            yeni.ikili_tablo_yazdirma();
            Console.WriteLine("\nc)Yeni müşteri için sırayla iki adet ürün ismi giriniz:");
            int urun_adi1 = -1;
            int urun_adi2 = -1;
            Console.Write("\n1.ürün: ");
            switch (Console.ReadLine())
            {
                case "ekmek":
                case "Ekmek":
                    urun_adi1 = 0;
                    break;
                case "simit":
                case "Simit":
                    urun_adi1 = 1;
                    break;
                case "peynir":
                case "Peynir":
                    urun_adi1 = 2;
                    break;
                case "tereyağı":
                case "Tereyağı":
                    urun_adi1 = 3;
                    break;
                case "zeytin":
                case "Zeytin":
                    urun_adi1 = 4;
                    break;
                case "çay":
                case "Çay":
                    urun_adi1 = 5;
                    break;
                case "makarna":
                case "Makarna":
                    urun_adi1 = 6;
                    break;
                case "bal":
                case "Bal":
                    urun_adi1 = 7;
                    break;
                case "reçel":
                case "Reçel":
                    urun_adi1 = 8;
                    break;
                case "yumurta":
                case "Yumurta":
                    urun_adi1 = 9;
                    break;

            }
            Console.Write("\n2.ürün: ");
            switch (Console.ReadLine())
            {
                case "ekmek":
                case "Ekmek":
                    urun_adi2 = 0;
                    break;
                case "simit":
                case "Simit":
                    urun_adi2 = 1;
                    break;
                case "peynir":
                case "Peynir":
                    urun_adi2 = 2;
                    break;
                case "tereyağı":
                case "Tereyağı":
                    urun_adi2 = 3;
                    break;
                case "zeytin":
                case "Zeytin":
                    urun_adi2 = 4;
                    break;
                case "çay":
                case "Çay":
                    urun_adi2 = 5;
                    break;
                case "makarna":
                case "Makarna":
                    urun_adi2 = 6;
                    break;
                case "bal":
                case "Bal":
                    urun_adi2 = 7;
                    break;
                case "reçel":
                case "Reçel":
                    urun_adi2 = 8;
                    break;
                case "yumurta":
                case "Yumurta":
                    urun_adi2 = 9;
                    break;

            }
            yeni.urun_alip_oneri_dondurme(urun_adi1, urun_adi2);
            Console.WriteLine("\nProgramı sonlandırmak için bir tuşa basınız...");
            Console.ReadKey();

        }//end of Main
    }//end of Program
}//end of namespace
