#ifndef background_hpp
#define background_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Background
{
private:
  Texture texture;
  double tileX;
  double tileY;

  void init();

public:
  Background();
  void draw(RenderWindow &window);
};

#endif