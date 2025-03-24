#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    FILE *html_data;
    html_data = fopen("index.html", "r");

    if (html_data == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read HTML content from file
    fseek(html_data, 0, SEEK_END);
    long file_size = ftell(html_data);
    fseek(html_data, 0, SEEK_SET);
    char *response_data = malloc(file_size + 1);
    fread(response_data, 1, file_size, html_data);
    fclose(html_data);
    response_data[file_size] = '\0';

    // Construct HTTP header
    char http_header[2048];
    sprintf(http_header, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\nContent-Type: text/html\r\n\r\n", file_size);

    // Concatenate header and content
    strcat(http_header, response_data);

    // Create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0) {
        perror("Error creating socket");
        return 1;
    }

    // Define the address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = inet_addr("192.168.2.107");

    if (bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        return 1;
    }

    if (listen(server_socket, 5) < 0) {
        perror("Error listening");
        return 1;
    }
    
    int client_socket;
    while (1) {
        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("Error accepting connection");
            return 1;
        }
        
        // Send HTTP response
        ssize_t sent_bytes = send(client_socket, http_header, strlen(http_header), 0);
        if (sent_bytes < 0) {
            perror("Error sending response");
            close(client_socket);
            return 1;
        }
        printf("Sent %ld bytes of HTTP response\n", sent_bytes);
        close(client_socket);
    }
    
    free(response_data);
    return 0;
}

