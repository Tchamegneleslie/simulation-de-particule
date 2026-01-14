@echo off
echo =====================
echo Compilation du projet 
echo =====================

clang++ ^sources/main.cpp ^sources/core/Application.cpp ^sources/ui/ImguiLayer.cpp ^external/imgui/imgui.cpp ^external/imgui/imgui_draw.cpp ^external/imgui/imgui_tables.cpp ^external/imgui/imgui_widgets.cpp ^external/imgui/backends/imgui_impl_sdl3.cpp ^external/imgui/backends/imgui_impl_sdlrenderer3.cpp ^-Iexternal/imgui ^-Iexternal/imgui/backends ^-Iexternal/SDL3/include ^-Isources ^-Lexternal/SDL3/lib ^-lSDL3 ^-o app.exe

if %errorlevel% neq 0 (
    echo.
    echo Erreur de Compilation
    pause
    exit /b %errorlevel%
)

echo.
echo Compilation reussie
echo.
pause

