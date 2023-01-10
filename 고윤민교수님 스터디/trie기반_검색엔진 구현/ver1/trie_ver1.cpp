/*

	[Linux] + [C++]

	This is Related Search Machine based Trie.
	If you put a string that you want to search, you can find maximum 10 'Related Searches'.
	They all contains the string you put, and They are most frequently searched.

	Input data file has to have (string, number of search).
	Then this project will read data file, and make 'Related Search Machine' using it.


	Version 1			Text should be the same as the beginning of the sentence.

	Example		

	Search Text : 		Pohang

	Result :			Pohang Cafe		9000
						Pohang 			2000
						Pohang Weather  	1900
						Pohang Sea		 300

*/


#include <string>
#include <iostream>
#include <fstream> 	// file open
#include <algorithm> 	// sort
#include <vector> 	// vector
#include <unistd.h>	// for getch implementation
#include <termios.h>	// for getch implementation


using namespace std;

#define ALPHA 26


// Trie Struct

struct Trie{

	bool finish;		// End Point
	int num;			// number of searching
	string str;			// origin string (before modify)
	Trie* next[ALPHA];	// Trie pointer

	// Constructor

	Trie(){
		finish = false;
		str = "";
		for(int i = 0 ; i < ALPHA ; ++i) next[i] = NULL;
		num = 0;
	}

	// Destructor
	~Trie(){};
	
	// Member Function

	void Insert(const char* key , int num , string str);
	void Search_key(const char* key , vector<pair<string,int>> &search_pair);
	void Search_all(vector<pair<string,int>> &search_pair);
	void Search_n_Print();

};


// Sub Functions
// convert Upper + remove space

string Convert_str(string s1){
	string s2= "";
	for(int i = 0 ; i < s1.size();++i) s2 += toupper(s1[i]);
	s2.erase(remove(s2.begin(),s2.end(),' '),s2.end());
	return s2;
}

// Getch Function Implementation
// Get keyboard input

int getch(){

	int c;
	struct termios oldattr, newattr;

	tcgetattr(STDIN_FILENO , &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	newattr.c_cc[VMIN] = 1;
	newattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return c;
}

// Compare Function
// Pair.second -> Descending Order

bool compare(const pair<string,int> &a , const pair<string,int> &b)
{
	return a.second > b.second;
}


// Insert Function
// Insert converted string , number of searching , origin string

void Trie::Insert(const char* key, int num , string str){
	if(*key=='\0'){
		finish = true;
		this->num = num;
		this->str = str;	
		return;
	}

	int index = *key - 'A';
	
	if(!next[index]){
		next[index] = new Trie();
	}
	next[index]->Insert(key+1,num,str);

}


// Search and Print Function
// 
void Trie:: Search_n_Print(){
	
	// Pair of Found str & num 
	vector<pair<string,int>> search_pair;
	
	// variables
	string mdf_str;
	string str="";
	int c;
	char c_ch;
	
	// Clear print

	system("clear");
	printf("text : \n");
	printf("------------------------------------------------------");


	// Search and Print
	for(;;){

		// Print
		if(c = getch()){
			if(c == 127){
				system("clear");
				if(str!="") str.pop_back();
				printf("\033[38;2;255;255;0mtext : %s\n", str.c_str());
				printf("\033[0m------------------------------------------------------\n");
			}
			else{
				c_ch = c;
				system("clear");
				str+=c_ch;
				printf("\033[38;2;255;255;0mtext : %s\n",str.c_str());
				printf("\033[0m------------------------------------------------------\n");
			}

			// Search
			if(str == "") continue;

			// Convert str
			mdf_str = Convert_str(str);
			
			// Search string having mdf_str.
			Search_key(mdf_str.c_str(),search_pair);
	
			// Found string sort ( Number of Searching - Descending )
			sort(search_pair.begin() , search_pair.end() , compare);
			
			// Print Found list (Result)
			for(int i = 0 ; i < search_pair.size() && i < 10; ++i){ 
				printf("\033[38;2;0;255;255m%s %d\n",search_pair[i].first.c_str(), search_pair[i].second);
			}

			// Clear
			search_pair.clear();
		}
	}

}




// Searching Function
// Searching strings having Input string
void Trie::Search_key(const char* key, vector<pair<string,int>> & search_pair){
	
	// if this Trie has all 'const char* key'
	// Then from this location, it starts searching all string which it has.
	if(*key == '\0'){ Search_all(search_pair); return;}
	
	int index = *key - 'A';

	// If this Thie doesn't have all 'const char* key'
	if(!next[index]) return ;

	// next key check (recursive)
 	next[index]->Search_key(key+1,search_pair);
}



// Search_all Function
// It Searchs all strings, and it pushed all in vector.

void Trie::Search_all(vector<pair<string,int>> &search_pair){
	
	if(finish) search_pair.push_back(make_pair(this->str,this->num));
	
	for(int i = 0 ; i < ALPHA ; ++i){
		if(next[i]) next[i]->Search_all(search_pair);
	}

}


// Main Function

int main(int argc , char** argv){
	
	Trie* test = new Trie();

	// Variables

	string mdf_str;
	string str;
	int num;
	string line;
	
	ifstream openFile(argv[1]);

	system("clear");

	// Data File Reading

	if(openFile.is_open()){
		cout << " ";
		while(getline(openFile,line)){
			
			// origin str
			str = line.substr(0,line.find(","));

			// converted str
			mdf_str = Convert_str(str);

			// number of searching
			num = stoi(line.substr(line.find(",")+1));
			
			// insert in Trie
 			test->Insert(mdf_str.c_str(),num,str);
	
		}
		openFile.close();
	}


	test->Search_n_Print();
	return 0;
}
