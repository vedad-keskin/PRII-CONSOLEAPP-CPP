#include<iostream>
using namespace std;

char* GetNizKaraktera(const char* tekst) {


	int vel = strlen(tekst) + 1;
	char* novi = new char[vel];
	strcpy_s(novi, vel, tekst);
	return novi;
}



class Osoba {
protected:
	char* _imeprezime;
	char* _JMBG;



};


class Profesor {   
public:
	char* _titula;



};



class Predmet {
public:
	char* _naziv;
	int* _ECTS;
	Profesor* _predmetniProfesor;



};

class Student { 
public:
	char* _brojIndeksa;
	Predmet* _polozeniPredmeti; 
	int _max;
	int _trenutno;



};



void main() {


	system("PAUSE>0");
}