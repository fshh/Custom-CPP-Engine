// code derived from TwinklebearDev SDL 2.0 Tutorial
// https://www.willusher.io/pages/sdl2/

#ifndef RES_PATH_HPP
#define RES_PATH_HPP

#include <iostream>
#include <string>
#include <SDL.h>

/*
 * Get the resource path for resources located in res/subDir
 */
std::string getResourcePath(const std::string &subDir = "");

#endif
