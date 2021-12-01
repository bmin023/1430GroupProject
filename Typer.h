#include <fstream>
#include "SDL_Plotter.h"
#include "Color.h"
#include "vec2.h"

using namespace std;

struct TextObject
{
  string text;
  vec2 pos;
  int size;
  int layer;
  Color color;
  bool back;
  bool del;
  bool vis;
  TextObject();
  TextObject(string text, vec2 pos, int size, Color color, bool back, bool del);
};

class Typer
{
private:
  //5x5 matrices
  bool characters[39][5][5];
  void ImportLetters();
  void ImportNumbers();
  void ImportSymbols();
  bool TryLetter(char c, int& loc);
  void DrawBox(SDL_Plotter &g, int x, int y, int size, Color c);

public:
  Typer();
  void Write(string word, SDL_Plotter &g, vec2 pos, Color c, int size = 2, bool back = true);
  void Write(TextObject obj, SDL_Plotter &g);
};
