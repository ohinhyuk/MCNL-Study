/*

	[Linux] + [C++]


	This is Related Search Machine based Trie.
	If you put a string that you want to search, you can find maximum 10 'Related Searches'.
	They all contains the string you put, and They are most frequently searched.

	Input data file has to have (string, number of search).
	Then this project will read data file, and make 'Related Search Machine' using it.


	Version 2			Text should be included in the sentence.

	Example

	Search Text :		Pohang

	Result :			Busan and Pohang	3000
						Pohang sea			2000
						Pohang				1000
						Popohang			 500


*/


// Header
#include <iostream>
#include <fstream> 	// file open
#include <algorithm> 	// sort
#include <vector> 	// vector
#include <unistd.h>	// for getch implementation
#include <termios.h>	// for getch implementation
#include <map>		// map


using namespace std;

#define ALPHA 26 // Trie for A~Z
 

// Trie Struct

struct Trie{
	bool finish;		// is finish
	string search_str;	// search string
	int search_num;		// search number
	Trie* next[ALPHA];	// Trie pointer array
	
	// Constructor
	Trie(){
		finish = false;
		search_str = "";
		for(int i = 0 ; i < ALPHA ; ++i) next[i] = NULL;
		search_num = 0;
	}

	// Destructor
	~Trie(){ 
		for(int i = 0 ; i < ALPHA ;++i) delete next[i];
	}
	
	//Trie Functions

	void search_n_print();
	void search_Trie(const char* key , map<string,int> &searched_map);
	void key_start(const char* key , map<string,int> & searched_map);
	void search_all_sentence( map<string,int> &searched_map);
	void insert(const char* key , int num, string str);
	
		
};



// SubFunctions

// modify_str
// upper + remove space.
string modify_str(string s1){
	string s2= "";
	for(int i = 0 ; i < s1.size();++i) s2 += toupper(s1[i]);
	s2.erase(remove(s2.begin(),s2.end(),' '),s2.end());
	return s2;
}


// Getch Implementation

// get char from keyboard input.
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

// compare second element of pair
// In descending order
bool compare(const pair<string,int> &a , const pair<string,int> &b)
{
	return a.second > b.second;
}


// Trie Functions

// Search & Print Function
// It Gets string from keyboard
// It finds Related searched string from Trie.
// Print	
void Trie:: search_n_print(){

	map<string,int> searched_map;
	vector<pair<string,int>> searched_vec;
	
	string text="";
	
	int c;
	char c_mf;
	
	// text searching start

	system("clear");
	printf("text : \n");
	printf("-----------------------------------------");
	
	// text searching
	
	for(;;){
		if(c = getch()){
			
			// If input is space
			if(c == 127){
				system("clear");
				if(text!="") text.pop_back();
				printf("\033[38;2;255;255;0mtext : %s\n", text.c_str());
				printf("\033[0m-----------------------------------------\n");
			}
			
			// If input is alphabet
			else{
				c_mf = c;
				system("clear");
				text+=c_mf;
				printf("\033[38;2;255;255;0mtext : %s\n",text.c_str());
				printf("\033[0m-----------------------------------------\n");
			}
			
			// Search and Print result
			
			// Search
			string str_mf = modify_str(text);
			search_Trie(str_mf.c_str(),searched_map); // Search_Trie
	
			// sort in descending order for search_num
			for(auto it:searched_map) searched_vec.push_back(make_pair(it.first,it.second));
			sort(searched_vec.begin() , searched_vec.end() , compare);
			
			// Print highest ten results.
	       		for(int i = 0 ; i < searched_vec.size() && i < 10 ; ++i) printf("\033[38;2;0;255;255m%s    %d\n",searched_vec[i].first.c_str(),searched_vec[i].second);
			
			// clear
			searched_vec.clear();
			searched_map.clear();
		}
	}

}


// Search Trie Function

// All Trie search for containing string 'key'
void Trie:: search_Trie(const char* key, map<string,int>& searched_map){
	if(!next || *key=='\0') return;
	
	int index = *key - 'A';

	for(int i = 0 ; i < ALPHA; ++i){
		if(next[i]){
			if(i==index) next[i]->key_start(key+1,searched_map); //function
			next[i]->search_Trie(key , searched_map);
		}
	}
	
}


// Key Start Function

// matcing all part of string using string that corrects first char.
void Trie:: key_start(const char* key , map<string,int> & searched_map){
	
	if(*key=='\0'){ search_all_sentence(searched_map);
		return;}

	int index = *key - 'A';

	if(!next[index]) return ;

	next[index]->key_start(key+1,searched_map);

}

// Search Full Sentence Function

// search all strings containing matched string using mathced string.
// get origin string.
void Trie::search_all_sentence(map<string,int> &searched_map){
	if(finish){
		searched_map.insert({ search_str , search_num }); 
		if(!next) return;
	}
	
	for(int i = 0 ; i < ALPHA ; ++i){
		if(next[i]) next[i]->search_all_sentence(searched_map);
			
	}

}

// Insert Function

// From datafile , make Trie and insert all data.
void Trie::insert(const char* key, int num, string str){
	if(*key=='\0'){
		finish = true;
        search_str = str;
		search_num = num;
		return;
	}

	int index = *key - 'A';
	
	if(!next[index]){
		next[index] = new Trie();
	}
	next[index]->insert(key+1,num,str);

}


// Main Function

// 1) Data file Reading
// 2) Insert all data in Trie
// 3) Search 'Related Search'
// 4) Print
	
int main(int argc , char** argv){

	Trie* searchMachine = new Trie();
	
	string line;
	ifstream openFile(argv[1]);
	
	if(openFile.is_open()){
		cout << " ";
		while(getline(openFile,line)){
			
			// data -> string
			string str_origin = line.substr(0,line.find(','));
			
			// data -> int
			int search_num = stoi(line.substr(line.rfind(',')+1));

			// string modify : capital + remove space
			string str_mf = modify_str(str_origin);	
			
			// insert string(modified) in Trie
 			searchMachine->insert(str_mf.c_str(),search_num, str_origin);
	
		}
		openFile.close();
	}

	searchMachine->search_n_print();
	return 0;
	
}
