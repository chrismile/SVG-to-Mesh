#!/usr/bin/python
from SCons.Script import *
from SCons.Builder import Builder

def CreateCxxTest(env_test, target, source, env, includepaths=[], **kwargs):
	exec_tests = ARGUMENTS.get('exec_tests', False) # Set to false if standard is not to execute

	source_files = source
	test_header_file = target[0]
	test_name = os.path.splitext(os.path.basename(test_header_file))[0] + '_tester'
	env_test.Append(CPPPATH=includepaths)
	env_test.Append(CXXFLAGS=env['CXXFLAGS'])
	env_test.Append(CCFLAGS=env['CCFLAGS'])
	env_test.Append(CPPDEFINES=env['CPPDEFINES'])
	env_test.Append(LINKFLAGS=env['LINKFLAGS'])
	env_test.src_files = []
	for f in source_files:
		env_test.src_files.append(env.Object(f))
	env_test.CxxTest(test_name, [test_header_file] + env_test.src_files)
	
	print(Dir('.').srcnode().abspath)
	
	if exec_tests: 
		buildpath = 'build/build_svgtomesh/'
		test = Command(test_name + '_exec', None, action = buildpath + test_name)
		Execute(AlwaysBuild(test))

def generate(env, **kwargs):
	builder = Builder(action = CreateCxxTest)
	env.Append(BUILDERS = {'CreateCxxTest' : CreateCxxTest})
	return
	
def exists(env):
    return True
