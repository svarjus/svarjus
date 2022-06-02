#include "filesystem.h"
#include "file.h"
#include <direct.h>
#include <chrono>
#include <ctime>
#include <thread>
#include "log.h"


void varjus_c_drive(std::string path, std::string filename)
{
	std::string drive = "C:\\";
	std::string final_path;

	if (path.empty() || FS::GetFileExtension(path) == "No extension") {
		_log.AddLog("no folder path specified\n");
		return;
	}
	for (int i = 0; i < 1000000; i++) {

		if (!FS::GetRandomDirectory(&final_path, drive))
			break;

		try {
			FS::F_CopyFile(path, final_path + "\\" + filename + std::to_string(i) + ".jpg");
		}
		catch (std::exception& ex) {
			_log.AddLog("ERROR: %s\n", ex.what());
			continue;
		}
		//_log.AddLog("path: %s\n", final_path.c_str());
	}
}
void _FILE::ohno(std::string path, bool* var)
{
	int thread_count = 5;
	std::vector<std::thread> threads;

	threads.clear();
	threads.resize(thread_count);
	threads.erase(threads.begin(), threads.end());

	std::vector<std::string> names;
	FS::vecReset(&names, thread_count);

	
	for (int i = 0; i < thread_count; i++) {
		std::string randomname;
		FS::CreateRandomString((rand() % 40) + 20, &randomname);
		names.push_back(randomname);
	}


	for (int i = 0; i < thread_count; i++)
		threads.push_back(std::thread(varjus_c_drive, path, names[i]));

	for (int i = 0; i < thread_count; i++)
		if (threads[i].joinable())
			threads[i].join();

	for (int i = 0; i < thread_count; i++)
		threads[i].~thread();


	_log.AddLog("done!\n");
	*var = false;
	
}
void copy_varjus(std::string original_file_path, std::string out_file_path, UINT iterations)
{


	for (UINT i = 0; i < iterations; i++) {
		std::string randomname;
		FS::CreateRandomString((rand() % 50) + 20, &randomname);
		randomname += ".jpg";

		try {
			FS::F_CopyFile(original_file_path, out_file_path + "\\" + randomname);
		}
		catch (std::exception& ex) {
			_log.AddLog("error: %s\n", ex.what());
		}
	}


}
void _FILE::SpamVarjus(std::string path, int* var, int* folders)
{
	if (*var < *folders) {
		_log.AddLog("ERROR: iterations [%i] < folders[%i]\n", *var, *folders);
		return;
	}

	else if (*folders < 1) {
		_log.AddLog("ERROR: folders [%i] < 1\n", *folders);
		return;
	}
	
	std::string desktop = FS::GetDesktopDirectory();
	std::string fullpath = desktop + "\\hello";

	std::vector<std::string> directories;
	FS::vecReset(&directories, *folders);

	for (int i = 0; i < *folders; i++)
		directories.push_back(desktop + "\\hello" + std::to_string(i));
	
	const auto start = std::chrono::system_clock::now();
	for(int i = 0; i < *folders; i++)
		FS::F_RemoveDirectory(directories[i]);

	for (int i = 0; i < *folders; i++)
		FS::F_CreateDirectory(directories[i]);

	for (int i = 0; i < *folders; i++) {
		if (!FS::F_DirectoryExists(directories[i])) {
			_log.AddLog("failed to delete: %s", directories[i].c_str());
			return;
		}
		_log.AddLog("directory[%i]: %s\n", i, directories[i].c_str());
	}
	const auto end = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsed = end - start;

	_log.AddLog("time taken to delete and recreate: %.5f seconds\n", elapsed.count());

	int each = *var / *folders;

	const auto a = std::chrono::system_clock::now();

	std::vector<std::thread> threads;
	threads.clear();
	threads.resize(*folders);
	threads.erase(threads.begin(), threads.end());

	for(int i = 0; i < *folders; i++)
		threads.push_back(std::thread(copy_varjus, path, directories[i], each));

	for (int i = 0; i < *folders; i++)
		if (threads[i].joinable())
			threads[i].join();

	for (int i = 0; i < *folders; i++)
		threads[i].~thread();

	const auto b = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsed_time = b - a;

	_log.AddLog("time taken: %.5f seconds\n", elapsed_time.count());
	////std::cout << desktop << '\n';

	*var = 0;
	*folders = 0;
	//system("pause");
}