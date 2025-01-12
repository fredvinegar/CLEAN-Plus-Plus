#! /usr/bin/env python3

import os

from oclintscripts import environment
from oclintscripts import path

class builder:
    def __init__(self, source_path):
        self.__source_path = source_path
        self.__cmd = 'cmake'
        self.__cmd += ' -DCMAKE_BUILD_TYPE=Debug'
        if environment.is_mingw32():
            self.__cmd += ' -G "MSYS Makefiles"'


    def __wrap_double_quote(self, value):
        return '"' + value + '"'

    def str(self):
        cmd = self.__cmd + ' '
        if environment.is_mingw32():
            return cmd + self.__wrap_double_quote(self.__source_path)
        else:
            return cmd + self.__source_path

    def append(self, key, value, double_quote = False):
        self.__cmd += ' -D ' + key + '='
        if double_quote:
            self.__cmd += self.__wrap_double_quote(value)
        else:
            self.__cmd += value
        return self

    def release_build(self):
        return self.append('OCLINT_BUILD_TYPE', 'Release')

    def test_build(self):
        return self.append('TEST_BUILD', '1')

    def doc_gen_build(self):
        return self.append('DOC_GEN_BUILD', '1')

    def use_ninja(self):
        if not environment.is_mingw32():
            self.__cmd += ' -G Ninja'
        return self

    def append_dict(self, dict):
        for key, value in dict.items():
            self.append(key, value, environment.is_mingw32())
        return self
