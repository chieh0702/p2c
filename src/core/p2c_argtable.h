#ifndef _P2C_ARGTABLE_H_
#define _P2C_ARGTABLE_H_

#include <iostream>
#include <vector>
#include <map>

class p2c_argtable
{
private:
	std::map<std::string, std::vector<std::string>> _args;

public:
	p2c_argtable(){};
	p2c_argtable(int argc, char const *argv[]) { this->initArgs(argc, argv); };
	~p2c_argtable(){};
	void initArgs(int argc, char const *argv[]);
	void addArg(std::string, std::vector<std::string>);
	void addArg(std::string, std::string);
	std::vector<std::string> getArg(std::string);
};

void p2c_argtable::initArgs(int argc, char const *argv[])
{
	std::vector<std::string> tokens;
	for (int i = 1; i < argc; i++)
		tokens.push_back(argv[i]);
	// TODO: parser to table
}

void p2c_argtable::addArg(std::string name, std::vector<std::string> context)
{
	
}

void p2c_argtable::addArg(std::string name, std::string context)
{

}

std::vector<std::string> p2c_argtable::getArg(std::string name)
{
	
}

#endif