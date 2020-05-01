SettingBegin
#tagName=unlit/groundGrid
SettingEnd
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
uniform float u_iTime;
in vec2 v_TexCoord;

void main()  
{  
	float d = distance(v_TexCoord.xy, vec2(0.5, 0.5));
	      d =  exp(d*3.);
	vec2 xy = abs(fract((v_TexCoord.xy)*100.) - 0.5) ;
		 float f = smoothstep( 0.018- length(fwidth(xy))*1.5,0.02+ length(fwidth(xy)), min(xy.x, xy.y));
    vec4 texColor = mix(vec4(1., 1., 1., 1.0), vec4(1.,1.,1.,0.), f *d);
 color = texColor;
};