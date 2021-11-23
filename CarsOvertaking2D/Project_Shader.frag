
// Shader-ul de fragment / Fragment shader  

 #version 400

in vec4 ex_Color;
in vec2 tex_Coord;
out vec4 out_Color;

vec4 black = vec4(0.0,0.0,0.0,1.0);

uniform int codCol;
uniform sampler2D myTexture;


void main(void)
  {
	if ( codCol==0 )
		out_Color = ex_Color;
	if (codCol == 1)
	     out_Color =  texture(myTexture, tex_Coord);
    if (codCol == 2)
	     out_Color =  vec4(0.2,0.5,0.4,1.0);
  }
 