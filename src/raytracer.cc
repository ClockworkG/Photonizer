#include <iostream>
#include <boost/program_options.hpp>

namespace boostopt = boost::program_options;

int main(int argc, char **argv)
{
    boostopt::options_description desc{"raytracer [--version]"};
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
        std::cout << desc << std::endl;
        return EXIT_SUCCESS;
    }

    if (opts.count("version"))
    {
        std::cout << "Version - 0.0.1" << std::endl;
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
