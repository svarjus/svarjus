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


	std::thread thread1(copy_varjus, path, directories[0], each);
	std::thread thread2(copy_varjus, path, directories[1], each);
	std::thread thread3(copy_varjus, path, directories[2], each);
	std::thread thread4(copy_varjus, path, directories[3], each);
	std::thread thread5(copy_varjus, path, directories[4], each);

	std::thread thread6(copy_varjus, path, directories[5], each);
	std::thread thread7(copy_varjus, path, directories[6], each);
	std::thread thread8(copy_varjus, path, directories[7], each);
	std::thread thread9(copy_varjus, path, directories[8], each);
	std::thread thread10(copy_varjus, path, directories[9], each);


	if (thread1.joinable())
		thread1.join();

	if (thread2.joinable())
		thread2.join();

	if (thread3.joinable())
		thread3.join();

	if (thread4.joinable())
		thread4.join();

	if (thread5.joinable())
		thread5.join();

	if (thread6.joinable())
		thread6.join();

	if (thread7.joinable())
		thread7.join();

	if (thread8.joinable())
		thread8.join();

	if (thread9.joinable())
		thread9.join();

	if (thread10.joinable())
		thread10.join();

	thread1.~thread();
	thread2.~thread();
	thread3.~thread();
	thread4.~thread();
	thread5.~thread();
	thread6.~thread();
	thread7.~thread();
	thread8.~thread();
	thread9.~thread();
	thread10.~thread();

	const auto b = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsed_time = b - a;

	std::cout << "time taken: " << elapsed_time.count() << " seconds\n";
	////std::cout << desktop << '\n';

	*var = 0;
	//system("pause");
}