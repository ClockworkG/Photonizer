#pragma once

#include "photonizer-command.hh"
#include "libraytracer.hh"
#include "image-rgb.hh"
#include "ppm-writer.hh"

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
        template <typename Image, typename Tracer>
        void execute_(std::shared_ptr<const scene::Scene> scene);

        std::string output_file_ = "output.ppm";
        std::string photon_map_file_ = "";
        raytracer::RaytracerConfig config_;
        bool heatmap_ = false;
    };

    template <typename Image, typename Tracer>
    inline
    void RaytracerCommand::execute_(std::shared_ptr<const scene::Scene> scene)
    {
        image::PPMWriter<image::ImageRGB> ppm_writer{};
        std::ofstream output_stream{output_file_};

        auto photon_map = photon::PhotonMap(photon_map_file_);
        auto image_output = raytracer::render<Image, Tracer>(
                scene,
                std::move(photon_map),
                config_
        );

        spdlog::info("Writing output to {0}", output_file_);
        ppm_writer.write(output_stream, image_output);
    }
} // namespace raytracer::cli
