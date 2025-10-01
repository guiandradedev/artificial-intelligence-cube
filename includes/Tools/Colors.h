#pragma once
#include <string>

namespace Colors {
    //Cores apenas para imprimir no terminal
    extern const char* HEADER;
    extern const char* OKBLUE;
    extern const char* OKCYAN;
    extern const char* OKGREEN;
    extern const char* WARNING;
    extern const char* FAIL;
    extern const char* ENDC;
    extern const char* BOLD;
    extern const char* UNDERLINE;
    
    void error(const std::string& message);
    void ok(const std::string& message);
    void success(const std::string& message);
    void warning(const std::string& message);
    void bold(const std::string& message);
    void underline(const std::string& message);
    void header(const std::string& message);
    void info(const std::string& message);
}