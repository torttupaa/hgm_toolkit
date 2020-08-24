#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/compare.hpp>


using namespace std;
using namespace boost;

//global vars
vector<string> tiimit;
vector<string> paivat;
vector<vector<vector<string>>> ottelut_paivana_lista;
vector<vector<int>> ottelupaiva_tiimit_indexeina;
vector<vector<int>> joukkoeiden_ottelut;


void csvCreator()
{
	auto start = chrono::steady_clock::now();

	vector<string> rivitlistoissa;
	vector<string> rivilista;

	vector<vector<string>> ottelut_paivana;
	//vector<string> paivat{ ";" };
	//vector<string> tiimit;

	vector<string> temp_tiimi;

	//vector<vector<vector<string>>> ottelut_paivana_lista;

	string line_osa;
	string line;

	ifstream in("dddddd.txt");
	string contents((istreambuf_iterator<char>(in)),
		istreambuf_iterator<char>());

	split(rivitlistoissa, contents, is_any_of("\n"));

	ofstream filetowrite;
	filetowrite.open("ottelutaulukko.csv");
	ofstream file2towrite;
	file2towrite.open("pale.csv");

	filetowrite << ";";

	for (vector<string>::const_iterator i = rivitlistoissa.begin(); i != rivitlistoissa.end(); ++i)
	{
		line = *i;
		split(rivilista, line, is_any_of(" "));
		for (vector<string>::const_iterator j = rivilista.begin(); j != rivilista.end(); ++j)
		{
			line_osa = *j;
			if (line_osa.size() != 0)
			{
				if ((line_osa == "Monday,") || (line_osa == "Tuesday,") || (line_osa == "Wednesday,") || (line_osa == "Thursday,") || (line_osa == "Friday,") || (line_osa == "Saturday,") || (line_osa == "Sunday,"))
				{
					paivat.push_back(*(j + 1) + *(j + 2));
					filetowrite << *(j + 1) + *(j + 2) << ";";
					if (ottelut_paivana.size() > 0)
					{
						ottelut_paivana_lista.push_back(ottelut_paivana);
						ottelut_paivana.clear();
					}
				}
				if (line_osa.back() == '@')
				{
					line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
					split(temp_tiimi, line, is_any_of("@"));
					ottelut_paivana.push_back(temp_tiimi);

					if (!(find(tiimit.begin(), tiimit.end(), temp_tiimi[0]) != tiimit.end()))
					{
						tiimit.push_back(temp_tiimi[0]);
					}
				}
			}
		}
		rivilista.clear();
	}

	ottelut_paivana_lista.push_back(ottelut_paivana);


	bool on_peli;
	string vastustaja;

	//taulukko.push_back(paivat);
	filetowrite << endl;

	for (int i = 0; i < tiimit.size(); i++)
	{
		on_peli = false;
		filetowrite << tiimit[i] << ";";

		for (int j = 0; j < ottelut_paivana_lista.size(); j++)
		{
			for (int k = 0; k < ottelut_paivana_lista[j].size(); k++)
			{
				if (ottelut_paivana_lista[j][k][0] == tiimit[i])
				{
					on_peli = true;
					vastustaja = ottelut_paivana_lista[j][k][1];
					break;
				}
				if (ottelut_paivana_lista[j][k][1] == tiimit[i])
				{
					on_peli = true;
					vastustaja = ottelut_paivana_lista[j][k][0];
					break;
				}
			}
			if (on_peli)
			{
				//taulukko_rivi.push_back(vastustaja);
				filetowrite << vastustaja << ";";
				file2towrite << vastustaja << ";";
			}
			else
			{
				//taulukko_rivi.push_back(";");
				filetowrite << ";";
				file2towrite << ";";
			}
			on_peli = false;
		}
		filetowrite << endl;
		file2towrite << endl;
	}


	//taulukko.push_back(taulukko_rivi);


	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	std::cout << "Time: "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;

	cout << "created ottelutaulukko.csv && pale.csv" << endl;
}

void jottelut_create()
{
	vector<string> rivi;
	vector<string> rivilista;

	vector<int> jottelut;

	ifstream in("pale.csv");
	string contents((istreambuf_iterator<char>(in)),
		istreambuf_iterator<char>());

	split(rivi, contents, is_any_of("\n"));

	for (vector<string>::iterator it = rivi.begin(); it != rivi.end(); it++)
	{
		split(rivilista, *it, is_any_of(";"));
		for (vector<string>::iterator itr = rivilista.begin(); itr != rivilista.end(); itr++)
		{
			if ((*itr).size() > 1)
			{
				jottelut.push_back(1);
			}
			else
			{
				jottelut.push_back(0);
			}
		}
		jottelut.pop_back();
		//cout << jottelut.size() << endl;
		if (jottelut.size() == paivat.size())
		{
			joukkoeiden_ottelut.push_back(jottelut);
		}
		jottelut.clear();
	}
	//cout << joukkoeiden_ottelut.size() << endl;
}

void OPlistaConverter()
{
	vector<int> OPI;
	ottelupaiva_tiimit_indexeina.reserve(ottelut_paivana_lista.size());
	for (int i = 0; i < ottelut_paivana_lista.size(); i++)
	{
		for (int j = 0; j < ottelut_paivana_lista[i].size(); j++)
		{
			for (int k = 0; k < ottelut_paivana_lista[i][j].size(); k++)
			{
				for (int l = 0; l < tiimit.size(); l++)
				{
					if (tiimit[l] == ottelut_paivana_lista[i][j][k])
					{
						OPI.push_back(l);
						break;
					}
				}
			}
		}
		ottelupaiva_tiimit_indexeina.push_back(OPI);
		OPI.clear();
	}
}

int ottelumaara(vector<int> combo)
{
	int combon_ottelumaara = 0;
	for (int i = 0; i < ottelupaiva_tiimit_indexeina.size(); i++)
	{
		for (int j = 0; j < ottelupaiva_tiimit_indexeina[i].size(); j++)
		{
			if (ottelupaiva_tiimit_indexeina[i][j] == combo[i])
			{
				combon_ottelumaara++;
			}
		}
	}
	return combon_ottelumaara;
}

void one_vaihto()
{
	int just_counter = 0;

	vector<int> joukkoe_paivassa(paivat.size());
	int shifter = 1;

	int pos_team_ord = 2;
	vector<int> j1j2_ord(2);
	int j1;
	int j2;

	int edellinen_paras = 0;
	int combo_ottelut;

	ofstream filetowrite;
	filetowrite.open("1_vaihto.csv");

	for (vector<string>::iterator itr = paivat.begin(); itr != paivat.end(); itr++)
	{
		filetowrite << *itr << ";";
	}
	filetowrite << endl;

	//tiimien lapikaynti
	for (int t1_index = 0; t1_index < tiimit.size() - 1; t1_index++)
	{
		for (int t2_index = t1_index + 1; t2_index < tiimit.size(); t2_index++)
		{

			//team order esim 2 tiimillä ord1 t1,t2  ord2 t2,t1
			j1j2_ord = { t1_index , t2_index };
			for (int x = 0; x < pos_team_ord;x++)
			{
				j1 = j1j2_ord[0];
				j2 = j1j2_ord[1];

				j1j2_ord[0] = j2;
				j1j2_ord[1] = j1;

				//shifter on tiiminvaihtopositio
				for (int shifter = 0; shifter < paivat.size(); shifter++)
				{
					//tiimi 1 taytto
					for (unsigned int k = 0; k < shifter; ++k)
					{
						joukkoe_paivassa[k] = j1;
					}
					//tiimi 2 taytto
					for (unsigned int k = shifter; k < paivat.size(); ++k)
					{
						joukkoe_paivassa[k] = j2;
					}

					//vertailu edelisiin
					combo_ottelut = ottelumaara(joukkoe_paivassa);
					if (combo_ottelut >= edellinen_paras)
					{
						edellinen_paras = combo_ottelut;
						for (vector<int>::iterator itr = joukkoe_paivassa.begin(); itr != joukkoe_paivassa.end(); itr++)
						{
							filetowrite << tiimit[*itr] << ";";
						}
						filetowrite << combo_ottelut  << endl;
					}
					just_counter++;
				}
			}
		}
	}
}

void two_vaihto()
{
	unsigned long long just_counter = 0;

	vector<int> joukkoe_paivassa(paivat.size());

	int edellinen_paras = 0;
	int combo_ottelut;

	ofstream filetowrite;
	filetowrite.open("2_vaihto64.csv");

	for (vector<string>::iterator itr = paivat.begin(); itr != paivat.end(); itr++)
	{
		filetowrite << *itr << ";";
	}
	filetowrite << endl;

	//tiimien lapikaynti
	for (int t1_index = 0; t1_index < tiimit.size() - 1; t1_index++)
	{
		for (int t2_index = 0; t2_index < tiimit.size(); t2_index++)
		{
			if (t1_index != t2_index)
			{
				for (int t3_index = 0; t3_index < tiimit.size(); t3_index++)
				{
					if (t2_index != t3_index)
					{
						//shifter on tiiminvaihtopositio
						for (int shifter = 1; shifter < paivat.size()-2; shifter++)
						{
							for (int shifter2 = shifter + 1; shifter2 < paivat.size()-1; shifter2++)
							{
								//tiimi 1 taytto
								for (unsigned int k = 0; k < shifter; ++k)
								{
									joukkoe_paivassa[k] = t1_index;
								}
								//tiimi 2 taytto
								for (unsigned int k = shifter; k < shifter2; ++k)
								{
									joukkoe_paivassa[k] = t2_index;
								}
								// tiimi 3 taytto
								for (unsigned int k = shifter2; k < paivat.size(); ++k)
								{
									joukkoe_paivassa[k] = t3_index;
								}

								//vertailu edelisiin
								combo_ottelut = ottelumaara(joukkoe_paivassa);
								if (combo_ottelut >= edellinen_paras)
								{
									edellinen_paras = combo_ottelut;
									for (vector<int>::iterator itr = joukkoe_paivassa.begin(); itr != joukkoe_paivassa.end(); itr++)
									{
										filetowrite << tiimit[*itr] << ";";
									}
									filetowrite << combo_ottelut << endl;
								}
								just_counter++;
							}
						}
					}
				}
			}
		}
		cout << just_counter << " 2_vaihto.csv " << float(float(float(t1_index + 1) / tiimit.size()) * 100) << "%" << endl;
	}
	cout << just_counter << " comboo tarkastettu" << endl;
	cout << "created 2_vaihto.csv" << endl;
}

void tre_vaihto()
{
	unsigned long long just_counter = 0;

	vector<int> joukkoe_paivassa(paivat.size());

	int edellinen_paras = 0;
	int combo_ottelut;
	int gynder = 0;

	ofstream filetowrite;
	filetowrite.open("3_vaihto64.csv");

	for (vector<string>::iterator itr = paivat.begin(); itr != paivat.end(); itr++)
	{
		filetowrite << *itr << ";";
	}
	filetowrite << endl;

	//tiimien lapikaynti
	for (int t1_index = 0; t1_index < tiimit.size() - 1; t1_index++)
	{
		for (int t2_index = 0; t2_index < tiimit.size(); t2_index++)
		{
			if (t1_index != t2_index)
			{
				for (int t3_index = 0; t3_index < tiimit.size(); t3_index++)
				{
					if (t2_index != t3_index)
					{
						for (int t4_index = 0; t4_index < tiimit.size(); t4_index++)
						{
							if (t3_index != t4_index)
							{
								//shifter on tiiminvaihtopositio
								for (int shifter = 1; shifter < paivat.size()-3; shifter++)
								{
									for (int shifter2 = shifter+1; shifter2 < paivat.size()-2; shifter2++)
									{
										for (int shifter3 = shifter2+1; shifter3 < paivat.size()-1; shifter3++)
										{
											//tiimi 1 taytto
											for (unsigned int k = 0; k < shifter; ++k)
											{
												joukkoe_paivassa[k] = t1_index;
											}
											//tiimi 2 taytto
											for (unsigned int k = shifter; k < shifter2; ++k)
											{
												joukkoe_paivassa[k] = t2_index;
											}
											// tiimi 3 taytto
											for (unsigned int k = shifter2; k < shifter3; ++k)
											{
												joukkoe_paivassa[k] = t3_index;
											}
											for (unsigned int k = shifter3; k < paivat.size(); ++k)
											{
												joukkoe_paivassa[k] = t4_index;
											}

											//vertailu edelisiin
											combo_ottelut = ottelumaara(joukkoe_paivassa);
											if (combo_ottelut >= edellinen_paras)
											{
												edellinen_paras = combo_ottelut;
												for (vector<int>::iterator itr = joukkoe_paivassa.begin(); itr != joukkoe_paivassa.end(); itr++)
												{
													filetowrite << tiimit[*itr] << ";";
												}
												filetowrite << combo_ottelut << endl;
											}
											just_counter++;
										}
									}
								}
							}
						}
					}
				}
				gynder++;
				cout << just_counter << " 3_vaihto.csv " << float(float(float(gynder) / (tiimit.size() * tiimit.size())) * 100) << "%" << endl;
			}
		}
		//cout << just_counter << " tarkastettu " << (((t1_index+1)/tiimit.size())*100) << "%" << endl;
	}
	cout << just_counter << " comboo tarkastettu" << endl;
	cout << just_counter << " created 3_vaihto.csv" << endl;
}

void fast_tre()
{
	unsigned long long just_counter = 0;

	vector<int> joukkoe_paivassa(paivat.size());

	int edellinen_paras = 0;
	int combo_ottelut;
	int gynder = 0;

	int summa;

	ofstream filetowrite;
	filetowrite.open("3_vaihto64.csv");

	for (vector<string>::iterator itr = paivat.begin(); itr != paivat.end(); itr++)
	{
		filetowrite << *itr << ";";
	}
	filetowrite << endl;

	//tiimien lapikaynti
	for (int t1_index = 0; t1_index < tiimit.size() - 1; t1_index++)
	{
		for (int t2_index = 0; t2_index < tiimit.size(); t2_index++)
		{
			if (t1_index != t2_index)
			{
				for (int t3_index = 0; t3_index < tiimit.size(); t3_index++)
				{
					if (t2_index != t3_index)
					{
						for (int t4_index = 0; t4_index < tiimit.size(); t4_index++)
						{
							if (t3_index != t4_index)
							{
								//shifter on tiiminvaihtopositio
								for (int shifter = 1; shifter < paivat.size() - 3; shifter++)
								{
									for (int shifter2 = shifter + 1; shifter2 < paivat.size() - 2; shifter2++)
									{
										for (int shifter3 = shifter2 + 1; shifter3 < paivat.size() - 1; shifter3++)
										{
											summa = 0;
											for (unsigned int k = 0; k < shifter; ++k)
											{
												summa += joukkoeiden_ottelut[t1_index][k];
											}
											for (unsigned int k = shifter; k < shifter2; ++k)
											{
												summa += joukkoeiden_ottelut[t2_index][k];
											}
											for (unsigned int k = shifter2; k < shifter3; ++k)
											{
												summa += joukkoeiden_ottelut[t3_index][k];
											}
											for (unsigned int k = shifter3; k < paivat.size(); ++k)
											{
												summa += joukkoeiden_ottelut[t4_index][k];
											}

											//vertailu edelisiin
											//combo_ottelut = ottelumaara(joukkoe_paivassa);
											if (summa >= edellinen_paras)
											{
												edellinen_paras = summa;
												for (vector<int>::iterator itr = joukkoe_paivassa.begin(); itr != joukkoe_paivassa.end(); itr++)
												{
													for (unsigned int k = 0; k < shifter; ++k)
													{
														joukkoe_paivassa[k] = t1_index;
													}
													for (unsigned int k = shifter; k < shifter2; ++k)
													{
														joukkoe_paivassa[k] = t2_index;
													}
													for (unsigned int k = shifter2; k < shifter3; ++k)
													{
														joukkoe_paivassa[k] = t3_index;
													}
													for (unsigned int k = shifter3; k < paivat.size(); ++k)
													{
														joukkoe_paivassa[k] = t4_index;
													}
													filetowrite << tiimit[*itr] << ";";
												}
												filetowrite << summa << endl;
											}
											just_counter++;
										}
									}
								}
							}
						}
					}
				}
				gynder++;
				cout << just_counter << " 3_vaihto.csv " << float(float(float(gynder) / (tiimit.size() * tiimit.size())) * 100) << "%" << endl;
			}
		}
	}
	cout << just_counter << " comboo tarkastettu" << endl;
	cout << just_counter << " created 3_vaihto.csv" << endl;
}

int summaaja(int joukkoe,int eturaja, int takaraja)
{
	int ek = 0;
	for (int j = eturaja; j < takaraja; j++) //shift 1 asti
	{
		ek += joukkoeiden_ottelut[joukkoe][j];
	}
	return ek;
}

void superboosted_tre()
{
	ofstream filetowrite;
	filetowrite.open("3_vaihto.csv");

	int gynnther = 0;

	int eka;
	int ek;
	int toka;
	int tk;
	int kolmas;
	int kolm;
	int neljas;
	int nelj;

	int summa;

	int t1;
	int t2;
	int t3;
	int t4;

	int total = 0;

	for (int shifter1 = 1; shifter1 < paivat.size() - 3; shifter1++)
	{
		for (int shifter2 = shifter1 + 1; shifter2 < paivat.size() - 2; shifter2++)
		{
			for (int shifter3 = shifter2 + 1; shifter3 < paivat.size() - 1; shifter3++)
			{
				eka = -1;
				toka = -1;
				kolmas = -1;
				neljas = -1;
				for (int i = 0; i < joukkoeiden_ottelut.size(); i++) //tiimit lapi
				{
					//eka
					ek = 0;
					for (int j = 0; j < shifter1; j++)
					{
						ek += joukkoeiden_ottelut[i][j];
					}
					if (ek > eka)
					{
						eka = ek;
						t1 = i;
					}
					//toka
					tk = 0;
					for (int j = shifter1; j < shifter2; j++)
					{
						tk += joukkoeiden_ottelut[i][j];
					}
					if (tk > toka)
					{
						toka = tk;
						t2 = i;
					}
					//kolmas
					kolm = 0;
					for (int j = shifter2; j < shifter3; j++)
					{
						kolm += joukkoeiden_ottelut[i][j];
					}
					if (kolm > kolmas)
					{
						kolmas = kolm;
						t3 = i;
					}
					//neljäs
					nelj = 0;
					for (int j = shifter3; j < paivat.size(); j++)
					{
						nelj += joukkoeiden_ottelut[i][j];
					}
					if (nelj > neljas)
					{
						neljas = nelj;
						t4 = i;
					}
					/*
					summa = eka + toka + kolmas + neljas;
					if (summa >= total)
					{
						total = summa;
						for (int j = 0; j < shifter1; j++) 
						{
							filetowrite << tiimit[t1] << ";";
						}

						for (int j = shifter1; j < shifter2; j++) 
						{
							filetowrite << tiimit[t2] << ";";
						}

						for (int j = shifter2; j < shifter3; j++)
						{
							filetowrite << tiimit[t3] << ";";
						}

						for (int j = shifter3; j < paivat.size(); j++)
						{
							filetowrite << tiimit[t4] << ";";
						}
						filetowrite << summa << endl;
					}*/
				}
				summa = eka + toka + kolmas + neljas;
				if (summa >= total)
				{
					total = summa;
					for (int j = 0; j < shifter1; j++)
					{
						filetowrite << tiimit[t1] << ";";
					}

					for (int j = shifter1; j < shifter2; j++)
					{
						filetowrite << tiimit[t2] << ";";
					}

					for (int j = shifter2; j < shifter3; j++)
					{
						filetowrite << tiimit[t3] << ";";
					}

					for (int j = shifter3; j < paivat.size(); j++)
					{
						filetowrite << tiimit[t4] << ";";
					}
					filetowrite << summa << endl;
				}
			}
		}
	}
}

void superboosted_two()
{
	ofstream filetowrite;
	filetowrite.open("2_vaihto.csv");

	int gynnther = 0;

	int eka;
	int ek;
	int toka;
	int tk;
	int kolmas;
	int kolm;

	int summa;

	int t1;
	int t2;
	int t3;


	int total = 0;

	for (int shifter1 = 1; shifter1 < paivat.size() - 2; shifter1++)
	{
		for (int shifter2 = shifter1 + 1; shifter2 < paivat.size() - 1; shifter2++)
		{
			eka = -1;
			toka = -1;
			kolmas = -1;
			for (int i = 0; i < joukkoeiden_ottelut.size(); i++) //tiimit lapi
			{
				//eka
				ek = 0;
				for (int j = 0; j < shifter1; j++)
				{
					ek += joukkoeiden_ottelut[i][j];
				}
				if (ek > eka)
				{
					eka = ek;
					t1 = i;
				}
				//toka
				tk = 0;
				for (int j = shifter1; j < shifter2; j++)
				{
					tk += joukkoeiden_ottelut[i][j];
				}
				if (tk > toka)
				{
					toka = tk;
					t2 = i;
				}
				//kolmas
				kolm = 0;
				for (int j = shifter2; j < paivat.size(); j++)
				{
					kolm += joukkoeiden_ottelut[i][j];
				}
				if (kolm > kolmas)
				{
					kolmas = kolm;
					t3 = i;
				}

				/*
				summa = eka + toka + kolmas;
				if (summa >= total)
				{
					total = summa;
					for (int j = 0; j < shifter1; j++)
					{
						filetowrite << tiimit[t1] << ";";
					}

					for (int j = shifter1; j < shifter2; j++)
					{
						filetowrite << tiimit[t2] << ";";
					}

					for (int j = shifter2; j < paivat.size(); j++)
					{
						filetowrite << tiimit[t3] << ";";
					}

					filetowrite << summa << endl;
				}*/

			}
			
			summa = eka + toka + kolmas;
			if (summa >= total)
			{
				total = summa;
				for (int j = 0; j < shifter1; j++)
				{
					filetowrite << tiimit[t1] << ";";
				}

				for (int j = shifter1; j < shifter2; j++)
				{
					filetowrite << tiimit[t2] << ";";
				}

				for (int j = shifter2; j < paivat.size(); j++)
				{
					filetowrite << tiimit[t3] << ";";
				}

				filetowrite << summa << endl;
			}
		}
	}
}

void superboosted_four()
{
	ofstream filetowrite;
	filetowrite.open("4_vaihto.csv");

	int gynnther = 0;

	int eka;
	int ek;
	int toka;
	int tk;
	int kolmas;
	int kolm;
	int neljas;
	int nelj;
	int viides;
	int viid;

	int summa;

	int t1;
	int t2;
	int t3;
	int t4;
	int t5;

	int total = 0;

	for (int shifter1 = 1; shifter1 < paivat.size() - 4; shifter1++)
	{
		for (int shifter2 = shifter1 + 1; shifter2 < paivat.size() - 3; shifter2++)
		{
			for (int shifter3 = shifter2 + 1; shifter3 < paivat.size() - 2; shifter3++)
			{
				for (int shifter4 = shifter3 + 1; shifter4 < paivat.size() - 1; shifter4++)
				{
					eka = -1;
					toka = -1;
					kolmas = -1;
					neljas = -1;
					viides = -1;
					for (int i = 0; i < joukkoeiden_ottelut.size(); i++) //tiimit lapi
					{
						//eka
						ek = 0;
						for (int j = 0; j < shifter1; j++)
						{
							ek += joukkoeiden_ottelut[i][j];
						}
						if (ek > eka)
						{
							eka = ek;
							t1 = i;
						}
						//toka
						tk = 0;
						for (int j = shifter1; j < shifter2; j++)
						{
							tk += joukkoeiden_ottelut[i][j];
						}
						if (tk > toka)
						{
							toka = tk;
							t2 = i;
						}
						//kolmas
						kolm = 0;
						for (int j = shifter2; j < shifter3; j++)
						{
							kolm += joukkoeiden_ottelut[i][j];
						}
						if (kolm > kolmas)
						{
							kolmas = kolm;
							t3 = i;
						}
						//neljäs
						nelj = 0;
						for (int j = shifter3; j < shifter4; j++)
						{
							nelj += joukkoeiden_ottelut[i][j];
						}
						if (nelj > neljas)
						{
							neljas = nelj;
							t4 = i;
						}

						//viides
						viid = 0;
						for (int j = shifter4; j < paivat.size(); j++)
						{
							viid += joukkoeiden_ottelut[i][j];
						}
						if (viid > viides)
						{
							viides = viid;
							t5 = i;
						}
						/*
						summa = eka + toka + kolmas + neljas + viides;
						if (summa >= total)
						{
							total = summa;
							for (int j = 0; j < shifter1; j++)
							{
								filetowrite << tiimit[t1] << ";";
							}

							for (int j = shifter1; j < shifter2; j++)
							{
								filetowrite << tiimit[t2] << ";";
							}

							for (int j = shifter2; j < shifter3; j++)
							{
								filetowrite << tiimit[t3] << ";";
							}

							for (int j = shifter3; j < shifter4; j++)
							{
								filetowrite << tiimit[t4] << ";";
							}

							for (int j = shifter4; j < paivat.size(); j++)
							{
								filetowrite << tiimit[t5] << ";";
							}
							filetowrite << summa << endl;
						}*/

					}
					summa = eka + toka + kolmas + neljas + viides;
					if (summa >= total)
					{
						total = summa;
						for (int j = 0; j < shifter1; j++)
						{
							filetowrite << tiimit[t1] << ";";
						}

						for (int j = shifter1; j < shifter2; j++)
						{
							filetowrite << tiimit[t2] << ";";
						}

						for (int j = shifter2; j < shifter3; j++)
						{
							filetowrite << tiimit[t3] << ";";
						}

						for (int j = shifter3; j < shifter4; j++)
						{
							filetowrite << tiimit[t4] << ";";
						}

						for (int j = shifter4; j < paivat.size(); j++)
						{
							filetowrite << tiimit[t5] << ";";
						}
						filetowrite << summa << endl;
					}
				}
			}
		}
	}
}

void superboosted_five()
{
	ofstream filetowrite;
	filetowrite.open("5_vaihto.csv");

	int gynnther = 0;

	int eka;
	int ek;
	int toka;
	int tk;
	int kolmas;
	int kolm;
	int neljas;
	int nelj;
	int viides;
	int viid;
	int kuudes;
	int kuud;

	int summa;

	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;

	int total = 0;

	for (int shifter1 = 1; shifter1 < paivat.size() - 5; shifter1++)
	{
		for (int shifter2 = shifter1 + 1; shifter2 < paivat.size() - 4; shifter2++)
		{
			for (int shifter3 = shifter2 + 1; shifter3 < paivat.size() - 3; shifter3++)
			{
				for (int shifter4 = shifter3 + 1; shifter4 < paivat.size() - 2; shifter4++)
				{
					for (int shifter5 = shifter4 + 1; shifter5 < paivat.size() - 1; shifter5++)
					{
						eka = -1;
						toka = -1;
						kolmas = -1;
						neljas = -1;
						viides = -1;
						kuudes = -1;
						for (int i = 0; i < joukkoeiden_ottelut.size(); i++) //tiimit lapi
						{
							//eka
							ek = 0;
							for (int j = 0; j < shifter1; j++)
							{
								ek += joukkoeiden_ottelut[i][j];
							}
							if (ek > eka)
							{
								eka = ek;
								t1 = i;
							}
							//toka
							tk = 0;
							for (int j = shifter1; j < shifter2; j++)
							{
								tk += joukkoeiden_ottelut[i][j];
							}
							if (tk > toka)
							{
								toka = tk;
								t2 = i;
							}
							//kolmas
							kolm = 0;
							for (int j = shifter2; j < shifter3; j++)
							{
								kolm += joukkoeiden_ottelut[i][j];
							}
							if (kolm > kolmas)
							{
								kolmas = kolm;
								t3 = i;
							}
							//neljäs
							nelj = 0;
							for (int j = shifter3; j < shifter4; j++)
							{
								nelj += joukkoeiden_ottelut[i][j];
							}
							if (nelj > neljas)
							{
								neljas = nelj;
								t4 = i;
							}

							//viides
							viid = 0;
							for (int j = shifter4; j < shifter5; j++)
							{
								viid += joukkoeiden_ottelut[i][j];
							}
							if (viid > viides)
							{
								viides = viid;
								t5 = i;
							}

							//kuudes
							kuud = 0;
							for (int j = shifter5; j < paivat.size(); j++)
							{
								kuud += joukkoeiden_ottelut[i][j];
							}
							if (kuud > kuudes)
							{
								kuudes = kuud;
								t6 = i;
							}
							/*
							summa = eka + toka + kolmas + neljas + viides + kuudes;
							if (summa >= total)
							{
								total = summa;
								for (int j = 0; j < shifter1; j++)
								{
									filetowrite << tiimit[t1] << ";";
								}

								for (int j = shifter1; j < shifter2; j++)
								{
									filetowrite << tiimit[t2] << ";";
								}

								for (int j = shifter2; j < shifter3; j++)
								{
									filetowrite << tiimit[t3] << ";";
								}

								for (int j = shifter3; j < shifter4; j++)
								{
									filetowrite << tiimit[t4] << ";";
								}

								for (int j = shifter4; j < shifter5; j++)
								{
									filetowrite << tiimit[t5] << ";";
								}

								for (int j = shifter5; j < paivat.size(); j++)
								{
									filetowrite << tiimit[t6] << ";";
								}
								filetowrite << summa << endl;
							}*/

						}
						summa = eka + toka + kolmas + neljas + viides + kuudes;
						if (summa >= total)
						{
							total = summa;
							for (int j = 0; j < shifter1; j++)
							{
								filetowrite << tiimit[t1] << ";";
							}

							for (int j = shifter1; j < shifter2; j++)
							{
								filetowrite << tiimit[t2] << ";";
							}

							for (int j = shifter2; j < shifter3; j++)
							{
								filetowrite << tiimit[t3] << ";";
							}

							for (int j = shifter3; j < shifter4; j++)
							{
								filetowrite << tiimit[t4] << ";";
							}

							for (int j = shifter4; j < shifter5; j++)
							{
								filetowrite << tiimit[t5] << ";";
							}

							for (int j = shifter5; j < paivat.size(); j++)
							{
								filetowrite << tiimit[t6] << ";";
							}
							filetowrite << summa << endl;
						}
					}
				}
			}
		}
	}
}

void arvailu()
{
	vector<string> rivi;
	vector<string> rivilista;
	vector<vector<int>> parhaat_indexeina;
	vector<int>indexeina;

	ofstream filetowrite;
	filetowrite.open("4_vaihto_arvailu.csv");

	ofstream file2towrite;
	file2towrite.open("5_vaihto_arvailu.csv");

	ifstream in("parhaat_3_vaihtoo.csv");
	string contents((istreambuf_iterator<char>(in)),
		istreambuf_iterator<char>());

	split(rivi, contents, is_any_of("\n"));

	for (vector<string>::iterator it = rivi.begin(); it != rivi.end(); it++)
	{
		split(rivilista, *it, is_any_of(";"));
		for (vector<string>::iterator itr = rivilista.begin(); itr != rivilista.end(); itr++)
		{
			for (int i = 0; i < tiimit.size(); i++)
			{
				if (tiimit[i] == *itr)
				{
					indexeina.push_back(i);
					break;
				}
			}
		}
		if (indexeina.size() == paivat.size())
		{
			parhaat_indexeina.push_back(indexeina);
		}
		indexeina.clear();
	}
	//combot
	int combot_kayty = 0;
	int edellinen_paras4 = 0;
	int edellinen_paras5 = 0;
	int OM4;
	int OM5;
	int vaihtomaara;
	int tindex = 99;

	for (vector<vector<int>>::iterator it = parhaat_indexeina.begin(); it != parhaat_indexeina.end(); it++)
	{
		for (int team = 0; team < tiimit.size(); team++)
		{
			for (int juna_len = 1; juna_len < paivat.size(); juna_len++)
			{
				for (int juna_start = 0; juna_start < (paivat.size() - juna_len); juna_start++)
				{
					indexeina = *it;
					vaihtomaara = 0;
					tindex = 99;
					for (int maali_kohde = juna_start; maali_kohde < (juna_start + juna_len); maali_kohde++)
					{
						indexeina[maali_kohde] = team;
					}

					combot_kayty++;

					for (vector<int>::iterator itr = indexeina.begin(); itr != indexeina.end(); itr++)
					{
						if (*itr != tindex && tindex != 99)
							vaihtomaara++;
						tindex = *itr;
					}

					if (vaihtomaara == 4)
					{
						OM4 = ottelumaara(indexeina);
						if (OM4 >= edellinen_paras4)
						{
							edellinen_paras4 = OM4;
							for (vector<int>::iterator itr = indexeina.begin(); itr != indexeina.end(); itr++)
							{

								filetowrite << tiimit[*itr] << ";";

							}
							filetowrite << OM4 << endl;
						}
					}
					if (vaihtomaara == 5)
					{
						OM5 = ottelumaara(indexeina);
						if (OM5 >= edellinen_paras5)
						{
							edellinen_paras5 = OM5;
							for (vector<int>::iterator itr = indexeina.begin(); itr != indexeina.end(); itr++)
							{

								file2towrite << tiimit[*itr] << ";";

							}
							file2towrite << OM5 << endl;
						}
					}
				}
			}
		}
	}
	cout << combot_kayty << " comboo tsekattu" << endl;
	cout << "created 4_vaihto_arvailu.csv && 5_vaihto_arvailu.csv" << endl;
}

int main()
{
	csvCreator();
	OPlistaConverter();
	jottelut_create();
	cout << paivat.size() << " ottelupaivaa" << endl;
	cout << "enter to continue" << endl;
	cin.get();
	int laskenta;

	while (true)
	{

		cout << "valitse laskenta:" << endl;
		cout << "1.parhaat 1 , 2 ja 3 vaihtoo" << endl;
		cout << "2.parhaat 4 vaihtoo" << endl;
		cout << "3.parhaat 5 vaihtoo" << endl;
		cout << "4.quit" << endl;

		cin >> laskenta;


		if (laskenta == 1)
		{

			auto start = chrono::steady_clock::now();//ajanotto alkaa

			one_vaihto();
			superboosted_two();
			superboosted_tre();


			//ajanotto paattyy================================================
			chrono::steady_clock::time_point end = chrono::steady_clock::now();
			std::cout << "Time: "
				<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
				<< " ms" << endl;
			//================================================================
			cout << "created 1_vaihto.csv, 2_vaihto.csv, 3_vaihto.csv" << endl;
			cout << "ender do gondinue" << endl;
			cin.get();
			cin.get();
		}
		if (laskenta == 2)
		{
			auto start = chrono::steady_clock::now();//ajanotto alkaa


			superboosted_four();


			//ajanotto paattyy================================================
			chrono::steady_clock::time_point end = chrono::steady_clock::now();
			std::cout << "Time: "
				<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
				<< " ms" << endl;
			//================================================================
			cout << "created 4_vaihto.csv" << endl;
			cout << "ender do gondinue" << endl;
			cin.get();
			cin.get();
		}
		if (laskenta == 3)
		{
			auto start = chrono::steady_clock::now();//ajanotto alkaa


			superboosted_five();


			//ajanotto paattyy================================================
			chrono::steady_clock::time_point end = chrono::steady_clock::now();
			std::cout << "Time: "
				<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
				<< " ms" << endl;
			//================================================================
			cout << "created 5_vaihto.csv" << endl;
			cout << "ender do gondinue" << endl;
			cin.get();
			cin.get();
		}
		if (laskenta == 4)
		{
			break;
		}
	}
}

