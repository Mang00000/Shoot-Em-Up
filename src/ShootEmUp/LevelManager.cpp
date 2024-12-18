#include "LevelManager.h"

LevelManager::LevelManager()
{
}

void LevelManager::ReadFile(const char* path)
{
	mFile.open(path);
	std::string myline;
	char mychar;

	std::getline(mFile, myline);
	int FileLenght = myline.length();

	mFile.clear();
	mFile.seekg(0);

	if (mFile.is_open()) {
		int i = 0;
		while (true) {
			if (i == FileLenght) {
				break;
			}
			while (std::getline(mFile, myline)) {
				mychar = myline.at(i);
				std::cout << mychar << std::endl;
			}
			i++;
			mFile.clear();
			mFile.seekg(0);
		}
	}
	else {
		std::cout << "Couldn't open file\n";
	}
}

void LevelManager::PrintFile(const std::string& filepath)
{
}
