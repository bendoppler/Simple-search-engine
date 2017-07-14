#include "trie.h"


void makeLowercase( string & a ) {
	int n = a.length();
	for (int i = 0; i < n; ++i)
		if ('A' <= a[i] && a[i] <= 'Z')
			a[i] = a[i] - 'A' + 'a';
}

int charToNum( char x ) {
	if (x == '#') return 26;
	if (x == '$') return 27;
	if (x == '\'') return 28;
	return x - 'a';
}

bool isWord( char x ) {
	return (x >= 'a' && x <= 'z') || (x == '#') || (x == '$') || (x == '\'');
}

vector <string> strToVector( string query ) {
	makeLowercase( query );
	vector <string> res;
	string tmp = "";
	int len = query.length();
	for (int i = 0; i < len; ++i) {
		if (isWord( query[i] ))
			tmp.push_back( query[i] );
		else {
			if (tmp == "") continue;
			res.push_back( tmp );
			tmp.clear();
		}
	}
	if (tmp != "") res.push_back( tmp );
	return res;
}

vector <string> getFileName() {
	ifstream fin; fin.open( "filename.txt" );
	string tmp; getline( fin, tmp );
	vector<string> res;
	while (!fin.eof()) {
		res.push_back( tmp );
		getline( fin, tmp );
	}
	fin.close();
	return res;
}

Trie getTrie( ifstream & fin ) {
	Trie res;
	string tmp = "";
	string iterate; getline( fin, iterate );
	makeLowercase( iterate );
	int row = 0, sentence = 1;
	while (!fin.eof()) {
		row++;
		int n = iterate.length();
		for (int i = 0; i < n; ++i) {
			char k = iterate[i];
			if (isWord( k ))
				tmp += k;
			else {
				if (!tmp.empty()) {
					res.insert( tmp, sentence, row );
					tmp.clear();
				}
			}
			if (k == '.' || k == '!' || k == ';' || k == '?')
				sentence++;
		}
		getline( fin, iterate );
		makeLowercase( iterate );
	}
	fin.close();
	return res;
}

void initTree( vector <Trie> &tree ) {
	vector <string> name = getFileName();
	tree.resize( name.size() );
	ifstream fin;
	for (int i = 0; i < (int)name.size(); ++i) {
		fin.open( "Database/" + name[i] );
		tree[i] = getTrie( fin );
		fin.close();
	}
}

vector <string> summary( string query, vector<Trie> &t ) {
	int numTries = t.size();
	vector<string> ret( numTries );
	for (int i = 0; i < numTries; i++)
		ret[i] = t[i].isInSameSentence( query );
	return ret;
}

vector<string> getAnd( vector<string> a, vector<string> b ) {
	vector <string> res( a.size() );
	for (int i = 0; i < a.size(); ++i)
		res[i] = (a[i].empty() || b[i].empty()) ? "" : a[i] + "\n" + b[i];
	return res;
}

vector<string> getOr( vector<string> a, vector<string> b ) {
	vector <string> res( a.size() );
	for (int i = 0; i < a.size(); ++i) {
		if (a[i] == "")
			res[i] = b[i];
		else if (b[i] == "")
			res[i] = a[i];
		else
			res[i] = a[i] + "\n" + b[i];
	}
	return res;
}

/***************HAM TAO LAM O DAY*********************/
vector <string> getNot( vector<string> a, vector<string> b ) {
	int len = a.size();
	for (int i = 0; i < len; i++) {
		if (!b[i].empty()) {
			a[i] = "";
		}
	}
	return a;
}
string getNotString( int &start,const string &query ) {
	start = start + 1;
	string ret="";
	if (start == query.size())return ret;
	int len = query.size();
	int i;
	for (i = start; i < len; ++i) {
		if (isWord( query[i] )) {
			ret += query[i];
		}
		else {
			start = i+1;
			s = start;
			return ret;
		}
	}
	start = i;
	s = i;
	return ret;
}
bool getNotStringRecursion(int &start, vector <string> &A, const string &query,vector <Trie> &tree ) {
	string rem = getNotString( start, query );
	vector<string> C = summary( rem, tree );
	A = getNot( A, C );
	int len = A.size();
	bool check = true;
	for (int i = 0; i < len; ++i) {
		if (A[i] != "") {
			check = false;
			break;
		}
	}
	if (check == true) return false;
	if (query[start] == '-') {
		return getNotStringRecursion( start, A, query, tree );
	}
}