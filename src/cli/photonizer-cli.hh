#pragma once

#include <list>
#include <string>

#include <CLI11.hpp>

#include "photonizer-command.hh"

namespace cli
{
    class PhotonizerCLI
    {
    public:
        PhotonizerCLI();
        ~PhotonizerCLI();
        PhotonizerCLI(const PhotonizerCLI&) = delete;
        PhotonizerCLI(PhotonizerCLI&&) = delete;
        PhotonizerCLI& operator=(const PhotonizerCLI&) = delete;
        PhotonizerCLI& operator=(PhotonizerCLI&&) = delete;

        template <typename Type, typename ... Args>
        void add_subcommand(Args&&... args);

        int operator()(int argc, char** argv);

    private:
        CLI::App app_;

        std::list<PhotonizerCommand*> subcommands_;

        bool debug_mode_ = false;
        std::string scene_file_ = "";
    };

    template <typename Type, typename ... Args>
    void PhotonizerCLI::add_subcommand(Args&&... args)
    {
        auto sub = new Type(app_, std::forward<Args>(args)...);
        sub->configure();
        subcommands_.push_back(sub);
    }
} // namespace cli
