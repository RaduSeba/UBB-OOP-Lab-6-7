#pragma once
#include "Contract.h"
#include "validator.h"

#include <vector>
#include <string>
#include <ostream>
#include <map>

using std::vector;
using std::string;
using std::ostream;
using namespace std;


class AbsRepo {
public:
	
	virtual void store(const Disciplina& p)=0;
	
	virtual void delet(int poz)=0;
	
	virtual void modifica(const Disciplina& d,int poz)=0;

	virtual bool exportFisier(const string filename, const string type);

	virtual vector<Disciplina>& getAllDiscipline()=0;

	virtual ~AbsRepo() = default;
};







class ContractRepo: public AbsRepo {

public:
	ContractRepo() = default;
	//nu permitem copierea de obiecte
	ContractRepo(const ContractRepo& ot) = delete;
	
	virtual void store(const Disciplina& p) override;
	virtual void delet(int poz) override;
	virtual void modifica(const Disciplina& d,int poz) override;

	/*
	Cauta
	arunca exceptie daca nu exista disciplina
	*/
	const Disciplina& find(string denumire, string cadru);
	const Disciplina& find2(string denumire);

	bool exist(const Disciplina& p) ;
	//bool exist2(const Disciplina& p);


	//bool exportFisier(const string filename, const string type);
	/*
	returneaza toate animalele salvate
	*/
	vector<Disciplina>& getAllDiscipline() override;
	
	~ContractRepo() = default;

private:

	vector<Disciplina> allDiscipline;

};

class FileRepo :public ContractRepo {
private:
	string filename;

	void load_from_file();

	void save_to_file();
public:
	FileRepo() = default;
	explicit FileRepo(string fn);
	//FileRepo(const FileRepo& ot) : Repo(ot) {*this=ot;};

	~FileRepo() override = default;

	void store(const Disciplina& p) override {
		ContractRepo::store(p);
		save_to_file();
	}

	void delet(int poz) override {
		ContractRepo::delet(poz);
		save_to_file();
	}

	void modifica(const Disciplina& d,int poz) override {
		ContractRepo::modifica(d,poz);
		save_to_file();
	}


};


class RepoProb :public AbsRepo {
private:
	float prob;
	map<int, Disciplina> allDiscipline;
	void det_luck();
	


public:
	RepoProb() = default;
	~RepoProb() = default;

	explicit RepoProb(float chance);
	 
	void store(const Disciplina& p) override;
	
	void delet(int poz) override;
	
	void modifica(const Disciplina& d,int poz) override;
	vector<Disciplina> all;
	vector<Disciplina>& getAllDiscipline() override;
};





/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class ContractRepoException {
private:
	string errorMsg;
public:
	ContractRepoException(string errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		return this->errorMsg;
	}
};

class BadLuckException {
private:
	string errorMsg;
public:
	BadLuckException(string errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		return this->errorMsg;
	}
};


//ostream& operator<<(ostream& out, const ContractRepoException& ex);

void testeRepo();