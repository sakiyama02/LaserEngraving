# distutils: language = c++

cdef class PyRectangle:
    cdef LaserEngraving
    def run(self,bytes _filepath):
           return self.c_rect.Run(_filepath)
