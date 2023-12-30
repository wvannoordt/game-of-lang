#include <SFML/Graphics.hpp>

int main()
{
        sf::RenderWindow window(sf::VideoMode(800, 600), "Skew Image", sf::Style::Default);

        sf::Texture texture;
        if (!texture.loadFromFile("image.png"))
        {
                return EXIT_FAILURE;
        }

        // vertexarray with 8 vertices (4 per quad)
        sf::VertexArray quads(sf::Quads, 8);

        // first quad (vertices 0 - 3)
        quads[0].position = sf::Vector2f(100, 100);
        quads[1].position = sf::Vector2f(196, 100);
        quads[2].position = sf::Vector2f(196, 196);
        quads[3].position = sf::Vector2f(100, 196);
        quads[0].texCoords = sf::Vector2f(0, 0);
        quads[1].texCoords = sf::Vector2f(47, 0);
        quads[2].texCoords = sf::Vector2f(47, 47);
        quads[3].texCoords = sf::Vector2f(0, 47);

        // second quad (vertices 4 - 7)
        quads[4].position = sf::Vector2f(210, 160);
        quads[5].position = sf::Vector2f(320, 100);
        quads[6].position = sf::Vector2f(292, 250);
        quads[7].position = sf::Vector2f(180, 240);
        quads[4].texCoords = sf::Vector2f(0, 0);
        quads[5].texCoords = sf::Vector2f(47, 0);
        quads[6].texCoords = sf::Vector2f(47, 47);
        quads[7].texCoords = sf::Vector2f(0, 47);

        while (window.isOpen())
        {
                sf::Event event;
                while (window.pollEvent(event))
                {
                        if (event.type == sf::Event::Closed)
                        {
                                window.close();
                        }
                }
                window.clear();

                // draw both quads using the texture
                window.draw(quads, &texture);

                window.display();
        }
        return EXIT_SUCCESS;
}
