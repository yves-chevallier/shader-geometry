//main.cpp
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <GL/glew.h>
#include <random>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Test");

    sf::Shader shader;
    shader.loadFromFile("shader.vert", "shader.geom", "shader.frag");
    sf::Transform matrix = sf::Transform::Identity;
    matrix.scale(1 / 800.f, 1 / 800.f);
    //matrix.translate(100, -0.5);
    sf::Glsl::Mat4 projectionViewMatrix = matrix;

    shader.setUniform("projectionViewMatrix", projectionViewMatrix);

    shader.setUniform("boid_colour", sf::Glsl::Vec4(0.9, 0.7, 0.25, 1));

    size_t points = 1;
    std::vector<GLfloat> vertices(3*points);
    for (int i = 0; i < points; i++)
    {
        vertices[3*i] = (float)(rand() % 800);
        vertices[3*i+1] = (float)(rand() % 800);
        vertices[3*i+2] = (float)(rand() / (float)RAND_MAX) * 2. * 3.14;
    }

    vertices[3*0] = 0;
    vertices[3*0+1] = 0;
    vertices[3*0+2] = (float)(rand() / (float)RAND_MAX) * 2. * 3.14;
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

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glDrawArrays(GL_POINTS, 0, vertices.size());
        glDisableClientState(GL_VERTEX_ARRAY);

        sf::Shader::bind(&shader);

        window.display();
    }
}
