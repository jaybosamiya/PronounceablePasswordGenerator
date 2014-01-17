#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool fileExists(char *file);
void readAll(char *file);
void generatePassword();

int mono[26];
int di[26][26];
int tri[26][26][26];

int n, pronouncability = 5;

char *password;

int main(int argc, char** argv) {
	if ( argc != 3 && argc != 4 ) {
		cerr << "Usage: " << argv[0] << " <trigraph name> <password length> [pronouncability]\n";
		return 0;
	}
	if ( !fileExists(argv[1]) ) {
		cerr << "Trigraph file " << argv[1] << " missing.\n";
		return 0;
	}
	if ( argc == 4 ) {
		int ZZZ = atoi(argv[3]);
		pronouncability = (ZZZ < 20)?ZZZ:20;
		pronouncability = ((pronouncability>0)?pronouncability:1);
	}
	readAll(argv[1]);
	n = atoi(argv[2]);
	password = new char[n];
	generatePassword();
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
	srand(time(NULL));
	char k1 = -1, k2 = -1, k3 = -1;
	int bestVal = 0;
	char bestChar = 'z';
	for ( int i = 0 ; i < n ; i++ ) {
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
}
