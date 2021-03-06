// Tema.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <string>
#include <cctype>

using namespace std;

//Things boy
void Amintire();
void AdaugareTest(int i);
void FinalizareProgram();
void Verificare(string x);

int teste = 0;

int main()
{
	cout << "Ce ati dori sa faceti?" << endl;
	Amintire();

	int choice;
	string check;
	int i = 1;

	//Acest while va continua pe tot parcursul programului.
	while (1) {

		cin >> choice;
		if (choice == 1) {

			cout << "Mai aveti alte teste?(Da/Nu)" << endl;
			cin >> check;
			if (check == "Da" || check == "DA" || check == "dA" || check == "da") {
				ifstream Verif("Note " + to_string(i) + ".txt");
				while (Verif.is_open()) {
					teste++;
					ifstream Verificare("Note " + to_string(i) + ".txt");
					if (!Verificare.is_open())
						break;
					i++;
				}
				cout << flush;
				system("CLS");
			}
			if (check == "Nu" || check == "NU" || check == "nu" || check == "nU") {
				//Curatam ecranul.
				teste++;
				cout << flush;
				system("CLS");
				AdaugareTest(teste);
			}
			else {
				cout << "Raspuns necorepsunzator." << endl;
				cout << "Reintroduceti raspunsul(Da/Nu)" << endl;
				continue;
			}
		}
		else if (choice == 2) {

			cout << flush;
			system("CLS");
			FinalizareProgram();

		}
		else if (choice == 3)
			Amintire();
		else if (choice == 0) {
			cout << flush;
			system("CLS");
			exit(0);
		}
		else
			cout << "Nu exita aceasta optiune." << endl;

		if (choice != 3)
			cout << "Ce doriti sa faceti acum? Daca ati uitat optiunile, introduceti numarul 3." << endl;
	}
	return 0;
}

//Functie pentru adaugarea testelor
void AdaugareTest(int i) {

	//Deschidem fisierul.
	ofstream Fisier("Note " + to_string(i) + ".txt");
	string Nume;
	string Prenume;
	string Nota;
	bool are_doar_numere = false;

	if (!Fisier.is_open()) {
		cout << "Fisierul nu a putut fi deschis" << endl;
		exit(0);
	}

	cout << "Introduceti datele studentului si nota de la testul " << teste << endl;

	string Alegere = "Da";

	//Adaugarea de studenti.
	while (Alegere == "Da" || Alegere == "da" || Alegere == "DA" || Alegere == "dA") {

	start1:
		cout << "Nume:";
		cin >> Nume;

		for (size_t check = 0; check < Nume.length(); check++) {
			if (isdigit(Nume[check])) {
				cout << "Numele contine cifre, va rog sa-l introduceti din nou.\n" << endl;
				goto start1;
			}
		}

	start2:
		cout << "Prenume:";
		cin >> Prenume;

		for (size_t check = 0; check < Prenume.length(); check++) {
			if (isdigit(Prenume[check])) {
				cout << "Prenumele contine cifre, va rog sa-l introduceti din nou.\n" << endl;
				goto start2;
			}
		}

	start3:
		cout << "Nota:";
		cin >> Nota;

		for (size_t check = 0; check < Nota.length(); check++) {
			if (!isdigit(Nota[check])) {
				cout << "Nota contine litere, va rog sa reintroduceti nota.\n" << endl;
				goto start3;
			}
		}


		if (stod(Nota) < 0 || stod(Nota) >100) {
			cout << "Nota nu este corecta. Reintroduceti nota." << endl;
			goto start3;
		}

		Fisier << Nume << ", " << Prenume << ", " << Nota << endl;

		cout << "Doriti sa mai adaugati un student?(Da/Nu)" << endl;
		cin >> Alegere;
		if (Alegere == "Nu")
			break;
		cout << flush;
		system("CLS");

	}

}

//Functie care termina programul si adauga toate notele si toti studentii.
void FinalizareProgram() {

	if (teste == 0) {
		teste = teste - 1;
		int i = 1;
		ifstream Deschidere("Note 1.txt");
		while (Deschidere.is_open()) {
			teste++;
			ifstream Checks("Note " + to_string(i) + ".txt");
			if (!Checks.is_open())
				break;
			i++;
		}
	}
	//Curatam ecranul.
	cout << flush;
	system("CLS");
	string Line;

	//Creem o harta
	map<string, vector<double>> Results;

	//Parcurgem fiecare fisier
	for (int counting = 1; counting <= teste; ++counting) {

		ifstream Reading("Note " + to_string(counting) + ".txt");

		if (!Reading.is_open()) {
			cout << "Fisierul nu a putut fi deschis" << endl;
			exit(0);
		}

		getline(Reading, Line);
		while (!Reading.eof()) {

			//Despartim Numele, Prenumele si Nota fiecarui student in 2 string-uri, respectiv un int.
			int Thing = Line.find(",");
			string Nume = Line.substr(0, Thing);
			Line = Line.substr(Thing + 1);

			Thing = Line.find(",");
			string Prenume = Line.substr(0, Thing);
			Line = Line.substr(Thing + 1);

			//Vom trimite string-ul Line la o variabila double
			double Nota = stod(Line);

			//Vom folosi harta astfel incat key-ul sa fie realizat dintr-un Nume+Prenume in cazul in care exista 2 studenti cu acelasi nume.
			//Daca exista 2 studenti cu nume si prenume identice.. oh well.
			//Vom reface marimea Hartii "Results astfel incat sa aiba dimensiuni exacte.
			Results[Nume + Prenume].resize(teste);

			//Vom atribui fiecarui key pe pozitia counting-1 nota respectiva.
			Results[Nume + Prenume][counting - 1] = Nota;

			getline(Reading, Line);
		}

	}

	//Scrierea in fisierul "Note Finale"
	ofstream Writing("Note Finale.txt");

	if (!Writing.is_open()) {
		cout << "Fisierul final nu a putut fi deschis" << endl;
		exit(0);
	}

	//Folosim iteratorul auto pentru a porni variabila it, unde, it= inceputul hartii Results si care va continua pana la sfarsitul hartii.
	for (auto it = Results.begin(); it != Results.end(); it++) {

		Writing << "\"" << (*it).first << "\"";

		//Folosim auto deoarece iteratorul it este de tip auto?? - Self.note
		auto Grades = (*it).second;

		//Vom trece toate notele fiecarui student.
		for (double Grade : Grades)
			Writing << ", " << Grade;
		Writing << endl;
	}

}

//Functie pentru a aminti utilizatorul de optiunile lui.
void Amintire() {

	cout << "\n0.Ies din program." << endl;
	cout << "1.Sa adaug un test nou." << endl;
	cout << "2.Finalizez programul." << endl;

}



