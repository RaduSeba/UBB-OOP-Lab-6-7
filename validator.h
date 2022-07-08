#pragma once
#include <string>
#include "Contract.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	vector<string> errorMsg;
public:
	ValidateException(vector<string> errorMessages) :errorMsg{ errorMessages } {};

	string getErrorMessages() {
		string fullMsg = "";
		for (const string e : errorMsg) {
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
};

//class BadLuckException {
//private:
//	string msg;
//public:
//	explicit BadLuckException(const string& str) : msg{ str } {}
//
//	friend ostream& operator<<(ostream& out, const BadLuckException& ex);
//};
//
//ostream& operator<<(ostream& out, const BadLuckException& ex);

//ostream& operator<<(ostream& out, const ValidateException& ex);

class ContractValidator {
public:
	void validate(const Disciplina& p);
};

void testValidator();