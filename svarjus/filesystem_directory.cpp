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
	vecReset(&(*out), 4096);
	int i{ 0 };
	
	int permission = (int)(fs::perms)(fs::status(directory).permissions());
	std::string thisdir;
	//std::cout << "permission: " << permission << '\n';
	//if (!hasperms(fs::status(directory).permissions())) {
	//	std::cout << "no permission\n";
	//	return false;
	//}

	if (!fs::exists(directory)) {
		out->resize(0);
		return false;
	}
	try {
		for (const auto& entry : fs::directory_iterator(directory)) {
			if (entry.is_directory() && entry.exists()) {
				thisdir = entry.path().string();
				//permission = (int)(fs::perms)(fs::status(thisdir).permissions());
				DWORD attributes = GetFileAttributes(thisdir.c_str());
				if (attributes & FILE_ATTRIBUTE_HIDDEN) 
					continue;
				
				out->push_back(thisdir);
				i += 1;
			}
		}
	}
	catch (std::exception& ex) {
		//std::cout << "error: " << ex.what() << '\n';
		//std::cout << "failed permission: " << permission << '\n';
		//std::cout << "failed dir: " << thisdir << '\n';
		//system("pause");
		out->resize(0);
		return false;
	}

	out->resize(i);

	return out->size() > 0;
}
void FS::GetRandomDirectory(std::string* out, std::string start_path)
{
	std::vector<std::string> vec;
	vecReset<std::string>(&vec, 4096);
	//*out = start_path;
	*out = start_path;
	if (!F_SubDirectoriesInDirectory(*out, &vec)) {
		_log.AddLog("directory does not exist.. aborting\n");
		return;
	}
	std::string thispath = start_path;
	int directory{};

	for(int i = 0; i < vec.size(); i++){
		directory = rand() % vec.size();

		thispath = vec[directory];

		//vecReset<std::string>(&vec, 20000);

		if (F_SubDirectoriesInDirectory(thispath, &vec)/* && rand() % 20 != 1*/) {
		//	std::cout << "subdirectory found!\n";
			directory = rand() % vec.size();
			thispath = vec[directory];
			continue;
		}
	//	std::cout << "subdirectory found after: " << i << " iterations\n";
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
bool FS::F_DirectoryExists(std::string directory_path)
{
	return fs::exists(directory_path);
}