from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain

class AvrRecipe(ConanFile):
        settings = "os", "arch", "compiler", "build_type"

        def build_requirements(self):
                self.tool_requires("ninja/1.12.1")
                self.tool_requires("cmake/3.31.3")

        def generate(self):
                cmake = CMakeDeps(self)
                cmake.generate()
                tc = CMakeToolchain(self, generator="Ninja")
                tc.user_presets_path = False
                tc.generate()

        def build(self):
                cmake = CMake(self)
                cmake.configure()
                cmake.build()
