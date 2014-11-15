//
//  File: config.h
//  Author: Chad Hatcher
//  CSci 152
//  Spring 2014
//  Instructor: Alex Liu
//
//  Config Class Definition
// Provides a standard interface for loading config files.
// File entries should have this format:
// <property_name> <property_type> <property_value(s)>
//

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

enum ConfigType {
	CT_ERROR,
	CT_STRING,
	CT_FLOAT,
	CT_DECIMAL,
	CT_INT,
	CT_NUMBER,
	CT_INT_PAIR,
	CT_INT_TRIPLE,
	CT_HEX,
	CT_FILE,
};

class Config
{
	virtual bool setProperty(std::string property, std::string value)         { return false; }
	virtual bool setProperty(std::string property, int    value)              { return false; }
	virtual bool setProperty(std::string property, double value)              { return false; }
	virtual bool setProperty(std::string property, int value1, int value2)    { return false; }
	virtual bool setProperty(std::string property, int * valueSet, int count) { return false; }

protected:
	void load(std::string file);

public:
	Config();
	Config(std::string file);


};

#endif
