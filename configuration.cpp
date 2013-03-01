#include "configuration.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <gtkmm.h>

Configuration::Configuration(){
        folderList_ = new std::vector<std::string>();
        pathConfFile_ = Glib::get_current_dir()+std::string("/")+std::string("usharer.conf");
}
Configuration::~Configuration(){
        delete folderList_;
}
void Configuration::ReadConfigFile(std::string path)
{
        //  static char filename[] = "/home/frdeso/projets/gushare/usharer.conf";
        FILE *file = fopen ( pathConfFile_.c_str(), "r" );
        if ( file != NULL )
        {
                char line [ 128 ]; /* or other suitable maximum line size */
                while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
                {
                        AnalyseLine(line);
                }
                fclose ( file );
        } else {
                perror ( pathConfFile_.c_str() ); /* why didn't the file open? */
        }
}

void Configuration::WriteConfigFile(std::string path)
{
//        static char filename[] = "/home/frdeso/projets/gushare/wusharer.conf";
        FILE *file = fopen ( pathConfFile_.c_str(), "w" );
        if ( file != NULL ){
                char line [ 128 ]; /* or other suitable maximum line size */
                for(int i = 0; i < NUMBEROFARGUMENT; i++){
                    /*TODO: Saving the updated configuration*/    
                }
                fclose ( file );
        }else{
                perror ( pathConfFile_.c_str() ); /* why didn't the file open? */
        }
}

void Configuration::AnalyseLine(std::string line)
{
        std::string arg = "";
        std::string value = "";
        char *current = '\0';
        if(line[0] == '#')
                return;
        for(int i = 0;i < line.size();i++) {
                if(line[i] == '=') {
                        std::stringstream correctLine(line);
                        getline(correctLine, arg, '=');
                        getline(correctLine, value, '=');

                        std::cout <<arg<<"="<<value<< "\n";
                        value = value.substr(0,value.size()-1);
                        setArguments(arg, value);
                }
        }
}

void Configuration::setArguments(std::string arg, std::string value){
        if(arg == "USHARE_NAME")
                uShareName_ = value;
        else if(arg ==  "USHARE_IFACE")
                uShareIFace_ = value;
        else if(arg ==  "USHARE_PORT")
                uSharePort_ = value;
        else if(arg ==  "USHARE_TELNET_PORT")
                uShareTelnetPort_ = value;
        else if(arg ==  "USHARE_DIR"){
                std::stringstream pathList(value);
                for (std::string path; std::getline(pathList, path, ','); folderList_->push_back(path));
        }else if(arg ==  "USHARE_OVERRIDE_ICONV_ERR")
                uShareOverrideIConvErr_ = value;
        else if(arg ==  "USHARE_ENABLE_WEB")
                uShareEnableWeb_ = value;
        else if(arg ==  "USHARE_ENABLE_TELNET")
                uShareEnableTelnet_ = value;
        else if(arg ==  "USHARE_ENABLE_XBOX")
                uShareEnableXbox_ = value;
        else if(arg ==  "USHARE_ENABLE_DLNA")
                uShareEnableDlna_ = value;
}

std::vector<std::string> *Configuration::getFolderList(){
        //TODO change it to be more secure returning a copy of the
        //real vector also setter that can add element
        return folderList_;
}

/*Getters*/
std::string Configuration::getuShareName() {return this->uShareName_;}
std::string Configuration::getuShareIFace(){return this->uShareIFace_;}
std::string Configuration::getuSharePort(){return this->uSharePort_;}
std::string Configuration::getuShareTelnetPort(){return this->uShareTelnetPort_;}
std::string Configuration::getuShareOverrideIConvErr(){return this->uShareOverrideIConvErr_;}
std::string Configuration::getuShareEnableWeb(){return this->uShareEnableWeb_;}
std::string Configuration::getuShareEnableTelnet(){return this->uShareEnableTelnet_;}
std::string Configuration::getuShareEnableXbox(){return this->uShareEnableXbox_;}
std::string Configuration::getuShareEnableDlna(){return this->uShareEnableDlna_;}
