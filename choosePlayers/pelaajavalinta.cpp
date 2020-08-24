#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/compare.hpp>
#include "boost/tuple/tuple.hpp"
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;


vector<boost::tuple<string, double, int>> tuplelista_tekstista(string filename)
{
	vector<boost::tuple<string, double, int>> lista;
	vector<string>rivit;
	vector<string>pala_in_rivi;
	string palikka;
	double hgmp;
	int hinta;
	ifstream in(filename);
	string contents((istreambuf_iterator<char>(in)),
		istreambuf_iterator<char>());
	split(rivit, contents, is_any_of("\n"));
	for (vector<string>::const_iterator it = rivit.begin(); it != rivit.end(); ++it)
	{

		palikka = *it;
		for (int i = 0; i < 3; i++)
		{
			palikka.pop_back();
		}

		split(pala_in_rivi, palikka, is_any_of("\t"));

		palikka = pala_in_rivi[21];
		palikka.erase(remove_if(palikka.begin(), palikka.end(), isspace), palikka.end());
		lista.push_back(boost::make_tuple(pala_in_rivi[0], lexical_cast<double>(pala_in_rivi[19]), lexical_cast<int>(palikka)));
	}
	return lista;

}

void koko_kentta(vector<boost::tuple<string, double, int>> hyokkaajat, vector<boost::tuple<string, double, int>> puolustajat,int raha)
{

	double hgmp_edellinen = 0;
	double hgmp = 0;
	int pelaajien_hinta = 0;
	int counter = 0;

	for (vector<boost::tuple<string, double, int>>::const_iterator it1 = hyokkaajat.begin(); it1 != hyokkaajat.end(); ++it1)
	{
		cout << float(counter / float(hyokkaajat.size())) * float(100) << "%" << endl;
		counter++;
		for (vector<boost::tuple<string, double, int>>::const_iterator it2 = hyokkaajat.begin(); it2 != hyokkaajat.end(); ++it2)
		{
			for (vector<boost::tuple<string, double, int>>::const_iterator it3 = hyokkaajat.begin(); it3 != hyokkaajat.end(); ++it3)
			{
				if (get<0>(*it1) != get<0>(*it2) && get<0>(*it1) != get<0>(*it3) && get<0>(*it2) != get<0>(*it3))
				{
					for (vector<boost::tuple<string, double, int>>::const_iterator it4 = puolustajat.begin(); it4 != puolustajat.end(); ++it4)
					{
						for (vector<boost::tuple<string, double, int>>::const_iterator it5 = puolustajat.begin(); it5 != puolustajat.end(); ++it5)
						{
							if (get<0>(*it4) != get<0>(*it5))
							{
								pelaajien_hinta = get<2>(*it1) + get<2>(*it2) + get<2>(*it3) + get<2>(*it4) + get<2>(*it5);
								if (pelaajien_hinta <= raha)
								{
									hgmp = get<1>(*it1) + get<1>(*it2) + get<1>(*it3) + get<1>(*it4) + get<1>(*it5);
									if (hgmp > hgmp_edellinen)
									{
										hgmp_edellinen = hgmp;
										cout << "hyokkaajat: " << get<0>(*it1) << "," << get<0>(*it2) << "," << get<0>(*it3) << endl << "puolustajat: " << get<0>(*it4) << "," << get<0>(*it5) << endl << "hgmp/o: " << hgmp_edellinen << ",  hinta: " << pelaajien_hinta << endl;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void two_H_two_P(vector<boost::tuple<string, double, int>> hyokkaajat, vector<boost::tuple<string, double, int>> puolustajat, int raha)
{
	double hgmp_edellinen = 0;
	double hgmp = 0;
	int pelaajien_hinta = 0;

	for (vector<boost::tuple<string, double, int>>::const_iterator it1 = hyokkaajat.begin(); it1 != hyokkaajat.end(); ++it1)
	{
		for (vector<boost::tuple<string, double, int>>::const_iterator it2 = hyokkaajat.begin(); it2 != hyokkaajat.end(); ++it2)
		{
			if (get<0>(*it1) != get<0>(*it2))
			{
				for (vector<boost::tuple<string, double, int>>::const_iterator it4 = puolustajat.begin(); it4 != puolustajat.end(); ++it4)
				{
					for (vector<boost::tuple<string, double, int>>::const_iterator it5 = puolustajat.begin(); it5 != puolustajat.end(); ++it5)
					{
						if (get<0>(*it4) != get<0>(*it5))
						{
							pelaajien_hinta = get<2>(*it1) + get<2>(*it2) + get<2>(*it4) + get<2>(*it5);
							if (pelaajien_hinta <= raha)
							{
								hgmp = get<1>(*it1) + get<1>(*it2) + get<1>(*it4) + get<1>(*it5);
								if (hgmp > hgmp_edellinen)
								{
									hgmp_edellinen = hgmp;
									cout << "hyokkaajat: " << get<0>(*it1) << "," << get<0>(*it2) << endl << "puolustajat: " << get<0>(*it4) << "," << get<0>(*it5) << endl << "hgmp/o: " << hgmp_edellinen << ",  hinta: " << pelaajien_hinta << endl;
								}
							}
						}
					}
				}
			}
			
		}
	}
}

void one_H_two_P(vector<boost::tuple<string, double, int>> hyokkaajat, vector<boost::tuple<string, double, int>> puolustajat, int raha)
{
	double hgmp_edellinen = 0;
	double hgmp = 0;
	int pelaajien_hinta = 0;

	for (vector<boost::tuple<string, double, int>>::const_iterator it1 = hyokkaajat.begin(); it1 != hyokkaajat.end(); ++it1)
	{
		for (vector<boost::tuple<string, double, int>>::const_iterator it4 = puolustajat.begin(); it4 != puolustajat.end(); ++it4)
		{
			for (vector<boost::tuple<string, double, int>>::const_iterator it5 = puolustajat.begin(); it5 != puolustajat.end(); ++it5)
			{
				if (get<0>(*it4) != get<0>(*it5))
				{
					pelaajien_hinta = get<2>(*it1) + get<2>(*it4) + get<2>(*it5);
					if (pelaajien_hinta <= raha)
					{
						hgmp = get<1>(*it1) + get<1>(*it4) + get<1>(*it5);
						if (hgmp > hgmp_edellinen)
						{
							hgmp_edellinen = hgmp;
							cout << "hyokkaajat: " << get<0>(*it1) << endl << "puolustajat: " << get<0>(*it4) << "," << get<0>(*it5) << endl << "hgmp/o: " << hgmp_edellinen << ",  hinta: " << pelaajien_hinta << endl;
						}
					}
				}
			}
		}
	}
}

void one_H_one_P(vector<boost::tuple<string, double, int>> hyokkaajat, vector<boost::tuple<string, double, int>> puolustajat, int raha)
{
	double hgmp_edellinen = 0;
	double hgmp = 0;
	int pelaajien_hinta = 0;

	for (vector<boost::tuple<string, double, int>>::const_iterator it1 = hyokkaajat.begin(); it1 != hyokkaajat.end(); ++it1)
	{
		for (vector<boost::tuple<string, double, int>>::const_iterator it5 = puolustajat.begin(); it5 != puolustajat.end(); ++it5)
		{
			pelaajien_hinta = get<2>(*it1) + get<2>(*it5);
			if (pelaajien_hinta <= raha)
			{
				hgmp = get<1>(*it1) + get<1>(*it5);
				if (hgmp > hgmp_edellinen)
				{
					hgmp_edellinen = hgmp;
					cout << "hyokkaajat: " << get<0>(*it1) << endl << "puolustajat: " << get<0>(*it5) << endl << "hgmp/o: " << hgmp_edellinen << ",  hinta: " << pelaajien_hinta << endl;
				}
			}
		}
	}
}

void two_H_one_P(vector<boost::tuple<string, double, int>> hyokkaajat, vector<boost::tuple<string, double, int>> puolustajat, int raha)
{
	double hgmp_edellinen = 0;
	double hgmp = 0;
	int pelaajien_hinta = 0;

	for (vector<boost::tuple<string, double, int>>::const_iterator it1 = hyokkaajat.begin(); it1 != hyokkaajat.end(); ++it1)
	{
		for (vector<boost::tuple<string, double, int>>::const_iterator it2 = hyokkaajat.begin(); it2 != hyokkaajat.end(); ++it2)
		{
			if (get<0>(*it1) != get<0>(*it2))
			{

				for (vector<boost::tuple<string, double, int>>::const_iterator it5 = puolustajat.begin(); it5 != puolustajat.end(); ++it5)
				{

					pelaajien_hinta = get<2>(*it1) + get<2>(*it2) + get<2>(*it5);
					if (pelaajien_hinta <= raha)
					{
						hgmp = get<1>(*it1) + get<1>(*it2) + get<1>(*it5);
						if (hgmp > hgmp_edellinen)
						{
							hgmp_edellinen = hgmp;
							cout << "hyokkaajat: " << get<0>(*it1) << "," << get<0>(*it2) << endl << "puolustajat: " << get<0>(*it5) << endl << "hgmp/o: " << hgmp_edellinen << ",  hinta: " << pelaajien_hinta << endl;
						}
					}
				}
			}
		}
	}
}

void tre_H(vector<boost::tuple<string, double, int>> hyokkaajat, int raha)
{
	double hgmp_edellinen = 0;
	double hgmp = 0;
	int pelaajien_hinta = 0;
	for (vector<boost::tuple<string, double, int>>::const_iterator it1 = hyokkaajat.begin(); it1 != hyokkaajat.end(); ++it1)
	{
		for (vector<boost::tuple<string, double, int>>::const_iterator it2 = hyokkaajat.begin(); it2 != hyokkaajat.end(); ++it2)
		{
			for (vector<boost::tuple<string, double, int>>::const_iterator it3 = hyokkaajat.begin(); it3 != hyokkaajat.end(); ++it3)
			{
				if (get<0>(*it1) != get<0>(*it2) && get<0>(*it1) != get<0>(*it3) && get<0>(*it2) != get<0>(*it3))
				{
					pelaajien_hinta = get<2>(*it1) + get<2>(*it2) + get<2>(*it3);
					if (pelaajien_hinta <= raha)
					{
						hgmp = get<1>(*it1) + get<1>(*it2) + get<1>(*it3);
						if (hgmp > hgmp_edellinen)
						{
							hgmp_edellinen = hgmp;
							cout << "hyokkaajat: " << get<0>(*it1) << "," << get<0>(*it2) << "," << get<0>(*it3) << endl << "hgmp/o: " << hgmp_edellinen << ",  hinta: " << pelaajien_hinta << endl;
						}
					}
				}
			}
		}
	}
}

void two_H(vector<boost::tuple<string, double, int>> hyokkaajat, int raha)
{
	double hgmp_edellinen = 0;
	double hgmp = 0;
	int pelaajien_hinta = 0;

	for (vector<boost::tuple<string, double, int>>::const_iterator it2 = hyokkaajat.begin(); it2 != hyokkaajat.end(); ++it2)
	{
		for (vector<boost::tuple<string, double, int>>::const_iterator it3 = hyokkaajat.begin(); it3 != hyokkaajat.end(); ++it3)
		{
			if (get<0>(*it2) != get<0>(*it3))
			{
				pelaajien_hinta = get<2>(*it2) + get<2>(*it3);
				if (pelaajien_hinta <= raha)
				{
					hgmp = get<1>(*it2) + get<1>(*it3);
					if (hgmp > hgmp_edellinen)
					{
						hgmp_edellinen = hgmp;
						cout << "hyokkaajat: " << get<0>(*it2) << "," << get<0>(*it3) << endl << "hgmp/o: " << hgmp_edellinen << ",  hinta: " << pelaajien_hinta << endl;
					}
				}
			}
		}
	}
}

void oneH(vector<boost::tuple<string, double, int>> hyokkaajat, int raha)
{
	double hgmp_edellinen = 0;
	double hgmp = 0;
	int pelaajien_hinta = 0;


	for (vector<boost::tuple<string, double, int>>::const_iterator it3 = hyokkaajat.begin(); it3 != hyokkaajat.end(); ++it3)
	{
		pelaajien_hinta = get<2>(*it3);
		if (pelaajien_hinta <= raha)
		{
			hgmp = get<1>(*it3);
			if (hgmp > hgmp_edellinen)
			{
				hgmp_edellinen = hgmp;
				cout << "hyokkaajat: " << get<0>(*it3) << endl << "hgmp/o: " << hgmp_edellinen << ",  hinta: " << pelaajien_hinta << endl;
			}
		}	
	}
}

void two_P(vector<boost::tuple<string, double, int>> puolustajat, int raha)
{
	double hgmp_edellinen = 0;
	double hgmp = 0;
	int pelaajien_hinta = 0;


	for (vector<boost::tuple<string, double, int>>::const_iterator it4 = puolustajat.begin(); it4 != puolustajat.end(); ++it4)
	{
		for (vector<boost::tuple<string, double, int>>::const_iterator it5 = puolustajat.begin(); it5 != puolustajat.end(); ++it5)
		{
			if (get<0>(*it4) != get<0>(*it5))
			{
				pelaajien_hinta = get<2>(*it4) + get<2>(*it5);
				if (pelaajien_hinta <= raha)
				{
					hgmp = get<1>(*it4) + get<1>(*it5);
					if (hgmp > hgmp_edellinen)
					{
						hgmp_edellinen = hgmp;
						cout << "puolustajat: " << get<0>(*it4) << "," << get<0>(*it5) << endl << "hgmp/o: " << hgmp_edellinen << ",  hinta: " << pelaajien_hinta << endl;
					}
				}
			}
		}
	}
}

void oneP(vector<boost::tuple<string, double, int>> puolustajat, int raha)
{
	double hgmp_edellinen = 0;
	double hgmp = 0;
	int pelaajien_hinta = 0;

	for (vector<boost::tuple<string, double, int>>::const_iterator it5 = puolustajat.begin(); it5 != puolustajat.end(); ++it5)
	{
		pelaajien_hinta = get<2>(*it5);
		if (pelaajien_hinta <= raha)
		{
			hgmp = get<1>(*it5);
			if (hgmp > hgmp_edellinen)
			{
				hgmp_edellinen = hgmp;
				cout << "puolustajat: " << get<0>(*it5) << endl << "hgmp/o: " << hgmp_edellinen << ",  hinta: " << pelaajien_hinta << endl;
			}
		}
			
	}
}



int main()
{
	bool looppi = true;
	int rahe;
	int inputti;
	string filename_hyokkaajat = "hyokkaajat.txt";
	string filename_puolustajat = "puolustajat.txt";
	vector<boost::tuple<string, double, int>> hyokkaajat = tuplelista_tekstista(filename_hyokkaajat);
	vector<boost::tuple<string, double, int>> puolustajat = tuplelista_tekstista(filename_puolustajat);

	
	while (looppi)
	{
		cout << "mita vaihdetaan:D? anna numero" << endl;
		cout << "0,koko kentta" << endl;
		cout << "1,two_H_two_P" << endl;
		cout << "2,one_H_two_P" << endl;
		cout << "3,two_H_one_P" << endl;
		cout << "4,one_H_one_P" << endl;
		cout << "5,tre_H" << endl;
		cout << "6,two_H" << endl;
		cout << "7,one_H" << endl;
		cout << "8,two_P" << endl;
		cout << "9,one_P" << endl;
		cout << "10,quit" << endl;
		cin >> inputti;

		if (inputti == 10)
		{
			looppi = false;
			break;
		}

		cout << "paljonko rahea?: ";
		cin >> rahe;

		switch (inputti)
		{
		case 0:
			koko_kentta(hyokkaajat, puolustajat, rahe);
			break;
		case 1:
			two_H_two_P(hyokkaajat, puolustajat, rahe);
			break;
		case 2:
			one_H_two_P(hyokkaajat, puolustajat, rahe);
			break;
		case 3:
			two_H_one_P(hyokkaajat, puolustajat, rahe);
			break;
		case 4:
			one_H_one_P(hyokkaajat, puolustajat, rahe);
			break;
		case 5:
			tre_H(hyokkaajat, rahe);
			break;
		case 6:
			two_H(hyokkaajat, rahe);
			break;
		case 7:
			oneH(hyokkaajat, rahe);
			break;
		case 8:
			two_P(puolustajat, rahe);
			break;
		case 9:
			oneP(puolustajat, rahe);
			break;
		}
		cout << "valmis!" << endl;
		cout << "press enter to gondinnue" << endl;
		cin.get();
		cin.get();
	}
}