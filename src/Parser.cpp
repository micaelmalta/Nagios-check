#include "Parser.hpp"
#include <iostream>

Parser::Parser()
{
	currentAlerte = "";
	currentAttribute = "";
	currentHostName = "";
	currentName = "";
	currentOutput = "";
	currentServiceName = "";
	currentStatus = Parser::OK;
}

void Parser::treatLine(const std::string &line)
{
	if(!line.empty() && line[0] != '#' && line[0] != '\t')
	{
		currentName = parseName(line);
	}
	else if(line[0] == '\t')
	{
		std::vector <std::string> attribute = parseAttribute(line);

		if(attribute[0].compare("host_name") == 0)
		{
			currentHostName = attribute[1];
		}

		if(attribute[0].compare("service_description") == 0)
		{
			currentServiceName = attribute[1];
		}

		if(attribute[0].compare("current_state") == 0)
		{
			currentStatus = getStatus(attribute[1]);
		}

		if(attribute[0].compare("plugin_output") == 0)
		{
			currentOutput = attribute[1];
		}

		if(attribute[0].compare("}") == 0 && currentName.compare("servicestatus") == 0)
		{
			ServiceStatus status;

			status.hostName = currentHostName;
			status.serviceName = currentServiceName;
			status.status = currentStatus;
			status.output = currentOutput;

			services.push_back(status);

			currentAlerte = "";
			currentAttribute = "";
			currentHostName = "";
			currentName = "";
			currentOutput = "";
			currentServiceName = "";
			currentStatus = Parser::OK;
		}

	}

}

std::vector <Parser::ServiceStatus>  Parser::getServices()
{
	return services;
}

Parser::Status Parser::getStatus(const std::string &name)
{
	if(name.compare("0") == 0)
	{
		return Parser::OK;
	}
	else if(name.compare("1") == 0)
	{
		return Parser::UNKNOWN;
	}
	else if(name.compare("2") == 0)
	{
		return Parser::UNKNOWN;
	}
	else if(name.compare("3") == 0)
	{
		return Parser::UNKNOWN;
	}
	else
	{
		return Parser::UNKNOWN;
	}
}

std::vector <std::string> Parser::parseAttribute(const std::string &name)
{
	std::vector <std::string> result;
	unsigned int i = 1;
	char c = '\0';
	std::string key = "";
	std::string val = "";
	c = name[i];

	while(i < name.size() && c != '=')
	{
		c = name[i];
		if(c != '=')
			key += c;
		i++;
	}

	while(i < name.size())
	{
		c = name[i];
		val += c;
		i++;
	}

	result.push_back(key);
	result.push_back(val);

	return result;
}

std::string Parser::parseName(const std::string &name)
{
	std::string result = "";
	unsigned int i = 0;
	char c = '\0';
	c = name[i];

	while(i < name.size() && c != ' ')
	{
		c = name[i];
		if(c != ' ')
			result += c;
		i++;
	}

	return result;
}
