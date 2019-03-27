#include "photonizer-command.hh"

namespace cli
{
    PhotonizerCommand::PhotonizerCommand(CLI::App& cli,
                                         const Desc& desc)
        : app_(cli.add_subcommand(desc.name, desc.desc))
    {}

    void PhotonizerCommand::operator()(std::shared_ptr<const scene::Scene> scene)
    {
        if (app_->parsed())
            execute(scene);
    }
} // namespace cli
