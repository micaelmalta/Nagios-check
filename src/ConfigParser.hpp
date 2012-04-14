#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <string>
#include <vector>

class ConfigParser
{
public:
    ConfigParser();
	 struct Host{
		 std::string hostName;
		 std::string userName;
		 std::string fileName;
	 };

	 void treatLine(const std::string &line);
	 std::vector <Host> getHosts();

private:
	 std::string parseName(const std::string &name);
	 std::vector <std::string> parseAttribute(const std::string &name);

	 std::vector <Host> hosts;

	 std::string currentName;
	 std::string currentHostName;
	 std::string currentUserName;
	 std::string currentFilename;
};

#endif // CONFIGPARSER_HPP
