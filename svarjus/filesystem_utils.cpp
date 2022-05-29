#include "filesystem.h"

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