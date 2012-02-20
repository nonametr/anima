#ifndef DICTJSONGENERATOR_H
#define DICTJSONGENERATOR_H

#include "./game_server/database_manager.h"
#include <string>
#include "./shared/common.h"

using namespace std;

class DictJSONGenerator
{
public:
    DictJSONGenerator();
    void generate();
private:
    string genSection(string section_name, string sql);
    MySQLDatabase *db;

    string dict_json_file_name;
};

#endif // DICTJSONGENERATOR_H
