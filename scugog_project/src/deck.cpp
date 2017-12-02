#pragma once
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <boost/shared_ptr.hpp>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <..\scugog_project\src\deck.h>

using namespace std;

// Exception
DeckException::DeckException(const string& message) : message(message) {}
string& DeckException::what() { return message; }

// Constructor
Deck::Deck() {
}
Deck::Deck(int deck_number) {
	deck_num = deck_number;
	retrieve_cards();
}


// Accessor
int Deck::get_deck_num() {
	return deck_num;
}
int Deck::get_size() {
	return cards.size();
}
Card Deck::access_card(int index) {
	if (index >= get_size()) {
		throw DeckException("Index is not allowed because it falls outside the size of the deck.");
	} else {
		return cards[index];
	}
}

// Set Functions
void Deck::add_card_to_deck(Card card_value) {
	cards.push_back(card_value);
}

Card Deck::pop_card(int index) {
	if (index >= get_size()) {
		throw DeckException("Index is not allowed because it falls outside the size of the deck.");
	}
	else {
		Card requested_card = cards[index];
		cards.erase(cards.begin() + index);
		return requested_card;
	}
}

void Deck::retrieve_cards() {
	// Some of the descriptions might differ from the original database because I copy pasted all of this data. All the data can be found on the cards
	// The ints are for sure right, only the description might vary
	vector<Card> deck1 = { Card(0,	3,	3,	3,	0,	1,	"pepper.png",	"Let this pepper unleash its ability and you'll be picking a peck of pickled punches to the face!",	"Pepper"),
		Card(0,	3,	3,	3,	0,	1,	"pepper.png",	"Let this pepper unleash its ability and you'll be picking a peck of pickled punches to the face!",	"Pepper"),
		Card(0,	3,	3,	3,	0,	1,	"pepper.png",	"Let this pepper unleash its ability and you'll be picking a peck of pickled punches to the face!",	"Pepper"),
		Card(1,	10,	2,	1,	0,	2,	"carrot.png",	"Don’t let this cone - head fool you!Mess with the carrot and prepare to be speared",	"Carrot"),
		Card(1,	10,	2,	1,	0,	2,	"carrot.png",	"Don’t let this cone - head fool you!Mess with the carrot and prepare to be speared",	"Carrot"),
		Card(1,	10,	2,	1,	0,	2,	"carrot.png",	"Don’t let this cone - head fool you!Mess with the carrot and prepare to be speared",	"Carrot"),
		Card(2,	5,	5,	5,	0,	3,	"onion.png",	"Try and slice open this onerous onion and it'll leave you crying to mama!",	"Onion"),
		Card(2,	5,	5,	5,	0,	3,	"onion.png",	"Try and slice open this onerous onion and it'll leave you crying to mama!",	"Onion"),
		Card(2,	5,	5,	5,	0,	3,	"onion.png",	"Try and slice open this onerous onion and it'll leave you crying to mama!",	"Onion"),
		Card(3,	7,	3,	4,	0,	2,	"potato.png",	"Let this particularily powerful potato attack your produce and you'll end up in the ground",	"Potato"),
		Card(3,	7,	3,	4,	0,	2,	"potato.png",	"Let this particularily powerful potato attack your produce and you'll end up in the ground",	"Potato"),
		Card(3,	7,	3,	4,	0,	2,	"potato.png",	"Let this particularily powerful potato attack your produce and you'll end up in the ground",	"Potato"),
		Card(4,	6,	2,	6,	5,	2,	"pumpkin.png",	"Face an attack from this autumnal monstrosity and you'll be giving thanks to the doctors!",	"Pumpkin"),
		Card(4,	6,	2,	6,	5,	2,	"pumpkin.png",	"Face an attack from this autumnal monstrosity and you'll be giving thanks to the doctors!",	"Pumpkin"),
		Card(4,	6,	2,	6,	5,	2,	"pumpkin.png",	"Face an attack from this autumnal monstrosity and you'll be giving thanks to the doctors!",	"Pumpkin"),
		Card(5,	5,	8,	8,	0,	4,	"turnip.png",	"Receive a direct attack from this vegetable and you'll wish you turned right around and gave up!",	"Turnip"),
		Card(5,	5,	8,	8,	0,	4,	"turnip.png",	"Receive a direct attack from this vegetable and you'll wish you turned right around and gave up!",	"Turnip"),
		Card(5,	5,	8,	8,	0,	4,	"turnip.png",	"Receive a direct attack from this vegetable and you'll wish you turned right around and gave up!",	"Turnip"),
		Card(6,	7,	3,	7,	4,	4,	"beet.png",	"Face the wrath of this voracious veggie and it'll beat you 'till you're purple!",	"Beet"),
		Card(6,	7,	3,	7,	4,	4,	"beet.png",	"Face the wrath of this voracious veggie and it'll beat you 'till you're purple!",	"Beet"),
		Card(6,	7,	3,	7,	4,	4,	"beet.png",	"Face the wrath of this voracious veggie and it'll beat you 'till you're purple!",	"Beet"),
		Card(7,	5,	6,	7,	0,	3,	"broccoli.png",	"A distant relative of Bruce Lee, this \"Brock - Lee\" can send a menacing direct attack kick!", "Broccoli"),
		Card(7,	5,	6,	7,	0,	3,	"broccoli.png",	"A distant relative of Bruce Lee, this \"Brock - Lee\" can send a menacing direct attack kick!", "Broccoli"),
		Card(7,	5,	6,	7,	0,	3,	"broccoli.png",	"A distant relative of Bruce Lee, this \"Brock - Lee\" can send a menacing direct attack kick!", "Broccoli"),
		Card(8,	10,	5,	5,	0,	4,	"cabbage.png",	"I wouldn't want to be a kid in a patch of these cabbages, they'll attack your produce or you directl",	"Cabbage"),
		Card(8,	10,	5,	5,	0,	4,	"cabbage.png",	"I wouldn't want to be a kid in a patch of these cabbages, they'll attack your produce or you directl",	"Cabbage"),
		Card(8,	10,	5,	5,	0,	4,	"cabbage.png",	"I wouldn't want to be a kid in a patch of these cabbages, they'll attack your produce or you directl",	"Cabbage"),
		Card(9,	7,	3,	7,	0,	3,	"radish.png",	"It might not be totally rad, but this rad - ish vegetable is cool enough to bury you on all fronts!", "Radish"),
		Card(9,	7,	3,	7,	0,	3,	"radish.png",	"It might not be totally rad, but this rad - ish vegetable is cool enough to bury you on all fronts!", "Radish"),
		Card(9,	7,	3,	7,	0,	3,	"radish.png",	"It might not be totally rad, but this rad - ish vegetable is cool enough to bury you on all fronts!", "Radish"),
		Card(10,	10,	10,	10,	0,	8,	"corn.png",	"Come up against this mighty cob - dweller and it'll toss you by the ears!",	"Corn"),
		Card(10,	10,	10,	10,	0,	8,	"corn.png",	"Come up against this mighty cob - dweller and it'll toss you by the ears!",	"Corn"),
		Card(11, 18,	5,	6,	0,	6,	"cauliflower.png",	"Don't stop to smell this flower, the cauliflower will slice you up and serve you with cheddar!",	"Cauliflower"),
		Card(11, 18,	5,	6,	0,	6,	"cauliflower.png",	"Don't stop to smell this flower, the cauliflower will slice you up and serve you with cheddar!",	"Cauliflower"),
		Card(12,	15,	10,	1,	0,	6,	"spinach.png",	"Popeye had the right idea scarfing down this vegetable.Your produce will be green with envy after l",	"Spinach"),
		Card(12,	15,	10,	1,	0,	6,	"spinach.png",	"Popeye had the right idea scarfing down this vegetable.Your produce will be green with envy after l",	"Spinach"),
		Card(13,	1,	8,	20,	3,	7,	"kale.png",	"There's a reason they call it a super-food. Let the Kale attack you directly and it'll toss you like",	"Kale"),
		Card(13,	1,	8,	20,	3,	7,	"kale.png",	"There's a reason they call it a super-food. Let the Kale attack you directly and it'll toss you like",	"Kale"),
		Card(14,	2,	2,	10,	8,	3,	"brusselsprout.png",	"Get attacked directly by this vicious vegetable and you'll be sent all the way to Belgium!", "Brussel Sprout"),
		Card(14,	2,	2,	10,	8,	3,	"brusselsprout.png",	"Get attacked directly by this vicious vegetable and you'll be sent all the way to Belgium!", "Brussel Sprout") };

	vector<Card> deck2 = { Card(15,	5,	2,	1,	0,	1,	"strawberry.png",	"This puny strawberry packs a moderate fruit punch when it comes to other produce, but try to attack", 	"Strawberry"),
		Card(15,	5,	2,	1,	0,	1,	"strawberry.png",	"This puny strawberry packs a moderate fruit punch when it comes to other produce, but try to attack", 	"Strawberry"),
		Card(15,	5,	2,	1,	0,	1,	"strawberry.png",	"This puny strawberry packs a moderate fruit punch when it comes to other produce, but try to attack", 	"Strawberry"),
		Card(16,	3,	1,	3,	2, 3,	"blueberry.png",	"Don't be blue looking at this fruit's attack, moderately high defence and power are in its roots!", "Blueberry"),
		Card(16,	3,	1,	3,	2, 3,	"blueberry.png",	"Don't be blue looking at this fruit's attack, moderately high defence and power are in its roots!", "Blueberry"),
		Card(16,	3,	1,	3,	2, 3,	"blueberry.png",	"Don't be blue looking at this fruit's attack, moderately high defence and power are in its roots!", "Blueberry"),
		Card(17,1,	10,	5,	0, 3,	"raspberry.png",	"You can attack this resiliant raspberry 'till you're red in the face!", "Raspberry"),
		Card(17,1,	10,	5,	0, 3,	"raspberry.png",	"You can attack this resiliant raspberry 'till you're red in the face!", "Raspberry"),
		Card(17,1,	10,	5,	0, 3,	"raspberry.png",	"You can attack this resiliant raspberry 'till you're red in the face!", "Raspberry"),
		Card(18,	3,	3,	6,	7,2, "banana.png",	"This curved companion might have moderately low attack and defence, but face his direct attack fury", 	"Banana"),
		Card(18,	3,	3,	6,	7,2, "banana.png",	"This curved companion might have moderately low attack and defence, but face his direct attack fury", 	"Banana"),
		Card(18,	3,	3,	6,	7,2, "banana.png",	"This curved companion might have moderately low attack and defence, but face his direct attack fury", 	"Banana"),
		Card(19,	8,	5,	5,	0,3,	"mango.png",	"Watch out if you find yourself pitted against the mighty mango, this tropical terror boasts a high a",	"Mango"),
		Card(19,	8,	5,	5,	0,3,	"mango.png",	"Watch out if you find yourself pitted against the mighty mango, this tropical terror boasts a high a",	"Mango"),
		Card(19,	8,	5,	5,	0,3,	"mango.png",	"Watch out if you find yourself pitted against the mighty mango, this tropical terror boasts a high a",	"Mango"),
		Card(20,	4,	2,	4,	1,4, 	"blackberry.png",	"Don't underestimate this easily-breakable blackberry! Let him attack first and you'll be the one end", "Blackberry"),
		Card(20,	4,	2,	4,	1,4, 	"blackberry.png",	"Don't underestimate this easily-breakable blackberry! Let him attack first and you'll be the one end", "Blackberry"),
		Card(20,	4,	2,	4,	1,4, 	"blackberry.png",	"Don't underestimate this easily-breakable blackberry! Let him attack first and you'll be the one end", "Blackberry"),
		Card(21,	5,	7,	6,	0, 3,	"cherry.png",	"Face off against this pitted pariah and you'll end up in knots!",	"Cherry"),
		Card(21,	5,	7,	6,	0, 3,	"cherry.png",	"Face off against this pitted pariah and you'll end up in knots!",	"Cherry"),
		Card(21,	5,	7,	6,	0, 3,	"cherry.png",	"Face off against this pitted pariah and you'll end up in knots!",	"Cherry"),
		Card(22,	12,	5,	7,	0, 4,	"grapes.png",	"All hail the Great Grape!This fearsome fruit doesn't need his vicious vinemates to send your produc",	"Grape"),
		Card(22,	12,	5,	7,	0, 4,	"grapes.png",	"All hail the Great Grape!This fearsome fruit doesn't need his vicious vinemates to send your produc",	"Grape"),
		Card(22,	12,	5,	7,	0, 4,	"grapes.png",	"All hail the Great Grape!This fearsome fruit doesn't need his vicious vinemates to send your produc",	"Grape"),
		Card(23,	6,	3,	5,	0,2,	"pear.png",	"Come up against this shapely fruit and it'll send you back in two!",	"Pear"),
		Card(23,	6,	3,	5,	0,2,	"pear.png",	"Come up against this shapely fruit and it'll send you back in two!",	"Pear"),
		Card(23,	6,	3,	5,	0,2,	"pear.png",	"Come up against this shapely fruit and it'll send you back in two!",	"Pear"),
		Card(24, 7,	6,	7,	0, 4, 	"peach.png",	"Don't mess with this summer staple, this fruit will leave you anything but peachy!",	"Peach"),
		Card(24, 7,	6,	7,	0, 4, 	"peach.png",	"Don't mess with this summer staple, this fruit will leave you anything but peachy!",	"Peach"),
		Card(24, 7,	6,	7,	0, 4, 	"peach.png",	"Don't mess with this summer staple, this fruit will leave you anything but peachy!",	"Peach"),
		Card(25,	10,	6,	8,	0, 4,	"kiwi.png",	"Receive an attack from this fruit and you'll be as helpless as a flightless bird!",	"Kiwi"),
		Card(25,	10,	6,	8,	0, 4,	"kiwi.png",	"Receive an attack from this fruit and you'll be as helpless as a flightless bird!",	"Kiwi"),
		Card(26,	3,	4,	4,	6, 3,	"pomegranate.png",	"This pint - sized pomegranite seems like a weakling, but come up against it and you're not likely to s",	"Pomegranate"),
		Card(26,	3,	4,	4,	6, 3,	"pomegranate.png",	"This pint - sized pomegranite seems like a weakling, but come up against it and you're not likely to s",	"Pomegranate"),
		Card(27,	10,	9,	20,	0, 8,	"pineapple.png",	"Check out this spiky spectacle!Don't let it attack you directly or you'll be the one fried with ham",	"Pineapple"),
		Card(27,	10,	9,	20,	0, 8,	"pineapple.png",	"Check out this spiky spectacle!Don't let it attack you directly or you'll be the one fried with ham",	"Pineapple"),
		Card(28,	5,	18,	10,	0, 8,	"apple.png",	"Use this indestructible fruit to keep more than the doctor away!It's high defence and power should", 	"Apple"),
		Card(28,	5,	18,	10,	0, 8,	"apple.png",	"Use this indestructible fruit to keep more than the doctor away!It's high defence and power should", 	"Apple"),
		Card(29,	16,	5,	8,	0, 6,	"orange.png",	"Get on the wrong end of this fruit's attack and you'll end up sliced and juiced!", "Orange"),
		Card(29,	16,	5,	8,	0, 6,	"orange.png",	"Get on the wrong end of this fruit's attack and you'll end up sliced and juiced!", "Orange")};

	if (get_deck_num() == 0) {
		for (auto i : deck1) {
			add_card_to_deck(i);
		}
	}
	if (get_deck_num() == 1) {
		for (auto i : deck2) {
			add_card_to_deck(i);
		}
	}


	// Used for remote database of values
	//try {
	//	sql::Driver *driver;
	//	sql::Connection *con;
	//	sql::ResultSet *res;
	//	sql::PreparedStatement *pstmt;
	//	sql::ResultSet *res2 = nullptr;
	//	sql::PreparedStatement *pstmt2 = nullptr;
	//	/* Create a connection */
	//	//tcp://138.197.148.75
	//	//guest
	//	//guestUser
	//	driver = get_driver_instance();
	//	//con = driver->connect("tcp://192.168.2.96:3306", "guest", "cisc320");
	//	con = driver->connect("tcp://70.54.133.31:3306", "guest", "cisc320");
	//	/* Connect to the MySQL test database */
	//	con->setSchema("CISC320");
	//	/* Select in ascending order */
	//	//pstmt = con->prepareStatement("SELECT * FROM card WHERE idcard IN(0,1,2)");
	//	pstmt = con->prepareStatement("SELECT * FROM deck WHERE iddeck = " + std::to_string(get_deck_num()));
	//	res = pstmt->executeQuery();



	//	/* Fetch in reverse = descending order! */
	//	//res->afterLast();
	//	while (res->next()) {
	//		pstmt2 = con->prepareStatement("SELECT * FROM card WHERE idcard = " + std::to_string(res->getInt("card")));
	//		res2 = pstmt2->executeQuery();
	//		while (res2->next()) {
	//			Card test(res2->getInt("idcard"), res2->getInt("attack"), res2->getInt("defense"), res2->getInt("power"), res2->getInt("ability"), res2->getInt("cost"), res2->getString("image"), res2->getString("description"), res2->getString("name"));
	//			add_card_to_deck(test);
	//		}
	//	}
	//	delete pstmt2;
	//	delete res2;
	//	delete res;
	//	delete pstmt;
	//	delete con;
	//}
	//catch (sql::SQLException &e) {
	//	cout << "# ERR: SQLException in " << __FILE__;
	//	cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
	//	cout << "# ERR: " << e.what();
	//	cout << " (MySQL error code: " << e.getErrorCode();
	//	cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	//}
}