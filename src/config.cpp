//
//  File: config.cpp
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Config Class Implementation
//

#include "config.h"

#include <iostream>
#include <fstream>

using namespace std;

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
	int         valueNumber[3] = {0};
	double      valueDecimal = 0.0;

	bool accepted;

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
		else if(typeString == "FLOAT") type = CT_FLOAT;
		else if(typeString == "DECIMAL") type = CT_DECIMAL;
		else if(typeString == "INT") type = CT_INT;
		else if(typeString == "NUMBER") type = CT_NUMBER;
		else if(typeString == "INT_PAIR") type = CT_INT_PAIR;
		else if(typeString == "INT_TRIPLE") type = CT_INT_TRIPLE;
		else if(typeString == "HEX") type = CT_HEX;

		switch(type)
		{
			case CT_STRING:
				fin.ignore(1); // ignore the space between TYPE and VALUE;
				getline(fin, valueString);
				accepted = setProperty(property, valueString);
				break;

			case CT_FLOAT:
			case CT_DECIMAL:
				fin >> valueDecimal;
				accepted = setProperty(property, valueDecimal);
				break;

			case CT_INT:
			case CT_NUMBER:
				fin >> valueNumber[0];
				accepted = setProperty(property, valueNumber[0]);
				break;

			case CT_INT_PAIR:
				fin >> valueNumber[0];
				fin >> valueNumber[1];
				accepted = setProperty(property, valueNumber[0], valueNumber[1]);
				break;

			case CT_INT_TRIPLE:
				fin >> valueNumber[0];
				fin >> valueNumber[1];
				fin >> valueNumber[2];
				accepted = setProperty(property, valueNumber, 3);
				break;

			case CT_HEX:
				fin >> std::hex >> valueNumber[0] >> std::dec;
				accepted = setProperty(property, valueNumber[0]);
				break;

			default:
				accepted = true;
				if(typeString.length())
					cerr << "Invalid property type: " << typeString << endl;
				break;
		}

		if(!accepted)
			cerr << "\033[33m Invalid identifier: " << property << "\033[m" << endl;
	}
}
