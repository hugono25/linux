#version 400 core
in vec3 v_vertexColors;
out vec4 fragColor;

void main()
{
   fragColor = vec4(v_vertexColors.r, v_vertexColors.g, v_vertexColors.b, 1.0f);
}