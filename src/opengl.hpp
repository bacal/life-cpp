#pragma once
/*
 * macOS has is in charge of loading the correct OpenGL functions, no loading library is needed.
 */
#if defined( __APPLE__ )
#define GL_SILENCE_DEPRECATION
#include <OpenGL/GL.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif
