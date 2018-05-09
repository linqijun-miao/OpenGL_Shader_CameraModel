#pragma once
#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include"stb_image.h"
#include"Shader.h"
#include<vector>
class skyBox {
public:
	skyBox(std::vector<const char*> picFilePathVec) {
		skyBoxTextId = 0;
		this->setupData();
		this->skyBoxTextId = loadCubeMapTexture(picFilePathVec);
		
	}

	static  GLuint load2DTexture(const char* filename,bool alpha = false) {
		// Step1 ���������������

		GLuint textureId = 0;

		glGenTextures(1, &textureId);

		glBindTexture(GL_TEXTURE_2D, textureId);

		// Step2 �趨wrap����

		// ע������ʹ��GL_CLAMP_TO_EDGE �����Ե���ְ�͸�����Ӿ�bug

		// ��Ե���ְ�͸�� ����Ϊʹ���´��ظ�����������ֵ���µ�

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);

		// Step3 �趨filter����

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR); // ΪMipMap�趨filter����

		// Step4 ��������

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
	
	static GLuint loadCubeMapTexture(std::vector<const char*> picFilePathVec) {
		GLuint textId;

		glGenTextures(1, &textId);

		glBindTexture(GL_TEXTURE_CUBE_MAP, textId);
		int width, height, nrComponents;
		unsigned char *data = NULL;
		for (std::vector<const char*>::size_type i = 0; i < picFilePathVec.size(); ++i)
		{

			int channels = 0;
			data = stbi_load(picFilePathVec[i], &width, &height, &nrComponents, 0);
			if (data)
			{
				GLenum format;
				if (nrComponents == 1)
					format = GL_RED;
				else if (nrComponents == 3)
					format = GL_RGB;
				else if (nrComponents == 4)
					format = GL_RGBA;
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,0, format, width,height, 0,format ,GL_UNSIGNED_BYTE,data);
				stbi_image_free(data);
			}

		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		return textId;
	}

	void draw(Shader& skyboxShader) {

		GLint OldDepthFuncMode;
		glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);
		glDepthFunc(GL_LEQUAL);
		skyboxShader.use();
		glBindVertexArray(this->skyBoxVAOId);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(OldDepthFuncMode);

	}
	GLuint getTextId() const
	{
		return this->skyBoxTextId;
	}
private:
	GLuint skyBoxTextId;

	GLuint skyBoxVAOId, skyBoxVBOId;
	void setupData()

	{

		// ָ����Χ�еĶ������� λ��

		GLfloat skyboxVertices[] = {
			-1.0f, 1.0f, -1.0f,		// A
			-1.0f, -1.0f, -1.0f,	// B
			1.0f, -1.0f, -1.0f,		// C
			1.0f, -1.0f, -1.0f,		// C
			1.0f, 1.0f, -1.0f,		// D
			-1.0f, 1.0f, -1.0f,		// A

			// �����
			-1.0f, -1.0f, 1.0f,		// E
			-1.0f, -1.0f, -1.0f,	// B
			-1.0f, 1.0f, -1.0f,		// A
			-1.0f, 1.0f, -1.0f,		// A
			-1.0f, 1.0f, 1.0f,		// F
			-1.0f, -1.0f, 1.0f,		// E

			// �Ҳ���
			1.0f, -1.0f, -1.0f,		// C
			1.0f, -1.0f, 1.0f,		// G
			1.0f, 1.0f, 1.0f,		// H
			1.0f, 1.0f, 1.0f,		// H
		    1.0f, 1.0f, -1.0f,		// D
			1.0f, -1.0f, -1.0f,		// C

			// ����
			-1.0f, -1.0f, 1.0f,  // E
			-1.0f, 1.0f, 1.0f,  // F
			1.0f, 1.0f, 1.0f,  // H
			1.0f, 1.0f, 1.0f,  // H
		    1.0f, -1.0f, 1.0f,  // G
			-1.0f, -1.0f, 1.0f,  // E

			 // ����
			 -1.0f, 1.0f, -1.0f,  // A
			 1.0f, 1.0f, -1.0f,  // D
			 1.0f, 1.0f, 1.0f,  // H
			 1.0f, 1.0f, 1.0f,  // H
			 -1.0f, 1.0f, 1.0f,  // F
			 -1.0f, 1.0f, -1.0f,  // A

			  // ����
			  -1.0f, -1.0f, -1.0f,  // B
			  -1.0f, -1.0f, 1.0f,   // E
			    1.0f, -1.0f, 1.0f,    // G
				1.0f, -1.0f, 1.0f,    // G
				1.0f, -1.0f, -1.0f,   // C
			   -1.0f, -1.0f, -1.0f,  // B

		};
		glGenVertexArrays(1, &this->skyBoxVAOId);
		glGenBuffers(1, &this->skyBoxVBOId);
		glBindVertexArray(this->skyBoxVAOId);
		glBindBuffer(GL_ARRAY_BUFFER, this->skyBoxVBOId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
		// ����λ������
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(GL_FLOAT), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}
};