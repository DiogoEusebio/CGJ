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
		if (state == ONGOING || state == REVERSE) {

			current_time = std::chrono::system_clock::now();
			std::chrono::duration<float> passed = current_time - start_time;

			if (state == REVERSE)
				animationTime -= (float)(passed.count());
			if (state == ONGOING)
				animationTime += (float)(passed.count());

			if (animationTime > MAX_ANIMATION_TIME)
			{
				if (state == ONGOING)
				{
					state = END;
				}
				animationTime = MAX_ANIMATION_TIME;
			}
			else if (animationTime < 0.0f)
			{
				if (state == REVERSE)
				{
					state = START;
				}
				animationTime = 0.0f;
			}
		}
		root->Draw(camera, animationTime / MAX_ANIMATION_TIME);
	}

	void SceneGraph::translate(vec3 v)
	{
		root->translate(v);
		draw();
	}

	void SceneGraph::animate()
	{
		switch (state) {
		case START:
			state = ONGOING;
			break;
		case END:
			state = REVERSE;
			break;
		case REVERSE:
			state = ONGOING;
			break;
		case ONGOING:
			state = REVERSE;
			break;
		}
		start_time = std::chrono::system_clock::now();
	}
};