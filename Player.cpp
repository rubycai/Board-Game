//
//  Player.cpp
//  Project 3
//
//  Created by Ruby on 5/10/14.
//  Copyright (c) 2014 Ruby. All rights reserved.
//

#include "Player.h"
#include "Board.h"
#include <string>

//========================================================================
// Timer t;                 // create a timer
// t.start();               // start the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#if __cplusplus == 201103L  // C++11

#include <chrono>

class Timer
{
public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {
        std::chrono::duration<double,std::milli> diff =
        std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
private:
    std::chrono::high_resolution_clock::time_point m_time;
};

#elif defined(_MSC_VER)  // not C++11, but Windows

#include <windows.h>

class Timer
{
public:
    Timer()
    {
        QueryPerformanceFrequency(&ticksPerSecond);
        start();
    }
    void start()
    {
        QueryPerformanceCounter(&m_time);
    }
    double elapsed() const
    {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000.0 * (now.QuadPart - m_time.QuadPart)) / ticksPerSecond.QuadPart;
    }
private:
    LARGE_INTEGER m_time;
    LARGE_INTEGER ticksPerSecond;
};

#else // not C++11 or Windows, so C++98

#include <ctime>

class Timer
{
public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::clock();
    }
    double elapsed() const
    {
        return (1000.0 * (std::clock() - m_time)) / CLOCKS_PER_SEC;
    }
private:
    std::clock_t m_time;
};

#endif

/////////////////////////////////////// Base Class ////////////////////////////////////////////
Player::Player(std::string name)
:m_name(name)
{}

Player::~Player()
{}

std::string Player::name() const
{
    return m_name;
}

bool Player::isInteractive() const
//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
{
    return false;
}

/////////////////////////////////////// Derived Class ////////////////////////////////////////

//===================================== Human Player ========================================//
HumanPlayer::HumanPlayer(std::string name)
:Player(name)
{}

bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
//Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
{
    int pickedHole=-1;
    bool MovePossible=false;
    
    for (int i=1; i<b.holes()+1; i++)
    {
        if (b.beans(s, i)>0)
        {
            MovePossible=true;
            break;
        }
    }
    if (MovePossible==false)
        return -1;
    int iterate=0;
    while (pickedHole<0 || pickedHole > b.holes() || b.beans(s, pickedHole)<=0)
    {
        if (iterate>0 && (pickedHole<0 || pickedHole>b.holes()))
            std::cout << "The hole number must be from 1 to " << b.holes() << std::endl;
        else if (iterate>0 && b.beans(s, pickedHole)<=0)
            std::cout << "There are no beans in that hole." << std::endl;
        std::cout << name() << " choose a hole to pick the beans: ";
        std::cin >> pickedHole;
        iterate++;
    }
    return pickedHole;
}

//=========================================== Bad Player ===============================================//
BadPlayer::BadPlayer(std::string name)
:Player(name)
{}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
    bool MovePossible=false;
    
    for (int i=1; i<b.holes()+1; i++)
    {
        if (b.beans(s, i)>0)
            MovePossible=true;
    }
    if (MovePossible==false)
        return -1;
    
    int pickedHole=0;
    while (pickedHole<=0 || pickedHole > b.holes() || b.beans(s, pickedHole)<=0)  //search until there is a "qualified" hole
    {
        pickedHole++;
    }
    
    std::cout << name() << " chooses hole " << pickedHole << std::endl;
    return pickedHole;
}

//========================================= Smart Player ============================================//
SmartPlayer::SmartPlayer(std::string name)
:Player(name)
{}

Timer timer;
int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    /*bool MovePossible=false;
    
    for (int i=1; i<b.holes()+1; i++)
    {
        if (b.beans(s, i)>0)
            MovePossible=true;
    }*/
    if (MovePossible(b, s)==false)
        return -1;
    int bestHole=0;
    long value=0;
    timer.start();
    evalMove(s, b, bestHole, value, timer);
    std::cout << name() << " chooses hole " << bestHole << std::endl;
    return bestHole;
}

void SmartPlayer::evalMove(Side playerSide, const Board& b, int& bestHole, long& value, Timer timer) const
{
    //depth++;
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
    
    //if (depth>20)
    if (timer.elapsed()>=4900)
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
                //depth--;
                evalMove(playerSide, copy, h2, v2, timer);
                //depth--;
            }
            else if (endSide==playerSide && endHole!=0 && copy.beans(playerSide, endHole)==1 && copy.beans(opponent(playerSide), endHole)!=0)
            {
                copy.moveToPot(opponent(playerSide), endHole, playerSide);
                copy.moveToPot(playerSide, endHole, playerSide);
                evalMove(opponent(playerSide), copy, h2, v2, timer);
                //depth--;
            }
            else
            {
                evalMove(opponent(playerSide), copy, h2, v2, timer);
                //depth--;
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
}




