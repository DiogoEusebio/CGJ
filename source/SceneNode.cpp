#include "../header/SceneNode.h"

namespace egn {

	SceneNode::SceneNode(SceneNode* parent_, float h)
	{
		parent = parent_;
		if (parent != nullptr)
			parent->addChild(this);
		height = h;
		color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	void SceneNode::destroy()
	{
		objmesh->destroyBufferObjects();
		shader->destroyShaderProgram();
		for (SceneNode* node : nodes)
		{
			node->destroy();
		}
	}

	void SceneNode::addChild(SceneNode* node)
	{
		nodes.push_back(node);
	}

	void SceneNode::setTranslation(vec3 v)
	{
		localTranslationVec = v;
	}
	
	void SceneNode::setScaleMatirx(mat4 matrix)
	{
		scaleMatirx = matrix;
	}
	void SceneNode::setModelMatrix(mat4 matrix)
	{
		modelMatrix = matrix;
	}
	void SceneNode::setQuaternion(qtrn q)
	{
		localQuaternion = q;
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
	void SceneNode::Draw(Camera* cam)
	{
		float colorF[4];
		color.getData(colorF);
		mat4 modelMatrix = mat4::identityMatrix();
		GLfloat glModelMatrix[16];
		mat4 viewMatrix = cam->getViewMatrix();
		GLfloat glViewMatrix[16];
		mat4 projectionMatrix = cam->getProjectionMatrix();
		GLfloat glProjectionMatrix[16];

		glUseProgram(shader->ProgramID);

		glUniform4fv(shader->Color_UID, 1, colorF);
		glUniformMatrix4fv(shader->ModelMatrix_UID, 1, GL_FALSE, modelMatrix.convertToGL(glModelMatrix));
		glUniformMatrix4fv(shader->ViewMatrix_UID, 1, GL_FALSE, viewMatrix.convertToGL(glViewMatrix));
		glUniformMatrix4fv(shader->ProjectionMatrix_UID, 1, GL_FALSE, projectionMatrix.convertToGL(glProjectionMatrix));

		objmesh->draw();

		glUseProgram(0);
		glBindVertexArray(0);
	}
}