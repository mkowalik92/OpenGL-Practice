#version 330 core
out vec4 fragColor;
in vec3 inputColor;
in vec3 vecPos;
void main ()
{
  fragColor = vec4(vecPos, 1.0);
}
