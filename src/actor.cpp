
// $Id: actor.cpp,v 1.10 2003-08-15 20:38:54 bernard Exp $

#include <iostream>

#include "vector.h"
#include "actor.h"


int Actor::id_seq = 1;


ActorManager *ActorManager::instance = 0;

ActorManager *ActorManager::getInstance() {

   if(instance == 0)
      instance = new ActorManager();

   return instance;
}


Actor::Actor(int type, vector3 p, vector3 v, float m, float ms, float br, float mtf, float msf, float mbf, vector3 d, vector3 u) {

   actor_id = id_seq++;
   actor_type = type;

   position = p;
   velocity = v;

   acceleration.set(0.0f,0.0f,0.0f);
   force.set(0.0f,0.0f,0.0f);

   speed = velocity.length();

   mass = m;

   max_speed = ms;

   max_thrust_force = mtf;
   max_steering_force = msf;
   max_braking_force = mbf;
   
   if(speed <= tiny)
      forward_axis = !d;
   else
      forward_axis = !velocity;

   right_axis = forward_axis % u;
   up_axis = forward_axis % right_axis;


   delay = 0.0f;
   state = flags = 0;
}


void Actor::update(float dt) {

   //printf("update with %f\n", dt);

   delay -= dt;

   action(dt);

   if(force.lengthSquared() > max_force*max_force)
      force = (!force) * max_force;

   //acceleration = (acceleration*2.0 + force / mass) / 3.0;
   acceleration = force / mass;

   velocity += acceleration * dt;

   if(velocity.lengthSquared() > max_speed*max_speed)
      velocity = (!velocity) * max_speed;

   if(velocity.lengthSquared() < tiny)
      velocity.set(0.0, 0.0, 0.0);

   position += velocity * dt;

   //std::cout << actor_type << " " << actor_id << " " << position << " " << velocity << " " << velocity.length() << " " << force << " " << force.length() << std::endl;

//   force.set(0,0,0);

   speed = velocity.length();

   if(speed > tiny) {
      forward_axis = !velocity;
      right_axis = forward_axis % up_axis;
      up_axis = forward_axis % right_axis;
   }
}


ActorList ActorManager::get_actor_type_list(int type) {

   ActorList al;

   ActorList::iterator k = master_actor_list.begin();

   while(k != master_actor_list.end()) {
      if((*k)->actor_type == type)
         al.push_back((*k));
      k++;
   }

   return al;
}


void ActorManager::insert_new_actors() { 


   ActorList::iterator k = new_actor_list.begin();

   while(k != new_actor_list.end()) {
      master_actor_list.push_back((*k));
      k = new_actor_list.erase(k);
   }

   assert(new_actor_list.empty());
}



// updates the actor.
// checks current and future collisions, setting flags.
// calls user function
// performs movement step based on dt
// deletes old actors.

void ActorManager::update(float dt) {


   insert_new_actors();

   // TODO
   // check collisions here

   // now call user function
   ActorList::iterator k = master_actor_list.begin();
   while(k != master_actor_list.end()) {
      //printf("calling update for %p %d %d\n", (void *)(*k), (*k)->actor_type, (*k)->actor_id);
      (*k)->update(dt);
      k++;
   }

   // remove old actors

   k = master_actor_list.begin();
   while(k != master_actor_list.end()) {
      if((*k)->flags & ACT_REMOVE)
         // TODO fix leak here, need to delete the actor itself...  or perhaps flag it for reuse?
         k = master_actor_list.erase(k);
      else
         k++;
   }

}


void ActorManager::render() {


   ActorList::iterator k = master_actor_list.begin();
   while(k != master_actor_list.end()) {
      //printf("calling render for %p %d %d\n", (void *)(*k), (*k)->actor_type, (*k)->actor_id);
  //    int t = SDL_GetTicks();
      (*k)->render();
//printf("rendering %d %d took %d\n", (*k)->actor_type, (*k)->actor_id, SDL_GetTicks()-t);
      k++;
   }
}










/*
int Actor::Overlap(Actor *pact) {

   if(fFlags & ACT_SPH) {   // use bounding circles?

      int x0 = nXPos+nWidth/2;
      int y0 = nYPos+nHeight/2;

      int x1 = pact->nXPos+pact->nWidth/2;
      int y1 = pact->nYPos+pact->nHeight/2;

      int dx = x1 - x0;
      int dy = y1 - y0;

      int dist = dx*dx + dy*dy;

      if(dist - nRadius*nRadius - pact->nRadius*pact->nRadius < 0)
         return(1);
   }
   else {

      // bounding rectangles

      int w0 = nWidth;
      int h0 = nHeight;

      int w1 = pact->nWidth;
      int h1 = pact->nHeight;

      if(nXPos+w0 >= pact->nXPos && pact->nXPos+w1 >= nXPos &&
         nYPos+h0 >= pact->nYPos && pact->nYPos+h1 >= nYPos) {
         return(1);
      }
   }

   return(0);
}
*/

/*
void ActorListBase::Collision(ActorListBase &al1) {

   Actor *pact0 = First();

   // only check collision if not allready collided
   while(!(pact0->fFlags & ACT_HIT) && pact0 != Head()) {

      Actor *pact1 = al1.First();

      // only check collision if not allready collided
      while(!(pact1->fFlags & ACT_HIT) && !(pact0->fFlags & ACT_HIT)
                        && pact1 != al1.Head()) {

         if(pact0 != pact1) {
            if(pact0->Overlap(pact1)) {
               pact1->Collision(pact0);
               pact0->Collision(pact1);
            }
         }
         pact1 = al1.Next();
      }

      pact0 = Next();
   }

}
*/

/*
void ActorListBase::insert(Actor *pact) {

   pact->pactNext = actHead.pactNext;
   pact->pactPrev = &actHead;
   actHead.pactNext->pactPrev = pact;
   actHead.pactNext = pact;

   cActors++;
}

void ActorListBase::remove(Actor *pact) {

   cActors--;

   pact->pactNext->pactPrev = pact->pactPrev;
   pact->pactPrev->pactNext = pact->pactNext;
}

ActorListBase::~ActorListBase() {

   Actor *pact = actHead.pactNext;

   while(pact != &actHead) {
      Actor *pactTmp = pact->pactNext;
      remove(pact);
      delete pact;
      pact = pactTmp;
   }
}

void ActorListBase::action() {

   Actor *pact = actHead.pactNext;

   while(pact != &actHead) {
      // don't call if actor going to be deleted
//      if(!(pact->fFlags & ACT_DEL))
         pact->action();
      pact = pact->pactNext;
   }
}

void ActorListBase::render() {

   Actor *pact = actHead.pactNext;

   while(pact != &actHead) {
      // don't call if actor going to be deleted
//      if(!(pact->fFlags & ACT_DEL)) {
//         pact->cErase[nPage]++;
         pact->render();

//circle(pbmPage[nPage], pact->nXPos+pact->nWidth/2, pact->nYPos+pact->nHeight/2, pact->nRadius-1, nWhite);

 //     }
      pact = pact->pactNext;
   }
}
*/

/*
void ActorListBase::Erase(int nPage) {

   Actor *pact = actHead.pactNext;

   while(pact != &actHead) {
      // call erase if needed
      if(pact->cErase[nPage] > 0) {
         pact->Erase(nPage);
         pact->cErase[nPage]--;
      }
      // if flags for deletion and no more erasure needed then delete
      if(pact->fFlags & ACT_DEL && pact->cErase[0] == 0 && pact->cErase[1] == 0) {
         Actor *pactTmp = pact->pactNext;
         Remove(pact);
         delete pact;
         pact = pactTmp;
      }
      else
         pact = pact->pactNext;
   }
}
*/

/*
void ActorListBase::clear() {

   Actor *pact = actHead.pactNext;

   while(pact != &actHead) {
      Actor *pactTmp = pact->pactNext;
      remove(pact);
      delete pact;
      pact = pactTmp;
   }
}

*/
