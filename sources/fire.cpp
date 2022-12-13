#include "../headers/fire.hpp"

Fire::Fire(BoatDirection direction, Vector2f boatPos, double boatW, double boatH)
{
  this->boatPos = boatPos;
  this->boatWidth = boatW;
  this->boatHeight = boatH;
  this->boatDirection = direction;

  this->loadAssets();
  this->init();
}

void Fire::loadAssets()
{
  this->texture.loadFromFile("assets/fire/fire1.png");
  this->width = this->texture.getSize().x;
  this->height = this->texture.getSize().y;
}

void Fire::init()
{
  this->sprite.setPosition(Vector2f(this->boatPos.x, this->boatPos.y));
  this->sprite.setScale(Vector2f(.5, .5));
}

void Fire::draw(RenderWindow &window, double speed)
{
  this->sprite.setTexture(this->texture);
  this->sprite.setOrigin(Vector2f(this->width / 2, this->height / 2));

  window.draw(this->sprite);

  // move fire
  if (this->boatDirection == to_topRight || this->boatDirection == to_topLeft || this->boatDirection == to_bottomRight || this->boatDirection == to_bottomLeft)
    speed *= sqrt(2) / 2;

  Vector2f fireMove{};
  double rotation = 0;
  switch (this->boatDirection)
  {
  case to_top:
    fireMove.y = speed * -1;
    rotation = 270;
    break;
  case to_right:
    fireMove.x = speed;
    rotation = 0;
    break;
  case to_bottom:
    fireMove.y = speed;
    rotation = 90;
    break;
  case to_left:
    fireMove.x = speed * -1;
    rotation = 180;
    break;

  case to_topRight:
    fireMove.x = speed;
    fireMove.y = speed * -1;
    rotation = 315;
    break;
  case to_topLeft:
    fireMove.x = speed * -1;
    fireMove.y = speed * -1;
    rotation = 225;
    break;
  case to_bottomRight:
    fireMove.x = speed;
    fireMove.y = speed;
    rotation = 45;
    break;
  case to_bottomLeft:
    fireMove.x = speed * -1;
    fireMove.y = speed;
    rotation = 135;
    break;
  }

  this->sprite.setRotation(rotation);
  this->sprite.move(fireMove);
}

Sprite Fire::getSpriteFire() { return this->sprite; }

bool Fire::isOverflow(RenderWindow &window)
{
  auto windowSize = window.getSize();
  auto windowX = windowSize.x;
  auto windowY = windowSize.y;
  auto pos = this->sprite.getPosition();
  return (pos.x <= 0 || pos.x >= windowX || pos.y <= 0 || pos.y >= windowY);
}