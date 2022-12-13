#ifndef fire_hpp
#define fire_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "boat_direction.hpp"

using namespace sf;
using namespace std;

class Fire
{
private:
  Vector2f boatPos;
  BoatDirection boatDirection;
  Texture texture;
  Sprite sprite;
  double height;
  double width;

  double boatHeight;
  double boatWidth;

  void loadAssets();
  void init();

public:
  Fire(BoatDirection direction, Vector2f boatPos, double boatW, double boatH);
  void draw(RenderWindow &window, double speed);
  Sprite getSpriteFire();
  bool isOverflow(RenderWindow &window);
};

#endif