#include <iostream>
#include <string>

#include <cli/photonizer-cli.hh>
#include <photon_map/cli.hh>
#include <raytracer/cli.hh>

constexpr static inline auto version = (PHOTONIZER_VERSION);

int main(int argc, char **argv)
{
    cli::PhotonizerCLI app(version);
    app.add_subcommand<photon::cli::PhotonMapCommand>();
    app.add_subcommand<raytracer::cli::RaytracerCommand>();
    return app(argc, argv);
}
