#pragma once
#ifndef MAGAZIN_H
#define MAGAZIN_H

class Magazin {
	Produs **p; //aici vor fi stocate tipurile de produse, nu cantitatea
	int nr;
	Stoc *stoc;

	int clienti;

	static float profit;

public:
	
	Magazin() {
		stoc = Stoc::get_instanta();
	}

	void set_clienti(int _clienti) {
		clienti = _clienti;
	}
	
	static void adauga_profit(float _profit) {
		profit += _profit;
	}
	static void afiseaza_profit() {
		cout << "Profitul este: " << profit << endl;
	}

	void citire_produse() {
		
		cout << "Cate tipuri de produse incarcati?(maxim 7)"<<endl;
		cin >> nr;
		p = new Produs*[nr];

		int optiune;
		for (int i = 0; i < nr; i++)
		{
			cout << "Ce produs incarcati?" << endl << "niciunul=0; varza=1; faina=2; bere=3; cartofi=4; jucarie=5; vin varsat=6; vin de soi=7"<<endl;
			do {
				cin >> optiune;
				try {
					if (optiune < 0 || optiune>7)
						throw runtime_error("Nu ati introdus o optiune valida :(");
				}
				catch (runtime_error &e) {
					cout << e.what() << endl;
				}
			} while (optiune < 0 || optiune>7);

			switch (optiune)
			{
			case 0:
			{
				break;
			}
			case 1:
				{
					p[i] = new Varza();
					stoc->adauga_produs<Varza>(stoc->cantitate_varza);
					break;
				}
			case 2:
				{
					p[i] = new Faina();
					stoc->adauga_produs<Faina>(stoc->cantitate_faina);
					break;
				}
			case 3:
				{
					p[i] = new Bere();
					stoc->adauga_produs<Bere>(stoc->cantitate_bere);
					break;
				}
			case 4:
				{
					p[i] = new Cartofi();
					stoc->adauga_produs<Cartofi>(stoc->cantitate_cartofi);
					break;
				}
			case 5:
				{
					p[i] = new Jucarie();
					stoc->adauga_produs<Jucarie>(stoc->cantitate_jucarii);
					break;
				}
			case 6:
				{
					p[i] = new Vin_Varsat();
					stoc->adauga_produs<Vin_Varsat>(stoc->cantitate_vin_varsat);
					break;
				}
			case 7:
				{
					p[i] = new Vin_de_Soi();
					stoc->adauga_produs<Vin_de_Soi>(stoc->cantitate_vin_de_soi);
				}

			default:
				break;
			}
			
		}
	
	}

	void afisare_produse() {
		
		for (int i = 0; i < nr; i++) {
			cout << "Produs: " << p[i]->get_denumire() << endl;
		}
	}


	void serveste_clienti() {
		int optiune;
		for (int i = 0; i < clienti; i++) {

			cout << "Clientul numarul " << i + 1 << endl;
			cout << "Ce produs cumparati?" << endl << "niciunul=0; varza=1; faina=2; bere=3; cartofi=4; jucarie=5; vin varsat=6; vin de soi=7" << endl;
			do {
				cin >> optiune;
				try {
					if (optiune < 0 || optiune>7)
						throw runtime_error("Nu ati introdus o optiune valida :(");
				}
				catch (runtime_error &e) {
					cout << e.what() << endl;
				}
			} while (optiune < 0 || optiune>7);

			switch (optiune)
			{
			case 0:
			{
				break;
			}
			case 1:
			{
				p[i] = new Varza();
				stoc->vinde_produs<Varza>(stoc->cantitate_varza);
				break;
			}
			case 2:
			{
				p[i] = new Faina();
				stoc->vinde_produs<Faina>(stoc->cantitate_faina);
				break;
			}
			case 3:
			{
				p[i] = new Bere();
				stoc->vinde_produs<Bere>(stoc->cantitate_bere);
				break;
			}
			case 4:
			{
				p[i] = new Cartofi();
				stoc->vinde_produs<Cartofi>(stoc->cantitate_cartofi);
				break;
			}
			case 5:
			{
				p[i] = new Jucarie();
				stoc->vinde_produs<Jucarie>(stoc->cantitate_jucarii);
				break;
			}
			case 6:
			{
				p[i] = new Vin_Varsat();
				stoc->vinde_produs<Vin_Varsat>(stoc->cantitate_vin_varsat);
				break;
			}
			case 7:
			{
				p[i] = new Vin_de_Soi();
				stoc->vinde_produs<Vin_de_Soi>(stoc->cantitate_vin_de_soi);
			}

			default:
				break;
			}

		}
	}

	void afisare_stoc() {
		for (int i = 0; i < nr; i++) {
			if (p[i]->get_denumire() == "varza")
			{
				cout << "Varza: " << endl;
				stoc->afisare_produs<Varza>(stoc->cantitate_varza);
			}

			if (p[i]->get_denumire() == "faina")
			{
				cout << "Faina: " << endl;
				stoc->afisare_produs<Faina>(stoc->cantitate_faina);
			}

			if (p[i]->get_denumire() == "cartofi")
			{
				cout << "Cartofi: " << endl;
				stoc->afisare_produs<Cartofi>(stoc->cantitate_cartofi);
			}

			if (p[i]->get_denumire() == "bere")
			{
				cout << "Bere: " << endl;
				stoc->afisare_produs<Bere>(stoc->cantitate_bere);
			}

			if (p[i]->get_denumire() == "jucarie")
			{
				cout << "Jucarii: " << endl;
				stoc->afisare_produs<Jucarie>(stoc->cantitate_jucarii);
			}

			if (p[i]->get_denumire() == "vin varsat")
			{
				cout << "Vin varsat: " << endl;
				stoc->afisare_produs<Vin_Varsat>(stoc->cantitate_vin_varsat);
			}

			if (p[i]->get_denumire() == "vin de soi")
			{
				cout << "Vin de soi: " << endl;
				stoc->afisare_produs<Vin_de_Soi>(stoc->cantitate_vin_de_soi);
			}
		}
	}

};

float Magazin::profit = 0;


#endif