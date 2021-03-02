# Copyright (C) 2021 Koki Fukuda

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https:#www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.15)
project(hashtable C)

if("${CMAKE_BUILD_TYPE}" MATCHES [Dd][Ee][Bb][Uu][Gg]
    AND NOT MSVC)
  add_link_options(-fsanitize=address,leak)
  add_compile_options(-fsanitize=address,leak)
endif()

add_library(hashtable SHARED hashtable.c)
target_compile_definitions(hashtable PRIVATE
  -DHASHTABLE_LIBRARY_BUILD=1)

option(BUILD_TEST "Build test executables" OFF)

if(BUILD_TEST)
  enable_testing()

  add_executable(hashtable_test hashtable_test.c)
  target_link_libraries(hashtable_test hashtable)

  add_test(NAME hashtable_test
    COMMAND hashtable_test)
endif()
