#pragma once
#include "Utility.h"
#include <iostream>
#include <string>

using namespace std;

class Player
{
private:
	string name;
	Color C;
public:
	Player(string name,Color C);
	string getName();
	Color getColor();
};