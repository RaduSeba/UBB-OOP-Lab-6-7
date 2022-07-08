#include "validator.h"
#include <assert.h>
#include <sstream>

void ContractValidator::validate(const Disciplina& p) {
	vector<string> msgs;
	if (p.getOre() < 0) msgs.push_back("Nr de ore negativ!!!");
	if (p.getTip().size() == 0) msgs.push_back("Tip vid!!!");
	if (p.getDenumire().length() == 0) msgs.push_back("Denumire vida!!!");
	if (p.getCadru().size() == 0) msgs.push_back("Cadru vid!!!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

//ostream& operator<<(ostream& out, const BadLuckException& ex) {
//	out << ex.msg;
//	return out;
//}
