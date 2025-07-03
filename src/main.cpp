#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Empty default paths in mod.json breaks on iOS.
// Workaround is to create a config folder and use
// that as the default file on iOS.
#ifdef GEODE_IS_IOS
$on_mod(Loaded) {
    auto defaultSplash = Mod::get()->getConfigDir() / R"(default.splash)";
    if (std::filesystem::exists(defaultSplash)) return;
    const std::string& content = "# this is where she makes a mod";
    if (const auto result = utils::file::writeString(defaultSplash, content); result.isErr()) log::error("Error writing to default.splash");
}
#endif // #ifdef GEODE_IS_IOS