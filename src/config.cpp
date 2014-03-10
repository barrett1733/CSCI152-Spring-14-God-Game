
#include "config.h"

#include <iostream>
#include <fstream>

using namespace std;

const string configFile = "config.txt";

Config config;

Config::Config()
{
	ifstream fin(configFile.c_str());
	if(fin.fail())
		cerr << "Config file not found: " << configFile << endl;
	else
		cout << "Found config." << endl;
}
