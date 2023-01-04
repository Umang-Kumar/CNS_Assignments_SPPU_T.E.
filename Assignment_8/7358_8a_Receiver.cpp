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
	int clientSocket , serverSocket , receiveMsgSize;
	
	clientSocket = socket(AF_INET , SOCK_STREAM , 0);
	
	if(clientSocket < 0){
		cout << "Client Socket Error";
		return 0;
	}
	
	struct sockaddr_in serverAddr , clientAddr;
	
	serverAddr.sin_family = AF_INET;
    // For peer to peer mode address used for both sender and receiver is 127.0.0.1
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(5200);
	
	if(connect(clientSocket ,  (struct sockaddr*) & serverAddr , sizeof(serverAddr)) < 0){
		cout << "Connection Error!" << endl;
		return 0;
	}
	else{
		cout << " -> Connection Established" << endl;
	}
	
	while(true){
		string s;
		char input[MAX];
		cout << "Receiver : ";
		getline(cin , s);
		
		int n = s.size();
		for(int i = 0 ; i < n ; i++){
			input[i] = s[i];
		}
		
		input[n] = '\0';
		
		send(clientSocket , input , strlen(input)+1 , 0); 
			
		char receiveMessage[MAX];
		int rMsgSize = recv(clientSocket , receiveMessage , MAX , 0);
		
		if(rMsgSize < 0){
			cout << "Error: Packet Not Received" << endl;
			return 0;
		}
		else if(rMsgSize == 0){
			cout << "Server OFF" << endl;
			return 0;
		}
		
		if(receiveMessage[0] == 'b' && receiveMessage[1] == 'y' && receiveMessage[2] == 'e'){
			cout << "\nMessage 'bye' received, Connection Ends." << "\n\n";
			break;
		}
		
		cout << "Sender : " << receiveMessage << "\n\n";
	}
	
    // For closing the socket connection
	close(clientSocket);
	
	return 0;
}