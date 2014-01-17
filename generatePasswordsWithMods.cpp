#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool fileExists(char *file);
void readAll(char *file);
void generatePassword();
void modPassword();
void output();

int mono[26];
int di[26][26];
int tri[26][26][26];

int n, pronouncability = 5;
int counter = 1;

const int MAXPRO = 25;

char *password;

inline void seedRNG() { srand(time(NULL)); }

int main(int argc, char** argv) {
	seedRNG();
	if ( argc != 3 && argc != 4 && argc != 5 ) {
		cerr << "Usage: " << argv[0] << " <trigraph name> <password length> [number of passwords] [pronouncability]\n";
		return 0;
	}
	if ( !fileExists(argv[1]) ) {
		cerr << "Trigraph file " << argv[1] << " missing.\n";
		return 0;
	}
	if ( argc >= 4 ) {
		int ZZZ = atoi(argv[3]);
		counter = (ZZZ>0)?ZZZ:1;
	}
	if ( argc == 5 ) {
		int ZZZ = atoi(argv[4]);
		pronouncability = (ZZZ < MAXPRO)?ZZZ:MAXPRO;
		pronouncability = ((pronouncability>0)?pronouncability:1);
	}
	readAll(argv[1]);
	n = atoi(argv[2]);
	password = new char[n+1];
	for ( int i = 0 ; i < counter ; i++ ) {
		generatePassword();
		modPassword();
		output();
	}
	delete[] password;
	return 0;
}

bool fileExists(char *file) {
	ifstream ifile(file);
	if ( !ifile ) {
		ifile.close();
		return false;
	}
	ifile.close();
	return true;
}

void readAll(char *file) {
	ifstream ifile(file,ios::binary);
	
	ifile.read((char*)mono,sizeof(mono));
	ifile.read((char*)di,sizeof(di));
	ifile.read((char*)tri,sizeof(tri));
	
	ifile.close();
}

int getValue(int k1, int k2, int k3) {
	if ( k1 >= 0 ) return tri[k1-'a'][k2-'a'][k3-'a'];
	if ( k2 >= 0 ) return di[k2-'a'][k3-'a'];
	return mono[k3-'a'];
}

void generatePassword() {
	char k1 = -1, k2 = -1, k3 = -1;
	for ( int i = 0 ; i < n ; i++ ) {
		int bestVal = 0;
		char bestChar = 'z';
		while ( bestVal == 0 ) {
			char c = ((rand() % 26)+'a');
			int val = getValue(k1,k2,c);
			if ( val > bestVal ) {
				bestVal = val;
				bestChar = c;
			}
		}
		for ( int j = 0 ; j < pronouncability ; j++ ) {
			char c = ((rand() % 26)+'a');
			int val = getValue(k1,k2,c);
			if ( val > bestVal ) {
				bestVal = val;
				bestChar = c;
			}
		}
		k3 = bestChar;
		password[i] = k3;
		k1 = k2;
		k2 = k3;
	}
	password[n] = 0;
}

void modPassword() {
	char specials[] = {'!','@','#','$','%'};
	for ( char *c = password ; *c ; c++ ) {
		if ( rand() % 4 == 0 && *c >= 'a' && *c <= 'z' ) {
			*c = *c - 'a' + 'A';
		}
	}
	password[n-(n/5)-1] = specials[rand()%5];
	for ( int i = n - (n/5) ; i < n ; i++ ) {
		password[i] = (rand()%10)+'0';
	}
}

void output() {
	cout << password << endl;
}
