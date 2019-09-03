#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

int main()
{
    srand(time(0));        //Setting for random sequence generation.

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");      //Creating the window.

    int grid[12][12];
    int sgrid[12][12]; //for showing

    Texture t;
    t.loadFromFile("tiles.jpg");        //Loading the image.
    Sprite s(t);        //Sprite class for displaying the texture.

    Vector2u texture_size = t.getSize();                             //Getting length of the texture.
    //std::cout<<(float)texture_size.x<<" "<<(float)texture_size.y;

    int w = (float)texture_size.y;       //Length of the texture.

    for (int i=1;i<=10;i++)     //Setting bombs at random places inside the grid.
     for (int j=1;j<=10;j++)
      {
        sgrid[i][j] = 10;
        if (rand()%5 == 0)
            grid[i][j] = 9;         //Position of bomb in picture.
            //std::cout<<i<<" "<<j<<"\n";}
        else
            grid[i][j] = 0;
      }

    for (int i=1;i<=10;i++)     //Setting grid with numbers ranging from 1-11.
     for (int j=1;j<=10;j++)
      {
        int n=0;
        if (grid[i][j]==9) continue;
        if (grid[i+1][j]==9) n++;
        if (grid[i][j+1]==9) n++;
        if (grid[i-1][j]==9) n++;
        if (grid[i][j-1]==9) n++;
        if (grid[i+1][j+1]==9) n++;
        if (grid[i-1][j-1]==9) n++;
        if (grid[i-1][j+1]==9) n++;
        if (grid[i+1][j-1]==9) n++;
        grid[i][j]=n;
      }

    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);
        //std::cout<<pos.x<<" "<<pos.y;
        int x = pos.x/w;        //Dividing by 32 to get it inside the range.
        int y = pos.y/w;

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
              if (e.key.code == Mouse::Left) sgrid[x][y]=grid[x][y];    //Placing the input in other grid.
            else if (e.key.code == Mouse::Right) sgrid[x][y]=11;      //11 is the position of the flag.
        }

        app.clear(Color::Blue);       //Background color blue.

        for (int i=1;i<=10;i++)     //Drawing the game.
         for (int j=1;j<=10;j++)
          {
           if (sgrid[x][y]==9) sgrid[i][j]=grid[i][j];
           s.setTextureRect(IntRect(sgrid[i][j]*w,0,w,w));      //x,y,height,width
           s.setPosition(i*w, j*w);
           app.draw(s);                                         //Drawing the grid.
          }

        app.display();
    }

    return 0;
}
