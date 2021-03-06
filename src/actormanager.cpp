
// $Id: actormanager.cpp,v 1.1 2003-09-02 01:28:51 bernard Exp $

#include <iostream>
#include <sstream>
#include <iomanip>

#include "vector.h"
#include "actor.h"


int Actor::id_seq = 1;


ActorManager *ActorManager::instance = 0;

ActorManager *ActorManager::getInstance() {

   if(instance == 0)
      instance = new ActorManager(1.0/100.0);

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



void ActorManager::move_actors() {

   ActorList::iterator k = master_actor_list.begin();

   while(k != master_actor_list.end()) {

      if((*k)->force.lengthSquared() > (*k)->max_force*(*k)->max_force)
         (*k)->force = (!(*k)->force) * (*k)->max_force;

      vector3 acceleration = (*k)->force * (*k)->inv_mass;

      vector3 new_pos = 2.0f * (*k)->position - (*k)->prev_position + acceleration * time_step * time_step;
      (*k)->prev_position = (*k)->position;
      (*k)->position = new_pos;

      //(*k)->position = (*k)->prev_position;

      ++k;
   }
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
      if((*k != p) && ((*k)->type & p->collision_flags != 0))
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


// checks for collision between this actor and p.
// sets the ACT_COLLISON flag and the various hit_* variables.
bool Actor::collide(Actor *p) {

   const vector3 delta = p->position - position;
   const float rest_length = p->radius + radius;

   const float delta_squared = delta*delta;

   if(delta_squared - rest_length*rest_length > 0.0f)
      return false;

   //float length = delta.length();
   // approx sqrt above
   const float length = 0.5f * (rest_length + delta_squared/rest_length);

   const float diff = (length - rest_length) / (length * (p->inv_mass + inv_mass) + 0.0001);

   if(diff > 0.0f)
      return false;

   position += diff * inv_mass * delta;
   p->position -= diff * p->inv_mass * delta;

   flags |= ACT_COLLISION;
   hit_actor = p;

   p->flags |= ACT_COLLISION;
   p->hit_actor = this;

   return true;
}

 
void ActorManager::collision_test(ActorList& al) {

   ActorList::iterator i = al.begin();
   while(i != --(al.end())) {

      if((*i)->collision_flags != 0) {

         ActorList::iterator j = i;
         ++j;

         while(j != al.end()) {
            if((*i)->collision_flags & (*j)->type)
               (*i)->collide(*j);
            ++j;
         }
      }
      ++i;
   }

/*
   for(int i=0; i<al.size()-1; ++i) {

      if(al[i]->collision_flags == 0) 
         continue;
   
      for(int j=i+1; j<al.size(); ++j) {
         
         if(al[i]->collision_flags & al[j]->type) {
            // TODO maybe inline this
            al[i]->collide(al[j]);
         }
      }
   }
*/
}

 
void ActorManager::collide(int iter) {

//   std::cout << "collide\n";

   for(int k=0; k<iter; k++) {

      relax(1);

      GridMap::iterator g = grid.grid_map.begin();
      while(g != grid.grid_map.end()) {
         ActorList& al = ((*g).second)->get_actors();
         if(!al.empty())
            collision_test(al);
         ++g;
      }
   }
}


// satisfy constraint
// return true if position modified
// this would indicate a collision has occured


void Constraint::satisfy() {

   vector3 delta = p2->position - p1->position;

   // TODO optimize this sqrt
   //float length = delta.length();

   // approx sqrt above
   float delta_squared = delta*delta;
   float length = 0.5f * (rest_length + delta_squared/rest_length);

   float diff = (length - rest_length) / (length * (p1->inv_mass + p2->inv_mass) + 0.0001);

   // TODO need info on type of constraint...
   // currently is a rod

   p1->position += diff * p1->inv_mass * delta;
   p2->position -= diff * p2->inv_mass * delta;

   // TODO maybe set flags so actor know the constrain is held?
   // TODO constraints need a way of being broken...
}

// satisfies constraints
// flags collisions too

void ActorManager::relax(int iter) {

   for(int i=0; i<iter; i++) {

      ConstraintList::iterator k = constraint_list.begin();

      while(k != constraint_list.end()) {

         (*k)->satisfy();
   
         ++k;
      }
   }
}


void Grid::add_actor(Actor *p) {

   assert(p != 0);
/*
   ActorList::iterator k = actor_list.begin();
   while(k != actor_list.end()) {
      if((*k) == p) {
         return;
      }
      ++k;
   }
   actor_list.push_back(p);
*/

   // is this actor in this grid?
   ActorList::iterator k = find(actor_list.begin(), actor_list.end(), p);

   // no so add it
   if(k == actor_list.end()) {
      // add actor to grid
      actor_list.push_back(p);
      // add grid to actor's list
      p->grid_list.push_back(this);

//      std::cout << "add actor " << p->name << " to grid " << x << " " << y << std::endl;
   }
//   else
//      std::cout << "actor " << p->name << " already in grid " << x << " " << y << std::endl;
}

void Grid::remove_actor(Actor *p) {

   assert(p != 0);

   ActorList::iterator k = find(actor_list.begin(), actor_list.end(), p);

   if(k != actor_list.end()) {
      actor_list.erase(k);
/*
      GridList::iterator g = find(p->grid_list.begin(), p->grid_list.end(), this);
      if(g != p->grid_list.end()) {
         p->grid_list.erase(g);
      }
*/

//      std::cout << "removed actor " << p->name << " from grid " << x << " " << y << std::endl;
   }
//   else
//      std::cout << "actor " << p->name << " not in grid " << x << " " << y << std::endl;
/*
   ActorList::iterator k = actor_list.begin();
   while(k != actor_list.end()) {
      if((*k) == p) {
         actor_list.erase(k);
         return true;
      }
      ++k;
   }
   return false;
*/
}

CollisionGrid::CollisionGrid() { 

   w = 10; 
   h = 10; 
}

CollisionGrid::~CollisionGrid() { 
   // nothing 
}


Grid* CollisionGrid::insert(float x, float y, Actor *p) {

   int px = (int)x;
   int py = (int)y;

   int grid_x = px / w;
   int grid_y = py / h;

   if(px < 0)
      grid_x--;

   if(py < 0)
      grid_y--;

   int key = ((grid_x&0xfff) << 16) | (grid_y & 0xfff);

//   std::cout << "position " << p->position << " " << grid_x << " " << grid_y << std::endl;

   GridMap::iterator gm = grid_map.find(key);

   if(gm == grid_map.end()) {
      // create new grid for this actor
 //     std::cout << "created new grid\n";
      Grid *g = new Grid(grid_x, grid_y, w, h);
      // add grid to map of grids
      grid_map[key] = g;
      g->add_actor(p);
      return g;
   }
   else {
      // insert actor into this grid
//      std::cout << "found grid\n";
      (*gm).second->add_actor(p);
      return (*gm).second;
   }
}

bool point_in_grid(float x, float y, int gx, int gy, int w, int h) {

   return x >= gx && y >= gy && x < gx+w && y < gy+h ;
}

void CollisionGrid::update_position(Actor *p) {

   assert(p != 0);

   // remove actor from the grids it is already in
   if(!p->grid_list.empty()) {
      for(GridList::iterator k = p->grid_list.begin(); k!=p->grid_list.end(); ++k) {
         assert((*k) != 0);
         (*k)->remove_actor(p);
/*
         ActorList::iterator a = find((*k)->actor_list.begin(), (*k)->actor_list.end(), p);
         if(a != (*k)->actor_list.end()) {
            (*k)->actor_list.erase(a);
         }
*/
      }
      p->grid_list.clear();
      assert(p->grid_list.empty());
   }

   Grid *g = insert(p->position.x+p->radius, p->position.y+p->radius, p);

   const vector3& v = p->position;
   const float r = p->radius;

  
   if(!point_in_grid(v.x-r, v.y+r, g->x, g->y, g->w, g->h))
      insert(p->position.x-p->radius, p->position.y+p->radius, p);

   if(!point_in_grid(v.x-r, v.y-r, g->x, g->y, g->w, g->h))
      insert(p->position.x-p->radius, p->position.y-p->radius, p);

   if(!point_in_grid(v.x+r, v.y-r, g->x, g->y, g->w, g->h))
      insert(p->position.x+p->radius, p->position.y-p->radius, p);
   

   // only holds if radius is less than grid size
   assert(p->grid_list.size() <= 4);

}

// updates the actor.
// checks current and future collisions, setting flags.
// calls user function
// performs movement step based on dt
// deletes old actors.

void ActorManager::update(float dt) {

   insert_new_actors();

   // now call user function
   ActorList::iterator k = master_actor_list.begin();
   while(k != master_actor_list.end()) {
      (*k)->action(time_step);
      ++k;
   }
   // remove old actors
   remove_dead_actors();

   k = master_actor_list.begin();
   while(k != master_actor_list.end()) {
      // reset collision flags
      (*k)->flags &= ~ACT_COLLISION;
      (*k)->hit_actor = 0;
      // update position
      //(*k)->update(dt);
      // update actors position in the collision grid
      if((*k)->collision_flags != 0) 
         grid.update_position(*k);
      ++k;
   }

   // update position
   move_actors();

   // hit actors
   collide(1);

   k = master_actor_list.begin();
   while(k != master_actor_list.end()) {

      // calculate velocity
      (*k)->velocity = (*k)->position - (*k)->prev_position;

      // constrain velocity
      if((*k)->velocity.lengthSquared() > (*k)->max_speed*(*k)->max_speed)
         (*k)->prev_position = (*k)->position - !(*k)->velocity * (*k)->max_speed;

      // calc speed
      (*k)->speed = (*k)->velocity.length();

      if((*k)->speed < 0.0001f)
         (*k)->velocity.set(0.0f, 0.0f, 0.0f);

      if((*k)->speed > 0.0f) {
         (*k)->forward_axis = !(*k)->velocity;
         (*k)->right_axis = (*k)->forward_axis % (*k)->up_axis;
         (*k)->up_axis = (*k)->forward_axis % (*k)->right_axis;
      }

      ++k;
   }

}




void ActorManager::remove_dead_actors() {

   ActorList::iterator k = master_actor_list.begin();
   while(k != master_actor_list.end()) {

      if((*k)->flags & ACT_REMOVE) {
         // first remove all constraints references this actor
//         remove_all_constraints(*k);
         // remove this actor from the grids he is in
         if(!(*k)->grid_list.empty()) {
            for(GridList::iterator p = (*k)->grid_list.begin(); p!=(*k)->grid_list.end(); ++p) {
               assert((*p) != 0);
               (*p)->remove_actor(*k);
            }
            (*k)->grid_list.clear();
            assert((*k)->grid_list.empty());
         }

//         std::cout << "removing dead " << (*k)->name << std::endl;
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
