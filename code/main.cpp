#include "ComplexPlane.h"

int main()
{
	// Create a video mode object
	VideoMode vm(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2);

	// Create and open a window 
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

	// Construct the ComplexPlane
	ComplexPlane complexPlane(1, 1);

	// Construct the Font and Text objects
	Font font;
	font.loadFromFile("Courier.ttf");

	Text& output;
	output.setFont(font);
	output.setCharacterSize(24);
	output.setFillColor(Color::White);

	while (window.isOPen())
	{
		// Handle user input
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
					complexPlane.zoomIn();
					complexPlane.setCenter(event.mouseButton);
				}
				if (event.mouseButton.button == Mouse::Right)
				{
					complexPlane.zoomOut();
					complexPlane.setCenter(event.mouseButton);
				}
			}
			if (event.type == Event::MouseMoved)
			{
				complexPlane.setMouseLocation(event.mouseMove);
			}
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		window.close();
	}

	// Update scene
	complexPlane.updateRender();
	complexPlane.loadText(output);

	// Draw scene
	window.clear();
	window.draw(complexPlane);
	window.draw(output);
	window.display();
}