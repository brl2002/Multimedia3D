#include "GamePhysics.h"

#define RADIANS_PER_DEGREE 0.01745329f

GamePhysics::GamePhysics() : 
	m_pBroadphase(0), 
	m_pCollisionConfiguration(0), 
	m_pDispatcher(0), 
	m_pSolver(0), 
	m_pWorld(0),
	m_pMotionState(0),
	m_pPickedBody(0),
	m_pPickConstraint(0), 
	m_cameraPosition(0.0f, 20.0f, 100.0f),
	m_cameraDistance(0.0f),
	m_nearPlane(1.0f),
	m_farPlane(2000.0f),
	m_screenWidth(800), 
	m_screenHeight(600),
	m_cameraTarget(0.0f, 0.0f, 0.0f),
	m_upVector(0.0f, 1.0f, 0.0f),
	m_cameraPitch(20.0f),
	m_cameraYaw(0.0f)
{
}

GamePhysics::~GamePhysics()
{
	End();
}

void GamePhysics::End()
{
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
}

void GamePhysics::Initialize()
{
	m_pBroadphase = 0;
	m_pCollisionConfiguration = 0; 
	m_pDispatcher = 0; 
	m_pSolver = 0; 
	m_pWorld = 0;
	m_pMotionState = 0;
	m_pPickedBody = 0;
	m_pPickConstraint = 0; 
	m_cameraPosition = btVector3(0.0f, 20.0f, 100.0f);
	m_cameraDistance = 100.0f;
	m_nearPlane = 1.0f;
	m_farPlane = 2000.0f;
	m_screenWidth = 800;
	m_screenHeight = 600;
	m_cameraTarget = btVector3(0.0f, 0.0f, 0.0f);
	m_upVector = btVector3(0.0f, 1.0f, 0.0f);
	m_cameraPitch = 20.0f;
	m_cameraYaw = 0.0f;

	// create the collision configuration
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	// create the dispatcher
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
	// create the broadphase
	m_pBroadphase = new btDbvtBroadphase();
	// create the constraint solver
	m_pSolver = new btSequentialImpulseConstraintSolver();
	// create the world
	m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);
}

void GamePhysics::PhysicsUpdate(float dt)
{
	// check if the world object exists
	if (m_pWorld)
	{
		// step the simulation through time. This is called
		// every update and the amount of elasped time was 
		// determined back in ::Idle() by our clock object.
		m_pWorld->stepSimulation(dt * 5000);
	}

	for(GameObjects::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		//get the object from the iterator
		GameObject* pObj = *i;

		if (pObj->ContactTestRequired())
		{
			ContactTest(pObj);
		}
		
		//Sync object's mesh with rigidbody
		btTransform transform = pObj->GetRigidBody()->getWorldTransform();
		btVector3 v = transform.getOrigin();
		Advanced2D::Mesh *mesh = pObj->GetMesh();

		if (mesh)
		{
			mesh->SetPosition(v.x(), v.y(), -v.z());
		}
	}
}

void GamePhysics::ContactTest(GameObject *gameObject)
{
	btRigidBody *rigidBody = gameObject->GetRigidBody();
	ContactInfo info;
	info.gameObject = gameObject;
	ContactSensorCallback callback(*rigidBody, info);
	m_pWorld->contactTest(rigidBody, callback);
}

void GamePhysics::Reshape(int w, int h) {
	// this function is called once during application intialization
	// and again every time we resize the window

	// grab the screen width/height
	m_screenWidth = w;
	m_screenHeight = h;
	// update the camera
	UpdateCamera();
}

void GamePhysics::UpdateCamera()
{
	// exit in erroneous situations
	if (m_screenWidth == 0 && m_screenHeight == 0)
		return;

	// our values represent the angles in degrees, but 3D 
	// math typically demands angular values are in radians.
	float pitch = m_cameraPitch * RADIANS_PER_DEGREE;
	float yaw = m_cameraYaw * RADIANS_PER_DEGREE;

	// create a quaternion defining the angular rotation 
	// around the up vector
	btQuaternion rotation(m_upVector, yaw);

	// set the camera's position to 0,0,0, then move the 'z' 
	// position to the current value of m_cameraDistance.
	btVector3 cameraPosition(0,0,0);
	cameraPosition[2] = -m_cameraDistance;

	// create a Bullet Vector3 to represent the camera 
	// position and scale it up if its value is too small.
	btVector3 forward(cameraPosition[0], cameraPosition[1], cameraPosition[2]);
	if (forward.length2() < SIMD_EPSILON) {
		forward.setValue(1.f,0.f,0.f);
	}

	// figure out the 'right' vector by using the cross 
	// product on the 'forward' and 'up' vectors
	btVector3 right = m_upVector.cross(forward);

	// create a quaternion that represents the camera's roll
	btQuaternion roll(right, - pitch);

	// turn the rotation (around the Y-axis) and roll (around 
	// the forward axis) into transformation matrices and 
	// apply them to the camera position. This gives us the 
	// final position
	cameraPosition = btMatrix3x3(rotation) * btMatrix3x3(roll) * cameraPosition;

	// save our new position in the member variable, and 
	// shift it relative to the target position (so that we 
	// orbit it)
	m_cameraPosition[0] = cameraPosition.getX();
	m_cameraPosition[1] = cameraPosition.getY();
	m_cameraPosition[2] = cameraPosition.getZ();
	m_cameraPosition += m_cameraTarget;

	m_camera->setPosition(m_cameraPosition[0], m_cameraPosition[1], m_cameraPosition[2]);
}

void GamePhysics::SetCamera(Advanced2D::Camera *camera)
{
	m_camera = camera;
}

void GamePhysics::DebugRender()
{
	for(GameObjects::iterator i = m_objects.begin(); i != m_objects.end(); ++i)
	{
		GameObject* pObj = *i;
		DrawBox(pObj);
	}
}

void GamePhysics::DrawBox(GameObject *gameObject)
{
	btCollisionShape *shape = gameObject->GetShape();

	if (shape->getShapeType() == BOX_SHAPE_PROXYTYPE)
	{
		btTransform transform = gameObject->GetRigidBody()->getWorldTransform();
		btVector3 v = transform.getOrigin();
		const btBoxShape* box = static_cast<const btBoxShape*>(shape);

		btVector3 halfSize = box->getHalfExtentsWithMargin();

		float halfWidth = halfSize.x();
		float halfHeight = halfSize.y();
		float halfDepth = halfSize.z();

		D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 255, 255);

		LPD3DXLINE line;
		D3DXCreateLine(g_engine->getDevice(), &line);
		D3DXMATRIX cameraProj = m_camera->getViewMatrix() * m_camera->getProjectionMatrix();

		line->SetWidth(1.0f);
		line->Begin();

		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + halfWidth, -v.z() + halfDepth, v.x() + -halfHeight, v.y() + halfWidth, -v.z() + halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + -halfWidth, -v.z() + halfDepth, v.x() + -halfHeight, v.y() + -halfWidth, -v.z() + halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + -halfHeight, v.y() + halfWidth, -v.z() + halfDepth, v.x() + -halfHeight, v.y() + -halfWidth, -v.z() + halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + halfWidth, -v.z() + halfDepth, v.x() + halfHeight, v.y() + -halfWidth, -v.z() + halfDepth);

		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + halfWidth, -v.z() + -halfDepth, v.x() + -halfHeight, v.y() + halfWidth, -v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + -halfWidth, -v.z() + -halfDepth, v.x() + -halfHeight, v.y() + -halfWidth, -v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + -halfHeight, v.y() + halfWidth, -v.z() + -halfDepth, v.x() + -halfHeight, v.y() + -halfWidth, -v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + halfWidth, -v.z() + -halfDepth, v.x() + halfHeight, v.y() + -halfWidth, -v.z() + -halfDepth);

		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + halfWidth, -v.z() + halfDepth, v.x() + halfHeight, v.y() + halfWidth, -v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + halfHeight, v.y() + -halfWidth, -v.z() + halfDepth, v.x() + halfHeight, v.y() + -halfWidth, -v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + -halfHeight, v.y() + halfWidth, -v.z() + halfDepth, v.x() + -halfHeight, v.y() + halfWidth, -v.z() + -halfDepth);
		DrawLine(line, &cameraProj, color, v.x() + -halfHeight, v.y() + -halfWidth, -v.z() + halfDepth, v.x() + -halfHeight, v.y() + -halfWidth, -v.z() + -halfDepth);

		line->End();
		line->Release();
	}
}

void GamePhysics::DrawLine(LPD3DXLINE line, D3DXMATRIX *camProj, D3DCOLOR color, float v1_x, float v1_y, float v1_z, float v2_x, float v2_y, float v2_z)
{
	D3DXVECTOR3 lineSet[] = {D3DXVECTOR3(v1_x, v1_y, v1_z), D3DXVECTOR3(v2_x, v2_y, v2_z)};
	line->DrawTransform(lineSet, 2, camProj, color);
}

GameObject* GamePhysics::CreateGameObject(GameObjectType type, btCollisionShape* pShape, const float &mass, const btVector3 &color, const btVector3 &initialPosition, const btQuaternion &initialRotation)
{
	// create a new game object
	GameObject* pObject = new GameObject(type, pShape, mass, color, initialPosition, initialRotation);

	// push it to the back of the list
	m_objects.push_back(pObject);

	// check if the world object is valid
	if (m_pWorld)
	{
		// add the object's rigid body to the world
		m_pWorld->addRigidBody(pObject->GetRigidBody());
	}

	return pObject;
}

void GamePhysics::Mouse(int button, int state, int x, int y) 
{
	if (button == 0 && state == 1)
	{
		CreatePickingConstraint(x, y);
		//ShootBox(GetPickingRay(x, y));
	}

	if (button == 1 && state == 1)
	{
		ShootBox(GetPickingRay(x, y));
	}

	//switch(button)
	//{
	//case 0:  // left mouse button
	//	{
	//		if (state == 1) { // button down
	//			// create the picking constraint when we click the LMB
	//			CreatePickingConstraint(x, y);
	//		}
	//		else
	//		{ // button up
	//			// remove the picking constraint when we release the LMB
	//			RemovePickingConstraint();
	//		}
	//		break;
	//	}
	//case 2: // right mouse button
	//	{
	//		if (state == 0) { // pressed down
	//			// shoot a box
	//			ShootBox(GetPickingRay(x, y));
	//		}
	//		break;
	//	}
	//}
}

btVector3 GamePhysics::GetPickingRay(int x, int y)
{
	// calculate the field-of-view
	float tanFov = 1.0f / m_nearPlane;
	float fov = btScalar(2.0) * btAtan(tanFov);

	// get a ray pointing forward from the 
	// camera and extend it to the far plane
	btVector3 rayFrom = m_cameraPosition;
	//btVector3 rayFrom = btVector3(m_cameraPosition.x(), m_cameraPosition.y(), -m_cameraPosition.z());
	btVector3 rayForward = (m_cameraTarget - m_cameraPosition);
	//btVector3 rayForward = btVector3(m_cameraTarget.x() - m_cameraPosition.x(), m_cameraTarget.y() - m_cameraPosition.y(), m_cameraPosition.z() - m_cameraTarget.z());
	rayForward.normalize();
	rayForward*= m_farPlane;

	// find the horizontal and vertical vectors 
	// relative to the current camera view
	btVector3 ver = m_upVector;
	btVector3 hor = rayForward.cross(ver);
	hor.normalize();
	ver = hor.cross(rayForward);
	ver.normalize();
	hor *= 2.f * m_farPlane * tanFov;
	ver *= 2.f * m_farPlane * tanFov;

	// calculate the aspect ratio
	btScalar aspect = m_screenWidth / (btScalar)m_screenHeight;

	// adjust the forward-ray based on
	// the X/Y coordinates that were clicked
	hor*=aspect;
	btVector3 rayToCenter = rayFrom + rayForward;
	btVector3 dHor = hor * 1.f/float(m_screenWidth);
	btVector3 dVert = ver * 1.f/float(m_screenHeight);
	btVector3 rayTo = rayToCenter - 0.5f * hor + 0.5f * ver;
	rayTo += btScalar(x) * dHor;
	rayTo -= btScalar(y) * dVert;

	// return the final result
	return rayTo;
}

void GamePhysics::ShootObject(btRigidBody *rigidBody, float speed, int x, int y)
{
	btTransform t = rigidBody->getWorldTransform();
	btVector3 v = btVector3(m_cameraPosition.x(), m_cameraPosition.y(), m_cameraPosition.z());
	t.setOrigin(v);

	// calculate the velocity
	btVector3 velocity = GetPickingRay(x, y); 
	velocity.normalize();
	velocity *= speed;

	// set the linear velocity of the box
	rigidBody->setLinearVelocity(velocity);
	//rigidBody->applyForce(velocity, v);
}

void GamePhysics::ShootBox(const btVector3 &direction)
{
	// create a new box object
	GameObject* pObject = CreateGameObject(FISH, new btBoxShape(btVector3(1, 1, 1)), 1, btVector3(0.4f, 0.f, 0.4f), m_cameraPosition);

	// calculate the velocity
	btVector3 velocity = direction; 
	velocity.normalize();
	velocity *= 25.0f;

	// set the linear velocity of the box
	pObject->GetRigidBody()->setLinearVelocity(velocity);
}

bool GamePhysics::Raycast(const btVector3 &startPosition, const btVector3 &direction, RayResult &output)
{
	if (!m_pWorld) 
		return false;

	// get the picking ray from where we clicked
	btVector3 rayTo = direction;
	btVector3 rayFrom = m_cameraPosition;

	// create our raycast callback object
	btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,rayTo);

	// perform the raycast
	m_pWorld->rayTest(rayFrom,rayTo,rayCallback);
	
	// did we hit something?
	if (rayCallback.hasHit())
	{
		// if so, get the rigid body we hit
		btRigidBody* pBody = (btRigidBody*)btRigidBody::upcast(rayCallback.m_collisionObject);
		if (!pBody)
			return false;


		// prevent us from picking objects 
		// like the ground plane
		if (pBody->isStaticObject() || pBody->isKinematicObject()) 
			return false;

		// set the result data
		output.pBody = pBody;
		output.hitPoint = rayCallback.m_hitPointWorld;
		return true;
	}

	// we didn't hit anything
	return false;
}

void GamePhysics::DestroyGameObject(GameObject* go)
{
	// we need to search through the objects in order to 
	// find the corresponding iterator (can only erase from 
	// an std::vector by passing an iterator)
	btRigidBody* pBody = go->GetRigidBody();

	for (GameObjects::iterator iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		if ((*iter)->GetRigidBody() == pBody)
		{
			GameObject* pObject = *iter;
			// remove the rigid body from the world
			m_pWorld->removeRigidBody(pObject->GetRigidBody());
			// erase the object from the list
			m_objects.erase(iter);
			// delete the object from memory
			delete go;

			return;
		}
	}

}

void GamePhysics::Motion(int x, int y) 
{
	// did we pick a body with the LMB?
	if (m_pPickedBody)
	{
		btGeneric6DofConstraint* pickCon = static_cast<btGeneric6DofConstraint*>(m_pPickConstraint);
		if (!pickCon)
			return;

		// use another picking ray to get the target direction
		btVector3 dir = GetPickingRay(x,y) - m_cameraPosition;
		dir.normalize();

		// use the same distance as when we originally picked the object
		dir *= m_oldPickingDist;
		btVector3 newPivot = m_cameraPosition + dir;

		// set the position of the constraint
		pickCon->getFrameOffsetA().setOrigin(newPivot);
	}
}

void GamePhysics::CreatePickingConstraint(int x, int y)
{
	if (!m_pWorld) 
		return;

	// perform a raycast and return if it fails
	RayResult output;
	if (!Raycast(m_cameraPosition, GetPickingRay(x, y), output))
		return;

	// store the body for future reference
	m_pPickedBody = output.pBody;

	// prevent the picked object from falling asleep
	m_pPickedBody->setActivationState(DISABLE_DEACTIVATION);

	// get the hit position relative to the body we hit 
	btVector3 localPivot = m_pPickedBody->getCenterOfMassTransform().inverse() * output.hitPoint;

	// create a transform for the pivot point
	btTransform pivot;
	pivot.setIdentity();
	pivot.setOrigin(localPivot);

	// create our constraint object
	btGeneric6DofConstraint* dof6 = new btGeneric6DofConstraint(*m_pPickedBody, pivot, true);
	bool bLimitAngularMotion = true;
	if (bLimitAngularMotion)
	{
		dof6->setAngularLowerLimit(btVector3(0,0,0));
		dof6->setAngularUpperLimit(btVector3(0,0,0));
	}

	// add the constraint to the world
	m_pWorld->addConstraint(dof6,true);

	// store a pointer to our constraint
	m_pPickConstraint = dof6;

	// define the 'strength' of our constraint (each axis)
	float cfm = 0.5f;
	dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,0);
	dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,1);
	dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,2);
	dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,3);
	dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,4);
	dof6->setParam(BT_CONSTRAINT_STOP_CFM,cfm,5);

	// define the 'error reduction' of our constraint (each axis)
	float erp = 0.5f;
	dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,0);
	dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,1);
	dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,2);
	dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,3);
	dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,4);
	dof6->setParam(BT_CONSTRAINT_STOP_ERP,erp,5);

	// save this data for future reference
	m_oldPickingDist  = (output.hitPoint - m_cameraPosition).length();
}

void GamePhysics::RemovePickingConstraint()
{
	// exit in erroneous situations
	if (!m_pPickConstraint || !m_pWorld) 
		return;


	// remove the constraint from the world
	m_pWorld->removeConstraint(m_pPickConstraint);

	// delete the constraint object
	delete m_pPickConstraint;

	// reactivate the body
	m_pPickedBody->forceActivationState(ACTIVE_TAG);
	m_pPickedBody->setDeactivationTime( 0.f );

	// clear the pointers
	m_pPickConstraint = 0;
	m_pPickedBody = 0;
}