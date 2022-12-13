#ifndef boat_hpp
#define boat_hpp

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "boat_direction.hpp"
#include "fire.hpp"

using namespace sf;
using namespace std;

class Boat
{
private:
  RenderWindow *window;

  vector<Texture> vectorBoat1WaterFrame;
  Sprite boat;
  BoatDirection boatDirection = to_right;
  int boatSpeed = 5;
  double boatWidth;
  double boatHeight;

  Clock clockBoat1WaterFrame;
  double intervalBoat1WaterFrame;
  double delayBoat1WaterFrame = 150;
  int currIndexBoat1WaterFrame = 0;

  vector<Texture> vectorCannon1Frame;
  Sprite cannon;
  double cannonWidth;
  double cannonHeight;

  Clock clockCannonFire;
  double intervalCannonFire;
  double delayCannonFire = 200;
  double fireSpeed = 10;
  vector<Fire> vectorCannonFire;
  int currIndexCannon1Frame = 0;
  bool isShooting = false;

  void loadAssets();
  void loop();
  void initBoat1();
  void initCannon1();
  void handleBoat1FrameWater();
  void handleDirection();
  void handleShooting();

public:
  Boat();
  void draw(RenderWindow &window);
  void up();
  void down();
  void right();
  void left();
  void fire();
};

#endif