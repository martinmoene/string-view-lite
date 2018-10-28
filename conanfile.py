from conans import ConanFile

class StringViewLiteConan(ConanFile):
    version = "0.0.0"
    name = "string-view-lite"
    description = "string-view"
    license = "Boost Software License - Version 1.0. http://www.boost.org/LICENSE_1_0.txt"
    url = "https://github.com/martinmoene/string-view-lite.git"
    exports_sources = "include/nonstd/*", "LICENSE.txt"
    build_policy = "missing"    
    author = "Martin Moene"

    def build(self):
        """Avoid warning on build step"""
        pass

    def package(self):
        """Provide pkg/include/nonstd/*.hpp"""
        self.copy("*.hpp")

    def package_info(self):
        self.info.header_only()
