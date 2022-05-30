#include "filesystem.h"
#include "keys.h"

char KEY::keyPressed()
{
    for (int i = 0x20; i < 0x5B; i++)
        if (GetAsyncKeyState(i) & 1)
            return (char)i;
    if (GetAsyncKeyState(VK_SPACE) & 1)
        return (char)VK_SPACE;

    return 0;
}
void KEY::ReadKeys()
{
    while (!false) {
        char key = keyPressed();

        if (key > 1)
            std::cout << key;
    }
}
