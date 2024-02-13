#include "Window.h"

void sdlInit(Window *window){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("error init sdl \n%s", SDL_GetError());
    }
    //  before creating a window
    //  init version 4.0 of opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
    window->win = SDL_CreateWindow("opengl",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    800,
                                    800,
                                    SDL_WINDOW_OPENGL);

    if(!window->win){
        printf("error init window->\n%s", SDL_GetError());
    }

    //  after window->    //  init glad
    window->context = SDL_GL_CreateContext(window->win);
    gladLoadGLLoader(SDL_GL_GetProcAddress);

    
}

void openglInfo(){
    //  opengl information
    printf("Vender: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));
    printf("Shading Language: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    
}

void cleanUp(Window *window){
        
    SDL_DestroyWindow(window->win);
    SDL_Quit();

}
//  reads the files and stores the vertex shader source and the fragment shader source
char *shaderRead(char *filename){
    
    FILE *file;

    file = fopen(filename, "r");
    //vertexshaderSource = fopen("../source/shaders/vertexTriangle.glsl", "r");
    
    if( file == NULL){
        return NULL;
    }

    fseek(file, 0, SEEK_END);   //  moves the file pointer to the end of the file
    int length = ftell(file);   //  current position of the file
    fseek(file, 0, SEEK_SET);   //  moves the file pointer to the begining of the file

    char *string = malloc(sizeof(char) * (length+1));   //  +1 to include the NULL terminator

    char c;
    int i = 0;

    while((c = fgetc(file)) != EOF){    //  read every char and stores in 'c' until return EOF(end of the file)
        string[i] = c;
        i++;
    }
    string[i] = '\0';   //  add NULL terminator at the end

    fclose(file);

    return string; 
    
    //vertexshaderSource = fopen("../source/shaders/fragmentTriangle.glsl", "r");

}

/*************************************RGB Triangle*****************************/

void setrgbTria(Tri *tri, const char *vertexShaderSource, const char *fragmentShaderSource){

    //  vertex shader
    tri->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(tri->vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(tri->vertexShader);

    glGetShaderiv(tri->vertexShader, GL_COMPILE_STATUS, &tri->shaderCompiled);
    if(tri->shaderCompiled != GL_TRUE){
        glGetShaderInfoLog(tri->vertexShader, 512, NULL, tri->message);
        printf("error vertex shader%s\n", tri->message);
    }

    //  fragment shader
    tri->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(tri->fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(tri->fragmentShader);

    glGetShaderiv(tri->fragmentShader, GL_COMPILE_STATUS, &tri->shaderCompiled);
    if(tri->shaderCompiled != GL_TRUE){
        glGetShaderInfoLog(tri->fragmentShader, 512, NULL, tri->message);
        printf("error fragment shader%s\n", tri->message);
    }

    //  shader program
    tri->shaderProg = glCreateProgram();
    glAttachShader(tri->shaderProg ,tri->vertexShader);
    glAttachShader(tri->shaderProg, tri->fragmentShader);
    glLinkProgram(tri->shaderProg);

    glGetProgramiv(tri->shaderProg, GL_LINK_STATUS, &tri->shaderCompiled);
    if(tri->shaderCompiled != GL_TRUE){
        glGetProgramInfoLog(tri->shaderProg, 512, NULL, tri->message);
        printf("error program shader\n%s", tri->message);
    }
    glDeleteShader(tri->vertexShader);
    glDeleteShader(tri->fragmentShader);

    // triangle coordenates
    GLfloat vertices[] = {
        -0.8f, -0.4f, 0.0f,
        0.0f, 0.6f, 0.0f,
        0.8f, -0.4f, 0.0f
    };

    //  triangle colors
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    //  vertex array objects and vertex buffer object
    //  triangle position
    glGenVertexArrays(1, &tri->VAO);    
    glGenBuffers(1, &tri->VBO);     //  position buffer
    glGenBuffers(1, &tri->VBO2);    //  colors buffer

    glBindVertexArray(tri->VAO);
    
    //  position
    glBindBuffer(GL_ARRAY_BUFFER, tri->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    //  color
    glBindBuffer(GL_ARRAY_BUFFER, tri->VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //  unbind position objects
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    //  disable VAO
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}
//  draw and paint the triangle
void getrgbTria(Window *window, Tri *tri){

    glClearColor(1.0f, 0.5f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(tri->shaderProg);
    glBindVertexArray(tri->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(window->win);
}

void cleanrgbTria(Tri *tri){
    glDeleteVertexArrays(1, &tri->VAO);
    glDeleteBuffers(1, &tri->VBO);
    glDeleteBuffers(1, &tri->VBO2);
    glDeleteProgram(tri->shaderProg);
}
/*************************************RGB Triangle*****************************/
/////////////////////
/*************************************RGB Rectangle****************************/

//  note: make the size of the quad modifiable as an input parameter

void setrgbRecta(Tri *tri, const char *vertexShaderSource, const char *fragmentShaderSource){
    //  vertex shader
    tri->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(tri->vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(tri->vertexShader);

    glGetShaderiv(tri->vertexShader, GL_COMPILE_STATUS, &tri->shaderCompiled);
    if(tri->shaderCompiled != GL_TRUE){
        glGetShaderInfoLog(tri->vertexShader, 512, NULL, tri->message);
        printf("error vertex shader\n%s", tri->message);
    }

    //  fragment shader
    tri->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(tri->fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(tri->fragmentShader);

    glGetShaderiv(tri->fragmentShader, GL_COMPILE_STATUS, &tri->shaderCompiled);
    if(tri->shaderCompiled != GL_TRUE){
        glGetShaderInfoLog(tri->fragmentShader, 512, NULL, tri->message);
        printf("error fragment shader\n%s", tri->message);
    }

    //  shader program
    tri->shaderProg = glCreateProgram();
    glAttachShader(tri->shaderProg, tri->vertexShader);
    glAttachShader(tri->shaderProg, tri->fragmentShader);
    glLinkProgram(tri->shaderProg);

    glGetProgramiv(tri->shaderProg, GL_LINK_STATUS, &tri->shaderCompiled);
    if(tri->shaderCompiled != GL_TRUE){
        glGetProgramInfoLog(tri->shaderProg, 512, NULL, tri->message);
        printf("error shader program\n%s", tri->message);
    }

    glDeleteShader(tri->vertexShader);  
    glDeleteShader(tri->fragmentShader);

    //  coordenates and color
    GLfloat verticesColor[] = {
        //  0 - vertex
        -0.4f, -0.4f, 0.0f,     //  left point
        1.0f, 0.f, 0.0f,        //  color
        //  1 - vertex
        0.4f, -0.4f, 0.0f,      //  right point
        0.0f, 1.0f, 0.0f,       //  color
        //  2 - vertex
        -0.4f, 0.4f, 0.0f,     //  top point
        0.0f, 0.0f, 1.0f,        //  color
        //  3 - vertex
        //  the order of the point coodinates depends of the clock direction
        0.4f, 0.4f, 0.0f,      //  top right point
        1.0f, 0.0f, 0.0f        //  color
    };

    GLint indeces[] = {
        2, 0, 1,
        1, 3, 2
    };
    //  vertex objects
    glGenVertexArrays(1, &tri->VAO);
    glGenBuffers(1, &tri->VBO);    
    //  element buffer
    glGenBuffers(1, & tri->EBO);    

    glBindVertexArray(tri->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, tri->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColor), verticesColor, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

    //  position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6,(GLvoid*)0);
    glEnableVertexAttribArray(0);

    //  color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6,(GLvoid*)(sizeof(GL_FLOAT) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

void getrgbRecta(Window *window, Tri *tri){

    glClearColor(1.0f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(tri->shaderProg);
    glBindVertexArray(tri->VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    SDL_GL_SwapWindow(window->win);
}

void cleanrgbRecta(Tri *tri){

    glDeleteBuffers(1, &tri->VBO);
    glDeleteBuffers(1, &tri->EBO);
    glDeleteVertexArrays(2, &tri->VAO);
    glDeleteProgram(tri->shaderProg);

}

/*************************************RGB Rectangle****************************/

/*************************************Hollow Triangle**************************/

void sethollowTria(Tri *tri, const char *vertexShaderSource, const char *fragmentShaderSource){
    //  vertex shader
    tri->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(tri->vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(tri->vertexShader);

    glGetShaderiv(tri->vertexShader, GL_COMPILE_STATUS, &tri->shaderCompiled);

    if(tri->shaderCompiled != GL_TRUE){
        glGetShaderInfoLog(tri->vertexShader, 512, NULL, tri->message);
        printf("error vertex shader\n%s", tri->message);
    }
    //  fragment shader
    tri->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(tri->fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(tri->fragmentShader);

    glGetShaderiv(tri->fragmentShader, GL_COMPILE_STATUS, &tri->shaderCompiled);

    if(tri->shaderCompiled != GL_TRUE){
        glGetShaderInfoLog(tri->fragmentShader, 512, NULL, tri->message);
        printf("error fragment shader\n%s", tri->message);
    }

    //  shader program
    tri->shaderProg = glCreateProgram();
    glAttachShader(tri->shaderProg, tri->vertexShader);
    glAttachShader(tri->shaderProg, tri->fragmentShader);
    glLinkProgram(tri->shaderProg);

    glGetProgramiv(tri->shaderProg, GL_LINK_STATUS, &tri->programCompiled);
    if(tri->programCompiled != GL_TRUE){
        glGetProgramInfoLog(tri->shaderProg, 512, NULL, tri->message);
        printf("error shader program\n%s", tri->message);
    }

    glDeleteShader(tri->vertexShader);
    glDeleteShader(tri->fragmentShader);

    //  coordenates and color
    //  coordenates ordes is important first the points of the big triangle
    //  later the smaller triangles
    GLfloat verticesColor[] = {
        -0.6f, -0.4f, 0.0f,
        1.0f, 0.0f, 0.0f,       //  color
        
        0.6f, -0.4f, 0.0f,
        0.0f, 1.0f, 0.0f,       //  color
       
        0.0f, 0.6f, 0.0f,
        0.0f, 0.0f, 1.0f,       //  color

        -0.3f, 0.1f, 0.0f,
        0.0f, 1.0f, 0.0f,
        
        0.0f, -0.4f, 0.0f,
        0.0f, 0.0f, 1.0f,
        
        0.3f, 0.1f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    
    GLint indices[] = {
        3, 0, 4,
        4, 1, 5,
        5, 2, 3
    };
    //  vertex objects
    glGenVertexArrays(1, &tri->VAO);
    glGenBuffers(1, &tri->VBO);
    glGenBuffers(1, &tri->EBO);

    glBindVertexArray(tri->VAO);
    
    //  position and color buffer
    glBindBuffer(GL_ARRAY_BUFFER, tri->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColor), verticesColor, GL_STATIC_DRAW);

    //  indices buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tri->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //  position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (GLvoid*)0);   //  start a void*0 and pass every 6 floats
    glEnableVertexAttribArray(0);

    //  color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)* 6, (GLvoid*)(sizeof(GL_FLOAT) * 3));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

void gethollowTria(Window *window, Tri *tri){
    glClearColor(1.0f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(tri->shaderProg);
    glBindVertexArray(tri->VAO);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    SDL_GL_SwapWindow(window->win);
}

void cleanhollowTria(Tri *tri){
    glDeleteBuffers(1, &tri->VBO);
    glDeleteBuffers(1, &tri->EBO);
    glDeleteProgram(tri->shaderProg);
    glDeleteVertexArrays(2, &tri->VAO);
}

/*************************************Hollow Triangle**************************/

/*************************************Textured Quad****************************/

void setQuad(Quads *quad, const char *vertexShaderSource, const char *fragmentShaderSource){
    //  vertex shader
    quad->vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(quad->vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(quad->vertexShader);

    glGetShaderiv(quad->vertexShader, GL_COMPILE_STATUS, &quad->shaderCompiled);
    if(quad->shaderCompiled != GL_TRUE){
        glGetShaderInfoLog(quad->vertexShader, 512, NULL, quad->message);
        printf("error vertex shader\n%s", quad->message);
    }

    //  fragment shader
    quad->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(quad->fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(quad->fragmentShader);

    glGetShaderiv(quad->fragmentShader, GL_COMPILE_STATUS, &quad->shaderCompiled);
    if(quad->shaderCompiled != GL_TRUE){
        glGetShaderInfoLog(quad->fragmentShader, 512, NULL, quad->message);
        printf("error fragment shader\n%s", quad->message);
    }

    //  shader program
    quad->shaderProg = glCreateProgram();
    glAttachShader(quad->shaderProg, quad->vertexShader);
    glAttachShader(quad->shaderProg, quad->fragmentShader);
    glLinkProgram(quad->shaderProg);

    glGetProgramiv(quad->shaderProg, GL_LINK_STATUS, &quad->shaderCompiled);
    if(quad->shaderCompiled != GL_TRUE){
        glGetProgramInfoLog(quad->shaderProg, 512, NULL, quad->message);
        printf("error shader program\n%s", quad->message);
    }

    glDeleteShader(quad->vertexShader);  
    glDeleteShader(quad->fragmentShader);
   
    //  quad coordinates
    GLfloat quadCoordinates[] = {
        -0.5f, -0.5f, 0.0f,     //  vertex - 0
        1.0f, 0.0f, 0.0f,       //  color
        0.5f, -0.5f, 0.0f,      //  vertex - 1
        0.0f, 1.0f, 0.0f,       //  color
        -0.5f, 0.5f, 0.0f,      //  vertex - 2
        0.0f, 0.0f, 1.0f,       //  color
        0.5f, 0.5f, 0.0f        //  vertex - 3

    };

    //  quad index
    GLint quadIndices[] = {
        2, 0, 1,
        1, 3, 2
    };

    //  vertex objects
    glGenVertexArrays(1, &quad->VAO);
    glGenBuffers(1, &quad->VBO);    
    //  element buffer
    glGenBuffers(1, & quad->EBO);    

    glBindVertexArray(quad->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, quad->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadCoordinates), quadCoordinates, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    //  position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6,(GLvoid*)0);
    glEnableVertexAttribArray(0);

    //  color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6,(GLvoid*)(sizeof(GL_FLOAT) * 3));
    glEnableVertexAttribArray(1);

    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    //  quad coordinates
    GLfloat quadCoordinates2[] = {
        -1.0f, -0.6f, 0.0f,     //  vertex - 0
        1.0f, 0.0f, 0.0f,       //  color
        -0.6f, -0.6f, 0.0f,     //  vertex - 1
        0.0f, 1.0f, 0.0f,       //  color
        -1.0f, -0.2f, 0.0f,      //  vertex - 2
        0.0f, 0.0f, 1.0f,       //  color
        -0.6f, -0.2f, 0.0f        //  vertex - 3
    };

    //  quad index
    GLint quadIndices2[] = {
        2, 0, 1,
        1, 3, 2
    };

        //  vertex objects
    glGenVertexArrays(1, &quad->VAO2);
    glGenBuffers(1, &quad->VBO2);    
    //  element buffer
    glGenBuffers(1, & quad->EBO2);    

    glBindVertexArray(quad->VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, quad->VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadCoordinates2), quadCoordinates2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad->EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices2), quadIndices2, GL_STATIC_DRAW);

    //  position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6,(GLvoid*)0);
    glEnableVertexAttribArray(0);

    //  color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6,(GLvoid*)(sizeof(GL_FLOAT) * 3));
    glEnableVertexAttribArray(1);

    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
   
}

void getQuad(Window *window, Quads *quad){

    glClearColor(1.0f, 0.3f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(quad->shaderProg);
    glBindVertexArray(quad->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(quad->VAO2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    SDL_GL_SwapWindow(window->win);
}

void cleanQuad(Quads *quad){

    glDeleteBuffers(1, &quad->VBO);
    glDeleteBuffers(1, &quad->EBO);
    glDeleteVertexArrays(2, &quad->VAO);

    glDeleteBuffers(1, &quad->VBO2);
    glDeleteBuffers(1, &quad->EBO2);
    glDeleteVertexArrays(2, &quad->VAO2);
    glDeleteProgram(quad->shaderProg);

}
/*************************************Textured Quad****************************/






