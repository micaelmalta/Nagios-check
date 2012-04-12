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
	if(line[0] != '#' && line[0] != '\n' && line[0] != '\t')
	{
		//currentName = line;
		std::cout << parseName(line) << std::endl;
	}
}

std::string Parser::getAlert()
{
	return currentAlerte;
}

std::string Parser::parseName(const std::string &name)
{
	std::string result = "";
	int i = 0;
	char c;
	do{
		c = name[i];
		result += c;
		i++;
	}while(c != ' ');

	return result;
}
