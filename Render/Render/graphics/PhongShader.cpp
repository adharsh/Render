#include "PhongShader.h"

namespace ginkgo {

	PhongShader::PhongShader()
	{
		addVertexShader("Render/res/shaders/phongVertex.vs");
		addFragmentShader("Render/res/shaders/phongFragment.fs");
		compileShader();

		ambientLight = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
		directionalLight = DirectionalLight(BaseLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	}


	void PhongShader::updateUniforms(glm::mat4& model, glm::mat4& projectionMatrix, Texture& texture, glm::vec3& cameraPosition)
	{
		if (texture.hasImage())
			texture.bind();
		//else
		//	texture.unbind();

		setUniformMat4("model", model);
		setUniformMat4("transform", projectionMatrix);

		setUniform4f("baseColor", texture.getColor());
		setUniform4f("ambientLight", ambientLight);
		setUniform("directionalLight", directionalLight);

		setUniform1f("specularIntensity", texture.getSpecularIntensity());
		setUniform1f("specularPower", texture.getSpecularPower());

		setUniform3f("eyePos", cameraPosition);

		for (unsigned int i = 0; i < pointLights.size(); i++)
			setUniform("pointLights[" + std::to_string(i) + "]", pointLights[i]);

		//if (texture.hasImage())
		//	texture.unbind();
	}

	void PhongShader::setPointLights(const std::vector<PointLight>& pointLights)
	{
		if (pointLights.size() > MAX_POINT_LIGHTS)
		{
			std::cout << "Error: You passed in too many point lights. Max allowed is " <<
				MAX_POINT_LIGHTS << ", you passed in " << pointLights.size() << std::endl;
			system("pause");
		}
		this->pointLights = pointLights;
	}

	void PhongShader::setDirectionalLight(const DirectionalLight& directionalLight)
	{
		//DirectionalLight a = directionalLight; a.direction = glm::normalize(directionalLight.direction);
		this->directionalLight = directionalLight;
	}


	void PhongShader::setUniform(const std::string& name, BaseLight& baseLight)
	{
		setUniform4f((name + ".color").c_str(), baseLight.color);
		setUniform1f((name + ".intensity").c_str(), baseLight.intensity);
	}

	void PhongShader::setUniform(const std::string& name, DirectionalLight& directionalLight)
	{
		setUniform((name + ".base").c_str(), directionalLight.base);
		setUniform3f((name + ".direction").c_str(), directionalLight.direction);
	}

	void PhongShader::setUniform(const std::string& name, PointLight& pointLight)
	{
		setUniform((name + ".base").c_str(), pointLight.base);
		setUniform1f((name + ".attenuation.constant").c_str(), pointLight.attenuation.constant);
		setUniform1f((name + ".attenuation.linear").c_str(), pointLight.attenuation.linear);
		setUniform1f((name + ".attenuation.quadratic").c_str(), pointLight.attenuation.quadratic);
		setUniform3f((name + ".position").c_str(), pointLight.position);
	}

}