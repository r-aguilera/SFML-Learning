#pragma once
#ifndef _RESOURCEHOLDER_
#define _RESOURCEHOLDER_

#include <SFML\Graphics.hpp>
#include "identifiers.hpp"
#include <assert.h>

template<typename Resource, typename Identifier>
class ResourceHolder {
public:
	void load(Identifier, const std::string&);

	template <typename Parameter>
	void load(Identifier, const std::string&, const Parameter&);

	Resource& get(Identifier);

	const Resource& get(Identifier) const;

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename) {
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load failed to load " + filename);

	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));

	assert(inserted.second);
}

template<typename Resource, typename Identifier>
template<typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondPar) {
	std::unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename, secondPar))
		throw std::runtime_error("ResourceHolder::load failed to load " + filename);

	auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));

	assert(inserted.second);
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *found->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
	auto found = mResourceMap.find(id);
	assert(found != mResourceMap.end());
	return *found->second;
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif // _RESOURCEHOLDER_
