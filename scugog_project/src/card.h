#pragma once
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string>

using namespace std;

class Card {
public:
	Card();
	Card(int id, int attack, int defense, int power, int ability, int cost, string image, string description, string name);


	// Accessors
	int get_id();
	int get_attack();
	int get_defense();
	int get_power();
	int get_ability();
	int get_cost();
	string get_image();
	string get_description();
	string get_name();

	// Set Functions
	void set_attack(int);
	void set_defense(int);
	void set_power(int);
	void set_cost(int);

private:
	int id;
	int attack;
	int defense;
	int power;
	int ability;
	int cost;
	string image;
	string description;
	string name;

	friend ostream& operator<< (ostream& out, Card& card);

};

class CardException : public exception {
public:
	CardException(const string& message);
	string& what();

private:
	string message;
};
