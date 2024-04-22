#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = static_cast<float>(pixelHeight) / pixelWidth;
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;

	// Initialize VertexArray
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	int x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	int y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x, y };
	m_state = State::CALCULATING;
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	int x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	int y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x, y };
	m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text)
{
	stringstream outputStream;
	outputStream << "Mandelbrot Set" <<
			        "\nCenter: (" << m_plane_center.x << "," << m_plane_center.y << ")" <<
				    "\nCursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" <<
				    "\nLeft-click to Zoom in" << 
				    "\nRight-click to Zoom out";

	text.setString(outputStream.str());
}

void ComplexPlane::updateRender()
{
 if (m_state == State::CALCULATING)
    {
        for (int i = 0; i < m_pixel_size.y; ++i)
        {
            for (int j = 0; j < m_pixel_size.x; ++j)
            {
                m_vArray[j + i * m_pixel_size.x].position = { (float)j, (float)i };
                Vector2f coords = mapPixelToCoords(Vector2i(j, i));
                int iterations = countIterations(coords);
                Uint8 r, g, b;
                iterationsToRGB(iterations, r, g, b);
                m_vArray[j + i * m_pixel_size.x].color = Color(r, g, b);
            }
        }
        m_state = State::DISPLAYING;
    }
}

// Private member functions
int ComplexPlane::countIterations(Vector2f coord)
{
    complex<float> z(0, 0);
    complex<float> c(coord.x, coord.y);
    int iterations = 0;
    while (abs(z) < 2 && iterations < MAX_ITER)
    {
        z = z * z + c;
        iterations++;
    }
    return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    if (count == MAX_ITER)
    {
        r = g = b = 0; 
    }
    else
      {
        size_t region = count / (MAX_ITER / 5);
        switch (region)
        {
            case 0: 
                r = 128 + count % 128;
                g = 0;
                b = 255 - count % 128;
                break;
            case 1:
                r = 0;
                g = 128 + count % 128;
                b = 128 + count % 128;
                break;
            case 2: 
                r = 0;
                g = 255 - count % 128;
                b = 0;
                break;
            case 3: 
                r = 255 - count % 128;
                g = 255 - count % 128;
                b = 0;
                break;
            case 4: 
                r = 255;
                g = 0;
                b = count % 128;
                break;
        }
    }
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
  float minX = m_plane_center.x - m_plane_size.x / 2.0f;
    float maxX = m_plane_center.x + m_plane_size.x / 2.0f;
    float minY = m_plane_center.y - m_plane_size.y / 2.0f;
    float maxY = m_plane_center.y + m_plane_size.y / 2.0f;
    float x = ((float)mousePixel.x / m_pixel_size.x) * (maxX - minX) + minX;
    float y = ((float)(m_pixel_size.y - mousePixel.y) / m_pixel_size.y) * (maxY - minY) + minY;

    return Vector2f(x, y); 
}
