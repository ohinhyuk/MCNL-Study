#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <termios.h>

using namespace std;

#define ALPHA 26

struct Trie{
	bool finish;
	string search_str;
	int search_num;
	Trie* next[ALPHA];
	
	Trie(){
		finish = false;
		search_str = "";
		for(int i = 0 ; i < ALPHA ; ++i) next[i] = NULL;
		search_num = 0;
	}
	Trie(string s){
		finish = false;
		search_str = s;
		for(int i = 0 ; i < ALPHA; ++i) next[i] = NULL;
		search_num = 0;
	}
	~Trie(){};
	
	void insert(const char* key , int num);
	Trie** input_pos(const char* key , vector<pair<string,int>> &search_pair);
	void search_words(Trie** start, vector<pair<string,int>> &search_pair);
	void print(vector<string> &v1 , vector<string> &v2);

};

string toupper_str(string s1){
	string s2= "";
	for(int i = 0 ; i < s1.size();++i) s2 += toupper(s1[i]);
	s2.erase(remove(s2.begin(),s2.end(),' '),s2.end());
	return s2;
}

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

bool compare(const pair<string,int> &a , const pair<string,int> &b)
{
	return a.second > b.second;
}

void Trie:: print( vector<string> & v1 , vector<string>&v2){
	vector<pair<string,int>> search_pair;
	string s="";
	int a_before;
	char a;
	system("clear");
	printf("text : \n");
	printf("------------------");

	for(;;){
		if(a_before = getch()){
			if(a_before == 127){
				system("clear");
				if(s!="") s.pop_back();
				printf("\033[38;2;255;255;0mtext : %s\n", s.c_str());
				printf("\033[0m-------------------\n");
			}
			else{
				a = a_before;
				system("clear");
				//fflush(stdout);
				s+=a;
				printf("\033[38;2;255;255;0mtext : %s\n",s.c_str());
				printf("\033[0m-------------------\n");
			}
		string s_search = toupper_str(s);
		search_words(input_pos(s_search.c_str(),search_pair), search_pair);
	
	 sort(search_pair.begin() , search_pair.end() , compare);
	
	for(int i = 0 ; i < search_pair.size(); ++i){ 
		for(int j = 0 ; j < v1.size(); ++j){
			if(v1[j]==search_pair[i].first){ printf("\033[38;2;0;255;255m%s %d\n",v2[j].c_str(), search_pair[i].second);break;}
		}
	}
	search_pair.clear();
		}
	}

}



void Trie::insert(const char* key, int num){
	if(*key=='\0'){
		finish = true;
		search_num = num;
		return;
	}

	int index = *key - 'A';
	
	if(!next[index]){
		string s = search_str + *key;
		next[index] = new Trie(s);
	}
	next[index]->insert(key+1,num);

}

Trie** Trie::input_pos(const char* key, vector<pair<string,int>> & search_pair){
	
	if(*key == '\0') return next;
	
	int index = *key - 'A';

	if(!next[index]) return nullptr;
	
	if(*(key+1) =='\0' && next[index]->finish != false){ search_pair.push_back(make_pair(next[index]->search_str,next[index]->search_num));}

	return next[index]->input_pos(key+1,search_pair);
}

void Trie::search_words(Trie** start, vector<pair<string,int>> &search_pair){
	if(!start) return;
	
	for(int i = 0 ; i < ALPHA ; ++i){
		if(start[i]){
			if(start[i]->finish){
				search_pair.push_back(make_pair(start[i]->search_str , start[i]->search_num));
					
			}
			search_words(start[i]->next , search_pair);
		}
		
	}

}


int main(int argc , char** argv){
	string line;
	vector<pair<string,int>> search_pair;
	
	vector<string> origin_str;
	vector<string> upper_str;
	Trie test;

	ifstream openFile(argv[1]);
	
	if(openFile.is_open()){
		string line;
		while(getline(openFile,line)){
			cout << line << endl;
			
			string search_str = line.substr(0,line.find("\t"));
			// str
			origin_str.push_back(search_str);

			// toupper str
			search_str = toupper_str(search_str);
			upper_str.push_back(search_str);

			int search_num = stoi(line.substr(line.rfind("\t")+1));
					
 			test.insert(search_str.c_str(),search_num);
	
		}
		openFile.close();
	}
	
	search_pair.clear();

	test.print(upper_str,origin_str);
	return 0;
	
}
