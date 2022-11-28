/*
Implement a simple Bayesian Spam filter and determine if each email in 'test' folder is spam or ham.
- In 'train' folder, two files contain 100 spam and 100 non-spam messages.
- In 'test' folder, two files contain 20 spam and 20 non-spam messages.
- We want to classify 40 emails in 'test' folder based on the emails in 'train' folder.
- Thus, probabilies should be calcualted from emails in 'train' folder.
- Please ignore all special characters(e.g. '~!@#$%^&*()-<>?/ .... )
- Use C or C++. No other programming language (ex. python, Java etc)


[Procedue for decision.]
Per each email from test forder
	calculate r(w1, ...... , wn) and apply a threshold.
	assign label (spam or non-spam) which is a predicted label.


Caclualte accuracy of your prediction.
(the number of correctly classiferd test emails) divided by 40.
- since we have 40 test emails (20 spam and 20 non-spam).


For fun, let's try various 'threshold (T)' for decision.
T = 0.6, 0.7, 0.8, 0.9, 0.95.
This means that we will have 5 accuracies.


* What to submit.
- Your C code. (it should be ready for excution, TA will test it.)
- Report (attached in the notice).
- Zip your report and your code (.c) and submit.



Deadline: 11.30(Wed) 23:00

1)모든 word에 대한 P(word | spam) 과 P (word | nonSpam)을 구한다.
2) 어떤 문장이 들어왔을 때 그 문장에 있는 단어들을 W1,W2, ... 라고 했을 때
r(W1,W2,...) =   P( 모든 W_n | spam ) 들의 곱
		-------------------
	P(모든 W_n | spam)들의 곱 + P(모든 W_n | nonSpam)들의 곱      를 통해 구한다.

알고리즘

1) train에 있는 애들을 하나하나 for문으로 읽는다.
그리고 for문 속에서 전처리 + spam여부 확인 후 spam_map[단어 이름]++; 과 nonspam_map[단어이름]++; 한다.
그리고 P(spam) , P(non spam)도 구한다.


그러면 위의 자료를 통해 P(Word | spam) P (Word| nonSpam)을 구할 수 있다.

2) 

*/




#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

#define SPAM_NUM 100
#define HAM_NUM 100

map<string,int> spam_num;
map<string,int> ham_num;
double r_ham[20];
double r_spam[20];

void training(string filename){
   
    set<string> uniQset;

    string temp, line, buffer;

    ifstream in(filename);

    if(in.is_open()){

        getline(in,line); // first line num,labell,text

        //반복
        while(getline(in,line)){
        
        buffer = "";
        uniQset.clear();
        
        stringstream ss1(line); // second line -> get only subject 
        for(int i = 0 ; i < 3 ; ++i){
            getline(ss1,buffer,',');    // buffer = subject ~
        }
        buffer += "\n";

        while(getline(in,line)){
            if(line[line.size()-2] == '"'){    
                break;
            }

            buffer += line + '\n';
        }

        //preprocessing

        for(int i = 0 ; i < buffer.size() ; ++i){
            if(buffer[i] == '~' || buffer[i]== '!' || buffer[i]== '@' || buffer[i]=='#' 
            || buffer[i] == '$' || buffer[i] == '%' || buffer[i] == '^' || buffer[i] == '&'
            || buffer[i] == '*' || buffer[i] == '(' || buffer[i] == ')' || buffer[i] == '-'
            || buffer[i] == '<' || buffer[i] == '>' || buffer[i] == '.' || buffer[i] == '"'
            || buffer[i] == ':'|| buffer[i] == ',' || buffer[i] == '/' || buffer[i] == '?'
            ) buffer[i] = ' ';   
        }

        stringstream ss2(buffer);   // for converting Sentence to Word

        // strtok
        ss2.str(buffer);
        ss2 >> temp;
        while(ss2 >> temp){
            if(temp.size() == 1) continue;
            uniQset.insert(temp);
        }

        //  중복 제거
        set <string>::iterator it;
        
            if(filename == "csv/train/dataset_ham_train100.csv"){
                for(it = uniQset.begin(); it != uniQset.end(); ++it){
                    ham_num[*it]++;
                }
            }
            else if(filename == "csv/train/dataset_spam_train100.csv"){
                for(it = uniQset.begin(); it != uniQset.end(); ++it){
                    spam_num[*it]++;
                }
            }
        
        }

}
}

void calculate(string filename){

    int r_index = 1;
    set<string> uniQset;

    string temp, line, buffer;

    ifstream in(filename);

    if(in.is_open()){

        getline(in,line); // first line num,labell,text

        //반복
        while(getline(in,line)){
        
        buffer = "";
        uniQset.clear();

        double p = 1;
        double q = 1;
        
        // getline(in,line);   
        
        stringstream ss1(line); // second line -> get only subject 
        for(int i = 0 ; i < 3 ; ++i){
            getline(ss1,buffer,',');    // buffer = subject ~
        }
        buffer += "\n";
        // 쪼개서 숫자 , 다른거 , 다른거로 분리

        // 나머지 줄 들
        while(getline(in,line)){
            if(line[line.size()-2] == '"'){    
                break;
            }

            buffer += line + '\n';
        }

        // cout << buffer << endl;

        //preprocessing

        for(int i = 0 ; i < buffer.size() ; ++i){
            if(buffer[i] == '~' || buffer[i]== '!' || buffer[i]== '@' || buffer[i]=='#' 
            || buffer[i] == '$' || buffer[i] == '%' || buffer[i] == '^' || buffer[i] == '&'
            || buffer[i] == '*' || buffer[i] == '(' || buffer[i] == ')' || buffer[i] == '-'
            || buffer[i] == '<' || buffer[i] == '>' || buffer[i] == '.' || buffer[i] == '"'
            || buffer[i] == ':'|| buffer[i] == ',' || buffer[i] == '/' || buffer[i] == '?'
            ) buffer[i] = ' ';   
        }

        stringstream ss2(buffer);   // for converting Sentence to Word

        // strtok
        ss2.str(buffer);
        ss2 >> temp;
        while(ss2 >> temp){
            if(temp.size() == 1) continue;
            uniQset.insert(temp);
        }

        //  중복 제거
        set <string>::iterator it;
        
        for(it = uniQset.begin() ; it !=uniQset.end(); ++it){

            if(spam_num.find(*it) == spam_num.end() || ham_num.find(*it) == ham_num.end()) continue;
            p = (p * spam_num.find(*it)->second / 100 );
            q = (q * ham_num.find(*it)->second / 100);
            // p /=100;
            // q /=100;
            // cout << spam_num.find(*it)->second << ' ';
            // cout << ham_num.find(*it)->second << endl;

            // cout << p << q << endl;
        }
//             if (m.find("Alice") != m.end()) {
// 	cout << "find" << endl;
// }
// else {
// 	cout << "not find" << endl;
// }
        // cout << p <<"   " << q;
    if(filename == "csv/test/dataset_spam_test20.csv") r_spam[r_index++] = p / (p + q);
    else if(filename == "csv/test/dataset_ham_test20.csv") r_ham[r_index++] = p / (p + q);
    // cout << r << endl;
    }
    
}
    
    
}


int main(int argc , char** argv){
    float s_num;
    float accuracy;


    float threshold[5] = { 0.6 , 0.7 , 0.8 , 0.9 , 0.95};
    training("csv/train/dataset_spam_train100.csv");
    training("csv/train/dataset_ham_train100.csv");

    for(auto s : spam_num) cout << s.first << "  " << s.second << endl;
    cout << endl;
    cout << endl;
    for(auto s : ham_num) cout << s.first << "  " << s.second << endl;

    calculate("csv/test/dataset_spam_test20.csv");  
    calculate("csv/test/dataset_ham_test20.csv");   

    for(int i = 0 ; i < 5 ; ++i){
        s_num = 0;
        cout << "Bayesian Spam filter [ Threshold : "<< threshold[i] << " ]" << endl;
        cout << "-------------------Spam--------------------" << endl;
                
        for(int j = 0 ; j < 20 ; ++j){
            cout << j+1 <<"-th spam percent : " << r_spam[j];
            if(r_spam[j] >= threshold[i]){
                s_num++;
                cout << " [ SPAM ]" << endl;
            } 
            else cout << "[ HAM ]" << endl;
        }

        accuracy = s_num / 20;
        cout << "SPAM ACCURACY IS " << accuracy << endl;

        cout << "--------------------Ham---------------------" << endl;
        
        s_num = 0;
        for(int j = 0 ; j < 20 ; ++j){
            cout << j+1 <<"-th spam percent : " << r_ham[j] ;
            if(r_ham[j] >= threshold[i]){
                cout << " [ SPAM ]" << endl;
            } 
            else {
                s_num++;
                cout << "[ HAM ]" << endl;
            }
        }

        accuracy = s_num / 20;
        cout << "HAM ACCURACY IS " << accuracy << endl;

        cout << "----------------------------------------------"<< endl;
    }
}