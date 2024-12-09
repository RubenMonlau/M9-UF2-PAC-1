#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *response = "Hola des del servidor Jesus, soc el Rubén!";

    // Crear sòcol
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error al crear el sòcol");
        return 1;
    }

    // Configurar l'adreça
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Enllaçar el sòcol a l'adreça i port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Error al fer bind");
        close(server_fd);
        return 1;
    }

    // Escoltar connexions
    if (listen(server_fd, 3) < 0) {
        perror("Error al fer listen");
        close(server_fd);
        return 1;
    }

    std::cout << "-- Esperant connexions..." << std::endl;

    // Acceptar connexió entrant
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("Error al fer accept");
        close(server_fd);
        return 1;
    }

    // Llegir missatge del client
    read(new_socket, buffer, 1024);
    std::cout << "-- Missatge rebut del client: " << buffer << std::endl;

    // Enviar resposta al client
    send(new_socket, response, strlen(response), 0);
    std::cout << "-- Resposta enviada al client: " << response << std::endl;

    // Tancar connexió
    close(new_socket);
    close(server_fd);
    return 0;
}