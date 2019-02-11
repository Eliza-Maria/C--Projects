#pragma once
#include <iostream>

using namespace std;
#ifndef COLET_H
#define COLET_H

//FA CATE O CLASA PT DEADLINE,INTERVAL,CAT_MAI_REPEDE CARE SA MOSTENEASCA COLET , AICI O SA FOLOSESTI VIRTUAL


class colet {
protected:
	float masa;
	float volum;
	bool reci;

	coordonate client;
	coordonate destinatie;

	bool primit;

	int prioritate_timp;
	int index;



public:
	
	friend class dispecerat; //clasa dispecerat ii va putea accesa variabilele private
	friend class vehicul;

	//constructori
	colet() { primit = false; }

	colet(float _masa, float _volum, bool _reci) {
		masa = _masa;
		volum = _volum;
		reci = _reci;

		primit = false;
	}

	colet(float _masa, float _volum, bool _reci, coordonate _client, coordonate _destinatie) {
		masa = _masa;
		volum = _volum;
		reci = _reci;
		client.x = _client.x;
		client.y = _client.y;
		destinatie.x = _destinatie.x;
		destinatie.y = _destinatie.y;

		primit = false;
	}

	//seteri
	void set_coord(coordonate _client, coordonate _destinatie)
	{
		client.x = _client.x;
		client.y = _client.y;
		destinatie.x = _destinatie.x;
		destinatie.y = _destinatie.y;

	}
	void set_coord2(int xc, int yc, int xd, int yd)
	{
		client.x = xc;
		client.y = yc;
		destinatie.x = xd;
		destinatie.y = yd;

	}
	void set_coord_client(int xc, int yc) {
		client.x = xc;
		client.y = yc;
	}
	void set_coord_destinatie(int xd, int yd) {
		destinatie.x = xd;
		destinatie.y = yd;
	}
	void set_primit(bool _primit) {
		primit = _primit;
	}
	void set_index(int _index) {
		index = _index;
	}

	//geteri
	int get_index() {
		return index;
	}
	bool get_primit() {
		return primit;
	}
	float get_masa() {
		return masa;
	}
	float get_volum() {
		return volum;
	}
	coordonate get_coord_client()
	{
		return client;
	}
	coordonate get_coord_destinatie()
	{
		return destinatie;
	}

	//citiri si afisari
	virtual void print() {
		cout << "Masa: " << masa << endl << "Volum: " << volum << endl << "Reci: " << reci << endl << "Coordonate client: " << client.x << " " << client.y << endl << "Coordonate destinatie: " << destinatie.x << " " << destinatie.y << endl;
		if (primit == false)
			cout << "Coletul nu a putut fi livrat." << endl;
		else
			cout << "Coletul a fost livrat." << endl;
	}
	virtual void citire() {
		cout << "Masa: ";
		cin >> masa;
		cout << "Volum: ";
		cin >> volum;
		cout << "Reci: ";
		cin >> reci;
		cout << "Coordonate client(x si y): ";
		cin >> client.x >> client.y;
		cout << "Coordonate destinatie(x si y): ";
		cin >> destinatie.x >> destinatie.y;
	}

	//functii de logica
	virtual bool ajunge_la_timp(vehicul *veh) {
		return 0;
	}
	virtual int calculeaza_prioritate_timp() {
		return 0;
	}

	int calculeaza_minute(moment m1, moment m2) {

		int minute = 0;
		minute = (m2.ora * 60 + m2.minut) - (m1.ora * 60 + m1.minut);
		return minute;
	}
	
	moment cand_ajunge(vehicul *veh) {
		float timp = 0;
		moment aux;
		timp = ((veh->calculeaza_distanta(veh->get_coord(), this->client) + veh->calculeaza_distanta(this->client, this->destinatie)) / veh->get_viteza()) * 60;
		aux.ora = (int)(timp / 60);
		aux.minut = (int)(timp - aux.ora * 60);
		return aux;
	}


	//supraincarcare de operatori
	friend istream& operator>>(istream& in, colet &);
	friend ostream& operator<<(ostream&, colet &);
	colet operator=(const colet &arg);

};

istream& operator>>(istream& in, colet &c)
{
	in >> c.masa >> c.volum >> c.reci >> c.client.x >> c.client.y >> c.destinatie.x >> c.destinatie.y;
	return in;
}

ostream& operator<<(ostream& out, colet &c)
{
	out << c.masa << c.volum << c.reci << c.client.x << c.client.y << c.destinatie.x << c.destinatie.y;
	return out;
}

colet colet::operator=(const colet &arg)
{
	if (&arg != this)
	{
		masa= arg.masa;
		primit= arg.primit;
		prioritate_timp = arg.prioritate_timp;
		volum = arg.volum;
		reci = arg.reci;
		client = arg.client;
		destinatie = arg.destinatie;

	}
	
		return *this;
}


class deadline:public colet {
	moment deadline;
public:
	
	//seteri
	void set_deadline(moment _deadline) {
		deadline = _deadline;
	}
	void set_deadline2(int o, int min) {
		deadline.ora = o;
		deadline.minut = min;
	}

	//geteri
	moment get_deadline() {
		return deadline;
	}
	
	//citiri si afisari
	void print() {
		colet::print();
		cout << "ora: " << deadline.ora << ":" << deadline.minut;
	}
	void citire() {
		colet::citire();
		cout << "Deadline-ul este(ora+minute): ";
		cin >> deadline.ora >> deadline.minut;
	}
	
	//functii de logica
	int calculeaza_prioritate_timp() {
		prioritate_timp = 0;
		moment aux;
		aux.ora = 0;
		aux.minut = 0;
		prioritate_timp = calculeaza_minute(aux, deadline);
		return prioritate_timp;
	}
	bool ajunge_la_timp(vehicul *veh) {
		float timp = 0;

		timp += calculeaza_minute(veh->get_moment(), this->deadline);

		if (timp <= 0)
			return false;

		timp -= ((veh->calculeaza_distanta(veh->get_coord(), this->client) + veh->calculeaza_distanta(this->client, this->destinatie)) / veh->get_viteza()) * 60;
		//timp in minute (km/(km/h)*60)
		if (timp >= 0)
			return true;
		else
			return false;
	}
};

class interval :public colet {
	perioada p;
public:
	
	//seteri
	void set_perioada(perioada _p) {
		p = _p;
	}
	void set_perioada2(int o1, int min1, int o2, int min2) {
		p.inceput.ora = o1;
		p.inceput.minut = min1;
		p.sfarsit.ora = o2;
		p.sfarsit.minut = min2;

	}
	
	//geteri
	perioada get_interval() {
		return p;
	}
	
	//citiri si afisari
	void print() {
		colet::print();
		cout << "Intervalul: \n Ora inceput: " << p.inceput.ora << ":" << p.inceput.minut<<" \n Ora final: " << p.sfarsit.ora << ":" << p.sfarsit.minut;
	}
	void citire() {
		colet::citire();
		cout << "Intervalul este(ora+minute inceput ora+minute sfarsit): ";
		cin >> p.inceput.ora >> p.inceput.minut>>p.sfarsit.ora>>p.sfarsit.minut;
	}

	//functii de logica
	bool ajunge_la_timp(vehicul *veh) {
		float timp = 0;
		moment aux;
		timp = ((veh->calculeaza_distanta(veh->get_coord(), this->client) + veh->calculeaza_distanta(this->client, this->destinatie)) / veh->get_viteza()) * 60;
		//calculam timpul in minute in care ajunge coletul la destinatie

		if (timp <= 0)
			return false;

		aux.ora = (int)(timp / 60);
		aux.minut = (int)(timp - aux.ora * 60);
		//translatam in formatul ora,minut, pt a verifica daca se afla in interval
		if ((aux.ora > this->p.inceput.ora&&aux.minut > this->p.inceput.minut) && (aux.ora < this->p.sfarsit.ora&&aux.minut < this->p.sfarsit.minut))
			return true;
		else
			return false;
	}
	int calculeaza_prioritate_timp() {
		prioritate_timp = 0; 
		moment aux;
		aux.ora = 0;
		aux.minut = 0;
		prioritate_timp = calculeaza_minute(aux, p.inceput) + calculeaza_minute(p.inceput, p.sfarsit);
		return prioritate_timp;
	}
};

class cat_mai_repede :public colet {
	bool fara_limita;
public:
	cat_mai_repede() { fara_limita = true; }

	//citiri si afisari
	void print() {
		colet::print();
		cout << "Acest colet nu are limita de timp";
	}
	void citire() {
		colet::citire();
		cout << "Acest colet nu are limita de timp";
	}

	//functii de logica
	bool ajunge_la_timp(vehicul *veh)
	{
		return true;
	}
	int calculeaza_prioritate_timp() {
		prioritate_timp = INT_MAX;
		return prioritate_timp;
	}
};



#endif // !COLET_H

