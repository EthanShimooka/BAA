/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BOX2D_H
#define BOX2D_H

/**
\mainpage Box2D API Documentation

\section intro_sec Getting Started

For documentation please see http://box2d.org/documentation.html

For discussion please visit http://box2d.org/forum
*/

// These include files constitute the main Box2D API

#include <include/box2D/b2Settings.h>
#include <include/box2D/b2Draw.h>
#include <include/box2D/b2Timer.h>

#include <include/box2D/b2CircleShape.h>
#include <include/box2D/b2EdgeShape.h>
#include <include/box2D/b2ChainShape.h>
#include <include/box2D/b2PolygonShape.h>

#include <include/box2D/b2BroadPhase.h>
#include <include/box2D/b2Distance.h>
#include <include/box2D/b2DynamicTree.h>
#include <include/box2D/b2TimeOfImpact.h>

#include <include/box2D/b2Body.h>
#include <include/box2D/b2Fixture.h>
#include <include/box2D/b2WorldCallbacks.h>
#include <include/box2D/b2TimeStep.h>
#include <include/box2D/b2World.h>

#include <include/box2D/b2Contact.h>

#include <include/box2D/b2DistanceJoint.h>
#include <include/box2D/b2FrictionJoint.h>
#include <include/box2D/b2GearJoint.h>
#include <include/box2D/b2MotorJoint.h>
#include <include/box2D/b2MouseJoint.h>
#include <include/box2D/b2PrismaticJoint.h>
#include <include/box2D/b2PulleyJoint.h>
#include <include/box2D/b2RevoluteJoint.h>
#include <include/box2D/b2RopeJoint.h>
#include <include/box2D/b2WeldJoint.h>
#include <include/box2D/b2WheelJoint.h>

#endif
