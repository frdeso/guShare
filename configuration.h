#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <string>
#include <vector>
#define NUMBEROFARGUMENT 10
class Configuration{
public:
  Configuration();
  ~Configuration();
  void ReadConfigFile(std::string path);
  void WriteConfigFile(std::string path);
  void AnalyseLine(std::string line);
  void setArguments(std::string arg, std::string value);
  std::vector<std::string> *getFolderList();
  
  std::string getuShareName();
  std::string getuShareIFace();
  std::string getuSharePort();
  std::string getuShareTelnetPort();
  std::string getuShareOverrideIConvErr();
  std::string getuShareEnableWeb();
  std::string getuShareEnableTelnet();
  std::string getuShareEnableXbox();
  std::string getuShareEnableDlna();
  
private:
  std::string ReadOneLine(std::string path);
  std::string uShareName_;
  std::string uShareIFace_;
  std::string uSharePort_;
  std::string uShareTelnetPort_;
  std::vector<std::string> *folderList_;
  std::string uShareOverrideIConvErr_;
  std::string uShareEnableWeb_;
  std::string uShareEnableTelnet_;
  std::string uShareEnableXbox_;
  std::string uShareEnableDlna_;
};
#endif //configuration