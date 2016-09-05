#ifndef _locks_h_
#define _locks_h_

typedef void interrupt(*interPtr)(...);

#define lock() { asm pushf; asm cli; }
#define unlock() { asm popf; }

#endif
