#include "UI.h"

#include "Contract.h"
#include <iostream>
#include <string>

using namespace std;



void ConsolUI::printContractMeniu() {
	cout << "MENIU CONTRACT" << endl;
	cout << "1. Adauga contract in lista" << endl;
	cout << "2. Adauga contract random in list" << endl;
	cout << "3. Goleste lista" << endl;
	cout << "4. Afiseaza lista curenta" << endl;
	cout << "5. Inapoi" << endl;
	cout << "6.Export" << endl;
}




void ConsolUI::tipareste(const vector<Disciplina>& dis)
{
	cout << "Discipline:\n";
	for (const auto& d : dis)
	{
		cout << " " << d.getDenumire() << " " << d.getOre() << " " << d.getTip() << " " << d.getCadru()<<"\n";
	}
	cout << "Sfarsit lista discipline\n";
}
void ConsolUI::adaugaUI() {
	string denumire, tip,cadru;
	int ore;
	cout << "Denumire:";
	cin >> denumire;
	cout << "Numarul de ore:";
	cin >> ore;
	cout << "Tip:";
	cin >> tip;
	cout << "Cadru didactic:";
	cin >> cadru;
	try {

		ctr.addDisciplina(denumire,ore,tip,cadru);
		cout << "Adaugat cu succes\n";	
	}
	catch(ContractRepoException& ba)
	{
		cout << ba.getErrorMessage();
	}
	catch (ValidateException& ve) {
		cout << "Disciplina nu este valida \n";
		cout << ve.getErrorMessages();
	}
	catch (BadLuckException& b) {
		cout << b.getErrorMessage();
	}
	
}

void ConsolUI::uiSort() {
	cout << "Criteriul de sortare este (ore/denumire/cadru+tip):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "ore")
		tipareste(ctr.sortByOre());
	/*else if (criteriu == "cadru+tip")
		tipareste(ctr.sortByCadruTip());*/
	else if (criteriu == "denumire")
		tipareste(ctr.sortByDenumire());
	else
		cout << "Nu se poate sorta dupa criteriul dat.\n";

}


void ConsolUI::uiFilter() {
	cout << "Criteriul de filtrare este (ore/cadru):";
	string criteriu;
	cin >> criteriu;

	if (criteriu == "cadru") {
		cout << "Cadrul didactic pentru care se afiseaza disciplinele:\n";
		string searchedGenre;
		cin >> searchedGenre;
		tipareste(ctr.filtrareCadru(searchedGenre));
	}
	else if (criteriu == "ore") {
		int nrore;
		cout << "Nr de ore pentru care doriti filtrarea:\n";
		cin >> nrore;

		tipareste(ctr.filtrareOre(nrore));
	}

	else
		cout << "Nu se poate sorta dupa criteriul dat.\n";
}



void ConsolUI::deleteUI() {
	string denumire,cadru,tip;
	int ore;
	cout << "Denumire dupa care doriti stergere:";
	cin >> denumire;
	cout << "Numarul de ore al disciplinei pe care doriti sa o stergeti: ";
	cin >> ore;
	cout << "Tipul disciplinei care doriti sa o stergeti:";
	cin >> tip;
	cout << "Cadrul didactic dupa care doriti stergere:";
	cin >> cadru;
	auto d = Disciplina(denumire, ore, tip, cadru);
	int index = 0;
	for ( auto& dis : ctr.getAllDiscipline()) {
		if (dis == d)
		{
			break;
		}
		++index;
	}
	if (index == ctr.getAllDiscipline().size())
	{
		cout << "Nu exista disciplina data";
	}
	try {

		ctr.delDisciplina(index);
	}
	catch (ContractRepoException& ba)
	{
		cout << ba.getErrorMessage();
	}
	catch (BadLuckException& b) {
		cout << b.getErrorMessage();
	}

}

void ConsolUI::modifyUI() {
	string denumire, tip, cadru;
	int ore;
	cout << "Denumirea diciplinei care trbuie modificata:";
	cin >> denumire;
	cout << "Numarul de ore nou:";
	cin >> ore;
	cout << "Tipul nou:";
	cin >> tip;
	cout << "Cadru didactic nou :";
	cin >> cadru;
	int index = 0;
	for (auto& dis : ctr.getAllDiscipline()) {
		if (dis.getDenumire() == denumire)
		{
			break;
		}
		++index;
	}
	if (index == ctr.getAllDiscipline().size())
	{
		cout << "Nu exista disciplina data";
	}
	try {

		ctr.modifyDisciplina(index,denumire, ore, tip, cadru);
		cout << "Modificat cu succes\n";
	}
	catch (ContractRepoException& ba)
	{
		cout << ba.getErrorMessage();
	}
	catch (ValidateException& ve) {
		cout << "NU exista disciplina cu denumirea data \n";
		cout << ve.getErrorMessages();
	}
	catch (BadLuckException& b) {
		cout << b.getErrorMessage();
	}

}

void ConsolUI::cautaUI() {
	string denumire, cadru;
	cout << "Denumire dupa care doriti cautarea: ";
	cin >> denumire;
	cout << "Cadrul didactic dupa care doriti cautarea: ";
	cin >> cadru;
	try {

		//Disciplina d = ctr.cautareDisciplina(denumire, cadru);
		//cout << " " << d.getDenumire() << " " << d.getOre() << " " << d.getTip() << " " << d.getCadru() << "\n";

	}
	catch (ContractRepoException& ba)
	{
		cout << ba.getErrorMessage();
	}

}


void ConsolUI::uiaddtoLista() {
	string denumire, cadru;
	cout << "Denumirea Disciplinei este: ";
	getline(cin >> ws, denumire);

	cout << "Cadrul didactic al Disciplinei este : ";
	getline(cin >> ws, cadru);

	try {
		ctr.addToListaContract(denumire, cadru);
		cout << "Disciplina a fost adugata cu succes in lista." << endl;
	}
	catch (ContractRepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidateException& ve) {
		cout << "Disciplina nu este valida" << endl;
		cout << ve.getErrorMessages();
	}

}

void ConsolUI::uiaddrandomtoLista() {
	int cate;
	cout << "Cate discipline sa aduge in lista";
	cin >> cate;

	try {
		int cateadaugate = ctr.addRandomtoListaContract(cate);
		cout << "S-au adaugat " << cateadaugate << "  discipline in lista " << endl;

	}
	catch (ContractRepoException& re) {
		cout << re.getErrorMessage();
	}
}

void ConsolUI::uiemptyLista() {
	ctr.emptyListaContract();
	cout << "S- au sters toate disciplinele din lista curenta." << endl;
}

void ConsolUI::exportDisciplina()
{
	string filename, type;
	cout << "Introduceti numele fisierului: ";
	cin >> filename;
	cout << "Introduceti extensia fisierului (html/csv): ";
	cin >> type;
	if (ctr.exportFile(filename, type))
		cout << "\nExport cu succes!\n";
	else
		cout << "\nExport failed!\n";
}

void ConsolUI::uiListaContact() {
	int cmd;
	int runningList = 1;
	while (runningList) {
		printContractMeniu();
		cout << "Comanda este:";
		cin >> cmd;
		switch (cmd)
		{
		case 1:
			uiaddtoLista();
			break;
		case 2:
			uiaddrandomtoLista();
			break;
		case 3:
			uiemptyLista();
			break;
		case 4:
			tipareste(ctr.getListaContracte());
			break;
		case 5:
			runningList = 0;
			break;
		case 6:
			exportDisciplina();
			break;
		default:
			break;
		}
	}
}



void ConsolUI::start() {
	while (true) {
		cout << "\nMeniu:\n";
		cout << "1 Adauga\n2 Afiseaza discipline \n3 Sterge\n4. Mofifica disciplina\n5. Cauta disciplina \n6. Filtrare\n7. Sortare\n8.Lista Contacte UI\n9. Undo\n0 Iesire\nDati comanda:";
		int cmd;
		cin >> cmd;

		switch (cmd) {
		case 0:
			return;
		case 1:
			adaugaUI();
			break;
		case 2:
			tipareste(ctr.getAllDiscipline());
			break;
		case 3:
			deleteUI();
			break;

		case 4:
			modifyUI();
			break;
		case 5:
			cautaUI();
			break;
		case 6:
			uiFilter();
			break;
		case 7:
			uiSort();
			break;
		case 8:
			uiListaContact();
			break;
		case 9:
			if (ctr.undo() == -1)
			{
				cout << "NU se mai poate face undo!\n";
			}
			else
			{
				tipareste(ctr.getAllDiscipline());
			}
			break;
		}
	}
}