//
//  driver.cpp
//
//
//  Created by Henry on 10/27/14.
//
//

#include <stdio.h>
#include "Card.h"
#include <vector>
#include <list>
#include <locale>
#include <string>
#include <sstream>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main (int argc, char **argv ) {

	string jeff = "Jeff";
	string doug = "Doug";
	cout << " JEFF < Doug" << (jeff < doug) << endl;
	
	string test = "JoeNamath 20000";
	int space = test.find(" ");
	cout << "JoeNamath has space at " << space << endl;
	cout << "string test[space+1] is " << test[space + 1] << endl;
	cout << "string test is length of " << test.length() << endl;
	cout << "testing substring for name: JoeNamath " << test.substr(0, space) << endl;
	cout << "testing substring of " <<  test.substr(space+1, test.length() - 1 )<< endl;
	string value = test.substr(space+1, test.length() - 1 );
	int v = atoi(value.c_str());
	cout << "Printing out int v = " << v << "\n"<< endl;
	
	//vector <int> t = {1, 2, 5};
	Card c2("Jeff", 2000, 1, 200 );
	Card c1 ("Doug", 100, 2, 100);
	Card c3 ("Arthur", 30000, 3, 200);
	
	
	vector <Card> t = {c2, c1, c3 };
	cout << t[0] << " " << t[1] << " " << t[2] << endl;
	t.clear();
	cout << "T size is equal to " << t.size() << endl;
	sort (t.begin(), t.end() );
	while (next_permutation(t.begin(), t.end()  )) {
		   cout << "After loop: " << t[0] << " " << t[1] << " " << t[2] << endl;
	}

	ofstream outf("Dinhofer_H_output.txt");
	 string progName(argv[0]);
	 cout << endl << "Argc is an integer containing the number of arguments, " << endl;
	 cout << "including the program name itself. " << endl << endl;
	 cout << "This program contains " << argc << " argument(s)." << endl << endl;
	 cout << "You ran this program with " << progName << endl;
	 cout << "The other arguments are: " << endl;
	 for (int i=1; i<argc; i++)
		cout << "argv[" << i << "]: " << argv[i] << endl;
	 // One "C++" way to convert the C-style string in argv[1] into an int
	 // Don't forget to #include <sstream>
	 if (argc > 1) {
		istringstream buf(argv[1]); // create an input string stream
		int num1;
		buf >> num1; // use the extraction operator
		cout << "argv[1] as an int: " << num1 << endl;
	 }
	int totalMPF = 0, weight = 0, plNum =0, maxProfit = 0, lastProfit = 0;
	
	vector <Card> mpf, best, temp;
	vector <Card> profit;
	vector <Card> priceLists; //redundant and wastes space
	if (argc == 5) {
		ifstream in (argv[2] ); //market-price
		string line;
		int pos = 1;
		while (!in.eof() ) {
			getline (in, line);
			if (pos == 1) { totalMPF = atoi(line.c_str()); pos++; }
			Card c2(line, pos);
			mpf.push_back(c2);
			pos++;
		}
		ifstream instream (argv[4] ); //price-lists
		string s;
		int pos2 = 1;
		bool boolFirstTime = true;
		while (!instream.eof() ) {
			getline (instream, s);
			locale l;
			if (isdigit (s[0], l)) {  //start compute maxProfit but first gotta strip out I, W, plNum
				if (priceLists.size() > 0 && boolFirstTime) {
					best = priceLists[0].computeMaxProfit(priceLists,weight); // int pass by reference for maxProfit?
					for (Card c: best ) {maxProfit += c.getValue(); }
					
					lastProfit = maxProfit;
					priceLists.clear();
					int space = s.find(" ");
					string num = s.substr(0, space);
					plNum = atoi(num.c_str());
					string val = s.substr(space+1, s.length() - 1 );
					weight = atoi(val.c_str());
					outf << "Size of input: " << plNum << " MaxProfit: " << maxProfit << " Number of cards: " << best.size() << endl;
					boolFirstTime = false;
					maxProfit = 0;
				
				}
				else if (priceLists.size() > 0 && boolFirstTime == false) {
						temp = priceLists[0].computeMaxProfit(priceLists,weight);
					for (Card c: temp ) {maxProfit += c.getValue(); }
					if (lastProfit < maxProfit) { // unnecessary I thought we had to keep track of the single best solution
						best.clear();
						for (Card c : temp) {
							Card copy = c;
							best.push_back(copy);}
					}
						priceLists.clear();
						int space = s.find(" ");
						string num = s.substr(0, space);
						plNum = atoi(num.c_str());
						string val = s.substr(space+1, s.length() - 1 );
						weight = atoi(val.c_str());
						outf << "Size of input: " << plNum << " MaxProfit: " << maxProfit << " Number of cards: " << temp.size() << endl;
						lastProfit = maxProfit;
						maxProfit= 0;
				}
				
			}
			else {
				Card c (s, pos2);
			//	Card c3 (c, mpf);
				int sellAtIndex = c.getIndex(c, mpf);
				int sellAt= mpf[sellAtIndex].getValue();
				int gertPrice = c.getValue();
				int profit = sellAt - gertPrice;
				if (profit < 0) {
					cout << "Youre losing money if you sell: " <<c.getName() << ", card not added to deck to consider" << endl;
				}
				else if ( !c.isFound(c, mpf) )
				{
					cout << "Card in price list file not found in market price file. Exiting program." << endl;
					break;
				}
				else {
				Card p (c.getName(), profit, pos2, c.getValue() );
				priceLists.push_back(p);
				pos2++;
				}
			}
		}
	}
	else{
		cout << "Please invoke the program as ./program1 -m <market-price-file> -p <price-list-file> " << endl;
	}

	cout << "TotalMPF: " <<  totalMPF << " items in mpf vector: \n";
	for (Card c : mpf) {cout << c << endl; }
	cout << "----------------\n " << endl;
	for (Card c: priceLists) { cout << c <<endl; }
	cout << "----------------\n " << endl;
	for (Card c: best) {cout << c << endl; }
	//cout << "MaxProfit = " << maxProfit <<"\n" << endl;
	cout << "weight is listed as: " << weight <<endl;
	cout << "Remaining cards are: " << endl;
	for (Card c: priceLists) { cout << c << endl; }
	best = priceLists[0].computeMaxProfit(priceLists,weight);
	for (Card c: best ) {maxProfit += c.getValue(); }
	outf << "Size of input: " << plNum << " MaxProfit: " << maxProfit << " Number of cards: " << best.size() << endl;
	
	 //argv[2] = <market-price-file>
	 //argv[4] = <price-list-file>
	
	return 0;
}
