#ifndef RESOURCEMANAGER_H__
#define RESOURCEMANAGER_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <filesystem>


class ResourceManager
{
private:
	std::map<std::string, sf::Texture*> mTextureMap;
	std::map<std::string, sf::SoundBuffer*> mSoundMap;
	std::map<std::string, sf::Font*> mFontMap;

	std::string DEFAULT_INVALID_TEXTURE;
	std::string DEFAULT_INVALID_SOUND;
	std::string DEFAULT_INVALID_FONT;

	std::string mInvalidTexture;
	std::string mInvalidSound;
	std::string mInvalidFont;

	std::vector<std::filesystem::path> TEXTURE_EXTENSIONS;
	std::vector<std::filesystem::path> SOUND_EXTENSIONS;
	std::vector<std::filesystem::path> FONT_EXTENSIONS;

	ResourceManager();

public:
	~ResourceManager();

	static ResourceManager* Get();

				/*******************************
				*		     TEXTURE	   	   *
				*******************************/


	sf::Texture* GetTexture(const std::string _FilePath);

	int GetNumberOfTextures();

	void LoadTexture(const std::string& filePath);
	void LoadAllTextures(const std::string& folderPath);


	std::string GetInvalidTexturePath();

	void ClearTextures();


				/*******************************
				*		     SOUND		   	   *
				*******************************/


	sf::SoundBuffer* GetSound(const std::string _FilePath);

	int GetNumberOfSounds();

	void LoadSound(const std::string& filePath);
	void LoadAllSounds(const std::string& folderPath);
		

	std::string GetInvalidSoundPath();

	void ClearSounds();


				/*******************************
				*		     FONT		   	   *
				*******************************/


	sf::Font* GetFont(const std::string _FilePath);

	int GetNumberOfFonts();

	void LoadFont(const std::string& filePath);
	void LoadAllFonts(const std::string& folderPath);


	std::string GetInvalidFontPath();

	void ClearFonts();
};





#endif // !RESOURCEMANAGER_H__
