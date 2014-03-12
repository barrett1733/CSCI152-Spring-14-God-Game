
#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

class Config
{
	virtual void setProperty(std::string property, std::string value) {}
	virtual void setProperty(std::string property, int    value) {}
	virtual void setProperty(std::string property, double value) {}

protected:
	void load(std::string file);

public:
	Config();
	Config(std::string file);


};

#endif
