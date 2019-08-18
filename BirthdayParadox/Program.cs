using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace birthday_paradox
{
    class GlobalRandom
    {
        public static Random RAND = new Random();
        public static int[] toplam_cakisma = new int[3];
        public static int[,] deney_cakisma = new int[10,3];
    }
    class Program
    {
        static void Main(string[] args)
        {
            int[][] ay_tablo1 = new int[12][];
            int[][] ay_tablo2 = new int[3][]; //Kişilerin sadece Haziran-Ağustos tarihleri arasında doğduğunu varsayarken kullanılan tablo.

            for (int i=0; i<12; i++)
            {
                switch (i)
                {
                    case 0:
                    case 2:
                    case 4:
                    case 6:
                    case 7:
                    case 9:
                    case 11:
                        ay_tablo1[i] = new int[31];
                        break;
                    case 3:
                    case 5:
                    case 8:
                    case 10:
                        ay_tablo1[i] = new int[30];
                        break;
                    case 1:
                        ay_tablo1[i] = new int[28];
                        break;

                }
            }

            for (int j=0; j<3; j++)
            {
                switch(j)
                {
                    case 0:
                        ay_tablo2[j] = new int[30];
                        break;
                    case 1:
                    case 2:
                        ay_tablo2[j] = new int[31];
                        break;
                }
            }

            int secenek;
            do
            {
                secenek = menu();
                switch(secenek)
                {
                    case 1:
                        int sayi;
                        Console.Write("Deneyde yer alacak kişi sayısını giriniz: ");
                        sayi = Convert.ToInt32(Console.ReadLine());
                        deney1(ay_tablo1, sayi);
                        GlobalRandom.toplam_cakisma[0] = 0;
                        Console.WriteLine("\n Menuye donmek için bir tuşa basınız...");
                        Console.ReadKey();
                        break;
                    case 2:
                        for (int a = 0; a < 3; a++)
                            GlobalRandom.toplam_cakisma[a] = 0;

                        deney1(ay_tablo1, 100);
                        deney1(ay_tablo1, 500);
                        deney1(ay_tablo1, 1000);
                        Console.WriteLine("\n   Deneylerin Genel İstatistiği:");
                        Console.WriteLine(" ----------------------------------");
                        Console.WriteLine(" | Deney ||  100  |  500  |  1000 |");
                        Console.WriteLine(" |  No   ||  Kişi |  Kişi |  Kişi |");

                        for (int i=0; i<10; i++)
                        {
                            Console.WriteLine(" |-------||-------|-------|-------|");
                            Console.WriteLine(" |  {0,2}         {1}    {2}     {3}  |", i + 1, GlobalRandom.deney_cakisma[i, 0], GlobalRandom.deney_cakisma[i, 1], GlobalRandom.deney_cakisma[i, 2]);
                        }
                        Console.WriteLine(" |-------||-------|-------|-------|");
                        Console.WriteLine(" |  ORT. || {0}   | {1} | {2}   |", (double)GlobalRandom.toplam_cakisma[0] / 10, (double)GlobalRandom.toplam_cakisma[1] / 10, (double)GlobalRandom.toplam_cakisma[2] / 10);
                        Console.WriteLine(" |-------||-------|-------|-------|");
                        Console.WriteLine(" | YÜZDE || %{0}  | %{1}| %{2} |", (double)GlobalRandom.toplam_cakisma[0] * 10 / 100, (double)GlobalRandom.toplam_cakisma[1] * 10 / 500, (double)GlobalRandom.toplam_cakisma[2] * 10 / 1000);
                        Console.WriteLine(" ----------------------------------");
                        Console.WriteLine("\n Menuye dönmek için bir tuşa basınız...");
                        Console.ReadKey();
                        break;
                    case 3:
                        for (int a = 0; a < 3; a++)
                            GlobalRandom.toplam_cakisma[a] = 0;

                        deney2(ay_tablo2, 100);
                        deney2(ay_tablo2, 500);
                        deney2(ay_tablo2, 1000);
                        Console.WriteLine("\n   Deneylerin Genel İstatistiği:");
                        Console.WriteLine(" ----------------------------------");
                        Console.WriteLine(" | Deney ||  100  |  500  |  1000 |");
                        Console.WriteLine(" |  No   ||  Kişi |  Kişi |  Kişi |");

                        for (int i = 0; i < 10; i++)
                        {
                            Console.WriteLine(" |-------||-------|-------|-------|");
                            Console.WriteLine(" |  {0,2}         {1}    {2}     {3}  |", i + 1, GlobalRandom.deney_cakisma[i, 0], GlobalRandom.deney_cakisma[i, 1], GlobalRandom.deney_cakisma[i, 2]);
                        }
                        Console.WriteLine(" |-------||-------|-------|-------|");
                        Console.WriteLine(" |  ORT. || {0}   | {1} | {2}   |", (double)GlobalRandom.toplam_cakisma[0] / 10, (double)GlobalRandom.toplam_cakisma[1] / 10, (double)GlobalRandom.toplam_cakisma[2] / 10);
                        Console.WriteLine(" |-------||-------|-------|-------|");
                        Console.WriteLine(" | YÜZDE || %{0}  | %{1}| %{2} |", (double)GlobalRandom.toplam_cakisma[0] * 10 / 100, (double)GlobalRandom.toplam_cakisma[1] * 10 / 500, (double)GlobalRandom.toplam_cakisma[2] * 10 / 1000);
                        Console.WriteLine(" ----------------------------------");
                        Console.WriteLine("\n Menuye dönmek için bir tuşa basınız...");
                        Console.ReadKey();
                        break;
                }
            } while (secenek != 4);
        }//end of Main

        static void random_birth1(int[][] matris, int i, int j)
        {
            int[] ay_gün_say = new int[12] { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
            int ay = GlobalRandom.RAND.Next(12);
            int gun = GlobalRandom.RAND.Next(ay_gün_say[ay]);
            matris[ay][gun]++;
            cakisma(matris[ay][gun], i, j);
        }

        static void random_birth2(int[][] matris, int i, int j)
        {
            int[] ay_gün_say = new int[3] { 30, 31, 31 };
            int ay = GlobalRandom.RAND.Next(3);
            int gun = GlobalRandom.RAND.Next(ay_gün_say[ay]);
            matris[ay][gun]++;
            cakisma(matris[ay][gun], i, j);
        }

        static void cakisma(int sayi, int i, int j)
        {
            if(sayi>1)
            {
                GlobalRandom.toplam_cakisma[j]++;
                GlobalRandom.deney_cakisma[i, j]++;
            }
        }

        static void deney1(int[][] ay_tablo, int kisi_say)
        {
            string[] ay_isimleri = { "   OCAK", "  ŞUBAT", "   MART", "  NİSAN", "  MAYIS", "HAZİRAN", " TEMMUZ", "AĞUSTOS", "  EYLÜL", "   EKİM", "  KASIM", " ARALIK" };
            int k = 0;
            for (int j=0; j<10; j++)
            {
                //Sıfırlama işlemi
                for (int x=0; x<12; x++)
                {
                    for (int y=0; y<ay_tablo[x].GetLength(0); y++)
                    {
                        ay_tablo[x][y] = 0;
                    }
                }
                
                switch(kisi_say)
                {
                    case 100:
                        k = 0;
                        break;
                    case 500:
                        k = 1;
                        break;
                    case 1000:
                        k = 2;
                        break;
                }
                GlobalRandom.deney_cakisma[j, k] = 0;
                //Sıfırlama işleminin sonu

                Console.WriteLine("____________________________________________{0} Kişi için;____________________________________________", kisi_say);
                Console.WriteLine("______________________________________________{0}.Deney:______________________________________________", j + 1);

                for (int i=0; i<kisi_say; i++)
                {
                    random_birth1(ay_tablo, j, k);
                }
                Console.WriteLine("\n                                            ----- GÜNLER -----\n");
                Console.Write("  AYLAR|");

                for (int a=0; a<31; a++)
                {
                    Console.Write("{0,2}|", a + 1);
                }
                Console.WriteLine(" ");
                Console.WriteLine("-----------------------------------------------------------------------------------------------------");

                int w = 0;
                foreach (int[] ay in ay_tablo)
                {
                    Console.Write("{0,2}|", ay_isimleri[w++]);
                    foreach (int gun in ay)
                    {
                        if (gun - 1 <= 0)
                            Console.Write("{0,2}|", "");
                        else
                            Console.Write("{0,2}|", gun - 1);
                    }
                    Console.WriteLine();
                }

                Console.WriteLine("\nDeney {0} için çakışma sayısı: {1}\n", j + 1, GlobalRandom.deney_cakisma[j, k]);
                Console.WriteLine("Devam etmek için bir tuşa basınız...");
                Console.ReadKey();
            }
            Console.WriteLine("\n Toplam Çakışmalar");
            Console.WriteLine(" -----------------");
            Console.WriteLine("  ___________________");
            Console.WriteLine(" | Deney || Çakışma |");
            Console.WriteLine(" |  No   ||  Sayısı |");

            for (int i=0; i<10; i++)
            {
                Console.WriteLine(" |-------||---------|");
                Console.WriteLine(" |{0,-6} ||{1,-9}|", i + 1, GlobalRandom.deney_cakisma[i, k]);
            }
            Console.Write(" |------------------|");
            Console.WriteLine("\n Ortalama Çakışma: {0}\n Yüzde: %{1}", (double)GlobalRandom.toplam_cakisma[k] / 10, (double)GlobalRandom.toplam_cakisma[k] * 10 / kisi_say);
        }

        static void deney2(int[][] ay_tablo, int kisi_say)
        {
            string[] ay_isimleri = { "HAZİRAN", " TEMMUZ", "AĞUSTOS" };
            int k = 0;

            for (int j=0; j<10; j++)
            {
                //Sıfırlama işlemi
                for (int x=0; x<3; x++)
                {
                    for (int y=0; y<ay_tablo[x].GetLength(0); y++)
                    {
                        ay_tablo[x][y] = 0;
                    }
                }
                switch (kisi_say)
                {
                    case 100:
                        k = 0;
                        break;
                    case 500:
                        k = 1;
                        break;
                    case 1000:
                        k = 2;
                        break;
                }
                GlobalRandom.deney_cakisma[j, k] = 0;
                //Sıfırlama işleminin sonu

                Console.WriteLine("____________________________________________{0} Kişi için;____________________________________________", kisi_say);
                Console.WriteLine("______________________________________________{0}.Deney:______________________________________________", j + 1);

                for (int i=0; i<kisi_say; i++)
                {
                    random_birth2(ay_tablo, j, k);
                }

                Console.WriteLine("\n                                            ----- GÜNLER -----\n");
                Console.Write("  AYLAR|");

                for (int a=0; a<31; a++)
                {
                    Console.Write("{0,2}|", a + 1);
                }
                Console.WriteLine(" ");
                Console.WriteLine("-----------------------------------------------------------------------------------------------------");

                int w = 0;
                foreach (int[] ay in ay_tablo)
                {
                    Console.Write("{0,2}|", ay_isimleri[w++]);
                    foreach (int gun in ay)
                    {
                        if (gun - 1 <= 0)
                            Console.Write("{0,2}|", "");
                        else
                            Console.Write("{0,2}|", gun - 1);
                    }
                    Console.WriteLine();
                }

                Console.WriteLine("\nDeney {0} için çakışma sayısı: {1}\n", j + 1, GlobalRandom.deney_cakisma[j, k]);
                Console.WriteLine("Devam etmek için bir tuşa basınız...");
                Console.ReadKey();
            }
            Console.WriteLine("\n Toplam Çakışmalar");
            Console.WriteLine(" -----------------");
            Console.WriteLine("  ___________________");
            Console.WriteLine(" | Deney || Çakışma |");
            Console.WriteLine(" |  No   ||  Sayısı |");

            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(" |-------||---------|");
                Console.WriteLine(" |{0,-6} ||{1,-9}|", i + 1, GlobalRandom.deney_cakisma[i, k]);
            }
            Console.Write(" |------------------|");
            Console.WriteLine("\n Ortalama Çakışma: {0}\n Yüzde: %{1}", (double)GlobalRandom.toplam_cakisma[k] / 10, (double)GlobalRandom.toplam_cakisma[k] * 10 / kisi_say);
        }

        static int menu()
        {
            int secim;

            Console.Write("\n");
            Console.WriteLine("                    MENU                    ");
            Console.WriteLine("                    ----                    ");
            Console.WriteLine("1. Gireceğiniz bir kişi sayısı ile deneyi gerçekleştirme");
            Console.WriteLine("2. Önceden belirlenmiş kişi sayılarıyla deneyi gerçekleştirme(Kişi sayıları: 100,500,1000)");
            Console.WriteLine("3. Tüm kişilerin Haziran-Ağustos ayları arasında doğmuş olduğunu varsayarak deneyi gerçekleştirme");
            Console.WriteLine("4. Çıkış");

            Console.Write("Seçiminizi giriniz [1,4]: ");
            secim = sayi_al(1, 4);

            return secim;
        }

        static int sayi_al(int alt_limit, int ust_limit)
        {
            int sayi;

            sayi = Convert.ToInt32(Console.ReadLine());

            while (sayi < alt_limit || sayi > ust_limit)
            {
                Console.Write("Lütfen belirtilen aralıklarda bir sayı giriniz [{0},{1}]: ", alt_limit, ust_limit);
                sayi = Convert.ToInt32(Console.ReadLine());
            }

            return sayi;
        }
    }//end of Program

}//end of namespace
