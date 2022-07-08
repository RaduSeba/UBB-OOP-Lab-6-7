#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Disciplina{
	std::string denumire;
	std::string tip;
	std::string cadru;
	int ore;
public:

	Disciplina() = default;
	Disciplina(const string d, int o, const string t, const string c) :denumire{ d }, ore{ o }, tip{ t }, cadru{ c }{}

	Disciplina(const Disciplina& ot) :denumire{ ot.denumire }, ore{ ot.ore }, tip{ ot.tip }, cadru{ ot.cadru } {
	}


	string getDenumire() const {
		return denumire;
	}
	int getOre() const noexcept {
		return ore;
	}

	string getTip() const {
		return tip;
	}
	string getCadru() const
	{
		return cadru;
	}

	void setDenumire(string numenou);
	void setOre(int orenoi);
	void setTip(string tipnou);
	void setCadru(string cadrunou);

	bool operator==(const Disciplina& ot);


};
/*
Compara dupa tip
returneaza true daca p1.tip e mai mic decat p2.tip
*/
bool cmpOre(const Disciplina& p1, const Disciplina& p2);

/*
Compara dupa specie
returneaza true daca p1.specie e mai mic decat p2.specie
*/
bool cmpDenumire(const Disciplina& p1, const Disciplina& p2);

bool cmpCadruTip(const Disciplina& m1, const Disciplina& m2);


