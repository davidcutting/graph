project(
    'graph',
    'cpp',
    version : '0.0.1',
    license: 'MIT',
    default_options : [
        'cpp_std=c++20',
        'buildtype=debug',
        'warning_level=3'
    ]
)

project_description = 'A generic directed graph implementation.'

build_args = [
]

compiler = meson.get_compiler('cpp')
if compiler.get_id() == 'gcc'
    message('Compiler: GCC')
elif compiler.get_id() == 'clang'
    message('Compiler: LLVM/Clang')
endif

# --------------------------------------------------

# ======
# Target
# ======

include_dir = include_directories('include')

src = [
]

deps = [
]

build_args += [
    '-DPROJECT_NAME=' + meson.project_name(),
    '-DPROJECT_VERSION=' + meson.project_version()
]

shared_target = shared_library(
    meson.project_name(),
    dependencies: deps,
    include_directories : include_dir,
    sources : src,
    install : true,
    cpp_args : build_args
)

static_target = static_library(
    meson.project_name(),
    dependencies: deps,
    include_directories : include_dir,
    sources : src,
    install : true,
    cpp_args : build_args
)

install_subdir('include/graph', install_dir : 'include')

# --------------------------------------------------

# ======
# Project
# ======

pkg_mod = import('pkgconfig')
pkg_mod.generate(
    name : meson.project_name(),
    filebase : meson.project_name(),
    description : project_description,
    subdirs : meson.project_name(),
    libraries : [ shared_target, static_target ]
)

project_deps = declare_dependency(
    include_directories : include_dir,
    link_with : [ static_target ]
)

set_variable(meson.project_name() + '_dep', project_deps)

# --------------------------------------------------

# ======
# Tests
# ======

if not meson.is_subproject()
  add_languages('cpp')
  subdir('test')

  test('all_tests',
    executable(
      'graph_test',
      test_files,
      dependencies : [project_deps, test_dep],
      install : false
    )
  )
endif