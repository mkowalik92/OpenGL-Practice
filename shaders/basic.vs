// Bare minimum vertex shader
layout (location = 0) in vec3 input_vertex;
layout (location = 1) in vec3 input_color;

out vec3 output_color;

void main()
{
  gl_Position = vec4(input_vertex, 1.0f);
  output_color = input_color;
}
