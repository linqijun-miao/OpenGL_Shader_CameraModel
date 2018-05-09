#version 330 core
out vec4 FragColor;



struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 


in vec2 TexCoords;
in vec3 Normal;  
in vec3 FragPos;  



uniform sampler2D texture_diffuse1;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform float alpha;
void main()
{    
	
    vec3 ambient = material.ambient * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse )* lightColor;
            
      // specular
 
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular =  spec * lightColor * material.specular;  

	vec3 result = ambient + diffuse + specular;
    FragColor = texture(texture_diffuse1, TexCoords)*vec4(result,alpha) ;

}