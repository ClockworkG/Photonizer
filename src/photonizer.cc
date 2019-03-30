#include <iostream>
#include <string>

#include <cli/photonizer-cli.hh>
#include <photon_map/cli.hh>
#include <raytracer/cli.hh>

int main(int argc, char **argv)
{
    cli::PhotonizerCLI app{};
    app.add_subcommand<photon::cli::PhotonMapCommand>();
    app.add_subcommand<raytracer::cli::RaytracerCommand>();
    return app(argc, argv);
}
