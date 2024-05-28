# Simulare turneu si calcularea prestigiului

## Descriere
Acest proiect reprezintă o soluție software pentru simularea unui turneu de echipe și calcularea prestigiului fiecărei echipe. Turneul implică 32 de echipe care se confruntă pentru a determina câștigătorul final, iar prestigiul fiecărei echipe este calculat pe baza performanțelor lor în competiție.

## Structura Proiectului

### `main.c`
Fișierul principal al proiectului conține funcția `main`, care este punctul de intrare al programului. În acest fișier, inițializăm structurile de date necesare, citim datele de intrare și coordonăm executarea funcțiilor din celelalte module pentru a desfășura turneul și a calcula prestigiul echipelor.

### `structuri.h`
Acest fișier conține declarațiile structurilor de date utilizate în program:

- **Team**: Reprezintă o echipă cu atributele sale (poziție, nume, scor si numarul de victorii).
- **Node**: Nodul unei liste simplu înlănțuite folosită pentru a gestiona echipele.
- **Queue**: Structura de coadă pentru gestionarea meciurilor între echipe.
- **QueueNode**: Nodul unei cozi folosită pentru a gestiona echipele în timpul meciurilor.

### `functii.c` și `functii.h`
Aceste fișiere conțin funcțiile necesare pentru desfășurarea turneului și calcularea prestigiului echipelor:

- **`Node* createNode(Team *team)`**: Creează un nod nou în listă pentru o echipă.
- **`void addTeamToBack(Node **head, Team *team)`**: Adaugă o echipă la sfârșitul listei.
- **`Node* readTeams(FILE *in)`**: Citește echipele din fișierul de intrare și le adaugă în listă.
- **`void freeList(Node *head)`**: Eliberează memoria alocată pentru lista de echipe.
- **`void enqueue(Queue *queue, Team *team)`**: Adaugă o echipă în coadă.
- **`Team* dequeue(Queue *queue)`**: Extrage o echipă din coadă.
- **`int isEmptyQueue(Queue *queue)`**: Verifică dacă coada este goală.
- **`void formMatches(Node *teamList, Queue *queue)`**: Formează meciuri între echipele din listă și le adaugă în coadă.
- **`void processMatches(Queue *queue, Queue *losers, Queue *winners, int **adj_matrix)`**: Procesează meciurile din coadă, actualizând cozile de câștigători și pierzători și matricea de adiacență.
- **`double calculate_P_r(double q, int r, int l)`**: Calculează prestigiul unei echipe folosind formula dată.

#### Algoritmi folosiți:

##### Citirea Echipei
Funcția `readTeams` citește echipele dintr-un fișier text (team.in). Aceasta parcurge fiecare linie a fișierului, extrage informațiile despre echipă și le stochează într-un vector de structuri Team.

###### Algoritm 1
1. Deschide fișierul team.in pentru citire.
2. Pentru fiecare linie din fișier:
    >Citește scorul și numele echipei.
    >Creează un obiect Team și completează câmpurile total_score, name, wins și team_index.
    >Adaugă obiectul Team la sfârșitul listei.
3. Închide fișierul.

###### Algoritm 2
1. Creează cozi pentru echipele câștigătoare și pierzătoare.
2. Pentru fiecare rundă a turneului:
    >Inițializează o coadă pentru câștigătorii rundei curente.
    >Cât timp există echipe în coada de câștigători:
        >Extrage două echipe din coadă.
        >Compară scorurile echipelor. Dacă scorurile sunt egale, ordonează alfabetic numele echipelor.
        >Adaugă echipa câștigătoare în coada pentru runda următoare și echipa pierzătoare în coada de pierzători.
    >Înlocuiește coada de câștigători cu coada pentru runda următoare.
3. Returnează echipa câștigătoare finală și coada echipelor pierzătoare.

##### Crearea Matricei de Adiacență
Funcția `processMatches` creează o matrice de adiacență pentru a reprezenta graful turneului. Matricea de adiacență este o reprezentare bidimensională a relațiilor dintre echipele din turneu, unde fiecare element (i, j) indică dacă echipa i a învins echipa j. Pentru a construi această matrice, se parcurge fiecare meci din turneu și se actualizează matricea pentru a reflecta rezultatele. 

###### Algoritm 3
1. Inițializează o matrice de adiacență de dimensiune num_teams x num_teams cu valori zero.
2. Pentru fiecare meci din turneu:
    >Marchează o conexiune în matrice între echipa câștigătoare și echipa pierzătoare.
3. Actualizează matricea de adiacență pe măsură ce meciurile sunt procesate.

###### Calcularea Prestigiului
Prestigiul fiecărei echipe este calculat folosind funcția calculatePrestige. Prestigiul este determinat pe baza numărului de victorii ale echipei în turneu, folosind formula:
`prestigiu = (victorii / (numărul total de echipe - 1)) + q * ((numărul total de echipe - 1 - victorii) / (numărul total de echipe - 1))`
unde `q` este un factor constant (în acest caz, 0.15). Această formulă ia în considerare atât numărul de victorii cât și numărul de înfrângeri pentru a calcula prestigiul echipei într-un mod echitabil. Prestigiul calculat este atribuit fiecarei echipe și apoi sortat în ordine descrescătoare.

###### Algoritm 4
1. Pentru fiecare echipă:
    >Calculează prestigiul folosind formula dată.
    >Stochează prestigiul într-un vector de prestigiuri.
2. Sortează vectorul de prestigiuri în ordine crescătoare.
