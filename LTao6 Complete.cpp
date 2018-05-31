#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;



class Card
{

	public:
		string new_card;
		Card(string suit_value,string face_value,vector<Card>& deck_of_cards)
		{
			suit = suit_value;
			face = face_value;
			// create a card
			 new_card = suit_value + face_value; // create the card
           	//deck_of_cards.push_back(new_card);  // push into the vector
		}
		Card()
		{

		}

	/*	void print()
		{
			cout <<  new_card << endl;
		} */
		string print()
		{
			return new_card; // return the card
		}
		
		string get_suit() // get the suit
		{
			return suit; 
		}
		
		



	private:
		string suit;
		string face;
};

class Player
{
	public:

		virtual void print()
		{
			// cout << "This is the parent class";
		}
		virtual void set_player_number() // sets the player number
		{

		}
		// method to deal the cards
		virtual void initial_dealing(const Card& this_card)
		{

		}
		virtual void show_hand()
		{

		}
		virtual void choose_discard() // give it back an int later
		{
			
		}
		void replenish()
		{
			
		}
		virtual bool check_victory() // check if a player has won
		{
			
		}
	protected:
		int self_index; // index within player vector, starting with 0 for the human;
		int take_from; // player supplying new Card
		vector<Card> hand; // holds 7 cards
		Card discard; // card being discarded
		int discard_index; // position within hand of card being discarded
		static Card discard_list[ ];
		

};
Card Player::discard_list[5];

class Human: public Player
{
	// human derived class
	public:
		void set_player_number(int player_number_value)
		{
			player_number = player_number_value;
		}

		void initial_dealing(const Card& this_card) // deals the card
		{
			hand.push_back(this_card); // push the card to the hand
		}
		// show the cards in hand
		void show_hand()
		{
			
			cout << "Your hand: \n";
			cout << "0:\t\t";
			
			for(int i = 0; i < hand.size(); i++)
			{
			 	string s1 = hand[i].print();
			 	cout << s1 << "\t";
			}
			
			cout << "\n   \t\ta\tb\tc\td\te\tf\tg" << endl; // two spaces and two tabs followed by a\t b\t etc...
			
		}
		// only in human do we select it

		void print()
		{
			cout << player_number << endl;
		}
		
		void choose_discard(int discard_index_value) // discarding the card
		{
			discard_index = discard_index_value;
			discard = hand[discard_index];
			discard_list[0] = discard; // put card in
			string discard_value = discard.print(); // returns the card value
			cout << "Player 0 gave 1 " << discard_value << endl;
		}
		
		void replenish() // replenishing the hand
		{
			hand[discard_index] = discard_list[4];
		}
		bool check_victory() // check if the player won
		{
			// checks if this player has won
			string first_suit_value = hand[0].get_suit();
			bool victory_flag = true; // initially it is all the same suit
			for(int i = 1; i < hand.size(); i++)
			{
				if(hand[i].get_suit() != first_suit_value) // once one card is not the same suit, they could not win
				{
					return false;
				}
			}
			if(victory_flag == true)
			{
				cout << "\n\nPlayer " << player_number << " is a winner!";
				return true;
			}
			
		}
	private:
		int player_number;

};

class AutoPlayer: public Player
{
	public:
		void set_player_number(int player_number_value)
		{
			player_number = player_number_value;
		}
//	int player_number;
		void initial_dealing(const Card& this_card) // deals the card
		{
			hand.push_back(this_card);
		}
		//show hand
		void show_hand() // show the hands of the players
		{
			for(int i = 0; i < hand.size();i++)
			{

				string s1 = hand[i].print();
				cout << s1 << "\t";

			}
		}
		void choose_discard() // using logic to discard
		{
			int heart_count = 0;
			int spade_count = 0;
			int club_count = 0;
			int diamond_count = 0;
			string suit_value; // declare the variable out here so it doesn't have to be created every time it loops
			// find the number of  per suit in hand
			// the logic is that we get the suit with the most occurences , we then loop through the hand again and discard the first card that is not the suit with the most occurences
			for(int i = 0; i < hand.size(); i++)
			{
				suit_value = hand[i].get_suit(); // call get_suit method in Card class
				if(suit_value == "H")
				{
					heart_count++;
				}
				else if(suit_value == "S")
				{
					spade_count++;
				}
				else if(suit_value == "C")
				{
					club_count++;
				}
				else
				{
					diamond_count++;
				}
			}
			string most; // the suit with the most
			if((heart_count > spade_count) && (heart_count > club_count) && (heart_count > diamond_count))
			{
				most = "H"; // heart
			}
			else if((spade_count > heart_count) && (spade_count > club_count) && (spade_count > diamond_count))
			{
				most = "S"; // spade
			}
			else if((club_count > heart_count) && (club_count > spade_count) && (club_count > diamond_count))
			{
				most = "C"; // clubs
			}
			else
			{
				most = "D"; // 7 cards, 4 suits, one suit has to have the most 
			}
			// the card we discard is the first card that is not the "most"
			for(int i = 0; i < hand.size(); i++)
			{
				suit_value = hand[i].get_suit();
				if(suit_value != most) // if it is not of the most suit
				{
					discard_index = i;
					discard = hand[discard_index];
					discard_list[player_number] = discard;
					break; // we got our card
				}
			}
			string discard_value = discard.print(); // returns the card value
			if(player_number == 4)
			{
				cout << "Player 4 gave 0 " << discard_value << endl;
			}
			else // 1,2,3
			{
				cout << "Player " << player_number << " gave " << (player_number+1) << " " << discard_value << endl;
			}
			
			
		}
		void replenish() // replenish the hand
		{
			
			
			hand[discard_index] = discard_list[player_number-1];
			
		}
		void print() // print the player number
		{
			cout << player_number << endl;
		}
		bool check_victory()
		{
			// checks if this player has won
			string first_suit_value = hand[0].get_suit();
			bool victory_flag = true;
			for(int i = 1; i < hand.size(); i++)
			{
				if(hand[i].get_suit() != first_suit_value)
				{
					return false;
				}
			}
			if(victory_flag == true)
			{
				cout << "\n\nPlayer " << player_number << " is a winner!\n";
				return true;
			}
			
		}
	private:
		int player_number;

	// Autoplayer derived class
};

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main()
{
	srand(time(0)); // seed
	vector<string> different_suits = {"D","H","S","C"}; // diamonds, hearts, spades, clubs
	vector<string> different_faces = {"1","2","3","4","5","6","7","8","9","10","J","Q","K"}; // face values
	vector<Card> deck_of_cards;
	vector<Player *> players;

	for(int i = 0; i < different_suits.size(); i++) // create our deck of cards 
	{
		for(int j = 0; j < different_faces.size(); j++)
		{
			Card c = Card(different_suits[i],different_faces[j],deck_of_cards);
			deck_of_cards.push_back(c);
		}
	}
	// shuffle the deck
	random_shuffle(deck_of_cards.begin(),deck_of_cards.end());
	//create the players

	// print our new deck
	// delete later
/*	for(int i = 0; i < deck_of_cards.size(); i++)
	{
		string s2 = deck_of_cards[i].print();
		cout << s2 << endl;
		string s = deck_of_cards[i].print();
		cout << s << "\n";  */
	//}
	// create the human player and the autoplayers
	Human human; // create the pointer that is human
	Human *human_pointer = &human; // declaration of pointer human_pointer
	players.push_back(human_pointer); // push pointer of human
	human.set_player_number(0);
	// create AutoPlayer1
	AutoPlayer auto_player_one;
	AutoPlayer *player_one_pointer = &auto_player_one;
	auto_player_one.set_player_number(1);
	players.push_back(player_one_pointer);
	//create AutoPlayer2
	AutoPlayer auto_player_two;
	AutoPlayer *player_two_pointer = &auto_player_two;
	auto_player_two.set_player_number(2);
	players.push_back(player_two_pointer); // player_two_pointer holds the address of auto_player_two
	//create AutoPlayer3
	AutoPlayer auto_player_three;
	AutoPlayer *player_three_pointer = &auto_player_three;
	auto_player_three.set_player_number(3);
	players.push_back(player_three_pointer);
	// create AutoPlayer4
	AutoPlayer auto_player_four;
	AutoPlayer *player_four_pointer = &auto_player_four;
	auto_player_four.set_player_number(4);
	players.push_back(player_four_pointer);

	// algorithm to deal the cards
	int counter = 0;
	for(int i = 0; i < 35; i++) // deal first 35 cards of the shuffled deck
	{
		// counter corresponds to the player number
		// if the counter equals 4, reset the counter to 0 at the end of the loop
		players[counter]->initial_dealing(deck_of_cards[i]); // passing by reference a card object
		if(counter == 4)
		{
			counter = 0; // reset the counter
		}
		else
		{
			counter++;
		}
	}

//	cout << "Hands start to show \n";

	while(true)
	{
		// show our Hands
		players[0]->show_hand();
		// ask for input
		string input;
		cout << "cmd: ";
		cin >> input;

		if(input == "?")
		{
			for(int i = 0; i < 5; i++)
			{
				if(i != 0)
				{
					cout << i << ":\t\t";
				}
				players[i]->show_hand();
				cout << "\n";
			}
			cout << "cmd: ";
			cin >> input;
		}
		// make sure choice entered was valid
		while(!((input == "a") || (input == "b") || (input == "c") ||
		 (input == "d") || (input == "e") || (input == "f") || (input == "g")))
		 {
			 cout << "Invalid Choice " << endl;
			 cout << "cmd: ";
			 cin >> input;
		 }
		 int int_input;
		 if(input == "a") // converting the string input into an index
		 {
		 	int_input = 0;
		 }
		 else if(input == "b")
		 {
		 	int_input = 1;
		 }
		 else if(input == "c")
		 {
		 	int_input = 2;
		 }
		 else if(input == "d")
		 {
		 	int_input = 3;
		 }
		 else if(input == "e")
		 {
		 	int_input = 4;
		 }
		 else if(input == "f")
		 {
		 	int_input = 5;
		 }
		 else
		 {
		 	int_input = 6;
		 }
		 human.choose_discard(int_input); // take human input and discard
		 auto_player_one.choose_discard();
		 auto_player_two.choose_discard();
		 auto_player_three.choose_discard();
		 auto_player_four.choose_discard();
		 /*for(int i = 1; i <= 4; i++) // autoplayers discard
		 {
		 	players[i]->choose_discard();
		 }*/
		 human.replenish(); // chose top replenish might need to be changed, human replenishes
		 auto_player_one.replenish();
		 auto_player_two.replenish();
		 auto_player_three.replenish();
		 auto_player_four.replenish();
		 /*for(int i = 1; i <= 4; i++)
		 {
		 	players[i]->replenish(); // autoplayers replenishes
		 }*/
		 bool somebody_won = false; // nobody won yet, but more than one player can win
		 if(human.check_victory()) // human has won
		 {
		 	somebody_won = true;
		 }
		 for(int i = 1; i < players.size(); i++)
		 {
		 	if(players[i]->check_victory())
		 	{
		 	somebody_won = true;	
			}
		 }
		 if(somebody_won) // if somebody_won is true display everything
		 {
		 	cout << "At the end of the game the players had: \n";
		 	human.show_hand();
		 	for(int i = 1; i < 5; i++)
			{
				cout << i << ":\t\t";
				players[i]->show_hand();
				cout << "\n";
			}
			break;
		 }
		 // check if a player has won
	}
	cout << "Game is over" << endl;
	
	// players[4]->print(); // we use -> for pointers


return 0;
}

