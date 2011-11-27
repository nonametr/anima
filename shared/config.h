#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include "singleton.h"

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
        LSD_IP, LSD_NAME, LSD_USER, LSD_PASSWORD, LSD_CHARSET, LSD_LOG_PATH,
        ///login server general configuration, this configuration loads from LSD
        LS_IP, LS_DEMON_USER, LS_DEMON_DIR, LS_ERROR_LOG_PATH, LS_SRV_LOG_PATH, SIZE_STR
    };
    /**
     * @brief all int params of server configuration discribed in this enum
     **/
    enum CONFIG_PARAMS_INT
    {
        ///database connection configuration for login server. LSD = LOGIN SERVER DATABASE
        LSD_PORT,
        ///login server general configuration, this configuration loads from LSD
        LS_DBG_LVL, LS_PORT, SIZE_INT
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
    void loadFromFile();
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
    std::string _data_str[SIZE_STR];
    int _data_int[SIZE_INT];
};

#define iConfig Config::getSingletonPtr()
#endif // CONFIG_H
