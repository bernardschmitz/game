
// $Id: actor.cpp,v 1.15 2003-08-23 22:15:56 bernard Exp $

#include <iostream>
#include <sstream>

#include "vector.h"
#include "actor.h"


int Actor::id_seq = 1;


ActorManager *ActorManager::instance = 0;

ActorManager *ActorManager::getInstance() {

   if(instance == 0)
      instance = new ActorManager();

   return instance;
}


Actor::Actor(int t, std::string s, const vector3& p, const vector3& v, float m, float ms, float r, float mtf, float msf, float mbf, const vector3& d, const vector3& u) {

   id = id_seq++;
   type = t;

   std::stringstream ss;
   ss << s << id;
   name = ss.str();

   position = p;
   velocity = v;

   prev_position = position - velocity;

//   acceleration.set(0.0f,0.0f,0.0f);
   force.set(0.0f,0.0f,0.0f);

   speed = velocity.length();

   mass = m;

   if(mass > 0.0f)
      inv_mass = 1.0f/mass;
   else 
      inv_mass = 0.0f;

   radius = r;

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
   state = flags = collision_flags = 0;
}


inline bool sphere_collision(const vector3& Ap, const vector3& Av, const float Ar, const vector3& Bp, const vector3& Bv, const float Br) {

   const vector3 move = Av - Bv;

   const vector3 C = Bp - Ap;

   const float dist_squared = C.lengthSquared();
   const float sum_radii = Ar + Br;
   const float sum_radii_squared = sum_radii * sum_radii;

   const float move_len_squared = move.lengthSquared();

   if(move_len_squared < dist_squared - sum_radii_squared)
      return false;

   const float move_len = sqrt(move_len_squared);

   const vector3 N = (move_len>0.0f)? move/move_len : move;

   const float D = N * C;

   if(D <= 0.0f)
      return false;

   const float F = dist_squared - (D * D);

   if(F >= sum_radii_squared)
      return false;

   const float T = sum_radii_squared - F;

   if(T < 0.0f)
      return false;

   const float distance = D - sqrt(T);

   if(move_len < distance)
      return false;

/*
   vector3 new_move = !move * distance;

   t = 0.0;

   if(move.length() < 0.001f)
      t = 0.0;
   else
      t = new_move.length() / move.length();

   if(t >= 0.0 && t <= 1.0) {
      Av *= t;
      Bv *= t;
   }
*/
   return true;
}

void Actor::update(float dt) {

   //printf("update with %f\n", dt);

   delay -= dt;

   action(dt);

   if(force.lengthSquared() > max_force*max_force)
      force = (!force) * max_force;

   vector3 acceleration = force * inv_mass;


   vector3 new_position = 2.0f * position - prev_position + acceleration * dt * dt;
   prev_position = position;
   position = new_position;


//   std::cout << name << " " << position << " " << prev_position << std::endl;

   //std::cout << actor_type << " " << actor_id << " " << position << " " << velocity << " " << velocity.length() << " " << force << " " << force.length() << std::endl;
}

void ActorManager::insert(Actor *p) { 

   new_actor_list.push_back(p); 
}


ActorList ActorManager::get_actor_type_list(int type) {

   ActorList al;

   ActorList::iterator k = master_actor_list.begin();

   while(k != master_actor_list.end()) {
      if((*k)->type == type)
         al.push_back((*k));
      k++;
   }

   return al;
}

// adds a constraint from this actor to every other actor in the system
void ActorManager::add_all_constraints(Actor *p) {

   ActorList::iterator k = master_actor_list.begin();
   while(k != master_actor_list.end()) {
      // only add a constraint if we want to detect collisions
      if((*k != p) && ((*k)->type & p->collision_flags))
         constraint_list.push_back(new Constraint(p, *k));
      ++k;
   }
}

// removes all constraints this actor is a part of
void ActorManager::remove_all_constraints(Actor *p) {

   ConstraintList::iterator k = constraint_list.begin();
   while(k != constraint_list.end()) {
      if((*k)->p1 == p || (*k)->p2 == p) {
         // destroy the constraint
         delete (*k);
         // remove it from the list
         k = constraint_list.erase(k);
      }
      else
         ++k;
   }
}


void ActorManager::insert_new_actors() { 

   // insert new actors to main list
   ActorList::iterator k = new_actor_list.begin();

   while(k != new_actor_list.end()) {
      // insert the new actor
      master_actor_list.push_back(*k);
      // remove it from the new list and get the next one
      k = new_actor_list.erase(k);
   }

   assert(new_actor_list.empty());
}


inline bool ActorManager::constrain_collision(Actor *p1, Actor *p2) {

   vector3 delta = p2->position - p1->position;

   float rest_length = p1->radius + p2->radius;

   //float length = delta.length();
   // approx sqrt above
   float delta_squared = delta*delta;
   float length = 0.5f * (rest_length + delta_squared/rest_length);

   float diff = (length - rest_length) / (length * (p1->inv_mass + p2->inv_mass) + 0.0001);

   if(diff < 0.0f) {
      p1->position += diff * p1->inv_mass * delta;
      p2->position -= diff * p2->inv_mass * delta;
      return true;
   }

   return false;
}


void ActorManager::collide(int iter, float dt) {

//   std::cout << "collide\n";

   for(int k=0; k<iter; k++) {
   
      for(int i=0; i<master_actor_list.size()-1; ++i) {
   
         if(master_actor_list[i]->collision_flags == 0) 
            continue;
   
         for(int j=i+1; j<master_actor_list.size(); ++j) {
         
            if(master_actor_list[i]->collision_flags & master_actor_list[j]->type) {
   
               //std::cout << " check " << i << " against " << j;
   
               if(constrain_collision(master_actor_list[i], master_actor_list[j])) {
   
                  master_actor_list[i]->flags |= ACT_COLLISION;
                  master_actor_list[i]->hit_actor = master_actor_list[j];
      
                  master_actor_list[j]->flags |= ACT_COLLISION;
                  master_actor_list[j]->hit_actor = master_actor_list[i];
               }
            }
         }
      }
   }
}

// satisfy constraint
// return true if position modified
// this would indicate a collision has occured


inline bool Constraint::satisfy() {

   vector3 delta = p2->position - p1->position;

   // TODO optimize this sqrt
   //float length = delta.length();

   // approx sqrt above
   float delta_squared = delta*delta;
   float length = 0.5f * (rest_length + delta_squared/rest_length);

   float diff = (length - rest_length) / (length * (p1->inv_mass + p2->inv_mass) + 0.0001);

   if(diff < 0.0f) {
      // TODO need info on type of constraint...
      // currently is a one way rod to avoid spheres overlapping

//      std::cout << p1->name << " " << p2->name << " diff " << diff << " inv_mass " << p1->inv_mass << " " << p2->inv_mass << " delta " << delta << std::endl;

      p1->position += diff * p1->inv_mass * delta;
      p2->position -= diff * p2->inv_mass * delta;
      return true;
   }

   return false;
}

// satisfies constraints
// flags collisions too

void ActorManager::relax(float dt) {

   for(int i=0; i<1; i++) {

      ConstraintList::iterator k = constraint_list.begin();

      while(k != constraint_list.end()) {

         (*k)->satisfy();
   
         ++k;
      }
   }
}

// updates the actor.
// checks current and future collisions, setting flags.
// calls user function
// performs movement step based on dt
// deletes old actors.

void ActorManager::update(float dt) {

//   printf("update with %f\n", dt);

   insert_new_actors();

   // TODO
   // check collisions here

   // now call user function
   ActorList::iterator k = master_actor_list.begin();
   while(k != master_actor_list.end()) {
      //printf("calling update for %p %d %d\n", (void *)(*k), (*k)->actor_type, (*k)->actor_id);
      (*k)->update(dt);
      ++k;
   }

   // remove old actors
   remove_dead_actors();

   // hit actors
   collide(1, dt);

/*
   // bounce
   k = master_actor_list.begin();
   while(k != master_actor_list.end()) {

      if((*k)->flags & ACT_COLLISION) {

//         std::cout << "\tflags " << (*k)->flags << " actor_type " << (*k)->actor_type << " actor_id " << (*k)->actor_id << std::endl;

         Actor *p = (*k)->hit_actor;

         assert(p != 0);

         vector3 N = p->position - (*k)->position;



         vector3& Av = (*k)->velocity;
         vector3& Bv = p->velocity;

         float sum_inv_mass = 1.0f/(*k)->mass + 1.0f/p->mass;

         vector3 rv = Av - Bv;
         vector3 cn = !((*k)->position - p->position);
            
         float kk = ( -(1.0f+0.5f) * (rv * cn) )  /  ( (cn*cn) * sum_inv_mass );

//         std::cout << "\tAv " << Av << " Bv " << Bv << std::endl;
 
         Av += ((kk * cn) / (*k)->mass) ;// / dt;
         Bv -= ((kk * cn) / p->mass) ;// / dt;

 //        std::cout << "\t\tAv " << Av << " Bv " << Bv << std::endl;

         (*k)->flags &= ~ACT_COLLISION;
         p->flags &= ~ACT_COLLISION;
      }

      // constraint velocity
      if((*k)->velocity.lengthSquared() > (*k)->max_speed*(*k)->max_speed)
         (*k)->velocity = (!(*k)->velocity) * (*k)->max_speed;

      if((*k)->velocity.lengthSquared() < tiny)
         (*k)->velocity.set(0.0, 0.0, 0.0);

      (*k)->speed = (*k)->velocity.length();

      ++k;
   }
*/

   k = master_actor_list.begin();
   while(k != master_actor_list.end()) {

      (*k)->velocity = (*k)->position - (*k)->prev_position;

      // constrain velocity
      if((*k)->velocity.lengthSquared() > (*k)->max_speed*(*k)->max_speed)
         (*k)->velocity = (!(*k)->velocity) * (*k)->max_speed;

      if((*k)->velocity.lengthSquared() < tiny)
         (*k)->velocity.set(0.0, 0.0, 0.0);

      (*k)->speed = (*k)->velocity.length();

      ++k;
   }
}




void ActorManager::remove_dead_actors() {

   ActorList::iterator k = master_actor_list.begin();
   while(k != master_actor_list.end()) {
      if((*k)->flags & ACT_REMOVE) {
         // first remove all constraints references this actor
//         remove_all_constraints(*k);
         // TODO fix leak here, need to delete the actor itself...  or perhaps flag it for reuse?
         k = master_actor_list.erase(k);
      }
      else
         ++k;
   }

   // relax positions of all actors and flag collisions
   //relax(dt);
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
