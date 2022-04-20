#include <fxcg/display.h>
#include <fxcg/keyboard.h>
 
int main(void) {
    int key;

    PrintXY(1,1,"  Hello", TEXT_MODE_NORMAL, TEXT_COLOR_RED);
    PrintXY(1,1,"  World", TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);

    while (1) {
        GetKey(&key);
    }
 
    return 0;
}
