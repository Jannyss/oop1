#ifndef PARSER_EXCEPTIONS_H_INCLUDED
#define PARSER_EXCEPTIONS_H_INCLUDED
#endif // PARSER_EXCEPTIONS_H_INCLUDED

#pragma once
#include <string>
#include <exception>

using namespace std;

class exc_io: public exception {
public:
    exc_io();
    const char *what(string msg);
private:
    string message;
};

class exc_cfg_not_found_section: public exception {
public:
    exc_cfg_not_found_section();
    const char *what(const char* section);
private:
    const char* message;
};

class exc_cfg_not_found_param: public exception {
public:
    exc_cfg_not_found_param();
    const char *what(const char* param);
private:
    const char* message;
};

class exc_cfg_param_type: public exception {
public:
    exc_cfg_param_type();
    const char *what(const char* type);
private:
    const char* message;
};
