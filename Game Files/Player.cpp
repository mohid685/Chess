#include "Player.h"

Player::Player(string name, Color C) {

	this->name = name;
	this->C = C;
}
string Player::getName() {

	return name;
}
Color Player::getColor() {

	return C;
}