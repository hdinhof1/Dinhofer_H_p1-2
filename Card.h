//
//  Card.h
//  
//
//  Created by Henry on 2/12/15.
//
//

#ifndef ____Card__
#define ____Card__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include <vector>
#include <list>



using namespace std;

class Card {
private:
	int value;
	string name;
	int  pos;
	int weight;
	//ofstream outf;

public:
	
	Card (string n, int p);
	Card(string name, int value, int pos, int weight);
	Card (Card &c, vector<Card> &v);
	bool isFound (Card &c, vector <Card> card);
	vector<Card> computeMaxProfit(vector<Card> I, int W);
	Card &operator= (const Card &right);
	bool operator > (const Card & right) const;
	bool operator < (const Card &right) const;
	bool operator () (const Card &left, const Card & right) const;

	friend int operator+ ( const Card &c1,  const Card &c2);
	friend bool operator== (const Card &c1, const Card &c2);
	void setValue (int v);
	string getName();
	int getValue();
	int getWeight();
	int getIndex(Card c, vector <Card> card);
	friend ostream & operator << (ostream&out, const Card &c);
	
	//bool operator== ( const Nick &n1, const Nick &n2)
	//{
	//	return n1.username == n2.username;
	//}

	//string createName(string val);
	
	
	//friend isPowerOfTwo (unsigned int x);
	
};


#endif /* defined(____Card__) */
