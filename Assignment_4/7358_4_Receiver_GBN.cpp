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
    cout << " ---- Connection established sucessfully ----\n";

    string message;
    cin >> message;

    int itr = 3, j = 0;

    while (itr--)
    {
        string str = "";
        for (int i = j; i < message.size(); i++)
        {
            char recvbuf[5];
            int inLen;
            cout << "----> frame_recieved\n";
            // For accepting response from receiver
            if ((inLen = recv(recvSock, recvbuf, 2, 0)) < 0)
            {
                cout << "--- Error Recieving !" << endl;
                return 0;
            }
            str += recvbuf[0];
            char inp[5] = {'2', '\0'};
            // Allowing Sender
            send(recvSock, inp, 5, 0);
        }

        cout << "--- Packets recieved : " << str << endl;
        char ack = '1';

        if (ack == '1' && itr > 1)
        {
            // For generating random numbers for inducing error
            srand(time(NULL));
            int erp = rand() % (message.size());
            cout << "--- Error in " << erp << "th packet\n";
            ack = erp + '0';
            char inp[5] = {ack, '\0'};
            // Allowing Sender
            send(recvSock, inp, 5, 0);
            j = erp;
            continue;
        }

        char inp[5] = {'-', '\0'};
        // Allowing Sender
        send(recvSock, inp, 5, 0);
        break;
        cout << "\n";
    }

    cout << "\n\n\n";
    // For closing the socket connection
    shutdown(recvSock, 2);
    return 0;
}