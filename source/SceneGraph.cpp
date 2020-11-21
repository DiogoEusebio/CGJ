#include "../header/SceneGraph.h"

namespace egn {
	void SceneGraph::setRoot(SceneNode* node)
	{
		root = node;
	}

	SceneNode* SceneGraph::getRoot()
	{
		return root;
	}

	void SceneGraph::setCamera(Camera* cam)
	{
		camera = cam;
	}

	void SceneGraph::destroy()
	{
		root->destroy();
	}

	void SceneGraph::draw()
	{
		root->Draw(camera);
	}
};