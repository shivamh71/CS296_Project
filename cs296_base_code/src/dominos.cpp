// Files Included

#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
     #include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
    dominos_t::dominos_t(){
          b2Body* b1;

          // Ground
          {
               b2EdgeShape shape;
               shape.Set(b2Vec2(-80.0f, 0.0f), b2Vec2(80.0f, 0.0f));
               b2BodyDef bd;
               b1 = m_world->CreateBody(&bd);
               b1->CreateFixture(&shape, 0.0f);
          }

          // Water Pond 1 (with drowned object)
          {
               b2PolygonShape shape;
               shape.SetAsBox(0.4f, 4.0f);     
               b2BodyDef bd;
               bd.position.Set(-40.0f, 4.0f);
               b2Body* pond1 = m_world->CreateBody(&bd);
               pond1->CreateFixture(&shape, 0.0f);
               shape.SetAsBox(0.4f, 4.0f);
               bd.position.Set(-32.0f, 4.0f);
               pond1 = m_world->CreateBody(&bd);
               pond1->CreateFixture(&shape, 0.0f);
          }

          // Water Pond 2 (with boat)
          {
               b2PolygonShape shape;
               shape.SetAsBox(6.0f, 5.0f);      
               b2BodyDef bd;
               bd.position.Set(-5.0f, 5.0f);
               b2Body* ground = m_world->CreateBody(&bd);
               ground->CreateFixture(&shape, 0.0f);
          }

          // Botto Pulley System
          {

               // Object in pond

               b2PolygonShape shape;
               shape.SetAsBox(2.0f, 2.0f);
               b2FixtureDef fd;
               fd.shape = &shape;
               fd.density = 34.0f;
               fd.friction = 0.1f;      
               b2BodyDef *bd=new b2BodyDef;
               bd->type = b2_dynamicBody;
               bd->position.Set(-35.0f, 1.0f);
               b2Body* object_in_pond = m_world->CreateBody(bd);
               object_in_pond->CreateFixture(&shape, 34.0f);

               // Pulley System

               bd->type=b2_dynamicBody;
               bd->position.Set(-22.0f,10.0f);
               bd->fixedRotation=true;

               // Open Box

               b2FixtureDef *fd1=new b2FixtureDef;
               fd1->density = 10.0f;
               fd1->friction = 0.5f;
               fd1->restitution = 0.0f;
               fd1->shape = new b2PolygonShape;
               b2PolygonShape bs1;
               bs1.SetAsBox(2.0f, 2.0f);
               bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
               fd1->shape = &bs1;
               b2FixtureDef *fd2 = new b2FixtureDef;
               fd2->density = 10.0;
               fd2->friction = 0.5;
               fd2->restitution = 0.f;
               fd2->shape = new b2PolygonShape;
               b2PolygonShape bs2;
               bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
               fd2->shape = &bs2;
               b2FixtureDef *fd3 = new b2FixtureDef;
               fd3->density = 10.0;
               fd3->friction = 0.5;
               fd3->restitution = 0.f;
               fd3->shape = new b2PolygonShape;
               b2PolygonShape bs3;
               bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
               fd3->shape = &bs3;

               b2Body* box1 = m_world->CreateBody(bd);
               box1->CreateFixture(fd1);
               box1->CreateFixture(fd2);
               box1->CreateFixture(fd3);

               // Pulley Joint

               b2PulleyJointDef* myjoint = new b2PulleyJointDef();
               b2Vec2 worldAnchorOnBody1(-35.0f,1.0f); // Anchor point on body 1 in world axis
               b2Vec2 worldAnchorOnBody2(-22.0f,6.0f); // Anchor point on body 2 in world axis
               b2Vec2 worldAnchorGround1(-35.0, 15.0f); // Anchor point for ground 1 in world axis
               b2Vec2 worldAnchorGround2(-22.0f, 15.0f); // Anchor point for ground 2 in world axis
               float32 ratio = 1.0f; // Define ratio
               myjoint->Initialize(object_in_pond, box1, worldAnchorGround1, worldAnchorGround2, object_in_pond->GetWorldCenter(), box1->GetWorldCenter(), ratio);
               m_world->CreateJoint(myjoint);
          }   
     }
     sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
