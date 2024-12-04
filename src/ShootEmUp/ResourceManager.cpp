#include "ResourceManager.h"
#include "Utils.h"

namespace fs = std::filesystem;

ResourceManager::ResourceManager() {
	TEXTURE_EXTENSIONS = { fs::path(".png"), fs::path(".jpg"), fs::path(".jpeg") };
	SOUND_EXTENSIONS = { fs::path(".wav") };
	FONT_EXTENSIONS = { fs::path("ttf") };

	std::map<std::string, sf::Texture*> mTextureMap;
	std::map<std::string, sf::SoundBuffer*> mSoundMap;
	std::map<std::string, sf::Font*> mFontMap;

	std::string DEFAULT_INVALID_TEXTURE = "invalid.png";
	std::string DEFAULT_INVALID_SOUND = "invalid.wav";
	std::string DEFAULT_INVALID_FONT = "invalid.ttf";

	std::string mInvalidTexture = DEFAULT_INVALID_TEXTURE;
	std::string mInvalidSound = DEFAULT_INVALID_SOUND;
	std::string mInvalidFont = DEFAULT_INVALID_FONT;

}

ResourceManager::~ResourceManager()
{
	ClearTextures();
	ClearFonts();
	ClearSounds();
}

ResourceManager* ResourceManager::Get()
{
	static ResourceManager mInstance;

	return &mInstance;
}

//-----------------------------------------------------------------------
//------------------------------- TEXTURE -------------------------------
//-----------------------------------------------------------------------

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

void ResourceManager::LoadTexture(const std::string& filePath) 
{
	fs::path ImgPath = filePath;

	if (Utils::Contains(TEXTURE_EXTENSIONS, ImgPath.extension())) {
		sf::Texture* texture = new sf::Texture();

		texture->loadFromFile(ImgPath.string());
		mTextureMap[ImgPath.string()] = texture;
	}
}

void ResourceManager::LoadAllTextures(const std::string& folderPath)
{
	for (auto& file : fs::directory_iterator(folderPath)) {

		if (fs::is_directory(file)) 
		{
			LoadAllTextures(file.path().string());
			continue;
		}

		LoadTexture(file.path().string());
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


//----------------------------------------------------------------------
//------------------------------- SOUNDS -------------------------------
//----------------------------------------------------------------------



sf::SoundBuffer* ResourceManager::GetSound(const std::string _FilePath)
{
	for (auto element : mSoundMap) {
		if (element.first == _FilePath && element.first != mInvalidSound)
			return element.second;

	}

	sf::SoundBuffer* Sound = new sf::SoundBuffer();

	if (!Sound->loadFromFile(_FilePath)) {
		Sound->loadFromFile(mInvalidSound);
	}

	mSoundMap[_FilePath] = Sound;

	return mSoundMap[_FilePath];
}

int ResourceManager::GetNumberOfSounds()
{
	return mSoundMap.size();
}

void ResourceManager::LoadSound(const std::string& filePath)
{
	fs::path SoundPath = filePath;

	if (Utils::Contains(SOUND_EXTENSIONS, SoundPath.extension())) {
		sf::SoundBuffer* Sound = new sf::SoundBuffer();

		Sound->loadFromFile(SoundPath.string());
		mSoundMap[SoundPath.string()] = Sound;
	}
}

void ResourceManager::LoadAllSounds(const std::string& folderPath)
{
	for (auto& file : fs::directory_iterator(folderPath)) {

		if (fs::is_directory(file))
		{
			LoadAllSounds(file.path().string());
			continue;
		}

		LoadSound(file.path().string());
	}
}

std::string ResourceManager::GetInvalidSoundPath()
{
	return mInvalidSound;
}

void ResourceManager::ClearSounds()
{
	for (auto element : mSoundMap) {
		delete element.second;
	}

	mSoundMap.clear();
}




//----------------------------------------------------------------------
//------------------------------- FONTS --------------------------------
//----------------------------------------------------------------------

sf::Font* ResourceManager::GetFont(const std::string _FilePath)
{
	for (auto element : mFontMap) {
		if (element.first == _FilePath && element.first != mInvalidFont)
			return element.second;

	}

	sf::Font* CurrentFont = new sf::Font();

	if (!CurrentFont->loadFromFile(_FilePath)) {
		CurrentFont->loadFromFile(mInvalidFont);
	}

	mFontMap[_FilePath] = CurrentFont;

	return mFontMap[_FilePath];
}

int ResourceManager::GetNumberOfFonts()
{
	return mFontMap.size();
}

void ResourceManager::LoadFont(const std::string& filePath)
{
	fs::path FontPath = filePath;

	if (Utils::Contains(FONT_EXTENSIONS, FontPath.extension())) {
		sf::Font* CurrentSound = new sf::Font();

		CurrentSound->loadFromFile(FontPath.string());
		mFontMap[FontPath.string()] = CurrentSound;
	}
}

void ResourceManager::LoadAllFonts(const std::string& folderPath)
{
	for (auto& file : fs::directory_iterator(folderPath)) {

		if (fs::is_directory(file))
		{
			LoadAllFonts(file.path().string());
			continue;
		}

		LoadFont(file.path().string());
	}
}

std::string ResourceManager::GetInvalidFontPath()
{
	return mInvalidFont;
}

void ResourceManager::ClearFonts()
{
	for (auto element : mFontMap) {
		delete element.second;
	}

	mFontMap.clear();
}
