#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <assert.h>
#include <vector>
#include "UI.h"
#include "ContractRepo.h"
#include "Service.h"
#include "validator.h"
#include "Contract.h"






void testall() {
	testeRepo();
	testeService();
}

void startApp() {
	ContractRepo* rp = new ContractRepo;
	ContractValidator val;
	ContractService ctr{ rp,val };
	ConsolUI ui{ ctr };
	ui.start();
}

int main() {
		
		testall();
		startApp();
		return 0;
}