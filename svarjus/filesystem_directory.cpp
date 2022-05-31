#include "filesystem.h"

template <typename t>
void FS::vecReset(std::vector<t>* vec, size_t size)
{
	vec->clear();
	vec->resize(size);
	vec->erase(vec->begin(), vec->end());
}

bool hasperms(fs::perms p)
{
	return (p & fs::perms::owner_write) != fs::perms::none;

}
bool FS::F_SubDirectoriesInDirectory(std::string directory, std::vector<std::string>* out)
{
	bool hasFailed{ false };
	vecReset(&(*out), 10000);
	int i{ 0 };
	
	int permission = (int)(fs::perms)(fs::status(directory).permissions());

	//std::cout << "permission: " << permission << '\n';
	if (!hasperms(fs::status(directory).permissions())) {
		//std::cout << "no permission\n";
		return false;
	}

	if (!fs::exists(directory)) {
		out->resize(0);
		return false;
	}
	try {
		for (const auto& entry : fs::directory_iterator(directory)) {
			if (hasFailed)
				return false;
			if (entry.is_directory() && entry.exists()) {
				out->push_back(entry.path().string());
				i += 1;
			}
		}
	}
	catch (std::exception& ex) {
		//std::cout << "error: " << ex.what() << '\n';
		out->resize(0);
		hasFailed = true;
		return false;
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

		if (F_SubDirectoriesInDirectory(thispath, &vec)/* && rand() % 3 != 1*/) {
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