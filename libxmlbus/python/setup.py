from distutils.core import setup, Extension

setup(name = 'xmlbus',
      version = '1.0',
      ext_modules = [Extension('xmlbus', ['pyxmlbus.c'])])
