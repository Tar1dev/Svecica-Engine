#if !defined(MESH_HPP)
#define MESH_HPP

#include <vector>
#include <cstddef>


struct Vertex
{
    float coordinates[3];
};


class Mesh
{
private:
    unsigned int VBO, VAO, EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
public:
    Mesh(const float *verticesData, size_t verticesCount, const unsigned int *indicesData, size_t indicesCount);
    void draw();
};

#endif // MESH_HPP
