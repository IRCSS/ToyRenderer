SettingBegin
#tagName=skybox/procedural
SettingEnd
#shader vertex
#version 330 core  
  

layout(location = 0) in vec3 position;  

out vec3 v_TexCoords;
uniform mat4 u_MVP;
void main()  
{  
	v_TexCoords = position.xyz;
	vec4 pos = u_MVP * vec4(position.xyz, 1.);
	gl_Position = vec4(pos.xyww);

};


// ==========================================================

#shader fragment
#version 330 core  



layout(location = 0) out vec4 color;  
in vec3 v_TexCoords;

uniform vec4 _TopColor;
uniform vec4 _HorizonColor;
uniform vec4 _SunVector;
uniform vec4 _SunDecay;

void main()  
{  
	vec3 dir = normalize(v_TexCoords.xyz);
	float  f = clamp((exp(-dir.y *1.5)),0.,1.);

	float sun = smoothstep(0.995,0.998,-dot(dir, _SunVector.xyz));
    float MIE = clamp((exp(-dot(dir.xyz, _SunVector.xyz)*0.6+0.01)*0.24), 0.0, 1.0);
	
	color = ( _TopColor * (1.0 - f) + _HorizonColor * f+ sun * _SunDecay)+ MIE;
	 
};