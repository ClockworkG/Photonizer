#include "photonizer-command.hh"

namespace cli
{
    PhotonizerCommand::PhotonizerCommand(CLI::App& cli,
                                         const Desc& desc)
        : app_(cli.add_subcommand(desc.name, desc.desc))
    {}

    void PhotonizerCommand::operator()(scene::scene_ptr_t scene)
    {
        if (app_->parsed())
            execute(scene);
    }
} // namespace cli
