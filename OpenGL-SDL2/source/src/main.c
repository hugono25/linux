#include "Window.h"
#include "lAlgebra.h"

int main(int argc, char *argv[]){

    //
    //  note: if need something to change in run time use a pointer
    //  
    Window window;      //  struct with window sdl components
    Tri tri;
    Quads quad;
    //  glm mat4 create 4x4 matrix "translate"
    //  then the function glm::translate that use a identity matrix and a v3 as parameter
    //  

    //
    /* 
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            printf("%1.f", matrix[x][y]);
        }
        printf("\n");
    }
    */
    
    sdlInit(&window);   //  funct sdl, opengl and the window
    
    //  can't use const with free
    char *vertexShaderSource = shaderRead("../source/shaders/vertexQuad.glsl");
    char *fragmentShaderSource = shaderRead("../source/shaders/fragmentQuad.glsl");
    
    //setrgbTria(&tri, vertexShaderSource, fragmentShaderSource);
    //setrgbRecta(&tri, vertexShaderSource, fragmentShaderSource);
    //sethollowTria(&tri, vertexShaderSource, fragmentShaderSource);
    setQuad(&quad, vertexShaderSource, fragmentShaderSource);

    if( vertexShaderSource == NULL){
        printf("error opening file vertex shader\n");
    }
    free(vertexShaderSource);
    
    if( vertexShaderSource == NULL){
        printf("error opening file fragment shader\n");
    }
    free(fragmentShaderSource);

    float uOffset = 0.5f;   //  uniform variable
    GLuint location;

    float **matrix;
    

    glViewport(0,0, 800, 800);
    
    bool quit = false;
    while(!quit){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
            }
        }
        //  uniform variable location
        //  must be inside the game loop
        //  
        float v3[] = {0.0f, uOffset, 0.0f};
        matrix = algTranslate(1.0f, v3);
        
        location = glGetUniformLocation(quad.shaderProg, "uMatrixModel");
        if(location >= 0){
            glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);  //  pointer to an array
        }
        else{
            printf("could not find offset\n");
            exit(EXIT_FAILURE);
        }
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_UP]){
            uOffset += 0.1;
            printf("up\n");
        }
        if(state[SDL_SCANCODE_DOWN]){
            uOffset -= 0.1;
            printf("down\n");
        }
        
        //getrgbTria(&window, &tri);    
        //getrgbRecta(&window, &tri);
        //gethollowTria(&window, &tri);
        getQuad(&window, &quad);
        //SDL_GL_SwapWindow(window.win);
    }

    for(int i = 0; i < 4; i++){
        free(matrix[i]);
    }
    free(matrix);

    openglInfo();
    //cleanrgbTria(&tri);
    //cleanrgbRecta(&tri);
    //cleanhollowTria(&tri);
    cleanQuad(&quad);
    cleanUp(&window);    
    
    return 0;
}