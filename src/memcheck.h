
#ifndef __MEM_CHECK__
#define __MEM_CHECK__

#ifdef TRACK_MEMORY

#include <iostream>
#include <vector>

struct mem_block {
   size_t size;
   void *address;
   char file[100];
   int line;
};

extern int total_bytes;
extern int peak_bytes;
extern void mem_report();


inline void inc_mem_count(int size) {

   total_bytes += size;
   if(total_bytes > peak_bytes)
      peak_bytes = total_bytes;
}


inline void dec_mem_count(int size) {
   total_bytes -= size;
}

typedef std::vector<mem_block *> mem_list;

extern mem_list mem_track;


inline void *operator new(unsigned int size, const char *file, int line) {

   printf("new called %s %d\n", file, line);
   void *p = malloc(size);
   mem_block *mb = (mem_block *)malloc(sizeof(mem_block));

   mb->size = size;
   mb->address = p;
   mb->line = line;
   strncpy(mb->file, file, 99);

   inc_mem_count(size);

   mem_track.push_back(mb);
//   mem_track.push_back(new mem_block(size, p, file, line));
   return p;
}

inline void *operator new[](unsigned int size, const char *file, int line) {

   printf("new [] called %s %d\n", file, line);

   void *p = malloc(size);

   mem_block *mb = (mem_block *)malloc(sizeof(mem_block));

   mb->size = size;
   mb->address = p;
   mb->line = line;
   strncpy(mb->file, file, 99);
   inc_mem_count(size);

   mem_track.push_back(mb);
//   mem_track.push_back(new mem_block(size, p, file, line));
   return p;
}


inline void operator delete(void *p) {

   printf("delete called\n");
   mem_list::iterator i = mem_track.begin();

   for( ; i!=mem_track.end(); ++i) {
      if((*i)->address == p) {
         dec_mem_count((*i)->size);
         free (*i);
         mem_track.erase(i);
         free(p);
printf("done\n");
         return;
      }
   }

   std::cout << "attempt to free non existant block " << p << "\n";
}

inline void operator delete[](void *p) {

   printf("delete [] called\n");
   mem_list::iterator i = mem_track.begin();

   for( ; i!=mem_track.end(); ++i) {
      if((*i)->address == p) {
         dec_mem_count((*i)->size);
         free (*i);
         mem_track.erase(i);
         free(p);
printf("done\n");
         return;
      }
   }

   std::cout << "attempt to free non existant block " << p << "\n";
}


#define new  new(__FILE__, __LINE__)

#endif

#endif


