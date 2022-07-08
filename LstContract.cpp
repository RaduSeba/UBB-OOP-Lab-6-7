#include "LstContract.h"
using std::shuffle;

void ListaContract::addDisciplinatoLista(const Disciplina& d) {
	this->ContractDiscipline.push_back(d);
}

void ListaContract::emptyList() {
	this->ContractDiscipline.clear();
}

void ListaContract::addRandomDisciplina(vector<Disciplina> originaldiscipline, int cate) {
	shuffle(originaldiscipline.begin(), originaldiscipline.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (ContractDiscipline.size() < cate && originaldiscipline.size() > 0) {
		ContractDiscipline.push_back(originaldiscipline.back());
		originaldiscipline.pop_back();
	}
}

const vector<Disciplina>& ListaContract::getallContractDiscipline() {
	return this->ContractDiscipline;
}

size_t ListaContract::dimLista()
{
	return count_if(ContractDiscipline.begin(), ContractDiscipline.end(), [](auto) {return true; });
}