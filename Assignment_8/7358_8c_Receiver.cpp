// Write a program using TCP socket for wired network for arithmetic and trigonometric calculator

#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>

using namespace std;

int main(){
	int clientSocket , serverSocket , receiveMsgSize;
	clientSocket = socket(AF_INET , SOCK_STREAM , 0);
	if(clientSocket < 0){
		cout << "Client Socket Error" << endl;
		return 0;
	}
	
	struct sockaddr_in serverAddr , clientAddr;
	
	serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5200);
    // For peer to peer mode address used for both sender and receiver is 127.0.0.1
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	
	if(connect(clientSocket ,  (struct sockaddr*) & serverAddr , sizeof(serverAddr)) < 0){
		cout << "Connection Error!" << endl;
		return 0;
	}else{
		cout << "Connection Established\n" << endl;
	}

    cout << "\tArithmetic and Trigonometric Calculator" << endl;
// cout<<"\nAvailable Operations:\n"
     //   <<"1 -> Addition\t\t2 -> Subtraction\n"
       // <<"3 -> Multiplication\t4 -> Division\n"
//		<<"5 -> sin\t\t6 -> cos\n"
  //      <<"7 -> tan\t\t8 -> cosec\n"
    //    <<"9 -> sec\t\t10 -> cot\n\n";
char s1[200]={};
 recv(clientSocket ,s1,200,0);
       cout << s1 << endl;
	char ch='y';
	while(ch=='y'){
		int operation;
        double operand1, operand2, angle, result;
        int continue_flag=1;
      
        cout<<"Choose your operation(1-10): ";
        cin>>operation;

        send(clientSocket ,&operation, sizeof(operation),0);
         
        if(operation>=1 && operation <=4){
			cout<<"Enter operand 1: ";
			cin>>operand1;

			cout<<"Enter operand 2: ";
			cin>>operand2;

			send(clientSocket ,&operand1, sizeof(operand1),0);
			send(clientSocket ,&operand2, sizeof(operand2),0);
		}
		if(operation>=5 && operation<=10){
			cout<<"Enter angle(in degrees): ";
        	cin>>angle;

        	send(clientSocket ,&angle, sizeof(angle),0);
		}

        recv(clientSocket ,&result, sizeof(result),0);
        cout<<"\nAnswer Received: "<<result<<endl;
            
        cout<<"\nWant to continue? (y/n): ";
		cin>>ch;

		if (ch!='y'){
			cout << "You chose to quit :)!"<<endl;
            continue_flag = 0;
            send(clientSocket ,&continue_flag, sizeof(continue_flag),0);
			break;
		}

        send(clientSocket ,&continue_flag, sizeof(continue_flag),0);
        cout<<endl;
	}
	close(clientSocket);
	return 0;
}

