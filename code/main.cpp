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

	while (window.isOpen())
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
				Vector2i mouseLocation;
				if (event.mouseButton.button == Mouse::Left)
				{
					mouseLocation.x = event.mouseButton.x;
					mouseLocation.y = event.mouseButton.y;
					complexPlane.zoomIn();
					complexPlane.setCenter(mouseLocation);
				}
				if (event.mouseButton.button == Mouse::Right)
				{
					mouseLocation.x = event.mouseButton.x;
					mouseLocation.y = event.mouseButton.y;
					complexPlane.zoomOut();
					complexPlane.setCenter(mouseLocation);
				}
			}
			if (event.type == Event::MouseMoved)
			{
				mouseLocation.x = mouseMove.x;
				mouseLocation.y = mouseMove.y;
				complexPlane.setMouseLocation(mouseLocation);
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
