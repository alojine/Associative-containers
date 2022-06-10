
#include "Header.h"

using namespace std;


bool UrlCheck(string url, map<string, int> pabaigos) {

	bool check = false;
	std::regex url_pattern("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
	std::smatch url_match_result;
	if (std::regex_match(url, url_pattern)) { // matches url pattern
		check = true;
		return check;
	}		
		
	bool ar = false;

	
	for (int i = 0; i < url.length(); i++) {
		if (url[i] == '.') {
			ar = true;
		}
	}

	if (ar) {
		int taskas = 0; string galune;

		for (int i = 1; i < url.length(); i++) {
			if (url[i] == '.') 					// where is dot
				taskas = i;
		}

		if (taskas == 0) return check;

		for (int i = taskas + 1; i < url.length(); i++) {
			galune += url[i];
		}
		string pb;
		for (int i = 0; i < galune.length(); i++) {
			pb += toupper(galune[i]);
		}

		if (pabaigos.find(pb) != pabaigos.end()) {
			check = true;
			return check;
		}

	}

	return check;
}

string ValidateWord(string word) {

	word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());	// remove punctuation
	
	if (!word.empty()) {	// make lower case
		if ((word[0] >= 'A' && word[0] <= 'Z')) {
			word[0] = tolower(word[0]);
		}
	}
	
	return word;
}

struct text {
	string zodis;
	float kartai;
	vector<int> eilute;
};

int main() {

	int eil = 0;									
	string line, word;

	text z;											// struktura laikanti reiksmes
	map<string, vector<int> > wordMap;				// map for all possible words
	map<string, vector<int> >::iterator iter;		// map for iterator
	vector<text> trueMap;							// vector with my word (for output)

	ifstream fd("Input.txt");						// ivestis
	ofstream fr("Output.txt");						// isvestis
	ifstream pab("Pabaigos.txt");

	map<string, int> pabaigos;	string p;			// uzmapinamos visos imanomos pabaigos
	for (int i = 1; i < 1488; i++) {
		pab >> p;
		pabaigos.insert(make_pair(p, 1));
	}
		
	
	if (fd.is_open()) {
		while (getline(fd, line)) {
			eil++;
			istringstream ss(line);

			while (ss >> word) {
				if (UrlCheck(word, pabaigos)) {   // tikrina ar yra url
					cout << word << endl;
				}
				else {
					word = ValidateWord(word);  // numeta skirybos zenklus
					
					auto value = wordMap.insert(make_pair(word, 0));
					iter = wordMap.find(word);
					wordMap[iter->first].push_back(eil);

				}

			}

		}
	}

	for (auto otherMap : wordMap) {
		if (otherMap.second.size() > 1) {
			z.zodis = otherMap.first;
			z.kartai = otherMap.second.size();
			z.eilute = otherMap.second;

			trueMap.push_back(z);
		}

	}

	for (int i = 0; i < trueMap.size(); i++) {
		fr << std::setw(15) << left  << trueMap[i].zodis << " pasikartojantis " << std::setw(2) << left << trueMap[i].kartai << " kartu ir esantis: ";

		for (int j = 0; j < trueMap[i].eilute.size(); j++) {

			fr << " " << right << setw(3) << trueMap[i].eilute[j];

			/*		// unavailable because of exception handling :^(
			if (trueMap[i].eilute[j] != trueMap[i].eilute[j - 1])	// nespausdina tos pacios eilutes
				fr << " " << trueMap[i].eilute[j];
			*/
			
		}
		fr << endl;
	}


	return 0;
};

