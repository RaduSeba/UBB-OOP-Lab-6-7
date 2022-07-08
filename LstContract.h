#pragma once
#include "Contract.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;

class ListaContract {
private:
	vector<Disciplina> ContractDiscipline;
public:
	ListaContract() = default;



	void addDisciplinatoLista(const Disciplina& d);


	void emptyList();


	void addRandomDisciplina(vector<Disciplina> originalDiscipline, int cate);

	const vector<Disciplina>& getallContractDiscipline();

	size_t dimLista();
};