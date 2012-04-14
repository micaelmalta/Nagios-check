#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <gtkmm.h>
#include "notify.hpp"
#include "ConfigParser.hpp"

void quit(int)
{
	Gtk::Main::quit();
}

bool timeout()
{
	Gtk::Main::quit();
	return true;
}

int main(int argc, char * argv[])
{
	std::stringstream ss;
	std::string filename = "/tmp/status.dat";
	std::string alert = "";

	std::string defaultConfig = "config.cfg";

	if(argc>1)
		defaultConfig = std::string(argv[1]);
	std::vector <ConfigParser::Host> config = readConfig(defaultConfig);
	unsigned int i = 0;
	while(i < config.size())
	{
		ss.str("");

		ss << "scp -q "
			<< config[i].userName
			<< "@"
			<< config[i].hostName
			<< ":"
			<<  config[i].fileName
			<< " " << filename;

		//std::cout << ss.str() << std::endl;
		system(ss.str().c_str());

		alert += read(filename);

		i++;
	}

	if(!alert.empty())
	{

		Gtk::Main app(argc, argv);
		Gtk::MessageDialog dial(alert);

		// je cre un timer qui, aprs 10000ms,
		// lance la fonction timeout()
		Glib::RefPtr<Glib::TimeoutSource> ts;
		ts = Glib::TimeoutSource::create(10000);
		ts->connect(sigc::ptr_fun(&timeout));
		ts->attach();

		// je connecte le click du bouton valider  la fonction quit();
		dial.signal_response().connect(sigc::ptr_fun(&quit));

		// je balance la sauce
		app.run(dial);

	}

	return 0;
}
