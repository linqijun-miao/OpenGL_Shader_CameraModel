#version 330 core
layout(location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 view;

out vec3 TextCoord;

void main()
{
	vec4 pos = projection * view * vec4(position, 1.0); // ��skybox����Ҫģ�ͱ任
	gl_Position = pos.xyww;  // �˴���z=w ���Ӧ�����ֵ��Ϊdepth = w / w = 1.0

	TextCoord =  position;  // �����������봦��ԭ��ʱ ��������λ�ü��ȼ�������

}