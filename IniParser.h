#ifndef INIPARSER_H_INCLUDED
#define INIPARSER_H_INCLUDED


#pragma once
#endif // INIPARSER_H_INCLUDED

#include <map>
#include <string>
#include "parser_exceptions.cpp"
using namespace std;


class IniParser {
public:
    IniParser();
    IniParser(const char* filename_cstr);
    ~IniParser();
    void Initialize(const char* filename_cstr) const
        throw (exc_io);

    void Parser();

    bool IsHaveSection(const char* section_name) const
        throw (exc_cfg_not_found_section);

    bool IsHaveParam(const char* section_name, const char* param_name) const
        throw (exc_cfg_not_found_section, exc_cfg_not_found_param);

//    int GetValueInt(const char* section_name, const char* param_name) const
//        throw (exc_cfg_param_type);
//
//    double GetValueDouble(const char* section_name, const char* param_name) const
//        throw (exc_cfg_param_type);
//
//    string GetValueString(const char* section_name, const char* param_name) const
//        throw (exc_cfg_param_type);

    template<typename T>
    T GetValue(const char* section_name, const char* param_name) const
        throw (exc_cfg_param_type);

    void ShowFullFile();

private:
    typedef map<string, string> Params;
    typedef map<string, Params> Section;
    Section sections;
    string filename="";
};
