better_clocks_sources = [
  'main.c',
  'better-clocks-application.c',
  'better-clocks-window.c',
]

better_clocks_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
]

better_clocks_sources += gnome.compile_resources('better-clocks-resources',
  'better-clocks.gresource.xml',
  c_name: 'better_clocks'
)

executable('better-clocks', better_clocks_sources,
  dependencies: better_clocks_deps,
       install: true,
)
