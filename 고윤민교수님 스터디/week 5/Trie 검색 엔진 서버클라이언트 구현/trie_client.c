/**
 * @file trie_client.c
 * @author OhInhyuk (8156217@naver.com)
 * @brief This is client of Trie search engine.
 * This code sends a search term to the server.
 * And it takes associated search terms from the server and prints them out.
 * 
 * @version 0.1
 * @date 2022-07-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */


// Header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

// Macro
#define BUF_SIZE 1024 	// buffer size macro
#define C_GREN "\033[0;32m"
#define C_ORGE "\033[0;34m"


/**
 * @brief A structure that stores information about associated search terms to be received from a server.
 * 
 */
struct searched{
	int num;							// Number of associated string
	char searched_str[10][BUF_SIZE];	// associated string
	int searched_num[10];				// searching numbers
};



/**
 * @brief Error Processing function
 * 
 * @param message Error masseage to print out (Terminal)
 */
void error_handling(char * message){
	fputs(message , stderr);
	fputc('\n' , stderr);
	exit(1);
}



/**
 * @brief main function
 * 
 * @param argc 
 * @param argv 
 * argv[1] : Port number
 * argv[2] : Server IP
 */

int main(int argc, char** argv){
	
	int serv_sock;		// server socket fd
	int clnt_sock;		// client socket fd

	struct sockaddr_in serv_addr;					// sockaddr_in

	struct searched searched_struct;				// Structure to store information from server
	char search_word[BUF_SIZE];						// search_word

	// client socket creation
	clnt_sock = socket(PF_INET , SOCK_STREAM , 0 );
	if(clnt_sock == -1)
		error_handling("sock() error");
	
	// server address setting
	memset(&serv_addr , 0 , sizeof(serv_addr));		
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	// connecting client <-> server
	if(connect(clnt_sock , (struct sockaddr*)&serv_addr , sizeof(serv_addr)) == -1) 
		error_handling("connect() error");
	
	// Print
	printf("%s Search Word: ", C_GREN);					
	fgets(search_word , BUF_SIZE , stdin);					// Search word (Input)
	fputs("------------------------------\n",stdout);

	// Insert NULL
	search_word[strlen(search_word)-1] = 0;

	// sending to server
	write(clnt_sock , search_word , strlen(search_word));

	// receive searched struct from server	
	read(clnt_sock ,(struct searched_struct*) &searched_struct , sizeof(searched_struct));

	// Print
	for(int i = 0 ; i < searched_struct.num; ++i){
		printf("%s %s %d\n", C_ORGE ,searched_struct.searched_str[i],searched_struct.searched_num[i]);
	}

	// close
	close(clnt_sock);
}

