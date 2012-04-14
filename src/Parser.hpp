#ifndef PARSER_HPP
#define PARSER_HPP

#include <map>
#include <string>
#include <vector>

class Parser
{

public:
	enum Status {
		OK,
		WARNING,
		UNKNOWN,
		CRITICAL,
		PENDING
	};

	struct ServiceStatus{
		std::string hostName;
		std::string serviceName;
		std::string output;
		Parser::Status status;
	};

public:
	Parser();
	void treatLine(const std::string &line);
	std::string getAlert();
	std::vector <ServiceStatus>  getServices();

private:

	std::string parseName(const std::string &name);
	Parser::Status getStatus(const std::string &name);
	std::vector <std::string> parseAttribute(const std::string &name);

	std::string currentAlerte;
	std::string currentAttribute;
	std::string currentName;
	std::string currentHostName;
	std::string currentOutput;
	std::string currentServiceName;
	Parser::Status currentStatus;

	std::vector <ServiceStatus>  services;
};

#endif // PARSER_HPP
