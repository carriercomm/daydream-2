@ECHO off

CALL :deploy Debug d
CALL :deploy Release
GOTO:eof

:deploy
SET Configuration=%~1
SET ConfigurationShort=%~2
SET ConfigPath=bin\%~1
ECHO Deploying %Configuration%
:: Asset folders
MKLINK "%ConfigPath%\Models\" "assets\Models" /J
MKLINK "%ConfigPath%\Textures\" "assets\Textures\" /J
MKLINK "%ConfigPath%\Sounds\" "assets\Sounds\" /J
:: Shaders
MKLINK "%ConfigPath%\Shaders\" "src\dd\Core\Shaders\" /J
:: DLLs
COPY "libs\assimp-3.1.1\lib\%Configuration%\assimp%ConfigurationShort%.dll" "%ConfigPath%\assimp%ConfigurationShort%.dll"
COPY "libs\glfw-3.0.4\lib\%Configuration%\glfw3.dll" "%ConfigPath%\glfw3.dll"
COPY "libs\glew-1.11.0\bin\%Configuration%\Win32\glew32%ConfigurationShort%.dll" "%ConfigPath%\glew32%ConfigurationShort%.dll"
:: Licenses
COPY "libs\assimp-3.1.1\LICENSE" "%ConfigPath%\Assimp License.txt"
COPY "libs\glew-1.11.0\LICENSE.txt" "%ConfigPath%\GLEW License.txt"
COPY "libs\glm-0.9.5.4\copying.txt" "%ConfigPath%\GLM License.txt"
COPY "libs\assimp-3.1.1\LICENSE" "%ConfigPath%\Assimp License.txt"

GOTO:eof