#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <sys/wait.h>

// • Le premier enfant exécutera « firefox » de manière à ce que la navigateur s’ouvre dans une fe-
// nêtre de taille 800x1200 et avec deux onglets : un pointant sur « https://foad.ensicaen.fr » et
// l’autre sur « https://gitlab.ecole.ensicaen.fr ».
void openFireFox() {
   char *args[] = {
		"firefox",
        "--width=800", 
        "--height=1200",
        "https://foad.ensicaen.fr", 
        "https://gitlab.ecole.ensicaen.fr", 
        "--new-window", 
        NULL
    };

    if(execvp("firefox", args) == -1) {
        perror("Error at firefox");
        exit(1);
    }
}

// • Le deuxième enfant exécutera aussi « firefox » de manière à ce qu’une recherche sur « Codeium
// » et « Vim » soit réalisée par le moteur de recherche par défaut du navigateur.
void searchAtDefaultEngine() {
   char *args[] = {
		"firefox",
        "--search",
        "Vim",
		"--new-tab",
		"--search",
        "Codeium",  
        "--new-window", 
        NULL
    };

    if(execvp("firefox", args) == -1) {
        perror("Error at firefox");
        exit(1);
    }

}

// • Le troisième enfant exécutera « gedit » (l’éditeur par défaut) de manière à ce qu’il ouvre automa-
// tiquement un fichier de votre choix dont le nom aura été passé en argument lors de l’appel du
// programme.
void openFileAtEditor(char name[]) {
	char *args[] = {
		"gedit",
        name, 
        NULL
    };

    if(execvp("gedit", args) == -1) {
        perror("Error at gedit");
        exit(1);
    }
}

// • Le quatrième enfant exécutera le visualiseur de documents (« evince ») de manière à ce qu’il ouvre
// automatiquement ce fichier PDF.
void openPDF() {
	char *args[] = {
		"evince",
        "./01_tp-generation-courbe.pdf", 
        NULL
    };
	
    if(execvp("evince", args) == -1) {
        perror("Error at evince");
        exit(1);
    }
}

int main(int argc, char* argv[]) 
{ 
	// Creating first child 
	int n1 = fork(); 
	if(n1 == 0) {
        openFireFox();
		return 0;
	} else if (n1 == -1) {
		perror("Error at fork");
		exit(1);
	}
	printf("first child id is %d \n", n1); 

	// Creating second child 
	int n2 = fork(); 
	if(n2 == 0) {
        searchAtDefaultEngine();
		return 0;
	} else if (n2  == -1) {
		perror("Error at fork");
		exit(1);
	}
	printf("second child id is %d \n", n2); 

	// Creating third child 
	int n3 = fork(); 
	if(n3 == 0) {
        openFileAtEditor(argv[1]);
		return 0;
	} else if (n3 == -1) {
		perror("Error at fork");
		exit(1);
	}
	printf("third child id is %d \n", n3); 

	// Creating fourth child 
	int n4 = fork(); 
	if(n4 == 0) {
        openPDF(); 
		return 0;
	}  else if (n4 == -1) {
		perror("Error at fork");
		exit(1);
	}
	printf("fourth child id is %d \n", n4); 

	wait(NULL);
	return 0; 
} 

