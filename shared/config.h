#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "singleton.h"
#include "common.h"

#define DEFAULT_CONFIG_PATH "/home/nonametr/projects/anima/build/anima.cfg"
/**
 * @brief server configuration data store
 **/
class Config : public Singleton<Config>
{
public:
    /**
     * @brief all string params of server configuration discribed in this enum
     **/
    enum CONFIG_PARAMS_STR
    {
        ///database connection configuration for login server. LSD = LOGIN SERVER DATABASE
        SSD_IP, SSD_NAME, SSD_USER, SSD_PASSWORD, SSD_CHARSET, SIZE_STR
    };
    /**
     * @brief all int params of server configuration discribed in this enum
     **/
    enum CONFIG_PARAMS_INT
    {
        ///database connection configuration for login server. LSD = LOGIN SERVER DATABASE
        SSD_PORT, SIZE_INT
    };
    /**
     * @brief constructor performs loading all configurations params
     *
     **/
    Config();
    virtual ~Config();
    /**
     * @brief performs loading base configuration data from config file
     *
     * @return void
     **/
    void loadFromFile(const char *cfg_file);
    /**
     * @brief performs loading configuration data from database
     *
     * @return void
     **/
    void loadFromDB();
    const int &getParam ( CONFIG_PARAMS_INT int_param )
    {
        return _data_int[int_param];
    };
    const std::string &getParam ( CONFIG_PARAMS_STR str_param )
    {
        return _data_str[str_param];
    };
private:
    bool readFile(const string str_file);
    bool parseFileData(const char* file_data);
  
    char *buf;
    
    std::string _data_str[SIZE_STR];
    int _data_int[SIZE_INT];
};

#define iConfig Config::getSingletonPtr()
#endif // CONFIG_H
