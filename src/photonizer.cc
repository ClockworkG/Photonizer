#include <iostream>
#include <string>

#include "scene/libscene.hh"

#include <boost/program_options.hpp>

constexpr auto version = (PHOTONIZER_VERSION);
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
    boostopt::options_description desc{"photonizer [--version]"};
    desc.add_options()
        ("help,h", "Display help message.")
        ("version,v", "Display version information.")
        (
         "scene,s",
         boostopt::value<std::string>()->required(),
         "Scene configuration file.\n"
        );

    boostopt::variables_map opts;
    try {
        boostopt::store(parse_command_line(argc, argv, desc), opts);
        boostopt::notify(opts);
    }
    catch (const boostopt::unknown_option& exc)
    {
        ARG_ERROR_EXIT(exc, desc, EXIT_FAILURE);
    }
    catch (const boostopt::required_option& exc)
    {
        ARG_ERROR_EXIT(exc, desc, EXIT_FAILURE);
    }

    if (opts.count("help"))
    {
        std::cout << desc;
        return EXIT_SUCCESS;
    }

    if (opts.count("version"))
    {
        std::cout << "Raytracer & Photon Mapping - ISIM Project\n"
                  << "Alexandre Lamure, Robin Le Bihan - EPITA Image 2020\n"
                  << "Version " << version << '\n';
        return EXIT_SUCCESS;
    }

    auto filename = opts["scene"].as<std::string>();
    auto the_scene = scene::load_scene(filename);
    if (!the_scene)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
