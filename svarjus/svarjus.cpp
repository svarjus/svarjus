#include "filesystem.h"
#include "keys.h"
#include "pwsh.h"
#include "file.h"
int main()
{
	char confirmation;

	std::cout << "type [Y/y] to continue: ";
	std::cin >> confirmation;

	if (tolower(confirmation) != 'y')
		return 0;

	std::cout << "\nare you still sure? type [Y/y] to continue: ";
	std::cin >> confirmation;

	if (tolower(confirmation) != 'y')
		return 0;

	std::string path;
	FS::F_Main(&path);
	//PS::pwsh(path);
	//_FILE::SpamVarjus(path);
	_FILE::ohno(path);
	//KEY::ReadKeys();
	
	return 0;
}