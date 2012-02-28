#include "config.h"
#include "json.h"
#include "json_value.h"

initialiseSingleton ( Config );

Config::Config()
{
    for (uint32 i = 0; i < SIZE_STR; ++i)
    {
        _data_str[i] = string("");
    }
    for (uint32 i = 0; i < SIZE_INT; ++i)
    {
        _data_int[i] = 0;
    }
}
Config::~Config()
{

}
void Config::loadFromFile(const char *cfg_file)
{
    if (cfg_file == NULL)
        cfg_file = DEFAULT_CONFIG_PATH;
    readFile(cfg_file);
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
        "SSD_IP", "SSD_NAME", "SSD_USER", "SSD_PASSWORD", "SSD_CHARSET"
    };
    string int_config_params[SIZE_INT]  =
    {
        "SSD_PORT"
    };
    JSONValue *value = JSON::parse(file_data);
    JSONValue *second_value;
    JSONObject root;
    ASSERT(value->isObject());
    root = value->asObject();
    for (uint32 i = 0; i < SIZE_STR; ++i)
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
    for (uint32 i = 0; i < SIZE_INT; ++i)
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
            traceerr("Error loading configuration from file. Expected field \"%s\" not found.", int_config_params[i].c_str());
            continue;
        }
    }
    delete value;
    return true;
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

