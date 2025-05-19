#pragma once

#include "core/gl_includes.hpp"

#include <string>
#include <iostream>

GLenum glCheckError_(const char* file, int line);

#ifdef DEBUG
#define glCheckError() glCheckError_(__FILE__, __LINE__)
#else
#define glCheckError()
#endif
