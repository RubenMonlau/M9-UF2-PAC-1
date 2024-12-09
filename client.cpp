#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char *message = "Hola des del client Jesus, soc el Rubén!";
    char buffer[1024] = {0};

    // Crear sòcol
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error al crear el sòcol");
        return 1;
    }

    // Configurar l'adreça del servidor
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convertir l'adreça localhost
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Adreça invàlida o no suportada");
        return 1;
    }

    // Connectar al servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error al connectar amb el servidor");
        return 1;
    }

    std::cout << "-- Connexió establerta amb el servidor." << std::endl;

    // Enviar missatge al servidor
    send(sock, message, strlen(message), 0);
    std::cout << "-- Enviant missatge: " << message << std::endl;

    // Llegir resposta del servidor
    read(sock, buffer, 1024);
    std::cout << "-- Resposta del servidor: " << buffer << std::endl;

    // Tancar el sòcol
    close(sock);
    return 0;
}