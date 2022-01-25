# distutils: language = c++
from Reactangle cimport LaserEngraving

cdef class PyRectangle:
    cdef LaserEngraving
    cdef char *filename
    def run(self,char _filepath):
        print(_filepath)
        filename="./test.jpg"
           return self.c_rect.Run(filename)