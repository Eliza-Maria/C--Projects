#pragma once

#ifndef STRUCTURI_H
#define STRUCTURI_H

struct moment {
	int ora;
	int minut;
};

struct perioada {
	moment inceput;
	moment sfarsit;
};

struct coordonate {
	int x;
	int y;
};//o unitate inseamna 1km


#endif // !STRUCTURI_H

