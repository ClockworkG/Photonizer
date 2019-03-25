#include "cli.hh"

#include "image-rgb.hh"
#include "image-writer.hh"
#include "ppm-writer.hh"

namespace raytracer::cli
{
    RaytracerCommand::RaytracerCommand(CLI::App& cli)
        : ::cli::PhotonizerCommand(cli, {"trace", "Raytracer command"})
    {}

    void RaytracerCommand::configure()
    {
        app_->add_option("-m,--map", photon_map_file_, "Photon map file");
        app_->add_option("-r,--radius", config_.photon_gathering_radius,
                         "Photon gathering radius");
        app_->add_option("-c,--count", config_.photon_gathering_count,
                         "Photon gathering count");
        app_->add_option("output-file", output_file_,
                         "Rendered image output");
    }

    void RaytracerCommand::execute(std::shared_ptr<const scene::Scene> scene)
    {
        image::PPMWriter<image::ImageRGB> ppm_writer{};
        std::ofstream output_stream{output_file_};

        auto photon_map = photon::PhotonMap(photon_map_file_);
        auto image_output = raytracer::render<image::ImageRGB, raytracer::RayTracer>(
                scene,
                std::move(photon_map),
                config_
        );

        spdlog::info("Writing output to {0}", output_file_);
        ppm_writer.write(output_stream, image_output);
    }
} // namespace raytracer::cli
