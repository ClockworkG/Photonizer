#pragma once

#include <CLI11.hpp>

#include "scene.hh"

namespace cli
{
    class PhotonizerCommand
    {
    public:
        struct Desc
        {
            const char* name;
            const char* desc;
        };

        PhotonizerCommand(CLI::App& cli, const Desc& desc);
        virtual ~PhotonizerCommand() = default;
        PhotonizerCommand(const PhotonizerCommand&) = delete;
        PhotonizerCommand(PhotonizerCommand&&) = delete;
        PhotonizerCommand& operator=(const PhotonizerCommand&&) = delete;
        PhotonizerCommand& operator=(PhotonizerCommand&&) = delete;

        void operator()(scene::scene_ptr_t scene);
        virtual void configure() = 0;

    protected:
        virtual void execute(scene::scene_ptr_t scene) = 0;

        CLI::App* app_;
    };
} // namespace cli
