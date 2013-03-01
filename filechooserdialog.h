#ifndef FILECHOOSERDIALOG_H_
#define FILECHOOSERDIALOG_H_

#include <gtkmm.h>
class FileChooserDialog : public Gtk::Window
{
        public:
                FileChooserDialog();
                ~FileChooserDialog();

        protected:
                //Signal handlers:
                void on_button_file_clicked();
                void on_button_folder_clicked();

                //Child widgets:
                Gtk::VButtonBox m_ButtonBox;
                Gtk::Button m_Button_File, m_Button_Folder;
};
#endif //FILECHOOSERDIALOG_H_