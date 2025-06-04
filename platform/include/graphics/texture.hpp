#if !defined(TEXTURE_H)
#define TEXTURE_H

#include <glad/glad.h>
#include <stb_image.h>
#include <string>

class Texture2D
{
private:
    unsigned int ID;
public:
    Texture2D(std::string fileName);
    unsigned int *getID();
    void bind();
};


#endif // TEXTURE_H
