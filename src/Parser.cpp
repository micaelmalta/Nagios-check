#include "Parser.hpp"
#include <iostream>

Parser::Parser()
{
	currentName = "";
	currentAttribute = "";
	currentStatus = Parser::OK;
	currentAlerte = "";
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

		if(attribute[0].compare("current_state") == 0)
		{
			Parser::Status tmp = getStatus(attribute[1]);
			services[currentName] = tmp;
			Parser::Status tmp2 = services[currentName];
			int a = 0;
			a++;
		}

		//currentAttribute = attribute[0];
		//currentStatus = getStatus(attribute[1]);
//		if(attribute[0].compare("current_state") == 0)
//		{
//			currentStatus = getStatus(attribute[1]);
//		}
	}

	std::cout << currentName << " " << currentAttribute << " " << currentStatus << std::endl;
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

std::string Parser::getAlert()
{
	std::map < std::string , Parser::Status>::iterator it;
	std::string alert = "Not OK services :\n";

	for(it = services.begin(); it != services.end(); it++)
	{
		Parser::Status st = it->second;
		if(st != Parser::OK)
			alert += it->first + "\n";
	}

	return alert;
}

std::vector <std::string> Parser::parseAttribute(const std::string &name)
{
	std::vector <std::string> result;
	int i = 1;
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
	int i = 0;
	char c = '\0';
	c = name[i];

	while(i < name.size() && c != ' ')
	{
		c = name[i];
		result += c;
		i++;
	}

	return result;
}
