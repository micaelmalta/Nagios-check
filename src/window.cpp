#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <string>

class MaFenetre : public Gtk::Window
{
protected:
	 Gtk::VBox vb;
	 Gtk::Label l;

public:
	MaFenetre(std::string alert);
	virtual ~MaFenetre();
};

MaFenetre::MaFenetre(std::string alert)
{
	 set_title("Nagios Alert !");
	 set_default_size(300, 100);

	 vb.pack_start(l);
	 l.show();

	 l.set_text(alert);

	 add(vb);

	 vb.show();
}

MaFenetre::~MaFenetre()
{
}

