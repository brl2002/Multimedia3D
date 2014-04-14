#ifndef DXMOTIONSTATE_H
#define DXMOTIONSTATE_H

#include "btBulletCollisionCommon.h"

class DXMotionState : public btDefaultMotionState
{
public:
	DXMotionState(const btTransform &transform) : btDefaultMotionState(transform) {}
	
	void GetWorldTransform(btScalar* transform)
	{
		btTransform trans;
		getWorldTransform(trans);
		trans.getOpenGLMatrix(transform);
	}
};

#endif