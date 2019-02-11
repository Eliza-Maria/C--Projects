#include<iostream>
#include<string>
#include<typeinfo>
#include<vector>
#include "Produs.h"
#include "Stoc.h"
#include "Magazin.h"


using namespace std;

int main() {
	
	Magazin m;
	
	m.citire_produse();
	m.set_clienti(1);
	m.serveste_clienti();
	m.afisare_stoc();
	m.afiseaza_profit();
	m.afisare_produse();

	system("pause");
	return 0;
}