#ifndef NOTIFY_HPP
#define NOTIFY_HPP

#include <string>
#include "Parser.hpp"
#include "ConfigParser.hpp"

std::string getAlert(Parser *parser);
std::string read(const std::string &filename);
std::vector <ConfigParser::Host> readConfig(const std::string &filename);

#endif // NOTIFY_HPP
