
#ifndef CONFIG_H_
#define CONFIG_H_

class Config
{
public:
	Config(string file);

	virtual void setProperty(string property, string value) {}
	virtual void setProperty(string property, int    value) {}
	virtual void setProperty(string property, double value) {}
};

#endif
