#include <iostream>
#include <boost/program_options.hpp>

#include "vector3.hh"

constexpr auto version = (PHOTONIZER_VERSION);

namespace boostopt = boost::program_options;

int main(int argc, char **argv)
{
    Vector3<int> v1(1, 2, 3);
    Vector3<int> v2(2, 0, -1); 
    Vector3<int> v3 = v1 + v2;
    v3 = v1 - v2;
    v3 = v1 ^ v2;
    std::cout << v1 * v2 << std::endl;
    boostopt::options_description desc{"photonizer [--version]"};
    desc.add_options()
        ("help,h", "Display help message.")
        ("version,v", "Display version information.\n");

    boostopt::variables_map opts;
    try {
        boostopt::store(parse_command_line(argc, argv, desc), opts);
        boostopt::notify(opts);
    }
    catch (const boostopt::unknown_option& exc)
    {
        std::cerr << "Error while parsing command line options: "
                  << exc.what() << "\n\n" << desc << std::endl;
        return EXIT_FAILURE;
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

    return EXIT_SUCCESS;
}
