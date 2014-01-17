#include <iostream>
#include <fstream>

using namespace std;

int mono[26];
int di[26][26];
int tri[26][26][26];

bool fileExists(char *file);
void parse(char *file);
void output(char *file);

int main(int argc, char **argv) {
	if ( argc < 3 ) {
		cerr << "Usage: " << argv[0] << "<trigraph name> <name of text file>\n";
		return 0;
	}
	if ( fileExists(argv[1]) ) {
		char c;
		cout << argv[1] << " already exists. Do you want to overwrite? [Y/N] ";
		cin >> c;
		if ( c != 'Y' && c != 'y' ) {
			cout << "Process aborted.\n";
			return 0;
		}
	}
	for ( int ZZZ = 2 ; ZZZ < argc ; ZZZ++ ) {
		parse(argv[ZZZ]);
	}
	output(argv[1]);
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

void parse(char *file) {
	if ( fileExists(file) ) {
		cerr << "Error opening " << file << ".\n";
		return;
	}
	
	ifstream ifile(file);
	char c;
	char k1 = -1, k2 = -1, k3 = -1;
	
	while ( ifile.get(k3) ) {
		if ( k3 >= 'a' && k3 <= 'z' ) {
			k3 -= 'a';
		} else if ( k3 >= 'A' && k3 <= 'Z' ) {
			k3 -= 'A';
		} else {
			continue;
		}
		if ( k1 >= 0 ) {
			tri[k1][k2][k3]++;
		}
		if ( k2 >= 0 ) {
			di[k2][k3]++;
		}
		mono[k3]++;
		k1 = k2;
		k2 = k3;
	}
	
	ifile.close();
}

void output(char *file) {
	ofstream ofile(file,ios::binary);
	
	ofile.write((char*)mono,sizeof(mono));
	ofile.write((char*)di,sizeof(di));
	ofile.write((char*)tri,sizeof(tri));
	
	ofile.close();
}
