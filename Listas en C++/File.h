#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <conio.h>
#include <stdlib.h>

using namespace std;
class File {
private:
	ofstream filewrite; //offstream escribe
	ifstream fileread; //ifstream lee
	string cod_distrito, cod_partido, cant_votos;
public:
	File() {}
	void read2() {
		string line = "";
		fileread.open("votos.txt", ios::in);
		if (fileread.fail()) {                             
			fileread.close();               
			filewrite.open("votos.txt", ios::out);
			filewrite << "U202215888|SI32|2023";           
			filewrite.close();
			fileread.open("votos.txt", ios::in);
		}
		while (getline(fileread, line, ' ')) {
			stringstream s(line);
			getline(s, cod_distrito, '|');
			getline(s, cod_partido, '|');
			getline(s, cant_votos, '|');
		}
		fileread.close();
	}
	string getcod_distrito() { return cod_distrito; }
	string getcod_partido() { return cod_partido; }
	string getcant_votos() { return cant_votos; }

};