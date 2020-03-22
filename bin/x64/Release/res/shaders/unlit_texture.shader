#shader vertex
#version 330 core  
  

layout(location = 0) in vec3 position;  
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 vertexColor;

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
in vec2 v_TexCoord;

void main()  
{  
  color = texture(u_Texture, v_TexCoord);
};