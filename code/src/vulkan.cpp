#include "engine/engine.hpp"

int main() 
{
	engine e;
	engine_init(&e);
	engine_run(&e);
	engine_destroy(&e);
}
