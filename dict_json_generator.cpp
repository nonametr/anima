#include "dict_json_generator.h"
#include "./shared/json_value.h"

#define SQL_DICT_AIRCRAFT "SELECT * from dict_aircraft"
#define SQL_DICT_BUILDINGS "SELECT * from dict_building"
#define SQL_DICT_PSI "SELECT * from dict_psi"
#define SQL_DICT_WEAPON "SELECT * from dict_weapon"
#define SQL_DICT_WEAPON_CLIP "SELECT * from dict_weapon_clip"
#define SQL_DICT_ITEM "SELECT * from dict_item"
#define SQL_DICT_MULTILANGUAGE "SELECT * from dict_multilanguage"
#define SQL_DICT_NEED_ITEM "SELECT * from dict_need_item"
#define SQL_DICT_SOLDIER "SELECT * from dict_soldier"
#define SQL_DICT_RESEACH "SELECT * from dict_research"
#define SQL_DICT_WORKSHOP "SELECT * from dict_workshop"
#define SQL_DICT_ARMOR "SELECT * from dict_armor"

DictJSONGenerator::DictJSONGenerator()
{
    dict_json_file_name = "dict_json.html";
    db = iDBManager->getSSDatabase();
    generate();
}

string DictJSONGenerator::genSection(string section_name, string sql)
{
    string json = {"\0"};
    Field *field;

    shared_ptr<QueryResult> qres(db->queryNA(sql.c_str()));
    if (!qres.get())
        return "";
    json += "\"";
    json += section_name;
    json += "\":[";
    do
    {
        field = qres->fetch();
        json += "{\"obj\":[";
        for (uint i = 0; i < qres->getFieldCount(); ++i)
        {
            json += "\"";
	    json += field[i].getString();
            json += "\"";
            if (i != qres->getFieldCount() - 1)
                json += ",";
        }
        json += "]},";
    }
    while (qres->nextRow());
    json.erase(json.length() - 1, 1);
    json += "],";
    return json;
}

void DictJSONGenerator::generate()
{
    string json = {"\0"};
    json += "{";
    json += genSection("aircraft", SQL_DICT_AIRCRAFT);
    json += genSection("building", SQL_DICT_BUILDINGS);
    json += genSection("psi", SQL_DICT_PSI);
    json += genSection("weapon", SQL_DICT_WEAPON);
    json += genSection("weapon_clip", SQL_DICT_WEAPON_CLIP);
    json += genSection("soldier", SQL_DICT_SOLDIER);
    json += genSection("item", SQL_DICT_ITEM);
    json += genSection("multilanguage", SQL_DICT_MULTILANGUAGE);
    json += genSection("need_item", SQL_DICT_NEED_ITEM);
    json += genSection("research", SQL_DICT_RESEACH);
    json += genSection("workshop", SQL_DICT_WORKSHOP);
    json += genSection("armor", SQL_DICT_ARMOR);
    json.erase(json.length() - 1, 1);
    json += "}";

    FILE* json_file = fopen(dict_json_file_name.c_str(), "w");
    if (json_file)
    {
        fprintf(json_file, "%s", json.c_str());
        fclose(json_file);
    }
}

