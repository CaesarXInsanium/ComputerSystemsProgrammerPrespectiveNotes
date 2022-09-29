project(
  'useful',
  'c',
  version : '0.1',
  default_options: [
    'warning_level=3',
    'buildtype=debugoptimized',
    'debug=true',
    #'optimization=3',
    'c_std=gnu11'
  ]
)

SRC = [
  'lib/useful.c'
  ]

useful = library(
          'useful',
          SRC, 
           )
INC = include_directories('lib')

subdir('02ch')

