#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <gtkmm.h>
#include "notify.hpp"
#include "Parser.hpp"
#include "ConfigParser.hpp"

std::string read(const std::string &filename)
{
	Parser *parser = new Parser();

	std::string line;

	std::ifstream myfile (filename.c_str());
	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
			getline (myfile,line);
			parser->treatLine(line);
		}
		myfile.close();
	}

	else std::cout << "Unable to open file";

	std::string alerte = getAlert(parser);

	delete parser;

	return alerte;

}

std::vector <ConfigParser::Host> readConfig(const std::string &filename)
{
	ConfigParser *configParser = new ConfigParser();

	std::string line;

	std::ifstream myfile (filename.c_str());
	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
			getline (myfile,line);
			configParser->treatLine(line);
		}
		myfile.close();
	}

	else std::cout << "Unable to open file";

	std::vector <ConfigParser::Host> config = configParser->getHosts();

	delete configParser;

	return config;

}

std::string getAlert(Parser *parser)
{
	std::vector <Parser::ServiceStatus> services = parser->getServices();

	std::vector <Parser::ServiceStatus>::iterator it;
	std::string alert = "";

	for(it = services.begin(); it != services.end(); it++)
	{
		Parser::ServiceStatus status = *it;
		if(status.status != Parser::OK)
		{
			alert += status.hostName + " : " + status.serviceName + "\n" + status.output + "\n\n";
		}
	}
	if(!alert.empty())
	{
		//alert = "Not OK services :\n" + alert;
	}
	return alert;
}


