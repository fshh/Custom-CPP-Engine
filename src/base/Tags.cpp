#include "base/Tags.hpp"

Tags* Tags::instance = nullptr;

Tags& Tags::getInstance() {
	if (instance == nullptr) {
		instance = new Tags();
	}
	return *instance;
}


void Tags::deleteInstance() {
	delete instance;
	instance = nullptr;
}
