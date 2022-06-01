#include "filesystem.h"
#include <direct.h>
std::string FS::GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}
std::string FS::GetExePath()
{
	std::string f = GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}
void FS::F_GetAppDataRoaming(std::string* out)
{
	char* name;
	size_t len;
	_dupenv_s(&name, &len, "APPDATA");

	*out = name;
}
std::string FS::F_GetAppDataRoaming(std::string buffer)
{
	F_GetAppDataRoaming(&buffer);

	return buffer;
}
bool FS::F_CopyFile(std::string from, std::string to)
{
	fs::copy(from, to);

	return true;
}
bool FS::F_DownloadFile(std::string url, std::string dst)
{
	return (URLDownloadToFile(NULL, url.c_str(), dst.c_str(), 0, NULL) == S_OK);
}

void FS::GoToPreviousDirectory(std::string* directory)
{
	size_t pos = directory->find_last_of('\\');

	if (pos > 0)
		*directory = directory->substr(0, pos) + '\\';
}
std::string FS::GoToPreviousDirectory(std::string directory)
{
	size_t pos = directory.find_last_of('\\');
	if (pos < 1)
		return directory;

	return directory.substr(0, pos);
}
char FS::GetRandomAlNumCharacter()
{
	unsigned char ch{};
	int ran{};
	while (true) {
		ran = (rand() % 253) + 1;
		ch = (char)ran;
		
		if (std::isalnum(ch))
			return (char)ch;
	}
	return (char)97; //lowercase a
}
void FS::CreateRandomString(UINT characters, std::string* out)
{

	for (UINT i = 0; i < characters; i++) {
		out->push_back(GetRandomAlNumCharacter());
	}
}
bool FS::F_OpenFile(std::fstream* fp, std::string path, fileopen type)
{


	if (fp->is_open())
		return true;

	switch (type)
	{
	case FS::fileopen::FILE_IN:
		fp->open(path, std::ios_base::in);
		break;
	case FS::fileopen::FILE_OUT:
		fp->open(path, std::ios_base::out);
		break;
	case FS::fileopen::FILE_APP:
		fp->open(path, std::ios_base::out);
		break;
	case FS::fileopen::FILE_BINARY:
		fp->open(path, std::ios_base::binary);
		break;
	default:
		return false;
	}


	if (!fp->is_open()) {
		_log.AddLog("failed to open file!\n");
		_log.AddLog("%s\n", path.c_str());
		return false;
	}

	return true;
}
bool FS::F_CloseFile(std::fstream* fp)
{
	if (fp->is_open())
		fp->close();

	if (fp->is_open()) //this should not be possible..?
		return false;
	

	return true;
}
bool FS::F_WriteToFile(std::fstream* fp, std::string text)
{
	if (!fp->is_open())
		return false;

	*fp << text.c_str();

	return true;
}
bool FS::F_WriteToFile(std::fstream* fp, char text)
{
	if (!fp->is_open())
		return false;

	fp->put(text);

	return true;
}
bool FS::F_CreateDirectory(std::string path)
{
	return _mkdir((path).c_str()) != -1;
}
bool FS::F_CreateFile(std::string directory, std::string path)
{
	char* name;
	size_t len;
	_dupenv_s(&name, &len, "DESKTOP");

	_log.AddLog("desktop: %s\n", name);

	return 1;
}
std::string FS::GetDesktopDirectory()
{
	char* name;
	size_t len;
	_dupenv_s(&name, &len, "UserProfile");

	std::string desktop = (const char*)name;
	desktop += "\\Desktop";

	return desktop;
}
template<typename t>
void FS::F_FilesInThisDirectory(std::string directory, std::vector<t>* out)
{
	vecReset(&(*out), 4096 * 3);
	int i{ 0 };
	if (!fs::exists(directory)) {
		return;
	}
	for (const auto& entry : fs::directory_iterator(directory)) {
		if (entry.is_directory())
			continue;

		out->push_back(entry.path().string());
		i += 1;
	}
	out->resize(i);
}
bool FS::F_DeleteFilesFromDirectory(std::string directory)
{
	std::vector<std::string> files;
	F_FilesInThisDirectory(directory, &files);

	if (files.size() < 1)
		return false;

	else if (fs::is_empty(directory)) {
		_log.AddLog("directory is empty\n");
		return true;
	}

	for (int i = 0; i < files.size(); i++) 
		fs::remove(files[i]);
	
	return true;
	
}
bool FS::F_RemoveDirectory(std::string directory) //only removes files and NOT subfolders
{
	if (FS::F_DeleteFilesFromDirectory(directory)) {
		fs::remove(directory);
		return true;
	}
	return false;
}