# Board-Game

1.	a description of the design of the classes.
•	Board:
•	private member: 
•	int* m_Hole[2]: an array of pointer/a 2-D array; m_Hole[0] points to a dynamically allocated array (size is indicated while calling the constructor), of which every element indicates the number of beans in each hole of the north side (eg. m_Hole[0][0]=0 means there is 0 beans in the North’s pot; m_Hole[0][1]=2 means there are two beans in the North’s hole 1); similarly with m_Hole[1] (SOUTH) 
•	int m_nHolesPerSide: indicate the number of holes on each side of the board
•	implementations:
•	constructor: create two dynamically allocated array, assign “nInitialBeansPerHole” to every element of the 2D array m_Hole[][], except for m_Hole[0][0] and m_Hole[1][0] which initializes to 0; assign “nHoles” to m_nHolesPerSide;
•	destructor: delete dynamically allocated array m_Hole[0] and m_Hole[1];
•	copy constructor: deep copy m_Hole[][], for the purpose of SmartPlayer’s chooseMove function;
•	Player:
•	Base class Player: 
•	private member: string m_name;
•	isInteractive function returns false;
•	Derived class HumanPlayer:
•	isInteractive function returns true;
•	inherits m_name from the base class;
•	Derived class SmartPlayer and BadPlayer:
•	don’t implement isInteractive function;
•	inherits m_name from the base class;
•	Game:
•	private member: 
•	Player* m_player[2]: array of pointer; m_player[0] points to the north player and m_player[1] points to the south player;
•	Board m_board: the board to play the game;
•	Side m_takeTurn: indicate which side should take turn (to pick the beans and sow)
•	Constructor: initialize m_takeTurn to SOUTH, m_player[0] to north, m_player[1] to south and m_board to b;

2.	a description of my design for SmartPlayer::chooseMove
•	heuristic I use: the greater the difference between player pot’s beans and opponent pot’s beans, the better.
•	SmartPlayer::chooseMove(…)
{
	check if there is possible move; (whether the game is over)
	start clocking the time;
	call function evalMove (…);
	return bestHole;
}
•	void evalMove(Side playerSide, const Board& b, int& bestHole, int& value, Timer timer) //SmartPlayer’s private member function
{
   if no move for player exists (i.e., game is over),
       bestHole = -1;
       sweep the remaining beans into the pot they belong to;
       if south pot’s #beans > north…, value = 9999999;
       if south pot’s #beans < north…, value = -9999999;
       if equal, value = 0;
       return

   if it has passed more than 5 seconds,
       bestHole = -1
       value = (#beans in South pot) - (#beans in North pot);
       return

   for every hole h the player can choose (valid hole number and not empty)
       declare a new board copy using copy constructor;
       make move on the copied board (sow);
       if ends on the player’s own pot,
	evalMove (this player, copy, h2, v2);
       else if the condition for “capture” is satisfied,
	capture;
	evalMove (opponent, copy, h2, v2);
       else
	evalMove(opponent, h2, v2)  (recursion, v2 is the best value for opponent)
       if v2 is better for the player than best seen so far, (for South v2>value; for North v2<value)
           bestHole = the current hole h;
           value = v2;
}


3.	pseudocode for non-trivial algorithms.
•	bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
if hole is invalid number or there is no bean in the given hole, return false;
initialize tempSide to s;
iterate until there are no more beans to sow
      if the player is on North side,
	if hole >1
	   move to the hole just before this hole (hole++), sow one bean in that hole, and update the remaining beans;
	if hole = 1
	   move to hole #0 (pot);
	   if it’s the player’s own pot, sow it and update the remaining beans;
	if hole = 0
	   switch tempSide to SOUTH;
      if the player is on South side
	if hole <  #holes
	   move to the hole just after this hole, sow one bean in that hole, and update the remaining beans;
	if player is at the last hole of the south side
	   move to south pot (hole = 0);
	   if it’s player’s own pot, sow it and update the remaining beans,
	   if the there are still beans remain, assign hole to be (#holes + 1);
	if player is at South pot, (hole = #holes +1)
	   switch side to North;
endSide = tempSide;
endHole = hole;

•	void Game::status(bool& over, bool& hasWinner, Side& winner) const
if the m_takeTurn side has no more possible move, set over1 to true; else, false;
if the other side has no more possible move, set over2 to true; else, false;
if either over1 is true and over2 is true, set over to true;
if over is true,
	compare #beans in North and South’s pot, 
	   if North = South, set hasWinner to false;
	   if North > South, set hasWinner to true and winner to North;
	   if North < South, set hasWinner to true and winner to South;

•	bool Game::move()
if the game is over, return false;
while the player ends in his own pot (has initialized the position to the pot)
	if the game is over, break the loop;
	if the player does ends in his own pot (has traversed the loop at least once)
		display the current board;
		print “… gets another turn.”;
	make the player pick one hole;
	sow the holes;
	increment iterate (to trace how many times the loop is iterated);
if the last bean is placed in one of the player's own holes that was empty just a moment before, and if the opponent's hole directly opposite from that hole is not empty
	display the current board;
	print “xxx captures”;
	move the beans in the exact hole on both side to the current player’s pot;
if player’s side still have beans, set over1 to false; else, true;
if opponent’s side still have beans, set over2 to false; else, true;
if over1 is true and over2 is false, set overSide to player’s side;
if over2 is true and over1 is false, set overSide to opponent’s side;
if only one side is empty/over and the other side still has beans remained
	display the current board;
	print “sweep the remaining beans into xxx’s pot”;
	move the beans to the right pot;
update m_takeTurn (switching side);
return true;

•	void Game::play()
display the initial board;
if neither of the player is human player
	wait until the user has hit the enter key;
	while the game isn’t over
		make a move (the player pick a hole and sow the beans);
		display the current board;
		wait until the user has hit the enter key;
else (if there is at least one human player)
	while the game isn;t over
		make a move;
		display the current board;
call the status function, check the status;
if the game doesn’t have a winner,
	print “The game doesn’t have a winner.”;
else
	print “The winner is XXX”;

4.	a note about any known bugs, serious inefficiencies, or notable problems you had.
•	SmartPlayer’s chooseMove function run into infinite loop (because returns the best Hole -1)
•	try to use chooseMove function to see whether there is still possible move for the player, but that leads to excess prompts which let the player choose move if the player is humanPlayer and there are still possible moves.
•	have a hard time to figure out how SmartPlayer works.
•	forget to reduce the depth when game“tree” is traced back to the starting depth to continue search the next node

5.	a list of the test cases that would thoroughly test the functions.

======================== Board.cpp ============================
Board b(3,2);
Board c(2,4);
//test public functions of Board
•	assert(b.holes()==3 && b.beansInPlay(NORTH)==6 && b.beans(SOUTH, 0)==0 && b.beans(SOUTH, 1)==2 && b.totalBeans()==12); 
//test sow function of Board
•	assert(b.sow(NORTH, 0, endSide, endHole)==false && b.sow(NORTH, -1, endSide, endHole)==false && b.sow(NORTH, 4, endSide, endHole)==false);
•	assert(b.sow(NORTH, 2, endSide, endHole)==true && endSide==NORTH && endHole==0 && b.beans(NORTH, 1)==3);
•	assert(b.sow(NORTH, 2, endSide, endHole)==false);   //test the case when try to pick a hole with no beans in it
•	assert(b.sow(NORTH, 1, endSide, endHole)==true && endSide==SOUTH && endHole==2);   //test the case where sowing gets to the player’s own pot
•	assert(c.sow(NORTH, 1, endSide, endHole)==true && endSide==NORTH && endHole==2);    //test the case where sowing gets so far that arrives at opponent’s pot  
//test moveToPot function
•	assert(c.moveToPot(NORTH, 2, NORTH)==true && c.beans(NORTH, 2)==0 && c.beans(NORTH, 0)==6);

========================= Player.cpp ==========================
Board a(3,0);
Player* player[5];
player[0] = new HumanPlayer("Ruby");
player[1] = new BadPlayer("fool");
player[2] = new SmartPlayer("clever");
    assert(player[0]->isInteractive()==true && player[1]->isInteractive()==false && player[2]->isInteractive()==false);   //test isInteractive function
    assert(player[0]->name()==“Ruby");   //test name function
//test chooseMove function
    assert(player[0]->chooseMove(a, NORTH)==-1 && player[1]->chooseMove(a, NORTH)==-1 && player[2]->chooseMove(a, NORTH)==-1);  
    a.setBeans(SOUTH, 2, 3);
    a.setBeans(NORTH, 3, 2);
    assert(player[1]->chooseMove(a, NORTH)==3 && player[2]->chooseMove(a, SOUTH)==2);

======================== Game.cpp =============================
Player* player[5];
player[0] = new HumanPlayer("Ruby");
player[1] = new BadPlayer("fool");
player[2] = new SmartPlayer("clever");
Board d(3, 2);
Game game(d, player[2], player[1]);
game.display();    //test display function
bool over, hasWinner;
Side Winner;
game.status(over, hasWinner, Winner);   //test status function
assert(over==false);
while (game.move())     //test move() function
{}
 game.status(over, hasWinner, Winner);
 assert(over==true && hasWinner==true && Winner==SOUTH);   //test SmartPlayer class, it is supposed to be write if the SmartPlayer is implemented right
game.play();    //test play function, after hit enter, should output “The winner is Clever”
assert(game.beans(SOUTH, 1)==0 && game.beans(NORTH, 2)==0 && game.beans(SOUTH, 4)==-1);   //test the beans function
