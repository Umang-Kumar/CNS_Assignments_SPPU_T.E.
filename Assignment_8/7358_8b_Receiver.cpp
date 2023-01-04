// Write a program using TCP socket for wired network for file transfer

#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
#include<fstream>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

#define MAX 2048

int main(){
	int clientId , serverId , receiveMsgSize;
	
	clientId = socket(AF_INET , SOCK_STREAM , 0);
	
	if(clientId < 0){
		cout << "Client Socket Error" << endl;
		return 0;
	}
	
	struct sockaddr_in serverAddr , clientAddr;
	
	serverAddr.sin_family = AF_INET;
    // For peer to peer mode address used for both sender and receiver is 127.0.0.1
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(5200);

	if(connect(clientId ,  (struct sockaddr*) & serverAddr , sizeof(serverAddr)) < 0){
		cout << "Connection Error!" << endl;
		return 0;
	}
	else{
		cout << " -> Connection Established" << endl;
	}
	
	cout << "Enter the name of file to send : "; 
	string s;
	cin >> s;
	
	int n = s.size();
	char input[MAX];
	input[n+1];
	for(int i = 0 ; i < n ; i++){
		input[i] = s[i];
	}
	
	input[n] = '\0';

	send(clientId , input , strlen(input)+1 , 0);
	
	ofstream fout;
	fout.open("7306_output_file.txt");
	
	if(!fout.is_open()){
		cout << "Error: File is not created" << endl;
		return 0;
	}
	
	char receiveMessage[MAX];
	int recmsgsize;
	
	while(true){
		if((recmsgsize = recv(clientId , receiveMessage , MAX , 0)) > 0){
			if(strcmp(receiveMessage , "eofSuccess") == 0 || strcmp(receiveMessage , "eofFail") == 0){
				break;
			}
			fout << receiveMessage << endl;
			send(clientId , input , strlen(input)+1 , 0);
		}
	}
	
	fout.close();
	
	if(strcmp(receiveMessage , "eofSuccess") == 0){
		cout << "Output file saved!" << endl;
		cout << "\nFile sent successfully" << "\n\n";
	}
	else if(strcmp(receiveMessage , "eofFail") == 0){
		cout << "\nError: File not received." << "\n\n";
	}
	
    // For closing the socket connection
	close(clientId);
	return 0;
}
