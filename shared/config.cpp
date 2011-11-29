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
    loadFromFile();
    loadFromDB();
}
Config::~Config()
{

}
void Config::loadFromFile()
{
  readFile(DEFAULT_CONFIG_PATH);
}
void Config::loadFromDB()
{

}
bool Config::parseFileData(const char* file_data)
{
    string str_config_params[SIZE_STR] =
        (
            "LSD_IP", "LSD_NAME", "LSD_USER", "LSD_PASSWORD", "LSD_CHARSET", "LSD_LOG_PATH",
            "LS_IP", "LS_DEMON_USER", "LS_DEMON_DIR", "LS_ERROR_LOG_PATH", "LS_SRV_LOG_PATH"
        );
    string int_config_params[SIZE_INT]  =
    {
        "LSD_PORT",
        "LS_DBG_LVL", "LS_PORT", "LS_NUM_EPOLLS_WORKER_THREADS", "LS_NUM_LOGIN_PROCCESSING_THREADS"
    };
    JSONValue *value = JSON::Parse(file_data);
    JSONObject root;
    ASSERT(value->isObject());
    root = value->asObject();
    for (uint i = 0; i < SIZE_STR; ++i)
    {
        JSONObject::iterator it = root.find(str_config_params[i]);
        if (it != root.end())
        {
            value = it->second;
            ASSERT(value->isString());
            _data_str[i] = value->asString();
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
            value = it->second;
            ASSERT(value->isNumber());
            _data_int[i] = value->asNumber();
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
    char *buf;

    fp=fopen(str_file.c_str(),"rb");
    if (fp)
    {
        fseek(fp, 0, SEEK_END); ///go to end
        len=ftell(fp); ///get position at end (length)
        fseek(fp, 0, SEEK_SET); ///go to begin.
        buf=(char *)malloc(len); ///malloc buffer
        fread(buf, len, 1, fp); ///read into buffer
        fclose(fp);
        this->parseFileData(buf);
        free(buf);
        tracelog(4, "Loading configuration file from = %s, success", str_file.c_str());
    }
    else
    {
        traceerr("Config file = %s, load error", str_file.c_str());
        return false;
    }
    return true;
}

