#pragma once
#ifndef STOC_H
#define STOC_H

class Stoc {

	static Stoc* instanta;

	vector<Varza> cantitate_varza; //la kg
	vector<Faina> cantitate_faina; //la kg
	vector<Cartofi> cantitate_cartofi; //la kg
	vector<Vin_Varsat> cantitate_vin_varsat; //la volum

	vector<Bere>cantitate_bere;//la bucata 
	vector<Jucarie>cantitate_jucarii;//la bucata
	vector<Vin_de_Soi>cantitate_vin_de_soi;//la bucata(sticla)

	Stoc() {}
	Stoc& operator=(Stoc& ob) {}
	Stoc(const Stoc& ob) {}

public:
	friend class Magazin;

	static Stoc* get_instanta() {
		if (instanta == 0)
			instanta = new Stoc();
		return instanta;
	}

	template<class T>
	void adauga_produs(vector<T> &arg) {
		int t;
		T ob;
		cout << "Cate tipuri de "<<ob.get_denumire()<<" incarcati?";
		cin >> t;
		for (int i = 0; i < t; i++)
		{
			ob.citire();
			arg.push_back(ob);
		}

	}


	template<class T>
	void vinde_produs(vector<T> &arg) {
		T ob;
		int t;
		float n;
		bool exista = false;
		cout << "Cate tipuri de " << ob.get_denumire() << " doriti sa cumparati?";
		cin >> t;
		for (int j = 0; j < t; j++) {
			exista = false;
			ob.citire_client();
			cout << "Cate produse de acest tip doriti?";
			cin >> n;
			for (int i = 0; i < arg.size(); i++)
				if (arg.at(i) == ob)
				{
					if (n > arg.at(i).get_cantitate())
						cout << "Ne pare rau, nu avem suficient!";
					else
					{
						Magazin::adauga_profit(arg.at(i).get_pret()*n);
						arg.at(i).scade_cantitate(n);
						exista = true;
						break;
					}

				}
			if (exista == false)
				cout << "Ne cerem scuze, nu avem acest tip de produs!";

		}
	}

	template<class T>
	void afisare_produs(vector<T> arg) {
		for (int i = 0; i < arg.size(); i++)
		{
			arg.at(i).afisare();
			cout << "Cantitate: " << arg.at(i).get_cantitate() << endl;
		}
	}
};

Stoc* Stoc::instanta = NULL;

//clasa singleton

#endif // !CANTITATE_H

