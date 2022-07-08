#pragma once

#include "Contract.h"
#include "ContractRepo.h"
#include "LstContract.h"
#include <string>
#include <vector>

#include <functional>
#include "validator.h"
#include "Undo.h"

using std::vector;
using std::function;

class ContractService {
private:
	AbsRepo* rep;
	 ContractValidator val;

	vector<ActiuneUndo*>undoActiuni;

	ListaContract currentList;
	

public:
	ContractService(AbsRepo* rep, ContractValidator& val);
	

	 vector<Disciplina>& getAllDiscipline();
	


	void addDisciplina(const string& denumire, int ore, const string& tip, const string& cadru);
	void	delDisciplina(const int& poz);
	void modifyDisciplina(const int& poz,const string& denumire,const int& ore, const string& tip, const string& cadru);
	//const Disciplina& cautareDisciplina(const string denumire, const string cadru);



	vector<Disciplina>filtrareOre(int ore);
	vector<Disciplina> filtrareCadru(string cadru);


	vector<Disciplina>sortByOre();
	vector<Disciplina>sortByDenumire();


	void addToListaContract(string denumire, string cadru);

	int addRandomtoListaContract(int cate);

	void emptyListaContract();

	const vector<Disciplina>& getListaContracte();

	
	bool exportFile(const string filename, const string type);


	size_t dimListaContract();

	int undo();

	~ContractService() = default;


};
void testeService();

