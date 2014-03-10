
#include "config.h"

#include <iostream>
#include <fstream>

using namespace std;

enum ConfigType {
	CT_NONE,
	CT_STRING,
	CT_NUMBER,
	CT_DECIMAL
};

Config::Config(std::string file)
{
	std::string property;
	std::string typeString;
	ConfigType type;
	std::string valueString;
	int    valueNumber;
	double valueDecimal;

	ifstream fin(file.c_str());

	if(fin.fail())
		cerr << "Config file not found: " << file << endl;

	else
	{
		fin >> property;
		fin >> typeString;
		type = CT_NONE;

		if(typeString == "STRING") type = CT_STRING;
		else if(typeString == "NUMBER") type = CT_NUMBER;
		else if(typeString == "DECIMAL") type = CT_DECIMAL;

		switch(type)
		{
			case CT_STRING:
				getline(fin, valueString);
				setProperty(property, valueString);
				break;

			case CT_NUMBER:
				fin >> valueNumber;
				setProperty(property, valueNumber);
				break;

			case CT_DECIMAL:
				fin >> valueDecimal;
				setProperty(property, valueDecimal);
				break;

			default:
				cerr << "Invalid property type: " << type << endl;
				break;
		}
	}
}
