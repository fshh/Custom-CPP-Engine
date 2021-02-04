#include "base/GetResourcePath.hpp"
#include "base/Localization.hpp"
#include "base/ResourceManager.hpp"

const std::string Localization::fontFile = "712_serif.ttf";

const std::string Localization::fpsText = "FPS";
const std::string Localization::livesText = "Lives";
const std::string Localization::scoreText = "Score";
const std::string Localization::winText = "Win";
const std::string Localization::loseText = "Lose";

const std::string Localization::localizationFile = "localization.json";
const std::string Localization::localizationFileName = "localization file";

Localization* Localization::instance = nullptr;

Localization* Localization::getInstance() {
	if (instance == nullptr) {
		instance = new Localization();
	}
	return instance;
}

void Localization::deleteInstance() {
	delete instance;
	instance = nullptr;
}

std::string Localization::getLocalizedText(std::string key) {
	Json::Value table = *(ResourceManager::get<LocalizationFileResource>(localizationFileName)->getLocalizationTable());
	return table[key][currentLanguage].asString();
}

void Localization::setLanguage(Language newLanguage) {
	currentLanguage = newLanguage;
}

Localization::Localization() {
	currentLanguage = Language::English;
	ResourceManager::add<LocalizationFileResource>(
		new LocalizationFileResource(
				localizationFileName,
				getResourcePath() + localizationFile));
	std::cout << "Loaded Localization File." << std::endl;
}
