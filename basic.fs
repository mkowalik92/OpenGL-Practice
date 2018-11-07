// Bare minimum fragment shader
in vec3 input_frag_color
out vec4 output_frag_color;

void main()
{
  output_frag_color = vec4(input_frag_color, 1.0f);
}
