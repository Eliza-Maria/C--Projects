#pragma once
#include <iostream>
using namespace std;
#ifndef VEHICUL_H
#define VEHICUL_H

enum tip { linie_dreapta, manhattan };
enum strategie_sofer { urgent, apropiat, first_come_first_served };


class vehicul {
protected:
	coordonate pozitie;
	float masa;
	float volum;

	float masa_ramasa;
	float volum_ramas;

	strategie_sofer ss; //in functie de strategie, se va apela functia corespunzatoare
	moment m; //fiecare vehicul are timer-ul propriu

	int viteza; 
	bool frigorifica;

public:


	friend class dispecerat; 
	
	//constructori
	vehicul() {
		m.ora = 0;
		m.minut = 0;
		pozitie.x = 0;
		pozitie.y = 0; //initial, coordonatele sunt coordonatele dispeceratului i.e. (0,0)
	}
	vehicul(coordonate _pozitie, float _masa, float _volum, strategie_sofer _ss) {
		pozitie.x = _pozitie.x;
		pozitie.y = _pozitie.y;
		masa = _masa;
		volum = _volum;
		ss = _ss;
		m.ora = 0;
		m.minut = 0;
		pozitie.x = 0;
		pozitie.y = 0; //initial, coordonatele sunt coordonatele dispeceratului i.e. (0,0)

		masa_ramasa = masa;
		volum_ramas = volum;
	}
	vehicul(const vehicul &ob) {
		masa = ob.masa;
		volum = ob.volum;
		ss = ob.ss;
		m.ora = ob.m.ora;
		m.minut = ob.m.minut;
		viteza = ob.viteza;
		frigorifica = ob.frigorifica;

		masa_ramasa = masa;
		volum_ramas = volum;

	}

	//seteri
	void set_ss(strategie_sofer _ss) {
		ss = _ss;
	}
	void set_coord(coordonate _pozitie)
	{
		pozitie.x = _pozitie.x;
		pozitie.y = _pozitie.y;
	}
	void set_masa(float _masa) {
		masa = _masa;
		masa_ramasa = masa;
	}
	void set_volum(float _volum) {
		volum = _volum;
		volum_ramas = volum;
	}
	void set_moment(moment _m) {
		m = _m;
	}
	void set_masa_ramasa(float _masa_ramasa) {
		masa_ramasa = _masa_ramasa;
	}
	void set_volum_ramas(float _volum_ramas) {
		volum_ramas = _volum_ramas;
	}


	//geteri
	
	coordonate get_coord() {
		return pozitie;
	}
	float get_masa() {
		return masa;
	}
	float get_volum() {
		return volum;
	}
	int get_viteza() {
		return viteza;
	}
	bool get_frigorifica() {
		return frigorifica;
	}
	moment get_moment() {
		return m;
	}
	float get_masa_ramasa() {
		return masa_ramasa;

	}
	float get_volum_ramas() {
		return volum_ramas;
	}
	
	//afisari si citiri

	void print_ss() {
		switch (ss)
		{
		case 0:
			cout << "urgent";
			break;
		case 1:
			cout << "apropiat";
			break;
		case 2:
			cout << "first_come_first_served";
			break;
		default:
			break;
		}
	}
	void afisare_moment() {
		cout << m.ora << " " << m.minut;
	}
	void citire() {
		cout << "Masa vehiculului:";
		cin >> masa;
		cout << "Volumul vehiculului:";
		cin >> volum;
		cout << "Coordonatele vehiculului(x si y):";
		cin >> pozitie.x >> pozitie.y;
		masa_ramasa = masa;
		volum_ramas = volum;

	}
	void afisare() {
		cout << "Masa vehiculului:" << masa<<endl;
		cout << "Volumul vehiculului:" << volum<<endl;
		cout << "Coordonatele vehiculului(x si y):" << pozitie.x << " " << pozitie.y << endl;
		cout << "Masa ramasa a vehiculului:" << masa_ramasa << endl;
		cout << "Volumul ramas al vehiculului:" << volum_ramas << endl;
	}

	//functii de logica

	virtual float calculeaza_distanta(coordonate c1, coordonate c2) {
		return 0;
	}
};

class masina :public vehicul {

	const tip t = manhattan;

public:

	masina() { viteza = 10; frigorifica = false; }

	float calculeaza_distanta(coordonate c1, coordonate c2) {
		float distanta = 0;
		distanta = abs(c2.x - c1.x) + abs(c2.y - c1.y);
		return distanta;
	}
	
};

class scuter :public vehicul {

	const tip t = linie_dreapta;

public:
	scuter() { viteza = 20; frigorifica = false; }

	float calculeaza_distanta(coordonate c1, coordonate c2) {
		float distanta = 0;
		distanta = (float)(sqrt((c2.x - c1.x)*(c2.x - c1.x) + (c2.y - c1.y)*c2.y - c1.y));
		return distanta;
	}

};

class duba :public vehicul {
	
	const tip t = manhattan;

public:
	duba() { viteza = 5; frigorifica = true; }
	
	float calculeaza_distanta(coordonate c1, coordonate c2) {
		float distanta = 0;
		distanta = abs(c2.x - c1.x) + abs(c2.y - c1.y);
		return distanta;
	}
};

#endif // !VEHICUL.H
