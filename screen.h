#ifndef SCREEN_H
#define SCREEN_H

#include "header.h"
#include "vector.h"





Screen initScreen(int sizeX, int sizeY, int total_text){
    //initialise
    Screen screen;
    screen.nb_text = 0;
    screen.total_text = total_text;
    screen.text_zone = malloc(sizeof(Vector*) * screen.total_text);
    testAlloc(screen.text_zone, "initScreen(), screen.text_zone");
    for (int i = 0; i<screen.total_text; i++){
        screen.text_zone[i] = malloc(sizeof(Vector) *2);
        testAlloc(screen.text_zone[i], "initScreen(), screen.text_zone");
    }
    screen.width = sizeX+2;
    screen.height = sizeY+2;
    screen.frame = NULL;
    screen.frame = malloc(sizeof(char*)*screen.height);
    testAlloc(screen.frame, "initScreen(), screen.frame");
    for (int y = 0; y< screen.height; y++){
        screen.frame[y] = NULL;
        screen.frame[y] = malloc(screen.width);
        testAlloc(screen.frame[y], "initScreen(), screen.frame[y]");
    }
    
    
    //défini le cadre
    for(int y = 0; y<screen.height; y++){
        for(int x = 0; x<screen.width; x++){
            
            if (y==0){
                if (x==0 || x==screen.width-1){
                    screen.frame[y][x] = '+';
                }
                else{
                    screen.frame[y][x] = '-';
                }
            }
            else if(y == screen.height-1){
                if (x==0 || x==screen.width-1){
                    screen.frame[y][x] = '+';
                }
                else{
                    screen.frame[y][x] = '-';
                }
            }
            else{
                if (x==0 || x==screen.width-1){
                    screen.frame[y][x] = '|';
                } 
                else{
                    screen.frame[y][x] = ' ';
                }
            }
        }
    }
    
    return screen;
}






void clearScreen(Screen screen){
    for (int y = 1; y< screen.height-1; y++){
        for (int x = 1; x< screen.width-1; x++){
            screen.frame[y][x] = ' ';   
        }
    }
}


void freeScreen(Screen *screen){
    if(screen->text_zone != NULL){
        for (int i = 0; i<screen->total_text; i++){
            free(screen->text_zone[i]);
            screen->text_zone[i] = NULL;
        }
        free(screen->text_zone);
        screen->text_zone = NULL;
    }
    screen->total_text = 0;
    screen->nb_text = 0;
    if (screen->frame != NULL){
        for (int y = 0; y< screen->height; y++){
            if (screen->frame[y] != NULL){
                free(screen->frame[y]);
                screen->frame[y] = NULL;
            }
        }
        free(screen->frame);
        screen->frame = NULL;
    }
    
    screen->width = 0;
    screen->height = 0;
}
    
    



void display2(Screen screen){
    int is_text = 0;
    int shift_x;
    for (int y = 0; y< screen.height; y++){
        shift_x =0;
        for (int x = 0; x< screen.width; x++){
            for (int i=0; i<screen.nb_text; i++){
                if(screen.text_zone[i][0].x <= x && x <= screen.text_zone[i][1].x && screen.text_zone[i][0].y <= y && y <= screen.text_zone[i][1].y){
                    is_text=1;
                    shift_x++;
                    break;
                }
                else{
                    is_text =0;
                }
            }
            if(is_text){
                if(screen.frame[y][x] != '&'){
                    printf("%c", screen.frame[y][x]);
                }else{
                    for(int i = 0; i<shift_x+2; i++){
                        printf(" ");
                    }
                    shift_x = 0;
                }
            }else{
                for(int i = 0; i<shift_x; i++){
                    printf(" ");
                }
                shift_x = 0;
                switch (screen.frame[y][x]){
                    case '+':
                        if(x==0){
                            if (y==0){
                                printf("\u2554");
                            }
                            else if (y==screen.height-1){
                                printf("\u255A");
                            }
                            else{
                                printf("\u255F");
                            }
                        }
                        else if(x==screen.width-1){
                            if (y==0){
                                printf("\u2557");
                            }
                            else if (y==screen.height-1){
                                printf("\u255D");
                            }
                            else{
                                printf("\u2562");
                            }
                        }
                        else{
                            if (y==0){
                                printf("\u2564\u2550");
                            }
                            else if (y==screen.height-1){
                                printf("\u2567\u2550");
                            }else{
                                if(screen.frame[y-1][x] == '|' && screen.frame[y+1][x] == '|'){
                                    if(screen.frame[y][x+1] != '-'){
                                        printf("\u2524 ");
                                    }
                                    else if(screen.frame[y][x-1] != '-'){
                                        printf(" \u251C");
                                    }
                                    else{
                                        printf("\u253C\u2500");
                                    }
                                }
                                else if(screen.frame[y-1][x] != '|'){
                                    printf("\u252C\u2500");
                                }else{
                                    printf("\u2534\u2500");
                                }
                            }
                        }
                        break;
                    
                    
                    case '-':
                        if (y==0 || y== screen.height-1){
                            printf("\u2550\u2550");
                        }else{
                            printf("\u2500\u2500");
                        }
                        break;
                        
                        
                    case '|':
                        if (x==0 || x== screen.width-1){
                            printf("\u2551");
                        }else{
                            printf("\u2502 ");
                        }
                        break;
                        
                        
                    case 'c':
        				printf("\e[48;2;159;126;39m");
        				printf("\U0001f980 ");
        			    break;
        			case 'k':
        				printf("\e[48;2;248;230;49m");
        				printf("\U0001f451 ");
        			    break;
        			case 'm':
        				printf("\e[48;2;34;50;50m");
        				printf("\U0001f412 ");
        			    break;
        			case 'p':
        				printf("\e[48;2;171;135;41m");
        				printf("  ");
        			    break;
        			case 's':
        				printf("\e[48;2;223;198;65m");
        				printf("  ");
        			    break;
        			case 'S':
        				printf("\e[48;2;223;198;65m");
        				printf("\u26F1\uFE0F ");
        			    break;
        			case 'T':
        				printf("\033[42m");
        				printf("  ");
        				//printf("\U0001f333 ");
        			    break;
        			case 't':
        				printf("\e[48;2;2;131;6m");
        				printf("  ");
        				//printf("\U0001f333 ");
        			    break;
        			case 'w':
                		printf("\033[44m");
                		printf("  ");
        				//printf("\U0001f30a ");
        			    break;
                        
                    default:
                        printf(" %c", screen.frame[y][x]);
                        break;
                }
                printf("\033[0m");
            }
        }
        printf("\n");
    }
    printf("\n");
}





void frameAddChar(char c, Screen screen, int pos_x, int pos_y){
    /*On choisi un caractere a placer dans un écrant en position x et y*/
    if (pos_x<screen.width-1 && 0<pos_x && pos_y<screen.height-1 && 0<pos_y ){
        switch (c){
            case '-':
                if(screen.frame[pos_y][pos_x] == '|'){
                    screen.frame[pos_y][pos_x] = '+';
                }else{
                    screen.frame[pos_y][pos_x] = c;
                }
                break;
            case '|':
                if(screen.frame[pos_y][pos_x] == '-'){
                    screen.frame[pos_y][pos_x] = '+';
                }else{
                    screen.frame[pos_y][pos_x] = c;
                }
                break;
            default:
                screen.frame[pos_y][pos_x] = c;
                break;
        }
    }
    
    else if(c == '-' && pos_y != 0 && pos_y != screen.height-1){
        if(pos_x == 0 || pos_x == screen.width-1){
            screen.frame[pos_y][pos_x] = '+';
        }
    }else if(c == '|' && pos_x != 0 && pos_x != screen.width-1){
        if(pos_y == 0 || pos_y == screen.height-1){
            screen.frame[pos_y][pos_x] = '+';
        }
    }
}




void frameAddTabChar(char* tab, int width, Screen screen, int pos_x, int pos_y){
    /*On choisi un tableau de dimmention largeur a placer dans un écrant en position x et y*/
    for (int x = 0; x< width; x++){
        frameAddChar(tab[x], screen, pos_x+x, pos_y);
    }
}


void frameAddTabTabChar(char** tab, int width, int height, Screen screen, int pos_x, int pos_y){
    /*On choisi un tableau de tableau de dimmention largeur et hauteur a placer dans un écrant en position x et y*/
    for (int y = 0; y< height; y++){
        frameAddTabChar(tab[y], width, screen, pos_x, pos_y+y);
    }
}



void frameAddNumber(int val, Screen screen, int pos_x, int pos_y){
    testComparison(0<=val && val<100, "frameAddNumber(), val");
    int num = val%10;
    val = val/10;
    frameAddChar('0'+num, screen, pos_x+1, pos_y);
    num = val%10;
    frameAddChar('0'+num, screen, pos_x, pos_y);
}


void frameAddTextZone(Screen *screen, int start_x, int start_y, int end_x, int end_y){
    testComparison(screen->nb_text < screen->total_text, "frameAddTextZone(), screen.nb_text");
    screen->text_zone[screen->nb_text][0] = vector(start_x, start_y);
    screen->text_zone[screen->nb_text][1] = vector(end_x, end_y);
    screen->nb_text++;
}

void frameRemoveTextZone(Screen *screen, int index){
    testComparison(0 < screen->nb_text, "frameRemoveTextZone(), screen.nb_text");
    for(int i = index; i<screen->nb_text-1; i++){
        screen->text_zone[i][0] = screen->text_zone[i+1][0];
        screen->text_zone[i][1] = screen->text_zone[i+1][1];
    }
    screen->nb_text--;
}
/*
void frameAddTabVector(char c, Screen screen, Vector* vectors, int nb_vector, int shift_x, int shift_y){
    for(int i = 0; i<nb_vector; i++){
        frameAddChar(c, screen, vectors[i].x+shift_x, vectors[i].y+shift_y);
    }
}*/

void frameAddLigneChar(char c, Screen screen, int pos_y){
    int x=0;
    while(x<screen.width && screen.frame[pos_y][x+1] == ' '){
        frameAddChar(c, screen, x, pos_y);
        x++;
    }
    if(x<screen.width){
        frameAddChar(c, screen, x, pos_y);
        frameAddChar(c, screen, x+1, pos_y);
    }
}

void frameAddColumnChar(char c, Screen screen, int pos_x){
    int y=0;
    while(y<screen.height && screen.frame[y+1][pos_x] == ' '){
        frameAddChar(c, screen, pos_x, y);
        y++;
    }
    if (y<screen.height){
        frameAddChar(c, screen, pos_x, y);
        frameAddChar(c, screen, pos_x, y+1);
    }
}


#endif
