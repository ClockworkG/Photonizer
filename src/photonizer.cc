#include <iostream>
#include <string>

#include <scene/libscene.hh>

#include <boost/program_options.hpp>

constexpr const char* version = PHOTONIZER_VERSION;
constexpr auto error_message = "Error while parsing command line options: ";

#define ARG_ERROR_EXIT(Exception, Description, Exitcode)                \
    do {                                                                \
        std::cerr << error_message << (Exception).what() << "\n\n"      \
                  << (Description);                                     \
        std::exit(Exitcode);                                            \
    } while (false)

namespace boostopt = boost::program_options;

int main(int argc, char **argv)
{
    boostopt::options_description desc{"General options"};
    desc.add_options()
        ("help,h", "Display help message.")
        ("version,v", "Display version information.")
    ;

    std::string scene_file{};
    boostopt::options_description hidden{};
    hidden.add_options()
        (
         "scene-file",
         boostopt::value<std::string>(&scene_file), "scene"
        );

    boostopt::options_description all_opts{};
    all_opts.add(desc);
    all_opts.add(hidden);

    boostopt::positional_options_description positional_desc{};
    positional_desc.add("scene-file", 1);

    boostopt::variables_map vm;
    try {
        boostopt::store(boostopt::command_line_parser(argc, argv)
                        .options(all_opts)
                        .positional(positional_desc)
                        .run(), vm);
        boostopt::notify(vm);
    }
    catch (const boostopt::unknown_option& exc)
    {
        ARG_ERROR_EXIT(exc, all_opts, EXIT_FAILURE);
    }
    catch (const boostopt::required_option& exc)
    {
        ARG_ERROR_EXIT(exc, all_opts, EXIT_FAILURE);
    }

    if (vm.count("help"))
    {
        std::cout << all_opts;
        return EXIT_SUCCESS;
    }

    if (vm.count("version"))
    {
        std::cout << "Raytracer & Photon Mapping - ISIM Project\n"
                  << "Alexandre Lamure, Robin Le Bihan - EPITA Image 2020\n"
                  << "Version " << version << '\n';
        return EXIT_SUCCESS;
    }

    if (scene_file.empty())
    {
        std::cout << "Missing scene file\n" << all_opts;
        return EXIT_FAILURE;
    }

    auto the_scene = scene::load_scene(scene_file);
    if (!the_scene)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
