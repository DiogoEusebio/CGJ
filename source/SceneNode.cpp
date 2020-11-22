#include "../header/SceneNode.h"

namespace egn {

	SceneNode::SceneNode(SceneNode* parent_, float h)
	{
		parent = parent_;
		if (parent != nullptr)
			parent->addChild(this);
		height = h;
		totalMatrix = mat4::identityMatrix();
		scaleMatrix = mat4::identityMatrix();
		color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	void SceneNode::destroy()
	{
		objmesh->destroyBufferObjects();
		shader->destroyShaderProgram();
		for (SceneNode* child : childs)
		{
			child->destroy();
		}
	}

	void SceneNode::addChild(SceneNode* node)
	{
		childs.push_back(node);
	}

	void SceneNode::setTranslation(vec3 v)
	{
		initialTranslationVector = v;
	}

	void SceneNode::setAnimationTranslation(vec3 v)
	{
		finalTranslationVector = v;
	}
	
	void SceneNode::setScaleMatrix(mat4 matrix)
	{
		scaleMatrix = matrix;
	}
	void SceneNode::setModelMatrix(mat4 matrix)
	{
		modelMatrix = matrix;
	}
	void SceneNode::setQuaternion(qtrn q)
	{
		initialQuaternion = q;
	}
	void SceneNode::setAnimationQuaternion(qtrn q)
	{
		finalQuaternion = &q;
	}

	void SceneNode::setColor(vec4 c)
	{
		color = c;
	}
	void SceneNode::setMesh(mesh* m)
	{
		objmesh = m;
	}
	mesh* SceneNode::getMesh()
	{
		return objmesh;
	}
	void SceneNode::setShader(Shader* s)
	{
		shader = s;
	}
	Shader* SceneNode::getShader()
	{
		return shader;
	}
	void SceneNode::Draw(Camera* cam, float delta)
	{
		float colorF[4];
		color.getData(colorF);
		GLfloat glModelMatrix[16];
		mat4 viewMatrix = cam->getViewMatrix();
		GLfloat glViewMatrix[16];
		mat4 projectionMatrix = cam->getProjectionMatrix();
		GLfloat glProjectionMatrix[16];
		vec3 currentPosition;
		qtrn currentQuaternion;

		if (finalTranslationVector != NULL)
		{
			currentPosition = vec3::lerp(initialTranslationVector, finalTranslationVector, delta);
		}
		else
		{
			currentPosition = initialTranslationVector;
		}
		if (finalQuaternion != NULL)
		{
			currentQuaternion = qSlerp(*finalQuaternion, initialQuaternion, delta);
		}
		else
		{
			currentQuaternion = initialQuaternion;
		}

		if (parent != nullptr) {
			totalMatrix = parent->totalMatrix * mat4::translationMatrix(currentPosition);
		}
		else {
			totalMatrix = mat4::translationMatrix(currentPosition);
		}
		modelMatrix = totalMatrix * scaleMatrix;
		glUseProgram(shader->ProgramID);

		glUniform4fv(shader->Color_UID, 1, colorF);
		glUniformMatrix4fv(shader->ModelMatrix_UID, 1, GL_FALSE, modelMatrix.convertToGL(glModelMatrix));
		glUniformMatrix4fv(shader->ViewMatrix_UID, 1, GL_FALSE, viewMatrix.convertToGL(glViewMatrix));
		glUniformMatrix4fv(shader->ProjectionMatrix_UID, 1, GL_FALSE, projectionMatrix.convertToGL(glProjectionMatrix));

		objmesh->draw();

		glUseProgram(0);
		glBindVertexArray(0);

		for (SceneNode* child : childs) {
			child->Draw(cam, delta);
		}
	}

	void SceneNode::translate(vec3 v)
	{
		initialTranslationVector += v;
		if (finalTranslationVector != NULL)
		{
			finalTranslationVector += v;
		}
	}
}