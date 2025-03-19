#include "config.h"
#include "Allocators.h"

Allocators* Allocators::instance() {
	static Allocators alloc;
	return &alloc;
}