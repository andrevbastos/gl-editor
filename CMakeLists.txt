# Versão mínima do CMake e nome do projeto
cmake_minimum_required(VERSION 3.15)
project(gl-editor LANGUAGES C CXX)

# Configurações do CMake
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (UNIX)
    # Copia o compile_commands.json para a raiz do projeto para facilitar o uso por IDEs/linters
    add_custom_target(
        copy-compile-commands ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
        COMMENT "Copiando compile_commands.json para a raiz do projeto..."
    )
endif (UNIX)

# Flags de Compilação Comuns
set(COMMON_CXX_FLAGS "-Wall")
if (CMAKE_COMPILER_IS_GNUXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} -Wextra -Wpedantic")
endif ()

set(CMAKE_CXX_FLAGS_DEBUG_INIT "${COMMON_CXX_FLAGS} -g3")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "${COMMON_CXX_FLAGS} -O3 -DNDEBUG")

# Opção para sanitizers (útil para debug)
option(ENABLE_SANITIZERS "Enable Address and Undefined Behavior Sanitizers" OFF)
if(ENABLE_SANITIZERS AND CMAKE_BUILD_type MATCHES Debug)
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "${CMAKE_CXX_FLAGS_DEBUG_INIT} -fsanitize=address,undefined")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT "${CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT} -fsanitize=address,undefined")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG_INIT "${CMAKE_SHARED_LINKER_FLAGS_DEBUG_INIT} -fsanitize=address,undefined")
endif()

# Define CMAKE_BUILD_TYPE se não estiver definido (ex: por presets ou linha de comando)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

message(STATUS "Tipo de Build: ${CMAKE_BUILD_TYPE}")

# Encontrar Pacotes
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 CONFIG REQUIRED)
find_package(glm 0.9.9 REQUIRED)
find_package(Doxygen OPTIONAL_COMPONENTS dot)

# =-=-=-=-=-=-= DOCUMENTAÇÃO (Doxygen) =-=-=-=-=-=-=
if (DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_CONFIG_FILE ${CMAKE_SOURCE_DIR}/Doxyfile)

    if(EXISTS ${DOXYGEN_CONFIG_FILE})
        message(STATUS "Doxygen encontrado. Você pode usar `make docs` ou `ninja docs`.")
        add_custom_target(
            docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG_FILE}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Gerando documentação com Doxygen (saída em ${DOXYGEN_OUTPUT_DIR})..."
            VERBATIM
        )
    else()
        message(WARNING "Doxyfile não encontrado em ${DOXYGEN_CONFIG_FILE}. O target `docs` pode não funcionar como esperado.")
    endif()
else (DOXYGEN_FOUND)
    message(WARNING "Doxygen não encontrado. O target `docs` não estará disponível.")
endif (DOXYGEN_FOUND)

# =-=-=-=-=-=-= BIBLIOTECA gl-editor =-=-=-=-=-=-=
# Define onde as bibliotecas (.so, .dll, .dylib) serão colocadas
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Diretório base dos arquivos fonte da biblioteca
set(GL_EDITOR_LIB_BASE_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Encontra recursivamente todos os arquivos .cpp dentro do diretório fonte da biblioteca
file(GLOB_RECURSE GL_EDITOR_LIBRARY_CPP_FILES CONFIGURE_DEPENDS
    "${GL_EDITOR_LIB_BASE_SOURCE_DIR}/*.cpp"
)

# Lista final de arquivos fonte para a biblioteca
set(GL_EDITOR_LIBRARY_SOURCE_FILES
    ${GL_EDITOR_LIB_BASE_SOURCE_DIR}/glad/glad.c
    ${GL_EDITOR_LIBRARY_CPP_FILES}
)

# Adicionando a biblioteca gl-editor como SHARED (compartilhada)
add_library(gl-editor SHARED ${GL_EDITOR_LIBRARY_SOURCE_FILES})

# Definições de compilação para a biblioteca gl-editor
target_compile_definitions(gl-editor PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)

# Diretórios de Include para gl-editor
target_include_directories(
    gl-editor
    PUBLIC
        "${CMAKE_SOURCE_DIR}/include"
    PRIVATE
        "${GL_EDITOR_LIB_BASE_SOURCE_DIR}/glad"
)

# Bibliotecas para linkar com gl-editor
target_link_libraries(
    gl-editor
    PUBLIC
        OpenGL::GL
        glfw
        glm::glm
)

# Define o diretório de output para executáveis
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# =-=-=-=-=-=-= APLICAÇÃO PRINCIPAL =-=-=-=-=-=-=
set(APP_SOURCE_DIR ${CMAKE_SOURCE_DIR}/tests)
set(APP_MAIN_SOURCE_FILES "${APP_SOURCE_DIR}/main.cpp") # <-- Considere renomear seu arquivo de teste para algo mais genérico como main.cpp

add_executable(gl-editor_app ${APP_MAIN_SOURCE_FILES})

# Diretórios de Include para a Aplicação (para encontrar os headers da gl-editor)
target_include_directories(
    gl-editor_app
    PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
)

# Bibliotecas para linkar com a Aplicação
target_link_libraries(
    gl-editor_app
    PRIVATE
        gl-editor # Linka com a nossa nova biblioteca
)

# Comando Pós-Build para copiar DLLs no Windows (se gl-editor for SHARED)
if (WIN32)
    add_custom_command(TARGET gl-editor_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:gl-editor_app>
        $<TARGET_FILE_DIR:gl-editor_app>
        COMMAND_EXPAND_LISTS
        COMMENT "Copiando DLLs necessárias para o diretório do executável..."
    )
endif ()

# Mensagem final para o usuário
message(STATUS "Configuração do CMake concluída. Para construir, use 'make' ou 'ninja' no diretório de build.")
message(STATUS "Executável estará em: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/gl-editor_app")
message(STATUS "Biblioteca gl-editor estará em: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")