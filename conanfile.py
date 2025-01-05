from conan import ConanFile

class AvrRecipe(ConanFile):
        def build_requirements(self):
                self.tool_requires("ninja/1.12.1")
                self.tool_requires("cmake/3.31.3")

        def build(self):
                print("my cmake building...")
