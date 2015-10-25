//
//  Game.cpp
//  Project 3
//
//  Created by Ruby on 5/10/14.
//  Copyright (c) 2014 Ruby. All rights reserved.
//

#include "Game.h"
#include "Board.h"
#include "Player.h"
using namespace std;

Game::Game(const Board& b, Player* south, Player* north)
//Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
:m_board(b), m_takeTurn(SOUTH)
{
    m_player[SOUTH] = south;
    m_player[NORTH] = north;
}

void Game::display() const
//Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
{
    cout << "          North " << m_player[NORTH]->name() << endl;
    cout << "          " ;
    for (int i=1; i<m_board.holes()+1; i++)
        cout << i << " ";
    cout << endl << "          ";
    for (int i=1; i<m_board.holes()+1; i++)
        cout << "--";
    cout << endl << "          ";
    for (int i=1; i<m_board.holes()+1; i++)
        cout << m_board.beans(NORTH, i) << " ";
    cout << endl << "N_pot " << m_board.beans(NORTH, 0) << "  ";
    for (int i=1; i<m_board.holes()+1; i++)
        cout << "  ";
    cout << "   " << m_board.beans(SOUTH, 0) << " S_pot" << endl;
    cout << "          ";
    for (int i=1; i<m_board.holes()+1; i++)
        cout << m_board.beans(SOUTH, i) << " ";
    cout << endl << "          ";
    for (int i=1; i<m_board.holes()+1; i++)
        cout << "--";
    cout << endl << "          ";
    for (int i=1; i<m_board.holes()+1; i++)
        cout << i << " ";
    cout << endl;
    cout << "          South " << m_player[SOUTH]->name() << endl;
    cout << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
{
    over=false;
    bool over1=true, over2=true;
    for (int i=1; i<m_board.holes()+1; i++)   //check whether there is possible move for the takeTurn side
    {
        if (m_board.beans(m_takeTurn, i)>0)
        {
            over1=false;
            break;
        }
    }
    for (int i=1; i<m_board.holes()+1; i++)   //check the other side
    {
        if (m_board.beans(opponent(m_takeTurn), i)>0)
        {
            over2=false;
            break;
        }
    }
    if (over1==true || over2==true)  //if either side has no possible move, the game is over
        over=true;
    if (over==true)
    {
        if (m_board.beans(NORTH, 0)==m_board.beans(SOUTH, 0))
            hasWinner=false;
        else if (m_board.beans(NORTH, 0)>m_board.beans(SOUTH, 0))
        {
            hasWinner=true;
            winner=NORTH;
        }
        else
        {
            hasWinner=true;
            winner=SOUTH;
        }
    }
}

bool Game::move()
//If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.
//If it was placed in one of the player's own holes that was empty just a moment before, and if the opponent's hole directly opposite from that hole is not empty, then that bean and all beans in the opponent's hole directly opposite from that hole are put into the players pot, and the turn ends. (This is a capture.) Notice that it is not a capture if the player's last bean ends up in an empty hole on the opponent's side.
//Whenever a turn ends with all of the holes on one side of the board empty (no matter whose turn ended), the game is over, and any beans in the other player's holes are put into that other player's pot. The winner is then the player with the most beans in his pot.
{
    bool over, hasWinner;
    Side winner;
    status(over, hasWinner, winner);
    if (over)
        return false;
    
    Side endSide=m_takeTurn;
    int endHole=0;
    int iterate=0;
    while (endSide==m_takeTurn && endHole==0)
    {
        status(over, hasWinner, winner);
        if (over)
            break;
        if (iterate>0)
        {
            display();
            cout << m_player[m_takeTurn]->name() << " gets another turn." << endl;
        }
        int pickedHole = m_player[m_takeTurn]->chooseMove(m_board, m_takeTurn);
        m_board.sow(m_takeTurn, pickedHole, endSide, endHole);
        iterate++;
    }
    
    if (endSide==m_takeTurn && endHole!=0 && m_board.beans(endSide, endHole)==1 && m_board.beans(opponent(endSide), endHole)!=0)
    {
        display();
        cout << m_player[m_takeTurn]->name() << " captures." << endl;
        m_board.moveToPot(endSide, endHole, m_takeTurn);
        m_board.moveToPot(opponent(endSide), endHole, m_takeTurn);
    }
    
    bool over1=true;
    bool over2=true;
    Side overSide=m_takeTurn;
    for (int i=1; i<m_board.holes()+1; i++)
    {
        if (m_board.beans(NORTH, i)>0)   //if still has beans, not over on side 1
        {
            //cout << "Side north is not over." << endl;
            over1=false;
            break;
        }
    }

    for (int i=1; i<m_board.holes()+1; i++)  //same with the above, check another side
    {
        if (m_board.beans(SOUTH, i)>0)
        {
            //cout << "Side south is not over." << endl;
            over2=false;
            break;
        }
    }
    if (over1==true && over2!=true)   //if m_takeTurn side is over
        overSide=NORTH;
    else if (over2==true && over1!=true)  //if the opponent of m_takeTurn side is over
        overSide=SOUTH;
    /*if (m_player[NORTH]->chooseMove(m_board, NORTH)==-1)
    {
        overSide=NORTH;
        over=true;
    }
    else if (m_player[SOUTH]->chooseMove(m_board, SOUTH)==-1)
    {
        overSide=SOUTH;
        over=true;
    }
    else
        over=false;*/
    //cout << over1 << " " << over2 << endl;
    
    if (over1==true || over2==true)
    {
        if (!(over1==true && over2==true)) //if one side is empty but the other side has remaining beans
        {
            display();
            cout << "Sweeping the remaining beans into " << m_player[opponent(overSide)]->name() << "'s pot" << endl;
            for (int i=1; i<m_board.holes()+1; i++)
            {
                m_board.moveToPot(opponent(overSide), i, opponent(overSide));
            }
        }
    }
        
    m_takeTurn=opponent(m_takeTurn);
    return true;
}

void Game::play()
//Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function.
{
    bool over, hasWinner;
    Side winner;
    display();
    
    if (!m_player[NORTH]->isInteractive() && !m_player[SOUTH]->isInteractive())  //if no human player
    {
        cin.ignore(100, '\n');   //continue until hit "enter"
        while (move())
        {
            display();
            cin.ignore(100, '\n');
        }
    }
    else
    {
        while (move())
        {
            display();
        }
    }
    
    
    status(over, hasWinner, winner);
    if (!hasWinner)
    {
        cout << "The game does not have a winner." << endl;
    }
    else
    {
        cout << "The winner is " << m_player[winner]->name() << endl;
        cout << "South pot has " << m_board.beans(SOUTH, 0) << " North pot has " << m_board.beans(NORTH, 0) << endl;
    }
    
}

int Game::beans(Side s, int hole) const
//Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
{
    if (hole<0 || hole>m_board.holes())
        return -1;
    return m_board.beans(s, hole);
}



