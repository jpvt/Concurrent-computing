#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define BUFFER_SIZE 100

int main(int argc, char ** argv ){
    int endFlag = 1;
	int server_fd, port, recv_bytes = -1; //file descriptor do socket, porta e bytes recebidos
	char buffer[BUFFER_SIZE]; // buffer que armazenara mensagem recebida
	struct sockaddr_in server_addr; //estrutura que armazena informacoes do socket
    char * fim = "FIMDEMENSAGEM";

    if(argc > 2){
        printf("Parametros de entrada invalidos !\n Padrao Correto :\t ./receptor PORTA \n");
        return 1; 
    }

	port = atoi(argv[1]);
	
	server_fd = socket(AF_INET, SOCK_DGRAM, 0); //crio o socket UDP

	server_addr.sin_family = AF_INET;  
	server_addr.sin_port = htons(port); 
	server_addr.sin_addr.s_addr = INADDR_ANY; //Defino a recepcao de pacotes de qualquer origem 


	bind(server_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)); //associo estrutura ao socket
    
    FILE *fp = fopen("recebido.txt", "wb");

	while(endFlag != 0) {
	
		printf("Aguardando por mensagens UDP na porta %d...\n", port);
		recv_bytes = recvfrom(server_fd, buffer, BUFFER_SIZE, MSG_WAITALL, 
				NULL, NULL ); //funcao recvfrom bloqueante, recebe mensagens UDP e armazena em buffer
        
        endFlag = strncmp(buffer,fim,strlen(fim));

        if(endFlag != 0){
            printf("Recebi: %d bytes\n", recv_bytes);
		    fprintf(stdout, "Salvando a mensagem: %s\n", buffer);
            fprintf(fp, "%s", buffer);
        }
	}


	fclose(fp);
    puts("Salvou no arquivo recebido\n");

	return 0;
}
