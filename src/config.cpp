
#include "config.h"

#include <iostream>
#include <fstream>

using namespace std;

Config::Config(string file)
{
	string property;
	string type;
	string valueString;
	int    valueNumber;
	double valueDecimal;

	ifstream fin(file.c_str());

	if(fin.fail())
		cerr << "Config file not found: " << file << endl;
	else
	{
		fin >> property;
		fin >> type;
		switch(type)
		{
			case "STRING":
				getline(fin, valueString);
				setProperty(property, valueString);
				break;

			case "NUMBER":
				fin >> valueNumber;
				setProperty(property, valueNumber);
				break;

			case "DECIMAL":
				fin >> valueDecimcal;
				setProperty(property, valueDecimal);
				break;

			default:
				cerr << "Invalid property type: " << type << endl;
				break;
		}
	}
}
