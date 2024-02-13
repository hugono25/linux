#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 ColorPos;

uniform mat4 uMatrixModel;   // position offset

out vec3 v_vertexColors;

void main()
{
   v_vertexColors = ColorPos;

   vec4 newPosition = uMatrixModel * vec4(aPos, 1.0f);

   gl_Position = vec4(newPosition.x, newPosition.y, newPosition.z, 1.0f);
}