#pragma once
#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"stb_image.h"
#include"Shader.h"
class House
{
public:
	House() {};
	static  GLuint load2DTexture(const char* filename, bool alpha = false) {
		// Step1 创建并绑定纹理对象

		GLuint textureId = 0;

		glGenTextures(1, &textureId);

		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


																						// Step4 加载纹理

		int width, height, nrComponents;
		unsigned char *data = stbi_load(filename, &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
		return textureId;

	}
	void init() {
		GLfloat HInVertices[] = {
			// point         normal         
			//后
		-0.5f, 0.5f, -0.5f,	0.0f,  0.0f, 1.0f, 0.0f,1.0f, 	// A
		-0.5f, -1.0f, -0.5f,	0.0f,  0.0f, 1.0f, 0.0f,0.0f,// B
		0.5f, -1.0f, -0.5f,		0.0f,  0.0f, 1.0f, 1.0f,0.0f,// C
		0.5f, -1.0f, -0.5f,		0.0f,  0.0f, 1.0f,1.0f,0.0f, // C
		0.5f, 0.5f, -0.5f,		0.0f,  0.0f, 1.0f, 1.0f,1.0f,// D
		-0.5f, 0.5f, -0.5f,	0.0f,  0.0f, 1.0f, 0.0f,1.0f,	// A

		// 左侧面
		-0.5f, -1.0f, 0.5f,		1.0f,  0.0f, 0.0f,0.0f,1.0f, // E
		-0.5f, -1.0f, -0.5f,	1.0f,  0.0f, 0.0f,0.0f,0.0f,// B
		-0.5f, 0.5f, -0.5f,	1.0f,  0.0f, 0.0f,1.0f,0.0f,	// A
		-0.5f, 0.5f, -0.5f,	1.0f,  0.0f, 0.0f,	1.0f,0.0f,// A
		-0.5f, 0.5f, 0.5f,		1.0f,  0.0f, 0.0f,1.0f,1.0f,// F
		-0.5f, -1.0f, 0.5f,		1.0f,  0.0f, 0.0f,0.0f,1.0f,// E

		// 右侧面
		0.5f, -1.0f, -0.5f,		-1.0f,  0.0f, 0.0f,0.0f,1.0f,// C
		0.5f, -1.0f, 0.5f,		-1.0f,  0.0f, 0.0f,0.0f,0.0f, // G
		0.5f, 0.5f, 0.5f,		-1.0f,  0.0f, 0.0f,1.0f,0.0f,// H
		0.5f, 0.5f, 0.5f,		-1.0f,  0.0f, 0.0f,1.0f,0.0f,// H
		0.5f, 0.5f, -0.5f,		-1.0f,  0.0f, 0.0f,1.0f,1.0f,// D
		0.5f, -1.0f, -0.5f,		-1.0f,  0.0f, 0.0f,0.0f,1.0f,// C

		// 顶面
		-0.5f, 0.5f, -0.5f,  0.0f, -1.0f, 0.0f,0.0f,1.0f,// A
		0.5f, 0.5f, -0.5f,  0.0f, -1.0f, 0.0f,0.0f,0.0f, // D
		0.5f, 0.5f, 0.5f,   0.0f, -1.0f, 0.0f,1.0f,0.0f,// H
		0.5f, 0.5f, 0.5f,   0.0f, -1.0f, 0.0f, 1.0f,0.0f,// H
		-0.5f, 0.5f, 0.5f,   0.0f, -1.0f, 0.0f,1.0f,1.0f,// F
		-0.5f, 0.5f, -0.5f,   0.0f, -1.0f, 0.0f,0.0f,1.0f,// A

		 // 底面
		-0.5f, -1.0f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f,// B
		-0.5f, -1.0f, 0.5f,   0.0f, 1.0f, 0.0f,1.0f, 0.0f,// E
		0.5f, -1.0f, 0.5f,    0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// G
		0.5f, -1.0f, 0.5f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,// G
		0.5f, -1.0f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// C
		-0.5f, -1.0f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f, 1.0f // B

		};
		tid = load2DTexture("mp_hanging/qiangzhi.jpg ");
		
		glGenVertexArrays(1, &hVAOId);
		glGenBuffers(1, &hVBOId);
		// fill buffer
		glBindBuffer(GL_ARRAY_BUFFER, hVBOId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(HInVertices), HInVertices, GL_STATIC_DRAW);
		// link vertex attributes
		glBindVertexArray(hVAOId);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	
	


	}
	

	void initOut() {
		outId = load2DTexture("mp_hanging/waiqiang.jpg");

	}
	void drawOut() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, outId);
		// render Cube
		glBindVertexArray(hVAOId);
		glDrawArrays(GL_TRIANGLES, 0, 30);
		glBindVertexArray(0);
		
	}

	void table() {
		GLfloat Table[] = {
			-0.5f, 0.5f, -0.5f,	0.0f,  0.0f, 1.0f, 0.0f,1.0f, 	// A
			-0.5f, -1.0f, -0.5f,	0.0f,  0.0f, 1.0f, 0.0f,0.0f,// B
			0.5f, -1.0f, -0.5f,		0.0f,  0.0f, 1.0f, 1.0f,0.0f,// C
			0.5f, -1.0f, -0.5f,		0.0f,  0.0f, 1.0f,1.0f,0.0f, // C
			0.5f, 0.5f, -0.5f,		0.0f,  0.0f, 1.0f, 1.0f,1.0f,// D
			-0.5f, 0.5f, -0.5f,	0.0f,  0.0f, 1.0f, 0.0f,1.0f,	// A

			// 左侧面
			-0.5f, -1.0f, 0.5f,		-1.0f,  0.0f, 0.0f,0.0f,1.0f, // E
			-0.5f, -1.0f, -0.5f,	-1.0f,  0.0f, 0.0f,0.0f,0.0f,// B
			-0.5f, 0.5f, -0.5f,	-1.0f,  0.0f, 0.0f,1.0f,0.0f,	// A
			-0.5f, 0.5f, -0.5f,	-1.0f,  0.0f, 0.0f,	1.0f,0.0f,// A
			-0.5f, 0.5f, 0.5f,		-1.0f,  0.0f, 0.0f,1.0f,1.0f,// F
			-0.5f, -1.0f, 0.5f,		-1.0f,  0.0f, 0.0f,0.0f,1.0f,// E

			// 右侧面
			0.5f, -1.0f, -0.5f,		1.0f,  0.0f, 0.0f,0.0f,1.0f,// C
			0.5f, -1.0f, 0.5f,		1.0f,  0.0f, 0.0f,0.0f,0.0f, // G
			0.5f, 0.5f, 0.5f,		1.0f,  0.0f, 0.0f,1.0f,0.0f,// H
			0.5f, 0.5f, 0.5f,		1.0f,  0.0f, 0.0f,1.0f,0.0f,// H
			0.5f, 0.5f, -0.5f,		1.0f,  0.0f, 0.0f,1.0f,1.0f,// D
			0.5f, -1.0f, -0.5f,		1.0f,  0.0f, 0.0f,0.0f,1.0f,// C
			// 正面
			-0.5f, -1.0f, 0.5f,  0.0f,  0.0f, 1.0f, 0.0f,1.0f,// E
			-0.5f, 0.5f, 0.5f,  0.0f,  0.0f, 1.0f,0.0f,0.0f, // F
			0.5f, 0.5f, 0.5f, 0.0f,  0.0f, 1.0f,  1.0f,0.0f,// H
			0.5f, 0.5f, 0.5f,  0.0f,  0.0f, 1.0f,1.0f,0.0f, // H  
			0.5f, -1.0f, 0.5f,  0.0f,  0.0f, 1.0f, 1.0f,1.0f,// G
			-0.5f, -1.0f, 0.5f,  0.0f,  0.0f, 1.0f, 0.0f,1.0f,// E
			// 顶面
			-0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,0.0f,1.0f,// A
			0.5f, 0.5f, -0.5f,  0.0f, 1.0f, 0.0f,0.0f,0.0f, // D
			0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,1.0f,0.0f,// H
			0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f, 1.0f,0.0f,// H
			-0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f,1.0f,1.0f,// F
			-0.5f, 0.5f, -0.5f,   0.0f, 1.0f, 0.0f,0.0f,1.0f,// A
		};

		ttid = load2DTexture("mp_hanging/table.jpg ");

		glGenVertexArrays(1, &tVAOId);
		glGenBuffers(1, &tVBOId);
		// fill buffer
		glBindBuffer(GL_ARRAY_BUFFER, tVBOId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Table), Table, GL_STATIC_DRAW);
		// link vertex attributes
		glBindVertexArray(tVAOId);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void drawT() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ttid);
		// render Cube
		glBindVertexArray(tVAOId);
		glDrawArrays(GL_TRIANGLES, 0, 30);
		glBindVertexArray(0);
	}
	void draw() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tid);
		// render Cube
		glBindVertexArray(hVAOId);
		glDrawArrays(GL_TRIANGLES, 0, 30);
		glBindVertexArray(0);
	}
	~House() {};
	
private:
	GLuint outId;
	GLuint tid;
	GLuint ttid;
	GLuint tVAOId, tVBOId;
	GLuint hVAOId, hVBOId;
};


