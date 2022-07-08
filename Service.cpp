#include "Service.h"
#include <functional>
#include <algorithm>
#include <assert.h>

ContractService::ContractService(AbsRepo* rp, ContractValidator& vl) {
	rep = rp;
	val = vl;
	undoActiuni.clear();
}


vector<Disciplina>& ContractService::getAllDiscipline() {
	return rep->getAllDiscipline();
}







void ContractService::addDisciplina(const string& denumire, int ore,const string& tip,const string& cadru) {
	Disciplina p{ denumire,ore,tip,cadru };
	val.validate(p);
	rep->store(p);
	undoActiuni.push_back(new undoAdauga(rep, p));
}






void ContractService::delDisciplina(const int& poz) {
	auto dlt = rep->getAllDiscipline()[poz];
	rep->delet(poz);
	undoActiuni.push_back( new undoSterge(rep, dlt,poz));

}

void ContractService::modifyDisciplina(const int& poz,const string& denumire,const int& ore, const string& tip, const string& cadru) {
	Disciplina p{ denumire,ore,tip,cadru };
	val.validate(p);
	//const Disciplina disciplinademodificat = rep->find(denumire,cadru);
	
	auto di = rep->getAllDiscipline()[poz];
	rep->modifica(p, poz);
	undoActiuni.push_back( new undoUpdate(rep,di,poz));
}



//vector<Disciplina> ContractService::filter(function<bool(const Disciplina&)> fct) {
//	vector<Disciplina> filteredDiscipline;
//	for (const auto& disciplina : rep.getAllDiscipline()) {
//		if (fct(disciplina)) {
//			filteredDiscipline.push_back(disciplina);
//		}
//	}
//	return  filteredDiscipline;
//}
vector<Disciplina> ContractService::filtrareOre(int ore) {
	const vector<Disciplina>& allDiscipline = getAllDiscipline();
	vector<Disciplina> filtredDiscipline;
	std::copy_if(allDiscipline.begin(),allDiscipline.end(),back_inserter(filtredDiscipline),
	[ore](const Disciplina& m) {
		return m.getOre() == ore;
	});
	return filtredDiscipline;
}
vector<Disciplina> ContractService::filtrareCadru(string cadru) {
	const vector<Disciplina>& allDiscipline = getAllDiscipline();
	vector<Disciplina> filtredDiscipline;
	std::copy_if(allDiscipline.begin(), allDiscipline.end(), back_inserter(filtredDiscipline),
		[cadru](const Disciplina& m) {
			return m.getCadru() == cadru;
		});
	return filtredDiscipline;
}

vector<Disciplina> ContractService::sortByOre() {
	auto sortedCopy = rep->getAllDiscipline();
	sort(sortedCopy.begin(), sortedCopy.end(), cmpOre);
	return sortedCopy;
}

vector<Disciplina> ContractService::sortByDenumire() {
	auto sortedCopy = rep->getAllDiscipline();
	sort(sortedCopy.begin(), sortedCopy.end(), cmpDenumire);
	return sortedCopy;
}

//vector<Disciplina> ContractService::sortByCadruTip()
//{
//	return generalSort(cmpCadruTip);
//}



void ContractService::addToListaContract(string denumire, string cadru) {
	//const auto& disciplina = rep->find(denumire, cadru);
	//currentList.addDisciplinatoLista(disciplina);
	
}

int ContractService::addRandomtoListaContract(int cate) {
	currentList.addRandomDisciplina(this->getAllDiscipline(), cate);
	return cate;
}


void ContractService::emptyListaContract() {
	currentList.emptyList();
}

size_t ContractService::dimListaContract() {
	return currentList.dimLista();
}


const vector<Disciplina>& ContractService::getListaContracte() {
	return currentList.getallContractDiscipline();
}




int ContractService::undo()
{
	if (undoActiuni.empty())
		return -1;

	ActiuneUndo* act = undoActiuni.back();
	act->doUndo();
	undoActiuni.pop_back();
	delete act;
	return 0;
}

//ContractService::~ContractService()
//{
//	delete this->rep;
//}

bool ContractService::exportFile(const string filename, const string type)
{
	return rep->exportFisier(filename, type);
}







void testAddService() {
	auto* testRepo = new ContractRepo();
	auto testVal = ContractValidator();
	auto testService = ContractService(testRepo, testVal);

	testService.addDisciplina("oop",5,"de","fsega");
	testService.addDisciplina("oop2", 5, "de", "fsega2");
	testService.addDisciplina("oop3", 5, "de", "fsega3");

	assert(testService.getAllDiscipline().size() == 3);

	try {
		testService.addDisciplina("oop", 5, "de", "fsega");
	}
	catch (ContractRepoException&) {
		assert(true);
	}


	try {
		testService.addDisciplina("oo", -19, "de", "fsega");
	}
	catch (ValidateException& ve) {
		assert(ve.getErrorMessages() == "Nr de ore negativ!!!\n");
	}


	testService.delDisciplina(0);


	testService.modifyDisciplina(1,"oop2", 23, "2sas", "fsega2");



}

void testFilterService() {
	auto* testRepo = new ContractRepo();
	auto testVal = ContractValidator();
	auto testService = ContractService(testRepo, testVal);

	testService.addDisciplina("oop", 5, "de", "fsega");
	testService.addDisciplina("so", 3, "sas", "ubb");
	testService.addDisciplina("stefan", 22, "sirb", "ubb");
	testService.addDisciplina("seba", 212, "sssa", "fsega");

	//Disciplina d = testService.cautareDisciplina("so", "ubb");


	vector<Disciplina> disciplineore = testService.filtrareOre(5);
	assert(disciplineore.size() == 1);
	vector<Disciplina> disciplineubb = testService.filtrareCadru("ubb");
	assert(disciplineubb.size() == 2);


}

void testContract() {
	auto* testRepo = new ContractRepo();
	auto testVal = ContractValidator();
	auto testService = ContractService(testRepo, testVal);

	testService.addDisciplina("oop", 5, "de", "fsega");
	testService.addDisciplina("so", 3, "sas", "ubb");
	testService.addDisciplina("stefan", 22, "sirb", "ubb");
	testService.addDisciplina("seba", 212, "sssa", "fsega");

	testService.addRandomtoListaContract(1);
	assert(testService.getListaContracte().size() == 1);
	testService.emptyListaContract();
	assert(testService.getListaContracte().size() == 0);
	assert(testService.dimListaContract() == 0);


	testService.addToListaContract("oop", "fsega");

	assert(testService.getListaContracte().size() == 0);

	try {
		testService.addToListaContract("ba", "tare");
	}
	catch (ContractRepoException&) {
		assert(true);
	}



}

void testSortService() {
	auto* testRepo = new ContractRepo();
	auto testVal = ContractValidator();
	auto testService = ContractService(testRepo, testVal);

	testService.addDisciplina("so", 3, "sas", "ubb");
	testService.addDisciplina("stefan", 22, "sirb", "ubb");
	testService.addDisciplina("seba", 212, "sssa", "fsega");
	testService.addDisciplina("oop", 5, "de", "fsega");

	vector<Disciplina> sortedByOre = testService.sortByOre();
	assert(sortedByOre[0].getDenumire() == "so");
	assert(sortedByOre[1].getDenumire() == "oop");
	assert(sortedByOre[2].getDenumire() == "stefan");


	vector<Disciplina> sortedByDenumire = testService.sortByDenumire();
	assert(sortedByDenumire[0].getCadru() == "fsega");
	assert(sortedByDenumire[0].getDenumire() == "oop");





}

void testUndo()
{
	auto* testRepo = new ContractRepo();
	auto testVal = ContractValidator();
	auto testService = ContractService(testRepo, testVal);

	testService.addDisciplina("seba", 212, "da", "fsega");
	testService.modifyDisciplina(0,"seba", 22, "ay", "ubb");
	testService.delDisciplina(0);
	assert(testService.getAllDiscipline().size() == 0);
	testService.undo();
	assert(testService.getAllDiscipline().size() == 1);
	testService.undo();
	const Disciplina disciplina = testRepo->find2("seba");
	assert(disciplina.getOre() == 212);
	testService.undo();
	assert(testService.getAllDiscipline().size() == 0);
	assert(testService.undo() == -1);

}

void testeService() {
	testAddService();
	testFilterService();
	testContract();
	testSortService();
	testUndo();
}
