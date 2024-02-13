#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 ColorPos;

uniform float uOffset;  // uniform variable
uniform float uOffsetX; // uniform variable

out vec3 v_vertexColors;

void main()
{
   v_vertexColors = ColorPos;
   gl_Position = vec4(aPos.x + uOffsetX, aPos.y + uOffset, aPos.z, 1.0f);
}