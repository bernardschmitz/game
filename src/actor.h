
// $Id: actor.h,v 1.24 2003-08-28 01:02:54 bernard Exp $

#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <ext/hash_map>
#include <ext/hash_set>

#include "vector.h"

// TODO change to enum elsewhere...
#define ACT_CONSOLE      0x01
#define ACT_BACKGROUND   0x02
#define ACT_PLAYER       0x04
#define ACT_ENEMY        0x08
#define ACT_PARTICLE     0x10
#define ACT_BULLET       0x20


// actor class, much like a sprite
// TODO change to enum?
#define ACT_COLLISION      0x01
#define ACT_REMOVE         0x02


class Constraint;
class Actor;
class Grid;

// TODO change to list
typedef std::vector<Constraint*> ConstraintList;

// TODO change to list
typedef std::vector<Actor*> ActorList;
//typedef __gnu_cxx::hash_set<Actor*> ActorList;

typedef std::vector<Grid*> GridList;
//typedef __gnu_cxx::hash_set<Grid*> GridList;

typedef __gnu_cxx::hash_map<int, Grid*> GridMap;



class Actor {
   protected:

      vector3 position;
      vector3 prev_position;

      vector3 force;
      vector3 velocity;

      vector3 forward_axis;
      vector3 right_axis;
      vector3 up_axis;

      float mass, inv_mass;
      float speed;

      float max_force;
      float max_thrust_force;
      float max_steering_force;
      float max_braking_force;

      float max_speed;

      int id;             // unique actor id
      int type;           // type
      std::string name;

      float delay;                // delay counter

      int state;                // action state
      int flags;                // various flags, collision, delete etc...
      int collision_flags;

      static int id_seq;       

      float radius;

      float hit_time;
      vector3 hit_position;
      vector3 hit_normal;
      Actor *hit_actor;

      GridList grid_list;

   public:
      Actor(int t, std::string s="Actor", const vector3& pos=vector3(0.0f, 0.0f, 0.0f), const vector3& vel=vector3(0.0f, 0.0f, 0.0f),  
            float m=1.0f, float ms=10.0f, float r=1.0f, 
            float mtf=100.0f, float msf=1.0f, float mbf=1.0f,
            const vector3& dir=vector3(0.0f, 1.0f, 0.0f), const vector3& up=vector3(0.0f, 0.0f, 1.0f));

      virtual ~Actor() { }


      int getType() { return type; }
      int getId() { return id; }
      std::string getName() { return name; }

      vector3 getPosition() { return position; }
      vector3 getVelocity() { return velocity; }

      vector3 getForwardAxis() { return forward_axis; }
      vector3 getRightAxis() { return right_axis; }
      vector3 getUpAxis() { return up_axis; }

      float getMass() { return mass; }
      void setMass(float m) { mass = m;  if(mass > 0.0f) inv_mass = 1.0f/mass; else inv_mass = 0.0f; }

      float getRadius() { return radius; }
      void setRadius(float r) { radius = r; }

//      virtual void update(float dt);  // update, calls action, move etc...

      virtual void action(float dt) =0;  // actors user function

      virtual void render() =0;  // draws actor



      // checks for collision between this actor and p.
      // sets the ACT_COLLISON flag and the various hit_* variables.
      bool collide(Actor *p);

      friend class ActorManager;
      friend class Constraint;
      friend class CollisionGrid;
      friend class Grid;
};

class Grid {
private:
   int x, y, w, h;
   ActorList actor_list;
public:
   Grid(int xx, int yy, int ww, int hh) { x = xx; y = yy; w = ww; h = hh; }

   void add_actor(Actor *p);
   void remove_actor(Actor *p);

   bool empty() { return actor_list.empty(); }
   int size() { return actor_list.size(); }

   ActorList& get_actors() { return actor_list; }

   friend class CollisionGrid;
};


class CollisionGrid {
private:
   int w, h;
   GridMap grid_map;
public:
   CollisionGrid();
   ~CollisionGrid();

   void update_position(Actor *p);
   Grid *insert(float x, float y, Actor *p);

   friend class ActorManager;
};
  

 
class Constraint {
public:
   Actor *p1, *p2;
   float rest_length;
   Constraint() { p1 = p2 = 0; rest_length = 0.0f; }
   Constraint(Actor *a, Actor *b, float rl=-1.0f) {
      p1 = a;
      p2 = b;
      rest_length = rl;
      if(rest_length < 0.0f) {
         rest_length = (p1->position - p2->position).length();
      }
   }
   void satisfy();
};

class ActorManager {

   private:
      // may need a set of actor_types
      ActorList master_actor_list;

      ConstraintList constraint_list;

      ActorList new_actor_list;

      CollisionGrid grid;

      float time_step;

      void insert_new_actors();

      static ActorManager *instance;

      void collide(int iter);

      void collision_test(ActorList& al);

      ActorManager(float ts) { time_step = ts; }
      // TODO
      ~ActorManager() { std::cout << "ActorManager destructor probably should destroy actor_list elements!\n"; }

   public:
      static ActorManager *getInstance();
      // add a new actor
      void insert(Actor *p);

//      void remove(Actor *p);

      void update(float dt);    // calls update for all lists

      // TODO will use a RenderTarget later
      void render();    // calls render for all lists


      ActorList get_actor_type_list(int t); 

      void add_all_constraints(Actor *p);
      void remove_all_constraints(Actor *p);

      void move_actors();

      bool constrain_collision(Actor *p1, Actor *p2);
      void relax(int iter);

      void remove_dead_actors();

      void add_constraint(Actor *p1, Actor *p2, float rl=-1.0) { constraint_list.push_back(new Constraint(p1, p2, rl)); }
      void remove_constraint(Actor *p1, Actor *p2=0);
};


#endif

