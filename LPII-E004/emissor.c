#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#define BUFFER_SIZE 100


int main(int argc, char ** argv ){
    int client_fd, port; //file descriptor do socket, porta 
	char buffer[BUFFER_SIZE]; //buffer que armazena mensagem a ser enviada
	struct sockaddr_in server_addr;
    
    if(argc != 4){
        printf("Parametros de entrada invalidos !\n Padrao Correto :\t ./emissor arquivo.txt IP PORTA \n");
        return 1; 
    }

	port = atoi(argv[3]); // int com PORTA
    char * host = argv[2]; //string com endereco para quem a mensagem sera enviada via UDP
	
	client_fd = socket(AF_INET, SOCK_DGRAM, 0); //crio o socket 

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_aton(host, &server_addr.sin_addr); //passo para a estrutura o endereco para quem sera enviada a mensagem

    FILE * f = fopen(argv[1], "r");
    if (!f){  
        printf("Erro ao abrir arquivo !\n"); 
        return -1; 
    }


    while (fgets(buffer, BUFFER_SIZE, f) != NULL){ 
        printf("Enviar para o servidor UDP: %s\n", buffer); 
        sendto(client_fd, buffer, 100, 0, (struct sockaddr*) &server_addr, 
			    (unsigned int) sizeof(server_addr));  //envia para o servidor via UDP 
							                          // (passa a estrutura sockaddr na propria funcao)

    }

    fclose(f); 
	
	return 0;
}
