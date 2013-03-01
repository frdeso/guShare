#ifndef CONFWINDOW_H_
#define CONFWINDOW_H_

#include <gtkmm.h>
#include "configuration.h"
#include "mainwindow.h"

class ConfWindow : public Gtk::Dialog {
        public :
                ConfWindow(Gtk::Window* parent, Configuration * config);
                std::string get_text();
                void set_text(std::string texte);
                void populateConfig(Configuration *config);

        private :
                Gtk::Box* m_VBox;
                Gtk::Entry uShareNameTxtBox_;
                Gtk::Entry uShareIFaceTxtBox_;
                Gtk::Entry uSharePortTxtBox_;
                Gtk::Entry uShareTelnetPortTxtBox_;
                Gtk::Entry uShareOverrideIConvErrTxtBox_;
                Gtk::Entry uShareEnableWebTxtBox_;
                Gtk::Entry uShareEnableTelnetTxtBox_;
                Gtk::Entry uShareEnableXboxTxtBox_;
                Gtk::Entry uShareEnableDlnaTxtBox_;
};
#endif //CONFWINDOW_H_