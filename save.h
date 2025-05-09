#ifdef SAVE_H
#define SAVE_H

int fichierEstVide(const char *nomFichier) {
    FILE *f = fopen(nomFichier, "rb");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1; 
    }

    fseek(f, 0, SEEK_END);       
    long taille = ftell(f);     
    fclose(f);

    return (taille == 0);  
}

void save(GameData data){ // il faudra créer 3 fichiers binaires : un fichierSauvegarde1, fichierSauvegarde2, fichierSauvegarde3 pour chacune des sauvegardes
    char choix[15];
    int num;
    if(fichierEstVide(fichierSauvegarde1)){
        FILE *fichier = fopen(fichierSauvegarde1, "wb");
        if(fichier == NULL){
            printf("Erreur d'ouverture du fichier.\n");
            exit(EXIT_FAILURE);
        }
        int ecrits = fwrite(data, sizeof(data), 1, fichier);
        if(ecrits != 1){
            printf("Erreur d'écriture dans le fichier.\n");
        }
        fclose(fichier);
    }

    else if(fichierEstVide(fichierSauvegarde2)){
    FILE *fichier = fopen(fichierSauvegarde2, "wb");
    if(fichier == NULL){
        printf("Erreur d'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
    int ecrits = fwrite(Data, sizeof(Data), 1, fichier);
    if(ecrits != 1){
        printf("Erreur d'écriture dans le fichier.\n");
    }
    fclose(fichier);
    }
    else if(fichierEstVide(fichierSauvegarde3)){
    FILE *fichier = fopen(fichierSauvegarde3, "wb");
    if(fichier == NULL){
        printf("Erreur d'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
    int ecrits = fwrite(Data, sizeof(Data), 1, fichier);
    if(ecrits != 1){
        printf("Erreur d'écriture dans le fichier.\n");
    }
    fclose(fichier);
    }
    else{
        printf("Toutes les sauvegardes sont actuellement utilisées, voulez-vous ECRASER une sauvegarde ou ABANDONNER ?");
        scanf("%s", &choix);
        do {
            if(choix == "Abandonner" || choix == "abandonner" || choix == "ABANDONNER"){
            exit(1);
            }   
            else if(choix == "ECRASER" || choix == "Ecraser" || choix == "écraser" || choix == "ecraser"){
                printf("Quelles sauvegardes voulez-vous écraser ? 1, 2 ou 3 ?\n");
                scanf("%d", &num);
                if(num == 1){
                    FILE *f = fopen("fichierSauvegarde1", "wb");
                    if (f == NULL) {
                        printf("Erreur lors de l'ouverture du fichier");
                    }
                    else {
                    fclose(f);
                    }
                    save(GameData data);
                    exit(1);
                }
                if(num == 2){
                    FILE *f = fopen("fichierSauvegarde2", "wb");
                    if (f == NULL) {
                        printf("Erreur lors de l'ouverture du fichier");
                    }
                    else {
                    fclose(f);
                    }
                    save(GameData data);
                    exit(1);
                }
                if(num == 3){
                    FILE *f = fopen("fichierSauvegarde3", "wb");
                    if (f == NULL) {
                        printf("Erreur lors de l'ouverture du fichier");
                    }
                    else {
                    fclose(f);
                    }
                    save(GameData data);
                    exit(1);
                }
            }
            printf("Je n'ai pas compris, voulez-vous abandonner ou écraser ?");
        }while(choix != "Abandonner" || choix != "abandonner" || choix != "ABANDONNER" || choix != "ECRASER" || choix != "Ecraser" || choix != "écraser" || choix != "ecraser");
    }
}

Save* getSaves(){
    Save tab[3];
    return tab;
}

Save load(int n){
    Save save;
    return save; // pour que le programme principal crashe pas
}

#endif