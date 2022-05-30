#include "filesystem.h"

template <typename t>
void FS::vecReset(std::vector<t>* vec, size_t size)
{
	vec->clear();
	vec->resize(size);
	vec->erase(vec->begin(), vec->end());
}


bool FS::F_SubDirectoriesInDirectory(std::string directory, std::vector<std::string>* out)
{
	vecReset(&(*out), 10000);
	int i{ 0 };
	if (!fs::exists(directory)) {
		out->push_back(directory);
		return false;
	}
	for (const auto& entry : fs::directory_iterator(directory)) {
		if (entry.is_directory()) {
			out->push_back(entry.path().string());
			i += 1;
		}
	}
	out->resize(i);

	return out->size() > 0;
}
void FS::GetRandomDirectory(std::string* out, std::string start_path)
{
	std::vector<std::string> vec;
	vecReset<std::string>(&vec, 10000);
	*out = start_path;
	if (!F_SubDirectoriesInDirectory(start_path, &vec)) {
		std::cout << "directory does not exist.. aborting\n";
		return;
	}
	std::string thispath = start_path;
	int directory{};

	while (true) {
		directory = rand() % vec.size();

		thispath = vec[directory];

		//vecReset<std::string>(&vec, 20000);

		if (F_SubDirectoriesInDirectory(thispath, &vec)) {
			directory = rand() % vec.size();
			thispath = vec[directory];
			continue;
		}
		break;
	}

	*out = thispath;
}
std::string FS::GetFileExtension(std::string file)
{

	int extensionPos = file.find_last_of(".");

	if (extensionPos < 0)
		return "No extension";

	file = file.substr(extensionPos);


	return file;
}
std::string FS::removeFileExtension(std::string file, size_t chars)
{
	return file.substr(0, file.size() - chars);
}