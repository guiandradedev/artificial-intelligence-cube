#include "UI/UI.h"
#include "Tools/messages.h"
#include "Tools/RGB.h"

// Linux: g++ $(find src -name "*.cpp") -I ./includes -o programa -lGL -lGLU -lglut && ./programa

// U, L, U, F, U, F, L, U, L, L, U, L, U, L, U, L, U
int main(int argc, char** argv) {
    header(true);

    srand(time(NULL));
    
    std::string title = "Cubo 2x2";
    int w = 720;
    int h = 720;
    UI::UIDetails window_details = {title, w, h, white};

    UI application(argc, argv, window_details);
    application.run();
    return 0;
}