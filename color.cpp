/* Author: Brendon Kofink
 *         Johann Rajadurai
 *         Aaron Sierra
 *         David Day
 *         Lucy Ray
 * Assignment Title: Ball Game
 * Assignment Description: user can launch balls to hit objects.
 * Due Date: 12/08/2021
 * Date Created: 11/29/2021
 * Date Last Modified: 12/03/2021
 */

#include "color.h"

Color Color::HSV(int H, int S, int V)
{
  //HSV! Hue Saturation Value. Great for multicolor stuff.
  //Found this formula on the internet.

  float s = S / 100.0;
  float v = V / 100.0;
  float C = s * v;
  //Had so much trouble with this line before I found out
  //fabs and fmod are abs and mod for floats.
  float X = C * (1 - fabs(fmod(H/60.0,2) - 1));
  float m = v - C;
  float r, g, b;
  if (H >= 0 && H < 60)
  {
    r = C, g = X, b = 0;
  }
  else if (H >= 60 && H < 120)
  {
    r = X, g = C, b = 0;
  }
  else if (H >= 120 && H < 180)
  {
    r = 0, g = C, b = X;
  }
  else if (H >= 180 && H < 240)
  {
    r = 0, g = X, b = C;
  }
  else if (H >= 240 && H < 300)
  {
    r = X, g = 0, b = C;
  }
  else
  {
    r = C, g = 0, b = X;
  }
  int R = (r + m) * 255;
  int G = (g + m) * 255;
  int B = (b + m) * 255;

  return Color(R, G, B);
}

//Lerping is so fun. Animations are fun.
Color Color::Lerp(Color a, Color b, float t,bool clamp)
{
  if(clamp&&t>1)t=1;
  if(clamp&&t<0)t=0;

  int R = a.R + (b.R - a.R) * t;
  int G = a.G + (b.G - a.G) * t;
  int B = a.B + (b.B - a.B) * t;

  if(R > 255) R = 255;
  if(G > 255) G = 255;
  if(B > 255) B = 255;

  return Color(R, G, B);
}
