# distutils: language = c++

from Rectangle cimport LaserEngraving

cdef class PyRectangle:
    cdef LaserEngraving c_rect  # Hold a C++ instance which we're wrapping
    cdef char *filename
    def run(self):
        filename="./test.jpg"
        return self.c_rect.Run(filename)

