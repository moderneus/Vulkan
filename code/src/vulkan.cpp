#include "engine/Engine.hpp"

int main() 
{
	engine_t e;
	engine_init(&e);
	engine_run(&e);
	engine_destroy(&e);
}
