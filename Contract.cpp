#include "Contract.h"

void Disciplina::setDenumire(string denumirenoua) {
	
	this->denumire = denumirenoua;
}

void Disciplina::setOre(int orenoi) {

	this->ore = orenoi;
}

void Disciplina::setTip(string tipnou) {

	this->tip=tipnou;
}

void Disciplina::setCadru(string cadrunou) {

	this->cadru = cadrunou;
}

//bool Disciplina::operator==(const Disciplina& ot)
//{
//	if (denumire == ot.denumire && tip == ot.tip && ore == ot.ore && cadru == ot.cadru)
//	{
//		return true;
//	}
//	return false;
//}

bool Disciplina::operator==(const Disciplina& ot)
{
	if (denumire == ot.denumire && ore == ot.ore && tip == ot.tip && cadru == ot.cadru)
	{
		return true;
	}
	return false;

}


bool cmpDenumire(const Disciplina& p1, const Disciplina& p2)
{
	return p1.getDenumire() < p2.getDenumire();
}

bool cmpOre(const Disciplina& p1, const Disciplina& p2)
{
	return p1.getOre() < p2.getOre();
}

bool cmpCadruTip(const Disciplina& m1, const Disciplina& m2) {
	if (m1.getCadru() == m2.getCadru())
		return m1.getDenumire() < m2.getDenumire();
	else
		return m1.getTip() < m2.getTip();
}