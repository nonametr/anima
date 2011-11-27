#include "config.h"

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

}

void Config::loadFromDB()
{

}

