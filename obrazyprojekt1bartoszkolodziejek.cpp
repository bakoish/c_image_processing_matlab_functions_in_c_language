
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <tuple>

using namespace std;
using namespace System;
using namespace System::Drawing;

Bitmap ^ normalizacja(Bitmap ^obrazIN, int x1, int y1, int x2, int y2, int x3, int y3);
Bitmap ^ zamkniecie(Bitmap ^obrazIN, int promien);
Bitmap ^ wypukle_otoczenie(Bitmap ^obrazIN, int zbierznosc_n_operacji = 40);
Bitmap ^ filtracja_przestrzenna_std(Bitmap ^obrazIN, int maska = 3);

/*WYKONAL BARTOSZ KOLODZIEJEK 304314*/

int main()
{
	Bitmap ^obraz;
	Bitmap ^obraz2;


	if (obraz = gcnew Bitmap("D:\\polar.bmp", true)) {
		printf("Udalo sie zaladować obraz\n");
	}
	else {
		printf("Nie udalo sie zaladować obraz");
		return 1;
	}

	//obraz = gcnew Bitmap("D:\\zamkniecie.png", true);
	//obraz2 = gcnew Bitmap(obraz->Width, obraz->Height);
	//obraz = gcnew Bitmap("D:\\pogrubianie.png", true);

	printf("wymiary:\n");
	cout << obraz->Height << endl;
	cout << obraz->Width << endl;
	//int wysokosc = obraz->Height;
	//int szerokosc = obraz->Width;
	printf("Wybierz przekształcenie: (podaj nr)\n");
	printf("1. Normalizacja wg. 3 punktow\n");
	printf("2. Filtracja_przestrzenna_std\n");
	printf("3. Wypukle_otoczenie\n");
	printf("4. Zamkniecie obj kolowym\n");
	printf("5. EXIT\n");
	int x;
	cin >> x;

	switch (x)
	{
	case 1:
		int x1, x2, x3, y1, y2, y3;
		printf("Podaj x1: \n");
		cin >> x1;
		printf("Podaj y1: \n");
		cin >> y1;
		printf("Podaj x2: \n");
		cin >> x2;
		printf("Podaj y2: \n");
		cin >> y2;
		printf("Podaj x3: \n");
		cin >> x3;
		printf("Podaj y3: \n");
		cin >> y3;

		printf("Zaczynam!\n");
		obraz2 = normalizacja(obraz, x1, y1, x2, y2, x3, y3);
		printf("Skonczone!\n");
		break;

	case 2:
		printf("Zaczynam!\n");
		obraz2 = filtracja_przestrzenna_std(obraz);
		printf("Skonczone!\n");
		break;

	case 3:
		printf("Zaczynam!\n");
		obraz2 = wypukle_otoczenie(obraz);
		printf("Skonczone!\n");

		break;
	case 4:
		printf("Zaczynam!\n");
		obraz2 = zamkniecie(obraz, 5);
		printf("Skonczone!\n");
		break;

	case 5:
		printf("EXIT\n");
		return 0;

	default:
		printf("brak opcji - exit\n");
		return 0;
	}


	//obraz2 = normalizacja(obraz, 1, 1, 100, 200, 255, 255);
	//obraz2 = gcnew Bitmap(obraz->Width + (2 * 100), obraz->Height + (2 * 100));
	//obraz2 = zamkniecie(obraz, 5);
	//obraz2 = filtracja_przestrzenna_std(obraz);
	//obraz2 = wypukle_otoczenie(obraz);


	//obraz2->Save("D:\\zamkniecieErozjaNEW.jpg");
	//obraz2->Save("D:\\wypukle.jpg");
	//obraz2->Save("D:\\polarNEW.bmp");
	obraz2->Save("D:\\polarNORMALIZACJA___NEW.jpg");


	return 0;
}

Bitmap ^ normalizacja(Bitmap ^obrazIN, int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (obrazIN == nullptr) return nullptr;

	Bitmap ^obrazOUT;
	obrazOUT = gcnew Bitmap(obrazIN->Width, obrazIN->Height);
	Color Px;


	for (int kz = 0; kz < obrazIN->Height; kz++) {
		for (int kx = 0; kx < obrazIN->Width; kx++) {

			Px = obrazIN->GetPixel(kx, kz);
			obrazOUT->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));

		}
	}
	
	for (int kz = 0; kz < obrazIN->Height; kz++) {
		for (int kx = 0; kx < obrazIN->Width; kx++) {

			Px = obrazOUT->GetPixel(kx, kz);

			double red = 0;
			double green = 0;
			double blue = 0;

			//RED
			if (Px.R <= x1) {
				double temp = (double)y1 / (double)x1;
				double b = (double)y1 - (temp*(double)x1);

				if ((temp * (double)Px.R) + b > 255.0) red = 255;
				else if ((temp * (double)Px.R) + b <= 0) red = 0;
				else {
					temp *= (double)Px.R;
					temp += b;
					red = temp;
				}
				
				
			}
			else if (Px.R <= x2 && Px.R > x1) {
				double temp = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);
				double b = (double)y2 - (temp*(double)x2);

				if ((temp * (double)Px.R) + b > 255.0) red = 255;
				else if ((temp * (double)Px.R) + b <= 0) red = 0;
				else {
					temp *= (double)Px.R;
					temp += b;
					red = temp;
				}

			}
			else if (Px.R <= x3 && Px.R > x2) {

				double temp = ((double)y3 - (double)y2) / ((double)x3 - (double)x2);
				double b = (double)y3 - (temp*(double)x3);

				if ((temp * (double)Px.R) + b > 255.0) red = 255;
				else if ((temp * (double)Px.R) + b <= 0) red = 0;
				else {
					temp *= (double)Px.R;
					temp += b;
					red = temp;
				}

			}
			else {

				double temp = (255.0 - (double)y3) / (255.0 - (double)x3);
				double b = (double)255 - (temp*(double)255);


				if ((temp * (double)Px.R) + b > 255.0) red = 255;
				else if ((temp * (double)Px.R) + b <= 0) red = 0;
				else {
					temp *= (double)Px.R;
					temp += b;
					red = temp;
				}

			}
			
			//GREEN
			if (Px.G <= x1) {
				double temp = (double)y1 / (double)x1;
				double b = (double)y1 - (temp*(double)x1);

				if ((temp * (double)Px.G) + b > 255.0) green = 255;
				else if ((temp * (double)Px.G) + b <= 0) green = 0;
				else {
					temp *= (double)Px.G;
					temp += b;
					green = temp;
				}
			}
			else if (Px.G <= x2 && Px.G > x1) {
				double temp = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);
				double b = (double)y2 - (temp*(double)x2);

				if ((temp * (double)Px.G) + b > 255.0) green = 255;
				else if ((temp * (double)Px.G) + b <= 0) green = 0;
				else {
					temp *= (double)Px.G;
					temp += b;
					green = temp;
				}

			}
			else if (Px.G <= x3 && Px.G > x2) {

				double temp = ((double)y3 - (double)y2) / ((double)x3 - (double)x2);
				double b = (double)y3 - (temp*(double)x3);

				if ((temp * (double)Px.G) + b > 255.0) green = 255;
				else if ((temp * (double)Px.G) + b <= 0) green = 0;
				else {
					temp *= (double)Px.G;
					temp += b;
					green = temp;
				}

			}
			else {

				double temp = (255.0 - (double)y3) / (255.0 - (double)x3);
				double b = (double)255 - (temp*(double)255);

				if ((temp * (double)Px.G) + b > 255.0) green = 255;
				else if ((temp * (double)Px.G) + b <= 0) green = 0;
				else {
					temp *= (double)Px.G;
					temp += b;
					green = temp;
				}

			}
			//BLUE
			if (Px.B <= x1) {
				double temp = (double)y1 / (double)x1;
				double b = (double)y1 - (temp*(double)x1);

				if ((temp * (double)Px.B) + b > 255.0) blue = 255;
				else if ((temp * (double)Px.B) + b <= 0) blue = 0;
				else {
					temp *= (double)Px.B;
					temp += b;
					blue = temp;
				}
			}
			else if (Px.B <= x2 && Px.B > x1) {
				double temp = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);
				double b = (double)y2 - (temp*(double)x2);

				if ((temp * (double)Px.B) + b > 255.0) blue = 255;
				else if ((temp * (double)Px.B) + b <= 0) blue = 0;
				else {
					temp *= (double)Px.B;
					temp += b;
					blue = temp;
				}

			}
			else if (Px.B <= x3 && Px.B > x2) {

				double temp = ((double)y3 - (double)y2) / ((double)x3 - (double)x2);
				double b = (double)y3 - (temp*(double)x3);

				if ((temp * (double)Px.B) + b > 255.0) blue = 255;
				else if ((temp * (double)Px.B) + b <= 0) blue = 0;
				else {
					temp *= (double)Px.B;
					temp += b;
					blue = temp;
				}

			}
			else {

				double temp = (255.0 - (double)y3) / (255.0 - (double)x3);
				double b = (double)255 - (temp*(double)255);

				if ((temp * (double)Px.B) + b > 255.0) blue = 255;
				else if ((temp * (double)Px.B) + b <= 0) blue = 0;
				else {
					temp *= (double)Px.B;
					temp += b;
					blue = temp;
				}

			}

			Px = obrazOUT->GetPixel(kx, kz);
			obrazOUT->SetPixel(kx, kz, Px.FromArgb((int)red, (int)green, (int)blue));
			
		}
	}
	
	return obrazOUT;

}


Bitmap ^ filtracja_przestrzenna_std(Bitmap ^obrazIN, int promien_maski)
{
	Bitmap ^ filtracjaTEMP = gcnew Bitmap(obrazIN->Width, obrazIN->Height);
	Bitmap ^ filtracja = gcnew Bitmap(obrazIN->Width, obrazIN->Height);

	Color Px;
	int kz, kx;

	//tworzenie kopii + monochrom
	for (kz = 0; kz < obrazIN->Height; kz++) {
		for (kx = 0; kx < obrazIN->Width; kx++) {

			Px = obrazIN->GetPixel(kx, kz);

			double x = (0.299*Px.R) + (0.587*Px.G) + (0.114*Px.B);
			if (x <= 0) x = 0;
			if (x > 255) x = 255;

			filtracja->SetPixel(kx, kz, Px.FromArgb(x, x, x));
			filtracjaTEMP->SetPixel(kx, kz, Px.FromArgb(x, x, x));
			
		}
	}

	int promien = promien_maski; //promien 2 tworzy macierz promien_maski*promien_maski+1 czyli 5x5

	int * tabTEMP = new int[((promien_maski*promien_maski)+1)*((promien_maski*promien_maski) + 1)];

	for (kz = promien; kz < obrazIN->Height - promien; kz++) {
		for (kx = promien; kx < obrazIN->Width - promien; kx++) {


			
			//Px = filtracja->GetPixel(kx, kz);
			//bool zmien = 0;
			int suma = 0;
			int ilosc = 0;



			for (int i = kz - promien; i < kz - promien + (2 * promien + 1); i++) {
				for (int j = kx - promien; j < kx - promien + (2 * promien + 1); j++) {

					Px = filtracja->GetPixel(j, i);
					tabTEMP[ilosc] = Px.R;
					suma += Px.R;
					ilosc++;

				}
			}

			double srednia = suma / ilosc;

			double std = 0;
			for (int i = 0; i < ilosc; i++) {

				double x = tabTEMP[i] - srednia;
				//x = abs(x);
				x *= x;
				std += x;
			}
			std /= ilosc;
			std = sqrt(std);

			if (std <= 0) std = 0;
			if (std > 255) std = 255;

			Px = filtracja->GetPixel(kx, kz);
			filtracjaTEMP->SetPixel(kx, kz, Px.FromArgb(std, std, std));

			//tabTEMP = NULL;

		}
	}
	delete[] tabTEMP;


	

	//NORMALIZACJA
	double min = 255;
	double max = 0;
	for (kz = 0; kz < obrazIN->Height; kz++) {
		for (kx = 0; kx < obrazIN->Width; kx++) {

			Px = filtracjaTEMP->GetPixel(kx, kz);
			if (Px.R < min) min = Px.R;
			if (Px.R > max) max = Px.R;

		}
	}

	double mnoznik = ((255.0 - 0.0) / (max - min));

	for (kz = 0; kz < obrazIN->Height; kz++) {
		for (kx = 0; kx < obrazIN->Width; kx++) {


			Px = filtracjaTEMP->GetPixel(kx, kz);
			double x = Px.R;
			x -= min;

			//x *= mnoznik; //POPRAWNA WERSJA - SLABO NORMALIZUJE "MISIA"
			x *= 5.0;		//LEPSZA WERSJA DLA MISIA

			if (x <= 0.0) x = 0.0;
			if (x > 255.0) x = 255.0;
			filtracjaTEMP->SetPixel(kx, kz, Px.FromArgb(x, x, x));

		}
	}

	return filtracjaTEMP;
}


Bitmap ^ zamkniecie(Bitmap ^obrazIN, int promien)
{
	//dylatajca kolem: https://en.wikipedia.org/wiki/Dilation_(morphology)
	//erozja https://en.wikipedia.org/wiki/Erosion_(morphology)
	//zamknięcie = erozja((dylatacja, SE), SE)


	int x = 2 * promien + 1;
	int wsp_srodka = promien;

	int **tab = new int *[x]; //alokacja pamieci
	for (int i = 0; i < x; ++i)
	{
		tab[i] = new int[x]; //alokacja pamieci
		for (int j = 0; j < x; ++j)
		{
		
			if ((i-promien)*(i - promien) + (j-promien)*(j - promien) <= promien*promien) tab[i][j] = 255; //jezeli odleglosc xy od srodka w promieniu to = 0 czyli bialy
			else tab[i][j] = 0;
			
		}
		
	}

	//wyswietlenie dla kontoroli
	for (int i = 0; i < x; ++i, cout << endl)
		for (int j = 0; j < x; ++j)
			cout << tab[i][j] << '\t';

	
	Bitmap ^ obrazDylatacja = gcnew Bitmap(obrazIN->Width, obrazIN->Height);
	Bitmap ^ obrazErozja = gcnew Bitmap(obrazIN->Width, obrazIN->Height);

	Color Px;
	int kz, kx;

	//DYLATACJA TAB[][]
	for (kz = promien; kz < obrazIN->Height - promien; kz++) {
		for (kx = promien; kx < obrazIN->Width - promien; kx++) {

			Px = obrazIN->GetPixel(kx, kz);

			if (Px.R == 255) {

				for (int i = kz - promien, m = 0; i < kz- promien+( 2 * promien + 1); i++, m++) {
					for (int j = kx - promien, n = 0; j < kx - promien + (2 * promien + 1); j++, n++) {
						
						if(tab[m][n] == 255) obrazDylatacja->SetPixel(j, i, Px.FromArgb(tab[m][n], tab[m][n], tab[m][n]));
					}
				}

			}
		}
	}

	//tworzenie kopii
	for (kz = 0; kz < obrazErozja->Height; kz++) {
		for (kx = 0; kx < obrazErozja->Width; kx++) {

			Px = obrazDylatacja->GetPixel(kx, kz);
			obrazErozja->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));

		}
	}



	//EROZJA

	for (kz = promien; kz < obrazIN->Height - promien; kz++) {
		for (kx = promien; kx < obrazIN->Width - promien; kx++) {

			Px = obrazDylatacja->GetPixel(kx, kz);
			bool zmien = 0;

			if (Px.R == 255) {

				for (int i = kz - promien, m = 0; i < kz - promien + (2 * promien + 1); i++, m++) {
					for (int j = kx - promien, n = 0; j < kx - promien + (2 * promien + 1); j++, n++) {

						if (tab[m][n] == 255) {

							Px = obrazDylatacja->GetPixel(j, i);
							if (Px.R == 0) {
								zmien = 1; //zmiana bo roznica;
								break;
							}

						}
					
					}
				}

			}
			if (zmien) {
				Px = obrazDylatacja->GetPixel(kx, kz);
				obrazErozja->SetPixel(kx, kz, Px.FromArgb(0, 0, 0));
			}
		}
	}



	//zwolnienie tab
	for (int i(0); i < x; ++i)
		delete[] tab[i]; //uwolnienie pamieci
	delete[] tab; //uwolnienie pamieci
	tab = NULL;


	return obrazErozja;
}

Bitmap ^ wypukle_otoczenie(Bitmap ^obrazIN, int zbierznosc_n_operacji)
{

	Bitmap ^ wypukle = gcnew Bitmap(obrazIN->Width, obrazIN->Height);
	Bitmap ^ wypukleTEMP = gcnew Bitmap(obrazIN->Width, obrazIN->Height);

	Color Px;
	int kz, kx;

	//tworzenie kopii
	for (kz = 0; kz < obrazIN->Height; kz++) {
		for (kx = 0; kx < obrazIN->Width; kx++) {

			Px = obrazIN->GetPixel(kx, kz);
			wypukle->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));
			wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));
		}
	}
	

	//1  - sie zgadza czyli jest bialy
	//0  - ignorowane
	//-1 - tło (u nas czarny)

	int tab1[3][3] = { 0 };
	tab1[0][0] = 1; tab1[0][1] = 1; tab1[0][2] = 0;
	tab1[1][0] = 1; tab1[1][1] = -1; tab1[1][2] = 0;
	tab1[2][0] = 1; tab1[2][1] = 0; tab1[2][2] = 0;

	int tab2[3][3] = { 0 };
	tab2[0][0] = 0; tab2[0][1] = 1; tab2[0][2] = 1;
	tab2[1][0] = 0; tab2[1][1] = -1; tab2[1][2] = 1;
	tab2[2][0] = -1; tab2[2][1] = 0; tab2[2][2] = 1;

	int tab3[3][3] = { 0 }; //tab1+90 w prawo
	tab3[0][0] = 1; tab3[0][1] = 1; tab3[0][2] = 1;
	tab3[1][0] = 0; tab3[1][1] = -1; tab3[1][2] = 1;
	tab3[2][0] = -1; tab3[2][1] = 0; tab3[2][2] = 0;

	int tab4[3][3] = { 0 }; //tab2+90 w prawo
	tab4[0][0] = -1; tab4[0][1] = 0; tab4[0][2] = 0;
	tab4[1][0] = 0; tab4[1][1] = -1; tab4[1][2] = 1;
	tab4[2][0] = 1; tab4[2][1] = 1; tab4[2][2] = 1;

	int tab5[3][3] = { 0 }; //tab1+180 w prawo
	tab5[0][0] = -1; tab5[0][1] = 0; tab5[0][2] = 1;
	tab5[1][0] = 0; tab5[1][1] = -1; tab5[1][2] = 1;
	tab5[2][0] = 0; tab5[2][1] = 1; tab5[2][2] = 1;

	int tab6[3][3] = { 0 }; //tab2+180 w prawo
	tab6[0][0] = 1; tab6[0][1] = 0; tab6[0][2] = -1;
	tab6[1][0] = 1; tab6[1][1] = -1; tab6[1][2] = 0;
	tab6[2][0] = 1; tab6[2][1] = 1; tab6[2][2] = 0;

	int tab7[3][3] = { 0 }; //tab1+270 w prawo
	tab7[0][0] = 0; tab7[0][1] = 0; tab7[0][2] = -1;
	tab7[1][0] = 1; tab7[1][1] = -1; tab7[1][2] = 0;
	tab7[2][0] = 1; tab7[2][1] = 1; tab7[2][2] = 1;

	int tab8[3][3] = { 0 }; //tab2+270 w prawo
	tab8[0][0] = 1; tab8[0][1] = 1; tab8[0][2] = 1;
	tab8[1][0] = 1; tab8[1][1] = -1; tab8[1][2] = 0;
	tab8[2][0] = 0; tab8[2][1] = 0; tab8[2][2] = -1;




	int promien = 1; 

	for (int zbierznosc = 0; zbierznosc < zbierznosc_n_operacji; zbierznosc++) { //ilsoc powtorzonych petli
	
		//maska1
		for (kz = promien; kz < obrazIN->Height - promien; kz++) {
			for (kx = promien; kx < obrazIN->Width - promien; kx++) {

				Px = wypukle->GetPixel(kx, kz);
				bool zmien = 0;

				for (int i = kz - promien, m = 0; i < kz - promien + (3); i++, m++) {
					for (int j = kx - promien, n = 0; j < kx - promien + (3); j++, n++) {

						Px = wypukle->GetPixel(j, i);

						if (tab1[m][n] == 0) continue; //skip
						if (Px.R == 0 && tab1[m][n] == 1) { //czarny - konflikt

							zmien = 1;
							break;
						}
						if (Px.R == 255 && tab1[m][n] == -1) { //czarny - konflikt

							zmien = 1;
							break;
						}

					}
				}

				if (zmien) {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(0, 0, 0));
				}
				else {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(255, 255, 255));
				}
			}
		}

		for (kz = 0; kz < wypukleTEMP->Height; kz++) {
			for (kx = 0; kx < wypukleTEMP->Width; kx++) {

				Px = wypukleTEMP->GetPixel(kx, kz);
				if (Px.R == 255) wypukle->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));

			}
		}

		//maska 2:
		for (kz = promien; kz < obrazIN->Height - promien; kz++) {
			for (kx = promien; kx < obrazIN->Width - promien; kx++) {

				Px = wypukle->GetPixel(kx, kz);
				bool zmien = 0;

				for (int i = kz - promien, m = 0; i < kz - promien + (3); i++, m++) {
					for (int j = kx - promien, n = 0; j < kx - promien + (3); j++, n++) {

						Px = wypukle->GetPixel(j, i);

						if (tab2[m][n] == 0) continue; //skip
						if (Px.R == 0 && tab2[m][n] == 1) { //czarny - konflikt

							zmien = 1;
							break;
						}
						if (Px.R == 255 && tab2[m][n] == -1) { //czarny - konflikt

							zmien = 1;
							break;
						}

					}
				}

				if (zmien) {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(0, 0, 0));
				}
				else {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(255, 255, 255));
				}
			}
		}

		for (kz = 0; kz < wypukleTEMP->Height; kz++) {
			for (kx = 0; kx < wypukleTEMP->Width; kx++) {

				Px = wypukleTEMP->GetPixel(kx, kz);
				if (Px.R == 255) wypukle->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));

			}
		}

		//maska 3:
		for (kz = promien; kz < obrazIN->Height - promien; kz++) {
			for (kx = promien; kx < obrazIN->Width - promien; kx++) {

				Px = wypukle->GetPixel(kx, kz);
				bool zmien = 0;

				for (int i = kz - promien, m = 0; i < kz - promien + (3); i++, m++) {
					for (int j = kx - promien, n = 0; j < kx - promien + (3); j++, n++) {

						Px = wypukle->GetPixel(j, i);

						if (tab3[m][n] == 0) continue; //skip
						if (Px.R == 0 && tab3[m][n] == 1) { //czarny - konflikt

							zmien = 1;
							break;
						}
						if (Px.R == 255 && tab3[m][n] == -1) { //czarny - konflikt

							zmien = 1;
							break;
						}

					}
				}

				if (zmien) {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(0, 0, 0));
				}
				else {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(255, 255, 255));
				}
			}
		}

		for (kz = 0; kz < wypukleTEMP->Height; kz++) {
			for (kx = 0; kx < wypukleTEMP->Width; kx++) {

				Px = wypukleTEMP->GetPixel(kx, kz);
				if (Px.R == 255) wypukle->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));

			}
		}

		//maska 4:
		for (kz = promien; kz < obrazIN->Height - promien; kz++) {
			for (kx = promien; kx < obrazIN->Width - promien; kx++) {

				Px = wypukle->GetPixel(kx, kz);
				bool zmien = 0;

				for (int i = kz - promien, m = 0; i < kz - promien + (3); i++, m++) {
					for (int j = kx - promien, n = 0; j < kx - promien + (3); j++, n++) {

						Px = wypukle->GetPixel(j, i);

						if (tab4[m][n] == 0) continue; //skip
						if (Px.R == 0 && tab4[m][n] == 1) { //czarny - konflikt

							zmien = 1;
							break;
						}
						if (Px.R == 255 && tab4[m][n] == -1) { //czarny - konflikt

							zmien = 1;
							break;
						}

					}
				}

				if (zmien) {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(0, 0, 0));
				}
				else {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(255, 255, 255));
				}
			}
		}

		for (kz = 0; kz < wypukleTEMP->Height; kz++) {
			for (kx = 0; kx < wypukleTEMP->Width; kx++) {

				Px = wypukleTEMP->GetPixel(kx, kz);
				if (Px.R == 255) wypukle->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));

			}
		}

		//maska 5:
		for (kz = promien; kz < obrazIN->Height - promien; kz++) {
			for (kx = promien; kx < obrazIN->Width - promien; kx++) {

				Px = wypukle->GetPixel(kx, kz);
				bool zmien = 0;

				for (int i = kz - promien, m = 0; i < kz - promien + (3); i++, m++) {
					for (int j = kx - promien, n = 0; j < kx - promien + (3); j++, n++) {

						Px = wypukle->GetPixel(j, i);

						if (tab5[m][n] == 0) continue; //skip
						if (Px.R == 0 && tab5[m][n] == 1) { //czarny - konflikt

							zmien = 1;
							break;
						}
						if (Px.R == 255 && tab5[m][n] == -1) { //czarny - konflikt

							zmien = 1;
							break;
						}

					}
				}

				if (zmien) {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(0, 0, 0));
				}
				else {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(255, 255, 255));
				}
			}
		}

		for (kz = 0; kz < wypukleTEMP->Height; kz++) {
			for (kx = 0; kx < wypukleTEMP->Width; kx++) {

				Px = wypukleTEMP->GetPixel(kx, kz);
				if (Px.R == 255) wypukle->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));

			}
		}

		//maska 6:
		for (kz = promien; kz < obrazIN->Height - promien; kz++) {
			for (kx = promien; kx < obrazIN->Width - promien; kx++) {

				Px = wypukle->GetPixel(kx, kz);
				bool zmien = 0;

				for (int i = kz - promien, m = 0; i < kz - promien + (3); i++, m++) {
					for (int j = kx - promien, n = 0; j < kx - promien + (3); j++, n++) {

						Px = wypukle->GetPixel(j, i);

						if (tab6[m][n] == 0) continue; //skip
						if (Px.R == 0 && tab6[m][n] == 1) { //czarny - konflikt

							zmien = 1;
							break;
						}
						if (Px.R == 255 && tab6[m][n] == -1) { //czarny - konflikt

							zmien = 1;
							break;
						}

					}
				}

				if (zmien) {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(0, 0, 0));
				}
				else {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(255, 255, 255));
				}
			}
		}

		for (kz = 0; kz < wypukleTEMP->Height; kz++) {
			for (kx = 0; kx < wypukleTEMP->Width; kx++) {

				Px = wypukleTEMP->GetPixel(kx, kz);
				if (Px.R == 255) wypukle->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));

			}
		}

		//maska 7:
		for (kz = promien; kz < obrazIN->Height - promien; kz++) {
			for (kx = promien; kx < obrazIN->Width - promien; kx++) {

				Px = wypukle->GetPixel(kx, kz);
				bool zmien = 0;

				for (int i = kz - promien, m = 0; i < kz - promien + (3); i++, m++) {
					for (int j = kx - promien, n = 0; j < kx - promien + (3); j++, n++) {

						Px = wypukle->GetPixel(j, i);

						if (tab7[m][n] == 0) continue; //skip
						if (Px.R == 0 && tab7[m][n] == 1) { //czarny - konflikt

							zmien = 1;
							break;
						}
						if (Px.R == 255 && tab7[m][n] == -1) { //czarny - konflikt

							zmien = 1;
							break;
						}

					}
				}

				if (zmien) {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(0, 0, 0));
				}
				else {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(255, 255, 255));
				}
			}
		}

		for (kz = 0; kz < wypukleTEMP->Height; kz++) {
			for (kx = 0; kx < wypukleTEMP->Width; kx++) {

				Px = wypukleTEMP->GetPixel(kx, kz);
				if (Px.R == 255) wypukle->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));

			}
		}

		//maska 8:
		for (kz = promien; kz < obrazIN->Height - promien; kz++) {
			for (kx = promien; kx < obrazIN->Width - promien; kx++) {

				Px = wypukle->GetPixel(kx, kz);
				bool zmien = 0;

				for (int i = kz - promien, m = 0; i < kz - promien + (3); i++, m++) {
					for (int j = kx - promien, n = 0; j < kx - promien + (3); j++, n++) {

						Px = wypukle->GetPixel(j, i);

						if (tab8[m][n] == 0) continue; //skip
						if (Px.R == 0 && tab8[m][n] == 1) { //czarny - konflikt

							zmien = 1;
							break;
						}
						if (Px.R == 255 && tab8[m][n] == -1) { //czarny - konflikt

							zmien = 1;
							break;
						}

					}
				}

				if (zmien) {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(0, 0, 0));
				}
				else {
					Px = wypukle->GetPixel(kx, kz);
					wypukleTEMP->SetPixel(kx, kz, Px.FromArgb(255, 255, 255));
				}
			}
		}

		for (kz = 0; kz < wypukleTEMP->Height; kz++) {
			for (kx = 0; kx < wypukleTEMP->Width; kx++) {

				Px = wypukleTEMP->GetPixel(kx, kz);
				if (Px.R == 255) wypukle->SetPixel(kx, kz, Px.FromArgb(Px.R, Px.G, Px.B));

			}
		}
	
	}

	return wypukle;
}
	  

