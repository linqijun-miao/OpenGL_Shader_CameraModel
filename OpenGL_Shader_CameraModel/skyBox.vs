#version 330 core
layout(location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;

out vec3 TextCoord;

void main()
{
	vec4 pos = projection * view * vec4(position, 1.0); // 对skybox不需要模型变换
	gl_Position = pos.xyww;  // 此处让z=w 则对应的深度值变为depth = w / w = 1.0

	TextCoord =  position;  // 当立方体中央处于原点时 立方体上位置即等价于向量

}