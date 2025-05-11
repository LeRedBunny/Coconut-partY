#ifdef SAVE_H
#define SAVE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    GameData Data;
    char name[20];
} Save;

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

void verif_et_crea(){
    FILE *verif1 = fopen("save1.bin","rb");
    FILE *verif2 = fopen("save2.bin","rb");
    FILE *verif3 = fopen("save3.bin","rb");
    if(verif1 == NULL){
        verif1 = fopen("save1.bin", "wb");
        if(verif1 == NULL){
            perror("Erreur lors de la création du fichier save1.");
        }
        else{
            fclose(verif1);
        }
    }
    else{
        fclose(verif1);
    }

    if(verif2 == NULL){
        verif2 = fopen("save2.bin", "wb");
        if(verif2 == NULL){
            perror("Erreur lors de la création du fichier save2.");
        }
        else{
            fclose(verif2);
        }
    }
    else{
        fclose(verif2);
    }

    if(verif3 == NULL){
        verif3 = fopen("save3.bin", "wb");
        if(verif3 == NULL){
            perror("Erreur lors de la création du fichier save3.");
        }
        else{
            fclose(verif3);
        }
    }
    else{
        fclose(verif3);
    }
}

void saveGame(GameData data){ // il faudra créer 3 fichiers binaires : save1, save2, save3 pour chacune des sauvegardes
    char choix[15];
    int num;
    Save save;
    save.Data = data;
    verif_et_crea();
    do{
        printf("Comment voulez-vous appelez votre sauvegarde ? (20 caractères max)\n");
        scanf("%s", save.name);
    }while(strlen(save.name) <= 0 || strlen(save.name) > 20);
    if(fichierEstVide(save1)){
        FILE *fichier = fopen(save1, "wb");
        if(fichier == NULL){
            perror("Erreur d'ouverture du fichier.");
        }
        int ecrits = fwrite(&save, sizeof(Save), 1, fichier);
        if(ecrits != 1){
            perror("Erreur d'écriture dans le fichier.");
        }
        fclose(fichier);
    }

    else if(fichierEstVide(save2)){
        FILE *fichier = fopen(save2, "wb");
        if(fichier == NULL){
            perror("Erreur d'ouverture du fichier.");
        }
        int ecrits = fwrite(&save, sizeof(Save), 1, fichier);
        if(ecrits != 1){
            perror("Erreur d'écriture dans le fichier.");
        }
        fclose(fichier);

    }
    else if(fichierEstVide(save3)){
        FILE *fichier = fopen(save3, "wb");
        if(fichier == NULL){
            perror("Erreur d'ouverture du fichier.");
        }
        int ecrits = fwrite(&save, sizeof(Save), 1, fichier);
        if(ecrits != 1){
            perror("Erreur d'écriture dans le fichier.");
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
                    FILE *f = fopen("save1", "wb");
                    if (f == NULL) {
                        perror("Erreur lors de l'ouverture du fichier");
                    }
                    else {
                    fclose(f);
                    }
                    saveGame(data);
                    exit(1);
                }
                if(num == 2){
                    FILE *f = fopen("save2", "wb");
                    if (f == NULL) {
                        perror("Erreur lors de l'ouverture du fichier");
                    }
                    else {
                    fclose(f);
                    }
                    saveGame(data);
                    exit(1);
                }
                if(num == 3){
                    FILE *f = fopen("save3", "wb");
                    if (f == NULL) {
                        perror("Erreur lors de l'ouverture du fichier");
                    }
                    else {
                    fclose(f);
                    }
                    saveGame(data);
                    exit(1);
                }
            }
            printf("Je n'ai pas compris, voulez-vous abandonner ou écraser ?");
        }while(choix != "Abandonner" || choix != "abandonner" || choix != "ABANDONNER" || choix != "ECRASER" || choix != "Ecraser" || choix != "écraser" || choix != "ecraser");
    }
}

Save* getSaves(){
    Save tab[3];
    FILE *fichier1 = fopen(save1, "rb");
    if(fichier1 == NULL){
        perror("Erreur d'ouverture du fichier.");
    }
    int lus = fread(tab, sizeof(Save), 1, fichier1);
    if(lus == 0){
        printf("La sauvegarde 1 est vide.\n");
    }
    else if(lus != 1){
        perror("Erreur de lecture dans le fichier.");
    }
    fclose(fichier1);

    FILE *fichier2 = fopen(save2, "rb");
    if(fichier2 == NULL){
        perror("Erreur d'ouverture du fichier.");
    }
    int lus = fread(tab + 1, sizeof(Save), 1, fichier2);
    if(lus == 0){
        printf("La sauvegarde 2 est vide.\n");
    }
    else if(lus != 1){
        perror("Erreur de lecture dans le fichier.");
    }
    fclose(fichier2);

    FILE *fichier3 = fopen(save3, "rb");
    if(fichier3 == NULL){
        perror("Erreur d'ouverture du fichier.");
    }
    int lus = fread(tab + 2, sizeof(Save), 1, fichier3);
    if(lus == 0){
        printf("La sauvegarde 3 est vide.\n");
    }
    else if(lus != 1){
        perror("Erreur de lecture dans le fichier.");
    }
    fclose(fichier3);
    return tab;
}

Save load(int n){
    Save save;
    save = getSaves()[n - 1];
    return save;
}

#endif
