#include "cli.hh"

#include "image-rgb.hh"
#include "heatmap.hh"
#include "density-tracer.hh"

namespace raytracer::cli
{
    RaytracerCommand::RaytracerCommand(CLI::App& cli)
        : ::cli::PhotonizerCommand(cli, {"trace", "Raytracer command"})
    {}

    void RaytracerCommand::configure()
    {
        app_->add_flag("--heatmap", heatmap_, "Enable heatmap rendering");
        app_->add_option("-m,--map", photon_map_file_, "Photon map file");
        app_->add_option("-r,--radius", config_.photon_gathering_radius,
                         "Photon gathering radius");
        app_->add_option("-c,--count", config_.photon_gathering_count,
                         "Photon gathering count");
        app_->add_option("-a,--anti-aliasing", config_.sample_rate,
                         "Sample rate of anti-aliasing");
        app_->add_option("output-file", output_file_,
                         "Rendered image output");
    }

    void RaytracerCommand::execute(scene::scene_ptr_t scene)
    {
        if (heatmap_)
            execute_<image::Heatmap<float>, DensityTracer>(scene);
        else
            execute_<image::ImageRGB, RayTracer>(scene);
    }
} // namespace raytracer::cli
