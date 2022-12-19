//main.cpp
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <GL/glew.h>
#include <random>

#define WIDTH 800
int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, WIDTH), "Test");

    sf::Shader shader;
    shader.loadFromFile("shader.vert", "shader.geom", "shader.frag");
    sf::Transform matrix = sf::Transform::Identity;
    matrix.scale(1.0 / WIDTH, 1.0 / WIDTH);
    sf::Glsl::Mat4 projectionViewMatrix = matrix;

    shader.setUniform("projectionViewMatrix", projectionViewMatrix);

    std::vector<GLfloat> vertices;

    vertices.push_back(0.0); vertices.push_back(0.0); vertices.push_back(0.0);

    while (window.isOpen()) {
        sf::Event currEvent;
        while (window.pollEvent(currEvent)) {
            switch (currEvent.type) {
            case(sf::Event::Closed):
                window.close(); break;
            }
        }

        window.clear(sf::Color::Black);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POINTS, 0, vertices.size() / 3);
        glDisableClientState(GL_VERTEX_ARRAY);

        sf::Shader::bind(&shader);

        window.display();
    }
}
