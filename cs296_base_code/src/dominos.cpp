// Files Included
#include "cs296_base.hpp"
#include "render.hpp"

// Graphic Libraries Included
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
     #include "GL/freeglut.h"
#endif

// Other Libraries Included
#include <cstring>
using namespace std;

#include "dominos.hpp"

// Simulation Main Code
namespace cs296
{
    dominos_t::dominos_t(){
          
          //! <em><b> b2Body* b1 </b></em> : </b> b1 is a pointer to an object of b2Body class. This is used to create a number of bodies in our code
          b2Body* b1;

          // Ground
          //! <b> Ground </b>
          //! - <em><b> b2EdgeShape shape </b></em> : This is used to define the shape of Ground as an edge
          //! - <em><b> shape.Set(b2Vec2 X, b2Vec2 Y) </b></em> : This define shape as an edge from point X to point Y
          //! - <em><b> b2BodyDef bd </b></em> : This is used for defining a body in the world
          //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
          //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
          {
               b2EdgeShape shape;
               shape.Set(b2Vec2(-80.0f, 0.0f), b2Vec2(80.0f, 0.0f));
               b2BodyDef bd;
               b1 = m_world->CreateBody(&bd);
               b1->CreateFixture(&shape, 0.0f);
          }

          // Pendulum
          //! <b> Pendulum </b>
          {
               //! - <b> Horizontal Plancks </b>
               //! - <em><b> b2PolygonShape shape </b></em> : This gives shape to bodies which make up the pendulum
               //! - <em><b> shape.SetAsBox(X,Y) </b></em> : This defines shape of hirizontal planck which hangs the pendulum bobs. X=horizontal_length, Y=vertical_length
               //! - <em><b> b2BodyDef bd </b></em> : This is used for defining a body in the world
               //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
               //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
               //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
               b2Body* b2;
               {
                    b2PolygonShape shape;
                    shape.SetAsBox(4.0f, 0.2f);                      
                    b2BodyDef bd;
                    bd.position.Set(-9.0f, 95.0f);
                    b2 = m_world->CreateBody(&bd);
                    b2->CreateFixture(&shape, 10.0f);
               }

               //! - <b> Pendulum Bobs </b>
               //! - <em><b> b2CircleShape circle </b></em> : This is used for defining circular shape of pendulum bob
               //! - <em><b> circle.m_radius </b></em> : Radius of bob
               //! - <em><b> b2FixtureDef ballfd </b></em> : It is used to fix some properties of the body in the world
               //! - <em><b> ballfd.shape </b></em> : Shape of bob
               //! - <em><b> ballfd.density </b></em> : Density of bob
               //! - <em><b> ballfd.friction </b></em> : Friction Coefficient of bob
               //! - <em><b> ballfd.restitution </b></em> : Restitutioon Coefficient of bob
               //! - <em><b> ballbd.type = b2_dynamicBody </b></em> : Defines bob as a dynamic body
               //! - <em><b> b2RevoluteJointDef jd </b></em> : This is used for defining central point on horizontal planck about which bob revolutes
               //! - <em><b> ballbd.position.Set(X,Y) </b></em> : This is used initial position of center of bob
               //! - <em><b> b2Vec2 anchor </b></em> : This is used for defining string connected to bob
               //! - <em><b> anchor.Set(X,Y) </b></em> : This defines the point at which string connects the bob 
               //! - <em><b> jd.Initialize(b2, sbody, anchor) </b></em> : This connects the two bodies b2, sbody and sbody can revolute around point anchor on b2
               //! - <em><b> CreateJoint </b></em> : This creates the system of planck, bob and string in the world
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

          // Water Ponds
          //! <b> Water Ponds </b>
          //! - <em><b> b2PolygonShape shape </b></em> : This gives shape to bodies which make up the pond walls
          //! - <em><b> shape.SetAsBox(X,Y) </b></em> : This defines shape of walls of pond which hangs the pendulum bobs. X=horizontal_length, Y=vertical_length
          //! - <em><b> b2BodyDef bd </b></em> : This is used for defining a body in the world
          //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
          //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
          //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
          {
               // Water Pond 1
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
          {
               // Water Pond 2
               b2PolygonShape shape;
               shape.SetAsBox(0.25f, 6.0f);     
               b2BodyDef bd;
               bd.position.Set(0.0f, 6.0f);
               b2Body* pond1 = m_world->CreateBody(&bd);
               pond1->CreateFixture(&shape, 0.0f);
               shape.SetAsBox(0.25f, 6.0f);
               bd.position.Set(20.0f, 6.0f);
               pond1 = m_world->CreateBody(&bd);
               pond1->CreateFixture
               (&shape, 0.0f);
          }

          // Startup Elements
          //! <b> Startup Elements </b>
          {
               // Vertical Support
               //! - <b> Vertical and Horizontal Supports </b>
               //! - <em><b> b2PolygonShape shape </b></em> : This gives shape to horizontal and vertical support plancks
               //! - <em><b> shape.SetAsBox(X,Y) </b></em> : This defines shape of hirizontal and vertical plancks. X=horizontal_length, Y=vertical_length
               //! - <em><b> b2BodyDef bd </b></em> : This is used for defining a body in the world     
               //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
               //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
               //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z          
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

               // Ball which triggers Simulation
               //! - <b> Ball which triggers Simulation</b>
               //! - <em><b> b2CircleShape circle </b></em> : This is used for defining circular shape of ball
               //! - <em><b> circle.m_radius </b></em> : Radius of ball
               //! - <em><b> b2FixtureDef ballfd </b></em> : It is used to fix some properties of the body in the world
               //! - <em><b> ballfd.shape </b></em> : Shape of ball
               //! - <em><b> ballfd.density </b></em> : Density of ball
               //! - <em><b> ballfd.friction </b></em> : Friction Coefficient of ball
               //! - <em><b> ballfd.restitution </b></em> : Restitutioon Coefficient of ball
               //! - <em><b> ballbd.type = b2_dynamicBody </b></em> : Defines ball as a dynamic body
               //! - <em><b> ballbd.position.Set(X,Y) </b></em> : This is used initial position of center of ball
               //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
               //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z    
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

          // Slanted Surface on top
          //! <b> Slanted Surface on Top </b>
          {
               // Slanted Surface
               //! - <b> Slanted Surface </b>
               //! - <em><b> b2EdgeShape shape </b></em> : This is used to define the shape of Slanted Surface as an edge
               //! - <em><b> shape.Set(b2Vec2 X, b2Vec2 Y) </b></em> : This define shape as an edge from point X to point Y
               //! - <em><b> b2BodyDef *bd </b></em> : This is used for defining a body in the world
               //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
               //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
               b2EdgeShape shape;
               shape.Set(b2Vec2(20.0f, 86.8f), b2Vec2(42.0f, 82.0f));
               b2BodyDef *bd=new b2BodyDef;
               b1 = m_world->CreateBody(bd);
               b1->CreateFixture(&shape, 0.0f);

               // Ball on Slanted Surface
               //! - <b> Ball on Slanted Surface </b>
               //! - <em><b> b2CircleShape circle </b></em> : This is used for defining circular shape of ball
               //! - <em><b> circle.m_radius </b></em> : Radius of ball
               //! - <em><b> b2FixtureDef ballfd </b></em> : It is used to fix some properties of the body in the world
               //! - <em><b> ballfd.shape </b></em> : Shape of ball
               //! - <em><b> ballfd.density </b></em> : Density of ball
               //! - <em><b> ballfd.friction </b></em> : Friction Coefficient of ball
               //! - <em><b> ballfd.restitution </b></em> : Restitutioon Coefficient of ball
               //! - <em><b> ballbd.type = b2_dynamicBody </b></em> : Defines ball as a dynamic body
               //! - <em><b> ballbd.position.Set(X,Y) </b></em> : This is used initial position of center of ball
               //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
               //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z    
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
               }

               // Pulley System to Disturb Ball
               //! - <b> Pulley System to Disturb Ball </b>

               { 
                    bd->type=b2_dynamicBody;
                    bd->position.Set(7.0f,80.0f);
                    bd->fixedRotation=true;

                    // Open Box #1
                    //! - <b> Open Box 1 </b>
                    //! - <em><b> b2BodyDef *bd </b></em> : This is used for defining a body in the world 
                    //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
                    //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
                    //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
                    //! - <em><b> b2FixtureDef fd </b></em> : It is used to fix some properties of the body in the world
                    //! - <em><b> fd->shape </b></em> : Shape of boat parts
                    //! - <em><b> fd->density </b></em> : Density of planck
                    //! - <em><b> bd->type=b2_dynamicBody </b></em> : Makes box a dynamic body
                    //! - <em><b> fd->friction </b></em> : Friction Coeffecient of box parts
                    //! - <em><b> fd->restitution </b></em> : Restitution Coeffecient of box parts
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
                    //! - <b> Open Box 1 </b>
                    //! - <em><b> b2BodyDef *bd </b></em> : This is used for defining a body in the world 
                    //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
                    //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
                    //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
                    //! - <em><b> b2FixtureDef fd </b></em> : It is used to fix some properties of the body in the world
                    //! - <em><b> fd->shape </b></em> : Shape of boat parts
                    //! - <em><b> fd->density </b></em> : Density of planck
                    //! - <em><b> bd->type=b2_dynamicBody </b></em> : Makes box a dynamic body
                    //! - <em><b> fd->friction </b></em> : Friction Coeffecient of box parts
                    //! - <em><b> fd->restitution </b></em> : Restitution Coeffecient of box parts
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
                    //! - <b> Pulley Joint </b>
                    //!- <em><b> b2PulleyJointDef* myjoint = new b2PulleyJointDef() </b></em> : It defines a pulley system with two bodies
                    //!- <em><b> b2Vec2 worldAnchorOnBody1(X,Y) </b></em> : Point at which strng is attached to body1
                    //!- <em><b> b2Vec2 worldAnchorOnBody2(X,Y) </b></em> : Point at which strng is attached to body2
                    //!- <em><b> b2Vec2 worldAnchorGround1(X,Y) </b></em> : Point at which strng attached to body1 is fixed in world
                    //!- <em><b> b2Vec2 worldAnchorGround2(X,Y) </b></em> : Point at which strng attached to body2 is fixed in world
                    //!- <em><b> myjoint->Initialize(body1, body2, point_on_body1, point_on_body2, point_in_world_corressponding_to_body1, point_in_world_corressponding_to_body2) </b></em> : This initialises the pulley system 
                    //!- <em><b> m_world->CreateJoint(myjoint) </b></em> : Creates pulley system in the world
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

          // Other spheres in Simulation
          //! <b> Other Spheres in Simulation </b>          
          //! - <em><b> b2CircleShape circle </b></em> : This is used for defining circular shape of ball
          //! - <em><b> circle.m_radius </b></em> : Radius of ball
          //! - <em><b> b2FixtureDef ballfd </b></em> : It is used to fix some properties of the body in the world
          //! - <em><b> ballfd.shape </b></em> : Shape of ball
          //! - <em><b> ballfd.density </b></em> : Density of ball
          //! - <em><b> ballfd.friction </b></em> : Friction Coefficient of ball
          //! - <em><b> ballfd.restitution </b></em> : Restitutioon Coefficient of ball
          //! - <em><b> ballbd.type = b2_dynamicBody </b></em> : Defines ball as a dynamic body
          //! - <em><b> ballbd.position.Set(X,Y) </b></em> : This is used initial position of center of ball
          //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
          //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
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

          // Other Surfaces in Simulation 
          //! <b> Other Surfaces in Simulation </b>
          //! - <em><b> b2EdgeShape shape </b></em> : This is used to define the shape of Surface as an edge
          //! - <em><b> shape.Set(b2Vec2 X, b2Vec2 Y) </b></em> : This define shape as an edge from point X to point Y
          //! - <em><b> b2BodyDef *bd </b></em> : This is used for defining a body in the world
          //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
          //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
          {
               b2EdgeShape shape;
               shape.Set(b2Vec2(14.6f, 59.5f), b2Vec2(27.2f, 63.5f));
               b2BodyDef bd;
               b1 = m_world->CreateBody(&bd);
               b1->CreateFixture(&shape, 0.0f);

               shape.Set(b2Vec2(16.6f, 54.5f), b2Vec2(22.6f, 50.5f));
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

          // Rotating Platforms in the System
          //! <b> Rotating Platforms in the system </b>
          //! - <em><b> b2PolygonShape shape </b></em> : This gives shape to horizontal and vertical support plancks
          //! - <em><b> shape.SetAsBox(X,Y) </b></em> : This defines shape of rotating plancks. X=horizontal_length, Y=vertical_length
          //! - <em><b> b2BodyDef bd </b></em> : This is used for defining a body in the world 
          //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
          //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
          //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
          //! - <em><b> b2FixtureDef fd </b></em> : It is used to fix some properties of the body in the world
          //! - <em><b> fd->shape </b></em> : Shape of planck
          //! - <em><b> fd->density </b></em> : Density of planck
          //! - <em><b> b2RevoluteJointDef jointDef </b></em> : This is used for defining point about which planck rotates
          //! - <em><b> ballfd.restitution </b></em> : Restitutioon Coefficient of ball
          //! - <em><b> jointDef.body = b1 </b></em> : This joins body b1 to the axis point
          //! - <em><b> jointDef.localAnchorA.Set(X,Y) </b></em> : This sets the point about which axis of rotation passes. X=x_coordinate, Y=y_coordinate 
          {
               b2PolygonShape shape;
               b2BodyDef bd;
               b2PolygonShape shape2;
               b2BodyDef bd2;
               b2RevoluteJointDef jointDef;
               
               // Revolving Planck #3
               shape.SetAsBox(0.25f, 3.0f);
               bd.position.Set(41.2f, 74.8f);
               bd.type = b2_dynamicBody;
               b2Body* body = m_world->CreateBody(&bd);
               b2FixtureDef* fd = new b2FixtureDef;
               fd->density = 1.f;
               fd->shape = new b2PolygonShape;
               fd->shape = &shape;
               body->CreateFixture(fd);               
               shape2.SetAsBox(0.2f, 2.0f);               
               bd2.position.Set(41.2f, 74.8f);
               b2Body* body2 = m_world->CreateBody(&bd2);               
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

               // Revolving Planck #10
               shape.SetAsBox(8.0f, 0.2f);
               bd.position.Set(8.0f, 57.0f);
               bd.type = b2_dynamicBody;
               body = m_world->CreateBody(&bd);
               fd = new b2FixtureDef;
               fd->density = 1.f;
               fd->shape = new b2PolygonShape;
               fd->shape = &shape;
               body->CreateFixture(fd);               
               shape2.SetAsBox(0.2f, 2.0f);               
               bd2.position.Set(8.0f, 57.0f);
               body2 = m_world->CreateBody(&bd2);               
               jointDef.bodyA = body;
               jointDef.bodyB = body2;
               jointDef.localAnchorA.Set(0,0);
               jointDef.localAnchorB.Set(0,0);
               jointDef.collideConnected = false;
               m_world->CreateJoint(&jointDef);
          }

          // Second Pulley System
          //! <b> Top Pulley Triggering </b>
          {
               // Vertical Bar
               //! - <b> Vertical Bar </b>
               //! - <em><b> b2PolygonShape shape </b></em> : This gives shape to a bar
               //! - <em><b> shape.SetAsBox(X,Y) </b></em> : This defines shape of bar. X=horizontal_length, Y=vertical_length
               //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
               //! - <em><b> b2FixtureDef fd </b></em> : It is used to fix some properties of the body in the world
               //! - <em><b> fd->shape </b></em> : Shape of bar
               //! - <em><b> fd->density </b></em> : Density of bar
               //! - <em><b> bd->type=b2_dynamicBody </b></em> : Makes bar a dynamic body
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
               //! - <b> Open Box attached to pulley rope </b>
               //! - <em><b> b2BodyDef *bd </b></em> : This is used for defining a body in the world 
               //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
               //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
               //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
               //! - <em><b> b2FixtureDef fd </b></em> : It is used to fix some properties of the body in the world
               //! - <em><b> fd->shape </b></em> : Shape of boat parts
               //! - <em><b> fd->density </b></em> : Density of planck
               //! - <em><b> bd->type=b2_dynamicBody </b></em> : Makes box a dynamic body
               //! - <em><b> fd->friction </b></em> : Friction Coeffecient of box parts
               //! - <em><b> fd->restitution </b></em> : Restitution Coeffecient of box parts
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
               //! - <b> Pulley Joint </b>
               //!- <em><b> b2PulleyJointDef* myjoint = new b2PulleyJointDef() </b></em> : It defines a pulley system with two bodies
               //!- <em><b> b2Vec2 worldAnchorOnBody1(X,Y) </b></em> : Point at which strng is attached to body1
               //!- <em><b> b2Vec2 worldAnchorOnBody2(X,Y) </b></em> : Point at which strng is attached to body2
               //!- <em><b> b2Vec2 worldAnchorGround1(X,Y) </b></em> : Point at which strng attached to body1 is fixed in world
               //!- <em><b> b2Vec2 worldAnchorGround2(X,Y) </b></em> : Point at which strng attached to body2 is fixed in world
               //!- <em><b> myjoint->Initialize(body1, body2, point_on_body1, point_on_body2, point_in_world_corressponding_to_body1, point_in_world_corressponding_to_body2) </b></em> : This initialises the pulley system 
               //!- <em><b> m_world->CreateJoint(myjoint) </b></em> : Creates pulley system in the world
               b2PulleyJointDef* myjoint = new b2PulleyJointDef();
               b2Vec2 worldAnchorOnBody1(32.0f,42.0f); // Anchor point on body 1 in world axis
               b2Vec2 worldAnchorOnBody2(24.0f,46.0f); // Anchor point on body 2 in world axis
               b2Vec2 worldAnchorGround1(32.0, 52.0f); // Anchor point for ground 1 in world axis
               b2Vec2 worldAnchorGround2(24.0f, 52.0f); // Anchor point for ground 2 in world axis
               float32 ratio = 1.0f; // Define ratio
               myjoint->Initialize(object_in_pond, box1, worldAnchorGround1, worldAnchorGround2, object_in_pond->GetWorldCenter(), box1->GetWorldCenter(), ratio);
               m_world->CreateJoint(myjoint);
          }

          // Bottom Horizontal Shelf
          //! <b> Bottom Horizontal Shelf </b>
          //! - <em><b> b2PolygonShape shape </b></em> : This gives shape to planck
          //! - <em><b> shape.SetAsBox(X,Y) </b></em> : This defines shape of planck. X=horizontal_length, Y=vertical_length
          //! - <em><b> b2BodyDef bd </b></em> : This is used for defining a body in the world
          //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
          //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
          //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
          {
               b2PolygonShape shape;
               shape.SetAsBox(8.0f, 0.25f);
               b2BodyDef bd;
               bd.position.Set(-11.0f, 12.0f);
               b2Body* ground = m_world->CreateBody(&bd);
               ground->CreateFixture(&shape, 0.0f);
          }

          // Dominoes
          //! <b> Dominoes </b>
          //! - <em><b> b2PolygonShape shape </b></em> : This gives shape to a dominoe
          //! - <em><b> shape.SetAsBox(X,Y) </b></em> : This defines shape of planck. X=horizontal_length, Y=vertical_length
          //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
          //! - <em><b> b2FixtureDef fd </b></em> : It is used to fix some properties of the body in the world
          //! - <em><b> fd->shape </b></em> : Shape of dominoe
          //! - <em><b> fd->density </b></em> : Density of dominoe
          //! - <em><b> bd->type=b2_dynamicBody </b></em> : Makes dominoe a dynamic body
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

          // Heavy sphere on lowest platform
          //! <b> The heavy sphere on the lowest platform </b>
          //! - <em><b> b2CircleShape circle </b></em> : This is used for defining circular shape of ball
          //! - <em><b> circle.m_radius </b></em> : Radius of ball
          //! - <em><b> b2FixtureDef ballfd </b></em> : It is used to fix some properties of the body in the world
          //! - <em><b> ballfd.shape </b></em> : Shape of ball
          //! - <em><b> ballfd.density </b></em> : Density of ball
          //! - <em><b> ballfd.friction </b></em> : Friction Coefficient of ball
          //! - <em><b> ballfd.restitution </b></em> : Restitutioon Coefficient of ball
          //! - <em><b> ballbd.type = b2_dynamicBody </b></em> : Defines ball as a dynamic body
          //! - <em><b> ballbd.position.Set(X,Y) </b></em> : This is used initial position of center of ball
          //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
          //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z 
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

          // Boat Structure
          //! <b> Boat Structure </b>
          //! - <em><b> b2BodyDef *bd </b></em> : This is used for defining a body in the world 
          //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
          //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
          //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
          //! - <em><b> b2FixtureDef fd </b></em> : It is used to fix some properties of the body in the world
          //! - <em><b> fd->shape </b></em> : Shape of boat parts
          //! - <em><b> fd->density </b></em> : Density of planck
          //! - <em><b> bd->type=b2_dynamicBody </b></em> : Makes boat a dynamic body
          //! - <em><b> fd->friction </b></em> : Friction Coeffecient of boat
          //! - <em><b> fd->restitution </b></em> : Restitution Coeffecient of boat
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
          //! <b> Horizontal Planck before Pond with Boat </b>
          //! - <em><b> b2PolygonShape shape </b></em> : This gives shape to planck
          //! - <em><b> shape.SetAsBox(X,Y) </b></em> : This defines shape of planck. X=horizontal_length, Y=vertical_length
          //! - <em><b> b2BodyDef bd </b></em> : This is used for defining a body in the world
          //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
          //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
          //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
          {
               b2PolygonShape shape;
               shape.SetAsBox(8.0f, 0.25f);
               b2BodyDef bd;
               bd.position.Set(31.0f, 12.0f);
               b2Body* ground = m_world->CreateBody(&bd);
               ground->CreateFixture(&shape, 0.0f);
          }

          // Bottom Pulley System
          //! <b> Bottom Pulley System </b>
          {
               // Object in pond
               //! - <b> Heavy Object in pond </b>
               //! - <em><b> b2BodyDef *bd </b></em> : This is used for defining a body in the world 
               //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
               //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
               //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
               //! - <em><b> b2FixtureDef fd </b></em> : It is used to fix some properties of the body in the world
               //! - <em><b> fd->shape </b></em> : Shape of boat parts
               //! - <em><b> fd->density </b></em> : Density of planck
               //! - <em><b> bd->type=b2_dynamicBody </b></em> : Makes box a dynamic body
               //! - <em><b> fd->friction </b></em> : Friction Coeffecient of box
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
               //! - <b> Open Box attached to pulley rope </b>
               //! - <em><b> b2BodyDef *bd </b></em> : This is used for defining a body in the world 
               //! - <em><b> bd.position.Set(X,Y) </b></em> : This defines position of body in world. X=x_coordinate, Y=y_cooridinate
               //! - <em><b> m_world->CreateBody(&bd) </b></em> : This creates a body in the world (simulation)
               //! - <em><b> CreateFixture(&shape, z) </b></em> : This gives shape to body created in the world and also gives it density equal to z
               //! - <em><b> b2FixtureDef fd </b></em> : It is used to fix some properties of the body in the world
               //! - <em><b> fd->shape </b></em> : Shape of boat parts
               //! - <em><b> fd->density </b></em> : Density of planck
               //! - <em><b> bd->type=b2_dynamicBody </b></em> : Makes box a dynamic body
               //! - <em><b> fd->friction </b></em> : Friction Coeffecient of box parts
               //! - <em><b> fd->restitution </b></em> : Restitution Coeffecient of box parts
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
               //! - <b> Pulley Joint </b>
               //!- <em><b> b2PulleyJointDef* myjoint = new b2PulleyJointDef() </b></em> : It defines a pulley system with two bodies
               //!- <em><b> b2Vec2 worldAnchorOnBody1(X,Y) </b></em> : Point at which strng is attached to body1
               //!- <em><b> b2Vec2 worldAnchorOnBody2(X,Y) </b></em> : Point at which strng is attached to body2
               //!- <em><b> b2Vec2 worldAnchorGround1(X,Y) </b></em> : Point at which strng attached to body1 is fixed in world
               //!- <em><b> b2Vec2 worldAnchorGround2(X,Y) </b></em> : Point at which strng attached to body2 is fixed in world
               //!- <em><b> myjoint->Initialize(body1, body2, point_on_body1, point_on_body2, point_in_world_corressponding_to_body1, point_in_world_corressponding_to_body2) </b></em> : This initialises the pulley system 
               //!- <em><b> m_world->CreateJoint(myjoint) </b></em> : Creates pulley system in the world
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
