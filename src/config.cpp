
#include "config.h"

#include <iostream>
#include <fstream>

using namespace std;

enum ConfigType {
	CT_ERROR,
	CT_STRING,
	CT_NUMBER,
	CT_DECIMAL,
	CT_INT_PAIR,
};

Config::Config()
{}

Config::Config(std::string file)
{
	load(file);
}

void Config::load(std::string file)
{
	std::string property;
	std::string typeString;
	ConfigType  type;
	std::string valueString;
	int         valueNumber;
	int         valueNumber2;
	double      valueDecimal;

	ifstream fin(file.c_str());

	if (fin.fail())
		cerr << "Config file not found: " << file << endl;

	else while (!fin.eof())
	{
		typeString = "";

		fin >> property;
		fin >> typeString;
		type = CT_ERROR;

		if(typeString == "STRING") type = CT_STRING;
		else if(typeString == "NUMBER") type = CT_NUMBER;
		else if(typeString == "DECIMAL") type = CT_DECIMAL;
		else if(typeString == "INT_PAIR") type = CT_INT_PAIR;

		switch(type)
		{
			case CT_STRING:
				fin.ignore(1); // ignore the space between TYPE and VALUE;
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

			case CT_INT_PAIR:
				fin >> valueNumber;
				fin >> valueNumber2;
				setProperty(property, valueNumber, valueNumber2);
				break;

			default:
				if(typeString.length())
					cerr << "Invalid property type: " << typeString << endl;
				break;
		}
	}
}
