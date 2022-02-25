import qbs

CppApplication {
    name: "read-write-mutex-integration-tests"
    consoleApplication: true
    cpp.cxxLanguageVersion: "c++20"
    cpp.enableRtti: false
    cpp.includePaths: ["inc", "inc_dep"]
    Properties {
        condition: qbs.buildVariant == "debug"
        cpp.staticLibraries: ["pthread"]
        cpp.debugInformation: true
        cpp.optimization: "none"
    }
    Properties {
        condition: qbs.buildVariant == "release"
        cpp.staticLibraries: ["pthread"]
        cpp.debugInformation: false
        cpp.optimization: "O3"
    }
    Properties {
        condition: qbs.buildVariant == "sanitizer"
        cpp.cxxFlags: "-fsanitize=thread"
        cpp.staticLibraries: ["tsan", "pthread"]
        cpp.debugInformation: true
        cpp.optimization: "none"
    }
    files: [
        "inc_dep/read_write_mutex.hpp",
        "inc/base.hpp",
        "inc/consumer.hpp",
        "inc/producer.hpp",
        "inc/viewer.hpp",
        "src/integration_test.cpp",
    ]
    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
