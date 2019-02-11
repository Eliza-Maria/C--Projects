#pragma once
using namespace std;

#ifndef PRODUS_H
#define PRODUS_H

enum unitate{bucata,greutate,volum};
enum Soi{ CabernetSavignon, Merlot, SavignonBlanc, Chardonnay };

class Produs {
protected:
	float pret;
	unitate u;
	string denumire;
	float cantitate;
	
	
public:
	//citiri si afisari
	virtual void citire();
	virtual void afisare();

	virtual void citire_client() {};

	string get_denumire() {
		return denumire;
	}
	float get_pret() {
		return pret;
	}
	float get_cantitate() {
		return cantitate;
	}

	void set_pret(float _pret) {
		pret = _pret;
	}
	void set_cantitate(float _cantitate){
		cantitate = _cantitate;

	}

	void scade_cantitate(float _cantitate) {
		cantitate -= _cantitate;
	}
};

void Produs::citire() {
	cout << "Cantitatea produsului este: ";
	cin >> cantitate;
	cout << "Pretul produsului este: ";
	cin >> pret;
}

void Produs::afisare() {
	cout << "Pretul: " << pret<<endl;
}


class Varza :public Produs {
public:
	Varza() {
		u = bucata;
		denumire = "varza";
	}
	void citire() {
		Produs::citire();
	}
	void afisare() {
		Produs::afisare();
	}

	void citire_client(){}

	bool operator==(const Varza& ob) {
		return true;
	}
};

class Faina :public Produs {
	int calitate;
public:
	Faina() {
		u = greutate;
		denumire = "faina";
	}
	void citire() {
		cout << "Calitatea este(1,2 sau 3) ";
		cin >> calitate;
		Produs::citire();
	}
	void afisare() {
		cout << "Calitatea " << calitate << endl;
		Produs::afisare();
	}
	void citire_client() {
		cout << "De ce calitate sa fie faina(1,2 sau 3)?";
		cin >> calitate;
	}

	bool operator==(const Faina& ob) {
		return calitate == ob.calitate;
	}
};

class Bere :public Produs {
	string brand;
	string tip;
public:
	Bere() {
		u = bucata;
		denumire = "bere";
	}
	Bere(string _brand,string _tip) {
		brand = _brand;
		tip = _tip;
	}

	string get_brand() {
		return brand;
	}
	string get_tip() {
		return tip;
	}
	void citire() {
		cout << "Brand-ul este(Timisoreana,Ciucas,Ursus): ";
		cin >> brand;
		cout << "Tipul este(blonda/bruna) ";
		cin >> tip;
		Produs::citire();
	}
	void afisare() {
		cout << "Brandul: " << brand << endl << "Tipul: " << tip;
		Produs::afisare();
	}
	void citire_client() {
		cout << "Ce brand si ce tip sa aiba berea pe care doriti sa o cumparati?";
		cin >> brand >> tip;
	}

	bool operator==(const Bere& ob) {
		return (brand == ob.brand&&tip == ob.tip);
	}
};

class Cartofi :public Produs {
	string culoare;
public:
	Cartofi() {
		u = greutate;
		denumire = "cartofi";
	}
	void citire() {
		cout << "Culoarea este(rosu sau alb): ";
		cin >> culoare;
		Produs::citire();
	}
	void afisare() {
		cout << "Culoarea: " << culoare << endl;
		Produs::afisare();
	}
	void citire_client() {
		cout << "Ce fel de cartofi doriti sa cumparati?(rosii/albi)";
		cin >> culoare;
	}

	bool operator==(const Cartofi& ob) {
		return culoare == ob.culoare;
	}
};

class Jucarie :public Produs {
	string nume;
public:
	Jucarie() {
		u = bucata;
		denumire = "jucarie";
	}
	Jucarie(string _nume) {
		nume = _nume;
	}
	string get_nume() {
		return nume;
	}
	void citire() {
		cout << "Numele jucariei este: ";
		cin >> nume;
		Produs::citire();
	}
	void afisare() {
		cout << "Jucaria este " << nume << endl;
		Produs::afisare();
	}
	void citire_client(){
		cout << "Ce jucarie doriti sa cumparati?";
		cin >> nume;
	}

	bool operator==(const Jucarie& ob) {
		return nume == ob.nume;
	}
};

class Vin :public Produs {
protected:
	string culoare;
	string tip;
public:
	
	virtual void citire() {
		cout << "Culoarea vinului este(rosu/alb): ";
		cin >> culoare; 
		cout << "Tipul vinului este(sec/dulce/demi-sec/demi-dulce): ";
		cin >> tip;
		Produs::citire();
	}
	virtual void afisare() {
		cout << "Culoarea vinului este: " << culoare;
		cout << "Tipul vinului este: " << tip;
		Produs::afisare();
	}
	virtual void citire_client(){}

	friend istream& operator>>(istream&, Vin&);
	friend ostream& operator<<(ostream&, Vin&);
};

istream& operator>>(istream& in, Vin& v) {
	in >> v.pret >> v.culoare >> v.tip;
	return in;
}
ostream& operator<<(ostream& out, Vin& v) {
	out<< v.pret <<" "<< v.culoare << " " << v.tip;
	return out;
}

class Vin_Varsat :public Vin {
public:
	Vin_Varsat() {
		u = volum;
		tip = "sec";
		denumire = "vin varsat";
	}
	void citire() {
		Vin::citire();
	}
	void afisare() {
		Vin::afisare();
	}
	void citire_client() {
		cout << "Ce culoare(rosu/alb) si ce tip(dulce/sec/demi-dulce/demi-sec) de vin doriti sa cumparati?";
		cin >> culoare >> tip;
	}

	bool operator==(const Vin_Varsat& ob) {
		return (culoare == ob.culoare&&tip == ob.tip);
	}
};

class Vin_de_Soi:public Vin {
	Soi s;
	int an;
	string tara;
public:
	
	Vin_de_Soi() {
		u = bucata;
		denumire = "vin de soi";
	}
	Vin_de_Soi(int _an, string _tara) {
		an = _an;
		tara = _tara;
	}
	Soi get_soi() {
		return s;
	}
	int get_an() {
		return an;
	}
	string get_tara() {
		return tara;
	}
	void pregatire_stoc() {
		switch (s) {
		case 0:
		{
			culoare = "rosu";
			tip = "sec";
			break;
		}
		case 1:
		{
			culoare = "rosu";
			tip = "dulce";
			break;
		}
		case 2:
		{
			culoare = "alb";
			tip = "dulce";
			break;
		}
		case 3:
		{
			culoare = "alb";
			tip = "dulce";
			break;
		}
		}
	}
	void citeste_soiul() {
		cout << "Soiul vinului este(Cabernet Savignon(0), Merlot(1),Savignon Blanc(2),Chardonnay(3)): ";
		int soi;
		do {
			cin >> soi; 
			try {
				if (soi < 0 || soi > 3)
					throw runtime_error("Nu ati introdus o optiune valida :(");
			}
			catch (runtime_error &e) {
				cout << e.what() << endl;
			}
		} while (soi < 0 || soi > 3);
		switch (soi) {
		case 0:
		{
			s = CabernetSavignon;
			break;
		}
		case 1:
		{
			s = Merlot;
			break;
		}
		case 2:
		{

			s = SavignonBlanc;
			break;
		}
		case 3:
		{
			s = Chardonnay;
			break;
		}
		}

		pregatire_stoc();
	}
	void afiseaza_soiul() {
		cout << "Soiul vinului este ";
		switch (s) {
		case 0:
		{
			cout << "Cabernet Savignon" << endl;
			break;
		}
		case 1:
		{
			cout << "Merlot" << endl;
			break;
		}
		case 2:
		{
			cout << "Savignon Blanc" << endl;
			break;
		}
		case 3:
		{
			cout << "Chardonnay" << endl;
			break;
		}
		}
	}

	void citire() {
		
		citeste_soiul();
		cout << "Tara de provenienta este(Franta, Argentina, Chille, Australia): ";
		cin >> tara;
		cout << "Anul culegerii este: ";
		cin >> an;
		Produs::citire();

	}
	void afisare() {
		afiseaza_soiul();
		cout << "Tara de provenienta este: ";
		cout << tara;
		cout << "Anul culegerii este: ";
		cout << an;
		Produs::afisare();

	}
	void citire_client() {
		cout << "Din ce an si din ce tara este vinul pe care doriti sa il cumparati?";
		cin >> an >> tara;
		citeste_soiul();
	}

	bool operator==(const Vin_de_Soi& ob) {
		return (tara == ob.tara&&an == ob.an&&s == ob.s);
	}

};



#endif


