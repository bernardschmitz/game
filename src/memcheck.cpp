
#ifdef TRACK_MEMORY

#include "memcheck.h"

mem_list mem_track;

int total_bytes = 0;
int peak_bytes = 0;

void mem_report() {

   std::cout << "\nTotal mem allocated " << total_bytes << " bytes\n";
   std::cout << "\nPeak mem allocated " << peak_bytes << " bytes\n";

   if(mem_track.size() == 0) {
      std::cout << "All memory freed!\n";
      return;
   }

   mem_list::iterator i = mem_track.begin();

   while(i != mem_track.end()) {
      mem_block *m = *i;
      std::cout << "block " << m->address << " size " << m->size << " not freed at line " << m->line << " in " << m->file << "\n";
      ++i;
   }

   std::cout << "Done.\n";
}

#endif


