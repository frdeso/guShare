#include "confwindow.h"
#include <string>
ConfWindow::ConfWindow(Gtk::Window* parent, Configuration *config) : Gtk::Dialog("Configuration", *parent), m_VBox(get_vbox()) { //Récupération de la boîte verticale avec get_vbox().
    m_VBox->pack_start(uShareNameTxtBox_);
    m_VBox->pack_start(uShareIFaceTxtBox_);
    m_VBox->pack_start(uSharePortTxtBox_);
    m_VBox->pack_start(uShareTelnetPortTxtBox_);
    m_VBox->pack_start(uShareOverrideIConvErrTxtBox_);
    m_VBox->pack_start(uShareEnableWebTxtBox_);
    m_VBox->pack_start(uShareEnableTelnetTxtBox_);
    m_VBox->pack_start(uShareEnableXboxTxtBox_);
    m_VBox->pack_start(uShareEnableDlnaTxtBox_);
    
    set_resizable(false);
    set_size_request(400,500);
    resize(400,500);
    //Ajout de boutons à la boîte de dialogue.
    add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    populateConfig(config);
    show_all();
}

std::string ConfWindow::get_text() {
    return uShareNameTxtBox_.get_text();
}

void ConfWindow::set_text(std::string texte) {
}

void ConfWindow::populateConfig(Configuration *config)
{
 uShareNameTxtBox_.set_text(config->getuShareName());
 uShareIFaceTxtBox_.set_text(config->getuShareIFace());
 uSharePortTxtBox_.set_text(config->getuSharePort());
 uShareTelnetPortTxtBox_.set_text(config->getuShareTelnetPort());
 uShareOverrideIConvErrTxtBox_.set_text(config->getuShareOverrideIConvErr());
 uShareEnableWebTxtBox_.set_text(config->getuShareEnableWeb());
 uShareEnableTelnetTxtBox_.set_text(config->getuShareEnableTelnet());
 uShareEnableXboxTxtBox_.set_text(config->getuShareEnableXbox());
 uShareEnableDlnaTxtBox_.set_text(config->getuShareEnableDlna());
}
