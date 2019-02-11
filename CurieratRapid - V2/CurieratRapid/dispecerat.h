#pragma once
#include<algorithm>
#ifndef DISPECERAT_H
#define DISPECERAT_H

enum strategie { aproape, rapid, liber };
using namespace std;

int comp_timp(colet *pp, colet *qq) {
	return (pp->calculeaza_prioritate_timp() < qq->calculeaza_prioritate_timp());
}//functia de comparare pt sortarea prioritatilor la colete

class dispecerat {
	colet **c;
	int n;

	strategie st;

	vehicul **v;
	int nrv, nrm, nrd, nrs;

public:

	//constructori
	dispecerat() {}
	dispecerat(int _nrm, int _nrd, int _nrs) {
		nrm = _nrm;
		nrd = _nrd;
		nrs = _nrs;
		nrv = nrm + nrd + nrs;
		v = new vehicul*[nrv];

		for (int i = 0; i < nrm; i++)
		{
			cout << "Masina nr. " << i + 1 << ": ";
			v[i]->citire();
		}
		for (int i = nrm; i < nrd; i++)
		{
			cout << "Duba nr. " << i + 1 << ": ";
			v[i]->citire();
		}
		for (int i = nrd; i < nrs; i++)
		{
			cout << "Scuterul nr. " << i + 1 << ": ";
			v[i]->citire();
		}


	}

	//citiri si afisari
	void citire_comenzi();
	void afisare_comenzi();

	void citire_vehicule();
	void afisare_vehicule();
	
	void afisare_status_comenzi();

	void set_strategie(strategie _st);
	void print_strategie();

	//functii de logica
	bool verifica_frigorifica(colet *, vehicul *);
	bool verifica_spatiu(colet *, vehicul *);

	vehicul* calculeaza_minim_timp(colet *);
	vehicul* calculeaza_minim_distanta(colet *);
	vehicul* calculeaza_maxim_spatiu(colet *col);

	void distribuie_comenzi_rapid();
	void distribuie_comenzi_aproape();
	void distribuie_comenzi_liber();

	//o functie pe care am facut-o pana mi-am dat seama de ce nu merge sort.

	void bubblesort() {
		int ok;
		colet *aux;
		do {
			ok = 1;
			for (int i = 0; i < n - 1; i++)
				if (c[i]->calculeaza_prioritate_timp() > c[i + 1]->calculeaza_prioritate_timp())
				{
					aux = c[i];
					c[i] = c[i + 1];
					c[i + 1] = aux;
					ok = 0;
				}
		} while (ok == 0);
	}

	~dispecerat() {
		delete[] v;
		delete[] c;

	}
};


void dispecerat::citire_comenzi() {
	cout << "Dati numarul de comenzi:";
	cin >> n;
	c = new colet*[n];
	for (int i = 0; i < n; i++)
	{
		int specificatie;
		cout << "Ce specificatii are coletul "<<i+1<<"? Pentru deadline, apasati 0, pentru interval 1, pentru cat mai repede 2: \n";
		cin >> specificatie;
		switch (specificatie)
		{
		case 0:
			c[i] = new deadline();
			break;
		case 1:
			c[i] = new interval();
			break;
		case 2:
			c[i] = new cat_mai_repede();
			break;
		default:
			break;
		}
		c[i]->citire();
		c[i]->set_index(i);
	}
}

void dispecerat::afisare_comenzi() {
	for (int i = 0; i < n; i++)
		c[i]->print();
}

void dispecerat::citire_vehicule() {

	cout << "Dati nr. de masini:";
	cin >> nrm;
	cout << "Dati nr. de dube:";
	cin >> nrd;
	cout << "Dati nr. de scutere:";
	cin >> nrs;

	nrv = nrm + nrd + nrs;
	v = new vehicul*[nrv];


	int index = 0;
	for (int i = 0; i < nrm; i++)
	{
		v[index] = new masina();
		cout << "Masina nr. " << i+1 << ": ";
		v[index]->citire();
		index++;
	}

	for (int i = 0; i < nrd; i++)
	{
		v[index] = new duba();
		cout << "Duba nr. " << i+1 << ": ";
		v[index]->citire();
		index++;
	}
	
	for (int i = 0; i < nrs; i++)
	{
		v[index] = new scuter();
		cout << "Scuterul nr. " << i+1 << ": ";
		v[index]->citire();
		index++;
	}


}
void dispecerat::afisare_vehicule() {
	for (int i = 0; i < nrm; i++)
	{
		cout << "Masina nr. " << i + 1 << ": ";
		v[i]->afisare();
	}
	for (int i = nrm; i < nrd; i++)
	{
		cout << "Duba nr. " << i + 1 << ": ";
		v[i]->afisare();
	}
	for (int i = nrd; i < nrs; i++)
	{
		cout << "Scuterul nr. " << i + 1 << ": ";
		v[i]->afisare();
	}
}

void dispecerat::afisare_status_comenzi() {
	for (int i = 0; i < n; i++)
	{
		cout<<"Coletul "<<c[i]->get_index()<<" a fost: ";
		if (c[i]->get_primit() == true)
			cout << "livrat" << endl;
		else
			cout << "refuzat" << endl;
	}
}

void dispecerat::set_strategie(strategie _st) {
	st = _st;
}
void dispecerat::print_strategie() {
	switch (st)
	{
	case 0:
		cout << "aproape";
		break;
	case 1:
		cout << "rapida";
		break;
	case 2:
		cout << "liber";
		break;
	default:
		break;
	}
}

bool dispecerat::verifica_frigorifica(colet *col, vehicul *veh) {
	if (((col->reci == true) && (veh->frigorifica == true))|| (col->reci == false))
		return true;
	return false;
}
bool dispecerat::verifica_spatiu(colet *col, vehicul *veh) {
	if (veh->get_masa_ramasa() > col->get_masa() && veh->get_volum_ramas() > col->get_volum())
		return true;
	return false;
}

vehicul* dispecerat::calculeaza_minim_timp(colet *col) {
	vehicul *minv=v[0];
	for (int i = 1; i < nrv; i++)
	{
		int minute = col->calculeaza_minute(col->cand_ajunge(minv), col->cand_ajunge(v[i]));
		//calculam, in minute, diferenta dintre timpul in care ar ajunge minimul, si timpul in care ar ajunge vehiculul curent
		if (minute < 0 && (col->ajunge_la_timp(v[i]) == true) && (verifica_frigorifica(col, v[i])) && (verifica_spatiu(col, v[i])))
			minv = v[i];
		//daca diferenta e negativa, adica timpul in care ajunge v[i]<minv, atunci v[i] devine minimul
	}
	if ((col->ajunge_la_timp(minv) == true) && (verifica_frigorifica(col, minv)) && (verifica_spatiu(col, minv)))
		return minv;
	else
		return 0;
}
void dispecerat::distribuie_comenzi_rapid() {
	//pt fiecare comanda, se va gasi vehiculul care va distribui cel mai repede coletul (distanta/viteza)
	//in functie de coordonate(distanta euclidiana) si tipul vehiculului, fiecare vehicul avand propria viteza
	
	//bubblesort();
	sort(c, c + n, comp_timp);//sortam comenzile in functie de prioritatea de timp

	for (int i = 0; i < n; i++)
	{
		vehicul *vaux;
		if (calculeaza_minim_timp(c[i]) != 0)
		{
			vaux = calculeaza_minim_timp(c[i]);

			vaux->set_moment(c[i]->cand_ajunge(vaux));//momentul in care coletul a ajuns, devine momentul in care vehiculul se afla
			vaux->set_coord(c[i]->get_coord_destinatie());//pozitia la care coletul a ajuns, devine pozitia la care vehiculul se afla
			c[i]->set_primit(true);
			vaux->set_masa_ramasa(vaux->get_masa_ramasa() - c[i]->get_masa());
			vaux->set_volum_ramas(vaux->get_volum_ramas() - c[i]->get_volum());
			cout << "volumul a fost " << vaux->get_volum() << " si a ramas" << vaux->get_volum_ramas()<<endl;
		}
	}

	afisare_status_comenzi();
}

vehicul* dispecerat::calculeaza_minim_distanta(colet *col) {
	vehicul *minv = v[0];
	float mindist= minv->calculeaza_distanta(col->get_coord_client(), minv->get_coord());
	//initializam minimul cu primul element si elementul de comparatie cu distanta primului elem(vehicul) fata de colet
	for (int i = 1; i < nrv; i++)
	{
		int distanta = v[i]->calculeaza_distanta(col->get_coord_client(), v[i]->get_coord());
		//calculam distanta dintre vehiculul curent si colet
		if (distanta < mindist && (col->ajunge_la_timp(v[i]) == true) && (verifica_frigorifica(col, v[i])) && (verifica_spatiu(col, v[i])))
		{
			minv = v[i];
			mindist = distanta;
		}
		
	}
	if ((col->ajunge_la_timp(minv) == true) && (verifica_frigorifica(col, minv)) && (verifica_spatiu(col, minv)))
		return minv;
	else
		return 0;
}
void dispecerat::distribuie_comenzi_aproape() {
	//pt fiecare comanda, se va gasi vehiculul care este cel mai aproape de client (distanta)
	//in functie de distanta euclidiana
	sort(c, c + n, comp_timp);//sortam comenzile in functie de prioritatea de timp

	for (int i = 0; i < n; i++)
	{
		if (calculeaza_minim_distanta(c[i]) != 0)
		{
			vehicul *vaux;
			vaux = calculeaza_minim_distanta(c[i]);
			moment ceva = c[i]->cand_ajunge(vaux);
			cout << ceva.ora << " " << ceva.minut << endl;

			vaux->set_moment(c[i]->cand_ajunge(vaux));//momentul in care coletul a ajuns, devine momentul in care vehiculul se afla
			vaux->set_coord(c[i]->get_coord_destinatie());//pozitia la care coletul a ajuns, devine pozitia la care vehiculul se afla
			c[i]->set_primit(true);
			vaux->set_volum_ramas(vaux->get_volum_ramas() - c[i]->get_volum());
			cout << "volumul a fost " << vaux->get_volum() << " si a ramas" << vaux->get_volum_ramas()<<endl;
		}
	}

	afisare_status_comenzi();

}

vehicul* dispecerat::calculeaza_maxim_spatiu(colet *col) {
	vehicul *maxv = v[0];
	float maxsp = maxv->get_masa_ramasa() + maxv->get_volum_ramas();
	//initializam minimul cu primul element si elementul de comparatie cu spatiul primului vehicul(masa+volum)
	for (int i = 1; i < nrv; i++)
	{
		int spatiu = v[i]->get_masa_ramasa() + v[i]->get_volum_ramas();
		//calculam masa+volum pt fiecare vehicul curent
		if (spatiu > maxsp && (col->ajunge_la_timp(v[i]) == true) && (verifica_frigorifica(col, v[i])) && (verifica_spatiu(col, v[i])))
		{
			maxv = v[i];
			maxsp = spatiu;
		}

	}
	if ((col->ajunge_la_timp(maxv) == true) && (verifica_frigorifica(col, maxv)) && (verifica_spatiu(col, maxv)))
		return maxv;
	else
		return 0;
}
void dispecerat::distribuie_comenzi_liber() {
	//pt fiecare comanda, se va gasi vehiculul cel mai liber/gol(masa, volum cat mai mici)

	sort(c, c + n, comp_timp);//sortam comenzile in functie de prioritatea de timp

	for (int i = 0; i < n; i++)
	{
		if (calculeaza_maxim_spatiu(c[i]) != 0)
		{
			vehicul *vaux;
			vaux = calculeaza_maxim_spatiu(c[i]);

			vaux->set_moment(c[i]->cand_ajunge(vaux));//momentul in care coletul a ajuns, devine momentul in care vehiculul se afla
			vaux->set_coord(c[i]->get_coord_destinatie());//pozitia la care coletul a ajuns, devine pozitia la care vehiculul se afla
			c[i]->set_primit(true);
			vaux->set_volum_ramas(vaux->get_volum_ramas() - c[i]->get_volum());
			cout << "volumul a fost " << vaux->get_volum() << " si a ramas" << vaux->get_volum_ramas() << endl;
		}
	}

	afisare_status_comenzi();
}


#endif // !DISPECERAT_H

