#ifndef RESOURCEMANAGER_H__
#define RESOURCEMANAGER_H__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <filesystem>


class ResourceManager
{
private:
	static std::map<std::string, sf::Texture*> mTextureMap;
	static std::map<std::string, sf::SoundBuffer*> mSoundMap;
	static std::map<std::string, sf::Font*> mFontMap;

	const static std::string DEFAULT_INVALID_TEXTURE;
	const static std::string DEFAULT_INVALID_SOUND;
	const static std::string DEFAULT_INVALID_FONT;

	static std::string mInvalidTexture;
	static std::string mInvalidSound;
	static std::string mInvalidFont;

	const static std::vector<std::filesystem::path> TEXTURE_EXTENSIONS;
	const static std::vector<std::string> SOUND_EXTENSIONS;
	const static std::vector<std::string> FONT_EXTENSIONS;

public:

				/*******************************
				*		     TEXTURE	   	   *
				*******************************/


	static sf::Texture* GetTexture(const std::string _FilePath);

	static int GetNumberOfTextures();


	//le paramètre recurse permet au programme de chercher dans les fichiers en dessous dans la hiérarchie
	static void PreLoadTextures(const std::string folderPath, bool recurse = true);


	static std::string GetInvalidTexturePath();

	static void ClearTextures();

	//TO ADDD ClearSomeTextures


				/*******************************
				*		     SOUND		   	   *
				*******************************/


	//static sf::SoundBuffer* GetSound(const std::string _FilePath);


	static bool Contains(std::vector<std::string> vec, std::string str);
};





#endif // !RESOURCEMANAGER_H__
