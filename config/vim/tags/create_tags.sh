#!/bin/bash

rm -f *tags

CTAGS='ctags'
${CTAGS} -f phptags ./php_funclist

CTAGS=${CTAGS}' --c++-kinds=+p --fields=+iaS --extra=+q+f --tag-relative=yes --language-force=C++'
${CTAGS} -f cpptags -R /usr/include/c++ -R ~/.vim/cpp_src

CTAGS2=${CTAGS}' -I __THROW -I __attribute_pure__ -I __nonnull -I __attribute__ -I __restrict=restrict -I  __const=const -I ((1, -I 3))'
${CTAGS2} -f ctags /usr/include/*.h
${CTAGS2} -f gnutags -R /usr/include/x86_64-linux-gnu
${CTAGS2} -f kerneltags -R /usr/include/linux
