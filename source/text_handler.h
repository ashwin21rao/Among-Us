#ifndef _TEXT_HANDLER_H
#define _TEXT_HANDLER_H

#include <string>
#include <map>
#include "shader.h"

class TextHandler
{
public:
    TextHandler(int window_width, int window_height);
    void renderText(std::string text, float x, float y, float scale, glm::vec3 color);

private:
    struct Character
    {
        unsigned int TextureID; // ID handle of the glyph texture
        glm::ivec2   Size;      // Size of glyph
        glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
        unsigned int Advance;   // Horizontal offset to advance to next glyph
    };
    std::map<char, Character> Characters;

    std::string font_family;
    int font_size;

    Shader shader;
    unsigned int vao, vbo;

    void initFont();
    void createFont();
};


#endif
