#include "lAlgebra.h"

float **algTranslate(float val, float v3[]){
    
    float **matrix;
    //  allocates row memory
    matrix = malloc(sizeof(int *) * 4);     //  row
    //  allocates columns memory
    for(int c = 0; c < 4; c++){
        matrix[c] = malloc(sizeof(float * ) * 4);  //  columns
    }

    //  give values to memory
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            if(x == y){
                matrix[x][y] = val;
            }
            else if(x == 3 && y < 2){
                matrix[x][y] = val * v3[y];
            }
            else{
                matrix[x][y] = 0.0f;
            }
        }
    }

    return matrix;
}

void algTrans(float val, float v3[], float result[]){
    //  give values to memory
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            if(x == y){
                result[y] = val;
            }
            else{
                result[y] = 0.0f;
            }
        }
    }
    
}

void *algTransla(float val, float v3[], float *matrix){

    
        for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            if(x == y){
                matrix[y] = val;
            }
            else{
                matrix[y] = v3[y];
            }
        }
    }
    
}