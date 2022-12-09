#include <SFML/Graphics.hpp>

#define PI 3.14159265358979323846

const int W = 1300;
const int H = 1300;
float startAngle = PI / 2;
float angle = 2 * PI / 3;
float step = 0.006;
float legth = 500;
int iterations = 9;
int r = 100, g = 100, b = 100;
int colorStep = 1;

sf::RenderWindow window(sf::VideoMode(W, H), "Pythagoras tree (ultra modified)", sf::Style::Close);
void changeColor();

int main(int argc, char* args[])
{
    window.setFramerateLimit(75);

    sf::Vector2f center(W / 2, H / 2 + 90);

    sf::Font font;
    if (!font.loadFromFile("consolas.ttf")) {
        return 0;
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(20, 10);

    sf::Thread thChangeColor(changeColor);
    thChangeColor.launch();

    class tree {
    public:
        tree(float x1, float y1, float dir, float l, int iteration) {
            float x2 = x1 + cos(dir) * l;
            float y2 = y1 - sin(dir) * l;
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(x1, y1), sf::Color(r, g, b)),
                sf::Vertex(sf::Vector2f(x2, y2), sf::Color(r, g, b))
            };
            window.draw(line, 2, sf::Lines);
            if (iteration > 0) {
                tree(x2, y2, dir + angle, l * 0.5, iteration - 1);
                tree(x2, y2, dir - angle, l * 0.5, iteration - 1);
                tree(x2, y2, dir, l * 0.5, iteration - 1);
            }
        }
    };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                thChangeColor.terminate();
            }
        }

        window.clear(sf::Color(40, 40, 40));

        tree(center.x, center.y + 300, startAngle, legth, iterations);

        /*if (angle > PI || angle < 0) step = -step;
        angle += step;*/

        text.setString("angle: " + std::to_string(angle * 2) + " radian");
        window.draw(text);
        window.display();
    }

    return 0;
}

void changeColor()
{
    while (true)
    {
        sf::sleep(sf::milliseconds(10));
        r += colorStep * 3;
        g += colorStep * 5;
        b += colorStep * 10;
    }
}























//#include <SFML/Graphics.hpp>
//
//#define PI 3.14159265358979323846
//
//const int W = 1300;
//const int H = 1000;
//float startAngle = PI / 2;
//float angle = 0;
//float step = 0.004;
//float legth = 300;
//int iterations = 8;
//
//sf::RenderWindow window(sf::VideoMode(W, H), "Pythagoras tree (ultra modified)", sf::Style::Close);
//
//int main(int argc, char* args[])
//{
//    window.setFramerateLimit(75);
//
//    sf::Vector2f center(W / 2, H / 2 + 90);
//
//    sf::Font font;
//    if (!font.loadFromFile("consolas.ttf")) {
//        return 0;
//    }
//    sf::Text text;
//    text.setFont(font);
//    text.setCharacterSize(24);
//    text.setFillColor(sf::Color::White);
//    text.setPosition(20, 10);
//
//    class tree {
//    public:
//        tree(float x1, float y1, float dir, float l, int iteration, float corner) {
//            float x2 = x1 + cos(dir + corner) * l;
//            float y2 = y1 - sin(dir + corner) * l;
//            sf::Vertex line[] =
//            {
//                sf::Vertex(sf::Vector2f(x1, y1)),
//                sf::Vertex(sf::Vector2f(x2, y2))
//            };
//            window.draw(line, 2, sf::Lines);
//            if (iteration > 0) {
//                tree(x2, y2, dir + angle * (2 * PI / 3), l * 0.5, iteration - 1, 0);
//                tree(x2, y2, dir + angle * (4 * PI / 3), l * 0.5, iteration - 1, 0);
//                tree(x2, y2, dir + angle * (6 * PI / 3), l * 0.5, iteration - 1, 0);
//            }
//        }
//    };
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//        window.clear();
//
//        tree(center.x, center.y, startAngle, legth, iterations, 0);
//        tree(center.x, center.y, startAngle, legth, iterations, (2 * PI / 3));
//        tree(center.x, center.y, startAngle, legth, iterations, -(2 * PI / 3));
//
//        if (angle > 2 * PI || angle < -2 * PI) step = -step;
//        angle += step;
//
//        text.setString("angle: " + std::to_string(angle) + " radian");
//        window.draw(text);
//        window.display();
//    }
//
//    return 0;
//}
//
