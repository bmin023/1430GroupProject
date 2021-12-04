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
  /*
  * description: Default constructor
  * return: none
  * precondition: The user wants to create a text object
  * postcondition: The text object is created
  */
  TextObject();
  /*
  * description: Constructor with parameters
  * return: none
  * precondition: The user wants to create a text object
  * postcondition: The text object is created
  */
  TextObject(string text, vec2 pos, int size, Color color, bool back, bool del);
};

class Typer
{
private:
  //5x5 matrices
  bool characters[41][5][5];
  /*
  * description: Loads the letters into the matrix
  * return: void
  * precondition: The user wants to load the letters
  * postcondition: The letters are loaded into the matrix
  */
  void ImportLetters();
  /*
  * description: Loads the numbers into the matrix
  * return: void
  * precondition: The user wants to load the numbers
  * postcondition: The numbers are loaded into the matrix
  */
  void ImportNumbers();
  /*
  * description: Loads the symbols into the matrix
  * return: void
  * precondition: The user wants to load the symbols
  * postcondition: The symbols are loaded into the matrix
  */
  void ImportSymbols();
  /*
  * description: Checks if a character exists in the matrix
  * return: bool
  * precondition: loc exists
  * postcondition: Returns true if the character exists. 
  *  loc is set to the location of the character
  */
  bool TryLetter(char c, int& loc);
  /*
  * description: Draws a box to the screen
  * return: void
  * precondition: g is a valid SDL_Plotter
  * postcondition: A box is drawn to the screen
  */
  void DrawBox(SDL_Plotter &g, int x, int y, int size, Color c);

public:
  /*
  * description: Constructor
  * return: none
  * precondition: The user wants to create a Typer object
  * postcondition: The Typer object is created
  */
  Typer();
  /*
  * description: Draws the text to the screen
  * return: void
  * precondition: g is a valid SDL_Plotter. All characters are valid
  * postcondition: The text is drawn to the screen
  */
  void Write(string word, SDL_Plotter &g, vec2 pos, Color c, int size = 2, bool back = true);
  /*
  * description: Draws the text to the screen (takes a text object)
  * return: void
  * precondition: g is a valid SDL_Plotter. All characters are valid
  * postcondition: The text is drawn to the screen
  */
  void Write(TextObject obj, SDL_Plotter &g);
};
