
#ifndef __XE_GRAPHICS_SHAPEGENERATOR_HPP__
#define __XE_GRAPHICS_SHAPEGENERATOR_HPP__

#include <vector>
#include <XE/Math.hpp>

namespace XE {
    class ShapeGenerator {
    public:
        virtual ~ShapeGenerator();

        virtual std::vector<XE::Math::Vector3f> GenerateVertexCoordinates() const = 0;

        virtual std::vector<XE::Math::Vector3f> GenerateVertexNormals() const = 0;

        virtual std::vector<XE::Math::Vector2f> GenerateVertexTexCoords() const = 0;

        virtual std::vector<int> GenerateIndices() const = 0;
    };
}

#endif
