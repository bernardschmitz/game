
// $Id: actor.h,v 1.6 2003-08-04 23:01:20 bernard Exp $

#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "main.h"

#include <iostream>
#include <vector>

#define ACT_CONSOLE      1
#define ACT_BACKGROUND   2
#define ACT_PLAYER       3
#define ACT_ENEMY        4
#define ACT_PARTICLE     5
#define ACT_BULLET       6


// actor class, much like a sprite

#define ACT_COLLISION      0x01
#define ACT_REMOVE         0x02

class Actor {
   protected:

      vector3 position, oldpos;
      vector3 velocity, oldvel;
      vector3 direction;
      quaternion orientation;

      int actor_id;             // unique actor id
      int actor_type;           // type

      int delay;                // delay counter
      int state;                // action state
      int flags;                // various flags, collision, delete etc...

      static int id_seq;       

      //sgBox bound_box;
      //sgSphere bound_sphere;

//      Actor *pactNext;           // next actor
//      Actor *pactPrev;           // prev actor

      void init(int type, vector3 p, vector3 v, vector3 d);

   public:
      Actor(int type);
      Actor(int type, vector3 p, vector3 v, vector3 d);
      virtual ~Actor() { }

      //int XPos(void) { return(nXPos); }
      //int YPos(void) { return(nYPos); }
      //int Width(void) { return(nWidth); }
      //int Height(void) { return(nHeight); }
   
      vector3 getPosition() { return position; }
      vector3 getVelocity() { return velocity; }
      vector3 getDirection() { return direction; }
      quaternion getOrientation() { return orientation; }

      //int Overlap(Actor *);   // returns true if this actor overlaps (collides)
                              // with the actor pointed to

      void update(float dt);  // update, calls action, move etc...

      virtual void action() =0;  // actors user function

      virtual void render() =0;  // draws actor

      // called when an actor hits another.
      // sets the collision flag
      //virtual void Collision(Actor *pact) { pact=pact; fFlags |= ACT_HIT; }

      friend class ActorManager;
};


typedef std::vector<Actor *> ActorList;

class ActorManager {

   private:
      // may need a set of actor_types
      ActorList master_actor_list;

      ActorList new_actor_list;

      void insert_new_actors();
   public:
      ActorManager() { }
      // TODO
      ~ActorManager() { std::cout << "ActorManager destructor probably should destroy actor_list elements!\n"; }


      // add a new actor
      void insert(Actor *p) { new_actor_list.push_back(p); }

//      void remove(Actor *p);

      void update(float dt);    // calls update for all lists

      // TODO will use a RenderTarget later
      void render();    // calls render for all lists


      ActorList get_actor_type_list(int t); 
};

extern ActorManager actor_manager;

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

