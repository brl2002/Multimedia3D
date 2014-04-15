#ifndef GAMEPHYSICS_H
#define GAMEPHYSICS_H

#include "..\Engine\Advanced2D.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "DXMotionState.h"
#include "GameObject.h"
#include "Contact.h"
#include <vector>
#include <Windows.h>
typedef std::vector<GameObject*> GameObjects;

/*ADD*/	// struct to store our raycasting results
/*ADD*/	struct RayResult {
/*ADD*/		btRigidBody* pBody;
/*ADD*/		btVector3 hitPoint;
/*ADD*/	};

class GamePhysics
{
public:
	~GamePhysics();

	static GamePhysics& getInstance()
	{
		static GamePhysics instance;

		return instance;
	}

	void Initialize();
	void End();

	void PhysicsUpdate(float dt);

	void DebugRender();

	void SetCamera(Advanced2D::Camera *camera);

	void Mouse(int button, int state, int x, int y);

	void Motion(int x, int y);

	void Reshape(int w, int h);

	void UpdateCamera();

	GameObject* CreateGameObject(GameObjectType type, btCollisionShape* pShape, 
			const float &mass, 
			const btVector3 &color = btVector3(1.0f,1.0f,1.0f), 
			const btVector3 &initialPosition = btVector3(0.0f,0.0f,0.0f), 
			const btQuaternion &initialRotation = btQuaternion(0,0,1,1));

	void ShootObject(btRigidBody *rigidBody, float speed, int x, int y);

	/*ADD*/		void ShootBox(const btVector3 &direction);
	/*ADD*/		void DestroyGameObject(GameObject* go);

	/*ADD*/		// picking functions
	/*ADD*/		btVector3 GetPickingRay(int x, int y);
	/*ADD*/		bool Raycast(const btVector3 &startPosition, const btVector3 &direction, RayResult &output);
	/*ADD*/		void CreatePickingConstraint(int x, int y);
	/*ADD*/		void RemovePickingConstraint();

	Advanced2D::Camera* GetCamera() { return m_camera; }

protected:
	/*ADD*/		btRigidBody* m_pPickedBody;				// the body we picked up
	/*ADD*/		btTypedConstraint*  m_pPickConstraint;	// the constraint the body is attached to
	/*ADD*/		btScalar m_oldPickingDist;				// the distance from the camera to the hit point (so we can move the object up, down, left and right from our view)

protected:
	void DrawBox(GameObject *gameObject);
	void DrawLine(LPD3DXLINE line, D3DXMATRIX *camProj, D3DCOLOR color, float v1_x, float v1_y, float v1_z, float v2_x, float v2_y, float v2_z);
	void ContactTest(GameObject *gameObject);

protected:
	GamePhysics();
	// added in this implementation
	GameObjects m_objects;

	Advanced2D::Camera *m_camera;

	// core Bullet components
	btBroadphaseInterface* m_pBroadphase;
	btCollisionConfiguration* m_pCollisionConfiguration;
	btCollisionDispatcher* m_pDispatcher;
	btConstraintSolver* m_pSolver;
	btDynamicsWorld* m_pWorld;

	// our custom motion state
	DXMotionState* m_pMotionState;

	// camera control
	btVector3 m_cameraPosition; // the camera's current position
	btVector3 m_cameraTarget;	 // the camera's lookAt target
	float m_nearPlane; // minimum distance the camera will render
	float m_farPlane; // farthest distance the camera will render
	btVector3 m_upVector; // keeps the camera rotated correctly
	float m_cameraDistance; // distance from the camera to its target
	float m_cameraPitch; // pitch of the camera 
	float m_cameraYaw; // yaw of the camera

	int m_screenWidth;
	int m_screenHeight;
};

#endif