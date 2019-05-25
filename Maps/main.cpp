//Michael Lewis - MikesTheGuy
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<pair<string, string>, float> bigram_counts;
map<string, float> unigram_counts;

void calc_bigrams(const string&);
void lookup_bigram(const string&, const string&);
void process(string&);

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: ./calc_bigrams <FILENAME>\n";
		return 0;
	}

	calc_bigrams(argv[1]);
    cout << "Made it here" << endl;

	vector<pair<string, string>> words = {
		{ "with", "me" },
		{ "the", "grass" },
		{ "the", "king" },
		{ "to", "you" }
	};

	for (auto p : words) {
		lookup_bigram(p.first, p.second);
	}

	return(0);
}

// Given filename fn, read in the file word by word
// for each word:
// 1. process(word)
// 2. increment count of that word in unigram_counts
// 3. increment count of (prevword, word) in bigram_counts
void calc_bigrams(const string& fn) {
    ifstream infile(fn, std::ifstream::in); //Declare new input filestream and attempt to open it
    string word1, word2;

    if(infile.is_open()){ //Check if input filestream is open
        cout << "Successfully opened file." << endl;
        infile >> word1 >> word2; //Get the first two words
        process(word1);
        process(word2);
        unigram_counts[word1] += 1;
        unigram_counts[word2] += 1;
        bigram_counts[make_pair(word1, word2)] += 1; //Increment bigram count of both words

        word1 = word2; //Sets the previous word for next word input

        while(!infile.eof()){ //While not at end of file
            infile >> word2;
            process(word2);
            unigram_counts[word2] += 1; //Increment count of input word
            bigram_counts[make_pair(word1, word2)] += 1;
            word1 = word2;
        }
    }
    else if(!infile.is_open()){ //End program is filestream isn't open
        cout << "Error, file not found." << endl;
        cout << "Terminating porgram." << endl;
        exit(1);
    }

    infile.close(); //Close input file stream
}

// Given words w1 and w2,
// 0. process the words
// 1. print the words
// 2. if bigram (w1, w2) is not found, print "Bigram not found"
// 3. print how many times w1 appears
// 4. print how many times (w1, w2) appears
// 5. print count(w1, w2)/count(w1)
// (see example output)
void lookup_bigram(const string& w1, const string& w2) {
    string copy1 = w1, copy2 = w2;
    cout << w1 << ", " << w2 << ":" << endl;
    process(copy1);
    process(copy2);

    map<pair<string, string>, float>::iterator it;
    it = bigram_counts.find(make_pair(copy1, copy2)); //Get iterator to element position

    if(it == bigram_counts.end()){ //If element isn't found
        cout << "Bigram " << w1 << " " << w2 << " not found." << endl;
    }
    else{
        cout << copy1 << " appears " << unigram_counts[copy1] << " times." << endl;
        cout << copy1 << ", " << copy2 << " appears " << bigram_counts[make_pair(copy1,copy2)] << " times." << endl;
        cout << bigram_counts[make_pair(copy1, copy2)] / unigram_counts[w1] << endl;
    }
    return;
}

void process(string& str) {
	for (int i = 0; i < str.length(); ++i) {
		if(isalpha(str[i])) {
			str[i] = tolower(str[i]);
		}
		else {
			str[i] = '*';
		}
	}
	str.erase( remove(str.begin(), str.end(), '*'), str.end());
	return;
}
