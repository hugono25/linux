#include <stdio.h>
#include <stdlib.h>     //  malloc,...
#include <stdbool.h>
#include <math.h>
#include "glad.h"
#include <SDL2/SDL.h>

#include "cglm/cglm.h"
#include "cglm/vec3.h"
#include "cglm/mat4.h"


#ifndef WINDOW_H
#define WINDOW_H
//  struct with the components of opengl
typedef struct {
    GLuint VAO, VAO2;
    GLuint VBO, VBO2;
    GLuint EBO;

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProg;

    const char *vertexShaderSource;   //  max_lines, max_rows
    const char *fragmentShaderSource; //  store the shaders source

    GLuint shaderCompiled;
    GLuint programCompiled;
    GLchar message[512];

} Tri;

typedef struct {
    GLuint VAO, VAO2;
    GLuint VBO, VBO2;
    GLuint EBO, EBO2;

    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProg;

    const char *vertexShaderSource;   //  max_lines, max_rows
    const char *fragmentShaderSource; //  store the shaders source

    GLuint shaderCompiled;
    GLuint programCompiled;
    GLchar message[512];

} Quads;

//  struct with the component of sdl
typedef struct {

    SDL_Window *win;
    SDL_GLContext context;
    
} Window;
//  note: about the structs, cannot declare the variable inside the struct
//  only variables that can are goind to be defined


void sdlInit(Window *window);         //  init sdl, window and opengl

char *shaderRead(char *filename);

//  rgb triangle
void setrgbTria(Tri *tri, const char *vertexShaderSource, const char *fragmentShaderSource);
void getrgbTria(Window *window,Tri *tri);
void cleanrgbTria(Tri *tri);

//  rgb rectangle
void setrgbRecta(Tri *tri, const char *vertexShaderSource, const char *fragmentShaderSource);
void getrgbRecta(Window *window,Tri *tri);   
void cleanrgbRecta(Tri *tri);

//  rgb triangle with a hollow triangle in the middle
void sethollowTria(Tri *tri, const char *vertexShaderSource, const char *fragmentShadeSource);
void gethollowTria(Window *window, Tri *tri);
void cleanhollowTria(Tri *tri);

//  rgb rectangle with x,y pos and width,height parameters
void setQuad(Quads *quad, const char *vertexShaderSource, const char *fragmentShadeSource);
void getQuad(Window *window, Quads *quad);
void cleanQuad(Quads *quad);


void openglInfo();                    //  opengl informationS
void cleanUp(Window *window);         //  destroy window and exit sdl

#endif  //  WINDOW_H