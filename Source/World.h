//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#pragma once

#include "ParsingHelper.h"
#include "Billboard.h"
#include <vector>

class Camera;
class Model;
class Animation;
class AnimationKey;
class ParticleSystem;

class World
{
public:
	static const char* sceneFile;

	World();
	~World();
	
    static World* GetInstance();

	void Update(float dt);
	void Draw();

	void World::LoadScene();

	void LoadScene(const char * scene_path);

    Animation* FindAnimation(ci_string animName);
	AnimationKey* FindAnimationKey(ci_string keyName);

    const Camera* GetCurrentCamera() const;
    void AddBillboard(Billboard* b);
    void RemoveBillboard(Billboard* b);
    void AddParticleSystem(ParticleSystem* particleSystem);
    void RemoveParticleSystem(ParticleSystem* particleSystem);
    
	Camera* GetCamera() { return mCamera[mCurrentCamera]; }

private:
    static World* instance;
    
	std::vector<Model*> mModel;
    std::vector<Animation*> mAnimation;
    std::vector<AnimationKey*> mAnimationKey;
	std::vector<Camera*> mCamera;
    std::vector<ParticleSystem*> mParticleSystemList;
	unsigned int mCurrentCamera;

    BillboardList* mpBillboardList;
};
