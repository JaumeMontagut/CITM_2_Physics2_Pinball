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
class PBPhone;
class PBArrow;
class PBStar;
class PBTriangle;
enum class BUMPER_TYPE;
enum class ARROW_COLOR;

enum class COLLISION_FILTER : uint16 {
	BACKGROUND = 1,//The place where the ball passes through on the start of the game
	FOREGROUND = 2,
	BALL = 4
};

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

	virtual update_status PreUpdate();
	virtual update_status Update();
	virtual update_status PostUpdate();

	virtual void OnCollisionEnter(PhysBody* bodyB);
	virtual void OnCollision(PhysBody* bodyB);
	virtual void OnCollisionExit();

public:
	int width, height;
	bool wasColliding = false;
	bool isColliding = false;
	b2Body* body = nullptr;
};

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

	PhysBody* CreateCircle(int x, int y, int radius, bool isOnBackground = true);
	PhysBody* CreateRectangle(int x, int y, int width, int height, COLLISION_FILTER filter = COLLISION_FILTER::BACKGROUND, b2BodyType bodyType = b2_dynamicBody);
	PBPhone* CreatePhonePiece(int x, int y, int width, int height, float angle);
	PBStar* CreateStar(int x, int y, int width, int height, float angle);
	PBTriangle* CreateTriangle(int x, int y, int width, int height, float angle);
	PBArrow * CreateArrow(int x, int y, int width, int height, float angle, ARROW_COLOR color);
	PhysBody* CreateChain(int x, int y, int* points, int size, b2BodyType type = b2_staticBody, float restitution = 0.0f, COLLISION_FILTER filter = COLLISION_FILTER::BACKGROUND);
	PhysBody* CreateBumper(int x, int y, int radius, BUMPER_TYPE type);
	PhysBody* CreateFliper(int x, int y, bool rightFliper, float MaxAngle= 30);
	b2Joint* CreateJoint_2(const b2JointDef& def);
	PhysBody* CreateTri(int x, int y, int* points, int size, bool isLeft, int blitX, int blitY);
	PhysBody* CreateTeleport(const iPoint & pos, const iPoint & tpPoint, b2Vec2 ForceDirection);
	PhysBody* CreateBell(int x, int y, int width, int height);

	b2Body* ground;
	b2World* world;


private:

	bool debug;
	
	b2MouseJoint* mouse_joint= nullptr;
	
	b2Body* clickedBody = nullptr;
};