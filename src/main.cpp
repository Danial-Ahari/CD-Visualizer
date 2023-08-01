// CD Image Visualizer
// Danial Ahari, mentored by Dr. Jacob Hauenstein
// The University of Alabama in Huntsville
// Summer 2023
//*************************************************************
// This project is part of a Summer 2023 RCEU conducted at the
// University of Alabama in Huntsville
//
// The code contained in edcchk.cpp is based on Natalia
// Portillo's code that can be found at 
// https://github.com/claunia/edccchk
// The licensing information is contained within that file.
//
// Many thanks are given to the people that contributed to
// projects used here. Without you, none of this would have
// been possible.

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
