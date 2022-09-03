#type vertex
#version 330 core
layout(location=0) in vec3 a_Position;
layout(location=1) in vec4 a_Color;
layout(location=2) in vec2 a_TextCoord;
out vec2 v_TextCoord;
out vec4 v_Color;
uniform mat4 m_viewProjection;
//uniform mat4 m_transform;
void main(){
	v_TextCoord = a_TextCoord;
	v_Color=a_Color;
	//gl_Position = m_viewProjection*m_transform*vec4(a_Position,1.0);
	gl_Position = m_viewProjection*vec4(a_Position,1.0);
}

#type fragment
#version 330 core
layout(location=0) out vec4 color;
in vec2 v_TextCoord;
in vec4 v_Color;
uniform sampler2D u_Texture;
uniform int hasTexture;
uniform vec4 m_color;
void main() {
	if(hasTexture==1){
		color = texture(u_Texture,v_TextCoord*10);
	}else{
		color=v_Color;
	}
}