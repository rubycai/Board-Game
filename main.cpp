//
//  main.cpp
//  Project 3
//
//  Created by Ruby on 5/10/14.
//  Copyright (c) 2014 Ruby. All rights reserved.
//

#include "Player.h"
#include "Board.h"
#include "Side.h"
#include "Game.h"
#include <iostream>
#include <cassert>
using namespace std;


/*#include <iostream>
#include "Side.h"
#include "Board.h"
#include "Player.h"
#include "Game.h"
using namespace std;



int main(int argc, const char * argv[])
{
    cerr << SOUTH << endl;
    int* a[2];
    a[0]=new int[8];
    a[0][1]=3;
    for (int i=0; i<8; i++)
        a[0][i]=i;
    cerr << a[0][1] << endl;
    
    Board c(3, 5);
    Board d(c);
    Side endSide;
    int endHole;
    cerr << c.sow(NORTH, 1, endSide, endHole) <<endl;
    cerr << endSide << " " << endHole << endl;
    cerr << c.totalBeans() << endl;
    cerr << c.beansInPlay(NORTH) << endl;
    cerr << c.beans(NORTH, 3) << endl;
    cerr << c.beans(SOUTH, 0) << endl;
    
    Player* player[4];
    player[0] = new HumanPlayer("Ruby");
    //player[0]->chooseMove(d, NORTH);
    player[1] = new BadPlayer("fool");
    player[2] = new BadPlayer("stupid");
    cerr << d.beansInPlay(NORTH) << endl;
    cerr << d.beans(NORTH, 3) << endl;
    cerr << d.beans(SOUTH, 0) << endl;
    
    Game game(d, player[2], player[1]);
    cout << game.beans(NORTH, 3) << endl;
    //game.display();
    game.play();
    //cout << game.move() << " " << game.move()<< " ";
    //cout << game.move() << endl;
    //game.display();
    
    bool over, hasWinner;
    Side winner;
    game.status(over, hasWinner, winner);
    cout << over << endl;
}
*/

/*#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doGameTests()
{
    BadPlayer bp1("Bart");
    BadPlayer bp2("Homer");
    Board b(3,0);
    b.setBeans(SOUTH, 1, 2);
    b.setBeans(NORTH, 2, 1);
    b.setBeans(NORTH, 3, 2);
    Game g(b, &bp1, &bp2);
    bool over;
    bool hasWinner;
    Side winner;
    //    Homer
    //   0  1  2
    // 0         0
    //   2  0  0
    //    Bart
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, 0) == 0 && g.beans(SOUTH, 0) == 0 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
           g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    
    g.move();
    //   0  1  0
    // 0         3
    //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, 0) == 0 && g.beans(SOUTH, 0) == 3 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
    
    g.move();
    //   1  0  0
    // 0         3
    //   0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, 0) == 0 && g.beans(SOUTH, 0) == 3 &&
           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);
    
    g.move();
    //   1  0  0
    // 0         3
    //   0  0  1
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, 0) == 0 && g.beans(SOUTH, 0) == 3 &&
           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);
    
    g.move();
    //   0  0  0
    // 1         4
    //   0  0  0
    g.status(over, hasWinner, winner);
    assert(over && g.beans(NORTH, 0) == 1 && g.beans(SOUTH, 0) == 4 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
    assert(hasWinner && winner == SOUTH);
}

int main()
{
    doGameTests();
    cout << "Passed all tests" << endl;
}*/

/*#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <iostream>
#include <cassert>
using namespace std;

void doPlayerTests()
{
    HumanPlayer hp("Marge");
    assert(hp.name() == "Marge"  &&  hp.isInteractive());
    BadPlayer bp("Homer");
    assert(bp.name() == "Homer"  &&  !bp.isInteractive());
    SmartPlayer sp("Lisa");
    assert(sp.name() == "Lisa"  &&  !sp.isInteractive());
    Board b(3,2);
    b.setBeans(SOUTH, 2, 0);
    cout << "=========" << endl;
    int n = hp.chooseMove(b, SOUTH);
    cout << "=========" << endl;
    assert(n == 1  ||  n == 3);
    n = bp.chooseMove(b, SOUTH);
    assert(n == 1  ||  n == 3);
    n = sp.chooseMove(b, SOUTH);
    //assert(n == 1  ||  n == 3);
    cerr << n << endl;
}

int main()
{
    doPlayerTests();
    cout << "Passed all tests" << endl;
}*/

//////////////////////////////////// play the game //////////////////////////////
#include "Player.h"
#include "Board.h"
#include "Side.h"
#include "Game.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    int endHole=-1;
    Side endSide=NORTH;
    Board b(3,2);
    //b.setBeans(SOUTH, 1, 0);
    //int bestHole, value, depth;
    //evalMove(NORTH, b, bestHole, value, depth);
    //cout << bestHole;
    Player* player[4];
    player[0]=new HumanPlayer("Ruby");
    player[1]=new BadPlayer("fool");
    player[2]=new HumanPlayer("Lucy");
    player[3]=new SmartPlayer("smart");
    Game game(b, player[0], player[3]);
    
    //int bestHole=0, value=0, depth=0;
    //cout << MovePossible(b, NORTH) << endl;
    //evalMove(NORTH, b, bestHole, value, depth);
    //cout << bestHole << endl << value << endl;
    //cout << player[3]->chooseMove(b, NORTH) << endl;
    game.play();
    //game.move();
    //player[0]->chooseMove(b, SOUTH);
    b.sow(SOUTH, 3, endSide, endHole);
    cout << endSide << " " << endHole <<endl;
    for (int i=0; i<4; i++)
        delete player[i];
}


///////////////////////////////////////// test data ///////////////////////////////////////////////////
/*#include "Player.h"
#include "Board.h"
#include "Side.h"
#include "Game.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Side endSide;
    int endHole;
    Board b(3,2);
    assert(b.holes()==3 && b.beansInPlay(NORTH)==6 && b.beans(SOUTH, 0)==0 && b.beans(SOUTH, 1)==2 && b.totalBeans()==12);
    assert(b.sow(NORTH, 0, endSide, endHole)==false && b.sow(NORTH, -1, endSide, endHole)==false && b.sow(NORTH, 4, endSide, endHole)==false);
    assert(b.sow(NORTH, 2, endSide, endHole)==true && endSide==NORTH && endHole==0 && b.beans(NORTH, 1)==3);
    assert(b.sow(NORTH, 2, endSide, endHole)==false);
    assert(b.sow(NORTH, 1, endSide, endHole)==true && endSide==SOUTH && endHole==2);
    
    Board c(2,4);
    assert(c.sow(NORTH, 1, endSide, endHole)==true && endSide==NORTH && endHole==2);
    
    //test moveToPot function
    assert(c.moveToPot(NORTH, 2, NORTH)==true && c.beans(NORTH, 2)==0 && c.beans(NORTH, 0)==6);
    //c.sow(SOUTH, 1, endSide, endHole);
    //cout << endHole << endSide;
    
    
    //======================= player.cpp ==========================//
    Board a(3,0);
    Player* player[5];
    player[0] = new HumanPlayer("Ruby");
    player[1] = new BadPlayer("fool");
    player[2] = new SmartPlayer("clever");
    assert(player[0]->isInteractive()==true && player[1]->isInteractive()==false && player[2]->isInteractive()==false);
    assert(player[0]->name()=="Ruby");
    assert(player[0]->chooseMove(a, NORTH)==-1 && player[1]->chooseMove(a, NORTH)==-1 && player[2]->chooseMove(a, NORTH)==-1);
    a.setBeans(SOUTH, 2, 3);
    a.setBeans(NORTH, 3, 2);
    assert(player[1]->chooseMove(a, NORTH)==3 && player[2]->chooseMove(a, SOUTH)==2);
    
    //====================== Game.cpp ===========================//
    Board d(3, 2);
    Game game(d, player[2], player[1]);
    game.display();    //test display function
    bool over, hasWinner;
    Side Winner;
    game.status(over, hasWinner, Winner);
    assert(over==false);
    while (game.move())
    {}
    game.status(over, hasWinner, Winner);
    assert(over==true && hasWinner==true && Winner==SOUTH);
    game.play();
    assert(game.beans(SOUTH, 1)==0 && game.beans(NORTH, 2)==0 && game.beans(SOUTH, 4)==-1);
    
    
    cout << "pass all the tests!" << endl;
}*/

///////////////////////////////////////// additional functions ////////////////////////////////////////////////

/*void chooseMove(in: player; out: bestHole, value):
if no move for player exists (i.e., game is over),
    bestHole = -1
    value = value of this position (i.e., +∞, -∞, or 0)
    return
if the criterion says we should not search below this node
    bestHole = -1
    value = value of this position
    return
for every hole h the player can choose
    "make" the move h
    chooseMove(opponent, h2, v2)
    "unmake" the move
    if v2 is better for the player than best seen so far,
        bestHole = h
        value = v2
return*/

/*void evalMove(Side playerSide, const Board& b, int& bestHole, long& value, int& depth)
{
    
    depth++;
    Board copy(b);
    if (!MovePossible(b, playerSide) || !MovePossible(b, opponent(playerSide)))   //if game is over
    {
        // move the remaining beans into the belonging pot
        for (int i=1; i<b.holes()+1; i++)
            copy.moveToPot(opponent(playerSide), i, opponent(playerSide));
        
        for (int i=1; i<b.holes()+1; i++)
            copy.moveToPot(playerSide, i, playerSide);
        
        bestHole=-1;
        if (copy.beans(SOUTH, 0)>copy.beans(NORTH, 0))
            value=999999;
        else if (copy.beans(SOUTH, 0)<copy.beans(NORTH, 0))
            value=-999999;
        else
            value=0;
        return;
    }
    
    if (depth>20)
    //if (timer.elapsed()>=4900)
    {
        bestHole=-1;
        value=b.beans(SOUTH, 0)-b.beans(NORTH, 0);
        return;
    }
    
    Side endSide=playerSide;
    int endHole=0;
    int h2=-1;
    long v2=-1;
    //value=0;
    int iterate=0;
    for (int i=1; i<b.holes()+1; i++)
    {
        if (b.beans(playerSide, i)>0)
        {
            Board copy(b);
            copy.sow(playerSide, i, endSide, endHole);
            //value=b.beans(playerSide, 0)-b.beans(opponent(playerSide), 0);
            
            if (endSide==playerSide && endHole==0)
            {
                depth--;
                evalMove(playerSide, copy, h2, v2, depth);
                depth--;
            }
            else if (endSide==playerSide && endHole!=0 && copy.beans(playerSide, endHole)==1 && copy.beans(opponent(playerSide), endHole)!=0)
            {
                copy.moveToPot(opponent(playerSide), endHole, playerSide);
                copy.moveToPot(playerSide, endHole, playerSide);
                evalMove(opponent(playerSide), copy, h2, v2, depth);
                depth--;
            }
            else
            {
                evalMove(opponent(playerSide), copy, h2, v2, depth);
                depth--;
            }
            
            switch (playerSide)
            {
                case SOUTH:
                    if (iterate==0)
                        value=-999999999;
                    if (v2>value)
                    {
                        bestHole=i;
                        value=v2;
                    }
                    break;
                case NORTH:
                    if (iterate==0)
                        value=9999999999;
                    if (v2<value)
                    {
                        bestHole=i;
                        value=v2;
                    }
                    break;
            }
            iterate++;
        }
    }
    return;
}*/

bool MovePossible (const Board& b, Side s)
{
    for (int i=1; i<b.holes()+1; i++)
    {
        if (b.beans(s, i)>0)
            return true;
    }
    return false;
}

