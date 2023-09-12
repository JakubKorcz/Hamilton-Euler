#include <iostream>
#include <fstream>

using namespace std;

bool **e_visited;
bool* t_visited;
int* stos;
int *stos_ost;
int wsk;
int **tab;
int **tab1;
int poczatek=1;

void HamRek(int a,int b, int v)
{
	v = v - 1;
	stos[wsk] = v; // zapamiętujemy na stosie bieżący wierzchołek
	wsk++;
	if (wsk < a)                 
	{
		t_visited[v] = true;		// Oznaczamy bieżący wierzchołek jako odwiedzony
		for (int i = 0; i < a; i++)   // Przeglądamy sąsiadów wierzchołka v
		{
	
			if (tab1[v][i] == 1 && !t_visited[i]) // Szukamy nieodwiedzonego jeszcze sąsiada
			{
				
				HamRek(a, b, i+1);                 // Rekurencyjnie wywołujemy szukanie cyklu Hamiltona
			}
		}
		t_visited[v] = false;         // Zwalniamy bieżący wierzchołek
	}
	else if (tab1[v][poczatek - 1] == 1 && a==wsk)         // Jeśli znaleziona ścieżka jest cyklem Hamiltona
	{
			for (int i = 0; i< a; i++) //  kopiujemy stos do stosu ost
				stos_ost[i] = stos[i];
	}
	wsk--;
}

void Hamilton(int a,int b)
{
	 
	for (int i = 0; i < a; i++)
	{
		t_visited[i] = false;
	}
	for (int i = 0; i < a; i++)
	{
		e_visited[i] = new bool[a];
		for(int j=0;j<a;j++)
		{
			e_visited[i][j] = false;
		}
	}
	
	HamRek(a,b,poczatek);
}


void EulRek(int a, int b, int v)
{
	v = v - 1;
	for (int i = 0; i < a; i++)   // Przeglądamy sąsiadów
		while (tab1[v][i])
		{
			tab1[v][i] --;       // Usuwamy krawędź
			//tab1[i][v] --;
			EulRek(a,b,i+1);        // Rekurencja
		}
	stos[wsk++] = v;          // Wierzchołek v umieszczamy na stosie
}


void Euler(int a, int b)
{
	for (int i = 0; i < a; i++)
	{
		t_visited[i] = false;
	}
	for (int i = 0; i < a; i++)
	{
		e_visited[i] = new bool[a];
		for (int j = 0; j < a; j++)
		{
			e_visited[i][j] = false;
		}
	}
	EulRek(a,b,poczatek);
}


int main()
{
	int a = 20;
	int b = 0;
	int c;
	int d;
	bool pom[7] = { true };
	
	 stos = new int[b];
	 stos_ost = new int[a];
	e_visited = new bool* [a];//czy krawedz odwiedzona
	 t_visited = new bool[a];//czy wierzchołek odwiedzony
	 wsk = 0;
	
		fstream plik;
		plik.open("dane.txt" , ios::out | ios::in);
		if (plik.good() == true)
		{
			
			//Algorytm losowania grafu
			
			/*srand(time(NULL));
			
			for (int i = 0; i < a; i++)
			{
				int czy_jeszcze = 0;
				while (czy_jeszcze == 0) {
					czy_jeszcze = (rand() % 2);
					int wylosowana_liczba = (std::rand() % 7) + 1;

					if (i + wylosowana_liczba <= a&&pom[wylosowana_liczba-1])
					{
						plik << i << " " << i + wylosowana_liczba << endl;
						b++;
						pom[wylosowana_liczba - 1] = false;
					}
				}
				for(int k=0;k<7;k++)
				{
					pom[k] = true;
				}
			}*/
			plik.seekg(0);
			plik >> a >> b;
			
			tab = new int* [b]; // tablica zawierajaca wszytskie wierzchołki z pliku
			for (int i = 0; i < b; i++)
			{

				plik >> c >> d;
				tab[i] = new int[2];
				tab[i][0] = c;
				tab[i][1] = d;
			}
			
			tab1 = new int* [a]; //wsk na tablice pokazujaca ilosc wierzchołków i usytuowanie krawedzi
			
			
		   //lokowanie pamieci
			for (int i = 0; i < a; i++)
			{
				tab1[i] = new int[a];
				for (int j = 0; j < a; j++)
					for (int k = 0; k < b; k++)
					{
						if (tab[k][0] - 1 == i && tab[k][1] - 1 == j)
						{
							tab1[i][j] = 1;
							break;
						}
						else {
							tab1[i][j] = 0;
						}
					}
			}

			//wypisywanie 
			for (int i = 0; i < a; i++) {
				for (int j = 0; j < a; j++)
				{
					cout << tab1[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;

			Hamilton(a,b);

			//wypisywanie hamiltona
			cout << "Cykl hamiltona: " << endl;
			for (int i = 0; i < a; i++)
				cout << stos_ost[i]+1 << ", ";
			cout << endl;

			Euler(a, b);
			
			//wypisywanie Eulera
			cout << "Cykl Eulera: " << endl;
			for (int i = b; i >0 ; i--)
				cout << stos[i]+1 << ", ";
			//cout << stos[0]+1;
			cout << endl;

			//usuwanie tablic

			for (int i(0); i < a; ++i)
				delete[] tab1[i]; //uwolnienie pamieci
			delete[] tab1; //uwolnienie pamieci
			tab1 = NULL;

		}
		else cout << "Dostep do pliku zostal zabroniony!" << endl;
		plik.close();
}