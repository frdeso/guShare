#include "mainwindow.h"
#include <gtkmm/main.h>

int main(int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  MainWindow window;
  //Shows the window and returns when it is closed.
  window.show_all();
  Gtk::Main::run(window);

  return 0;
}