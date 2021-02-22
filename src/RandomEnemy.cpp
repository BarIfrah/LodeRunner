#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Enemy.h"
#include "RandomEnemy.h"
#include <ctime>       /* time */
using namespace std;
using namespace sf;

int RandomEnemy::whereToMove()
{
    srand(time(nullptr));
    return int(rand() % 5);
}
