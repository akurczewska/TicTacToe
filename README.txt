Gra Kółko i krzyżyk

KOMPILACJA:
Znajdując się kolejno w folderze klienta i serwera, w celu komilacji programu należy wpisać w terminalu: ./kompiluj

URUCHOMIENIE:
W celu uruchomienia projektu, znajdując się w odpowiednich folderach (klient lub serwer) należy wpisać w terminalu: 
-dla serwera: ./serwer
-dla klienta: ./klient

ZAWARTOŚĆ PLIKÓW:
- plik serwer.c zawiera wszystkie odpowiednie mechanizmy do komunikacji TCP, struktury i instrukcje potrzebne do działania serwera gry.
   		Ogólny zarys działania programu: Proces macieżysty przez cały czas działania programu nasłuchuje czy jakiś nowy klient chce się połączyć z serwerem. Następnie tworzony jest wątek, który szuka drugiego gracza dla klienta. Jeżeli istnieje dwóch graczy oczekujących na rozgrywkę tworzony jest kolejny wątek, który odpowiada za komunikację z serwerem i przeprowadzenie rozgrywki. 

- plik klient.c zawiera wszystkie odpowiednie mechanizmy do komunikacji TCP, struktury i instrukcje potrzebne do działania klienta gry.
		Ogólny zarys działania programu: Uruchomienie programu powoduje nawiązanie połączenia z serwerem. Pobierane zostają informacje od serwera na temat kolejności przeprowadzenia rozgrywki. Następnie odbierane/wysyłane są dane przez bufor do serwera z danymi odnośnie do wykonanych ruchów.
