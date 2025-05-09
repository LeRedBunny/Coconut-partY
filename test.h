#ifndef TEST_H
#define TEST_H


void testAlloc(void* p, char* from){
    if(from == NULL){
        from = "information non fourni...";
    }

    if (p == NULL){
            printf("Allocation error:\nFROM: %s", from);
            exit(4110);//4110 for AllO-cation
        }
}


#endif