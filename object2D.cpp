#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include "transform2D.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(-length / 2, length / 2, 0), color),
        VertexFormat(corner + glm::vec3(length / 2, length / 2, 0), color),
        VertexFormat(corner + glm::vec3(length / 2, -length / 2, 0), color),
        VertexFormat(corner + glm::vec3(-length / 2, -length / 2, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateDiamond(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //rombulet
        VertexFormat(corner + glm::vec3(-length/4, 0, 1), color),
        VertexFormat(corner + glm::vec3(0, length/2, 1), color),
        VertexFormat(corner + glm::vec3(length/4, 0, 1), color),
        VertexFormat(corner + glm::vec3(0, -length / 2, 1), color),
        VertexFormat(corner + glm::vec3(length/4, 0, 1), color),
        VertexFormat(corner + glm::vec3(-length/4, 0, 1), color),
        //triunghi1 tun
        VertexFormat(corner + glm::vec3(0, length / 8, 1), color), //6
        VertexFormat(corner + glm::vec3(length/2, length / 8, 1), color), //7
        VertexFormat(corner + glm::vec3(0, -length / 8, 1), color), //8
        //triunghi2 tun
        VertexFormat(corner + glm::vec3(length / 2, -length / 8, 1), color) //9

    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5,
                                          6, 7, 8,
                                          7, 9, 8};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateHexagon(
    const std::string& name,
    glm::vec3 center,
    float size,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;

    // Calculate the vertices for the hexagon
    for (int i = 0; i < 6; i++) {
        glm::vec3 vertexPos(
            center.x + size/2 * cos(i * M_PI / 3 + M_PI / 4),
            center.y + size/2 * sin(i * M_PI / 3 + M_PI / 4),
            center.z
        );
        vertices.push_back(VertexFormat(vertexPos, color));
    }
    for (int i = 0; i < 6; i++) {
        glm::vec3 vertexPos(
            center.x + size / 3 * cos(i * M_PI / 3 + M_PI / 4),
            center.y + size / 3 * sin(i * M_PI / 3 + M_PI / 4),
            center.z + 1
        );
        vertices.push_back(VertexFormat(vertexPos, glm::vec3({ 0, 0.5, 0.5 })));
    }
    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 2, 3,
                                          0, 3, 4,
                                          0, 4, 5,
                                          6, 7, 8,
                                          6, 8, 9,
                                          6, 9, 10,
                                          6, 10, 11, 6 };

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
            indices.push_back(0);
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float length,
    glm::vec3 color,
    bool fill)
{
    length = length / 2;
    std::vector<VertexFormat> vertices;
        //triunghi1
        glm::vec3 vertexPos(
            center.x + length * cos(M_PI/2),
            center.y + length * sin(M_PI/2),
            center.z + 2
        );
        vertices.push_back(VertexFormat(vertexPos, color));

        vertexPos = {
            center.x + length * cos(4 * M_PI / 5 + M_PI / 2),
            center.y + length * sin(4 * M_PI / 5 + M_PI / 2),
            center.z + 2
        };
        vertices.push_back(VertexFormat(vertexPos, color));

        vertexPos = {
            center.x + length * 0.4f * cos(7 * M_PI / 5 + M_PI / 2 ),
            center.y + length * 0.4f * sin(7 * M_PI / 5 + M_PI / 2 ),
            center.z + 2
        };
        vertices.push_back(VertexFormat(vertexPos, color));
        
        //triunghi2
        vertexPos = {
            center.x + length * cos(2 * M_PI / 5 + M_PI / 2),
            center.y + length * sin(2 * M_PI / 5 + M_PI / 2),
            center.z + 2
        };
        vertices.push_back(VertexFormat(vertexPos, color));
        vertexPos = {
            center.x + length * cos(6 * M_PI / 5 + M_PI / 2),
            center.y + length * sin(6 * M_PI / 5 + M_PI / 2),
            center.z + 2
        };
        vertices.push_back(VertexFormat(vertexPos, color));
        vertexPos = {
            center.x + length * 0.4f * cos(-M_PI / 5 + M_PI / 2),
            center.y + length * 0.4f * sin(-M_PI / 5 + M_PI / 2),
            center.z + 2
        };
        //triunghi 3
        vertices.push_back(VertexFormat(vertexPos, color));
        vertexPos = {
            center.x + length * cos(8 * M_PI / 5 + M_PI / 2),
            center.y + length * sin(8 * M_PI / 5 + M_PI / 2),
            center.z + 2
        };
        vertices.push_back(VertexFormat(vertexPos, color));
        vertexPos = {
            center.x + length * 0.4f * cos(M_PI / 5 + M_PI / 2),
            center.y + length * 0.4f * sin(M_PI / 5 + M_PI / 2),
            center.z + 2
        };
        vertices.push_back(VertexFormat(vertexPos, color));

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 1, 6, 7};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 1 triangles. Add the remaining 2 indices
        indices.push_back(0);

    }

    square->InitFromData(vertices, indices);
    return square;
}


Mesh* object2D::CreateHeart(
    const std::string& name,
    glm::vec3 center,
    float size,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices;

    // Calculate the vertices for the hexagon
    for (int i = 0; i < 360; i++) {
        float theta = 2.0f * M_PI * float(i) / float(360);
        glm::vec3 vertexPos(
            center.x + 3 * 16 * pow(sin(theta), 3),
            center.y + 3 * (13 * cos(theta) - 5*cos(2*theta) - 2*cos(3*theta) - cos(4*theta) ),
            center.z
        );
        vertices.push_back(VertexFormat(vertexPos, color));
    }
    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1};

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        for (int i = 0; i < 360; i++) {
            indices.push_back(0);
            indices.push_back(i+1);
            indices.push_back(i + 2);
        }
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}
/*
void object2D::CollisionEnemy(
    int *flag_animation,
    float *collision_time,
    float *scaleX,
    float *scaleY,
    int start_enemy,
    float *deltaTimeSeconds,
    float *translateX
)
{
    glm::mat3 modelMatrix = glm::mat3(1);
    if (translateX + start_enemy <= 50 && flag_animation == 0) {
        scaleX -= *deltaTimeSeconds;
        scaleY = scaleX;
        flag_animation = 1;
        modelMatrix *= transform2D::Translate(50, 75);
    }
    else if (translateX + start_enemy < 50 && flag_animation == 1 && scaleX >= 0 && scaleY >= 0) {
        scaleX -= (deltaTimeSeconds);
        scaleY = scaleX;
        modelMatrix *= transform2D::Translate(50, 75);
        modelMatrix *= transform2D::Scale(scaleX, scaleY);
    }
    else {
        modelMatrix *= transform2D::Translate(start_enemy, 75);
        modelMatrix *= transform2D::Translate(translateX, 0);
    }
}
*/
