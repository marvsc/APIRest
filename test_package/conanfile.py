import os
from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout
from conan.tools.build import can_run


class apirestTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires("assinaturadigital/[>v0.1.15]")
        self.requires("verificaassinatura/[>=v0.1.7]")
        self.requires("openssl/[>3.5.0 <4.0.0]")
        self.requires("cppunit/[>=1.15.1]")
        self.requires("poco/[>1.11.0]")

    def configure(self):
        self.options["poco"].enable_data_postgresql = False
        self.options["poco"].enable_data_mysql = False
        self.options["poco"].enable_activerecord = False
        self.options["poco"].enable_activerecord_compiler = False
        self.options["poco"].enable_apacheconnector = False
        self.options["poco"].enable_cppparser = False
        self.options["poco"].enable_data = False
        self.options["poco"].enable_data_odbc = False
        self.options["poco"].enable_data_sqlite = False
        self.options["poco"].enable_encodings = False
        self.options["poco"].enable_fork = False
        self.options["poco"].enable_jwt = False
        self.options["poco"].enable_mongodb = False
        self.options["poco"].enable_pagecompiler = False
        self.options["poco"].enable_pagecompiler_file2page = False
        self.options["poco"].enable_pdf = False
        self.options["poco"].enable_pocodoc = False
        self.options["poco"].enable_redis = False
        self.options["poco"].enable_sevenzip = False
        self.options["poco"].enable_xml = False
        self.options["poco"].enable_zip = False
        self.options["poco"].enable_prometheus = False
        self.options["poco"].enable_json = True
        self.options["openssl"].no_module = True

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        
    def layout(self):
        cmake_layout(self)

    def test(self):
        if can_run(self):
            cmd_test = os.path.join(self.cpp.build.bindir, "teste")
            self.run(cmd_test)
