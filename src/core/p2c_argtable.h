#ifndef _P2C_ARGTABLE_H_
#define _P2C_ARGTABLE_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

class p2c_argtable
{
private:
	std::map<std::string, std::queue<std::string> *> *_args;

public:
	p2c_argtable()
	{
		_args = new std::map<std::string, std::queue<std::string> *>;
		p2c_alerter::alerting(DEBUG, "p2c_argtable:19: success new '_args'");
	};
	p2c_argtable(int argc, char const *argv[])
	{
		p2c_argtable();
		this->initArgs(argc, argv);
		p2c_alerter::alerting(DEBUG, "p2c_argtable:25: success initArgs");
	};
	~p2c_argtable()
	{
		for (auto &n : *_args)
		{
			delete n.second;
		}
		delete _args;
	};
	void initArgs(int argc, char const *argv[]);
	void addArg(std::string, std::vector<std::string>);
	void addArg(std::string, std::string);
	std::queue<std::string> *getArg(std::string);
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

void p2c_argtable::addArg(std::string name, std::vector<std::string> contexts)
{
	for (std::string context : contexts)
		this->addArg(name, context);
}

void p2c_argtable::addArg(std::string name, std::string context) // TODO: fix bug
{
	if (!_args->count(name))
	{
		_args->insert(std::pair<std::string, std::queue<std::string> *>(name, new std::queue<std::string>));
		p2c_alerter::alerting(DEBUG, "p2c_argtable:76: success new queue for", name);
	}
	(*_args)[name]->push(context);
}

std::queue<std::string> *p2c_argtable::getArg(std::string name)
{
	if (_args->count(name))
		return (*_args)[name];
	else
	{
		p2c_alerter::alerting(INFO, "map '_args' hasn't key =", name);
		return nullptr;
	}
}

std::string p2c_argtable::getJSON()
{
	std::string JSON = "{";
	bool first_key = true;
	for (auto &n : *_args)
	{
		if (first_key)
		{
			first_key = false;
			JSON += "\"" + n.first + "\":[";
		}
		else
			JSON += ",\"" + n.first + "\":[";
		bool first_val = true;
		std::queue<std::string> duplicate(*n.second);
		while (!duplicate.empty())
		{
			if (first_val)
			{
				first_val = false;
				JSON += "\"" + duplicate.front() + "\"";
			}
			else
				JSON += ",\"" + duplicate.front() + "\"";
			duplicate.pop();
		}
		JSON += "]";
	}
	JSON += "}";
	return JSON;
}

#endif