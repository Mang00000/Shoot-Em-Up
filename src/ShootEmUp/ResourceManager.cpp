#include "ResourceManager.h"

const std::vector <std::filesystem::path> ResourceManager::TEXTURE_EXTENSIONS = { std::filesystem::path(".png"), std::filesystem::path(".jpg") };
const std::vector<std::string> ResourceManager::SOUND_EXTENSIONS = { "wav" };
const std::vector<std::string> ResourceManager::FONT_EXTENSIONS = { "ttf" };

std::map<std::string, sf::Texture*> ResourceManager::mTextureMap;
std::map<std::string, sf::SoundBuffer*> ResourceManager::mSoundMap;
std::map<std::string, sf::Font*> ResourceManager::mFontMap;

const std::string ResourceManager::DEFAULT_INVALID_TEXTURE = "invalid.png";
const std::string ResourceManager::DEFAULT_INVALID_SOUND = "invalid.wav";
const std::string ResourceManager::DEFAULT_INVALID_FONT = "invalid.ttf";

std::string ResourceManager::mInvalidTexture = ResourceManager::DEFAULT_INVALID_TEXTURE;
std::string ResourceManager::mInvalidSound = ResourceManager::DEFAULT_INVALID_SOUND;
std::string ResourceManager::mInvalidFont = ResourceManager::DEFAULT_INVALID_FONT;



//------------------------------- TEXTURE -------------------------------

sf::Texture* ResourceManager::GetTexture(const std::string _FilePath)
{
	for (auto element : mTextureMap) {
		if (element.first == _FilePath && element.first != mInvalidTexture)
			return element.second;

	}

	sf::Texture* texture = new sf::Texture();

	if (!texture->loadFromFile(_FilePath)) {
		texture->loadFromFile(mInvalidTexture);
	}

	mTextureMap[_FilePath] = texture;

	return mTextureMap[_FilePath];
}

int ResourceManager::GetNumberOfTextures()
{
	return mTextureMap.size();
}

void ResourceManager::PreLoadTextures(const std::string folderPath, bool recurse)
{
	if (recurse) {
		for (auto& file : std::filesystem::recursive_directory_iterator(folderPath)) {
			std::stringstream ss;
			ss << file;
			std::filesystem::path path = file.path();
			//std::cout << std::string(path.extension().c_str()) << std::endl;
			//std::cout << TEXTURE_EXTENSIONS[0] << std::endl;

			
			if (Contains(TEXTURE_EXTENSIONS, ss.str().substr(ss.str().length() - 4, 3))) {
				sf::Texture* texture = new sf::Texture();

				std::string File = ss.str().substr(1, ss.str().length() - 2);
				texture->loadFromFile(File);
				mTextureMap[File] = texture;
			}
		}
	}
	else {
		for (auto& file : std::filesystem::directory_iterator(folderPath)) {
			std::stringstream ss;
			ss << file;      

			//Pour enlever les " à la fin on fait -4 et pas -3
			if (Contains(TEXTURE_EXTENSIONS, ss.str().substr(ss.str().length() - 4, 3))) {
				sf::Texture* texture = new sf::Texture();

				//Pour enlever les " au début et à la fin on commence a 1 et arrête a -2 (car on a avancer de 1 -> -1 -1 = -2)
				std::string File = ss.str().substr(1, ss.str().length() - 2);
				texture->loadFromFile(File);
				mTextureMap[File] = texture;
			}
		}
	}
}

std::string ResourceManager::GetInvalidTexturePath()
{
	return mInvalidTexture;
}

void ResourceManager::ClearTextures()
{
	for (auto element : mTextureMap) {
		delete element.second;
	}

	mTextureMap.clear();
}




bool ResourceManager::Contains(std::vector<std::string> vec, std::string str) {
	for (std::string s : vec) {
		if (s == str)
			return true;
	}
	return false;
}