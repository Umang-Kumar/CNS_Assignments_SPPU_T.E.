// Write a program using TCP socket for wired network for saying hello to each other

#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>

using namespace std;

#define MAX 500

int main(){
	int serverSocketHandler = socket(AF_INET , SOCK_STREAM , 0);
	if(serverSocketHandler < 0){	
		cout << "Server Socket Error";
		return 0;
	}
	
	struct sockaddr_in serverAddr , clientAddr;
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5200);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int bindStatus = bind(serverSocketHandler , (struct sockaddr*) & serverAddr , sizeof(serverAddr));
	
	if(bindStatus < 0){
		cout << "BIND Error" << endl;
		return 0;
	}
	
	int listenStatus = listen(serverSocketHandler , 5); 
	
	if(listenStatus < 0){
		cout << "LISTEN Error" << endl;
		return 0;
	}
	
	cout << "Waiting for connection" << endl;
	
	char buff[MAX];
	int clientSocketHandler;
	
	socklen_t len = sizeof(clientAddr);
	int connection;
	if((connection = accept(serverSocketHandler , (struct sockaddr*) & clientAddr , &len)) < 0){
		cout << "ACCEPT Error" << endl;
		return 0;
	}
	else{
		cout << " ---- Connection established sucessfully ---- \n" << endl;
	}
	
	
	while(true){ 
		int rMsgSize;
		
		if((rMsgSize  = recv(connection , buff , MAX , 0)) > 0){
			cout << "\nReceiver : " << buff << endl;
			
			if(buff[0] == 'b' && buff[1] == 'y' && buff[2] == 'e'){
				cout << "Sender : Sayonara" << endl;
				cout << "\nMessage 'bye' received, Connection Ends.\n" << endl;
				send(connection , buff , strlen(buff)+1 , 0);
				break;
			}
			
			cout << "Sender : "; 
			
			char input[MAX];
			string s;
			
			getline(cin , s);
			int n = s.size();
			for(int i = 0 ; i < n ; i++){
				input[i] = s[i];
			}
			
			input[n] = '\0';
			
			send(connection , input , strlen(input)+1 , 0);
		}
	}
	
	close(serverSocketHandler);
	return 0;
	
}
