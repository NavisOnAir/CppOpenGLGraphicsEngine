#pragma once
#include <cstdint>
#include "../../libs/glm/glm.hpp"
#include <iostream>

// glew
#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED

// sdl
#ifdef _WIN32
#include <SDL.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#else
#include <SDL2/SDL.h>
#endif

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef float float32;
typedef double float64;


struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
};

struct Transform {
	float x;
	float y;
	float z;
};

struct Material {
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 emissive;
	float shininess;
};

namespace gui{
	struct Color {
		float r;
		float g;
		float b;
		float a;

		Color() = default;

		Color(float red, float green, float blue, float alpha) {
			r = red;
			g = green;
			b = blue;
			a = alpha;
		}

		Color(float color) {
			r = color;
			g = color;
			b = color;
			a = color;
		}
	};
	struct Vertex2D {
		glm::vec2 position;
	};

	struct Material2D {
		gui::Color color;
	};
}