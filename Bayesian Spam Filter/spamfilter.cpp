/*
    This Program is a simple Bayesian Spam filter.
    In 'train' folder, two files contain 100 spam and 100 non-spam messages.
    In 'test' folder, two files contain 20 spam and 20 non-spam messages.
    This program classifies 40 emails in 'test' folder based on model trained by the emails in 'train' folder.
    Then it determines if each email in 'test' folder is spam or ham.

    Calculate accuracy of all test data. 
    - We have 40 test emails (20 spam and 20 non-spam).
    - (the number of correctly classiferd test emails) divided by 40.
    
    For fun, threshold (T) has various value.
    - T = 0.6, 0.7, 0.8, 0.9, 0.95.
    - This means that we will have 5 accuracies.

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

#define TRAIN_NUM 100
#define TEST_NUM 20

map<string,int> spam_num;   // pair < word , num > of all word in spam train100
map<string,int> ham_num;    // pair < word , num > of all word in ham train100
double r_ham[20];           // Bayesian result ( percent ) of all mail in ham test20
double r_spam[20];          // Bayesian result ( percent ) of all mail in spam test20

// Training Function
// Using training set -> Get map<string , int> spam_num , map<string,int> ham_num
// File open -> Train Dataset preprocessing -> getting frequency of word ( num )

void training(string filename){

    set<string> uniQset; // for preprocessing (unique)
    string temp, line, buffer;
    
    ifstream in(filename);

    if(in.is_open()){

        getline(in,line); // first line "num,label,text"

        // All Content read
        while(getline(in,line)){
        
        //init
        buffer = "";
        uniQset.clear();
        
        stringstream ss1(line); // second line
        for(int i = 0 ; i < 3 ; ++i){
            getline(ss1,buffer,',');    // num , label X  Subject O
        }
        buffer += "\n";

        // One mail read
        while(getline(in,line)){
            
            buffer += line + '\n';
            if( (line.size() <= 2 && line[line.size()-2] == '"' ) || (line.size() > 2 && line[line.size()-2]=='"' && (line[line.size()-3] !='"' && line[line.size()-1] !='"') )){ 
                break;
            }

        }

        //preprocessing
        for(int i = 0 ; i < buffer.size() ; ++i){
            if(!isalpha(buffer[i]) && !isnumber(buffer[i]) ) buffer[i] = ' ';
        }

        stringstream ss2(buffer);   // for converting Sentence to Word

        // strtok + unique using set
        ss2.str(buffer);
        ss2 >> temp;
        while(ss2 >> temp){
            if(temp.size() == 1) continue;
            uniQset.insert(temp);
        }

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
    set<string> uniQset;    // for preprocessing (unique)

    string temp, line, buffer;

    ifstream in(filename);

    if(in.is_open()){

        getline(in,line);           // first line "num,label,text"

        // All Content read
        while(getline(in,line)){
        
        //init
        buffer = "";
        uniQset.clear();

        double p = 1;
        double q = 1;
        
        
        stringstream ss1(line);         // second line
        for(int i = 0 ; i < 3 ; ++i){
            getline(ss1,buffer,',');    // num , label X  Subject O
        }
        buffer += "\n";
        

        // One mail read
        while(getline(in,line)){

            buffer += line + '\n';
            if( (line.size() <= 2 && line[line.size()-2] == '"' ) || (line.size() > 2 && line[line.size()-2]=='"' && (line[line.size()-3] !='"' && line[line.size()-1] !='"') )){ 
                break;
            }
            
        }


        //preprocessing
        for(int i = 0 ; i < buffer.size() ; ++i){
            if(!isalpha(buffer[i]) && !isnumber(buffer[i]) ) buffer[i] = ' ';
        }

        stringstream ss2(buffer);   // for converting Sentence to Word

        // strtok + unique using set
        ss2.str(buffer);
        ss2 >> temp;
        while(ss2 >> temp){
            if(temp.size() == 1) continue;
            uniQset.insert(temp);         
        }

        set <string>::iterator it;
        
        // Calculate p , q

        for(it = uniQset.begin() ; it !=uniQset.end(); ++it){
            
            if(spam_num.find(*it) == spam_num.end() || ham_num.find(*it) == ham_num.end()) continue;
            p = (p * spam_num.find(*it)->second / TRAIN_NUM );
            q = (q * ham_num.find(*it)->second / TRAIN_NUM);
        }
        
        // Calculate r

        if(filename == "csv/test/dataset_spam_test20.csv") r_spam[r_index++] = p / (p + q);
        else if(filename == "csv/test/dataset_ham_test20.csv") r_ham[r_index++] = p / (p + q);
    
    }
    
}
    
    
}

int main(int argc , char** argv){
    
    float s_num;
    float accuracy;
    float threshold[5] = { 0.6 , 0.7 , 0.8 , 0.9 , 0.95};

    training("csv/train/dataset_spam_train100.csv");
    training("csv/train/dataset_ham_train100.csv");

    calculate("csv/test/dataset_spam_test20.csv");  
    calculate("csv/test/dataset_ham_test20.csv");   

    for(int i = 0 ; i < 5 ; ++i){
        s_num = 0;
        cout << '\n';
        cout << "-------------------------------------------"<< endl;
        cout << "Bayesian Spam filter [ Threshold : " << threshold[i] << " ]" << endl;
        cout << "-------------------------------------------" << endl;
        cout << '\n';
        cout << "< SPAM TEST >" << endl;
        cout << '\n';

        for(int j = 0 ; j < TEST_NUM ; ++j){
            cout << right << setw(2) << j+1 <<"-th spam percent : " << left << setw(12) << r_spam[j];
            if(r_spam[j] >= threshold[i]){
                s_num++;
                cout << " [ SPAM ]" << endl;
            } 
            else cout << " [ HAM  ]" << endl;
        }
        cout << '\n';
        cout << "< HAM TEST >" << endl;
        cout << '\n';
        
        for(int j = 0 ; j < TEST_NUM ; ++j){
            cout << right << setw(2) << j+1 <<"-th spam percent : " << left << setw(12)<< r_ham[j] ;
            if(r_ham[j] >= threshold[i]){
                cout << " [ SPAM ]" << endl;
            } 
            else {
                s_num++;
                cout << " [ HAM  ]" << endl;
                
            }
        }

        accuracy = s_num / (TEST_NUM + TEST_NUM);
        
        cout << '\n';
        cout << "-------------------------------------------"<< endl;
        cout << "ACCURACY : " << accuracy << endl;
        cout << "-------------------------------------------"<< endl;

    }
}