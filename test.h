#ifndef TEST_H
#define TEST_H


void testAlloc(void* p, char* from){
    if(from == NULL){
        from = "information non fourni...";
    }

    if (p == NULL){
            printf("Erreur d'allocation:\nVenant de: %s", from);
            exit(41);//41 for Al-location
        }
}


void testComparison(int operation, char* from){
    if(from == NULL){
        from = "information non fourni...";
    }
    
    if (!operation){
        printf("Erreur de parametre, les données ne sont pas celles attendue:\nVenant de: %s\nVérifier bien que le test éffectuer correspond à la valeur attendue", from);
        exit(54);//54 for VA-lue
    }
}


#endif