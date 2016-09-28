import os

if 'verbose' in ARGUMENTS:
  verbose = ARGUMENTS['verbose']
else:
  verbose = 1

if 'test' in ARGUMENTS:
  SConscript('test/SConscript', exports='verbose')
else:
  SConscript('dev/SConscript', exports='verbose')
env = Environment()
