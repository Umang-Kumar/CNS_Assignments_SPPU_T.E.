#include<bits/stdc++.h>               //Umang Kumar
#include<sys/socket.h>                //7358
#include<arpa/inet.h>
using namespace std;

const int MAXPENDING = 5 ;

int main() {
   int servSock = socket(PF_INET, SOCK_STREAM, 0) ;
   if (servSock < 0) { cout << "Error with server socket";  return 0;}
   struct sockaddr_in serverAddr ;
   socklen_t serverLen ;
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   serverAddr.sin_port = htons(5103);
   serverLen = sizeof(serverAddr);
   if (bind(servSock, (struct sockaddr*)& serverAddr, sizeof(serverAddr) ) < 0 ) {
      cout << "Error : not able to BIND " << endl  ; return 0 ;
   }
   cout << "Waiting for connection" << endl ;
   if (listen(servSock, MAXPENDING) < 0) {
      cout << "Error : not able to LISTEN " << endl  ; return 0 ;
   }
   int clientSock = accept(servSock, (struct sockaddr*)& serverAddr, (socklen_t *)&serverLen ) ;
   if (clientSock < 0) {
      cout << "Error : not able to ACCEPT " << endl  ; return 0 ;
   }
  
   cout << " ---- Connection Successfull --- \n" ;
   
   while (1) {

        char c;
        // c = 'S';
        cout << "Enter a character :" << endl;
        cin >> c;                                      // taking input 
        bitset<8> a(c);                                // converting the input into 8 bit binary 
        cout << "Binary : ";
        for(int i = 0; i < 8; i++)
            cout << a[i] ;
        cout << endl;

        char msg[12];
        for(int i = 0; i < 12; i++)
            msg[i] = '0';

        for(int i = 0,j = 0; i < 12; i++){              // placing all the data bits 
            if(__builtin_popcount(i + 1) == 1) continue;
            if(a[j]) msg[i] = '1';
            j++;
        }

        for(int i = 0; i < 4; i++){
            int cn = 0;
            for(int j = 0; j < 12; j++){
                if(((j + 1) & ( 1<<i )))
                    cn += (msg[j] == '1');
            }
            cn = cn%2;
            if(cn)
                msg[(1 << i) - 1] = '1';                  //placing the parity bit 
        }
        cout << "Message : ";
        for(int i = 0; i < 12; i++)
            cout << msg[i];
        cout << endl; 

	send(clientSock, msg, strlen(msg) + 1, 0) ;          // sending the coded messege 
    
      // break ;
   }
   return 0 ;

}
