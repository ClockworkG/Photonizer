#pragma once

#include "photonizer-command.hh"
#include "libphoton.hh"

namespace photon::cli
{
    class PhotonMapCommand : public ::cli::PhotonizerCommand
    {
    public:
        using ::cli::PhotonizerCommand::Desc;

        PhotonMapCommand(CLI::App& cli);
        virtual ~PhotonMapCommand() = default;
        PhotonMapCommand(const PhotonMapCommand&) = delete;
        PhotonMapCommand(PhotonMapCommand&&) = delete;
        PhotonMapCommand& operator=(const PhotonMapCommand&) = delete;
        PhotonMapCommand& operator=(PhotonMapCommand&&) = delete;

        void configure() final;

    protected:
        void execute(std::shared_ptr<const scene::Scene> scene) final;

    private:
        std::string photon_file_ = "photons.pht";
        std::string caustics_file_ = "";
        PhotonTracerConfig config_;
    };
} // namespace photon::cli
