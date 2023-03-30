/*
#############################################################################################################
#############################################################################################################

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


#############################################################################################################
#############################################################################################################

*/


// Header
#include <iostream>
#include <fstream> 	// file open
#include <algorithm> 	// sort
#include <vector> 	// vector
#include <unistd.h>	// for getch implementation
#include <map>		// map


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>



using namespace std;


#define BUF_SIZE 1024
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
    
    vector<pair<string,int>> trie_total(char * search_str, char * filename);
	void search_Trie(const char* key , map<string,int> &searched_map);
	void key_start(const char* key , map<string,int> & searched_map);
	void search_all_sentence( map<string,int> &searched_map);
	void insert(const char* key , int num, string str);

    
		
};



void error_handling(char * message){
	fputs(message , stderr);
	fputc('\n' , stderr);
	exit(1);
}


// SubFunctions

// modify_str
// upper + remove space.
string modify_str(string s1){
	string s2= "";
	for(int i = 0 ; i < s1.size();++i) s2 += toupper(s1[i]);
	s2.erase(remove(s2.begin(),s2.end(),' '),s2.end());
	return s2;
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
vector<pair<string,int>> Trie:: trie_total(char * given_str, char * filename){

    string str_mf;
    
	map<string,int> searched_map;
	vector<pair<string,int>> searched_vec;

    // Trie* searchMachine = new Trie();
	
	string line;
	ifstream openFile(filename);
	
	if(openFile.is_open()){
		cout << " ";
		while(getline(openFile,line)){
			
			// data -> string
			string str_origin = line.substr(0,line.find(','));
			
			// data -> int
			int dataNum = stoi(line.substr(line.rfind(',')+1));

			// string modify : capital + remove space
			str_mf = modify_str(str_origin);	
			
			// insert string(modified) in Trie
 			insert(str_mf.c_str(),dataNum, str_origin);
	
		}
		openFile.close();
	}

	//searchMachine->search_n_print();
	
	// text searching start

	system("clear");
	printf("text : \n");
	printf("-----------------------------------------");
	
	// text searching
	
    // Search and Print result
    
    // Search
    str_mf = modify_str(given_str);
    search_Trie(str_mf.c_str(),searched_map); // Search_Trie

    // sort in descending order for search_num
    for(auto it:searched_map) searched_vec.push_back(make_pair(it.first,it.second));
    sort(searched_vec.begin() , searched_vec.end() , compare);
    
    // Print highest ten results.
    //for(int i = 0 ; i < searched_vec.size() && i < 10 ; ++i) printf("\033[38;2;0;255;255m%s    %d\n",searched_vec[i].first.c_str(),searched_vec[i].second);
    if(searched_vec.size() > 10) searched_vec.resize(10);

    return searched_vec;
    

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

struct searched{
    int num;
    char * searched_str[10];
    int searched_num[10];
    strs(){ num = 0;}
    ~strs(){}
};

int main(int argc, char** argv){
	
    vector<pair<string,int>> searched_vec;
    
    Trie* searchMachine = new Trie();
    struct searched searched_struct;
    

	int serv_sock;
	int clnt_sock;
	int read_cnt;

	char search_str[BUF_SIZE];
	socklen_t clnt_addr_sz;

	serv_sock = socket(PF_INET , SOCK_STREAM , 0);
	if(serv_sock == -1) error_handling("sock() error");
	
	struct sockaddr_in serv_addr , clnt_addr;
	
	memset(&serv_addr , 0 , sizeof(serv_addr));
	serv_addr.sin_family= AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(serv_sock , (struct sockaddr*) &serv_addr , sizeof(serv_addr))) error_handling("bind() error");

	if(listen(serv_sock , 5) == -1) error_handling("listen() error");
	
	
	//while(1){
		clnt_addr_sz = sizeof(clnt_addr);
		clnt_sock = accept(serv_sock , (struct sockaddr*)&clnt_addr ,&clnt_addr_sz);
		read_cnt = read(clnt_sock , search_str , BUF_SIZE - 1);
		
        searched_vec = searchMachine->trie_total(search_str , argv[2]);
        
        for(int i = 0 ; i < searched_strs.size(); ++i){
            //searched_vec[i].first.c_str(),searched_vec[i].second
            strcpy(searched_struct.searched_strs[i],searched_vec[i].first.c_str());
            searched_struct.searched_num[i] = searched_vec[i].second;
            searched_struct.num++;
        }

		write(clnt_sock , &searched_struct , read_cnt);
        
	close(serv_sock);
	close(clnt_sock);	
	

}
