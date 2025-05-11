#ifndef SAVE_H
#define SAVE_H

#include "header.h"


int EmptyFile(const char *nameFile) {    //If the character size in a file is empty, return 1
    FILE *f = fopen(nameFile, "rb");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1; 
    }

    fseek(f, 0, SEEK_END);       
    long length = ftell(f);     
    fclose(f);

    return (length == 0);  
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
    char choices[15];
    int num;
    Save save;
    save.data = data;
    verif_and_crea();
    if(EmptyFile("save1.bin")){    //search an empty file between save1, save2 and save3 to save the structure containing the name and all the game data
        FILE *file = fopen("save1.bin", "wb");
        if(file == NULL){
            perror("Erreur d'ouverture du fichier.");
        }
        do{
            printf("Comment voulez-vous appelez votre sauvegarde ? (20 caractères max)\n");
            scanf("%s", save.name);
        }while(strlen(save.name) <= 0 || strlen(save.name) > 20);
        int write = fwrite(&save, sizeof(Save), 1, file);
        if(write != 1){
            perror("Erreur d'écriture dans le fichier.");
        }
        fclose(file);
        return 1;
    }

    else if(EmptyFile("save2.bin")){
        FILE *file = fopen("save2.bin", "wb");
        if(file == NULL){
            perror("Erreur d'ouverture du fichier.");
        }
        do{
            printf("Comment voulez-vous appelez votre sauvegarde ? (20 caractères max)\n");
            scanf("%s", save.name);
        }while(strlen(save.name) <= 0 || strlen(save.name) > 20);
        int write = fwrite(&save, sizeof(Save), 1, file);
        if(write != 1){
            perror("Erreur d'écriture dans le fichier.");
        }
        fclose(file);
        return 1;
    }

    else if(EmptyFile("save3.bin")){
        FILE *file = fopen("save3.bin", "wb");
        if(file == NULL){
            perror("Erreur d'ouverture du fichier.");
        }
        do{
            printf("Comment voulez-vous appelez votre sauvegarde ? (20 caractères max)\n");
            scanf("%s", save.name);
        }while(strlen(save.name) <= 0 || strlen(save.name) > 20);
        int write = fwrite(&save, sizeof(Save), 1, file);
        if(write != 1){
            perror("Erreur d'écriture dans le fichier.");
        }
        fclose(file);
        return 1;
    }

    else{  //if all saves are used, ask the user to choose between give up or overwriting on a save
        printf("Toutes les sauvegardes sont actuellement utilisées, voulez-vous ECRASER une sauvegarde ou ABANDONNER ?");
        do {
            scanf("%s", choices);
            if(strcmp(choices, "Abandonner") == 0 || strcmp(choices, "abandonner") == 0 || strcmp(choices, "ABANDONNER") == 0){
            exit(1);
            }   
            else if(strcmp(choices, "ECRASER") == 0 || strcmp(choices, "Ecraser") == 0 || strcmp(choices, "écraser") == 0 || strcmp(choices, "ecraser") == 0){
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
        }while(strcmp(choices, "Abandonner") != 0 && strcmp(choices, "abandonner") != 0 && strcmp(choices, "ABANDONNER") != 0 && strcmp(choices, "ECRASER") != 0 && strcmp(choices, "Ecraser") != 0 && strcmp(choices, "écraser") != 0 && strcmp(choices, "ecraser") != 0);
    }
}

Save* getSaves(){  //takes the data from the 3 saves in an array, passing from the binary to the save structure and return the pointer of this array
    Save *tab = malloc(3 * sizeof(Save));
    FILE *file1 = fopen("save1.bin", "rb");
    if(file1 == NULL){
        strcpy(tab->name, "Vide");
    } 
    else {
        int read1 = fread(tab, sizeof(Save), 1, file1);
        if(read1 != 0 && read1 != 1){
            perror("Erreur de lecture dans le fichier.");
        }
    }
    fclose(file1);
    FILE *file2 = fopen("save2.bin", "rb");
    if(file2 == NULL){
        strcpy((tab + 1)->name, "Vide");
    } 
    else {
        int read2 = fread(tab + 1, sizeof(Save), 1, file2);
        if(read2 != 0 && read2 != 1){
            perror("Erreur de lecture dans le fichier.");
        }
    }
    fclose(file2);
    FILE *file3 = fopen("save3.bin", "rb");
    if(file3 == NULL){
        strcpy((tab + 2)->name, "Vide");
    } 
    else {
        int read3 = fread(tab + 2, sizeof(Save), 1, file3);
        if(read3 != 0 && read3 != 1){
            perror("Erreur de lecture dans le fichier.");
        }
    }
    fclose(file1);
    return tab;
}


#endif
