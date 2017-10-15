#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <vector>


using namespace std;
#include "IniParser.h"

IniParser::IniParser()
{
    cout << "Write a filename" << endl;
    cin >> filename;
}


IniParser::IniParser(const char* filename_cstr)
{
    filename = filename_cstr;
    IniParser::Initialize(filename_cstr);
}

IniParser::~IniParser() {}

void IniParser::Initialize(const char* filename_cstr) const throw (exc_io)
{
    try
    {
        ifstream conf_file;
        string str(filename_cstr);
        int dot = str.find('.');
        if (str.substr(dot+1, str.length()) != "ini")
            {
                throw exc_io();
            }
        conf_file.open(filename_cstr);
    }
    catch (exc_io)
    {
        cout << exc_io().what("Error format of file");
    }
}

void IniParser::Parser()
{
    IniParser::Initialize(filename.c_str());
    ifstream conf_file;
    conf_file.open(filename);
    string line;
    vector<string> lines;
    string sect;

    while (!conf_file.eof()) {
        getline(conf_file, line);
        int pos_of_comment = -1;
        pos_of_comment = line.find(';');
        if (pos_of_comment != -1) {
            line = line.substr(0, pos_of_comment);
            lines.push_back(line);
        }

        if ((line[0] == '[') && (line[line.length()-1] == ']')) {
            line = line.substr(1, line.length()-2);
            sections.insert (make_pair(line, Params()));
            sect = line;
        }
//        if ((!line.empty()) && !(line == "\n") && !(line == " ") && (line[0] != '[')) {
//        if (line.find('=') != 0) {
        string field, value_string;
        int pos_of_equal = -1;
        pos_of_equal = line.find("=");

        if (pos_of_equal != -1) {

            field = line.substr(0, pos_of_equal-1);
            field.erase(remove(field.begin(), field.end(), ' '), field.end());

            value_string = line.substr(pos_of_equal+2, line.length()-1);
            value_string.erase(remove(value_string.begin(), value_string.end(), ' '), value_string.end());

            sections[sect].insert(make_pair(field, value_string));
            }
        }
}

bool IniParser::IsHaveSection(const char* section_name) throw (exc_cfg_not_found_section)
{
    try {
        IniParser::Parser();
        if (sections.count(section_name) > 0)
            return true;
        else
            throw exc_cfg_not_found_section();
    }
    catch (exc_cfg_not_found_section) {
        cout << exc_cfg_not_found_section().what(section_name) << endl;
        return false;
    }
}

bool IniParser::IsHaveParam(const char* section_name, const char* param_name) throw (exc_cfg_not_found_section, exc_cfg_not_found_param)
{
    if (IsHaveSection(section_name)) {
        try {
            if ((sections.find(section_name)->second).count(param_name) > 0)
                return true;
            else
                throw exc_cfg_not_found_param();
        }
        catch (exc_cfg_not_found_param)
        {
            cout << exc_cfg_not_found_param().what(param_name) << endl;
            return false;
        }
    }

}

int IniParser::GetValueInt(const char* section_name, const char* param_name) throw (exc_cfg_param_type)
{
    if (IsHaveSection(section_name)) {
        if (IsHaveParam(section_name, param_name)) {
            try {
                string value = (sections.find(section_name)->second).find(param_name)->second;
                int value_int = atoi(value.c_str());
                double value_double = atof(value.c_str());
                if ((value.find(".") != -1) && (value_int == value_double)) throw exc_cfg_param_type();
                else {
                    if ((value_int == 0) && (value != "0")) throw exc_cfg_param_type();
                    else
                        cout << value_int;
                }
            }
            catch (exc_cfg_param_type) {cout << exc_cfg_param_type().what("integer");}
        }
    }
}

double IniParser::GetValueDouble(const char* section_name, const char* param_name) throw (exc_cfg_param_type)
{
    if (IsHaveSection(section_name)) {
        if (IsHaveParam(section_name, param_name)) {
            try {
                string value = (sections.find(section_name)->second).find(param_name)->second;
                int value_int = atoi(value.c_str());
                double value_double = atof(value.c_str());
                if ((value_double == value_int) && (value.find(".") == -1)) throw exc_cfg_param_type();
                else {
                    if ((value_double == 0) && (value != "0")) throw exc_cfg_param_type();
                    else
                        cout << value_double;
                }
            }
            catch (exc_cfg_param_type) {cout << exc_cfg_param_type().what("double"); }
        }
    }
}

string IniParser::GetValueString(const char* section_name, const char* param_name) throw (exc_cfg_param_type)
{
    if (IsHaveSection(section_name)) {
        if (IsHaveParam(section_name, param_name)) {
            try {
                string value = (sections.find(section_name)->second).find(param_name)->second;
                int value_int = atoi(value.c_str());
                if (((value_int == 0) || (value.find(".") == -1)) && (value != "0")) cout << value;
                    else throw exc_cfg_param_type();
            }
            catch (exc_cfg_param_type) {cout << exc_cfg_param_type().what("string"); }
        }
    }
}

template <typename K, typename V, class C, class A>         // code for nice viewing maps from
ostream &operator<< (ostream &os, map<K,V,C,A> const& m)    // https://ubuntuforums.org/showthread.php?t=641221
{
	os << "{ " << endl;
	typename map<K,V,C,A>::const_iterator p;
	for (p = m.begin(); p != m.end(); ++p) {
		os << p->first << ":" << p->second << ", " << endl;
	}
	return os << "}" << endl;
}

void IniParser::ShowFullFile()
{
    Parser();
    cout << sections << endl;
}
