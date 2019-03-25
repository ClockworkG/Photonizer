#pragma once

#include "photonizer-command.hh"
#include "libraytracer.hh"

namespace raytracer::cli
{
    class RaytracerCommand : public ::cli::PhotonizerCommand
    {
    public:
        using ::cli::PhotonizerCommand::Desc;

        RaytracerCommand(CLI::App& cli);
        virtual ~RaytracerCommand() = default;
        RaytracerCommand(const RaytracerCommand&) = delete;
        RaytracerCommand(RaytracerCommand&&) = delete;
        RaytracerCommand& operator=(const RaytracerCommand&) = delete;
        RaytracerCommand& operator=(RaytracerCommand&&) = delete;

        void configure() final;

    protected:
        void execute(std::shared_ptr<const scene::Scene> scene) final;

    private:
        std::string output_file_ = "output.ppm";
        std::string photon_map_file_ = "";
        raytracer::RaytracerConfig config_;
    };
} // namespace raytracer::cli
