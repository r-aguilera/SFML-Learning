#pragma once
#ifndef _SCENENODE_
#define _SCENENODE_

#include <SFML\Graphics.hpp>

enum Layer {
	Space,
	Ships,
	UI
};

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
public:
	typedef std::unique_ptr<SceneNode> Ptr;
public:
	SceneNode();
	void attachChild(Ptr);
	Ptr dettachChild(const SceneNode&);
private:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const final;
	virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const;
private:
	std::vector<Ptr> mChildren;
	SceneNode* mParent;
};

#endif // _SCENENODE_
