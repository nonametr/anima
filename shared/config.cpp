#include "config.h"
#include "../shared/json.h"
#include "../shared/jsonvalue.h"

initialiseSingleton ( Config );

Config::Config()
{
    for (uint i = 0; i < SIZE_STR; ++i)
    {
        _data_str[i] = string("");
    }
    for (uint i = 0; i < SIZE_INT; ++i)
    {
        _data_int[i] = 0;
    }
    _data_int[LS_DBG_LVL] = GODLIKE;
}
Config::~Config()
{

}
void Config::loadFromFile()
{
    readFile(DEFAULT_CONFIG_PATH);
    parseFileData(buf);
    free(buf);
}
void Config::loadFromDB()
{

}
bool Config::parseFileData(const char* file_data)
{
    string str_config_params[SIZE_STR] =
    {
        "LSD_IP", "LSD_NAME", "LSD_USER", "LSD_PASSWORD", "LSD_CHARSET", "LSD_LOG_PATH",
        "LS_IP", "LS_DEMON_USER", "LS_DEMON_DIR", "LS_ERROR_LOG_PATH", "LS_SRV_LOG_PATH"
    };
    string int_config_params[SIZE_INT]  =
    {
        "LSD_PORT",
        "LS_DBG_LVL", "LS_PORT", "LS_NUM_EPOLLS_WORKER_THREADS", "LS_NUM_LOGIN_PROCCESSING_THREADS"
    };
    JSONValue *value = JSON::Parse(file_data);
    JSONValue *second_value;
    JSONObject root;
    ASSERT(value->isObject());
    root = value->asObject();
    for (uint i = 0; i < SIZE_STR; ++i)
    {
        JSONObject::iterator it = root.find(str_config_params[i]);
        if (it != root.end())
        {
            second_value = it->second;
            ASSERT(second_value->isString());
            _data_str[i] = second_value->asString();
            tracelog(OPTIMAL, "Loading configuration param \"%s\" ---> \"%s\"", str_config_params[i].c_str(), _data_str[i].c_str());
        }
        else
        {
            traceerr("Error loading configuration from file. Expected field \"%s\" not found.", str_config_params[i].c_str());
            continue;
        }
    }
    for (uint i = 0; i < SIZE_INT; ++i)
    {
        JSONObject::iterator it = root.find(int_config_params[i]);
        if (it != root.end())
        {
            second_value = it->second;
            ASSERT(second_value->isNumber());
            _data_int[i] = second_value->asNumber();
            tracelog(OPTIMAL, "Loading configuration param \"%s\" ---> \"%u\"", int_config_params[i].c_str(), _data_int[i]);
        }
        else
        {
            traceerr("Error loading configuration from file. Expected field \"%s\" not found.", str_config_params[i].c_str());
            continue;
        }
    }
    delete value;
}
bool Config::readFile(const string str_file)
{
    FILE *fp;
    int len;

    fp=fopen(str_file.c_str(),"rb");
    if (fp)
    {
        fseek(fp, 0, SEEK_END); ///go to end
        len=ftell(fp) + 2; ///get position at end (length) + reserved 2 bytes
        fseek(fp, 0, SEEK_SET); ///go to begin.
        buf=(char *)malloc(len); ///malloc buffer
        memset(buf, 0, len);
        fread(buf, len, 1, fp); ///read into buffer
        fclose(fp);
        tracelog(4, "Loading configuration file from = %s", str_file.c_str());
    }
    else
    {
        traceerr("Config file = %s, load error", str_file.c_str());
        exit(-1);
    }
    return true;
}

