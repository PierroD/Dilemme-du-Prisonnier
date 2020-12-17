# ICS - Dilemme du prisonnier  

[![Video de présentation youtube](http://img.youtube.com/vi/1_BvK2cUkgg/0.jpg)](https://www.youtube.com/watch?v=1_BvK2cUkgg)

### Sommaire

- [Téléchargements](#Download)
- [Contexte](#Contexte)
- [Contraintes](#Contraintes)
- [A propos](#Propos)
- [Guide d'utilisation](#Usage)
- [Mise à jour de la configuration](#MAJ)
- [Protocoles](#Protocoles)
- [Architecture du projet](#Architecture)

### Téléchargements  <a name="Download"></a>
- [Télécharger le serveur et le client](https://gitlab.com/PierroD/projet_prisonnier/-/raw/master/download/both.7z?inline=false)
- [Télécharger le serveur](https://gitlab.com/PierroD/projet_prisonnier/-/raw/master/download/server.7z?inline=false)
- [Télécharger le client](https://gitlab.com/PierroD/projet_prisonnier/-/raw/master/download/client.7z?inline=false)


### Contexte  <a name="Contexte"></a>

L’ICS (institue of Cognitives Sciences) est un laboratoire interdisciplinaire qui intègre l'expertise de chercheurs des Sciences de la Vie (psychologie cognitive, neurosciences) et de médecine (pédopsychiatrie, neuro-pediatrie) avec celle de chercheurs des Sciences Humaines et Sociales (linguistique computationelle et théorique et philosophie) pour étudier la nature et la spécificité de l'esprit humain.

Le doctorant, qui n’est pas un développeur, a besoin d’accumuler des données expérimentales. Il a besoin que des volontaires jouent l’un contre l’autre un nombre de fois à définir, sans jamais savoir qui sont leurs adversaires. On définira une partie comme étant un certain nombre de rounds. Un round est défini comme une confrontation trahison-collaboration entre les deux volontaires.

### Contraintes <a name="Contraintes"></a>

- **2.1 Serveur :**
Le serveur doit être paramétrable. Le fichier de paramétrage permettra de définir l’adresse IP et le port sur lequel l’application serveur sera à l’écoute.
Le fichier contiendra aussi le paramétrage nécessaire pour définir les réglés du jeu : somme engagée a chaque partie, le nombre de parties et d’autres informations qui vous sembleront nécessaires.
A la fin de la partie, le serveur doit garder dans un fichier (le format est à définir) les choix de
chacun des joueurs, ainsi que le temps de décision et les montants accumulés ou perdus.
- **2.2 Client :**
Le fichier de paramétrage du client doit contenir l’adresse IP du serveur ainsi que le port et tout
autre paramétrage qui vous sembleront pertinents.
L’interface graphique des clients doit rester très simple : le cobaye ne doit pas être déconcentré par
des fioritures : deux boutons cliquables (Trahir, Collaborer), le résultat du round (il doit savoir s’il a
gagné ou perdu). Il doit être informé du début de chaque roun

### A propos <a name="Propos"></a>

Comme demandé des les consignes nous avons fait en sorte de rendre le code le plus évolutif possible, ainsi si vous voulez rajouter un joueur par partie, ou de faire en sorte qu'il y est plus de 2 parties jouables, vous pouvez directement modifier ces paramètres dans les fichiers de configurations.

Il était aussi demandé de donner une structure au projet, nous avons choisi le modèle **MVC** (**M**odel **V**iew **C**ontroller), étant une architecture très en vogue dans le monde de l'entreprise et en général nous avons voulu nous en rapprocher le plus possible.

### Guide d'utilisation <a name="Usage"></a>

- Pour démarrer le serveur :
    - Dans un premier temps assurez que la configuration vous convienne
    - Lancer le serveur (allez dans le dossier build ouvrez un terminal et tapez : ./server)
    - Une fois les parties finie, vous devez éteindre le serveur et le relancer à nouveau si le nombre de connexion maximum a été atteint suite à son premier lancement 

- Pour le client :
    - Dans un premier temps assurez que la configuration est conforme (Ip du serveur, port, où se trouve la vue)
    - Lancer le client (allez dans le dossier build ouvrez un terminal et tapez : ./client)
    - Si le serveur n'est pas encore lancé, lancez le ! :smile:
    - Une fois connecté, cliquez sur le bouton intitulé "je suis prêt"
    - Si un deuxième joueur est présent, la partie pourra alors commencé

*PS : la gestion des parties est en mode FIFO, donc si 2 joueurs veulent jouer en même temps il est préférable qu'ils se connectent en même temps.*

### Mise à jour de la configuration <a name="MAJ"></a>

##### Configuration du serveur
Ce fichier de configuration se trouve dans les dossiers de `builds`, ou à la racine de l'exécutable `serveur.exe` si vous avez uniquement téléchargé le serveur
**server.ini**
```ini
[network]
server_ip_address=0.0.0.0 ; adresse ip du serveur
server_port=7799 ; port du serveur

[parameters]
max_simultaneous_connection=4 ; nombre de connexion simultanées
max_player_per_room=2 ; nombre maximum de joueur par partie
round_number=2 ; nombre de tours par partie
time_to_decide=10 ; le temps qu'a le joueur pour se décider

[export]
export_folder_path= ; dossier vers lequel on veut exporter les résultats

[debug] ; Message affichés lorsque le serveur est lancé
show_packet=true ; affiche les paquets
show_player=true ; affiche les joueurs
show_room=true ; affiche la salle d'attente
show_game=false ; affiche la partie
show_round=true ; affiche le tour
show_dilemma=false ; affiche le dilemme envoyé
show_answer=true ; affiche les réponses reçues par le serveur
show_offset=false ; affiche les adresses mémoires 

```

##### Configuration du client 
Ce fichier de configuration se trouve dans les dossiers de `builds`, ou à la racine de l'éxécutable `client.exe` si vous avez uniquement téléchargé le client
**client.ini**
```ini
[network]
server_ip_address=127.0.0.1 ; adresse ip du serveur
server_port=7799 ; port du serveur

[view]
file_path=view/GameWindow.glade ; chemin vers la vue (peut être différent pour le debug)

```

### Protocoles <a name="Protocoles"></a>

Liste des protocoles envoyés :
| Protocoles   |       Serveur      |       Client       |
|--------------|:------------------:|:------------------:|
| CONNECTED    | :heavy_check_mark: |                    |
| PLAYER_READY | :heavy_check_mark: | :heavy_check_mark: |
| ROOM_READY   | :heavy_check_mark: |                    |
| ASK_CHOICE   | :heavy_check_mark: |                    |
| RESPONSE     |                    | :heavy_check_mark: |
| GAME_END     | :heavy_check_mark: |                    |
| DISCONNECT   |                    | :heavy_check_mark: |




### Architecture du projet <a name="Architecture"></a>

```bash
.
├── client // client 
│   ├── build // dossier contenant le build 
│   │   ├── client
│   │   ├── client.ini
│   │   └── view
│   │       ├── assets
│   │       │   ├── betray.png
│   │       │   └── silence.png
│   │       ├── GameWindow.glade
│   │       └── GameWindow.glade~
│   ├── Makefile // makefile
│   └── src // fichiers du client
│       ├── client.c // main
│       ├── controller // controlleurs du client
│       │   ├── gameWindowController.c
│       │   └── gameWindowController.h
│       ├── includes // includes
│       │   └── packetModel.h
│       ├── utils // outils du client
│       │   ├── buffer
│       │   │   ├── read.c
│       │   │   ├── read.h
│       │   │   ├── write.c
│       │   │   └── write.h
│       │   ├── config
│       │   │   ├── ini.c
│       │   │   ├── ini.h
│       │   │   ├── parser.c
│       │   │   └── parser.h
│       │   ├── connection
│       │   │   ├── manager.c
│       │   │   └── manager.h
│       │   ├── packet
│       │   │   ├── processor.c
│       │   │   └── processor.h
│       │   ├── response
│       │   │   ├── response.c
│       │   │   └── response.h
│       │   └── serialization
│       │       ├── serialize.c
│       │       └── serialize.h
│       └── view // la vue du client
│           ├── assets
│           │   ├── betray.png
│           │   └── silence.png
│           ├── GameWindow.glade
│           └── GameWindow.glade~
├── download // dossier contenant tous les builds du projet
│   ├── both.7z // client & serveur
│   ├── client.7z // client
│   └── server.7z // serveur
├── Doxyfile // fichier doxyfile
├── html // contnue de la documentation doxygene
├── ini files // tous les fichiers de configurations
│   ├── client.ini
│   └── server.ini
├── README.md // readme
└── server // serveur
    ├── build // dossier contenant le build
    │   ├── server
    │   └── server.ini
    ├── Makefile // makefile
    └── src // dossier contenant les fichiers du serveur
        ├── controllers // controlleurs du serveur
        │   ├── game
        │   │   ├── gameController.c
        │   │   └── gameController.h
        │   ├── player
        │   │   ├── playerController.c
        │   │   └── playerController.h
        │   └── room
        │       ├── roomController.c
        │       └── roomController.h
        ├── models // les models du serveur
        │   ├── gameModel.h
        │   ├── packetModel.h
        │   ├── playerModel.h
        │   └── roomModel.h
        ├── server.c // main du serveur
        ├── utils // les outils du serveur
        │   ├── buffer
        │   │   ├── read.c
        │   │   ├── read.h
        │   │   ├── write.c
        │   │   └── write.h
        │   ├── config
        │   │   ├── ini.c
        │   │   ├── ini.h
        │   │   ├── parser.c
        │   │   └── parser.h
        │   ├── connection
        │   │   ├── manager.c
        │   │   └── manager.h
        │   ├── export
        │   │   ├── tocsv.c
        │   │   └── tocsv.h
        │   ├── packet
        │   │   ├── processor.c
        │   │   └── processor.h
        │   ├── response
        │   │   ├── response.c
        │   │   └── response.h
        │   ├── serialization
        │   │   ├── serialize.c
        │   │   └── serialize.h
        │   └── table
        │       ├── fort.c
        │       └── fort.h
        └── views // la vue du serveur
            ├── game
            │   ├── gameView.c
            │   └── gameView.h
            ├── offset
            │   ├── offsetView.c
            │   └── offsetView.h
            ├── packet
            │   ├── packetView.c
            │   └── packetView.h
            └── room
                ├── roomView.c
                └── roomView.h
```
