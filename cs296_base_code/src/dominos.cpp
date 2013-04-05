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

          // Pendulum
          {
               b2Body* b2;
               {
                    b2PolygonShape shape;
                    shape.SetAsBox(4.0f, 0.2f);                      
                    b2BodyDef bd;
                    bd.position.Set(-9.0f, 95.0f);
                    b2 = m_world->CreateBody(&bd);
                    b2->CreateFixture(&shape, 10.0f);
               }
               b2Body* sbody;
               {
                    // Pendulum Bob #1
                    b2CircleShape circle;
                    circle.m_radius = 1.0;
                    b2FixtureDef ballfd;
                    ballfd.shape = &circle;
                    ballfd.density = 2.0f;
                    ballfd.friction = 0.0f;
                    ballfd.restitution = 0.0f;
                    b2BodyDef ballbd;
                    ballbd.type = b2_dynamicBody;
                    b2RevoluteJointDef jd;
                    b2Vec2 anchor;
                    ballbd.position.Set(-9.0f, 85.2f);
                    sbody = m_world->CreateBody(&ballbd);
                    sbody->CreateFixture(&ballfd);
                    anchor.Set(-9.0f, 95.0f);
                    jd.Initialize(b2, sbody, anchor);
                    m_world->CreateJoint(&jd);

                    // Pendulum Bob #2
                    ballbd.position.Set(-6.0f, 85.2f);
                    sbody = m_world->CreateBody(&ballbd);
                    sbody->CreateFixture(&ballfd);
                    anchor.Set(-6.0f, 95.0f);
                    jd.Initialize(b2, sbody, anchor);
                    m_world->CreateJoint(&jd);

                    // Pendulum Bob #3
                    ballbd.position.Set(-12.0f, 85.2f);
                    sbody = m_world->CreateBody(&ballbd);
                    sbody->CreateFixture(&ballfd);
                    anchor.Set(-12.0f, 95.0f);
                    jd.Initialize(b2, sbody, anchor);
                    m_world->CreateJoint(&jd);
               }
          }

          // Water Pond 1 (with drowned object)
          {
               b2PolygonShape shape;
               shape.SetAsBox(0.25f, 4.0f);     
               b2BodyDef bd;
               bd.position.Set(-40.0f, 4.0f);
               b2Body* pond1 = m_world->CreateBody(&bd);
               pond1->CreateFixture(&shape, 0.0f);
               shape.SetAsBox(0.25f, 4.0f);
               bd.position.Set(-32.0f, 4.0f);
               pond1 = m_world->CreateBody(&bd);
               pond1->CreateFixture(&shape, 0.0f);
          }

          // Water Pond 2 (with boat)
          {
               b2PolygonShape shape;
               shape.SetAsBox(0.25f, 6.0f);     
               b2BodyDef bd;
               bd.position.Set(0.0f, 6.0f);
               b2Body* pond1 = m_world->CreateBody(&bd);
               pond1->CreateFixture(&shape, 0.0f);
               shape.SetAsBox(0.25f, 6.0f);
               bd.position.Set(20.0f, 6.0f);
               pond1 = m_world->CreateBody(&bd);
               pond1->CreateFixture(&shape, 0.0f);
          }

          // Startup Elements
          {
               // Vertical Support
               b2PolygonShape shape;
               shape.SetAsBox(0.2f, 3.0f);
               b2BodyDef bd;
               bd.position.Set(0.0f, 81.0f);
               b2Body* ground = m_world->CreateBody(&bd);
               ground->CreateFixture(&shape, 0.0f);

               // Horizontal Support
               shape.SetAsBox(3.0f, 0.2f);
               bd.position.Set(0.0f, 84.2f);
               ground = m_world->CreateBody(&bd);
               ground->CreateFixture(&shape, 0.0f);

               // Ball which triggers
               {
                    b2Body* sbody;
                    b2CircleShape circle;
                    circle.m_radius = 1.0;
                    b2FixtureDef ballfd;
                    ballfd.shape = &circle;
                    ballfd.density = 2.0f;
                    ballfd.friction = 0.0f;
                    ballfd.restitution = 0.0f;
                    b2BodyDef ballbd;
                    ballbd.type = b2_dynamicBody;
                    ballbd.position.Set(-3.0f, 85.4f);
                    sbody = m_world->CreateBody(&ballbd);
                    sbody->CreateFixture(&ballfd);
               }
          }

          // Slanted Surface on Top
          {
               b2EdgeShape shape;
               shape.Set(b2Vec2(20.0f, 86.8f), b2Vec2(42.0f, 82.0f));
               b2BodyDef *bd=new b2BodyDef;
               b1 = m_world->CreateBody(bd);
               b1->CreateFixture(&shape, 0.0f);

               {
                    b2Body * curve1;
                    b2EdgeShape shape1[10];
                    b2BodyDef shape1bd[10];
                    b2FixtureDef shape1fd[10];

                    float32 x1 = -10.5f;
                    float32 y1 = 45.5f;
                    float32 radius1 = 20;
                    for(int i = 0 ; i < 5 ; i++){
                         shape1[i].Set(b2Vec2( x1+radius1*sin(5.0/4.0*b2_pi+i*b2_pi/20.0) , y1 + radius1*cos(5.0/4.0*b2_pi+i*b2_pi/20.0)) , b2Vec2( x1+radius1*sin(5.0/4.0*b2_pi+(i+1)*b2_pi/20.0) , y1 + radius1*cos(5.0/4.0*b2_pi+(i+1)*b2_pi/20.0)));
                         shape1fd[i].friction = 0;
                         shape1fd[i].shape = &shape1[i];
                         shape1fd[i].restitution = 1;
                         curve1 = m_world->CreateBody(&shape1bd[i]);
                         curve1->CreateFixture(&shape1fd[i]);
                    }
               }

               // Ball on Slanted Surface
               {
                    b2Body* sbody;
                    b2CircleShape circle;
                    circle.m_radius = 1.0;
                    b2FixtureDef ballfd;
                    ballfd.shape = &circle;
                    ballfd.density = 1.0f;
                    ballfd.friction = 0.0f;
                    ballfd.restitution = 0.0f;
                    b2BodyDef ballbd;
                    ballbd.type = b2_dynamicBody;
                    ballbd.position.Set(20.0f, 87.8f);
                    sbody = m_world->CreateBody(&ballbd);
                    sbody->CreateFixture(&ballfd);
                    // b2Vec2 force = b2Vec2(0, -10);
                    // sbody->SetLinearVelocity(force);
               }

               // Pulley System to Disturb Ball
               { 
                    bd->type=b2_dynamicBody;
                    bd->position.Set(7.0f,80.0f);
                    bd->fixedRotation=true;

                    // Open Box #1
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

                    // Open Box #2
                    bd->type=b2_dynamicBody;
                    bd->position.Set(17.0f,80.0f);
                    bd->fixedRotation=true;

                    fd1=new b2FixtureDef;
                    fd1->density = 10.0f;
                    fd1->friction = 0.5f;
                    fd1->restitution = 0.0f;
                    fd1->shape = new b2PolygonShape;
                    bs1.SetAsBox(2.0f, 2.0f);
                    bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
                    fd1->shape = &bs1;
                    fd2 = new b2FixtureDef;
                    fd2->density = 10.0;
                    fd2->friction = 0.5;
                    fd2->restitution = 0.f;
                    fd2->shape = new b2PolygonShape;
                    bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
                    fd2->shape = &bs2;
                    fd3 = new b2FixtureDef;
                    fd3->density = 10.0;
                    fd3->friction = 0.5;
                    fd3->restitution = 0.f;
                    fd3->shape = new b2PolygonShape;
                    bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
                    fd3->shape = &bs3;

                    b2Body* box2 = m_world->CreateBody(bd);
                    box2->CreateFixture(fd1);
                    box2->CreateFixture(fd2);
                    box2->CreateFixture(fd3);

                    // Pulley Joint
                    b2PulleyJointDef* myjoint = new b2PulleyJointDef();
                    b2Vec2 worldAnchorOnBody1(7.0f,80.0f); // Anchor point on body 1 in world axis
                    b2Vec2 worldAnchorOnBody2(17.0f,80.0f); // Anchor point on body 2 in world axis
                    b2Vec2 worldAnchorGround1(17.0, 90.0f); // Anchor point for ground 1 in world axis
                    b2Vec2 worldAnchorGround2(7.0f, 90.0f); // Anchor point for ground 2 in world axis
                    float32 ratio = 1.0f; // Define ratio
                    myjoint->Initialize(box2, box1, worldAnchorGround1, worldAnchorGround2, box2->GetWorldCenter(), box1->GetWorldCenter(), ratio);
                    m_world->CreateJoint(myjoint);
               }
          }

          // Revolving Platforms in the system
          {
               b2PolygonShape shape;
               b2BodyDef bd;
               b2PolygonShape shape2;
               b2BodyDef bd2;
               b2RevoluteJointDef jointDef;

               // Revolving Planck #1
               shape.SetAsBox(3.0f, 0.2f);
               bd.position.Set(50.0f, 60.0f);
               bd.type = b2_dynamicBody;
               b2Body* body = m_world->CreateBody(&bd);
               b2FixtureDef *fd = new b2FixtureDef;
               fd->density = 1.f;
               fd->shape = new b2PolygonShape;
               fd->shape = &shape;
               body->CreateFixture(fd);               
               shape2.SetAsBox(0.2f, 2.0f);               
               bd2.position.Set(50.0f, 60.0f);
               b2Body* body2 = m_world->CreateBody(&bd2);               
               jointDef.bodyA = body;
               jointDef.bodyB = body2;
               jointDef.localAnchorA.Set(0,0);
               jointDef.localAnchorB.Set(0,0);
               jointDef.collideConnected = false;
               m_world->CreateJoint(&jointDef);
               
               // Revolving Planck #2
               shape.SetAsBox(0.25f, 3.0f);
               bd.position.Set(41.2f, 63.0f);
               bd.type = b2_dynamicBody;
               body = m_world->CreateBody(&bd);
               fd = new b2FixtureDef;
               fd->density = 1.f;
               fd->shape = new b2PolygonShape;
               fd->shape = &shape;
               body->CreateFixture(fd);               
               shape2.SetAsBox(0.2f, 2.0f);               
               bd2.position.Set(41.2f, 63.0f);
               body2 = m_world->CreateBody(&bd2);               
               jointDef.bodyA = body;
               jointDef.bodyB = body2;
               jointDef.localAnchorA.Set(0,-3);
               jointDef.localAnchorB.Set(0,-3);
               jointDef.collideConnected = false;
               m_world->CreateJoint(&jointDef);

               // Revolving Planck #3
               shape.SetAsBox(0.25f, 3.0f);
               bd.position.Set(41.2f, 74.8f);
               bd.type = b2_dynamicBody;
               body = m_world->CreateBody(&bd);
               fd = new b2FixtureDef;
               fd->density = 1.f;
               fd->shape = new b2PolygonShape;
               fd->shape = &shape;
               body->CreateFixture(fd);               
               shape2.SetAsBox(0.2f, 2.0f);               
               bd2.position.Set(41.2f, 74.8f);
               body2 = m_world->CreateBody(&bd2);               
               jointDef.bodyA = body;
               jointDef.bodyB = body2;
               jointDef.localAnchorA.Set(0,-3);
               jointDef.localAnchorB.Set(0,-3);
               jointDef.collideConnected = false;
               m_world->CreateJoint(&jointDef);

               // Revolving Planck #4
               shape.SetAsBox(0.25f, 3.0f);
               bd.position.Set(43.2f, 79.8f);
               bd.type = b2_dynamicBody;
               body = m_world->CreateBody(&bd);
               fd = new b2FixtureDef;
               fd->density = 1.f;
               fd->shape = new b2PolygonShape;
               fd->shape = &shape;
               body->CreateFixture(fd);               
               shape2.SetAsBox(0.2f, 2.0f);               
               bd2.position.Set(43.2f, 79.8f);
               body2 = m_world->CreateBody(&bd2);               
               jointDef.bodyA = body;
               jointDef.bodyB = body2;
               jointDef.localAnchorA.Set(0,0);
               jointDef.localAnchorB.Set(0,0);
               jointDef.collideConnected = false;
               m_world->CreateJoint(&jointDef);

               // Revolving Planck #5
               shape.SetAsBox(3.0f, 0.2f);
               bd.position.Set(33.4f, 79.8f);
               bd.type = b2_dynamicBody;
               body = m_world->CreateBody(&bd);
               fd = new b2FixtureDef;
               fd->density = 1.f;
               fd->shape = new b2PolygonShape;
               fd->shape = &shape;
               body->CreateFixture(fd);               
               shape2.SetAsBox(0.2f, 2.0f);               
               bd2.position.Set(33.4f, 71.8f);
               body2 = m_world->CreateBody(&bd2);               
               jointDef.bodyA = body;
               jointDef.bodyB = body2;
               jointDef.localAnchorA.Set(0,0);
               jointDef.localAnchorB.Set(0,0);
               jointDef.collideConnected = false;
               m_world->CreateJoint(&jointDef);

               // Revolving Planck #6
               shape.SetAsBox(0.2f, 3.0f);
               bd.position.Set(33.4f, 67.0f);
               bd.type = b2_dynamicBody;
               body = m_world->CreateBody(&bd);
               fd = new b2FixtureDef;
               fd->density = 1.f;
               fd->shape = new b2PolygonShape;
               fd->shape = &shape;
               body->CreateFixture(fd);               
               shape2.SetAsBox(0.2f, 2.0f);               
               bd2.position.Set(33.4f, 67.0f);
               body2 = m_world->CreateBody(&bd2);               
               jointDef.bodyA = body;
               jointDef.bodyB = body2;
               jointDef.localAnchorA.Set(0,0);
               jointDef.localAnchorB.Set(0,0);
               jointDef.collideConnected = false;
               m_world->CreateJoint(&jointDef);

               // Revolving Planck #7
               shape.SetAsBox(3.0f, 0.2f);
               bd.position.Set(27.6f, 67.0f);
               bd.type = b2_dynamicBody;
               body = m_world->CreateBody(&bd);
               fd = new b2FixtureDef;
               fd->density = 1.f;
               fd->shape = new b2PolygonShape;
               fd->shape = &shape;
               body->CreateFixture(fd);               
               shape2.SetAsBox(0.2f, 2.0f);               
               bd2.position.Set(27.6f, 67.0f);
               body2 = m_world->CreateBody(&bd2);               
               jointDef.bodyA = body;
               jointDef.bodyB = body2;
               jointDef.localAnchorA.Set(0,0);
               jointDef.localAnchorB.Set(0,0);
               jointDef.collideConnected = false;
               m_world->CreateJoint(&jointDef);
               {
                    b2EdgeShape shape;
                    shape.Set(b2Vec2(20.6f, 58.5f), b2Vec2(27.2f, 63.5f));
                    b2BodyDef bd;
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(17.6f, 60.5f), b2Vec2(17.6f, 55.5f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(17.6f, 55.5f), b2Vec2(22.6f, 50.5f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(29.0f, 46.0f), b2Vec2(29.0f, 39.0f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(29.0f, 39.0f), b2Vec2(35.0f, 36.0f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);
               
                    shape.Set(b2Vec2(38.0f, 34.5f), b2Vec2(44.0f, 31.5f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(48.0f, 29.5f), b2Vec2(49.0f, 29.0f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(32.5f, 39.5f), b2Vec2(34.5f, 38.5f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(29.0f, 37.5f), b2Vec2(49.0f, 27.5f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(53.0f, 29.5f), b2Vec2(53.0f, 24.5f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(53.0f, 24.5f), b2Vec2(45.0f, 15.5f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(45.0f, 15.5f), b2Vec2(40.0f, 12.5f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(-15.0f, 80.0f), b2Vec2(-17.0f, 80.0f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);

                    shape.Set(b2Vec2(-19.0f, 80.0f), b2Vec2(-22.0f, 80.0f));
                    b1 = m_world->CreateBody(&bd);
                    b1->CreateFixture(&shape, 0.0f);
               }
               {
                    // Vertical Bar
                    b2PolygonShape shape;
                    shape.SetAsBox(0.2f, 3.0f);
                    b2FixtureDef fd;
                    fd.shape = &shape;
                    fd.density = 34.0f;
                    fd.friction = 0.1f;      
                    b2BodyDef *bd=new b2BodyDef;
                    bd->type = b2_dynamicBody;
                    bd->position.Set(32.0f, 42.0f);
                    b2Body* object_in_pond = m_world->CreateBody(bd);
                    object_in_pond->CreateFixture(&shape, 34.0f);

                    // Pulley System
                    bd->type=b2_dynamicBody;
                    bd->position.Set(24.0f,46.0f);
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
                    b2Vec2 worldAnchorOnBody1(32.0f,42.0f); // Anchor point on body 1 in world axis
                    b2Vec2 worldAnchorOnBody2(24.0f,46.0f); // Anchor point on body 2 in world axis
                    b2Vec2 worldAnchorGround1(32.0, 52.0f); // Anchor point for ground 1 in world axis
                    b2Vec2 worldAnchorGround2(24.0f, 52.0f); // Anchor point for ground 2 in world axis
                    float32 ratio = 1.0f; // Define ratio
                    myjoint->Initialize(object_in_pond, box1, worldAnchorGround1, worldAnchorGround2, object_in_pond->GetWorldCenter(), box1->GetWorldCenter(), ratio);
                    m_world->CreateJoint(myjoint);
               }
               {
                    b2Body* sbody;
                    b2CircleShape circle;
                    circle.m_radius = 1.0;
                    b2FixtureDef ballfd;
                    ballfd.shape = &circle;
                    ballfd.density = 1.0f;
                    ballfd.friction = 0.0f;
                    ballfd.restitution = 0.0f;
                    b2BodyDef ballbd;
                    ballbd.type = b2_dynamicBody;
                    ballbd.position.Set(30.0f, 46.0f);
                    sbody = m_world->CreateBody(&ballbd);
                    sbody->CreateFixture(&ballfd);
                    ballbd.position.Set(30.0f, 49.0f);
                    sbody = m_world->CreateBody(&ballbd);
                    sbody->CreateFixture(&ballfd);
                    ballbd.position.Set(30.0f, 51.0f);
                    sbody = m_world->CreateBody(&ballbd);
                    sbody->CreateFixture(&ballfd);

                    ballfd.density = 2000.0f;
                    ballbd.position.Set(-30.0f, 90.0f);
                    sbody = m_world->CreateBody(&ballbd);
                    sbody->CreateFixture(&ballfd);
               }

               // Revolving Planck #8
               shape.SetAsBox(4.0f, 0.2f);
               bd.position.Set(-14.0f, 82.0f);
               bd.type = b2_dynamicBody;
               body = m_world->CreateBody(&bd);
               fd = new b2FixtureDef;
               fd->density = 1.f;
               fd->shape = new b2PolygonShape;
               fd->shape = &shape;
               body->CreateFixture(fd);               
               shape2.SetAsBox(0.2f, 2.0f);               
               bd2.position.Set(-14.0f, 82.0f);
               body2 = m_world->CreateBody(&bd2);               
               jointDef.bodyA = body;
               jointDef.bodyB = body2;
               jointDef.localAnchorA.Set(0,0);
               jointDef.localAnchorB.Set(0,0);
               jointDef.collideConnected = false;
               m_world->CreateJoint(&jointDef);

               // Revolving Planck #9
               shape.SetAsBox(8.0f, 0.2f);
               bd.position.Set(-24.0f, 74.0f);
               bd.type = b2_dynamicBody;
               body = m_world->CreateBody(&bd);
               fd = new b2FixtureDef;
               fd->density = 1.f;
               fd->shape = new b2PolygonShape;
               fd->shape = &shape;
               body->CreateFixture(fd);               
               shape2.SetAsBox(0.2f, 2.0f);               
               bd2.position.Set(-24.0f, 74.0f);
               body2 = m_world->CreateBody(&bd2);               
               jointDef.bodyA = body;
               jointDef.bodyB = body2;
               jointDef.localAnchorA.Set(0,0);
               jointDef.localAnchorB.Set(0,0);
               jointDef.collideConnected = false;
               m_world->CreateJoint(&jointDef);
               {
                    b2BodyDef *bd=new b2BodyDef;
                    bd->type=b2_dynamicBody;
                    bd->position.Set(-18.0f,78.0f);
                    bd->fixedRotation=true;
                    b2FixtureDef *fd1=new b2FixtureDef;
                    fd1->density = 10.0f;
                    fd1->friction = 0.5f;
                    fd1->restitution = 0.0f;
                    fd1->shape = new b2PolygonShape;
                    b2PolygonShape bs1;
                    bs1.SetAsBox(1.5f,0.2f, b2Vec2(0.0f,2.2f), 0);
                    fd1->shape = &bs1;
                    b2FixtureDef *fd2 = new b2FixtureDef;
                    fd2->density = 10.0;
                    fd2->friction = 0.5;
                    fd2->restitution = 0.f;
                    fd2->shape = new b2PolygonShape;
                    b2PolygonShape bs2;
                    bs2.SetAsBox(0.2,2, b2Vec2(0.0f,0.0f), 0);
                    fd2->shape = &bs2;
                    b2FixtureDef *fd3 = new b2FixtureDef;
                    fd3->density = 10.0;
                    fd3->friction = 0.5;
                    fd3->restitution = 0.f;
                    fd3->shape = new b2PolygonShape;
                    b2PolygonShape bs3;
                    bs3.SetAsBox(1.5f,0.2f, b2Vec2(0.0f,-2.2f), 0);
                    fd3->shape = &bs3;

                    b2Body* box1 = m_world->CreateBody(bd);
                    box1->CreateFixture(fd1);
                    box1->CreateFixture(fd2);
                    box1->CreateFixture(fd3);
               }
          }

          // Bottom Horizontal Shelf
          {
               b2PolygonShape shape;
               shape.SetAsBox(8.0f, 0.25f);
               b2BodyDef bd;
               bd.position.Set(-11.0f, 12.0f);
               b2Body* ground = m_world->CreateBody(&bd);
               ground->CreateFixture(&shape, 0.0f);
          }

          // Dominoes
          {
               b2PolygonShape shape;
               shape.SetAsBox(0.1f, 1.0f);
               b2FixtureDef fd;
               fd.shape = &shape;
               fd.density = 20.0f;
               fd.friction = 0.1f;
               for (int i = 0; i < 12; ++i)
               {
                    b2BodyDef bd;
                    bd.type = b2_dynamicBody;
                    bd.position.Set(-17.0f + 1.0f * i, 15.0f);
                    b2Body* body = m_world->CreateBody(&bd);
                    body->CreateFixture(&fd);
               }
          }

          //The heavy sphere on the platform
          {
               b2Body* sbody;
               b2CircleShape circle;
               circle.m_radius = 1.0;
               b2FixtureDef ballfd;
               ballfd.shape = &circle;
               ballfd.density = 200.0f;
               ballfd.friction = 0.0f;
               ballfd.restitution = 0.0f;
               b2BodyDef ballbd;
               ballbd.type = b2_dynamicBody;
               ballbd.position.Set(-19.0f, 15.0f);
               sbody = m_world->CreateBody(&ballbd);
               sbody->CreateFixture(&ballfd);

               // Ball on small Slanted Surface
               ballfd.density = 20.0f;
               ballbd.position.Set(27.2f, 64.5f);
               sbody = m_world->CreateBody(&ballbd);
               sbody->CreateFixture(&ballfd);
          }

          //Boat Structure
          {
               b2BodyDef *bd=new b2BodyDef;
               bd->type=b2_dynamicBody;
               bd->gravityScale=0.0;
               bd->position.Set(17.0f,13.3f);
               bd->fixedRotation=true;
               b2FixtureDef *fd1=new b2FixtureDef;
               fd1->density = 0.0f;
               fd1->friction = 0.0f;
               fd1->restitution = 0.0f;
               fd1->shape = new b2PolygonShape;
               b2PolygonShape bs1;
               bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
               fd1->shape = &bs1;
               b2FixtureDef *fd2 = new b2FixtureDef;
               fd2->density = 0.0;
               fd2->friction = 0.0;
               fd2->restitution = 0.f;
               fd2->shape = new b2PolygonShape;
               b2PolygonShape bs2;
               bs2.SetAsBox(0.2,4, b2Vec2(0.0f,2.0f), 0);
               fd2->shape = &bs2;
               b2FixtureDef *fd3 = new b2FixtureDef;
               fd3->density = 0.0;
               fd3->friction = 0.0;
               fd3->restitution = 0.f;
               fd3->shape = new b2PolygonShape;
               b2PolygonShape bs3;
               bs3.SetAsBox(10.0,0.2f, b2Vec2(0.0f,0.0f), 0);
               fd3->shape = &bs3;
               b2Body* boat = m_world->CreateBody(bd);
               boat->CreateFixture(fd1);
               boat->CreateFixture(fd2);
               boat->CreateFixture(fd3);
          }

          // Horizontal Planck before Pond with Boat
          {
               b2PolygonShape shape;
               shape.SetAsBox(8.0f, 0.25f);
               b2BodyDef bd;
               bd.position.Set(31.0f, 12.0f);
               b2Body* ground = m_world->CreateBody(&bd);
               ground->CreateFixture(&shape, 0.0f);
          }

          // Bottom Pulley System
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
