#include "../headers/boat.hpp"

Boat::Boat()
{
  this->loadAssets();
  this->initBoat1();
  this->initCannon1();
}

void Boat::loadAssets()
{
  // load boat 1 water frame
  for (auto a = 1; a <= 4; a++)
  {
    Texture texture{};
    auto path = "assets/boat1/boat1_water_frame" + to_string(a) + ".png";
    texture.loadFromFile(path);

    this->boatWidth = texture.getSize().x;
    this->boatHeight = texture.getSize().y;

    this->vectorBoat1WaterFrame.push_back(texture);
  }

  // load cannon 1 frame
  for (auto a = 1; a <= 4; a++)
  {
    Texture texture{};
    texture.loadFromFile("assets/cannon1/cannon1_frame" + to_string(a) + ".png");

    this->cannonWidth = texture.getSize().x;
    this->cannonHeight = texture.getSize().y;

    this->vectorCannon1Frame.push_back(texture);
  }

  // load fire
  // this->textureFire.loadFromFile("assets/fire/fire1.png");
}

void Boat::initBoat1()
{
  this->boat.setPosition(Vector2f(this->boatWidth / 2, this->boatHeight / 2));
  // this->boat.setScale(Vector2f(2, 2));
}

void Boat::initCannon1()
{
  auto firstPos = Vector2f(
      this->boatWidth / 2, this->boatHeight / 2);
  this->cannon.setPosition(firstPos);
}

void Boat::loop()
{
  this->intervalBoat1WaterFrame = this->clockBoat1WaterFrame.getElapsedTime().asMilliseconds();
  this->intervalCannonFire = this->clockCannonFire.getElapsedTime().asMilliseconds();

  this->handleBoat1FrameWater();
  this->handleDirection();
  this->handleShooting();
}

void Boat::handleBoat1FrameWater()
{
  if (this->intervalBoat1WaterFrame >= this->delayBoat1WaterFrame)
  {
    if (this->currIndexBoat1WaterFrame < this->vectorBoat1WaterFrame.size() - 1)
      this->currIndexBoat1WaterFrame++;
    else
      this->currIndexBoat1WaterFrame = 0;
    this->clockBoat1WaterFrame.restart();
  }
}

void Boat::handleShooting()
{
  if (this->isShooting)
  {
    if (this->intervalCannonFire >= this->delayCannonFire / this->vectorCannon1Frame.size())
    {
      if (this->currIndexCannon1Frame < this->vectorCannon1Frame.size() - 1)
        this->currIndexCannon1Frame++;
      else
      {
        this->currIndexCannon1Frame = 0;
        this->isShooting = false;

        Fire fire(this->boatDirection, this->boat.getPosition(), this->boatWidth, this->boatHeight);

        this->vectorCannonFire.push_back(fire);
      }
      this->clockCannonFire.restart();
    }
  }
}

void Boat::handleDirection()
{
  if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Right))
    this->boatDirection = to_topRight;
  else if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Left))
    this->boatDirection = to_topLeft;
  else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Right))
    this->boatDirection = to_bottomRight;
  else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left))
    this->boatDirection = to_bottomLeft;

  else if (Keyboard::isKeyPressed(Keyboard::Up))
    this->boatDirection = to_top;
  else if (Keyboard::isKeyPressed(Keyboard::Down))
    this->boatDirection = to_bottom;
  else if (Keyboard::isKeyPressed(Keyboard::Right))
    this->boatDirection = to_right;
  else if (Keyboard::isKeyPressed(Keyboard::Left))
    this->boatDirection = to_left;
}

void Boat::draw(RenderWindow &window)
{
  this->window = &window;
  this->loop();

  // draw boat
  this->boat.setTexture(this->vectorBoat1WaterFrame.at(this->currIndexBoat1WaterFrame));

  this->boat.setOrigin(Vector2f(this->boatWidth / 2, this->boatHeight / 2));

  // 0   -> kanan
  // 45  -> kanan bawah
  // 90  -> bawah
  // 135 -> kiri bawah
  // 180 -> kiri
  // 225 -> kiri atas
  // 270 -> atas
  // 315 -> atas kanan

  // this->boat.setRotation(45);

  if (this->boatDirection == to_right)
  {
    this->boat.setRotation(0);
    this->cannon.setRotation(0);
  }
  else if (this->boatDirection == to_left)
  {
    this->boat.setRotation(180);
    this->cannon.setRotation(180);
  }
  else if (this->boatDirection == to_top)
  {
    this->boat.setRotation(270);
    this->cannon.setRotation(270);
  }
  else if (this->boatDirection == to_bottom)
  {
    this->boat.setRotation(90);
    this->cannon.setRotation(90);
  }

  else if (this->boatDirection == to_topRight)
  {
    this->boat.setRotation(315);
    this->cannon.setRotation(315);
  }
  else if (this->boatDirection == to_topLeft)
  {
    this->boat.setRotation(225);
    this->cannon.setRotation(225);
  }
  else if (this->boatDirection == to_bottomRight)
  {
    this->boat.setRotation(45);
    this->cannon.setRotation(45);
  }
  else if (this->boatDirection == to_bottomLeft)
  {
    this->boat.setRotation(135);
    this->cannon.setRotation(135);
  }

  window.draw(this->boat);

  // draw fire
  for (auto a = 0; a < this->vectorCannonFire.size(); a++)
  {
    Fire &fireAtIn = this->vectorCannonFire.at(a);
    fireAtIn.draw(window, this->fireSpeed);
    if (fireAtIn.isOverflow(window))
      this->vectorCannonFire.erase(this->vectorCannonFire.begin() + a);
  }

  // draw cannon
  this->cannon.setOrigin(Vector2f(
      this->cannonWidth / 2, this->cannonHeight / 2));
  this->cannon.setTexture(this->vectorCannon1Frame.at(this->currIndexCannon1Frame));

  window.draw(this->cannon);
}

void Boat::up()
{
  auto speed = this->boatSpeed;
  if (this->boatDirection == to_topRight || this->boatDirection == to_topLeft)
    speed = this->boatSpeed * sqrt(2) / 2;

  if (this->boat.getPosition().y > this->boatHeight / 2)
  {
    this->boat.move(Vector2f(0, speed * -1));
    this->cannon.move(Vector2f(0, speed * -1));
  }
}

void Boat::down()
{
  auto speed = this->boatSpeed;
  if (this->boatDirection == to_bottomLeft || this->boatDirection == to_bottomRight)
    speed = this->boatSpeed * sqrt(2) / 2;

  if (this->boat.getPosition().y < (this->window->getSize().y - this->boatWidth / 2))
  {
    this->boat.move(Vector2f(0, speed));
    this->cannon.move(Vector2f(0, speed));
  }
}

void Boat::right()
{
  auto speed = this->boatSpeed;
  if (this->boatDirection == to_topRight || this->boatDirection == to_bottomRight)
    speed = this->boatSpeed * sqrt(2) / 2;

  if (this->boat.getPosition().x < (this->window->getSize().x - this->boatWidth / 2))
  {
    this->boat.move(Vector2f(speed, 0));
    this->cannon.move(Vector2f(speed, 0));
  }
}

void Boat::left()
{
  auto speed = this->boatSpeed;
  if (this->boatDirection == to_topLeft || this->boatDirection == to_bottomLeft)
    speed = this->boatSpeed * sqrt(2) / 2;

  if (this->boat.getPosition().x > this->boatWidth / 2)
  {
    this->boat.move(Vector2f(speed * -1, 0));
    this->cannon.move(Vector2f(speed * -1, 0));
  }
}

void Boat::fire() { this->isShooting = true; }