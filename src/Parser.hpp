#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

class Parser
{
public:
	Parser();
	void treatLine(const std::string &line);
	std::string getAlert();

private:
	enum Status {
		OK,
		WARNING,
		UNKNOWN,
		CRITICAL,
		PENDING
	};

	std::string parseName(const std::string &name);

	std::string currentAlerte;
	std::string currentAttribute;
	std::string currentName;
	Parser::Status currentStatus;
};

#endif // PARSER_HPP
