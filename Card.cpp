//
//  Card.cpp
//  
//
//  Created by Henry on 2/12/15.
//
//

#include "Card.h"
#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>
#include <vector> 
#include <locale>


Card::Card (string n, int p) {
	int space = n.find(" ");
	name = n.substr(0, space);
	string val = n.substr(space+1, n.length() - 1 );
	value = atoi(val.c_str());
	pos = p;
	weight = 0;

}

Card:: Card ( string n, int v, int p, int w) {
	
	value = v;
	name = n;
	pos = p;
	weight = w;

	// makes sense to just strip the int out from the string getline
	
	/*
	a = first;
	b = second;
	//ofstream outf;
	outf.open(outFileName);
	//outf.open(argv[2]);
	if (outf.is_open() ) {
		cout << "Opened outputfile"<<endl;
	}
	else {
		cout << "Error opening file " <<endl;
	}
	*/
}
Card::Card (Card &c, vector <Card> &mpf) {
	if (isFound (c, mpf) ) {
		value = c.value;
		name = c.name;
		pos = c.pos;
		//Card temp = mpf.find (c);
		//cout << "indexVal " << indexVal << endl;
	}
}
void Card::setValue (int v) {
	value = v;
}
string Card::getName () {
	return name;
}
int Card::getValue () {
	return value;
}
int Card::getWeight() {
	return weight;
}

bool Card::isFound (Card &c , vector <Card> card ) {
	bool b = false;
	for (int i = 0; i < card.size(); i++ ) {
		if (card[i] == c)
		{b = true; }
	}
	return b;
}

int Card::getIndex (Card c, vector <Card> card)
{
	int ret = 0;
	for (int i = 0; i < card.size(); i++ ) {
		if (card[i] == c) {
			return ret;
		}
		else {
			ret++;
		}
	}
	return ret;
}


bool Card::operator > (const Card & right) const {
	Card p = right;
	Card p2 = *this;
	return (p2.pos > p.pos);
}

bool Card::operator < (const Card & right) const {
	Card p = right;
	Card p2 = *this;
	return (p2.pos < p.pos);
}

bool Card::operator () (const Card &left, const Card &right) const  {
	return left.pos  < right.pos;
}

bool operator == (const Card &c1, const Card &c2 ) {
	return c1.name == c2.name;
}


int operator+ ( const Card &c1, const Card &c2) {
	//if (c1 == c2)
	//{
		return (c1.value - c2.value);
		//c2.setValue (c1.value - c2.value);
	//}
	
}
vector<Card> Card::computeMaxProfit (vector<Card> I, int W)
{
	int maxProfit =0;
	vector <Card> S; // current set to consider
	vector <Card> M; // current maxProfit subset
	int sum =0;
	int currentProfit = 0;
	for (int i= 0; i< I.size(); i++) {
		sum += I[i].getWeight();
		maxProfit += I[i].getValue();
		Card copy = I[i];
		M.push_back(copy );
	}
	if ( sum <= W) {
		return M;
	}
	else {
		
		sum = maxProfit = 0; //reset
		for (int i = 0; i < I.size(); i++) {
			if ( (sum += I[i].getWeight() ) <= W) {
				sum+= I[i].getWeight();
				currentProfit += I[i].getValue();
				Card copy = I[i];
				S.push_back(copy);
			}
		}
		if (currentProfit > maxProfit ) {
			maxProfit = currentProfit;
			M.clear();
			for (Card c: S) {
				Card copy = c;
				M.push_back(copy); }
		}
		//Utilizes next permutation function to go through all possible subsets, brute force

		while (next_permutation(I.begin(), I.end()  ))
		{
			sum = currentProfit = 0;
			for (int i = 0; i < I.size(); i++ ) {
				if ( (sum += I[i].getWeight() ) <= W) {
					sum+= I[i].getWeight();
					currentProfit += I[i].getValue();
					Card copy = I[i];
					S.push_back(copy);
				}
			}
			if (currentProfit > maxProfit ) {
				maxProfit = currentProfit;
				M.clear();
				for (Card c: S) {
					Card copy = c;
					M.push_back(copy); }
			}
		}

		
	}
	return M;
	
	
	
}
Card &Card::operator=(const Card& right) {
	value = right.value;
	name = right.name;
	pos = right.pos;
	weight = right.weight;
	return (*this);
}

ostream & operator << (ostream &out, const Card &c) {
	
	Card copy = c;
	//if (copy.carValue == 13)  ...cout
	out <<copy.name << " "<< copy.value;
	
	
	return out;
}







