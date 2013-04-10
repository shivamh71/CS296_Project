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

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#ifndef _CS296BASE_HPP_
#define _CS296BASE_HPP_

#include "render.hpp"
#include <Box2D/Box2D.h>
#include <cstdlib>

#define	RAND_LIMIT 32767

namespace cs296
{

  /*! Struct in C++ is used to various variables of different or same type together whereas class provide an additional
  functionality of grouping methods along with the varaibles into a single unit
  */
  class base_sim_t;
  struct settings_t;
  
  //! typedef is used to create a user defined variable type, mostly to avoid writing bigger typenames again and again.\n
  //! It provides clarity and good structure to the code
  typedef base_sim_t* sim_create_fcn(); 

  //! \b settings_t() \b : Simulation settings. Some can be controlled in the GUI.\n
  //! \b view_center(0.0f, 20.0f) \b : this function call sets the center of gui as (0.0,20.0)\n
  //! \b velocity_iterations(8) \b : It sets the default no. of velocity iterations to 8, each iteration involves a single pass over all the constraints\n
  //! \b position_iterations(3) \b : It sets default no of position iteration to 3\n
  //! \b draw_shapes(1) \b : It sets draw_shapes property to 1 which enables drawing of shapes\n 
  //! \b draw_joints(1) \b : It sets draw_joint property to 1 which enables drawing of joints\n
  //! \b draw_AABBs(0) \b : It sets draw_AABBs property to 0 which disables drawing of bounding boxes\n
  //! \b draw_pairs(0) \b : It sets draw_pairs property to 0 \n
  //! \b draw_contact_points(0) \b : It sets draw_contact_points property to 0 which disables appearing of contact points\n
  //! \b draw_contact_normals(0) \b : It sets draw_contact_normals property to 0 which disables appearing of contact normals\n
  //! \b draw_contact_forces(0) \b : It sets draw_contact_forces property to 0 which disables showing of contact forces\n
  //! \b draw_friction_forces(0) \b : It sets draw_friction_forces property to 0 which disables showing of friction forces\n
  //! \b draw_COMs(0) \b : This disables showing of COMs\n
  //! \b draw_stats(0) \b : Disable showing of statistics on the screen\n
  //! \b draw_profile(0) \b : It disables showing of profile on the screen\n
  //! \b enable_warm_starting(1) \b : It enables warm starting of simulation\n
  //! \b enable_continuous(1) \b : It enables the continuous property for continued calculation of velocity, positiion etc\n
  //! \b enable_sub_stepping(0) \b : This disables sub_stepping property\n
  //! \b pause(0) \b : It disables the pause\n
  //! \b single_step(0) \b : it disables the single step process. Single step enables us to see the simulation step by step\n
  //! \b b2Vec2 view_center \b : this defines the center of GUI\n
  //! \b int32 \b velocity_iterations \b : This stores the number of velocity iteration which is no of passes over velocity constraints in one time step\n
  //! \b int32 \b position_iterations \b : This stores the number of position iteration which is no of passes over position constraints in one time step\n
  //! \b int32 \b draw_shapes \b : Enabling / Disabling key of drawing shapes on GUI\n
  //! \b int32 \b draw_joints \b : Enabling / Disabling key of drawing joints on GUI\n
  //! \b int32 \b draw_AABBs \b : Enabling / Disabling key of drawing enclosing boxes on GUI\n
  //! \b int32 \b draw_pairs \b : Enabling / Disabling key of drawing pairs on GUI\n
  //! \b int32 \b draw_contact_points \b : Enabling / Disabling key of drawing contact points on GUI\n
  //! \b int32 \b draw_contact_normals \b : Enabling / Disabling key of drawing contact normals on GUI\n
  //! \b int32 \b draw_contact_forces \b : Enabling / Disabling key of drawing contact forces on GUI\n
  //! \b int32 \b draw_friction_force \b : Enabling / Disabling key of drawing friction forces on GUI\n
  //! \b int32 \b draw_COMs \b : Enabling / Disabling key of drawing COMs on GUI\n
  //! \b int32 \b draw_stats \b : Enabling / Disabling key of drawing statistics on GUI\n
  //! \b int32 \b draw_profile \b : Enabling / Disabling key of showing profile on GUI\n
  //! \b int32 \b enable_warm_starting \b : Enabling / Disabling key of warm starting of simulation\n
  //! \b int32 \b enable_continuous \b : Enabling / Disabling key of continuous evaluation of velocity and position\n
  //! \b int32 \b enable_sub_stepping \b : Enabling / Disabling key of sub stepping property\n
  //! \b int32 \b pause \b : Enabling / Disabling key of pausing button\n
  //! \b int32 \b single_step \b : Enabling / Disabling key of single stepping button\n
  struct settings_t
  {
    
    settings_t() :
      view_center(0.0f, 20.0f), 
      hz(60.0f), 
      velocity_iterations(8), 
      position_iterations(3),  
      draw_shapes(1),
      draw_joints(1),
      draw_AABBs(0),
      draw_pairs(0),
      draw_contact_points(0),
      draw_contact_normals(0),
      draw_contact_forces(0),
      draw_friction_forces(0),
      draw_COMs(0),
      draw_stats(0),
      draw_profile(0),
      enable_warm_starting(1),
      enable_continuous(1),
      enable_sub_stepping(0),
      pause(0),
      single_step(0)
    {}
    
    b2Vec2 view_center;
    float32 hz;
    int32 velocity_iterations;
    int32 position_iterations;
    int32 draw_shapes;
    int32 draw_joints;
    int32 draw_AABBs;
    int32 draw_pairs;
    int32 draw_contact_points;
    int32 draw_contact_normals;
    int32 draw_contact_forces;
    int32 draw_friction_forces;
    int32 draw_COMs;
    int32 draw_stats;
    int32 draw_profile;
    int32 enable_warm_starting;
    int32 enable_continuous;
    int32 enable_sub_stepping;
    int32 pause;
    int32 single_step;
  };
  
  //! \b const \b char \b *name \b : An dentifier of character type\n
  //! \b sim_create_fcn \b *create_fcn \b : It is a pointer to an object of type sim_create_fcn which stores reference to base_sim_t struct\n
  //! \b sim_t(const char *_name, sim_create_fcn *_create_fcn) \b : Constructor for the struct sim_t\n 
  struct sim_t
  {
    const char *name;
    sim_create_fcn *create_fcn;

    sim_t(const char *_name, sim_create_fcn *_create_fcn): 
      name(_name), create_fcn(_create_fcn) {;}
  };
  
  extern sim_t *sim;
  
  
  const int32 k_max_contact_points = 2048; 
  //! This defines one of the contact points\n
  //! \b b2Fixture* \b fixtureA \b : It defines first fixture in contact \n
  //! \b b2Fixture* \b fixtureB \b : It defines another fixture in contact\n
  //! \b b2Vec2 \b normal \b : It defines normal to the contact point\n
  //! \b b2Vec2 \b position \b : It stores the position of point of contact\n 
  //! \b b2PointState \b state \b : It stores the state of point of contact\n
  struct contact_point_t
  {
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
    b2Vec2 normal;
    b2Vec2 position;
    b2PointState state;
  };
  
  //! \b b2Body* \b m_ground_body \b : It refers to the body which is on the ground in the simulation.\n
  //! \b b2AABB \b m_world_AABB \b :  It refers to the enclosing boxses around objects\n
  //! \b contact_point_t \b m_points[k_max_contact_points] \b : It is an array to store contact points with maximum size possible. \n
  //! \b int32 \b m_point_count \b : This stores the total number of contact points. \n 
  //! \b debug_draw_t \b m_debug_draw \b : It is used to provide debug drawing in the physics part of the game. \n 
  //! \b int32 \b m_text_line \b : it stores the number of lines used when profile or statistics is showed in GUI \n 
  //! \b b2World* \b m_world \b : It is an object of type b2World, it handles all the physcs related to simulation all movements. \n
  //! \b int32 \b m_step_count \b : Total number of steps occurred till the present time. \n
  //! \b b2Profile \b m_max_profile \b : it stores the maximum profile time. \n 
  //! \b b2Profile \b m_total_profile \b : It stores the total profile time. \n 
  //! \b set_text_line(int32 line) : It sets the maximum number of lines used when showing profile or statistics. \n 
  //! \b draw_title(int x, int y, const char *string) : This method writes the title at given co-ordinates of a particular name(string). \n 
  //! \b  step(settings_t* settings) \b : This functions is called when a single step is taken with parameters as settings of the simulation.  \n
  //! \b  keyboard(unsigned char key) \b : Mehod to be called when any key on keyboard is pressed. \n 
  //! \b  keyboard_up(unsigned char key) \b : method to be called when up-key is pressed on keyboard.  \n
  //! \b  shift_mouse_down(const b2Vec2& p) \b : method to be called when shift + mouse is pressed on keyboard.  \n
  //! \b  mouse_down(const b2Vec2& p) \b : Method to be called when mouse is clicked \n 
  //! \b  mouse_up(const b2Vec2& p) \b : Method to be called when mouse is unclicked \n
  //! \b  mouse_move(const b2Vec2& p) \b : Method to be called when mouse pointer is moved  \n
  //! \b  joint_destroyed(b2Joint* joint) \b : This method tells the derived tests that a joint is destroyed \n
  //! \b  begin_contact(b2Contact* contact) \b : Method called when two fixtures come in contact \n 
  //! \b  end_contact(b2Contact* contact) \b : Method called when two fixtures stop being in contact \n 
  //! \b  pre_solve(b2Contact* contact, const b2Manifold* oldManifold) \b : this method is called after a contact is updated.  \n
  //! \b  post_solve(const b2Contact* contact, const b2ContactImpulse* impulse) \b : This method is called to inspect a contact after the solver is finished\n
  class base_sim_t : public b2ContactListener
  {
  public:
    
    base_sim_t();

    /*! In C++ a destructor is generally used to deallocate memory and do some other cleanup for a class object and it’s class members 
        whenever an object is destroyed. make the base class destructor virtual, and that will ensure that the destructor for any class 
        that derives from Base is called when an object of Base class goes out of scope
    */
    virtual ~base_sim_t();
    
    void set_text_line(int32 line) { m_text_line = line; }
    void draw_title(int x, int y, const char *string);
    virtual void step(settings_t* settings);

    virtual void keyboard(unsigned char key) { B2_NOT_USED(key); }
    virtual void keyboard_up(unsigned char key) { B2_NOT_USED(key); }
		inline b2World* get_world(void){
			return m_world;
			};
    void shift_mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    virtual void mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    virtual void mouse_up(const b2Vec2& p) { B2_NOT_USED(p); }
    void mouse_move(const b2Vec2& p) { B2_NOT_USED(p); }

    
    // Let derived tests know that a joint was destroyed.
    virtual void joint_destroyed(b2Joint* joint) { B2_NOT_USED(joint); }
    
    // Callbacks for derived classes.
    virtual void begin_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    virtual void end_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
      B2_NOT_USED(contact);
      B2_NOT_USED(impulse);
    }

  /*! Private data members can only be used within the class definition and not in in outside world or in friend class whereas
  Protected data members are visible both inside class definition as well as inside definition of friend class
  */
  protected:

    //! Friend classes of the given class refers to those classes which inherit from this class. Inheritence my be public, private or protected
    friend class contact_listener_t;
    
    b2Body* m_ground_body;
    b2AABB m_world_AABB;
    contact_point_t m_points[k_max_contact_points];
    int32 m_point_count;

    debug_draw_t m_debug_draw;
    int32 m_text_line;
    b2World* m_world;

    int32 m_step_count;
    
    b2Profile m_max_profile;
    b2Profile m_total_profile;
  };
}

#endif
