project(
  'space_invaders_clone',
  'c',
  version: '0.1',
  default_options: ['warning_level=3'],
)

cc = meson.get_compiler('c')
math_dep = cc.find_library('m', required: false)

exe = executable(
  'space_invaders_clone',
  'space_invaders_clone.c',
  install: true,
  dependencies: [subproject('raylib').get_variable('raylib_dep'), math_dep],
)

test('basic', exe)
