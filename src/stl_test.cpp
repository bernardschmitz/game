
#include <stdlib.h>

//#include "SDL.h"
//#include "SDL_opengl.h"
//#include "SDL_image.h"

//#include "game/src/sg/sg.h"

//
// C++ STL Headers
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
//
#ifdef _WIN32
using namespace std;
#endif
//

enum ActorID { bad1, bad2 };

class Actor {
   protected:

      static int sequence;
      int id;
      int uuid;
      int delay;                // delay counter
      int state;                // action state
      int flags;                // various flags, collision, delete etc...
      bool dead;
//      Actor *pactNext;           // next actor
//      Actor *pactPrev;           // prev actor
   public:
      Actor(int ai) { id = ai; uuid = sequence++; dead = false; }
      virtual ~Actor() { cout << "actor id " << id << "uuid " << uuid << " destructor\n"; }

//      void position(sgVec3 p) { sgCopyVec3(p, pos); }

      virtual void action() { }  // called to update actor position
      virtual void render() { cout << id << endl; }  // called to update actor position

      friend class ActorManager;
};

int Actor::sequence = 0;

class E01 : public Actor {

   private:
      int life;
   public:
      E01(int i) : Actor(i) { life = 5+rand() % 10; }
      ~E01() { cout << "E01 " << id << " destroyed\n"; }

      void action() { if(life > 0) { life--; } else dead = true; }
      void render() { cout << id << ": " << life << endl; }
};

class E02 : public Actor {

   private:
      int life;
      char graphic;
   public:
      E02(int i, char c) : Actor(i) { graphic = c; life = 15+rand()%50; }
      ~E02() { cout << "E02 " << id << " destroyed\n"; }

      void action() { if(life > 0) { life--; } else dead = true; }
      void render() { cout << id << ": "; for(int i=0; i<life; i++) cout << graphic; cout << endl;  }
};



typedef vector<Actor*> ActorList;
typedef map<int, ActorList*> ActorMap;

class ActorManager {

   private:
      ActorList actor_master_list;
      ActorMap actor_lists;

   public:
      ActorManager() { cout << "actor manager created\n"; }
      ~ActorManager() { cout << "actor manager destroyed\n"; } 

      void add(Actor *a);
      void action();
      void render();

};

void ActorManager::add(Actor *a) {

   // first add actor to master list
   actor_master_list.push_back(a);

   // find the list containing actors if this id
   ActorMap::iterator i = actor_lists.find(a->id);

   if(i == actor_lists.end()) {
      // list not found, make a new one and add actor to it
      ActorList* al = new ActorList();
      al->push_back(a); 
      // add new list to map
      actor_lists[a->id] = al;
   }
   else {
      // list for this id found
      ActorList* al = (*i).second;
      // add actor to the list
      al->push_back(a); 
   }

//   cout << actor_lists << endl;

   cout << "current actormap:\n";

   ActorMap::iterator mi = actor_lists.begin();

   while(mi != actor_lists.end()) {

      ActorList::iterator k=((*mi).second)->begin();

      while(k != ((*mi).second)->end()) {

         cout << (*k)->id << " ";

         k++;
      }
      cout << endl;

      mi++;
   }
}

void ActorManager::render() {

   ActorList::iterator k=actor_master_list.begin();

   while(k != actor_master_list.end()) {

      (*k)->render();

      k++;
   }
}



void ActorManager::action() {

   ActorList::iterator k=actor_master_list.begin();

   while(k != actor_master_list.end()) {

      (*k)->action();

      if((*k)->dead) {
         cout << (*k)->id << " is dead.\n";
         delete (*k);
         k = actor_master_list.erase(k);
      }
      else 
         k++;
   }
}



int main( int argc, char *argv[] )
{

   ActorManager am;


   am.add(new E01(10));
   am.add(new E01(10));
   am.add(new E01(20));
   am.add(new E01(30));
   am.add(new E01(30));

   am.add(new E02(15, '='));
   am.add(new E02(25, '*'));
   am.add(new E02(25, '$'));

   for(int i=0; i<100; i++) {
      if(i == 25) {
        am.add(new E01(40));
        am.add(new E02(35, '#'));
      }
      am.action();
      cout << "frame " << i << endl;
      am.render();
   }

/*
   int ival, nitems = 0;
   vector<leng> v;
//
   cout << "Enter integers, <Return> after each, <Ctrl>Z to finish:" << endl;
//
   while( cin >> ival, cin.good() ) {
      leng k = leng(ival);
      v.push_back( k );
      cout.width(6);
      cout << nitems << ": " << v[nitems++].get() << endl;
   } 
//
   if ( nitems ) {
      sort( v.begin(), v.end() );
      for (vector<leng>::iterator viter=v.begin(); viter!=v.end(); ++viter)
         cout << (*viter).get() << " ";
         cout << endl;
   }
*/
   return( EXIT_SUCCESS );
}
