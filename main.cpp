#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <limits>
//#include <vector>                                         //Apparently included in <SFML/Graphics.hpp>
#include <time.h> //TESTING
#include "Noisegen.hpp"
#include "basetile.hpp"

void buildtilemap(std::vector < std::vector <basetile> > & basetile_data, unsigned short xsize, unsigned short ysize);                      //Initialises a "matrix" of basetiles

void drawtilemap(const std::vector < std::vector <basetile> > & basetile_data, sf::RenderWindow &window, const sf::Vector2f &viewpoint);    //Draws a map of basetiles given the data, the window, and viewpoint

void changeviewpoint(sf::Vector2f &viewpoint, bool leftpressed, bool rightpressed, bool uppressed, bool downpressed);                       //Pans the screen based off which keys are pressed

int main()
{
    //testing
    srand (time(NULL));




    std::vector < std::vector <basetile> > basetile_data;               //This is an empty vector of vectors which contain base tiles
    //buildtilemap(basetile_data, 512, 512);                            //Currently working with 513 x 513 map
    buildtilemap(basetile_data, 120, 120);                              //debug tilemap

    //sf::RenderWindow window(sf::VideoMode(1280, 960), "Townhou", sf::Style::Close);       //For when people with 4:3 monitors want a distribution
    sf::RenderWindow window(sf::VideoMode(1920, 960), "Townhou", sf::Style::Close);
    window.setFramerateLimit(120);

    //sf::Vector2f viewpoint(960.f, -480.f);                            //The normal starting viewpoint
    sf::Vector2f viewpoint(0.f,-540.f);                                    //debug viewpoint

    bool    leftpressed = false,                                        //These are used for seamless scrolling
            rightpressed= false,                                        //
            uppressed   = false,                                        //
            downpressed = false;                                        //


    //unsigned char zoom_level 4;                                       //Primarily for rendering purposes; currently unused


//    std::cout << basetile_data[0][7].leftheight << std::endl;           //debug
//    std::cout << basetile_data[0][7].topheight << std::endl;
//    std::cout << basetile_data[0][7].rightheight << std::endl;
//    std::cout << basetile_data[0][7].botheight << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    leftpressed = true;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    rightpressed = true;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    uppressed = true;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    downpressed = true;
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    leftpressed = false;
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    rightpressed = false;
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    uppressed = false;
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    downpressed = false;
                }
            }
        }

        changeviewpoint(viewpoint, leftpressed, rightpressed, uppressed, downpressed);

        window.clear();
        drawtilemap(basetile_data, window, viewpoint);
        window.display();
    }

    return 0;
}

//A function to build a map from the defined map size
//
//
void buildtilemap(std::vector < std::vector <basetile> > & basetile_data, unsigned short xsize, unsigned short ysize)
{
    std::vector <basetile> temporary_y_vector;                          //Create a temporary vector of base tiles to create and push back iteratively

    PerlinNoise testingnoise(.125, .0625, 16, 8, rand());

    for(unsigned short i = 0; i < xsize; i++)                           //Tick up the main vector as long as defined
    {
        for(unsigned short j = 0; j < ysize; j++)                       //Tick up
        {
            //temporary_y_vector.push_back(basetile(i,j,rand() % 512,0));
            temporary_y_vector.push_back(basetile(16 * floor(testingnoise.GetHeight(i,j) + 16),         //basetile(left, top, right, bottom)
                                                  16 * floor(testingnoise.GetHeight(i+1,j) + 16),
                                                  16 * floor(testingnoise.GetHeight(i+1,j+1) + 16),
                                                  16 * floor(testingnoise.GetHeight(i,j+1) + 16)));
        }
        basetile_data.push_back(temporary_y_vector);
        temporary_y_vector.clear();
    }
}

//A function to draw the entirety of a vector of vectors of basetiles on a window given a viewpoint
//  TODO: Add in heights
//
void drawtilemap(const std::vector < std::vector <basetile> > & basetile_data, sf::RenderWindow &window, const sf::Vector2f &viewpoint)
{
    sf::ConvexShape flat_iso_tile(4);                       //      This code is to draw an openGL SFML isometric flat square.
    flat_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));      //      If you use sprites, remove it eventually
    flat_iso_tile.setPoint(1, sf::Vector2f(32.f, 16.f));    //      For some reason, I have these all drawing counterclockwise
    flat_iso_tile.setPoint(2, sf::Vector2f(64.f, 0.f));     //         even though all measurements are clockwise.  This should be fixed
    flat_iso_tile.setPoint(3, sf::Vector2f(32.f, -16.f));   //
    flat_iso_tile.setOutlineThickness(1);
    flat_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _0_1_1_1_iso_tile(4);
    _0_1_1_1_iso_tile.setPoint(0, sf::Vector2f(0.f, 16.f));
    _0_1_1_1_iso_tile.setPoint(1, sf::Vector2f(32.f, 16.f));
    _0_1_1_1_iso_tile.setPoint(2, sf::Vector2f(64.f, 0.f));
    _0_1_1_1_iso_tile.setPoint(3, sf::Vector2f(32.f, -16.f));
    _0_1_1_1_iso_tile.setOutlineThickness(1);
    _0_1_1_1_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _1_0_1_1_iso_tile(4);
    _1_0_1_1_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _1_0_1_1_iso_tile.setPoint(1, sf::Vector2f(32.f, 16.f));
    _1_0_1_1_iso_tile.setPoint(2, sf::Vector2f(64.f, 0.f));
    _1_0_1_1_iso_tile.setPoint(3, sf::Vector2f(32.f, 0.f));
    _1_0_1_1_iso_tile.setOutlineThickness(1);
    _1_0_1_1_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _1_1_0_1_iso_tile(4);
    _1_1_0_1_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _1_1_0_1_iso_tile.setPoint(1, sf::Vector2f(32.f, 16.f));
    _1_1_0_1_iso_tile.setPoint(2, sf::Vector2f(64.f, 15.f));
    _1_1_0_1_iso_tile.setPoint(3, sf::Vector2f(32.f, -16.f));
    _1_1_0_1_iso_tile.setOutlineThickness(1);
    _1_1_0_1_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _1_1_1_0_iso_tile(4);
    _1_1_1_0_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _1_1_1_0_iso_tile.setPoint(1, sf::Vector2f(32.f, 32.f));
    _1_1_1_0_iso_tile.setPoint(2, sf::Vector2f(64.f, 0.f));
    _1_1_1_0_iso_tile.setPoint(3, sf::Vector2f(32.f, -16.f));
    _1_1_1_0_iso_tile.setOutlineThickness(1);
    _1_1_1_0_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _0_1_1_0_iso_tile(4);
    _0_1_1_0_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _0_1_1_0_iso_tile.setPoint(1, sf::Vector2f(32.f, 16.f));
    _0_1_1_0_iso_tile.setPoint(2, sf::Vector2f(64.f, -16.f));
    _0_1_1_0_iso_tile.setPoint(3, sf::Vector2f(32.f, -32.f));
    _0_1_1_0_iso_tile.setOutlineThickness(1);
    _0_1_1_0_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _0_0_1_1_iso_tile(4);
    _0_0_1_1_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _0_0_1_1_iso_tile.setPoint(1, sf::Vector2f(32.f, 0.f));
    _0_0_1_1_iso_tile.setPoint(2, sf::Vector2f(64.f, -16.f));
    _0_0_1_1_iso_tile.setPoint(3, sf::Vector2f(32.f, -16.f));
    _0_0_1_1_iso_tile.setOutlineThickness(1);
    _0_0_1_1_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _1_0_0_1_iso_tile(4);
    _1_0_0_1_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _1_0_0_1_iso_tile.setPoint(1, sf::Vector2f(32.f, 16.f));
    _1_0_0_1_iso_tile.setPoint(2, sf::Vector2f(64.f, 16.f));
    _1_0_0_1_iso_tile.setPoint(3, sf::Vector2f(32.f, 0.f));
    _1_0_0_1_iso_tile.setOutlineThickness(1);
    _1_0_0_1_iso_tile.setOutlineColor(sf::Color(255,255,255,128));

    sf::ConvexShape _1_1_0_0_iso_tile(4);
    _1_1_0_0_iso_tile.setPoint(0, sf::Vector2f(0.f, 0.f));
    _1_1_0_0_iso_tile.setPoint(1, sf::Vector2f(32.f, 32.f));
    _1_1_0_0_iso_tile.setPoint(2, sf::Vector2f(64.f, 16.f));
    _1_1_0_0_iso_tile.setPoint(3, sf::Vector2f(32.f, -16.f));
    _1_1_0_0_iso_tile.setOutlineThickness(1);
    _1_1_0_0_iso_tile.setOutlineColor(sf::Color(255,255,255,128));





    int x1, y1;                                             //      used for algebraic purposes

    float   xsize = basetile_data.size(),                   //      The arbitrary "x" size of the game map
            ysize;                                          //      The arbitrary "y" size of the game map;  In theory this supports non-homologous lengths, but that'll never get implemented?
                                                            //      Not worth making width variable, so why make height variable?
                                                            //      Will probably take this out eventually for optimization or something


    // see (COMMENT ID: 000001) for information about this loop
    for(unsigned int i = std::max((viewpoint.x/64 - viewpoint.y/32) - 48, 0.f); i < std::min(xsize, ((viewpoint.x/64 - viewpoint.y/32) + 1920/64) + 0); i++)
    {
        ysize = basetile_data[i].size();                    //      The arbitrary "y" size of the fame map;  See above variable creation


    // see (COMMENT ID: 000002) for information about this loop
        for(unsigned int j = std::max((viewpoint.x/64 + viewpoint.y/32) + 0, 0.f); j < std::min(ysize, ((viewpoint.x/64 + viewpoint.y/32) + 960/32 + 48)); j++)
        {
            x1 = 32 * (i + j);      //the x and y solutions to the transformation matrix [x] [ 32      32 ]
            y1 = 16 * (-i + j);     //                                                   [y] [-16      16 ]

            if((basetile_data[i][j].leftheight == basetile_data[i][j].topheight) &&
               (basetile_data[i][j].topheight == basetile_data[i][j].rightheight) &&
               (basetile_data[i][j].rightheight == basetile_data[i][j].botheight))
            {
                flat_iso_tile.setFillColor(sf::Color(std::min(basetile_data[i][j].topheight/2.f, 255.f), std::min(basetile_data[i][j].rightheight/2.f, 255.f), std::min(basetile_data[i][j].botheight/2.f, 255.f), 255));
                flat_iso_tile.setPosition(sf::Vector2f(x1 - viewpoint.x, y1 - viewpoint.y - basetile_data[i][j].leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(flat_iso_tile);
            }
            else if ((basetile_data[i][j].leftheight < basetile_data[i][j].topheight) &&
                     (basetile_data[i][j].topheight == basetile_data[i][j].rightheight) &&
                     (basetile_data[i][j].rightheight == basetile_data[i][j].botheight))
            {
                _0_1_1_1_iso_tile.setFillColor(sf::Color(std::min(basetile_data[i][j].topheight/2.f, 255.f), std::min(basetile_data[i][j].rightheight/2.f, 255.f), std::min(basetile_data[i][j].botheight/2.f, 255.f), 255));
                _0_1_1_1_iso_tile.setPosition(sf::Vector2f(x1 - viewpoint.x, y1 - viewpoint.y - basetile_data[i][j].botheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_0_1_1_1_iso_tile);
            }
            else if ((basetile_data[i][j].leftheight > basetile_data[i][j].topheight) &&
                     (basetile_data[i][j].topheight < basetile_data[i][j].rightheight) &&
                     (basetile_data[i][j].rightheight == basetile_data[i][j].botheight))
            {
                _1_0_1_1_iso_tile.setFillColor(sf::Color(std::min(basetile_data[i][j].topheight/2.f, 255.f), std::min(basetile_data[i][j].rightheight/2.f, 255.f), std::min(basetile_data[i][j].botheight/2.f, 255.f), 255));
                _1_0_1_1_iso_tile.setPosition(sf::Vector2f(x1 - viewpoint.x, y1 - viewpoint.y - basetile_data[i][j].leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_1_0_1_1_iso_tile);
            }
            else if ((basetile_data[i][j].leftheight == basetile_data[i][j].topheight) &&
                     (basetile_data[i][j].topheight > basetile_data[i][j].rightheight) &&
                     (basetile_data[i][j].rightheight < basetile_data[i][j].botheight))
            {
                _1_1_0_1_iso_tile.setFillColor(sf::Color(std::min(basetile_data[i][j].topheight/2.f, 255.f), std::min(basetile_data[i][j].rightheight/2.f, 255.f), std::min(basetile_data[i][j].botheight/2.f, 255.f), 255));
                _1_1_0_1_iso_tile.setPosition(sf::Vector2f(x1 - viewpoint.x, y1 - viewpoint.y - basetile_data[i][j].leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_1_1_0_1_iso_tile);
            }
            else if ((basetile_data[i][j].leftheight == basetile_data[i][j].topheight) &&
                     (basetile_data[i][j].topheight == basetile_data[i][j].rightheight) &&
                     (basetile_data[i][j].rightheight > basetile_data[i][j].botheight))
            {
                _1_1_1_0_iso_tile.setFillColor(sf::Color(std::min(basetile_data[i][j].topheight/2.f, 255.f), std::min(basetile_data[i][j].rightheight/2.f, 255.f), std::min(basetile_data[i][j].botheight/2.f, 255.f), 255));
                _1_1_1_0_iso_tile.setPosition(sf::Vector2f(x1 - viewpoint.x, y1 - viewpoint.y - basetile_data[i][j].leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_1_1_1_0_iso_tile);
            }
            else if ((basetile_data[i][j].leftheight < basetile_data[i][j].topheight) &&
                     (basetile_data[i][j].topheight == basetile_data[i][j].rightheight) &&
                     (basetile_data[i][j].rightheight > basetile_data[i][j].botheight))
            {
                _0_1_1_0_iso_tile.setFillColor(sf::Color(basetile_data[i][j].topheight/2.f, 0, 0, 255));
                _0_1_1_0_iso_tile.setPosition(sf::Vector2f(x1 - viewpoint.x, y1 - viewpoint.y - basetile_data[i][j].leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_0_1_1_0_iso_tile);
            }
            else if((basetile_data[i][j].leftheight == basetile_data[i][j].topheight) &&
                     (basetile_data[i][j].topheight < basetile_data[i][j].rightheight) &&
                     (basetile_data[i][j].rightheight == basetile_data[i][j].botheight))
            {
                _0_0_1_1_iso_tile.setFillColor(sf::Color(basetile_data[i][j].topheight/2.f, 0, 0, 255));
                _0_0_1_1_iso_tile.setPosition(sf::Vector2f(x1 - viewpoint.x, y1 - viewpoint.y - basetile_data[i][j].leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_0_0_1_1_iso_tile);
            }
            else if ((basetile_data[i][j].leftheight > basetile_data[i][j].topheight) &&
                     (basetile_data[i][j].topheight == basetile_data[i][j].rightheight) &&
                     (basetile_data[i][j].rightheight < basetile_data[i][j].botheight))
            {
                _1_0_0_1_iso_tile.setFillColor(sf::Color(basetile_data[i][j].topheight/2.f, 0, 0, 255));
                _1_0_0_1_iso_tile.setPosition(sf::Vector2f(x1 - viewpoint.x, y1 - viewpoint.y - basetile_data[i][j].leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_1_0_0_1_iso_tile);
            }
            else if ((basetile_data[i][j].leftheight == basetile_data[i][j].topheight) &&
                     (basetile_data[i][j].topheight > basetile_data[i][j].rightheight) &&
                     (basetile_data[i][j].rightheight == basetile_data[i][j].botheight))
            {
                //_1_1_0_0_iso_tile.setFillColor(sf::Color(std::min(basetile_data[i][j].topheight/2.f, 255.f), std::min(basetile_data[i][j].rightheight/2.f, 255.f), std::min(basetile_data[i][j].botheight/2.f, 255.f), 255));
                _1_1_0_0_iso_tile.setFillColor(sf::Color(basetile_data[i][j].topheight/2.f, 0, 0, 255));
                _1_1_0_0_iso_tile.setPosition(sf::Vector2f(x1 - viewpoint.x, y1 - viewpoint.y - basetile_data[i][j].leftheight));        //Set the new position of the template tile offset by the viewpoint

                window.draw(_1_1_0_0_iso_tile);
            }
        }
    }
}


//A function that scrolls the viewpoint when certain keys are pressed
//  TODO: Make viewpoint dependent on map location; i.e. stay a certain distance from map (will scroll diagonally)
//
void changeviewpoint(sf::Vector2f &viewpoint, bool leftpressed, bool rightpressed, bool uppressed, bool downpressed)
{
    viewpoint.x = std::max(viewpoint.x + 12 * rightpressed - 12 * leftpressed, 0.f);    //
    viewpoint.y = std::max(viewpoint.y + 12 * downpressed  - 12 * uppressed, -8208.f);  //return std::min eventually
}
