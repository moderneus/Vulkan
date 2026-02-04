#include "engine/Engine.hpp"

int main() 
{
	engine_t engine;
	engine_init(&engine);
	engine_run(&engine);
	engine_destroy(&engine);
}
