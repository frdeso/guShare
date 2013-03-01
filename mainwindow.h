#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include "configuration.h"

class MainWindow : public Gtk::Window
{
        public:
                MainWindow();
                virtual ~MainWindow();
                void on_menu_file_new_generic();
                void on_menu_option_preference_generic();
                void on_menu_file_add_directory();
                void on_menu_file_quit();
                void populateTree(Configuration *conf);
                void populateMenu();
                Configuration* getConfiguration();

        protected:
        //Signal handlers:
                void on_button_quit();
                void on_treeview_row_activated(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);


                //Tree model columns:
                class ModelColumns : public Gtk::TreeModel::ColumnRecord
                {
                public:

                ModelColumns()
                { add(m_col_id); add(m_col_name); }

                Gtk::TreeModelColumn<int> m_col_id;
                Gtk::TreeModelColumn<Glib::ustring> m_col_name;
                };

                ModelColumns m_Columns;

                //Child widgets:
                Gtk::VBox m_VBox;
                Glib::RefPtr<Gtk::UIManager> m_refUIManager;
                Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
                Glib::RefPtr<Gtk::RadioAction> m_refChoiceOne, m_refChoiceTwo;

                Gtk::ScrolledWindow m_ScrolledWindow;
                Gtk::TreeView m_TreeView;
                Glib::RefPtr<Gtk::TreeStore> m_refTreeModel;

                Gtk::HButtonBox m_ButtonBox;
                Gtk::Button m_Button_Quit;
                Configuration* m_Conf;
};

#endif //GTKMM_EXAMPLEWINDOW_H