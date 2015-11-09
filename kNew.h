
#ifndef __kNew_H
#define __kNew_H

	#include <malloc.h>

	void *operator new(size_t size);
	void *operator new[](size_t size);
	void operator delete(void *p);
	void operator delete[](void *p);

#endif
