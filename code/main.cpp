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

	Text output;
	output.setFont(font);
	output.setCharacterSize(14);
	output.setFillColor(Color::White);

	Text& text = output;

	// Declare a coordinate for mouse pixel
	Vector2i mousePixel;

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
				if (event.mouseButton.button == Mouse::Left)
				{
					mousePixel.x = event.mouseButton.x;
					mousePixel.y = event.mouseButton.y;
					complexPlane.zoomIn();
					complexPlane.setCenter(mousePixel);
				}
				if (event.mouseButton.button == Mouse::Right)
				{
					mousePixel.x = event.mouseButton.x;
					mousePixel.y = event.mouseButton.y;
					complexPlane.zoomOut();
					complexPlane.setCenter(mousePixel);
				}
			}
			if (event.type == Event::MouseMoved)
			{
				mousePixel.x = event.mouseMove.x;
				mousePixel.y = event.mouseMove.y;
				complexPlane.setMouseLocation(mousePixel);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Update scene
		complexPlane.updateRender();
		complexPlane.loadText(text);

		// Draw scene
		window.clear();
		window.draw(complexPlane);
		window.draw(output);
		window.display();
	}
}
