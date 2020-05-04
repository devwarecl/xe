
#include "EllipsoidGenerator.hpp"

#include <XE/Math/Matrix.hpp>

namespace XE {
    Vector3f sphere_vertex_at(const int slices, const int stacks, const int i, const int j) {
        const float phi = 0.0f;
        const float theta = 0.0f;

        const float cos_phi = std::cos(phi);
        const float cos_theta = std::cos(theta);

        return {
            std::cos(phi) * std::cos(theta),
            std::cos(phi) * std::sin(theta),
            std::sin(theta)
        };
    }


    EllipsoidGenerator::EllipsoidGenerator(const int slices, const int stacks, const Vector3f &dimensions) {
        this->slices = slices;
        this->stacks = stacks;
        this->dimensions = dimensions;
    }


    EllipsoidGenerator::~EllipsoidGenerator() {}


    std::vector<Vector3f> EllipsoidGenerator::generateVertexCoordinates() const {
        const float delta_theta = XE::radians(360.0f) / static_cast<float>(stacks);
        const float delta_phi = XE::radians(180.0f) / static_cast<float>(slices);

        for (int i = 0; i < stacks; i++) {
            const float theta = i * delta_theta;

            for (int j = 0; j < slices; j++) {    
                const float phi = j * delta_phi;
            }
        }

        return {};
    }


    std::vector<Vector3f> EllipsoidGenerator::generateVertexNormals() const {
        return {};
    }


    std::vector<Vector2f> EllipsoidGenerator::generateVertexTexCoords() const {
        return {};
    }


    std::vector<int> EllipsoidGenerator::generateIndices() const {
        return {};
    }
}
