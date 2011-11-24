#include "config.h"

initialiseSingleton ( Config );

Config::Config()
{
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

