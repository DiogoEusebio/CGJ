#pragma once
#include "Matrix.h"
#include "Quaternion.h"
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"
#include <vector>

namespace egn {
	class SceneNode {
	protected:
		SceneNode* parent;
		Shader* shader;
		mat4 modelMatrix;
		mat4 scaleMatrix;
		mat4 totalMatrix;
		mesh* objmesh;
		vec4 color;
		float height;
		vec3 initialTranslationVector;
		vec3 finalTranslationVector = NULL;
		qtrn initialQuaternion;
		qtrn finalQuaternion;
		bool animated = false;
		std::vector<SceneNode*> childs;
	public:
		vec3 localTranslationVec;
		qtrn localQuaternion;
	public:
		SceneNode(SceneNode* parent_, float h);
		void destroy();
		void addChild(SceneNode* node);
		void Draw(Camera* cam, float delta);
		void setModelMatrix(mat4 matrix);
		void setTranslation(vec3 v);
		void setAnimationTranslation(vec3 v);
		void setScaleMatrix(mat4 matrix);
		void setQuaternion(qtrn q);
		void setAnimationQuaternion(qtrn q);
		void setColor(vec4 c);
		void setMesh(mesh* m);
		mesh* getMesh();
		void setShader(Shader* s);
		Shader* getShader();
		void translate(vec3 v);
	};
}