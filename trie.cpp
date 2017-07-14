#include "Trie.h"

TrieNode::TrieNode() {
	for (int i = 0; i < 29; ++i)
		children[i] = NULL;
	numSen.clear();
	numRow.clear();
}

bool TrieNode::isHave( int k ) {
	for (int i = 0; i < (int)numSen.size(); ++i)
		if (numSen[i] == k) return true;
	return false;
}

string Trie::isInSameSentence( string query ) {
	vector <string> word = strToVector( query );
	vector <pair<int, int> > result;
	for (int i = 0; i < (int)word.size(); ++i) {
		vector <pair<int, int> > a = search( word[i] );
		for (int j = 0; j < (int)a.size(); j++)
			result.push_back( a[j] );
	}
	sort( result.begin(), result.end() );
	string res = query + " is founded in the row: ";
	bool check = false;
	int size = word.size(), len = result.size();
	string tmp;
	for (int i = 0; i < len - size + 1; ++i) {
		if (result[i].first == result[i + size - 1].first) {
			check = true;
			tmp = to_string( result[i].second );
			res += tmp + " ";
		}
	}
	return check ? res  : "";
}

void Trie::insert( string & key, int & sentence, int & row ) {
	makeLowercase( key );

	int length = key.length();

	TrieNode *tmp = root;

	for (int level = 0; level < length; ++level) {
		int index = charToNum( key[level] );
		if (!tmp->children[index])
			tmp->children[index] = new TrieNode();
		tmp = tmp->children[index];
	}
	if (!(*tmp).isHave( sentence )) {
		tmp->numSen.push_back( sentence );
		tmp->numRow.push_back( row );
	}
}

vector <pair<int, int> > Trie::search( string key ) {
	makeLowercase( key );
	int length = key.length();
	TrieNode *tmp = root;
	vector <pair<int, int> > res;

	for (int level = 0; level < length; ++level) {
		int index = charToNum( key[level] );
		if (!tmp->children[index])
			return res;
		tmp = tmp->children[index];
	}
	for (int i = 0; i < tmp->numSen.size(); ++i)
		res.push_back( pair<int, int>( tmp->numSen[i], tmp->numRow[i] ) );
	return res;
}
