#include<bits/stdc++.h>       //Umang Kumar
#include<sys/socket.h>        // 7358
#include<arpa/inet.h>
using namespace std;

int main() {
   int clientSock, servSock, recvMsgSize;
   clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP) ; //(Domain, Type, Protocol)
   if (clientSock < 0) { cout << "Error with client socket";  return 0; }
   struct sockaddr_in serverAddr ;
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   serverAddr.sin_port = htons(5103);
   if (connect(clientSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr) ) < 0) {
      cout << "Error : not able to connect" << endl  ; return 0 ;
   }
   cout << " ---- Connection Successfull --- \n" ;
   

   while (1) {
     
      char msg[1000];
      int inLen;
      if ( (inLen = recv(clientSock, msg, 1024, 0)) < 0) { //(socket, buffer, length, flag)
         cout << "Error Recieving !" << endl ; return 0;
      }
      cout << "Sender :" << msg << endl ;             // printing the recived message
      int choice = 0;
      cout << "Enter your option :" << endl;
      cout << "1. Without error" << endl;
      cout << "2. With error" << endl;
      cin >> choice;                                  
      inLen--;
      if(choice == 2 && inLen){
          int r = rand()%inLen;                       // getting a random position
          cout << "Adding error at : " << r + 1 << endl;
          msg[r] = msg[r]^'0'^'1';                    // adding error at random postion 
      }
      else if(choice != 1)
        break;  
      
      cout << "Final message :" << msg << endl ;
      
      int ck = 0;
      

      for(int i = 0; i < 4; i++){
            int cn = 0;
            for(int j = 0; j < 12; j++){
                if(((j + 1) & ( 1<<i )))
                    cn += (msg[j] == '1');
            }
            cn = cn%2;                              // checking the parity 
            if(cn)
                ck = ck|(1 << i);                   // if pairty is odd then there is error
        }
      if(ck){
          cout << "Error found at : " <<ck << endl;
          msg[ck - 1] = msg[ck - 1]^'0'^'1';          // removing the error
      }
      string s(8,'0');
      char ans = 0;
      for(int i = 0,j = 0; i < 12; i++){
         if(__builtin_popcount(i+1) == 1) continue;
         s[j] = msg[i];
         if(s[j] == '1')
            ans+=(1 << j);                             // removing the parity bits to find original message
         j++;
      }
      cout <<"Binary :" << s << endl;
      cout <<"Original message :" <<  ans << endl;
      cout << endl;
      
      // break ;
   }
  
   return 0 ;

}
