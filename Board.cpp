//
//  Board.cpp
//  Project 3
//
//  Created by Ruby on 5/10/14.
//  Copyright (c) 2014 Ruby. All rights reserved.
//

#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
:m_nHolesPerSide(nHoles)
//Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole
{
    m_Hole[NORTH] = new int[nHoles+1];
    m_Hole[SOUTH] = new int[nHoles+1];
    m_Hole[NORTH][0]=0;
    m_Hole[SOUTH][0]=0;
    for (int i=1; i<nHoles+1; i++)
    {
        m_Hole[NORTH][i]=nInitialBeansPerHole;
        m_Hole[SOUTH][i]=nInitialBeansPerHole;
    }
}

Board::Board(const Board& other)
:m_nHolesPerSide(other.m_nHolesPerSide)
{
    m_Hole[NORTH] = new int[other.m_nHolesPerSide+1];
    m_Hole[SOUTH] = new int[other.m_nHolesPerSide+1];
    for (int i=0; i<m_nHolesPerSide+1; i++)
    {
        m_Hole[NORTH][i]=other.m_Hole[NORTH][i];
        m_Hole[SOUTH][i]=other.m_Hole[SOUTH][i];
    }
}

Board::~Board()
{
    delete []m_Hole[NORTH];
    delete []m_Hole[SOUTH];
}

int Board::holes() const
//Return the number of holes on a side (not counting the pot)
{
    return m_nHolesPerSide;
}

int Board::beans(Side s, int hole) const
//Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid
{
    if (hole<0 || hole>m_nHolesPerSide)
        return -1;
    return m_Hole[s][hole];
}

int Board::beansInPlay(Side s) const
//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
{
    int totalBeans=0;
    for (int i=1; i<m_nHolesPerSide+1; i++)
        totalBeans+=m_Hole[s][i];
    return totalBeans;
}

int Board::totalBeans() const
//Return the total number of beans in the game.
{
    int totalBeans=0;
    for (int i=0; i<m_nHolesPerSide+1; i++)
    {
        totalBeans += (m_Hole[NORTH][i] + m_Hole[SOUTH][i]);
    }
    return totalBeans;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
//If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
{
    if (hole<=0 || hole>m_nHolesPerSide || m_Hole[s][hole]==0 )
        return false;
    Side tempSide = s;
    int beansToSow = m_Hole[s][hole];
    m_Hole[s][hole]=0;
    while (beansToSow>0)
    {
        if (tempSide==NORTH)
        {
            if (hole>1)
            {
                hole--;
                m_Hole[tempSide][hole]++;
                beansToSow--;
            }
            else if (hole==1)
            {
                hole--;
                if (tempSide==s)    //if the hole is on the player's own side, sow
                {
                    m_Hole[tempSide][hole]++;
                    beansToSow--;
                }
            }
            
            else  //hole=0, at the North player's pot
            {
                tempSide=SOUTH;  //switch side
                hole=0;
            }
        }
        else  //tempSide==SOUTH
        {
            if (hole<m_nHolesPerSide)
            {
                hole++;
                m_Hole[tempSide][hole]++;
                beansToSow--;
            }
            else if (hole==m_nHolesPerSide)
            {
                hole=0;    //set the position to south's pot
                if (tempSide==s)    //if it's on the player's own side, sow; else, skip
                {
                    m_Hole[tempSide][hole]++;
                    beansToSow--;
                }
                if (beansToSow>0)
                    hole=m_nHolesPerSide+1;   //for the purpose of iteration (continue to sow the North)
            }
            else //hole=m_nHolesPerSide+1, at South player's "pot"
            {
                tempSide=NORTH;   //switch side
                hole=m_nHolesPerSide+1;
            }
        }
    }
    endSide=tempSide;
    endHole=hole;
    return true;
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
//If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
{
    if (hole<=0 || hole>m_nHolesPerSide)
        return false;
    int capturedBeans = m_Hole[s][hole];
    m_Hole[s][hole]=0;
    m_Hole[potOwner][0] += capturedBeans;
    return true;
}

bool Board::setBeans(Side s, int hole, int beans)
//If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
{
    if (hole<0 || hole>m_nHolesPerSide || beans<0)
        return false;
    m_Hole[s][hole]=beans;
    return true;
}


