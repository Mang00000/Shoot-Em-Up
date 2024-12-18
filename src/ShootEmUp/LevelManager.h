#ifndef LEVELMANAGER_H__
#define LEVELMANAGER_H__

#include <iostream>
#include <fstream>
#include <string>

class LevelManager {
	std::ifstream mFile;
public:
	LevelManager();
	void ReadFile(const char* path);
	void PrintFile(const std::string& filepath);
};

#endif // !LEVELMANAGER_H__
