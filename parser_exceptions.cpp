#include <iostream>
#include <string>
#include <exception>
#include "parser_exceptions.h"
#include <cstring>

using namespace std;

exc_io::exc_io() {}
const char* exc_io::what(string msg)
{
    message = msg;
    return message.c_str();
}

exc_cfg_not_found_section::exc_cfg_not_found_section() {}
const char* exc_cfg_not_found_section::what(const char* section)
{
    return "There is no such section";
}

exc_cfg_not_found_param::exc_cfg_not_found_param() {}
const char* exc_cfg_not_found_param::what(const char* param)
{
    return "There is no such parameter";
}

exc_cfg_param_type::exc_cfg_param_type() {}
const char* exc_cfg_param_type::what(const char* type)
{
    //string str(type);
    //string msg = "This value can't be converted to";
    //msg += str;
    //return msg.c_str();
    return "This value can not be represented in this type";
}


