#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

//Physics Bodies
#include "PBBumper.h"
#include "PBPhone.h"
#include "PBFlipper.h"
#include "PBArrow.h"
#include "PBStar.h"
#include "PBTriangle.h"
#include "PBTri.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(bool start_enabled) : Module(start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	//Update of each body
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		PhysBody* pb = (PhysBody*)b->GetUserData();;
		if (pb != nullptr) {
			pb->PreUpdate();
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModulePhysics::Update() {
	//Update of each body
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		PhysBody* pb = (PhysBody*)b->GetUserData();;
		if (pb != nullptr) {
			pb->Update();
		}
	}

	//On collision calls
	//INFO: This implementation only detects if a body enters / is / exits a collision
	//If there were to be more than one body moving on the screen this wouldn't work as expected
	//INFO: In our case, as there is only one ball moving in the scene, this implementation works perfectly
	//and gets rid of using lists for each collision pair or a b2ContactListener (which would require substancially more processing)

	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		PhysBody* pb = (PhysBody*)b->GetUserData();;
		if (pb != nullptr) {
			pb->wasColliding = pb->isColliding;
			pb->isColliding = false;
		}
	}

	for (b2Contact* contact = world->GetContactList(); contact; contact = contact->GetNext())
	{
		if (contact->GetFixtureA() && contact->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

			pb1->isColliding = true;
			pb2->isColliding = true;

			if (pb1 && pb2) {
				if (pb1->isColliding && !pb1->wasColliding) {
					pb1->OnCollisionEnter(pb2);
				}
				else {
					pb1->OnCollision(pb2);
				}
			}

			if (pb1 && pb2) {
				if (pb2->isColliding && !pb2->wasColliding) {
					pb2->OnCollisionEnter(pb1);
				}
				else {
					pb2->OnCollision(pb1);
				}
			}
		}
	}

	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		PhysBody* pb = (PhysBody*)b->GetUserData();;
		if (pb != nullptr) {
			if (pb->wasColliding && !pb->isColliding) {
				pb->OnCollisionExit();
			}
		}
	}

	return UPDATE_CONTINUE;
}

update_status ModulePhysics::PostUpdate()
{
	//Post update of each body
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		PhysBody* pb = (PhysBody*)b->GetUserData();;
		if (pb != nullptr) {
			pb->PostUpdate();
		}
	}

	//Draw debug lines
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (!debug)
		return UPDATE_CONTINUE;

	b2Vec2 mousePosMeters(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));
	b2Vec2 mousePosPixels(App->input->GetMouseX(), App->input->GetMouseY());

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch (f->GetType())
			{
				// Draw circles ------------------------------------------------
			case b2Shape::e_circle:
			{
				b2CircleShape* shape = (b2CircleShape*)f->GetShape();
				b2Vec2 pos = f->GetBody()->GetPosition();
				App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
			}
			break;

			// Draw polygons ------------------------------------------------
			case b2Shape::e_polygon:
			{
				b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
				int32 count = polygonShape->GetVertexCount();
				b2Vec2 prev, v;

				for (int32 i = 0; i < count; ++i)
				{
					v = b->GetWorldPoint(polygonShape->GetVertex(i));
					if (i > 0)
						App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

					prev = v;
				}

				v = b->GetWorldPoint(polygonShape->GetVertex(0));
				App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
			}
			break;

			// Draw chains contour -------------------------------------------
			case b2Shape::e_chain:
			{
				b2ChainShape* shape = (b2ChainShape*)f->GetShape();
				b2Vec2 prev, v;

				for (int32 i = 0; i < shape->m_count; ++i)
				{
					v = b->GetWorldPoint(shape->m_vertices[i]);
					if (i > 0)
						App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
					prev = v;
				}

				v = b->GetWorldPoint(shape->m_vertices[0]);
				App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
			}
			break;

			// Draw a single segment(edge) ----------------------------------
			case b2Shape::e_edge:
			{
				b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
				b2Vec2 v1, v2;

				v1 = b->GetWorldPoint(shape->m_vertex0);
				v1 = b->GetWorldPoint(shape->m_vertex1);
				App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
			}
			break;
			}

			if (clickedBody == NULL &&
				App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN &&
				f->GetShape()->TestPoint(b->GetTransform(), mousePosMeters)) {
				clickedBody = b;
			}
		}
	}

	//if (clickedBody != NULL && mouse_joint == NULL) {
	//	b2MouseJointDef def;
	//	
	//	def.bodyA = ground;
	//	def.bodyB = clickedBody;
	//	def.target = mousePosMeters;
	//	def.dampingRatio = 0.5f;
	//	def.frequencyHz = 2.0f;
	//	def.maxForce = 100.0f * clickedBody->GetMass();
	//	mouse_joint = (b2MouseJoint*)world->CreateJoint(&def);
	//}

	//else if (clickedBody != NULL && mouse_joint != NULL && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
	//	App->renderer->DrawLine(METERS_TO_PIXELS(clickedBody->GetPosition().x), METERS_TO_PIXELS(clickedBody->GetPosition().y), mousePosPixels.x, mousePosPixels.y, 255, 0, 0, 255);
	//	mouse_joint->SetTarget(mousePosMeters);
	//}

	//else if (mouse_joint != NULL && App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP) {
	//	world->DestroyJoint(mouse_joint);
	//	mouse_joint = NULL;
	//	clickedBody = NULL;
	//}

	return UPDATE_CONTINUE;
}
b2Joint*  ModulePhysics::CreateJoint_2(const b2JointDef& def)
{
	return world->CreateJoint(&def);
}

PhysBody * ModulePhysics::CreateTri(int x, int y, int width, int height, int* points, int size, bool isLeft, int blitX, int blitY)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for (uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PBTri * pbody = new PBTri(isLeft, blitX, blitY);
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

PhysBody* ModulePhysics::CreateBumper(int x, int y, int radius, BUMPER_TYPE type)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.friction = 0.0f;
	fixture.restitution = 0.85f;
	
	b->CreateFixture(&fixture);

	PBBumper* pbody = new PBBumper(type);
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius * 2;

	return pbody;
}

PhysBody * ModulePhysics::CreateFliper(int x, int y, bool rightFliper)
{
	b2Body* CircleFlipper;
	b2Body* rectangleFlipper;
	b2RevoluteJointDef jointFlipperDef;
	b2Vec2 mesure(40, 10);
	if (!rightFliper)
	{
		CircleFlipper = CreateCircle(x, y, 4)->body;
		CircleFlipper->SetType(b2BodyType::b2_staticBody);
		rectangleFlipper = App->physics->CreateRectangle( x+20 , y, mesure.x, mesure.y)->body;
		rectangleFlipper->SetType(b2BodyType::b2_dynamicBody);
		
		
		jointFlipperDef.enableLimit = true;
		jointFlipperDef.lowerAngle = -30 * DEGTORAD;
		jointFlipperDef.upperAngle = 45 * DEGTORAD;
	}
	else
	{

		CircleFlipper = CreateCircle(x, y, 4)->body;
		CircleFlipper->SetType(b2BodyType::b2_staticBody);
		rectangleFlipper = App->physics->CreateRectangle(x-20, y, mesure.x, mesure.y)->body;
		rectangleFlipper->SetType(b2BodyType::b2_dynamicBody);
		
		jointFlipperDef.enableLimit = true;
		jointFlipperDef.lowerAngle = -45 * DEGTORAD;
		jointFlipperDef.upperAngle = 30 * DEGTORAD;
	}

	jointFlipperDef.Initialize(rectangleFlipper, CircleFlipper, CircleFlipper->GetWorldCenter());

	b2RevoluteJoint* joinFlipper;
	joinFlipper = (b2RevoluteJoint*)App->physics->world->CreateJoint(&jointFlipperDef);

	PBFlipper* newFliper = new PBFlipper({ mesure.x,mesure.y });
	newFliper->body = rectangleFlipper;
	rectangleFlipper->SetUserData(newFliper);
	newFliper->rightfliper = rightFliper;
	return newFliper;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = radius * 2;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PBPhone* ModulePhysics::CreatePhonePiece(int x, int y, int width, int height, float angle)
{
	b2BodyDef body;
	body.type = b2_staticBody;

	b2Body* b = world->CreateBody(&body);
	b->SetTransform(b2Vec2(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y)), DEGTORAD * angle);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PBPhone* pbody = new PBPhone();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PBStar * ModulePhysics::CreateStar(int x, int y, int width, int height, float angle)
{
	b2BodyDef body;
	body.type = b2_staticBody;

	b2Body* b = world->CreateBody(&body);
	b->SetTransform(b2Vec2(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y)), DEGTORAD * angle);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PBStar* pbody = new PBStar();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PBTriangle * ModulePhysics::CreateTriangle(int x, int y, int width, int height, float angle)
{
	b2BodyDef body;
	body.type = b2_staticBody;

	b2Body* b = world->CreateBody(&body);
	b->SetTransform(b2Vec2(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y)), DEGTORAD * angle);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PBTriangle* pbody = new PBTriangle();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PBArrow * ModulePhysics::CreateArrow(int x, int y, int width, int height, float angle, ARROW_COLOR color)
{
	b2BodyDef body;
	body.type = b2_staticBody;

	b2Body* b = world->CreateBody(&body);
	b->SetTransform(b2Vec2(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y)), DEGTORAD * angle);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PBArrow * pbody = new PBArrow(color);
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size, b2BodyType type, float restitution)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.restitution = restitution;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}





// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPixelPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - width * 0.5f;
	y = METERS_TO_PIXELS(pos.y) - height * 0.5f;
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void PhysBody::OnCollisionEnter(PhysBody * bodyB)
{
}

void PhysBody::OnCollision(PhysBody * bodyB)
{

}

void PhysBody::OnCollisionExit()
{

}

update_status PhysBody::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status PhysBody::Update()
{
	return UPDATE_CONTINUE;
}

update_status PhysBody::PostUpdate()
{
	return UPDATE_CONTINUE;
}
