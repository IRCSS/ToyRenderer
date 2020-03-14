#shader vertex
#version 330 core  
  

layout(location = 0) in vec4 position;  
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_MVP;
void main()  
{  
 gl_Position = u_MVP*vec4(position.xyz, 1.);
 v_TexCoord = texCoord;
};


// ==========================================================

#shader fragment
#version 330 core  



layout(location = 0) out vec4 color;  
uniform sampler2D u_Texture;
uniform float u_iTime;
in vec2 v_TexCoord;

void main()  
{  
	vec4 texColor = texture(u_Texture, fract(v_TexCoord*100.));
	vec2 xy = abs(fract((v_TexCoord.xy-0.5)*100.)) ;
		 float f = smoothstep( 0.05- length(fwidth(xy)),0.06, min(xy.x, xy.y));
		 texColor = mix(vec4(sin(u_iTime*0.002), 1., 1., 1.0), vec4(0.,0.,0.,0.), f );
 color = texColor;
};