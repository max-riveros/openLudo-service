//
// Created by max on 4/16/26.
//

module;

#include <print>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

export module UI.Network;

import UI;

export class NetworkUI /*: UI*/ {
private:
    static constexpr int MAX_CLIENTS = 4;
    static constexpr int INPUT_BUFFER_SIZE = 1024;
    int serverSocket = -1;
    int clientSockets[MAX_CLIENTS] = {};
    bool listening = false;

    static void bindTo(const int serverSocket, const in_addr_t ip, const in_port_t port) {
        sockaddr_in bindingAddress{};
        bindingAddress.sin_family = AF_INET;
        bindingAddress.sin_port = htons(port);
        bindingAddress.sin_addr.s_addr = ip;
        bind(serverSocket, reinterpret_cast<sockaddr *>(&bindingAddress), sizeof(bindingAddress));
        std::println("Binding to address {}:{} at socket {}!", std::to_string(ip), port, serverSocket);
    }

    void handleMessage(int clientSocket, const char buffer[INPUT_BUFFER_SIZE]) {
        std::println("Received \"{}\" from {}!", buffer, clientSocket);
        listening = false;
    }

    void listenClients() {
        std::println("Listening...");
        while (listening) {
            char buffer[1024] = {};
            recv(clientSockets[0], buffer, sizeof(buffer), 0);
            handleMessage(clientSockets[0], buffer);
        }
        std::println("Stopped listening.");
    }
public:
    static constexpr in_port_t DEFAULT_PORT = 1221;

    explicit NetworkUI() : NetworkUI(INADDR_ANY, DEFAULT_PORT) {}
    explicit NetworkUI(const in_addr_t ip, const in_port_t port) {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        bindTo(serverSocket, ip, port);
    }

    ~NetworkUI() /*override*/ {
        std::println("Closing server...");
        close(serverSocket);
    }

    void start() /*override*/ {
        std::println("Starting server...");
        listen(serverSocket, MAX_CLIENTS);

        sockaddr_in clientAddress{};
        socklen_t clientAddressLength = sizeof(clientAddress);
        clientSockets[0] = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddress), &clientAddressLength);

        if (clientSockets[0] < 0) {
            std::perror("Accept failed");
            throw std::runtime_error("Failed to start the server");
        }
        std::println("Client {}:{} connected!", std::to_string(clientAddress.sin_addr.s_addr), clientAddress.sin_port);

        listening = true;
        listenClients();
    }
};
