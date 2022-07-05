#include "text_renderer.h"

namespace gui {

	TextRenderer::TextRenderer() {

	}

	TextRenderer::TextRenderer(int screenWidth, int screenHeight, Shader* s) {
		s->init("src/shaders/font.vert", "src/shaders/font.frag");
		shader = s;
		fontFile = "";
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);

		// initialize shader and projection matrix
		glm::mat4 projMat = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight);
		shader->bind();
		glUniformMatrix4fv(glGetUniformLocation(shader->getShaderId(), "u_projection"), 1, GL_FALSE, glm::value_ptr(projMat));

	}

	int TextRenderer::loadFont(const char* fontFile) {
		this->fontFile = fontFile;
		FT_Library ft;
		if (FT_Init_FreeType(&ft)) {
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			return -1;
		}

		FT_Face face;
		if (FT_New_Face(ft, fontFile, 0, &face))
		{
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
			return -1;
		}
		else {
			FT_Set_Pixel_Sizes(face, 0, 48); // setting width to 0 lets the face dynamically size the letters based on demand

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

			for (unsigned char c = 0; c < 128; c++) {
				// load charayter glyph
				if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
					std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
					continue;
				}

				// generate textures
				uint32 texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);

				// set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				// store characters
				Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					static_cast<unsigned int>(face->glyph->advance.x)
				};

				characters.insert(std::pair<char, Character>(c, character));
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		// clear freetype's resources
		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		return 0;
	}

	void TextRenderer::renderText(std::string text, float x, float y, float scale, glm::vec3 color) {
		// activate corresponding render state
		shader->bind();
		GLint textColorLocation = glGetUniformLocation(shader->getShaderId(), "u_text_color");
		glUniform3f(textColorLocation, color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao);

		// iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = characters[*c];

			float xpos = x + ch.bearing.x * scale;
			float ypos = y - (ch.size.y - ch.bearing.y) * scale;

			float w = ch.size.x * scale;
			float h = ch.size.y * scale;
			// update VBO for each character
			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.textureID);
			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextRenderer::rezise(int width, int height) {
#ifdef _DEBUG
		std::cout << "Resizing textRenderer..." << std::endl;
#endif

		glm::mat4 projMat = glm::ortho(0.0f, (float)width, 0.0f, (float)height);
		shader->bind();
		glUniformMatrix4fv(glGetUniformLocation(shader->getShaderId(), "u_projection"), 1, GL_FALSE, glm::value_ptr(projMat));
	}

	int TextRenderer::getTextWidth(std::string text) {
		int width = 0;
		for (std::string::const_iterator i = text.begin(); i != text.end(); i++) {
			Character c = characters[*i];
			width += (c.advance >> 6);
			
		}
		return width;
	}

	int TextRenderer::getMaxTextHeight(std::string text) {
		int maxTopHeight = 0;
		int maxBotHeight = 0;
		for (std::string::const_iterator i = text.begin(); i != text.end(); i++) {
			Character c = characters[*i];
			if ((c.size.y - c.bearing.y) > maxBotHeight) {
				maxBotHeight = c.size.y - c.bearing.y;
			}
			if ((c.bearing.y) > maxTopHeight) {
				maxTopHeight = c.bearing.y;
			}
		}
		return maxBotHeight + maxTopHeight;
	}

}