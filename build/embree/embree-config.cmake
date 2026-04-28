## Copyright 2009-2021 Intel Corporation
## SPDX-License-Identifier: Apache-2.0

# use default install config
INCLUDE("${CMAKE_CURRENT_LIST_DIR}/embree-config-install.cmake")

# and override path variables to match for build directory
SET(EMBREE_INCLUDE_DIRS /home/lisa/Projects/GI/GI_Exersises/deps/embree/include)
SET(EMBREE_LIBRARY /home/lisa/Projects/GI/GI_Exersises/build/embree/libembree4.a)
SET(EMBREE_LIBRARIES ${EMBREE_LIBRARY})
