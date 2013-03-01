#include <iostream>
#include <glibmm/ustring.h>
#include "mainwindow.h"
#include "confwindow.h"
#include "configuration.h"

MainWindow::MainWindow() : m_Button_Quit("Quit")
{
        set_title("GuShare : a GUI for uShare");
        set_border_width(5);
        set_default_size(600, 500);
        m_Conf = new Configuration();
        m_Conf->ReadConfigFile("std::string path");

        add(m_VBox);
        populateMenu();
        //Add the TreeView, inside a ScrolledWindow, with the button underneath:
        m_ScrolledWindow.add(m_TreeView);

        //Only show the scrollbars when they are necessary:
        m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

        m_VBox.pack_start(m_ScrolledWindow);
        m_VBox.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);

        m_ButtonBox.pack_start(m_Button_Quit, Gtk::PACK_SHRINK);
        m_ButtonBox.set_border_width(5);
        m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
        m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::on_button_quit) );

        //Create the Tree model:
        m_refTreeModel = Gtk::TreeStore::create(m_Columns);
        m_TreeView.set_model(m_refTreeModel);
        //Add the TreeView's view columns:
        m_TreeView.append_column("#", m_Columns.m_col_id);
        m_TreeView.append_column("Directory", m_Columns.m_col_name);

        //All the items to be reordered with drag-and-drop:
        m_TreeView.set_reorderable();
        populateTree(m_Conf);


        show_all_children();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_button_quit()
{
        hide();
}

void MainWindow::on_treeview_row_activated(const Gtk::TreeModel::Path& path,
        Gtk::TreeViewColumn* /* column */)
{
        Gtk::TreeModel::iterator iter = m_refTreeModel->get_iter(path);
        if(iter)
        {
                Gtk::TreeModel::Row row = *iter;
                std::cout << "Row activated: ID=" << row[m_Columns.m_col_id] << ", Name="
                << row[m_Columns.m_col_name] << std::endl;
        }
}
void MainWindow::populateTree(Configuration * conf){
        m_refTreeModel->clear();
        for(unsigned int i = 0; i < conf->getFolderList()->size();i++){
                Gtk::TreeModel::Row row = *(m_refTreeModel->append());
                row[m_Columns.m_col_id] = i;
                row[m_Columns.m_col_name] = Glib::ustring((*conf->getFolderList())[i]);
        }


        //Connect signal:
        m_TreeView.signal_row_activated().connect(sigc::mem_fun(*this,
                &MainWindow::on_treeview_row_activated) );

}

void MainWindow::populateMenu(){
 
        //Create actions for menus and toolbars:
        m_refActionGroup = Gtk::ActionGroup::create();

        //File|New sub menu:
        m_refActionGroup->add(Gtk::Action::create("FileNewStandard",
                Gtk::Stock::NEW, "_New", "Create a new file"),
                sigc::mem_fun(*this, &MainWindow::on_menu_file_new_generic));
        //File|New sub menu:
        m_refActionGroup->add(Gtk::Action::create("FileAddDirectory",
                Gtk::Stock::NEW, "_Add Directory", "Add a new directory"),
                sigc::mem_fun(*this, &MainWindow::on_menu_file_add_directory));
        m_refActionGroup->add(Gtk::Action::create("OptionMenu", "Options"));
        m_refActionGroup->add(Gtk::Action::create("OptionConfiguration",Gtk::Stock::PREFERENCES
        , "_Configuration", "Create a new file"),
                sigc::mem_fun(*this, &MainWindow::on_menu_option_preference_generic));
        //File menu:
        m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));
        //Add directory menu:
        m_refActionGroup->add(Gtk::Action::create("AddDirectory", "File"));
        //Sub-menu.
        m_refActionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW));
        m_refActionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT),
                sigc::mem_fun(*this, &MainWindow::on_menu_file_quit));



        m_refUIManager = Gtk::UIManager::create();
        m_refUIManager->insert_action_group(m_refActionGroup);

        add_accel_group(m_refUIManager->get_accel_group());

        //Layout the actions in a menubar and toolbar:
        Glib::ustring ui_info = 
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='FileMenu'>"
        "        <menuitem action='FileNewStandard'/>"
        "      <separator/>"
        "       <menuitem action='FileAddDirectory'/>"
        "      <separator/>"
        "      <menuitem action='FileQuit'/>"
        "    </menu>"
        "    <menu action='OptionMenu'>"
        "        <menuitem action='OptionConfiguration'/>"
        "    </menu>"
        "  </menubar>"
        "</ui>";

        try
        {
                m_refUIManager->add_ui_from_string(ui_info);
        }
        catch(const Glib::Error& ex)
        {
                std::cerr << "building menus failed: " <<  ex.what();
        }

        //Get the menubar and toolbar widgets, and add them to a container widget:
        Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
        if(pMenubar)
                m_VBox.pack_start(*pMenubar, Gtk::PACK_SHRINK);


}

void MainWindow::on_menu_file_quit()
{
        hide(); //Closes the main window to stop the Gtk::Main::run().
}

void MainWindow::on_menu_file_new_generic()
{
        std::cout << "A File|New menu item was selected." << std::endl;
}
void MainWindow::on_menu_option_preference_generic()
{
        ConfWindow cw(this, getConfiguration());
        cw.run();
        std::cout << "A Option|preferences menu item was selected." << std::endl;
}
void MainWindow::on_menu_file_add_directory()
{
        Gtk::FileChooserDialog dialog(*this, "Ouverture d'un fichier",Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
        //Ajout de boutons.
        dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
        dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
        dialog.set_current_folder(Glib::get_home_dir());

        int ret = dialog.run();

        if(ret == Gtk::RESPONSE_OK)
        {
                m_Conf->getFolderList()->push_back(dialog.get_filename());
        }
        populateTree(m_Conf);
}

Configuration* MainWindow::getConfiguration(){
        return m_Conf;
}
