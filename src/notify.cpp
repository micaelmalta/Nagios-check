#include <iostream>
#include <libnotify/notify.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Parser.hpp"

using namespace std;

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
	stringstream ss;

	sf::Clock mainClock;
	
	float x = 0, y = 0;
	string filename = "/tmp/status.dat";
	ss << "scp -q root@monitoring.serieslive.com:/usr/local/nagios/var/status.dat " << filename;
	
	//system(ss.str().c_str());
	std::string alert = read(filename);
	if(!alert.empty())
	{

		sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(400, 200, 8),
												"Nagios Notify", sf::Style::Close);

		mainClock.Reset();
		while(window->IsOpened())
		{
			sf::Event e;
			window->GetEvent(e);
			if(e.Type == sf::Event::Closed)
				window->Close();

			//Rendu
			window->Clear();

			sf::String text(alert);
			text.SetSize(16);

			sf::FloatRect rect = sf::FloatRect(0, 0, 400, 200);
			sf::Vector2f buttonCenter(
						rect.Left+(rect.Right-rect.Left)/2.f,
						rect.Top+(rect.Bottom-rect.Top)/2.f
						);

			sf::FloatRect tr = text.GetRect();

			text.SetPosition( buttonCenter.x - ((tr.Right-tr.Left)/2.f),
									buttonCenter.y - ((tr.Bottom-tr.Top)/2.f) - 2
									);
//			text.SetPosition( buttonCenter.x - ((tr.Right-tr.Left)/2.f),
//									buttonCenter.y - ((tr.Bottom-tr.Top)/2.f) - 2
//									);


			window->Draw(text);

//			if(mainClock.GetElapsedTime() > 6.f)
//				window->Close();

			window->Display();

		}

//		notify_init("verify");
//		NotifyNotification * notif = notify_notification_new (
//					"Check result :",
//					alert.c_str(),
//					"dialog-information");
//		notify_notification_show (notif, NULL);
	}
	
	return 0;
}
