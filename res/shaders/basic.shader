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
	vec4 texColor = texture(u_Texture, v_TexCoord);

	vec2 xy = fract(v_TexCoord.xy*100.);
	     xy = smoothstep(0.95, 0.97, xy);
		 float f =  1.-max(xy.x, xy.y);
		 texColor = mix(vec4(1., 1., 1., 1.0), vec4(0.,0.,0.,0.), f + u_iTime*0.0001);
 color = texColor;
};