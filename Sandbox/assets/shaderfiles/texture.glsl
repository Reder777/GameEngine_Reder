#type vertex
#version 330 core
layout(location=0) in vec3 a_Position;
layout(location=1) in vec2 a_TextCoord;
out vec2 v_TextCoord;
uniform mat4 m_viewProjection;
uniform mat4 m_transform;
void main(){
	v_TextCoord = a_TextCoord;
	gl_Position = m_viewProjection*m_transform*vec4(a_Position,1.0);
}

#type fragment
#version 330 core
layout(location=0) out vec4 color;
in vec2 v_TextCoord;
uniform sampler2D u_Texture;
void main() {
	color = texture(u_Texture,v_TextCoord*10)*vec4(0.5f,0.5f,0.0f,1.0f);
}