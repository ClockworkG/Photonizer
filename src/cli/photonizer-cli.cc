#include "photonizer-cli.hh"

#include <spdlog/spdlog.h>

#include "libscene.hh"

namespace cli
{
    PhotonizerCLI::PhotonizerCLI(const char* version)
        : app_{"Photonizer - raytracer extended with photon mapping"}
        , version_(version)
    {
        app_.require_subcommand();
        app_.add_flag("-g,--debug", debug_mode_, "Enable debug logging");
        app_.add_option("scene-file", scene_file_, "JSON containing the scene")
            ->required()
            ->check(CLI::ExistingFile);
    }

    PhotonizerCLI::~PhotonizerCLI()
    {
        for (auto* cmd : subcommands_)
            delete cmd;
    }

    int PhotonizerCLI::operator()(int argc, char** argv)
    {
        try {
            app_.parse(argc, argv);
        } catch (const CLI::Error& e) {
            return app_.exit(e);
        }

        if (debug_mode_)
            spdlog::set_level(spdlog::level::debug);

        auto the_scene = scene::load_scene(scene_file_);
        for (auto* cmd : subcommands_)
            (*cmd)(the_scene);

        return EXIT_SUCCESS;
    }
} // namespace cli
