#pragma once
#include "Contract.h"
#include "ContractRepo.h"
#include <vector>
#include <algorithm>

using std::vector;

class ActiuneUndo {

public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;

};

class undoAdauga : public ActiuneUndo
{
	Disciplina disciplinaAdaugata;
	AbsRepo* repo;
public:
	undoAdauga(AbsRepo* repo, const Disciplina& disciplina) : repo{ repo }, disciplinaAdaugata{ disciplina }{}
	void doUndo() override
	{
		int i = 0;
		for (auto& it : repo->getAllDiscipline()) {
			if (it == disciplinaAdaugata) {
				break;
			}
			++i;
		}
		repo->delet(i);
	}


};


class undoSterge : public ActiuneUndo
{
	Disciplina disciplinaStearsa;
	AbsRepo* repo;
	int poz;


public:

	undoSterge(AbsRepo* repo, const Disciplina& disciplina, const int poz) : repo{ repo }, disciplinaStearsa{ disciplina }, poz{poz} {}
	void doUndo() override
	{
		auto it = repo->getAllDiscipline().begin();
		it += poz;
		repo->getAllDiscipline().insert(it, disciplinaStearsa);
	}


};


class undoUpdate : public ActiuneUndo
{
	Disciplina disciplinaModificata;
	AbsRepo* repository;
	int poz;

public:
	undoUpdate(AbsRepo* repository, const Disciplina& disciplina, const int p) : repository{ repository }, disciplinaModificata{ disciplina }, poz{p}{}
	void doUndo() override
	{
		repository->modifica(disciplinaModificata,poz);
	}


};