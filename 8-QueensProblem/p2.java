package m2;

import java.util.Random;
import java.util.Scanner;

public class p2 {

	public static void main(String[] args) 
	{
		
		int s_tahtasi [][] = new int [8][8];
		double tablo [][] = new double [16][3]; //iþlem süresi
		Random r = new Random();
		Scanner sc = new Scanner(System.in);
		int satýr = 0, sütun = 0, kontrol = 0;
		int k = 0;
		int en_kucuk = 0;
		int yer_degistirme = 0;
		int random_sayýsý = 0;
		int yerleþtirme;
		int sayac=0;
		
		
		while(sayac<15)
		{
			long startTime = System.nanoTime(); 
			yer_degistirme=0;
			random_sayýsý=0;
			do
			{
				for(int i=0;i<8;i++)
				{
					for(int j=0;j<8;j++)
						s_tahtasi[i][j]=0;
				}
			
				for(int i=0;i<8;i++) //random oluþturma
				{
					yerleþtirme=r.nextInt(8);
					s_tahtasi[i][yerleþtirme]=1;
				}
				random_sayýsý++;
				int s_tahtasi2 [][] = new int[8][8];
				for(int i=0;i<8;i++)
				{
					for(int j=0;j<8;j++)
					{
						s_tahtasi2[i][j] = s_tahtasi[i][j];
					}
				}
			
				for(int vezir=0;vezir<7;vezir++) //her bir vezir için toplam ihtimal sayýsý
				{
					for(int i=vezir;i<8;i++)
					{
						for(int j=0;j<8;j++)
						{
							if(s_tahtasi[i][j]==1)
							{
								if(kontrol==0)
								{
									satýr=i;
									sütun=j;
									kontrol=1;
									break;
								}
								else if(j==sütun || i+j==satýr+sütun || i-j==satýr-sütun)
								{
									en_kucuk++;
									break;
								}
							}
						}
					}
					kontrol=0;
				}
				int gercek_deger [] = new int [2];
				int en_kucuk_indis [] = new int [2];
				int en_kucuk_kontrol[]= new int [2];
				en_kucuk_kontrol[1]=en_kucuk;

			
				do
				{
					en_kucuk_kontrol[0]=en_kucuk_kontrol[1];
					for (int x=0;x<8;x++){
						for (int y=0;y<8;y++){
							if(s_tahtasi[x][y]==1){
								gercek_deger[0]=x;
								gercek_deger[1]=y;
								s_tahtasi[x][y]=2;
								break;
							}
							
						}
						for(int y=0;y<8;y++){
							s_tahtasi[x][y]=1;
							for(int vezir=0;vezir<7;vezir++) //her bir vezir için toplam ihtimal sayýsý
							{
								for(int i=vezir;i<8;i++)
								{
									for(int j=0;j<8;j++)
									{
										if(s_tahtasi[i][j]==1)
										{
											if(kontrol==0)
											{
												satýr=i;
												sütun=j;
												kontrol=1;
												break;
											}
											else if(j==sütun || i+j==satýr+sütun || i-j==satýr-sütun)
											{
												k++;
												break;
											}
										}
									}
								}
								kontrol=0;
							}
							 
							s_tahtasi[x][y]=0;
							if(k<en_kucuk)
							{
								en_kucuk=k;
								en_kucuk_indis[0]=x;
								en_kucuk_indis[1]=y;
							}
							k=0;
						}
						s_tahtasi[gercek_deger[0]][gercek_deger[1]]=1;
					}
					for(int i=0;i<8;i++)
					{
						s_tahtasi[en_kucuk_indis[0]][i]=0;
					}
					s_tahtasi[en_kucuk_indis[0]][en_kucuk_indis[1]]=1;
					yer_degistirme++;
					
					en_kucuk_kontrol[1]=en_kucuk;
					if(en_kucuk==0)
					{
						System.out.println((sayac+1)+".çözüm");
						System.out.println("Tahtanýn ilk hali     Tahtanýn son hali");
						for(int i=0;i<8;i++)
						{
							for(int j=0;j<8;j++)
							{
								System.out.print(s_tahtasi2[i][j]+" ");
							}
							System.out.print("      ");
							for(int j=0;j<8;j++)
							{
								System.out.print(s_tahtasi[i][j]+" ");
							}
							System.out.println();
						}
						System.out.println();
						System.out.println();
						tablo[sayac][0] = yer_degistirme;
						tablo[sayac][1] = random_sayýsý;
						tablo[15][0]+=tablo[sayac][0];
						tablo[15][1]+=tablo[sayac][1];
					
						en_kucuk_kontrol[0]=en_kucuk_kontrol[1];
					}
				} while(en_kucuk_kontrol[0]!=en_kucuk_kontrol[1]);
			}while(en_kucuk!=0);
			long endTime = System.nanoTime(); 
			long estimatedTime = endTime - startTime;
			double seconds = (double)estimatedTime/1000000000;
			tablo[sayac][2] = seconds;
			tablo[15][2] +=tablo[sayac][2];
			sayac++;
		}
		
		for(int i=0;i<3;i++)
		{
			tablo[15][i]/=15;
		}
		
		for(int i=0;i<15;i++)
		{
			System.out.println((i+1)+".deneme için "+"yer deðiþtirme sayýsý="+(int) tablo[i][0]+" ve random restartsayýsý="
		+(int) tablo[i][1]+" ve iþlem süresi="+tablo[i][2]+" sn");
		}
		
		System.out.println();
		System.out.println("Ortalama yer deðiþtirme sayýsý="+tablo[15][0]+"\nOrtalama random restart sayýsý="+tablo[15][1]+"\nOrtalama iþlem süresi="+tablo[15][2]);
		sc.close();
	}

}