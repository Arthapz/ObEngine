#include <vili/Vili.hpp>

#include <System/MountablePath.hpp>
#include <System/Path.hpp>
#include <System/Workspace.hpp>

namespace obe
{
    namespace System
    {
        namespace Workspace
        {
            std::string GetWorkspaceLocation(const std::string& workspaceName)
            {
                if (WorkspaceExists(workspaceName))
                    return (vili::DataParser("Workspace/Workspaces.vili")->at<vili::BaseAttribute>(workspaceName, "path").get<std::string>());
                throw aube::ErrorHandler::Raise("ObEngine.Workspace.Workspace.InexistantWorkspace", {{"workspace", workspaceName}});
            }

            bool WorkspaceExists(const std::string& workspaceName)
            {
                return (vili::DataParser("Workspace/Workspaces.vili")->contains(vili::AttributeType::ComplexAttribute, workspaceName));
            }

            bool Load(const std::string& workspaceName, unsigned int priority)
            {
                if (WorkspaceExists(workspaceName))
                {
                    Path::Mount(MountablePath(PathType::Workspace, GetWorkspaceLocation(workspaceName), priority));
                    std::cout << "<System> Mounting Workspace : " << workspaceName << " : " << GetWorkspaceLocation(workspaceName) << std::endl;
                    return true;
                }
                throw aube::ErrorHandler::Raise("ObEngine.Workspace.Workspace.InexistantWorkspace", {{"workspace", workspaceName}});
            }
        }
    }
}
