#include <bits/stdc++.h>
#include <sys/socket.h>
#include <arpa/inet.h>

using namespace std;

const int MAXPENDING = 5;

int main()
{
    int sendSock = socket(PF_INET, SOCK_STREAM, 0);
    if (sendSock < 0)
    {
        cout << "Server Socket Error";
        return 0;
    }
    struct sockaddr_in serverAddr;
    socklen_t serverLen;
    serverAddr.sin_family = AF_INET;
    // For peer to peer mode address used for both sender and receiver is 127.0.0.1
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(5105);
    serverLen = sizeof(serverAddr);
    if (bind(sendSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cout << "BIND Error" << endl;
        return 0;
    }
    cout << "Waiting for connection" << endl;
    if (listen(sendSock, MAXPENDING) < 0)
    {
        cout << "LISTEN Error" << endl;
        return 0;
    }
    int recvSock = accept(sendSock, (struct sockaddr *)&serverAddr, (socklen_t *)&serverLen);
    if (recvSock < 0)
    {
        cout << "ACCEPT Error" << endl;
        return 0;
    }
    cout << " ---- Connection established sucessfully ---- \n";

    // Message for receiving and sending
    string message;
    cin >> message;

    int itr = 5, j = 0;

    while (itr--)
    {
        for (int i = j; i < message.size(); i++)
        {
            char inp[5] = {message[i], '\0'};
            send(recvSock, inp, 2, 0);
            // For sending message to receiver
            cout << "----> frame_sent " << i << "\n";
            char recvbuf[5];
            int inLen;
            // For accepting response from receiver
            if ((inLen = recv(recvSock, recvbuf, 5, 0)) < 0)
            {
                cout << "--- Error Receiving !" << endl;
                return 0;
            }
            // For displaying message
            if (recvbuf[0] != '2')
            {
                cout << "--- Error ---\n";
                shutdown(sendSock, 2);
                break;
            }
        }
        char recvbuf[5];
        // For accepting response from receiver
        int inLen;
        if ((inLen = recv(recvSock, recvbuf, 5, 0)) < 0)
        {
            cout << "--- Error Recieving !" << endl;
            return 0;
        }
        // For displaying message
        if (recvbuf[0] != '-')
        {
            cout << "--- Resending packets from " << recvbuf[0] << "---\n";
            j = recvbuf[0] - '0';
            continue;
        }
        else
        {
            cout << " ---- Packets received successfully ----";
            break;
        }
        cout << "\n";
    }
    cout << "\n\n\n";
    // For closing the socket connection
    shutdown(sendSock, 2);
    return 0;
}