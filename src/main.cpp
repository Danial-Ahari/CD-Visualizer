#include "../include/mainwindow.hpp"
#include <gtkmm/application.h>

int main (int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.danialahari.cdvisualizer");
  
  MainWindow mainwindow;
  //Shows the window and returns when it is closed.
  app->set_flags(Gio::APPLICATION_NON_UNIQUE);
  return app->run(mainwindow);
}
