#type vertex
#version 330 core
layout(location=0) in vec3 a_Position;
uniform mat4 m_viewProjection;
uniform mat4 m_transform;
void main(){
	gl_Position = m_viewProjection*m_transform*vec4(a_Position,1.0);
}	

#type fragment
#version 330 core
layout(location=0) out vec4 color;
uniform vec3 m_color;
void main() {
	color = vec4( m_color, 1.0);
}