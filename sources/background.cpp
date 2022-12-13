#include "../headers/background.hpp"

Background::Background()
{
  this->init();
}

void Background::init()
{
  this->texture.loadFromFile("assets/water/water.png");
  this->tileX = this->texture.getSize().x;
  this->tileY = this->texture.getSize().y;
}

void Background::draw(RenderWindow &window)
{
  auto windowSize = window.getSize();
  auto windowX = windowSize.x;
  auto windowY = windowSize.y;

  for (auto a = 0; a < (windowX / this->tileX); a++)
    for (auto b = 0; b < (windowY / this->tileY); b++)
    {
      Sprite sprite{};
      sprite.setTexture(this->texture);
      sprite.setPosition(Vector2f(
          this->tileX * a, this->tileY * b));

      window.draw(sprite);
    }
}