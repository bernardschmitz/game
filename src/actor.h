
// $Id: actor.h,v 1.2 2003-07-18 03:33:57 bernard Exp $

#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "main.h"

// actor class, much like a sprite

class Actor {
   protected:

      sgVec3 pos;               // position
      sgVec3 vel, acc;          // velocity and acceleration
      sgVec3 dir, hpr;          // direction vector, rotation angles
      sgQuat rot;               // rotation quaternion

      int delay;                // delay counter
      int state;                // action state
      int flags;                // various flags, collision, delete etc...

      sgBox bound_box;
      sgSphere bound_sphere;

      Actor *pactNext;           // next actor
      Actor *pactPrev;           // prev actor
   public:
      Actor();
      virtual ~Actor() { }

      //int XPos(void) { return(nXPos); }
      //int YPos(void) { return(nYPos); }
      //int Width(void) { return(nWidth); }
      //int Height(void) { return(nHeight); }

      void position(sgVec3 p) { sgCopyVec3(p, pos); }

      //int Overlap(Actor *);   // returns true if this actor overlaps (collides)
                              // with the actor pointed to

      virtual void action() { };  // called to update actor position
      virtual void render() { }    // draws actor

      // called when an actor hits another.
      // sets the collision flag
      //virtual void Collision(Actor *pact) { pact=pact; fFlags |= ACT_HIT; }

      friend class ActorListBase;
};


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


#endif

