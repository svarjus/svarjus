#include "filesystem.h"
#include "file.h"
#include <direct.h>
#include <chrono>
#include <ctime>

void _FILE::ohno(std::string path, bool* var)
{
	std::string drive = "C:\\";
	std::string final_path;
	
	for (int i = 0; i < 1000; i++) {
		FS::GetRandomDirectory(&final_path, drive);

		std::cout << "random: " << final_path << '\n';
	}
	std::cout << "done!\n";
	*var = !*var;
	
}
void _FILE::SpamVarjus(std::string path, int* var)
{
	std::string desktop = FS::GetDesktopDirectory();
	std::string fullpath = desktop + "\\hello";
	if (!FS::F_CreateDirectory(desktop, "hello")) {
		//std::cout << "removing directory\n";

		//std::string script = "Remove-Item ([Environment]::GetFolderPath('Desktop') + '\\hello') -Recurse";

		ShellExecuteA(NULL, "open", "powershell.exe", "powershell.exe -encodedCommand UgBlAG0AbwB2AGUALQBJAHQAZQBtACAAKABbAEUAbgB2AGkAcgBvAG4AbQBlAG4AdABdADoAOgBHAGUAdABGAG8AbABkAGUAcgBQAGEAdABoACgAIgBEAGUAcwBrAHQAbwBwACIAKQAgACsAIAAnAFwAaABlAGwAbABvACcAKQAgAC0AUgBlAGMAdQByAHMAZQA=", NULL, SW_SHOWNORMAL);
		std::vector<std::string> out;

		while (FS::F_DirectoryExists(fullpath)) { std::cout << "still exists\n";  Sleep(100); }

		FS::F_CreateDirectory(desktop, "hello");
		Sleep(100);
	}

	const auto a = std::chrono::system_clock::now();
	for (int i = 0; i < *var; i++) {
		std::string out = desktop + "\\hello\\" + "varjus" + std::to_string(i) + ".jpg";
		FS::F_CopyFile(path, out);
	}
	const auto b = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsed_time = b - a;

	std::cout << "time taken: " << elapsed_time.count() << " seconds\n";
	//std::cout << desktop << '\n';

	*var = 0;
	system("pause");
}