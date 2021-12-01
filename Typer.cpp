#include "Typer.h"

Typer::Typer()
{
  ImportLetters();
}

void Typer::ImportLetters()
{
  ifstream file("A.txt");
  char c;
  for (int i = 0; i < 26; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      for (int k = 0; k < 5; k++)
      {
        file.get(c);
        if (c == '1')
        {
          letters[i][j][k] = true;
        }
        else
        {
          letters[i][j][k] = false;
        }
      }
      file.ignore();
    }
  }

  file.close();
}

void Typer::DrawBox(SDL_Plotter &g, int x, int y, int size, Color c)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      g.plotPixel(x + i, y + j, c.R, c.G, c.B);
    }
  }
}

void Typer::Write(string word, SDL_Plotter &g, vec2 pos, Color c, int size, bool back)
{
  for (int i = 0; i < word.length(); i++)
  {
    int letter = toupper(word[i]) - 'A';
    for (int j = 0; j < 5; j++)
    {
      for (int k = 0; k < 5; k++)
      {
        if (letters[letter][j][k] && word[i] != ' ')
        {
          DrawBox(g, pos.x + i*5*size+i*size + k * size, pos.y + j * size, size, c);
        }
        else if (back)
        {
          DrawBox(g, pos.x + i * 5 * size+i*size + k * size, pos.y + j * size, size, BLANK);
        }
      }
    }
  }
}