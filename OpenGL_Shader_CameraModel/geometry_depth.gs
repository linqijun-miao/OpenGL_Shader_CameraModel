#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 50) out;

uniform float radius;
uniform float uStep;
uniform int uStepsNum;
uniform int vStepsNum;
uniform mat4 lightSpaceMatrix;
uniform mat4 model;

vec4 getPoint(float u, float v)
{
	float x = sin(3.1415926*v)*cos(6.2831853*u)*radius;
	float z = sin(3.1415926*v)*sin(6.2831853*u)*radius;
	float y = cos(3.1415926*v)*radius;
	return vec4(x, y, z,0.0);
}

void Adraw(vec4 position)
{
	float vstep = 1.0f/vStepsNum;
	float ustep = 1.0f/uStepsNum;
	float u = 0;
	float v = 0;

	//绘制上端三角形组
	gl_Position = lightSpaceMatrix * model * (position+ getPoint(0, 0));
    EmitVertex(); 
	gl_Position = lightSpaceMatrix * model * (position+ getPoint(uStep, vstep));
    EmitVertex(); 
	gl_Position = lightSpaceMatrix * model * (position + getPoint(uStep + ustep, vstep));
	EmitVertex();
	
	//绘制中间三角形组
	u = 0, v = vstep;
	for (int i = 1; i<vStepsNum - 1; i++)
	{
		gl_Position = lightSpaceMatrix * model * (position + getPoint(uStep, v + vstep));
		EmitVertex();
		gl_Position = lightSpaceMatrix * model * (position + getPoint(uStep + ustep, v + vstep));
		EmitVertex();
		v += vstep;
	}
	
	//绘制下端三角形组
	gl_Position = lightSpaceMatrix * model * (position + getPoint(0, 1));
    EmitVertex();
	
	EndPrimitive();
}

void main() {    
	Adraw(gl_in[0].gl_Position);
}