#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "controls.h"

const unsigned int renderWidth = 320;
const unsigned int renderHeight = 240;
const unsigned int windowUpscale = 3;

// holds a single pixel
struct Pixel {
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  // no alpha value, pixels are assumed to be fully opaque
};

int main()
{
  auto window = sf::RenderWindow{ { renderWidth * windowUpscale, renderHeight * windowUpscale }, "Not Doom" };
  window.setFramerateLimit(60);

  // create a grid of black pixels
  std::vector<std::vector<Pixel> > screenPixels{
    renderWidth, std::vector<Pixel>{ renderHeight, Pixel{0, 0, 0} }
  };

  sf::Image bufferImage;
  sf::Texture bufferTexture;
  sf::Sprite bufferSprite;
  sf::RenderTexture upscaler;
  sf::Sprite upscalerSprite;

  window.setView(sf::View(sf::FloatRect(0, 0, renderWidth, renderHeight)));
  bufferImage.create(renderWidth, renderHeight);
  upscaler.create(renderWidth, renderHeight);
  upscaler.setSmooth(false);
  upscalerSprite.setTexture(upscaler.getTexture());

  while (window.isOpen())
  {
    for (auto event = sf::Event{}; window.pollEvent(event);)
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    // update the action map
    for (const auto &pair : keybinds) {
      if (sf::Keyboard::isKeyPressed(pair.second.key) && (sf::Keyboard::isKeyPressed(modifierKey) == pair.second.requiresModifier)) {
        actionMap[pair.first] = true;
      }else{
        actionMap[pair.first] = false;
      }
    }

    window.clear();
    upscaler.clear();

    for (size_t x{0}; x < renderWidth; ++x) {
      for (size_t y{0}; y < renderHeight; ++y) {
        bufferImage.setPixel(x, y, {
          screenPixels[x][y].red,
          screenPixels[x][y].green,
          screenPixels[x][y].blue
        });
      }
    }
    bufferTexture.loadFromImage(bufferImage);
    bufferSprite.setTexture(bufferTexture);
    upscaler.draw(bufferSprite);

    upscaler.display();
    window.draw(upscalerSprite);
    window.display();
  }
  return 0;
}