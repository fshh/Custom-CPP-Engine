#ifndef INCLUDE_LOCALIZATION_HPP_
#define INCLUDE_LOCALIZATION_HPP_

#include <string>
#include <json/json.h>

/**
 * Enumerated list of supported languages.
 * Their index corresponds to the index they are expected at in the JSON list.
 */
enum Language {
	English = 0,
	Spanish = 1,
	Japanese = 2
};

/**
 * Singleton class for localizing in-game text to different languages.
 */
class Localization {
public:
	/**
	 * The UTF-8 font that this text should use (not enforced).
	 */
	static const std::string fontFile;

	static const std::string fpsText; /**< Convenience const for the JSON key of the FPS text. */
	static const std::string livesText; /**< Convenience const for the JSON key of the lives text. */
	static const std::string scoreText; /**< Convenience const for the JSON key of the score text. */
	static const std::string winText; /**< Convenience const for the JSON key of the win screen text. */
	static const std::string loseText; /**< Convenience const for the JSON key of the game over screen text. */

	/**
	 * Gets the current instance of Localization or creates one if there is none.
	 * @return the singleton instance of this class.
	 */
	static Localization* getInstance();

	/**
	 * Cleans up the current instance. Note that a new instance is created again if getInstance() is called after this.
	 * Use to free up memory in places where Localization is not needed.
	 */
	static void deleteInstance();

	/**
	 * Gets a UTF-8 encoded String of the text at the given key in the current language.
	 * @param key The key used to access the text resource.
	 * @return a UTF-8 encoded CString in the current language.
	 */
	std::string getLocalizedText(std::string key);

	/**
	 * Sets the language the localization uses to get text. Note that this does not automatically refresh localized text.
	 * @param newLanguage The new language to switch to.
	 */
	void setLanguage(Language newLanguage);

private:
	/**
	 * The path to the JSON file to load in.
	 */
	static const std::string localizationFile;

	/**
	 * The name of the localization file used by the resource manager.
	 */
	static const std::string localizationFileName;

	static Localization* instance;

	Language currentLanguage;

	Localization();  // Private Singleton
	Localization(Localization const&) = delete; // Avoid copy constructor.
	void operator=(Localization const&) = delete; // Don't allow copy assignment.
	Localization(Localization const&&) = delete; // Avoid move constructor.
	void operator=(Localization const&&) = delete; // Don't allow move assignment.
};



#endif /* INCLUDE_LOCALIZATION_HPP_ */
