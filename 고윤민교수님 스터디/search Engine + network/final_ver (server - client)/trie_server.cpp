/*
#############################################################################################################
#############################################################################################################

	[Linux] + [C++]


	This is Related Search Machine based Trie. ( Server )
	This program receives search terms from client.
	Then, it searches the top 10 search rankings that contain search terms and sends them to the client.

	Input data file has to have (string, number of search).
	Then this project will read data file, and make 'Related Search Machine' using it.

	Version 1			Text should be included in the sentence.

	Example

	Search Text :		Pohang

	Result :			Busan and Pohang	3000
						Pohang sea			2000
						Pohang				1000
						Popohang			 500


#############################################################################################################
#############################################################################################################

*/


// Header for Trie

#include <iostream>
#include <string>
#include <fstream> 		// file open
#include <algorithm> 	// sort
#include <vector> 		// vector
#include <unistd.h>		// for getch implementation
#include <map>			// map

// Header for server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


using namespace std;

// Macro

#define BUF_SIZE 1024	// buffer size definition
#define ALPHA 26 		// Trie for A~Z


/**
 * @brief A structure that will stores information about associated search terms.
 * we will send it to server.
 */
struct searched{
    int num;							//	numbers of associated strings
    char searched_str[10][BUF_SIZE];	//	associated strings
    int searched_num[10];				//	searching numbers

    searched(){ num = 0;}	// Constructor
    ~searched(){}			// Destructor
};


/**
 * @brief Trie structure
 * 
 */

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
    
    vector<pair<string,int>> trie_total(char * given_str, char * filename);
	void search_Trie(const char* key , map<string,int> &searched_map);
	void key_start(const char* key , map<string,int> & searched_map);
	void search_all_sentence( map<string,int> &searched_map);
	void insert(const char* key , int num, string str);

    
		
};


// SubFunctions

/**
 * @brief Converting function
 * Converting to Upper
 * Removing spaces
 * 
 * @param s1 	string before converting
 * @return string	 string after converting
 */
string modify_str(string s1){
	string s2= "";
	for(int i = 0 ; i < s1.size();++i) s2 += toupper(s1[i]);
	s2.erase(remove(s2.begin(),s2.end(),' '),s2.end());
	return s2;
}


/**
 * @brief compare second element of pair
 * 
 * @param a pair 1
 * @param b pair 2
 * @return true 	Searching num of a > Searching num of b
 * @return false 	Searching num of a < Searching num of b
 */
bool compare(const pair<string,int> &a , const pair<string,int> &b)
{
	return a.second > b.second;
}

/**
 * @brief Error Processing Function
 * 
 * @param message Error message to print out
 */
void error_handling(string message){
	cout << message << endl;
	exit(1);
}



// Trie Functions

// 
// It Gets string from keyboard
// It finds Related searched string from Trie.
// Print

/**
 * @brief Total course of trie
 * Reading Data file and Storing Data
 * Making Trie using Data
 * Searching using given search word
 * Returnning vector having associated string and searching num
 * 
 * @param given_str 	Search word
 * @param filename 		Data file name
 * @return vector<pair<string,int>>  vector having associated string and searching num
 */
vector<pair<string,int>> Trie:: trie_total(char * given_str, char * filename){

    string str_mf;
    string given_string(given_str);
	map<string,int> searched_map;
	vector<pair<string,int>> searched_vec;
	
	string line;
	ifstream openFile(filename);
	

	// Reading Data file and Storing Data
	// Making Trie
	cout << "HERE" << endl;
	if(openFile.is_open()){
		
		while(getline(openFile,line)){
			
			// data ( string )
			string str_origin = line.substr(0,line.find(','));
			
			// data ( int )
			int dataNum = stoi(line.substr(line.rfind(',')+1));
			
			// string modify : capital + remove space
			str_mf = modify_str(str_origin);	
			
			// Making Trie
			// insert string(modified) in Trie
			insert(str_mf.c_str(), dataNum, str_origin);
			line = "";
		}
		openFile.close();
	}
	
	system("clear");
	printf("Searching.............\n");

    // Searching Trie

    str_mf = modify_str(given_string);

    search_Trie(str_mf.c_str(),searched_map);

    // sort in descending order for search_num
    for(auto it:searched_map) searched_vec.push_back(make_pair(it.first,it.second));
    
    sort(searched_vec.begin() , searched_vec.end() , compare);
    
    // Only highest ten results
    if(searched_vec.size() > 10) searched_vec.resize(10);
	

	printf("Searching Complement\n");

    return searched_vec;

}



/**
 * @brief All Trie search for containing string 'key'
 * 
 * @param key 	search word
 * @param searched_map	map having searching result
 */
void Trie:: search_Trie(const char* key, map<string,int>& searched_map){
	if(!next || *key=='\0') return;

	int index = *key - 'A';

	for(int i = 0 ; i < ALPHA; ++i){
		if(next[i]){
			if(i==index) next[i]->key_start(key+1,searched_map); 
			next[i]->search_Trie(key , searched_map);
		}
	}
	
}


/**
 * @brief Matcing all part of string using string that corrects first char.
 * 
 */
void Trie:: key_start(const char* key , map<string,int> & searched_map){
	
	if(*key=='\0'){ search_all_sentence(searched_map);
		return;}

	int index = *key - 'A';

	if(!next[index]) return ;

	next[index]->key_start(key+1,searched_map);

}

/**
 * @brief Search all strings containing matched string using mathced string.
 * 
 */
void Trie::search_all_sentence(map<string,int> &searched_map){
	if(finish){
		searched_map.insert({ search_str , search_num });
		if(!next) return;
	}
	
	for(int i = 0 ; i < ALPHA ; ++i){
		if(next[i]) next[i]->search_all_sentence(searched_map);
			
	}

}

/**
 * @brief From datafile , make Trie and insert all data.
 * 
 * @param key Converted string to search
 * @param num searching number
 * @param str origin string
 */
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


/**
 * @brief Main Function
 * Search Engine Server Implementation
 * @param argc 
 * @param argv 
 * argv[1] : Port number
 * argv[2] : Data File
 */
int main(int argc, char** argv){
	
    vector<pair<string,int>> searched_vec;	// vector for containing result

    Trie* searchMachine = new Trie();		// Trie init
    searched searched_struct;				// Struct to send to client
    
	int serv_sock;								// server socket fd
	int clnt_sock;								// client socket fd
	struct sockaddr_in serv_addr , clnt_addr;	// address
	socklen_t clnt_addr_sz;						// client address size

	int read_cnt;				// reading length
	char search_str[BUF_SIZE];	// Buffer
	
	// Socket init
	serv_sock = socket(PF_INET , SOCK_STREAM , 0);
	if(serv_sock == -1) error_handling("sock() error");
	
	// server address setting
	memset(&serv_addr , 0 , sizeof(serv_addr));
	serv_addr.sin_family= AF_INET;
	serv_addr.sin_port = htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// binding server socket
	if(bind(serv_sock , (struct sockaddr*) &serv_addr , sizeof(serv_addr))) 
		error_handling("bind() error");

	// listening server socket
	if(listen(serv_sock , 5) == -1) 
		error_handling("listen() error");
	
	
	// connecting server <-> client
	clnt_addr_sz = sizeof(clnt_addr);
	
	clnt_sock = accept(serv_sock , (struct sockaddr*)&clnt_addr ,&clnt_addr_sz);
	
	// receiving search word
	read_cnt = read(clnt_sock , search_str , BUF_SIZE - 1);	
	search_str[read_cnt] = 0 ;
	
	// Search using Trie
	searched_vec = searchMachine->trie_total(search_str , argv[2]);
     		
	
	// Result copies vector to struct
    for(int i = 0 ; i < searched_vec.size(); ++i){
        strcpy(searched_struct.searched_str[i],searched_vec[i].first.c_str());	// string
		searched_struct.searched_num[i] = searched_vec[i].second;				// searching num
        searched_struct.num++;													// size
	}

	// Sending struct to client
	write(clnt_sock ,(struct searched_struct *)&searched_struct , sizeof(searched_struct));
        
	//close
	close(serv_sock);
	close(clnt_sock);	

}
