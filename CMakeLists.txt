cmake_minimum_required(VERSION 3.23)

project(
  ocppi
  LANGUAGES CXX
  VERSION 0.2.3)

option(OCPPI_BUILD_EXAMPLES "Build examples of ocppi or not"
       ${PROJECT_IS_TOP_LEVEL})

option(OCPPI_ENABLE_TESTING "Enable test of ocppi or not"
       ${PROJECT_IS_TOP_LEVEL})

option(OCPPI_BUILD_SHARED_LIBRARY "Build a shared library or not"
       ${PROJECT_IS_TOP_LEVEL})

option(OCPPI_INSTALL "Enable install target or not" ${PROJECT_IS_TOP_LEVEL})

option(OCPPI_USE_VENDOR_EXPECTED
       "Use tl::expected which from vendor of project." OFF)

option(OCPPI_USE_VENDOR_SEMVER "Use semver which from vendor of project." OFF)

option(OCPPI_USE_VENDOR_JSON "Use nlohmann_json which from vendor of project."
       OFF)

option(OCPPI_USE_VENDOR_SPDLOG "Use spdlog which from vendor of project." OFF)

option(OCPPI_USE_VENDOR_ALL
       "Use all external dependencies which from vendor of project." OFF)

include(./cmake/CPM.cmake)

if(OCPPI_USE_VENDOR_ALL)

  set(OCPPI_USE_VENDOR_EXPECTED ON)
  set(OCPPI_USE_VENDOR_SEMVER ON)
  set(OCPPI_USE_VENDOR_JSON ON)
  set(OCPPI_USE_VENDOR_SPDLOG ON)

endif()

if(NOT TARGET expected)
  set(TL_EXPECTED_MINIMAL_VERSION 1.0.0)
  if(OCPPI_USE_VENDOR_EXPECTED)
    add_subdirectory(external/expected EXCLUDE_FROM_ALL)
    set_target_properties(expected PROPERTIES EXPECTED_BUILD_TESTS OFF)
  else()
    CPMFindPackage(
      NAME expected
      VERSION ${TL_EXPECTED_MINIMAL_VERSION}
      GITHUB_REPOSITORY TartanLlama/expected
      GIT_TAG v1.1.0
      GIT_SHALLOW ON
      OPTIONS "EXPECTED_BUILD_TESTS OFF"
      FIND_PACKAGE_ARGUMENTS "NAMES tl-expected"
      EXCLUDE_FROM_ALL ON)
  endif()
endif()

if(NOT TARGET semver::semver)
  if(OCPPI_USE_VENDOR_SEMVER)
    add_subdirectory(external/semver EXCLUDE_FROM_ALL)
  else()
    CPMFindPackage(
      NAME semver
      VERSION 0.3.0
      GITHUB_REPOSITORY Neargye/Semver
      GIT_TAG v0.3.1
      GIT_SHALLOW ON
      GIT_PROGRESS ON
      EXCLUDE_FROM_ALL ON)
  endif()
endif()

if(NOT TARGET nlohmann_json::nlohmann_json)
  set(JSON_MINIMAL_VERSION 3.11.2)
  if(OCPPI_USE_VENDOR_JSON)
    set(JSON_Install ON)
    add_subdirectory(external/json EXCLUDE_FROM_ALL)
  else()
    CPMFindPackage(
      NAME nlohmann_json
      VERSION ${JSON_MINIMAL_VERSION}
      URL "https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz"
      EXCLUDE_FROM_ALL ON
      OPTIONS "JSON_Install ON")
  endif()
endif()

if(NOT TARGET spdlog::spdlog)
  if(OCPPI_USE_VENDOR_SPDLOG)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    add_subdirectory(external/spdlog EXCLUDE_FROM_ALL)
  else()
    CPMFindPackage(
      NAME spdlog
      VERSION 1.10.0
      GITHUB_REPOSITORY "gabime/spdlog"
      GIT_TAG "v1.13.0"
      GIT_SHALLOW ON
      EXCLUDE_FROM_ALL ON
      OPTIONS
        "CMAKE_POSITION_INDEPENDENT_CODE ON" # NOTE:
                                             # https://github.com/gabime/spdlog/issues/1190
    )
  endif()
endif()

if(NOT TARGET tl::expected)
  # NOTE: v1.0.0 version of tl::expected doesn't have a namespaced alias so we
  # have to add it here.
  add_library(tl::expected ALIAS expected)
endif()

include(./cmake/GitSemver.cmake)

set(OCPPI_SEMVER ${PROJECT_VERSION})
gitsemver(OCPPI_SEMVER)

set(OCPPI_OCI_RUNTIME_SPEC_MIN "1.0.0")
set(OCPPI_OCI_RUNTIME_SPEC_MAX "1.1.0")
set(OCPPI_LIBRARY_TYPE "STATIC")
if(OCPPI_BUILD_SHARED_LIBRARY)
  set(OCPPI_LIBRARY_TYPE "SHARED")
endif()
set(OCPPI_SOVERSION 0)

set(CMAKE_CXX_FLAGS_DEBUG "-DSPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE")

include(./cmake/PFL.cmake)

pfl_init(ENABLE_TESTING ${OCPPI_ENABLE_TESTING} BUILD_EXAMPLES
         ${OCPPI_BUILD_EXAMPLES} INSTALL ${OCPPI_INSTALL})

pfl_add_library(
  SOVERSION
  ${OCPPI_SOVERSION}
  VERSION
  ${PROJECT_VERSION}
  TYPE
  ${OCPPI_LIBRARY_TYPE}
  INS
  include/ocppi/configure.hpp.in
  include/ocppi/runtime/configure.hpp.in
  SOURCES
  # find -regex '\.\/src\/.*\.\(h\|c\)pp' | sort
  ./src/ocppi/cli/CLI.cpp
  ./src/ocppi/cli/CommandFailedError.cpp
  ./src/ocppi/cli/CommonCLI.cpp
  ./src/ocppi/cli/crun/Crun.cpp
  ./src/ocppi/cli/ExecutableNotFoundError.cpp
  ./src/ocppi/cli/Process.cpp
  ./src/ocppi/cli/Process.hpp
  ./src/ocppi/cli/runc/Runc.cpp
  ./src/ocppi/cli/youki/Youki.cpp
  ./src/ocppi/configure.cpp
  ./src/ocppi/InvalidArgumentError.cpp
  ./src/ocppi/runtime/config/ConfigLoader.cpp
  ./src/ocppi/runtime/config/IncompatibleVersionError.cpp
  ./src/ocppi/runtime/config/InvalidConfigError.cpp
  ./src/ocppi/runtime/config/KeyMissingError.cpp
  ./src/ocppi/runtime/configure.cpp
  ./src/ocppi/runtime/config/WrongTypeError.cpp
  ./src/ocppi/runtime/ContainerID.cpp
  ./src/ocppi/runtime/CreateOption.cpp
  ./src/ocppi/runtime/DeleteOption.cpp
  ./src/ocppi/runtime/FeaturesOption.cpp
  ./src/ocppi/runtime/GlobalOption.cpp
  ./src/ocppi/runtime/KillOption.cpp
  ./src/ocppi/runtime/RunOption.cpp
  ./src/ocppi/runtime/Runtime.cpp
  ./src/ocppi/runtime/semver_range.cpp
  ./src/ocppi/runtime/semver_range.hpp
  ./src/ocppi/runtime/Signal.cpp
  ./src/ocppi/runtime/StartOption.cpp
  ./src/ocppi/runtime/StateOption.cpp
  HEADERS
  # find -regex '\.\/include\/.*\.hpp' | sort
  ./include/ocppi/cli/CLI.hpp
  ./include/ocppi/cli/CommandFailedError.hpp
  ./include/ocppi/cli/CommonCLI.hpp
  ./include/ocppi/cli/crun/Crun.hpp
  ./include/ocppi/cli/ExecutableNotFoundError.hpp
  ./include/ocppi/cli/runc/Runc.hpp
  ./include/ocppi/cli/youki/Youki.hpp
  ./include/ocppi/InvalidArgumentError.hpp
  ./include/ocppi/runtime/config/ConfigLoader.hpp
  ./include/ocppi/runtime/config/IncompatibleVersionError.hpp
  ./include/ocppi/runtime/config/InvalidConfigError.hpp
  ./include/ocppi/runtime/config/KeyMissingError.hpp
  ./include/ocppi/runtime/config/types/Anet.hpp
  ./include/ocppi/runtime/config/types/BlockIODeviceThrottle.hpp
  ./include/ocppi/runtime/config/types/BlockIODeviceWeight.hpp
  ./include/ocppi/runtime/config/types/BlockIO.hpp
  ./include/ocppi/runtime/config/types/BoottimeClass.hpp
  ./include/ocppi/runtime/config/types/Capabilities.hpp
  ./include/ocppi/runtime/config/types/CappedCPU.hpp
  ./include/ocppi/runtime/config/types/CappedMemory.hpp
  ./include/ocppi/runtime/config/types/Class.hpp
  ./include/ocppi/runtime/config/types/Config.hpp
  ./include/ocppi/runtime/config/types/ConsoleSize.hpp
  ./include/ocppi/runtime/config/types/DeviceCgroup.hpp
  ./include/ocppi/runtime/config/types/FluffyCPU.hpp
  ./include/ocppi/runtime/config/types/FluffyMemory.hpp
  ./include/ocppi/runtime/config/types/Generators.hpp
  ./include/ocppi/runtime/config/types/helper.hpp
  ./include/ocppi/runtime/config/types/Hook.hpp
  ./include/ocppi/runtime/config/types/Hooks.hpp
  ./include/ocppi/runtime/config/types/HugepageLimit.hpp
  ./include/ocppi/runtime/config/types/Hyperv.hpp
  ./include/ocppi/runtime/config/types/Hypervisor.hpp
  ./include/ocppi/runtime/config/types/IdMapping.hpp
  ./include/ocppi/runtime/config/types/IdType.hpp
  ./include/ocppi/runtime/config/types/Image.hpp
  ./include/ocppi/runtime/config/types/IntelRdt.hpp
  ./include/ocppi/runtime/config/types/IoPriority.hpp
  ./include/ocppi/runtime/config/types/Kernel.hpp
  ./include/ocppi/runtime/config/types/LinuxDevice.hpp
  ./include/ocppi/runtime/config/types/Linux.hpp
  ./include/ocppi/runtime/config/types/LinuxResources.hpp
  ./include/ocppi/runtime/config/types/Mount.hpp
  ./include/ocppi/runtime/config/types/NamespaceReference.hpp
  ./include/ocppi/runtime/config/types/NamespaceType.hpp
  ./include/ocppi/runtime/config/types/NetworkInterfacePriority.hpp
  ./include/ocppi/runtime/config/types/PersonalityDomain.hpp
  ./include/ocppi/runtime/config/types/Personality.hpp
  ./include/ocppi/runtime/config/types/Pids.hpp
  ./include/ocppi/runtime/config/types/Process.hpp
  ./include/ocppi/runtime/config/types/PurpleCPU.hpp
  ./include/ocppi/runtime/config/types/PurpleMemory.hpp
  ./include/ocppi/runtime/config/types/Rdma.hpp
  ./include/ocppi/runtime/config/types/ResourcesNetwork.hpp
  ./include/ocppi/runtime/config/types/Rlimit.hpp
  ./include/ocppi/runtime/config/types/RootfsPropagation.hpp
  ./include/ocppi/runtime/config/types/Root.hpp
  ./include/ocppi/runtime/config/types/RootImageFormat.hpp
  ./include/ocppi/runtime/config/types/SchedulerFlag.hpp
  ./include/ocppi/runtime/config/types/Scheduler.hpp
  ./include/ocppi/runtime/config/types/SchedulerPolicy.hpp
  ./include/ocppi/runtime/config/types/SeccompAction.hpp
  ./include/ocppi/runtime/config/types/SeccompArch.hpp
  ./include/ocppi/runtime/config/types/SeccompFlag.hpp
  ./include/ocppi/runtime/config/types/Seccomp.hpp
  ./include/ocppi/runtime/config/types/SeccompOperators.hpp
  ./include/ocppi/runtime/config/types/Solaris.hpp
  ./include/ocppi/runtime/config/types/Storage.hpp
  ./include/ocppi/runtime/config/types/SyscallArg.hpp
  ./include/ocppi/runtime/config/types/Syscall.hpp
  ./include/ocppi/runtime/config/types/TimeOffsets.hpp
  ./include/ocppi/runtime/config/types/User.hpp
  ./include/ocppi/runtime/config/types/Vm.hpp
  ./include/ocppi/runtime/config/types/WindowsDevice.hpp
  ./include/ocppi/runtime/config/types/Windows.hpp
  ./include/ocppi/runtime/config/types/WindowsNetwork.hpp
  ./include/ocppi/runtime/config/types/WindowsResources.hpp
  ./include/ocppi/runtime/config/types/ZosDevice.hpp
  ./include/ocppi/runtime/config/types/Zos.hpp
  ./include/ocppi/runtime/config/WrongTypeError.hpp
  ./include/ocppi/runtime/ContainerID.hpp
  ./include/ocppi/runtime/CreateOption.hpp
  ./include/ocppi/runtime/DeleteOption.hpp
  ./include/ocppi/runtime/ExecOption.hpp
  ./include/ocppi/runtime/FeaturesOption.hpp
  ./include/ocppi/runtime/features/types/Apparmor.hpp
  ./include/ocppi/runtime/features/types/Cgroup.hpp
  ./include/ocppi/runtime/features/types/Features.hpp
  ./include/ocppi/runtime/features/types/Generators.hpp
  ./include/ocppi/runtime/features/types/helper.hpp
  ./include/ocppi/runtime/features/types/IntelRdt.hpp
  ./include/ocppi/runtime/features/types/Linux.hpp
  ./include/ocppi/runtime/features/types/NamespaceType.hpp
  ./include/ocppi/runtime/features/types/SeccompAction.hpp
  ./include/ocppi/runtime/features/types/SeccompArch.hpp
  ./include/ocppi/runtime/features/types/SeccompFlag.hpp
  ./include/ocppi/runtime/features/types/Seccomp.hpp
  ./include/ocppi/runtime/features/types/SeccompOperators.hpp
  ./include/ocppi/runtime/features/types/Selinux.hpp
  ./include/ocppi/runtime/GlobalOption.hpp
  ./include/ocppi/runtime/KillOption.hpp
  ./include/ocppi/runtime/ListOption.hpp
  ./include/ocppi/runtime/RunOption.hpp
  ./include/ocppi/runtime/Runtime.hpp
  ./include/ocppi/runtime/Signal.hpp
  ./include/ocppi/runtime/SpecRuntime.hpp
  ./include/ocppi/runtime/StartOption.hpp
  ./include/ocppi/runtime/StateOption.hpp
  ./include/ocppi/runtime/state/types/Generators.hpp
  ./include/ocppi/runtime/state/types/helper.hpp
  ./include/ocppi/runtime/state/types/State.hpp
  ./include/ocppi/runtime/state/types/Status.hpp
  ./include/ocppi/types/ContainerListItem.hpp
  ./include/ocppi/types/Generators.hpp
  ./include/ocppi/types/helper.hpp
  EXAMPLES
  parse-config
  using-crun
  use-default-logger
  LINK_LIBRARIES
  PUBLIC
  nlohmann_json::nlohmann_json
  tl::expected
  PRIVATE
  spdlog::spdlog
  semver::semver
  COMPILE_FEATURES
  PUBLIC
  cxx_std_17)
