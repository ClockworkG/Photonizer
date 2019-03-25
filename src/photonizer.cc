#include <iostream>
#include <string>

#include <scene/libscene.hh>
#include <raytracer/libraytracer.hh>
#include <photon_map/libphoton.hh>
#include <image/image-rgb.hh>
#include <image/ppm-writer.hh>

#include <CLI11.hpp>
#include <spdlog/spdlog.h>

constexpr static inline auto version = (PHOTONIZER_VERSION);

int main(int argc, char **argv)
{
    spdlog::info("Running photonizer v{0}", version);
    CLI::App app{"Photonizer - raytracer extended with photon mapping"};

    bool debug_mode = false;
    std::string scene_file{};
    std::string output_file{"output.ppm"};
    std::string photon_file{"photons.pht"};
    std::string photon_map_file{};
    photon::PhotonTracerConfig p_config{};
    raytracer::RaytracerConfig r_config{};

    app.require_subcommand();
    app.add_flag("-g,--debug", debug_mode, "Enable debug logging");
    app.add_option("scene-file", scene_file, "JSON containing the scene")
        ->required()
        ->check(CLI::ExistingFile);

    auto photon_cmd = app.add_subcommand("map", "Photon mapping commands");
    auto ray_cmd = app.add_subcommand("trace", "Raytracer commands");

    ray_cmd->add_option("-m,--map", photon_map_file, "Photon map file");
    ray_cmd->add_option("-r,--radius", r_config.photon_gathering_radius, "Photon gathering radius");
    ray_cmd->add_option("-c,--count", r_config.photon_gathering_count, "Photon gathering count");
    ray_cmd->add_option("output-file", output_file, "PPM output");
    photon_cmd->add_option("output-file", photon_file, "Phton map output file");
    photon_cmd->add_option("-p,--photons", p_config.max_photons, "Number of photons to emit");
    photon_cmd->add_option("-b,--bounces", p_config.max_bounces, "Number of max bounces per photon");

    try {
        app.parse(argc, argv);
    } catch (const CLI::Error& e) {
        return app.exit(e);
    }

    if (debug_mode)
        spdlog::set_level(spdlog::level::debug);

    auto the_scene = scene::load_scene(scene_file);
    if (the_scene == nullptr)
        return EXIT_FAILURE;

    if (photon_cmd->parsed())
    {
        auto photon_map = photon::build_photon_map(the_scene, p_config);
        photon_map.serialize(photon_file);
    }

    if (ray_cmd->parsed())
    {
        image::PPMWriter<image::ImageRGB> ppm_writer{};
        std::ofstream output_stream{output_file};

        auto photon_map = photon::PhotonMap(photon_map_file);
        auto image_output = raytracer::render<image::ImageRGB>(
                the_scene,
                std::move(photon_map),
                r_config
        );

        spdlog::info("Writing output to {0}", output_file);
        ppm_writer.write(output_stream, image_output);
    }

    return EXIT_SUCCESS;
}
