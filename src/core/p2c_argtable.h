#ifndef _P2C_ARGTABLE_H_
#define _P2C_ARGTABLE_H_

#include <iostream>
#include <sstream>
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
	std::string getJSON();
	// TODO:json to argtable
	// void parserJSON(std::string);
};

void p2c_argtable::initArgs(int argc, char const *argv[])
{
	int state = 0;
	std::string tempstr;
	for (int i = 1; i < argc; i++)
		switch (state)
		{
		case 0:
			state = 1;
			tempstr.clear();
			tempstr = argv[i];
			break;
		case 1:
			if (argv[i][0] == '-')
			{
				this->addArg("command", tempstr);
				i--;
				state = 0;
				break;
			}
			tempstr += " ";
			tempstr += argv[i];
			break;
		default:
			break;
		}
	this->addArg("command", tempstr);
}

void p2c_argtable::addArg(std::string name, std::vector<std::string> context)
{
	this->_args[name].insert(_args[name].end(), context.begin(), context.end());
}

void p2c_argtable::addArg(std::string name, std::string context)
{
	this->_args[name].push_back(context);
}

std::vector<std::string> p2c_argtable::getArg(std::string name)
{
	if (_args.count(name))
		return this->_args[name];
	else
	{
		p2c_alerter::alerting(INFO, "map '_args' hasn't key =", name);
		return std::vector<std::string>();
	}
}

std::string p2c_argtable::getJSON()
{
	std::string JSON = "{";
	bool first_key = true;
	for (auto &n : this->_args)
	{
		if (first_key)
		{
			first_key = false;
			JSON += "\"" + n.first + "\":[";
		}
		else
			JSON += ",\"" + n.first + "\":[";
		bool first_val = true;
		for (std::string val : n.second)
		{
			if (first_val)
			{
				first_val = false;
				JSON += "\"" + val + "\"";
			}
			else
				JSON += ",\"" + val + "\"";
		}
		JSON += "]";
	}
	JSON += "}";
	return JSON;
}

#endif