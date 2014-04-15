#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "..\Engine\Advanced2D.h"
#include "btBulletDynamicsCommon.h"
#include "DXMotionState.h"

enum GameObjectType
{
	FISH,
	TRIGGER,
	OTHER
};

class GameObject
{
public:
	GameObject(GameObjectType type, btCollisionShape* pShape, float mass, const btVector3 &color, const btVector3 &initialPosition = btVector3(0,0,0), const btQuaternion &initialRotation = btQuaternion(0,0,1,1));
	~GameObject();

	void SetMesh(Advanced2D::Mesh *mesh);

	void LoadMesh(char *filename);

	Advanced2D::Mesh* GetMesh();

	// accessors
	btCollisionShape* GetShape() { return m_pShape; }

	btRigidBody* GetRigidBody() { return m_pBody; }

	btMotionState* GetMotionState() { return m_pMotionState; }

	void GetTransform(btScalar* transform)
	{ 
		if (m_pMotionState) m_pMotionState->GetWorldTransform(transform); 
	}
	
	btVector3 GetColor() { return m_color; }

	void SetScale(double x, double y, double z);

	GameObjectType GetType() { return m_type; }

	void RequiresContactTest() { m_RequiresContactTest = true; }
	bool ContactTestRequired() { return m_RequiresContactTest; }

protected:
	Advanced2D::Mesh *m_mesh;
	btCollisionShape*  m_pShape;
	btRigidBody*    m_pBody;
	DXMotionState*  m_pMotionState;
	btVector3      m_color;
	bool m_RequiresContactTest;
	GameObjectType m_type;
};
#endif