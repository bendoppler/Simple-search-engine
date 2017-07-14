
#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include<cstdlib>
#include <vector>
#include<sstream>
#include<ctime>

using namespace std;

/*NO DAY NAY */
static int s;
class TrieNode
{
public:
	TrieNode *children[29];
	vector <int> numSen; //number sentence
	vector <int> numRow; //Teacher ask to output the row.
	TrieNode();
	bool isHave( int k );
};

class Trie
{
public:
	TrieNode *root;

	Trie() { root = new TrieNode(); }

	string isInSameSentence( string query );
	void insert( string & key, int & sentence, int & row );
	vector < pair<int, int> > search( string key );
};

void makeLowercase( string & a );
int charToNum( char x );
vector <string> strToVector( string query );

vector <string> getFileName();

vector <string> summary( string query, vector <Trie> &t );

vector <string> getNot( vector<string> a,  vector<string> b );
vector <string> getAnd( vector <string> A, vector <string> B );
vector <string> getOr( vector <string> A, vector <string> B );

void initTree( vector<Trie> & tree );
void deleteCachCach( string & s );
string getNotString( int &start ,const string &query);
vector <string> solve( int L, int R );
bool getNotStringRecursion(int &start, vector <string> &A, const string &query ,vector <Trie> &tree);
#endif // !TRIE_H

