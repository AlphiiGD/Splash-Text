#include <Geode/Geode.hpp>

using namespace geode::prelude;

$on_mod(Loaded)
{
	// If the config dir doesn't exist we have to create it.
	Mod::get()->getConfigDir(true);
}