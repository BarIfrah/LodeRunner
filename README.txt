intro to OOP project:
__LODE_RUNNER__
//----------------------------------------------------------------------------
2. Creators:
a- Amit Ein-Dor   
b- Bar Ifrah      
//----------------------------------------------------------------------------
3. General ideas and goals of the project
User is the player(avatar Aang). Player moves with arrow keys. 
Goal is to collect all coins , 
While avoiding the enemies (the evil fire nation). For every coin collected the score goes up 
By 2 * levelNumber. Every cleared level gets +50 points to the user.
User also gets 3 lives. When touched by an enemy, one life goes away.
If the player collects any gifts, a good bonus of extra life/ time/score or a bad bonus 
Of extra enemy that will be added to the game map. 
Every 'strike' by an enemy, the level map resets, so is the score(of this level). 
The player can also dig through a wall in the game map. The player can fall through a hole, 
But an enemy gets stuck in the void, and returns to the game map after the hole disappears. 
When life counter == 0, the game will end.
Please refer to 'how to play' tab in the game menu for detailed information in game operation.
//----------------------------------------------------------------------------
4. Files:
genPOP:
CMakeLists.txt- cmake of the project.
Source files: 
all files with no description holds the ctrs and methods from headers
-CMakeLists.txt - Cmake file to all src files.

Source‫:‬
‫--‬Board.cpp		‫-‬Gift.cpp		‫-‬RandomEnemy.cpp		‫-‬Wall.cpp
‫--‬CMakeLists.txt		‫-‬Ladder.cpp		Rope.cpp		‫-‬main.cpp
‫--‬Coin.cpp		‫-‬Menu.cpp		‫-‬ScoreBoard.cpp		
‫--‬Controller.cpp		‫-‬MovingObject.cpp	‫-‬SmartEnemy.cpp
‫--‬Enemy.cpp		‫-‬PatrolEnemy.cpp		‫-‬StaticObject.cpp
‫--‬GameObject.cpp		‫-‬Player.cpp		‫-‬StatsBoard.cpp

Headers:
-CMakeLists.txt - To all headers
-Board.h  -The "drawing board"
‫--‬Board.h		‫-‬Enemy.h		‫-‬Menu.h		‫-‬RandomEnemy.h	‫-‬StaticObject.h
‫--‬CMakeLists.txt	‫-‬GameObject.h	‫-‬MovingObject.h	‫-‬Rope.h		‫-‬StatsBoard.h
‫--‬Coin.h		‫-‬Gift.h		‫-‬PatrolEnemy.h	‫-‬ScoreBoard.h	‫-‬Wall.h
‫--‬Controller.h	‫-‬Ladder.h	‫-‬Player.h	‫-‬SmartEnemy.h	‫-‬macros.h

Resources‫:‬
‫-‬Board‫.‬txt	// holds ALL levels.
‫--‬images and sounds‫--‬
air_ang.png
ang.png
ang2.png
ang3.png
ang4.png
azula.png
azula2.png
azula3.png
back.png
background.jfif
backgroundMusic.wav
coin.png
-coin_cellect.ogg
-exit.png
-exit2.png
-gameover.png
-gift.png
-howtobutton.png
-howtobutton2.png
-howtoplay.png
-ladder.png
-menu.png
-moving1.png
-moving2.png
-moving3.png
-moving4.png
-rope.png
-rope_ang.png
-soundtrack.ogg
-start.png
-start2.png
-tylee.png
-tylee2.png
-tylee3.png
-tylee4.png
-wall.png
-zuko.png
//----------------------------------------------------------------------------
5. Data structures :
   Vectors - unique pointer vectors are holding the game objects
   A 3D char vector holds the boards from 'Board.txt'

//----------------------------------------------------------------------------
6. Algorithms that are worth mentioning:
‫---‬
//----------------------------------------------------------------------------
7. Known bugs:
‫---‬
//----------------------------------------------------------------------------
8. Other notes:
   If you want to add a level, please insert your text file to 'Board.txt'
   Insert row, col, time(in seconds or '-1' for unlimited time) above the text
   Board you have inserted.
