#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;

class ExceptionsManager {

	vector<string> excpMsg;

public:
	ExceptionsManager* insertExcp(const string& msg);
	void printAllMsg();



};