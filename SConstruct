#!/usr/bin/python

import os

vars = Variables()

# Optionally read the build variables from a file
vars.AddVariables(PathVariable('buildVariablesFile', 'Path to a Python file containing the build variables', None, PathVariable.PathIsFile))
env = Environment(ENV=os.environ, variables=vars)
if 'buildVariablesFile' in env:
	vars = Variables(env['buildVariablesFile'])

# Application specific variables
vars.AddVariables(
	EnumVariable('compile_mode', 'Debug or release mode (standard: \'release\')', 'release', allowed_values=('debug', 'release')),
	BoolVariable('exec_tests', 'execute CxxTests on build automatically', False),
	PathVariable('lib_dir', 'Location of external libraries (optional)', None),
	PathVariable('include_dir', 'Location of external header files (optional)', None)
)

# set environment
env = Environment(ENV = {'PATH': os.environ['PATH']}, variables=vars)
env.Append(CXXFLAGS=['-std=c++11', '-Wall'])

# Custom library dir
if 'lib_dir' in env:
  env.Append(LIBPATH=[env['lib_dir']])

# Custom include dir
if 'include_dir' in env:
  env.Append(CPPPATH=[env['includeDir']])

# Add source directory to include path
includepaths = ['.']
env.Append(CPPPATH=includepaths)
Export('includepaths')

env.Append(LIBS=['png', 'tinyxml2', 'boost_system', 'boost_filesystem', 'boost_regex'])

# Compile mode: debug or build
if env['compile_mode'] == 'debug':
  env.Append(CPPDEFINES=['DEBUG'])
  env.Append(CCFLAGS=['-O0', '-g3', '-Wall'])
elif env['compile_mode'] == 'release':
  env.Append(CPPDEFINES=['NDEBUG'])
  env.Append(CCFLAGS=['-O3'])

# Output directory & program name
buildDir = '#build'
programName = 'svgtomesh'

# Get the source code files from the SConscript file in the src directory
Export('env')
env.src_files = []
SConscript(os.path.join('src', 'SConscript'),
    variant_dir=os.path.join(buildDir, 'build_'+programName),
    duplicate=0)

Import('env')

# Build the program
env.Program(os.path.join(buildDir, programName), env.src_files)
