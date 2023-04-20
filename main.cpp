#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
//test
// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;
int main()
{
	float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	sf::View view(sf::FloatRect(0.f, 0.f, width, height));
	// Create a video mode object
	VideoMode vm(width, height);
	//VideoMode vm(800, 600);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!", Style::Default);
	vector<Vector2f> vertices;
    vector<Vector2f> points;
    int numberOfPoints = 0;
    int lastvertex = 0;

	Text messageText;
	// We need to choose a font
	Font font;
	font.loadFromFile("./fonts/Roboto-Black.ttf");
	messageText.setFont(font);
	messageText.setCharacterSize(22);

    std:stringstream ss;
    ss<<"Left click 3+ points, then right click to start.";
    messageText.setString(ss.str());


	while (window.isOpen())
	{
        
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    cout << "the left button was pressed" << endl;
                    cout << "mouse x: " << event.mouseButton.x << endl;
                    cout << "mouse y: " << event.mouseButton.y << endl;

                    numberOfPoints = numberOfPoints + 1;

                    if(vertices.size() < numberOfPoints)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
                else if (event.mouseButton.button == Mouse::Right)
                {
                    if(points.size() == 0)
                    {
                        cout << "the right button was pressed" << endl;
                        cout << "mouse x: " << event.mouseButton.x << endl;
                        cout << "mouse y: " << event.mouseButton.y << endl;
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        

        if (points.size() > 0)
        {

            int random; 
            if (numberOfPoints == 3)
            {
                random = rand() % numberOfPoints;
            }
            else
            {
                do {random = rand() % numberOfPoints;} while (lastvertex == random);
                lastvertex = random;
            }

            
            points.push_back(Vector2f( (vertices[random].x + points[points.size() - 1].x) / 2, (vertices[random].y + points[points.size() - 1].y) / 2));
        }

        
        window.clear();
        window.draw(messageText);
        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(15,15));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Red);
            window.draw(rect);
            
  
        }
        for (int i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(7, 7));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::White);
            window.draw(rect);
        }
        
        window.display();
    }
}
