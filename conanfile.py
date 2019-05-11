from conans import ConanFile, CMake

class StringViewLiteConan(ConanFile):
    version = "1.2.0"
    name = "string-view-lite"
    description = "string-view"
    license = "Boost Software License - Version 1.0. http://www.boost.org/LICENSE_1_0.txt"
    url = "https://github.com/martinmoene/string-view-lite.git"
    exports_sources = "include/nonstd/*", "CMakeLists.txt", "cmake/*", "LICENSE.txt"
    build_policy = "missing"
    author = "Martin Moene"

    def build(self):
        """Avoid warning on build step"""
        pass

    def package(self):
        """Run CMake install"""
        cmake = CMake(self)
        cmake.definitions["STRINGVIEW_LITE_OPT_BUILD_TESTS"] = "OFF"
        cmake.definitions["STRINGVIEW_LITE_OPT_BUILD_EXAMPLES"] = "OFF"
        cmake.configure()
        cmake.install()

    def package_info(self):
        self.info.header_only()
