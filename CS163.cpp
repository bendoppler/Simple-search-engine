#include "trie.h"
const string DIVIDE = "------------------------------------------------";
const int numChild = 29;
string query;
vector <Trie> tree;
void deleteCachCach( string & s ) {
	string res;
	int n = s.length();
	for (int i = 0; i < n - 1; ++i) {
		if (s[i] == ' ' && s[i + 1] == ' ') continue;
		res.push_back( s[i] );
	}
	res.push_back( s[n - 1] );
	s = res;
}
vector <string> solve( int L, int R ) {

	vector <string> res;
	if (L > R) return res;
	if (query[L] == '"') {
		return res; //Chua xong
	}
	string tmp = "";
	for ( s = L; s <= R - 2; ++s) {//s t de o trie.h tai do co ham not DE O PHIA DUOI NAMESPACE STD
		if (query[s] == 'A' && query[s + 1] == 'N' && query[s + 2] == 'D') {
			vector <string> A = summary( tmp, tree );
			vector <string> B = solve( s + 4, R );
			return getAnd( A, B );
		}
		if (query[s] == 'O' && query[s + 1] == 'R') {
			vector <string> A = summary( tmp, tree );
			vector <string> B = solve( s + 3, R );
			return getOr( A, B );
		}
		if (query[s] == '-') {
			vector<string> A = summary( tmp, tree );
			if (!getNotStringRecursion(s, A,query,tree)) {
				res = A;
				return res;
			}
			else {
				if (s < R - 2) {
					if (query[s] == 'A' && query[s + 1] == 'N' && query[s + 2] == 'D') {
						vector <string> B = solve( s + 4, R );
						return getAnd( A, B );
					}
					else if (query[s] == 'O'&&query[s + 1] == 'R') {
						vector <string> B = solve( s + 3, R );
						return getOr( A, B );
					}
				}
				else {
					return A;
				}
			}
 		}
		tmp.push_back( query[s] );
	}
	tmp.push_back( query[R - 1] );
	tmp.push_back( query[R] );
	//cout << "Gone summary: " << tmp << endl;
	return summary( tmp, tree );
}
int main() {
	ofstream fout; fout.open( "answer.txt" );
	vector<string> name = getFileName(); int m = name.size();
	int n;
	bool check=false;
	system( "dir/b Database > filename.txt" );
	initTree( tree );// insert
	vector <string> res;

	cout << "************DUMBLE**************" << endl;
	string ans;
	cout << "Do you want to search by hand?" << endl;
	getline( cin, ans );
	makeLowercase( ans );
	clock_t begin = clock();
	while (ans != "no") {
		cout << "Search: ";
		getline( cin, query );
		deleteCachCach( query );
		fout << DIVIDE << endl;
		fout << query << endl;
		n = query.size();
		res = solve( 0, n - 1 );
		check = false;
		for (int i = 0; i < m; ++i) {
			if (res[i] != "") {
				fout << name[i] << endl;
				if (i == m - 1)
					fout << res[i];
				else fout << res[i] << '\n';
				check = true;
			}
		}
		if (!check) fout << "Not found" << endl;
		cout << "Continue?\n";
		getline( cin, ans );
		makeLowercase( ans );
	}
	clock_t end = clock();
	cout << (float)(end - begin) / CLOCKS_PER_SEC;
	if (check == true) 
	{ fout.close(); return 0; }
	cout << "Search by file.\n";
	/***************Insert query by file****************/
	ifstream fin; fin.open( "query.txt" );
	if (!fin.is_open()) {
		cout << "No" << endl;
		return 0;
	}
	getline( fin, query );
	begin = clock();
	while (!fin.eof()) {
		fout << DIVIDE << endl;
		fout << query << endl;
		deleteCachCach( query );
		n = query.size();
		res = solve( 0, n - 1 );
		check = false;
		for (int i = 0; i < m; ++i) {
			if (res[i] != "") {
				fout << name[i] << endl;
				if (i == m - 1)
					fout << res[i];
				else fout << res[i] <<'\n';
				check = true;
			}
		}
		if (!check) fout << "Not found" << endl;
		getline( fin, query );
		//if (query == "") break;
	}
	end = clock();
	cout << (float)(end - begin) / CLOCKS_PER_SEC;
	fin.close();
	fout.close();
	return 0;
}