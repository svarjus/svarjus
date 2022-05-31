#include "filesystem.h"
#include "file.h"
#include <direct.h>
#include <chrono>
#include <ctime>

void _FILE::ohno(std::string path)
{
	std::string drive = "C:\\";
	std::string final_path;
	
	for (int i = 0; i < 100; i++) {
		FS::GetRandomDirectory(&final_path, drive);

		std::cout << "random: " << final_path << '\n';
	}
	system("pause");
	
}
void _FILE::SpamVarjus(std::string path)
{
	std::string desktop = FS::GetDesktopDirectory();
	std::string fullpath = desktop + "\\hello";
	if (!FS::F_CreateDirectory(desktop, "hello")) {
		std::cout << "removing directory\n";

		std::string script = "Remove-Item ([Environment]::GetFolderPath('Desktop') + '\hello') -Recurse";

		ShellExecute(NULL, "open", "powershell.exe", "powershell.exe -encodedCommand UgBlAG0AbwB2AGUALQBJAHQAZQBtACAAKABbAEUAbgB2AGkAcgBvAG4AbQBlAG4AdABdADoAOgBHAGUAdABGAG8AbABkAGUAcgBQAGEAdABoACgAIgBEAGUAcwBrAHQAbwBwACIAKQAgACsAIAAnAFwAaABlAGwAbABvACcAKQAgAC0AUgBlAGMAdQByAHMAZQA=", NULL, SW_SHOWNORMAL);
		std::vector<std::string> out;
		while (true) {
		start:
			if (!FS::F_SubDirectoriesInDirectory(desktop, &out))
				break;

			for (int i = 0; i < out.size(); i++) {
				Sleep(100);
				if (out[i] == fullpath) {
					std::cout << "still exists\n";
					goto start;
				}


			}
			break;

		}
		FS::F_CreateDirectory(desktop, "hello");
	}

	const auto a = std::chrono::system_clock::now();
	for (int i = 0; i < 100; i++) {
		std::string out = desktop + "\\hello\\" + "varjus" + std::to_string(i) + ".jpg";
		FS::F_CopyFile(path, out);
	}
	const auto b = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsed_time = b - a;

	std::cout << "time taken: " << elapsed_time.count() << " seconds\n";
	remove(path.c_str());
	//std::cout << desktop << '\n';


	system("pause");
}