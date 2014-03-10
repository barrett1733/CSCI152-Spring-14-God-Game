
#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

class Config
{
public:
	Config(std::string file);

	virtual void setProperty(std::string property, std::string value) {}
	virtual void setProperty(std::string property, int    value) {}
	virtual void setProperty(std::string property, double value) {}
};

#endif
