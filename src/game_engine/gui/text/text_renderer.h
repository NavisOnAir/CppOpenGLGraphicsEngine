#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../../model/shader.h"
#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/ext/matrix_transform.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"

#include <map>
#include <iostream>
#include <string>

struct Character {
	uint32 textureID; // ID handle of the glyph texture
	glm::ivec2 size; // Size of glyph
	glm::ivec2 bearing; // Offset from baseline to left/top of glyph
	uint32 advance; // Offset to advance to next glyp
};

namespace gui {

	class TextRenderer {
	public:
		TextRenderer();
		TextRenderer(int screenWidth, int screenHeight, Shader* s); // after construct need to load font
		void renderText(std::string text, float x, float y, float scale, glm::vec3 color);
		void rezise(int width, int height);
		int loadFont(const char* fontFile);

		// get
		int getTextWidth(std::string text);
		int getMaxTextHeight(std::string text);

	private:
		Shader* shader;
		std::map<char, Character> characters;
		GLuint vao, vbo;
		const char* fontFile;
	};
}