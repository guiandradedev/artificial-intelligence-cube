#include "UI/UI.h"
#include "Tools/messages.h"

int main(int argc, char** argv) {
    header();
    std::string title = "Cubo 2x2";
    int w = 720;
    int h = 720;
    UI application(argc, argv, title, w, h);
    application.run();
    return 0;
}