#include <iostream>
#include <cstring>
#include "structuri.h"
#include "vehicul.h"
#include "colet.h"
#include "dispecerat.h"

using namespace std;

//FA FUNCTIE CARE GASESTE MINIMUL PT FIECARE COLET->CAND_AJUNGE(VEHICUL), PT FIECARE VEHICUL

int main() 
{
	/*colet c(10,30,false,deadline);
	c.set_coord_client(3, 4);
	c.set_coord_destinatie(8, 10);
	c.set_timp();
	list l;
	l.insert_last(c);
	l.print();*/

	/*masina mas;
	mas.afisare_moment();*/

	/*dispecerat d;
	d.citire_vehicule();
	d.afisare_vehicule();*/

	/*deadline col;
	vehicul *veh;

	veh = new masina();
	col.citire();
	veh->citire();
	//col.set_deadline2(120, 30);
	cout<<col.ajunge_la_timp(veh);*/

	dispecerat d;
	d.citire_comenzi();
	d.citire_vehicule();
	d.distribuie_comenzi_aproape();

	/*colet *c=new deadline();
	c->citire();
	vehicul *v = new masina();
	v->citire();
	cout<<(c->cand_ajunge(v)).ora<<" "<<( c->cand_ajunge(v)).minut;*/

	


	system("pause");
	return 0;
}