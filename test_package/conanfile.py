import os
from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.build import can_run


class apirestTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires("assinaturadigital/[>v0.1.15]")
        self.requires("verificaassinatura/[>=v0.3.6]")
        self.requires("cppunit/[>=1.15.1]")
    
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build
        
    def layout(self):
        cmake_layout(self)

    def test(self):
        if can_run(self):
            cmd_test = os.path.join(self.cpp.build.bindir, "teste")
            self.run(cmd_test)
