#shader vertex
#version 330 core  
  

layout(location = 0) in vec3 position;  

out vec2 v_TexCoord;
void main()  
{  
 gl_Position = vec4(position.xyz, 1.);
 v_TexCoord  = (position.xy + 1.)*0.5;
};


// ==========================================================

#shader fragment
#version 330 core  



layout(location = 0) out vec4 color;  
uniform sampler2D fbo_texture;
in vec2 v_TexCoord;

void main()  
{  
 //   color = texture(fbo_texture, v_TexCoord);
	//color = vec4(v_TexCoord.xy, 0., 1.);
	color = vec4(1., 0.,0., 1.);
};