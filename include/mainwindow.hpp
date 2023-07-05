#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/entry.h>
#include <string.h>
#include <gtkmm/image.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/eventbox.h>

class MainWindow : public Gtk::Window
{

public:
  MainWindow();
  virtual ~MainWindow();
  int levelsOfView = 0;
  int numOfSectors = 330000;
  int targetLocationLevel1;
  int targetLocationLevel2;
  int targetLocationLevel3;
  int targetLocationLevel4;
  int targetLocationLevel5;
  FILE *image;

protected:
  //Signal handlers:
  void on_0_button_clicked();
  void on_1_button_clicked();
  void on_2_button_clicked();
  void on_3_button_clicked();
  void on_4_button_clicked();
  void on_5_button_clicked();
  void on_6_button_clicked();
  void on_7_button_clicked();
  void on_8_button_clicked();
  void on_9_button_clicked();
  void on_sector_clicked(int button);
  void reset_vis();

  //Member widgets:
  Gtk::Grid main_grid;
  Gtk::Label instruction_label;
  Gtk::Label info_label;
  Gtk::Button sector_button_0;
  Gtk::Button sector_button_1;
  Gtk::Button sector_button_2;
  Gtk::Button sector_button_3;
  Gtk::Button sector_button_4;
  Gtk::Button sector_button_5;
  Gtk::Button sector_button_6;
  Gtk::Button sector_button_7;
  Gtk::Button sector_button_8;
  Gtk::Button sector_button_9;
  Gtk::Button reset_button;
  Gtk::Button open_file_button;
  Gtk::Entry file_path_view;
  Gtk::Label hex_viewer;
  Gtk::ScrolledWindow scroller;
  Gtk::Image imageObject;
  Gtk::Label file_path_label;
  Gtk::MessageDialog message;
  Gtk::EventBox imageObjectEvent;
  // Generally helpful functions:
  void updateLevel();
  void createSectorArray(FILE* image);
  std::string testSectors(int first, int last);
  std::string makeString(int first, int last);
  void renderBlocks(int level);
  std::string getHex(int sector);
  void open_file();
  void genImage();
  bool exportImage(GdkEventButton* event);
};

#endif // GTKMM_MAINWINDOW_H
