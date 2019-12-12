#shader vertex
#version 330 core  
  

layout(location = 0) in vec4 position;  
void main()  
{  
 gl_Position = position;  
};


// ==========================================================

#shader fragment
#version 330 core  

layout(location = 0) out vec4 color;  
vec4 u_iTime;

void main()  
{  
 color = vec4(1., abs(sin(u_iTime.x)),0.,1.);
};