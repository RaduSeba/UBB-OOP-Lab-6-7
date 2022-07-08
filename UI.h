#pragma once

#include "Service.h"
#include "Contract.h"
#include "ContractRepo.h"

class ConsolUI {
private:
	ContractService& ctr;
	
public:
	ConsolUI(ContractService& ctr) :ctr{ ctr } {
	}
	//nu permitem copierea obiectelor
	ConsolUI(const ConsolUI& ot) = delete;
	void printContractMeniu();
	void adaugaUI();
	void uiSort();
	void uiFilter();
	void deleteUI();
	void modifyUI();
	void cautaUI();
	void uiaddtoLista();
	void uiaddrandomtoLista();
	void uiemptyLista();
	void uiListaContact();
	void exportDisciplina();


	void tipareste(const vector<Disciplina>& dis);

	void start();
};