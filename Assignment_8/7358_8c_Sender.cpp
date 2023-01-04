// Write a program using TCP socket for wired network for arithmetic and trigonometric calculator

#include<bits/stdc++.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>

using namespace std;

int main(){
	int serverSocketHandler = socket(AF_INET , SOCK_STREAM , 0);
	if(serverSocketHandler < 0){	
		cout << "Server Socket Error";
		return 0;
	}
	
	struct sockaddr_in serverAddr , clientAddr;
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5200);
    // For peer to peer mode address used for both sender and receiver is 127.0.0.1
	serverAddr.sin_addr.s_addr =  inet_addr("127.0.0.1");
	
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
	
	char buff[500];
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

    cout << "\tArithmetic and Trigonometric Calculator" << endl;
	char s1[200]="1) Add\n2) Subtract\n3)multiply\n4)div\n5)sin\n6)cos\n7)tan\n8)cosec\n9)sec\n10)cot\n\n";
	send(connection,s1,200,0) ;
	cout << s1 << endl;
         
    while(true){
	    int operation;
        double operand1, operand2, angle, factor, result;
		factor = 3.141592 / 180;
        int continue_flag=1;
	    
	    recv(connection, &operation,(sizeof(operation)),0);
	    
	    cout<<"Operation Chosen: "<<operation<<endl;

		if(operation>=1 && operation <=4){
			recv(connection, &operand1, sizeof(operand1),0);
        	recv(connection, &operand2, sizeof(operand2),0);

			cout<<"Operand 1 Entered: "<<operand1<<endl;
        	cout<<"Operand 2 Entered: "<<operand2<<endl;
		}
	    
	    if(operation>=5 && operation <=10){
			recv(connection, &angle, sizeof(angle),0);

        	cout<<"Angle Entered: "<<angle<<endl;
		}
        	    
	    switch(operation) {
		    case 1: result=operand1+operand2;
		            cout<<"Answer sent to user: "<<result<<endl;
		            break;
		    case 2: result=operand1-operand2;
		            cout<<"Answer sent to user: "<<result<<endl;
		            break;
		    case 3: result=operand1*operand2;
		            cout<<"Answer sent to user: "<<result<<endl;
		            break;
            case 4: result=operand1/operand2;
                    cout<<"Answer sent to user: "<<result<<endl;
                    break;
			case 5: result=sin(angle*factor);
		            cout<<"Answer sent to user: "<<result<<endl;
		            break;
		    case 6: result=cos(angle*factor);
		            cout<<"Answer sent to user: "<<result<<endl;
		            break;
		    case 7: result=tan(angle*factor);
		            cout<<"Answer sent to user: "<<result<<endl;
		            break;
            case 8: result=(1/sin(angle*factor));
                    cout<<"Answer sent to user: "<<result<<endl;
                    break;
            case 9: result=(1/cos(angle*factor));
                    cout<<"Answer sent to user: "<<result<<endl;
                    break;
            case 10:result=(1/tan(angle*factor));
                    cout<<"Answer sent to user: "<<result<<endl;
                    break;
		    default: 
		            cout<<"\nChoose a number between 1 to 10\n";
	    }
    	
        send(connection,&result,sizeof(result),0);
        recv(connection, &continue_flag,(sizeof(continue_flag)),0);

        if(!continue_flag){
            cout<<"\nUser chose to exit."<<endl;
            break;
        }

        cout<<"\nUser chose to continue.\n"<<endl;
    }
	close(serverSocketHandler);
	return 0;
}
