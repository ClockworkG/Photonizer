#include "cli.hh"

namespace photon::cli
{
    PhotonMapCommand::PhotonMapCommand(CLI::App& cli)
        : ::cli::PhotonizerCommand(cli, {"map", "Photon mapping command"})
    {}

    void PhotonMapCommand::configure()
    {
        app_->add_option("output-file", photon_file_, "Photon map output file");
        app_->add_option("-p,--photons", config_.max_photons, "Number of photons to emit");
        app_->add_option("-b,--bounces", config_.max_bounces, "Number of max bounces");
    }

    void PhotonMapCommand::execute(std::shared_ptr<const scene::Scene> scene)
    {
        auto photon_map = photon::build_photon_map(scene, config_);
        photon_map.serialize(photon_file_);
    }
} // namespace photon::cli
