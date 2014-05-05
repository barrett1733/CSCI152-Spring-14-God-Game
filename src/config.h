
#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

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
