from distutils.core import setup, Extension

zet_module = Extension('zet', 
        include_dirs = ['include', 'src/include', 'src/include/linux',
        'src/include/compat' ],
        libraries = ['zet'],
        # FIXME next should be ${exec_prefix}/lib, but configure replaces this
        # with the Makefile variable ${exec_prefix}.  The following
        # is a hack, which will not work if exec_prefix != prefix
        library_dirs = ['/usr/local/lib'],
        sources = ['src/pyzet/zetmodule.c'])

setup (name = 'PyZettair',
       version = '0.9.3',
       package_dir = { '': 'src/pyzet' },
       description = 'This is a python wrapper for libzet',
       py_modules = ["pzet"],
       ext_modules = [zet_module])
