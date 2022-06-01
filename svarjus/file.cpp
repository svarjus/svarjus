#include "filesystem.h"
#include "file.h"
#include <direct.h>
#include <chrono>
#include <ctime>
#include <thread>

void _FILE::ohno(std::string path, bool* var)
{
	std::string drive = "C:\\";
	std::string final_path;
	
	if (path.empty() || FS::GetFileExtension(path) == "No extension") {
		std::cout << "no folder path specified\n";
		return;
	}
	for (int i = 0; i < 1000000; i++) {
		FS::GetRandomDirectory(&final_path, drive);

		//FS::F_CopyFile(path, final_path + "\\varjus" + std::to_string(i) + ".jpg");

		printf("path: %s\n", final_path.c_str());
	}
	std::cout << "done!\n";
	*var = !*var;
	
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
			std::cout << "error: " << ex.what() << '\n';
		}
	}


}
void _FILE::SpamVarjus(std::string path, int* var)
{
	std::string desktop = FS::GetDesktopDirectory();
	std::string fullpath = desktop + "\\hello";

	std::vector<std::string> directories;
	FS::vecReset(&directories, 10);

	for (int i = 0; i < 10; i++)
		directories.push_back(desktop + "\\hello" + std::to_string(i));
	
	const auto start = std::chrono::system_clock::now();
	for(int i = 0; i < 10; i++)
		FS::F_RemoveDirectory(directories[i]);

	for (int i = 0; i < 10; i++)
		FS::F_CreateDirectory(directories[i]);

	for (int i = 0; i < 10; i++) {
		if (!FS::F_DirectoryExists(directories[i])) {
			std::cout << "failed to delete: " << directories[i] << '\n';
			return;
		}
	}
	const auto end = std::chrono::system_clock::now();
	std::chrono::duration<float> elapsed = end - start;

	std::cout << "time taken to delete and recreate: " << elapsed.count() << " seconds\n";

	int each = *var / 10;

	const auto a = std::chrono::system_clock::now();

	std::vector<std::thread> threads;
	threads.clear();
	threads.resize(10);
	threads.erase(threads.begin(), threads.end());

	for(int i = 0; i < 10; i++)
		threads[i] = std::thread(copy_varjus, path, directories[i], each);

	for (int i = 0; i < 10; i++)
		if (threads[i].joinable())
			threads[i].join();

	for (int i = 0; i < 10; i++)
		threads[i].~thread();

	const auto b = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsed_time = b - a;

	std::cout << "time taken: " << elapsed_time.count() << " seconds\n";
	////std::cout << desktop << '\n';

	*var = 0;
	//system("pause");
}