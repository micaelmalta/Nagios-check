#include <iostream>
#include <libnotify/notify.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Parser.hpp"

using namespace std;

string readFile()
{
	string line;
	ifstream myfile ("myfile.txt");

	if(!myfile.good())
	{
		cout << "Can't open myfile.txt" << endl;
		exit(-1);
	}
	getline (myfile,line);

	myfile.close();
	return line;
}

string read(const string &filename)
{
	Parser *parser = new Parser();

	string line;

	ifstream myfile (filename.c_str());
	if (myfile.is_open())
	{
		while ( myfile.good() )
		{
			getline (myfile,line);
			parser->treatLine(line);
		}
		myfile.close();
	}

	else cout << "Unable to open file"; 
	
	std::string alerte = parser->getAlert();

	delete parser;

	return alerte;
	
}





int main()
{
	string orig = readFile();
	string current = orig;
	stringstream ss;
	
	string filename = "/tmp/status.dat";
	ss << "scp -q root@monitoring.serieslive.com:/usr/local/nagios/var/status.dat " << filename;
	
	system(ss.str().c_str());
	read(filename);
	/*
 while(1)
 {
  sleep(1);
  current = readFile();
  if(current.compare(orig) != 0)
  {
 ss.str("");
 notify_init("verify");
 ss << "myfile.txt has changed :" << endl;
 ss << "from '" << orig << "' to '" << current << "'" << endl;
 NotifyNotification * notif = notify_notification_new (
	 "Change!",
	 ss.str().c_str(),
	 "dialog-information");
 notify_notification_show (notif, NULL);
 orig = current;
  }
 }*/
	
	return 0;
}
