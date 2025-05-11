#ifndef SAVE_H
#define SAVE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int EmptyFile(const char *nomFichier) {    //If the character size in a file is empty, return 1
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

void verif_and_crea(){    //check if save files 1, 2 and 3 are created, and if not, create them
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

int saveGame(GameData data){
    char choix[15];
    int num;
    Save save;
    save.data = data;
    verif_and_crea();
    if(EmptyFile("save1.bin")){    //search an empty file between save1, save2 and save3 to save the structure containing the name and all the game data
        FILE *fichier = fopen("save1.bin", "wb");
        if(fichier == NULL){
            perror("Erreur d'ouverture du fichier.");
        }
        do{
            printf("Comment voulez-vous appelez votre sauvegarde ? (20 caractères max)\n");
            scanf("%s", save.name);
        }while(strlen(save.name) <= 0 || strlen(save.name) > 20);
        int ecrits = fwrite(&save, sizeof(Save), 1, fichier);
        if(ecrits != 1){
            perror("Erreur d'écriture dans le fichier.");
        }
        fclose(fichier);
        printf("Votre sauvegarde a eu lieu dans l'emplacement 1.\n");
        return 1;
    }

    else if(EmptyFile("save2.bin")){
        FILE *fichier = fopen("save2.bin", "wb");
        if(fichier == NULL){
            perror("Erreur d'ouverture du fichier.");
        }
        do{
            printf("Comment voulez-vous appelez votre sauvegarde ? (20 caractères max)\n");
            scanf("%s", save.name);
        }while(strlen(save.name) <= 0 || strlen(save.name) > 20);
        int ecrits = fwrite(&save, sizeof(Save), 1, fichier);
        if(ecrits != 1){
            perror("Erreur d'écriture dans le fichier.");
        }
        fclose(fichier);
        printf("Votre sauvegarde a eu lieu dans l'emplacement 2.\n");
        return 1;
    }

    else if(EmptyFile("save3.bin")){
        FILE *fichier = fopen("save3.bin", "wb");
        if(fichier == NULL){
            perror("Erreur d'ouverture du fichier.");
        }
        do{
            printf("Comment voulez-vous appelez votre sauvegarde ? (20 caractères max)\n");
            scanf("%s", save.name);
        }while(strlen(save.name) <= 0 || strlen(save.name) > 20);
        int ecrits = fwrite(&save, sizeof(Save), 1, fichier);
        if(ecrits != 1){
            perror("Erreur d'écriture dans le fichier.");
        }
        fclose(fichier);
        printf("Votre sauvegarde a eu lieu dans l'emplacement 3.\n");
        return 1;
    }

    else{  //if all saves are used, ask the user to choose between give up or overwriting on a save
        printf("Toutes les sauvegardes sont actuellement utilisées, voulez-vous ECRASER une sauvegarde ou ABANDONNER ?");
        do {
            scanf("%s", &choix);
            if(strcmp(choix, "Abandonner") == 0 || strcmp(choix, "abandonner") == 0 || strcmp(choix, "ABANDONNER") == 0){
            exit(1);
            }   
            else if(strcmp(choix, "ECRASER") == 0 || strcmp(choix, "Ecraser") == 0 || strcmp(choix, "écraser") == 0 || strcmp(choix, "ecraser") == 0){
                printf("Quelles sauvegardes voulez-vous écraser ? 1, 2 ou 3 ?\n"); //ask the number to overwriting, clean this file, and save in
                scanf("%d", &num);
                if(num == 1){
                    FILE *f = fopen("save1.bin", "wb");
                    if (f == NULL) {
                        perror("Erreur lors de l'ouverture du fichier");
                    }
                    else {
                    fclose(f);
                    }
                    saveGame(data);
                    return 1;
                }
                if(num == 2){
                    FILE *f = fopen("save2.bin", "wb");
                    if (f == NULL) {
                        perror("Erreur lors de l'ouverture du fichier");
                    }
                    else {
                    fclose(f);
                    }
                    saveGame(data);
                    return 1;
                }
                if(num == 3){
                    FILE *f = fopen("save3.bin", "wb");
                    if (f == NULL) {
                        perror("Erreur lors de l'ouverture du fichier");
                    }
                    else {
                    fclose(f);
                    }
                    saveGame(data);
                    return 1;
                }
            }
            printf("Je n'ai pas compris, voulez-vous abandonner ou écraser ?"); //loop as he doesn't tap give up or overwriting
        }while(strcmp(choix, "Abandonner") != 0 || strcmp(choix, "abandonner") != 0 || strcmp(choix, "ABANDONNER") != 0 || strcmp(choix, "ECRASER") != 0 || strcmp(choix, "Ecraser") != 0 || strcmp(choix, "écraser") != 0 || strcmp(choix, "ecraser") != 0);
    }
}

Save* getSaves(){  //takes the data from the 3 saves in an array, passing from the binary to the save structure and return the pointer of this array
    Save *tab = malloc(3 * sizeof(Save));
    FILE *fichier1 = fopen("save1.bin", "rb");
    if(fichier1 == NULL){
        perror("Erreur d'ouverture du fichier.");
    }
    int lus1 = fread(tab, sizeof(Save), 1, fichier1);
    if(lus1 == 0){
        printf("La sauvegarde 1 est vide.\n");
    }
    else if(lus1 != 1){
        perror("Erreur de lecture dans le fichier.");
    }
    fclose(fichier1);

    FILE *fichier2 = fopen("save2.bin", "rb");
    if(fichier2 == NULL){
        perror("Erreur d'ouverture du fichier.");
    }
    int lus2 = fread(tab + 1, sizeof(Save), 1, fichier2);
    if(lus2 == 0){
        printf("La sauvegarde 2 est vide.\n");
    }
    else if(lus2 != 1){
        perror("Erreur de lecture dans le fichier.");
    }
    fclose(fichier2);

    FILE *fichier3 = fopen("save3.bin", "rb");
    if(fichier3 == NULL){
        perror("Erreur d'ouverture du fichier.");
    }
    int lus3 = fread(tab + 2, sizeof(Save), 1, fichier3);
    if(lus3 == 0){
        printf("La sauvegarde 3 est vide.\n");
    }
    else if(lus3 != 1){
        perror("Erreur de lecture dans le fichier.");
    }
    fclose(fichier3);
    return tab;
}

Save load(int n){ //choose which save you want to recover on save 1, 2 or 3
    Save save;
    save = getSaves()[n - 1];
    return save;
}

#endif
