#include "ConfigParser.hpp"

ConfigParser::ConfigParser()
{
	currentName = "";
	currentHostName = "";
	currentUserName = "";
	currentFilename = "";
}


void ConfigParser::treatLine(const std::string &line)
{
	if(!line.empty() && line[0] != '#' && line[0] != '\t')
	{
		currentName = parseName(line);
	}
	else if(line[0] == '\t')
	{
		std::vector <std::string> attribute = parseAttribute(line);

		if(attribute[0].compare("hostname") == 0)
		{
			currentHostName = attribute[1];
		}
		else if(attribute[0].compare("username") == 0)
		{
			currentUserName = attribute[1];
		}
		else if(attribute[0].compare("filename") == 0)
		{
			currentFilename = attribute[1];
		}
		else if(attribute[0].compare("}") == 0 && currentName.compare("host") == 0)
		{
			Host host;

			host.hostName = currentHostName;
			host.userName = currentUserName;
			host.fileName = currentFilename;

			hosts.push_back(host);

			currentName = "";
			currentHostName = "";
			currentUserName = "";
			currentFilename = "";
		}

	}

}

std::vector <ConfigParser::Host>  ConfigParser::getHosts()
{
	return hosts;
}

std::vector <std::string> ConfigParser::parseAttribute(const std::string &name)
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

std::string ConfigParser::parseName(const std::string &name)
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
