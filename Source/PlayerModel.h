#ifndef PLAYERMODEL_H
#define PLAYERMODE_H

#include "CubeModel.h"

class PlayerState;
class PlayerModel;

enum Track { TRACK_LEFT, TRACK_MIDDLE, TRACK_RIGHT };

class PlayerState {

public:
	PlayerState(PlayerModel& player) : mPlayer(player), mCurrentTime(0) {}
	virtual ~PlayerState(){}

	virtual void setup() { mCurrentTime = 0; }

	virtual void Update(float dt) = 0 { mCurrentTime += dt; }

protected:
	PlayerModel& mPlayer;
	float mCurrentTime;
};

class TrackState : public PlayerState {

public:	
	TrackState(PlayerModel& player) : PlayerState(player) {}
	virtual void Update(float dt);
};

class MoveState : public PlayerState {
public:
	MoveState(PlayerModel& player) : PlayerState(player) {}
	virtual void Update(float dt);

	void SetTrackMove(Track dir);
private:
	Track mDir;
};

class PlayerModel : public CubeModel {

public:
	const static float DEFAULT_SPLINE_TIME_SPEED;
	const static float DEFAULT_MOVE_SPEED;
	const static float MODEL_SPACE_HEIGHT_OFFSET;

	PlayerModel() : CubeModel(), 
		mCurrentSplineTime(), 
		mSplineTimeSpeed(DEFAULT_SPLINE_TIME_SPEED),
		mMoveSpeed(DEFAULT_MOVE_SPEED),
		mTrack(TRACK_MIDDLE),
		mTrackState(*this),
		mMoveState(*this),
		mPlayerState(&mTrackState) {}

	virtual void Update(float dt);

private:
	void UpdatePosition(float dt);
	glm::vec3 TrackShiftDir(Track dir);

private:

	float mCurrentSplineTime;
	float mSplineTimeSpeed;
	float mMoveSpeed;

	glm::vec3 mSplineTrackOffset;

	Track mTrack;

	PlayerState* mPlayerState;
	TrackState mTrackState;
	MoveState mMoveState;

	friend TrackState;
	friend MoveState;
};


#endif
