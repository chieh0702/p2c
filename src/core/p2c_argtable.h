#include <iostream>
#include <vector>

class p2c_argtable
{
private:
	std::vector<std::string> _commend;
	std::string _from;
	std::vector<std::string> _add;
	std::vector<std::string> _copy;
	std::vector<std::string> _env;
	std::vector<std::string> _run;
	std::vector<std::string> _cmd;
	std::vector<std::string> _entrypoint;
	std::vector<std::string> _ignore;
	std::string _path;
public:
	p2c_argtable(){};
	p2c_argtable(int argc, char const *argv[]) { this->parserArgs(argc, argv); };
	~p2c_argtable(){};
	void parserArgs(int argc, char const *argv[]);
};

void p2c_argtable::parserArgs(int argc, char const *argv[])
{
	std::vector<std::string> tokens;
	for (int i = 1; i < argc; i++)
		tokens.push_back(argv[i]);
	// TODO: parser to table
}