#include "UI/UI.h"
#include "Tools/messages.h"

// Linux: g++ $(find src -name "*.cpp") -I ./includes -o programa -lGL -lGLU -lglut && ./programa

int main(int argc, char** argv) {
    header(true);

    srand(time(NULL));

    std::string title = "Cubo 2x2";
    int w = 720;
    int h = 720;
    UI application(argc, argv, title, w, h);
    application.run();
    return 0;
}