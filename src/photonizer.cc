#include <iostream>
#include <string>

#include <scene/libscene.hh>
#include <raytracer/raytracer.hh>
#include <image/image-rgb.hh>
#include <image/ppm-writer.hh>

#include <CLI11.hpp>
#include <spdlog/spdlog.h>

constexpr static inline auto version = (PHOTONIZER_VERSION);

int main(int argc, char **argv)
{
    CLI::App app{"Photonizer - raytracer extended with photon mapping"};

    std::string scene_file{};
    std::string output_file{"output.ppm"};

    app.require_subcommand();
    app.add_option("scene-file", scene_file, "JSON containing the scene")
        ->required()
        ->check(CLI::ExistingFile);

    auto photon_cmd = app.add_subcommand("map", "Photon mapping commands");
    auto ray_cmd = app.add_subcommand("trace", "Raytracer commands");

    ray_cmd->add_option("output-file", output_file, "PPM output");

    try {
        app.parse(argc, argv);
    } catch (const CLI::Error& e)
    {
        return app.exit(e);
    }

    auto the_scene = scene::load_scene(scene_file);
    if (the_scene == nullptr)
        return EXIT_FAILURE;

    if (ray_cmd->parsed())
    {
        auto image_output = raytracer::render(*the_scene);
        image::PPMWriter<image::ImageRGB> ppm_writer{};
        std::ofstream output_stream{output_file};

        spdlog::info("Writing output to {0}", output_file);
        ppm_writer.write(output_stream, image_output);
    }

    return EXIT_SUCCESS;
}
