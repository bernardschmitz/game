
// $Id: actor.h,v 1.14 2003-08-22 18:19:31 bernard Exp $

#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <iostream>
#include <vector>
#include <string>

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


class Actor {
   protected:

      vector3 position;
      vector3 prev_position;
      vector3 delta_position;
      vector3 velocity;
      vector3 acceleration;
      vector3 force;

      vector3 forward_axis;
      vector3 right_axis;
      vector3 up_axis;

      float mass;
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
      vector3 getAcceleration() { return acceleration; }

      vector3 getForwardAxis() { return forward_axis; }
      vector3 getRightAxis() { return right_axis; }
      vector3 getUpAxis() { return up_axis; }

      float getRadius() { return radius; }

      virtual void update(float dt);  // update, calls action, move etc...

      virtual void action(float dt) =0;  // actors user function

      virtual void render() =0;  // draws actor



      // checks for collision between this actor and p.
      // sets the ACT_COLLISON flag and the various hit_* variables.
      bool collide(Actor *p, float dt);



      friend class ActorManager;
};




typedef std::vector<Actor *> ActorList;

class ActorManager {

   private:
      // may need a set of actor_types
      ActorList master_actor_list;

      ActorList new_actor_list;

      void insert_new_actors();

      static ActorManager *instance;

      void collide(float dt);

      ActorManager() { }
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

      void check_collision(float dt);

};


/*
// list of actors

class ActorListBase {
   private:
      Actor actHead;     // head of list
      Actor *pactIter;   // used for list iteration
      int cActors;       // number of actors in list
   public:
      ActorListBase() { cActors = 0; actHead.pactNext = &actHead; actHead.pactPrev = &actHead; }
      virtual ~ActorListBase();

      void insert(Actor *);
      void remove(Actor *);

      void clear();

      int count() { return(cActors); }

      void action(); // calls the action() function for each actor in list
      void render();    // draw

      // returns the head of the list
      Actor *head() { return(&actHead); }

      // returns the first actor in the list
      Actor *first() { pactIter = actHead.pactNext; return(pactIter); }

      // return the next actor in the list
      Actor *next() { pactIter = pactIter->pactNext; return(pactIter); }

      // checks every actor in this list against every actor in passed list
      // calling overlap() to detect collision
      // calling collision() if collision occured
      //void Collision(ActorListBase &);
};

// actor list template to avoid having to manually cast list elements


template<class T> class ActorList : public ActorListBase {
   public:
      void insert(T *pact) { ActorListBase::insert(pact); }
      void remove(T *pact) { ActorListBase::remove(pact); }
      T *head() { return((T *)ActorListBase::head()); }
      T *first() { return((T *)ActorListBase::first()); }
      T *next() { return((T *)ActorListBase::next()); }
};
*/

#endif

