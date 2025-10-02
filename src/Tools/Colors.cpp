#include "Tools/Colors.h"
#include <iostream>

namespace Colors {
    const char* HEADER = "\033[95m";
    const char* OKBLUE = "\033[94m";
    const char* OKCYAN = "\033[96m";
    const char* OKGREEN = "\033[92m";
    const char* WARNING = "\033[93m";
    const char* FAIL = "\033[91m";
    const char* ENDC = "\033[0m";
    const char* BOLD = "\033[1m";
    const char* UNDERLINE = "\033[4m";

    void error(const std::string& message) { std::cout << FAIL << message << ENDC << std::endl; }
    void ok(const std::string& message) { std::cout << OKCYAN << message << ENDC << std::endl; }
    void success(const std::string& message) { std::cout << OKGREEN << message << ENDC << std::endl; }
    void warning(const std::string& message) { std::cout << WARNING << message << ENDC << std::endl; }
    void bold(const std::string& message) { std::cout << BOLD << message << ENDC << std::endl; }
    void underline(const std::string& message) { std::cout << UNDERLINE << message << ENDC << std::endl; }
    void header(const std::string& message) { std::cout << HEADER << message << ENDC << std::endl; }
    void info(const std::string& message) { std::cout << OKCYAN << message << ENDC << std::endl; }
}