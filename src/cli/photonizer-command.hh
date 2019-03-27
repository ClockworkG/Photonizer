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

        void operator()(std::shared_ptr<const scene::Scene> scene);
        virtual void configure() = 0;

    protected:
        virtual void execute(std::shared_ptr<const scene::Scene> scene) = 0;

        CLI::App* app_;
    };
} // namespace cli
