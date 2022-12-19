//main.cpp
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <GL/glew.h>
#include <random>

#define WIDTH 800
int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, WIDTH), "Test");

    sf::Shader shader;
    shader.loadFromFile("shader.vert", "shader.geom", "shader.frag");
    sf::Transform matrix = sf::Transform::Identity;
    matrix.scale(1.0 / WIDTH, 1.0 / WIDTH);
    sf::Glsl::Mat4 projectionViewMatrix = matrix;

    shader.setUniform("projectionViewMatrix", projectionViewMatrix);

    size_t points = 2;
    std::vector<GLfloat> vertices;
    // for (int i = 0; i < points; i++)
    // {
    //     vertices[3*i] = (float)(rand() % WIDTH);
    //     vertices[3*i+1] = (float)(rand() % WIDTH);
    //     vertices[3*i+2] = (float)(rand() / (float)RAND_MAX) * 2. * 3.14;
    // }

    // for (int i = 0; i < 5; i++) {
    //     for (int j = 0; j < 5; j++) {
    //         vertices.push_back(-500 + i * 100);
    //         vertices.push_back(-500 + j * 100);
    //         vertices.push_back(0);
    //     }
    // }

    vertices.push_back(400.0);
    vertices.push_back(400.0);
    vertices.push_back(0.0);

    vertices.push_back(-200.0);
    vertices.push_back(-200.0);
    vertices.push_back(1.0);

    while (window.isOpen())
    {
        sf::Event currEvent;
        while (window.pollEvent(currEvent))
        {
            switch (currEvent.type)
            {
            case(sf::Event::Closed):
                window.close();
                break;
            default:
                break;
            }
        }

        window.clear(sf::Color::Black);

        glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POINTS, 0, vertices.size() / 3);
        glDisableClientState(GL_VERTEX_ARRAY);

        sf::Shader::bind(&shader);

        window.display();
    }
}
