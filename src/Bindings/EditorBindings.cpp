#include <Bindings/EditorBindings.hpp>
#include <Editor/Grid.hpp>

namespace obe
{
    namespace Bindings
    {
        namespace EditorBindings
        {
            void LoadEditorGrid(kaguya::State& lua)
            {
                lua["Core"]["Editor"]["EditorGrid"].setClass(kaguya::UserdataMetatable<Editor::EditorGrid>()
                    .addFunction("draw", &Editor::EditorGrid::draw)
                    .addFunction("getCellHeight", &Editor::EditorGrid::getCellHeight)
                    .addFunction("getCellWidth", &Editor::EditorGrid::getCellWidth)
                    .addFunction("getOffsetX", &Editor::EditorGrid::getOffsetX)
                    .addFunction("getOffsetY", &Editor::EditorGrid::getOffsetY)
                    .addFunction("magnetize", &Editor::EditorGrid::magnetize)
                    .addFunction("moveMagnet", &Editor::EditorGrid::moveMagnet)
                    .addFunction("setCellHeight", &Editor::EditorGrid::setCellHeight)
                    .addFunction("setCellWidth", &Editor::EditorGrid::setCellWidth)
                    .addFunction("setOffset", &Editor::EditorGrid::setOffset)
                    .addFunction("setOffsetX", &Editor::EditorGrid::setOffsetX)
                    .addFunction("setOffsetY", &Editor::EditorGrid::setOffsetY)
                    .addFunction("setSize", &Editor::EditorGrid::setSize)
                );
            }
        }
    }
}