#pragma once

#pragma comment(lib, "Urlmon.lib")
#include <windows.h>
#include <cstdio>

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <Shlobj.h>
#include <ShlObj_core.h>
#include <fstream>
#include "log.h"
namespace fs = std::filesystem;
constexpr int MAX_VEC_SIZE = 20;
#ifndef thisfilesystem
#define thisfilesystem
namespace FS
{
	std::string GetExeFileName();
	std::string GetExePath();

	void F_Main(std::string* PATH, bool* var);
	bool F_WriteFile(std::string directory);

	bool F_CopyFile(std::string from, std::string to);
	bool F_DownloadFile(std::string url, std::string filename);
	void F_GetAppDataRoaming(std::string* out);
	std::string F_GetAppDataRoaming(std::string buffer);
	void GetRandomDirectory(std::string* out, std::string start_path);

	bool F_SubDirectoriesInDirectory(std::string directory, std::vector<std::string>* out);
	bool F_DirectoryExists(std::string directory_path);
	template<typename t> 
	void vecReset(std::vector<t>* vec, size_t size);

	void GoToPreviousDirectory(std::string* directory);
	std::string GoToPreviousDirectory(std::string directory);

	std::string GetFileExtension(std::string file);
	std::string removeFileExtension(std::string file, size_t chars);
	char GetRandomAlNumCharacter();
	void CreateRandomString(UINT characters, std::string* out);

	enum class fileopen
	{
		FILE_IN = 1,
		FILE_OUT = 2,
		FILE_APP = 8,
		FILE_BINARY = 32
	};

	bool F_OpenFile(std::fstream* fp, std::string path, fileopen type);
	bool F_CloseFile(std::fstream* fp);
	bool F_WriteToFile(std::fstream* fp, std::string text);
	bool F_WriteToFile(std::fstream* fp, char text);

	bool F_CreateDirectory(std::string path);
	bool F_CreateFile(std::string directory, std::string path);

	template<typename t> void F_FilesInThisDirectory(std::string directory, std::vector<t>* out);
	bool F_DeleteFilesFromDirectory(std::string directory);
	bool F_RemoveDirectory(std::string directory);

	std::string GetDesktopDirectory();


}
#endif
