#include "Typer.h"

Typer::Typer()
{
  ImportLetters();
  ImportNumbers();
  ImportSymbols();
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
          characters[i][j][k] = true;
        }
        else
        {
          characters[i][j][k] = false;
        }
      }
      file.ignore();
    }
  }

  file.close();
}

void Typer::ImportNumbers() {
  ifstream file("num.txt");
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
          characters[i+26][j][k] = true;
        }
        else
        {
          characters[i+26][j][k] = false;
        }
      }
      file.ignore();
    }
  }

  file.close();
}

void Typer::ImportSymbols() {
  ifstream file("special.txt");
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
          characters[i+36][j][k] = true;
        }
        else
        {
          characters[i+36][j][k] = false;
        }
      }
      file.ignore();
    }
  }

  file.close();
}

bool Typer::TryLetter(char c, int& index) {
  bool found = false;
  if(c=='!') {
    index = 36;
    found = true;
  }
  else if(c==':') {
    index = 37;
    found = true;
  }
  else if(c=='.') {
    index = 38;
    found = true;
  }
  return found;
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
  int character;
  for (int i = 0; i < word.length(); i++)
  {
    if(isalpha(word[i])) {
      character = toupper(word[i]) - 'A';
    } else if(isdigit(word[i])) {
      character = word[i] - '0' + 26;
    }
    else if(!TryLetter(word[i], character)) {
      character = 0;
    }
    for (int j = 0; j < 5; j++)
    {
      for (int k = 0; k < 5; k++)
      {
        if (characters[character][j][k] && word[i] != ' ')
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