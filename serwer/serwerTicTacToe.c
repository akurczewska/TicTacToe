#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define SERVER_PORT 1234
#define QUEUE_SIZE 5
//#define bufor 1024
#define N 500

//char cbBuf[bufor];
pthread_mutex_t example_mutex = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

//struktura do odebrania socketu klienta
struct thread_data_t
{
	int socket;
};

//struktura przechowująca informacje o graczach
struct players
{
	int ready; //1 - jeżeli gracz czeka na przydzielenie przeciwnika; 0 - jeżeli przeciwnik został przydzielony
	int socket; // nr socketu gracza
};
struct players player[N];

//struktura zawierająca nr graczy w strukturze player, co pozwala na komunikację między graczami podczas rozgrywki
struct whoPlay
{
    int id_player1; // nr gracza1 w strukturze player (kółko)
    int id_player2; // nr gracza2 w strukturze player (krzyżyk) 
};

//funkcja odpowiadająca za przeprowadzenie rozgrywki
void *Game(void *t_who)
{
    struct whoPlay *who = (struct whoPlay*)t_who;
    char cdBuf[24]; //bufor zawierający dane do wysłania klientowi
    int odp1; //do sprawdzenia czy gracz 1 nie wyłączył się z gry
    int odp2; //do sprawdzenia czy gracz 2 nie wyłączył się z gry
    
    //wysyłanie informacji, który gracz jest pierwszy, a który drugi
    bzero(cdBuf,sizeof(cdBuf));
    cdBuf[0] = '1';
    printf("Id graczy w strukturze player: %d %d\n", (*who).id_player1, (*who).id_player2);
    write(player[(*who).id_player1].socket, cdBuf, sizeof(cdBuf));
    
    bzero(cdBuf,sizeof(cdBuf));
    cdBuf[0] = '2';
    write(player[(*who).id_player2].socket, cdBuf, sizeof(cdBuf));
    
    
    int match = 1; //zmienna informująca czy odbywa się rozgrywka
    int round = 1; //zmienna informująca, który gracz aktualnie wykonuje ruch
    while(match == 1)  //pętla rozgrywki
    { 
      printf("gra\n");
      //odebranie ruchu gracza pierwszego
      if(round == 1)
      {
	printf("round %d\n", round);
	bzero(cdBuf,sizeof(cdBuf));
	if(odp2 = read(player[(*who).id_player1].socket, cdBuf, sizeof(cdBuf)) <= 0) //sprawdzenie czy gracz się rozłączył lub zresetował grę
	{
	  match = -1;
	  break;
	}
	
	if(cdBuf[0] == 0)
	{
	  write(player[(*who).id_player1].socket, cdBuf, sizeof(cdBuf));
	}
	else 
	{
	  //wysłanie stanu pól do drugiego gracza
	  round = 2;
	  write(player[(*who).id_player2].socket, cdBuf, sizeof(cdBuf));
	  printf("Wysłanie stanu pól do 2 %c\n", cdBuf[0]);
	}
	
      }
      
      //odebranie ruchu drugiego gracza
      if(round == 2)
      {
	printf("round %d\n", round);
	bzero(cdBuf,sizeof(cdBuf));
	if(odp1 = read(player[(*who).id_player2].socket, cdBuf, sizeof(cdBuf)) <= 0) //sprawdzenie czy gracz się rozłączył lub zresetował grę
	{
	  match = -1;
	  break;
	}
	
	
	if(cdBuf[0] == 0)
	{
	  write(player[(*who).id_player2].socket, cdBuf, sizeof(cdBuf));
	}
	else 
	{
	  //wysłanie stanu pól do pierwszego gracza
	  round = 1;
	  write(player[(*who).id_player1].socket, cdBuf, sizeof(cdBuf));
	  printf("Wysłanie stanu pól do 1 %c\n", cdBuf[0]);
	}
      }
    }
    
    //jeżeli gra została przerwana wysyłam informację do przeciwnika
    if(odp1 <= 0 && match == -1) 
    {
      printf("Odszedł: 1\n");
      bzero(cdBuf,sizeof(cdBuf));
      cdBuf[4] = '3';
      write(player[(*who).id_player2].socket, cdBuf, sizeof(cdBuf));
    }
    else if(odp2 <= 0 && match == -1)
    {
      printf("KONIEC GRY! odszedł: 2\n");
      bzero(cdBuf,sizeof(cdBuf));
      cdBuf[4] = '3';
      write(player[(*who).id_player1].socket, cdBuf, sizeof(cdBuf));
    }
    
    pthread_exit(NULL);
}

//funkcja obsługująca połączenie z nowym klientem
void *handleConnection(void *ta_data) {
  
    printf("HandleConnection\n");
    int create_result = 0;  //wynik tworzenia wątku

    //uchwyt na wątek
    pthread_t thread1;

    //dane, które zostaną przekazane do wątku
    struct thread_data_t *t_data = (struct thread_data_t*)ta_data;
  
    printf("przed mutexem\n");
    pthread_mutex_lock(&example_mutex); //MUTEX
  
    //zapisanie klienta do struktury player
    player[counter].socket = (*t_data).socket;
    player[counter].ready = 1;
    counter++;
     
    //sprawdzanie gotowych graczy
    int i = 0;
    struct whoPlay who;
    who.id_player1 = -1;
    who.id_player2 = -1;
    for(i = 0; i < counter; i++)
    {
      if(player[i].ready == 1)
      {
	if(who.id_player1 == -1) 
	{
	  who.id_player1 = i;
	}
	else
	{
	  who.id_player2 = i;
	  i = counter+1;
	}
      }
    }
    if(who.id_player1 != -1 && who.id_player2 != -1) 
    {
      player[who.id_player1].ready = 0;
      player[who.id_player2].ready = 0;
    }
    printf("koniec muxa\n");
    pthread_mutex_unlock(&example_mutex);
    //////////////////////////////////////
    

    //tworzę wątek do gry jeżeli znalezieni zostali dwaj gracze
    if(who.id_player1 != -1 && who.id_player2 != -1)
    {
      printf("GRA\n");
      printf("Id graczy: %d %d\n", who.id_player1, who.id_player2);

      create_result = pthread_create(&thread1, NULL, Game, (void *)&who);
      if (create_result)
      {
	printf("Błąd przy próbie utworzenia wątku, kod błędu: %d\n", create_result);
	exit(-1);
      }
      (void) pthread_join(thread1, NULL);
    }
    printf("Koniec Wszystkiego\n");
}

int main(int argc, char* argv[])
{
   int server_socket_descriptor;      //deskryptor serwera	
   int connection_socket_descriptor;  //deskryptor klienta
   int bind_result;
   int listen_result;
   char reuse_addr_val = 1;
   struct sockaddr_in server_address;

//////////////inicjalizacja gniazda serwera/////////////////////
   memset(&server_address, 0, sizeof(struct sockaddr));
   server_address.sin_family = AF_INET;
   server_address.sin_addr.s_addr = htonl(INADDR_ANY);
   server_address.sin_port = htons(SERVER_PORT);

   server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
   if (server_socket_descriptor < 0)
   {
       fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda..\n", argv[0]);
       exit(1);
   }
   setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_addr_val, sizeof(reuse_addr_val));

   bind_result = bind(server_socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));  //związanie gniazda z adresem maszyny
   if (bind_result < 0)
   {
       fprintf(stderr, "%s: Błąd przy próbie dowiązania adresu IP i numeru portu do gniazda.\n", argv[0]);
       exit(1);
   }
    
   listen_result = listen(server_socket_descriptor, QUEUE_SIZE); //gniazdo do odbierania zgłoszeń
   if (listen_result < 0) {
       fprintf(stderr, "%s: Błąd przy próbie ustawienia wielkości kolejki.\n", argv[0]);
       exit(1);
   }

   
   while(1)
   {
       printf("Czekam\n");
       connection_socket_descriptor = accept(server_socket_descriptor, NULL, NULL);  //funkcja oczekuje na zgłoszenie lub pobiera takowe z kolejki
       if (connection_socket_descriptor < 0)
       {
           fprintf(stderr, "%s: Błąd przy próbie utworzenia gniazda dla połączenia.\n", argv[0]);
           exit(1);
       }

       pthread_t thread1;
       struct thread_data_t t_data;
       t_data.socket = connection_socket_descriptor;
        printf("Wchodze do watku\n");
       pthread_create(&thread1, NULL, handleConnection, (void *)&t_data);
   }

   close(server_socket_descriptor);
   return(0);
}
