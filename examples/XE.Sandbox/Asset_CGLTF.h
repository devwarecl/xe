
#pragma once

#include <string>
#include <vector>
#include <functional>

#include <XE/Graphics/Subset.h>
#include <XE/Math/Vector.h>
#include <XE/Math/Matrix.h>

#include <cgltf.h>

#include "Common.h"

namespace Sandbox {
    class SceneLoaderGLTF : public SceneLoader {
    public:
        Scene load(const std::string &filePath) const override;
    };


    using SceneNodeCallback = std::function<void (const XE::Matrix4f &transform, const std::string &meshName)>;


    class Asset_CGLTF {
    public:
        Asset_CGLTF();
        
        Asset_CGLTF(const std::string &filePath);
        
        ~Asset_CGLTF();
        
        void load(const std::string &filePath);
        
        void visitDefaultScene(SceneNodeCallback callback);
        
        std::vector<Mesh> getMeshes() const;
        
    private:
        void visitNode(const XE::Matrix4f &matrix, const cgltf_node *node);
        
        void visitScene(const cgltf_scene *scene);
        
    private:
        cgltf_data *mData = nullptr;
        SceneNodeCallback mCallback;
    };
}
