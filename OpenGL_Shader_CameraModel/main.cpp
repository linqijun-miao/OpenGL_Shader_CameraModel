#include<glad\glad.h>
#include<gl\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"skyBox.h"
#include<iostream>
#include"Camera.h"
#include"Model.h"
#include"House.h"
#include"Shader.h"

float column[] = {
	// back face
	-1.0f, -5.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	1.0f,  5.0f, -1.0f,  0.0f,  0.0f, -1.0f, 2.0f, 10.0f, // top-right
	1.0f, -5.0f, -1.0f,  0.0f,  0.0f, -1.0f, 2.0f, 0.0f, // bottom-right         
	1.0f,  5.0f, -1.0f,  0.0f,  0.0f, -1.0f, 2.0f, 10.0f, // top-right
	-1.0f, -5.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	-1.0f,  5.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 10.0f, // top-left
	// front face
	-1.0f, -5.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	1.0f, -5.0f,  1.0f,  0.0f,  0.0f,  1.0f, 2.0f, 0.0f, // bottom-right
	1.0f,  5.0f,  1.0f,  0.0f,  0.0f,  1.0f, 2.0f, 10.0f, // top-right
	1.0f,  5.0f,  1.0f,  0.0f,  0.0f,  1.0f, 2.0f, 10.0f, // top-right
	-1.0f,  5.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 10.0f, // top-left
	-1.0f, -5.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	// left face
	-1.0f,  5.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 10.0f, // top-right
	-1.0f,  5.0f, -1.0f, -1.0f,  0.0f,  0.0f, 2.0f, 10.0f, // top-left
	-1.0f, -5.0f, -1.0f, -1.0f,  0.0f,  0.0f, 2.0f, 0.0f, // bottom-left
	-1.0f, -5.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 10.0f, // bottom-left
	-1.0f, -5.0f,  1.0f, -1.0f,  0.0f,  0.0f, 2.0f, 10.0f, // bottom-right
	-1.0f,  5.0f,  1.0f, -1.0f,  0.0f,  0.0f, 2.0f, 0.0f, // top-right
	// right face
	1.0f,  5.0f,  1.0f,  1.0f,  0.0f,  0.0f, 2.0f, 0.0f, // top-left
	1.0f, -5.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 10.0f, // bottom-right
	1.0f,  5.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // top-right         
	1.0f, -5.0f, -1.0f,  1.0f,  0.0f,  0.0f, 2.0f, 0.0f, // bottom-right
	1.0f,  5.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 10.0f, // top-left
	1.0f, -5.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
    // bottom face
	-1.0f, -5.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	1.0f, -5.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
	1.0f, -5.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	1.0f, -5.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	-1.0f, -5.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	-1.0f, -5.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	// top face
	-1.0f,  5.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	1.0f,  5.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	1.0f,  5.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
	1.0f,  5.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	-1.0f,  5.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	-1.0f,  5.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT =1100;
GLuint mid;
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float ball[] = {
	0.0f, 0.0f, 0.0f
};

float vase[] = {
	0.0f, 0.0f, 0.0f
};

unsigned int ballVAO = 0;
unsigned int ballVBO = 0;


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


unsigned int columnVAO = 0;
unsigned int columnVBO = 0;
void renderColumn()
{

	if (columnVAO == 0)
	{
		glGenVertexArrays(1, &columnVAO);
		glGenBuffers(1, &columnVBO);
		
		glBindBuffer(GL_ARRAY_BUFFER, columnVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(column), column, GL_STATIC_DRAW);
	
		glBindVertexArray(columnVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	glBindVertexArray(columnVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}


void renderBall(const Shader &shader, float radius)
{

	int uStepsNum = 20, vStepsNum = 20;
	shader.setFloat("radius", radius);
	shader.setInt("uStepsNum", uStepsNum);
	shader.setInt("vStepsNum", vStepsNum);
	if (ballVAO == 0)
	{
		glGenVertexArrays(1, &ballVAO);
		glGenBuffers(1, &ballVBO);

		glBindBuffer(GL_ARRAY_BUFFER, ballVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(ball), ball, GL_STATIC_DRAW);
	
		glBindVertexArray(ballVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	glBindVertexArray(ballVAO);
	float ustep = 1.0f / uStepsNum;
	for (int i = 0; i < uStepsNum; i++) {
		shader.setFloat("uStep", ustep*i);
		glDrawArrays(GL_POINTS, 0, 1);
	}
	glBindVertexArray(0);
}

unsigned int vaseVAO = 0;
unsigned int vaseVBO = 0;
void renderVase(const Shader &shader, float radius)
{

	int uStepsNum = 20, vStepsNum = 20;
	shader.setFloat("radius", radius);
	shader.setInt("uStepsNum", uStepsNum);
	shader.setInt("vStepsNum", vStepsNum);
	if (vaseVAO == 0)
	{
		glGenVertexArrays(1, &vaseVAO);
		glGenBuffers(1, &vaseVBO);

		glBindBuffer(GL_ARRAY_BUFFER, vaseVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vase), vase, GL_STATIC_DRAW);

		glBindVertexArray(vaseVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	glBindVertexArray(vaseVAO);
	float ustep = 1.0f / uStepsNum;
	for (int i = 0; i < uStepsNum; i++) {
		shader.setFloat("uStep", ustep*i);
		glDrawArrays(GL_POINTS, 0, 1);
	}
	glBindVertexArray(0);
}



int main() {
	

	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow *window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	glEnable(GL_DEPTH_TEST);




	Model dragon("mp_hanging/dragon.obj");
	mid = load2DTexture("mp_hanging/map.jpg");
	glm::vec3 lightPos(0.0f, 0.4f, 0.0f);

	Shader shader("shadow_mapping.vs", "shadow_mapping.fs");    //shadow
	Shader simpleDepthShader("shadow_mapping_depth.vs", "shadow_mapping_depth.fs");

	Shader shader2("shadow_mapping_g.vs", "shadow_mapping_g.fs", "geometry.gs");
	Shader simpleDepthShader2("shadow_mapping_depth_g.vs", "shadow_mapping_depth_g.fs", "geometry_depth.gs");

	Shader shader3("shadow_mapping_g.vs", "shadow_mapping_g.fs", "geometry2.gs");
	Shader shader4("shadow_mapping.vs", "shadow_mapping.fs");

	Shader ourShader("first.vs", "first.fs");
	Shader ourShader2("first.vs", "first.fs");
	Shader lightShader("first.vs", "light.fs");

	std::vector<const char*> faces;

	faces.push_back("mp_hanging/hangingstone_rt.tga");
	faces.push_back("mp_hanging/hangingstone_lf.tga");
	faces.push_back("mp_hanging/hangingstone_up.tga");
	faces.push_back("mp_hanging/hangingstone_dn.tga");
	faces.push_back("mp_hanging/hangingstone_bk.tga");
	faces.push_back("mp_hanging/hangingstone_ft.tga");

	Shader boxShader("skyBox.vs","skyBox.fs");
	skyBox* s = new skyBox(faces);
	House house;
	
	house.init();
	house.table();
	house.initOut();


	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	GLuint depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	
	GLuint depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

 

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	while (!glfwWindowShouldClose(window))
	{
	
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

	
		processInput(window);
		//*******************************************************
		
		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;




		glm::mat4 projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

	

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 model2;
		model2 = glm::translate(model, glm::vec3(0.0f, -0.86f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(0.3f, 0.01f, 0.3f));

		glm::mat4 model3;
		model3 = glm::translate(model, glm::vec3(0.0f, -0.9f, 0.0f));
		model3 = glm::scale(model3, glm::vec3(0.02f, 0.1f, 0.02f));

		glm::mat4 model4;
		model4 = glm::translate(model, glm::vec3(0.0f, -0.806f, 0.0f));
		model4 = glm::scale(model4, glm::vec3(0.1f, 0.1f, 0.1f));

		glm::mat4 model6;
		model6 = glm::translate(model, glm::vec3(0.0f, -0.830f, -0.1f));
		model6 = glm::scale(model6,glm::vec3(0.1f, 0.1f, 0.1f));

		glm::mat4 model7;
		model7 = glm::translate(model, glm::vec3(-0.1f, -0.842f, -0.1f));
		model7 = glm::scale(model7, glm::vec3(0.1f, 0.1f, 0.1f));

		glm::mat4 model8;
		model8 = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model8 = glm::scale(model8, glm::vec3(1.001f, 1.001f, 1.001f));

		glm::mat4 model9;
		
		model9 = glm::translate(model, glm::vec3(0.0f, -0.840f,-0.1f));
		model9 = glm::rotate(model9, 60.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		model9 = glm::scale(model9, glm::vec3(0.0005f, 0.008f, 0.0005f));
		

		GLfloat near_plane = 1.0f, far_plane = 7.5f;
		lightProjection = glm::perspective(glm::radians(150.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane);
		

		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;
	
		simpleDepthShader.use();
		glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader.ID, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		house.draw();

		glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model2));
		house.drawT();

		glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model3));
		house.drawT();

		glUniformMatrix4fv(glGetUniformLocation(simpleDepthShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model4));
		dragon.Draw(simpleDepthShader);

		simpleDepthShader2.use();
		renderBall(simpleDepthShader2, 0.2f);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	

		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		





		//************************************************
		// render
		// ------
		/*
	
		// don't forget to enable shader before setting uniforms
		ourShader.use();
		// view/projection transformations
	
		
		ourShader.setMat4("projection", projection);
		ourShader.setMat4("view", view);
		ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		ourShader.setVec3("lightPos", lightPos);
		ourShader.setVec3("viewPos", camera.position);

		ourShader.setVec3("material.ambient", 0.5f, 0.5f,0.5f);
		ourShader.setVec3("material.diffuse", 0.5f, 0.5f, 0.5f);
		ourShader.setVec3("material.specular", 0.5f,0.5f, 0.5f);
		ourShader.setFloat("material.shininess", 35.0f);
		ourShader.setFloat("alpha", 1.0f);
		// render the loaded model
	
		ourShader.setMat4("model", model);
		ourShader.setInt("texture_diffuse1", 0);
		house.draw();


		ourShader.setMat4("model", model2);
		house.drawT();

		
		
		ourShader.setMat4("model", model3);
		house.drawT();
		ourShader2.use();

		
		ourShader2.setMat4("projection", projection);
		ourShader2.setMat4("view", view);
		ourShader2.setMat4("model", model4);
		ourShader2.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		ourShader2.setVec3("viewPos", camera.position);
		ourShader2.setVec3("lightPos", lightPos);

		ourShader2.setVec3("material.ambient", 0.021500f, 0.174500f, 0.021500f);
		ourShader2.setVec3("material.diffuse", 0.075680f, 0.614240f, 0.075680f );
		ourShader2.setVec3("material.specular", 0.633000f, 0.727811f, 0.633000f);
		ourShader2.setFloat("material.shininess", 76.800003f);
		ourShader2.setFloat("alpha", 0.550000f);
		glEnable(GL_CULL_FACE);
		dragon.Draw(ourShader2);
		glDisable(GL_CULL_FACE);
	*/
		shader2.use();
		shader2.setMat4("projection", projection);
		shader2.setMat4("view", view);
		shader2.setVec3("viewPos", camera.position);
		shader2.setVec3("lightPos", lightPos);
		shader2.setMat4("lightSpaceMatrix", lightSpaceMatrix);
	
		shader2.setMat4("model", model6);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mid);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		shader2.setInt("shadowMap", 1);
		renderBall(shader2, 0.2f);

		shader3.use();
		shader3.setMat4("projection", projection);
		shader3.setMat4("view", view);
		shader3.setVec3("viewPos", camera.position);
		shader3.setVec3("lightPos", lightPos);
		shader3.setMat4("lightSpaceMatrix", lightSpaceMatrix);
		shader3.setMat4("model", model7);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		shader3.setInt("shadowMap", 1);
		renderVase(shader3, 0.2f);

		shader.use();

		// Set light uniforms
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
		// Enable/Disable shadows by pressing 'SPACE'

		shader.setInt("diffuseTexture", 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		shader.setInt("shadowMap", 1);

		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		shader.setVec3("lightPos", lightPos);
		shader.setVec3("viewPos", camera.position);

		shader.setVec3("material.ambient", 0.5f, 0.5f, 0.5f);
		shader.setVec3("material.diffuse", 0.5f, 0.5f, 0.5f);
		shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		shader.setFloat("material.shininess", 35.0f);
		shader.setFloat("alpha", 1.0f);

		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		house.draw();

		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model8));
		house.drawOut();

		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model2));
		house.drawT();

		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model3));
		house.drawT();

		shader.setVec3("material.ambient", 0.021500f, 0.174500f, 0.021500f);
		shader.setVec3("material.diffuse", 0.075680f, 0.614240f, 0.075680f);
		shader.setVec3("material.specular", 0.633000f, 0.727811f, 0.633000f);
		shader.setFloat("material.shininess", 76.800003f);
		shader.setFloat("alpha", 0.550000f);
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model4));
		glEnable(GL_CULL_FACE);
		dragon.Draw(shader);
		glDisable(GL_CULL_FACE);

		lightShader.use();
		glm::mat4 model5;
		model5 = glm::translate(model, glm::vec3(lightPos));
		model5 = glm::scale(model5, glm::vec3(0.1f, 0.1f, 0.1f));
		lightShader.setMat4("projection", projection);
		lightShader.setMat4("view", view);
		lightShader.setMat4("model", model5);
		house.drawT();

		shader4.use();
		shader4.setVec3("material.ambient", 0.5f, 0.5f, 0.5f);
		shader4.setVec3("material.diffuse", 0.5f, 0.5f, 0.5f);
		shader4.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		shader4.setFloat("material.shininess", 35.0f);
		shader4.setFloat("alpha", 1.0f);
		
		glActiveTexture(GL_TEXTURE1);

		glBindTexture(GL_TEXTURE_2D, depthMap);
		shader4.setInt("shadowMap", 1);
	
		shader4.setMat4("model", model9);
		shader4.setMat4("projection", projection);
		shader4.setMat4("view", view);
		shader4.setVec3("lightPos", lightPos);
		shader4.setVec3("viewPos", camera.position);
		renderColumn();


		// 然后绘制包围盒
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		boxShader.use();
		
		glm::mat4 view2 = glm::mat4(glm::mat3(view)); // 视变换矩阵 移除translate部分

		boxShader.setMat4("projection", projection);
		
		boxShader.setMat4("view", view2);
		

		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_CUBE_MAP, s->getTextId());

		boxShader.setInt("skybox", 0);
	

		s->draw(boxShader);

		

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}