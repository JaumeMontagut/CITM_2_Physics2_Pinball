#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"
#include "p2Point.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

struct SDL_Texture;
class PhysBodyPhone;

// Small class to return to other modules to track position and rotation of physics bodies
class PhysBody
{
public:
	PhysBody() : body(NULL)
	{}

	void GetPixelPosition(int& x, int &y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;
	virtual void OnCollision(PhysBody* bodyB);
	virtual update_status PreUpdate();
	virtual update_status Update();
	virtual update_status PostUpdate();

public:
	int width, height;
	b2Body* body = nullptr;
};

enum class BUMPER_TYPE;

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener
{
public:
	ModulePhysics(bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, int radius);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBodyPhone* CreatePhonePiece(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, int* points, int size);
	PhysBody* CreateBumper(int x, int y, int radius, BUMPER_TYPE type);
	b2Joint* CreateJoint_2(const b2JointDef& def);
	b2Body* ground;
	b2World* world;


private:

	bool debug;
	
	b2MouseJoint* mouse_joint;
	
	b2Body* clickedBody = NULL;
};