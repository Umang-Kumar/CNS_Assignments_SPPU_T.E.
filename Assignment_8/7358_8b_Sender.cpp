// Write a program using TCP socket for wired network for file transfer

#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<iostream>
#include<fstream>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>

using namespace std;

#define MAX 2048

void shutdownserver(int connection , int flag){

	if(flag){	
		string s = "eofSuccess";
		int n = s.size();
		char buff[MAX];
		
		for(int i = 0 ; i < n ; i++)    
			buff[i] = s[i];
			
		buff[n] = '\0';
		
		send(connection , buff , strlen(buff)+1 , 0);
		cout << "\nFile sent successfully" << "\n\n";
	}
	else{
		string s = "eofFail";
		int n = s.size();
		char buff[MAX];
		
		for(int i = 0 ; i < n ; i++)
			buff[i] = s[i];
			
		buff[n] = '\0';
		
		send(connection , buff , strlen(buff)+1 , 0);
		cout << "Error: File not found" << "\n\n";
	}
	
}

int main(){
	int serverId = socket(AF_INET , SOCK_STREAM , 0);
	if(serverId < 0){
		cout << "Server Socket Error" << endl;
		return 0;
	}	
	
	struct sockaddr_in serverAddr , clientAddr;
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5200);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int bindStatus = bind(serverId , (struct sockaddr*) & serverAddr , sizeof(serverAddr));
	
	if(bindStatus < 0){
		cout << "BIND Error" << endl;
		return 0;
	}
	
	int listenStatus = listen(serverId , 5); 
	
	if(listenStatus < 0){
		cout << "LISTEN Error" << endl;
		return 0;
	}
	
	cout << "Waiting for connection"<<endl;
	
	socklen_t len = sizeof(clientAddr);
	int connection;
	if((connection = accept(serverId , (struct sockaddr*) & clientAddr , &len)) < 0){
		cout << "ACCEPT Error" << endl;
		return 0;
	}
	else{
		cout << " ---- Connection established sucessfully ---- \n" << endl;
	}
	
	int recmsgsize;
	char file_name[100];
	while(true){
		if((recmsgsize  = recv(connection , file_name , 100 , 0)) > 0){
			cout << "Name of file to send : " << file_name << endl;
			break;
		}
	}
	
	ifstream in;
	in.open(file_name);
	
	if(!in.is_open()){
		cout << "FILE OPEN Error" << endl;
		shutdownserver(connection , 0);
		close(serverId);
		return 0;
	}
	
	while(!in.eof()){
		string s;
		char buff[MAX];
		getline(in , s);

		int n = s.size();
		for(int i = 0 ; i < n ; i++){
			buff[i] = s[i];
        }
		buff[n] = '\0';

		send(connection , buff , strlen(buff)+1 , 0);
		recmsgsize  = recv(connection , file_name , 100 , 0); 
		
	}
	
	in.close();
	shutdownserver(connection , 1);
	close(serverId);
	return 0;
}