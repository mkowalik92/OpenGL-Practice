#version 330 core
out vec4 fragColor;
in vec3 inputColor;
in vec3 vecPos;
void main ()
{
  // Uses vertex position as color value
  fragColor = vec4(vecPos, 1.0);
}
