#ifndef PARSER_HPP
#define PARSER_HPP

#include <map>
#include <string>
#include <vector>

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
	Parser::Status getStatus(const std::string &name);
	std::vector <std::string> parseAttribute(const std::string &name);

	std::string currentAlerte;
	std::string currentAttribute;
	std::string currentName;
	Parser::Status currentStatus;

	std::map < std::string , Parser::Status> services;
};

#endif // PARSER_HPP
