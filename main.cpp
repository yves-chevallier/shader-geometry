//main.cpp
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <GL/glew.h>
#include <random>
#include <iostream>
#include <sstream>
#include <cmath>

#define FRAMERATE 120

using namespace std;

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6) {
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;

    void update(float dt) {
        position += velocity * dt;
    }

    void bounce(sf::Vector2f size) {
        if (position.x < -size.x) {
            position.x = -size.x;
            velocity.x *= -1;
        }
        if (position.x > size.x) {
            position.x = size.x;
            velocity.x *= -1;
        }
        if (position.y < -size.y) {
            position.y = -size.y;
            velocity.y *= -1;
        }
        if (position.y > size.y) {
            position.y = size.y;
            velocity.y *= -1;
        }
    }
};

#define WIDTH 800
int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, WIDTH), "Test");

    sf::Shader shader;
    shader.loadFromFile("shader.vert", "shader.geom", "shader.frag");
    sf::Transform matrix = sf::Transform::Identity;
    matrix.scale(2.0 / WIDTH, 2.0 / WIDTH);
    sf::Glsl::Mat4 projectionViewMatrix = matrix;

    shader.setUniform("projectionViewMatrix", projectionViewMatrix);

    std::vector<float> vertices;

    // int rows=5, cols=5;
    // float offset = (float)WIDTH/rows;
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         vertices.push_back(-WIDTH + offset + (float)WIDTH * 2.0 / rows * i);
    //         vertices.push_back(-WIDTH + offset + (float)WIDTH * 2.0 / cols * j);
    //         vertices.push_back((float)i * j / (cols * rows));
    //     }
    // }
    // vertices.push_back(400.0); vertices.push_back(400.0); vertices.push_back(0.0);
    // vertices.push_back(400.0); vertices.push_back(-400.0); vertices.push_back(0.25);
    // vertices.push_back(-400.0); vertices.push_back(-400.0); vertices.push_back(0.5);
    // vertices.push_back(-400.0); vertices.push_back(400.0); vertices.push_back(0.75);
    // vertices.push_back(0.0); vertices.push_back(0.0); vertices.push_back(0.75);
    // vertices.push_back(400.0); vertices.push_back(0.0); vertices.push_back(0.75);
    // vertices.push_back(-400.0); vertices.push_back(-400.0); vertices.push_back(0.75);


    // Time management
    sf::Clock clock;
    sf::Clock seconds;
    sf::Time secondsCount = sf::Time::Zero;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f / FRAMERATE);
    sf::Time timeSinceLastDraw = sf::Time::Zero;
    window.setFramerateLimit(FRAMERATE);

   // Fps text
    sf::Font font;
    if (!font.loadFromFile("assets/collegiate.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }
    sf::Text fps;
    fps.setFont(font);
    fps.setPosition(10, 10);
    fps.setCharacterSize(16);
    fps.setFillColor(sf::Color::White);

    vector<Particle> particles(30000);
    for (int i = 0; i < particles.size(); i++) {
        particles[i].position = sf::Vector2f((rand() % WIDTH) - WIDTH/2, (rand() % WIDTH) - WIDTH/2);
        particles[i].velocity = sf::Vector2f(rand() % 200 - 50, rand() % 200 - 50);
        //std::cout << particles[i].position.x << " " << particles[i].position.y << std::endl;
    }
    // for (int i = 0; i < 100; i++) {
    //     vertices.push_back((float)(rand() % WIDTH - WIDTH / 2));
    //     vertices.push_back((float)(rand() % WIDTH - WIDTH / 2));
    //     vertices.push_back((float)(rand() % INT_MAX) * 2 * 3.14);
    // }




    while (window.isOpen()) {
        sf::Event currEvent;
        while (window.pollEvent(currEvent)) {
            switch (currEvent.type) {
            case(sf::Event::Closed):
                window.close(); break;
            }
        }

        timeSinceLastDraw = clock.restart();
        timeSinceLastUpdate += timeSinceLastDraw;
        double timeFps = 1.f / timeSinceLastDraw.asSeconds();
        //fps.setString("FPS: " + to_string_with_precision(timeFps, 0));


        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            vertices.clear();
            for (auto &p : particles) {
                p.update(timePerFrame.asSeconds());
                p.bounce(sf::Vector2f(WIDTH/2.0, WIDTH/2.0));
                vertices.push_back(p.position.x);
                vertices.push_back(p.position.y);
                vertices.push_back(atan2(p.velocity.y, p.velocity.x));
            }
            if (seconds.getElapsedTime() > sf::seconds(1)) {
                seconds.restart();
                std::cout << "FPS: " + to_string_with_precision(timeFps, 0) << std::endl;
            }
        }



        window.clear(sf::Color(40,44,52));
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
        glVertexPointer(3, GL_FLOAT, 0, vertices.data());
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POINTS, 0, vertices.size() / 3);
        sf::Shader::bind(&shader);
        glDisableClientState(GL_VERTEX_ARRAY);
        // window.draw(fps);

        window.display();
    }
}