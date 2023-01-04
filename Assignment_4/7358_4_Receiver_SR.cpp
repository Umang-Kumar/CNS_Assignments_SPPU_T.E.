#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

const int MAXPENDING = 5;

int main()
{
    int recvSock, sendSock, recvMsgSize;
    recvSock = socket(PF_INET, SOCK_STREAM, 0);
    if (recvSock < 0)
    {
        cout << "Client Socket Error";
        return 0;
    }
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    // For peer to peer mode address used for both sender and receiver is 127.0.0.1
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(5105);
    if (connect(recvSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cout << "Error : not able to connect" << endl;
        return 0;
    }
    cout << " -> Connection Established\n";

    // Message for receiving and sending
    string message;
    cin >> message;

    int itr = 5;

    while (itr--)
    {
        string str = "";
        for (int i = 0; i < message.size(); i++)
        {
            char recvbuf[2];
            int inLen;
            cout << "----> Frame Received\n";
            // For accepting response from receiver
            if ((inLen = recv(recvSock, recvbuf, 2, 0)) < 0)
            {
                cout << "--- Error Received ! ---" << endl;
                return 0;
            }
            str += recvbuf[0];
            char inp[2] = {'2', '\0'};
            // Allowing Sender
            send(recvSock, inp, 2, 0);
        }
        cout << " -> All Packets Received : " << str << endl;
        char ack = '1';
        if (ack == '1')
        {
            // For generating random numbers for inducing error
            srand(time(NULL));
            int erp = rand() % (message.size());
            cout << "--- Error in " << erp << "th packet\n";
            char inp[2] = {char(erp + '0'), '\0'};
            // Allowing Sender
            send(recvSock, inp, 2, 0);
            char recvbuf[2];
            int inLen;
            cout << "----> Frame Received\n";
            // For accepting response from receiver
            if ((inLen = recv(recvSock, recvbuf, 2, 0)) < 0)
            {
                cout << "--- Error Receiving !" << endl;
                return 0;
            }
            cout << " -> All Packets Received : " << recvbuf[0] << endl;
        }
        else
        {
            char inp[2] = {'-', '\0'};
            // Allowing Sender
            send(recvSock, inp, 2, 0);
        }
        cout << "\n";
        break;
    }
    cout << "\n";
    // For closing the socket connection
    shutdown(recvSock, 2);
    return 0;
}