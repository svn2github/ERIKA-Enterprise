Test 5

Il test5 riguarda l'attivazione di 2 tasks. Il primo
a priorità più bassa è attivato nel main all'inizio mentre 
il secondo a priorità più alta è attivato da un'interrupt (2)
innestata su un'altra interrupt (1) a priorità più bassa.
Il test serve per verificare che lo scheduler sia chiamato
al termine dell'interrupt 1.