#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 50) out;

uniform float radius;
uniform float uStep;
uniform int uStepsNum;
uniform int vStepsNum;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

out GS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} gs_out;

vec4 getPoint(float u, float v)
{
	float x = sin(3.1415926*v)*cos(6.2831853*u)*radius;
	float z = sin(3.1415926*v)*sin(6.2831853*u)*radius;
	float y = cos(3.1415926*v)*radius;
	return vec4(x, y, z,0.0);
}

vec4 getPoint2(float u, float v)
{
	float x = sin(3.1415926*v)*cos(6.2831853*u)*radius;
	float z = sin(3.1415926*v)*sin(6.2831853*u)*radius;
	float y = cos(3.1415926*v)*radius;
	return vec4(-x, 1.4142135*radius+y, -z,0.0)+normalize(vec4(x,0.0,z,0.0))*1.4142135*radius;
}

void Adraw(vec4 position)
{
	float vstep = 1.0f/vStepsNum;
	float ustep = 1.0f/uStepsNum;
	float u = 0;
	float v = 0;
	int num=3;
	
	//绘制上端三角形组
	gl_Position = projection * view * model *(position+ vec4(0.0,2*radius,0.0,0.0));
	gs_out.TexCoords=vec2(uStep,num*vstep);
	gs_out.FragPos=vec3(model * (position+ vec4(0.0,radius,0.0,0.0)));
	gs_out.FragPosLightSpace = lightSpaceMatrix * vec4(gs_out.FragPos, 1.0);
	gs_out.Normal=transpose(inverse(mat3(model)))*vec3(vec4(0.0,1,0.0,0.0));
    EmitVertex(); 
	gl_Position = projection * view * model *(position+ getPoint2(uStep, num*vstep));
	gs_out.TexCoords=vec2(uStep,num*vstep);
	gs_out.FragPos=vec3(model * (position+ getPoint2(uStep, num*vstep)));
	gs_out.FragPosLightSpace = lightSpaceMatrix * vec4(gs_out.FragPos, 1.0);
	gs_out.Normal=transpose(inverse(mat3(model)))*vec3(getPoint2(uStep, num*vstep));
    EmitVertex(); 
	gl_Position = projection * view * model *(position + getPoint2(uStep + ustep, num*vstep));
	gs_out.TexCoords=vec2(uStep + ustep, num*vstep);
	gs_out.FragPos=vec3(model * (position + getPoint2(uStep + ustep, num*vstep)));
	gs_out.FragPosLightSpace = lightSpaceMatrix * vec4(gs_out.FragPos, 1.0);
	gs_out.Normal=transpose(inverse(mat3(model)))*vec3(getPoint2(uStep + ustep, num*vstep));
	EmitVertex();
	
	//绘制中间三角形组
	u = 0, v = num*vstep;
	for (int i = num; i<(vStepsNum - 2*num); i++)
	{
		gl_Position = projection * view * model *(position + getPoint2(uStep, v + vstep));
		gs_out.TexCoords=vec2(uStep , v + vstep);
		gs_out.FragPos=vec3(model * (position + getPoint2(uStep, v + vstep)));
		gs_out.FragPosLightSpace = lightSpaceMatrix * vec4(gs_out.FragPos, 1.0);
		gs_out.Normal=transpose(inverse(mat3(model)))*vec3(getPoint2(uStep, v + vstep));
		EmitVertex();
		gl_Position = projection * view * model *(position + getPoint2(uStep + ustep, v + vstep));
		gs_out.TexCoords=vec2(uStep + ustep, v + vstep);
		gs_out.FragPos=vec3(model * (position + getPoint2(uStep + ustep, v + vstep)));
		gs_out.FragPosLightSpace = lightSpaceMatrix * vec4(gs_out.FragPos, 1.0);
		gs_out.Normal=transpose(inverse(mat3(model)))*vec3(getPoint2(uStep + ustep, v + vstep));
		EmitVertex();
		v += vstep;
	}
	
	//绘制中间三角形组
	u = 0, v = num*vstep;
	for (int i = num; i<(vStepsNum - 2*num); i++)
	{
		gl_Position = projection * view * model *(position + getPoint(uStep, v + vstep));
		gs_out.TexCoords=vec2(uStep , v + vstep);
		gs_out.FragPos=vec3(model * (position + getPoint(uStep, v + vstep)));
		gs_out.FragPosLightSpace = lightSpaceMatrix * vec4(gs_out.FragPos, 1.0);
		gs_out.Normal=transpose(inverse(mat3(model)))*vec3(getPoint(uStep, v + vstep));
		EmitVertex();
		gl_Position = projection * view * model *(position + getPoint(uStep + ustep, v + vstep));
		gs_out.TexCoords=vec2(uStep + ustep, v + vstep);
		gs_out.FragPos=vec3(model * (position + getPoint(uStep + ustep, v + vstep)));
		gs_out.FragPosLightSpace = lightSpaceMatrix * vec4(gs_out.FragPos, 1.0);
		gs_out.Normal=transpose(inverse(mat3(model)))*vec3(getPoint(uStep + ustep, v + vstep));
		EmitVertex();
		v += vstep;
	}
	gl_Position = projection * view * model *(position+ vec4(0.0,-0.5*radius,0.0,0.0));
	gs_out.TexCoords=vec2(uStep,num*vstep);
	gs_out.FragPos=vec3(model * (position+ vec4(0.0,-radius,0.0,0.0)));
	gs_out.FragPosLightSpace = lightSpaceMatrix * vec4(gs_out.FragPos, 1.0);
	gs_out.Normal=transpose(inverse(mat3(model)))*vec3(vec4(0.0,-1,0.0,0.0));
    EmitVertex(); 
	
	EndPrimitive();
}

void main() {    
	Adraw(gl_in[0].gl_Position);
}