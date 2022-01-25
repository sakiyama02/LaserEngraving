cdef extern from "./src/LaserEngraving.cpp":
    pass

# Declare the class with cdef
cdef extern from "./include/LaserEngraving.hpp" :
    cdef cppclass LaserEngraving:
        LaserEngraving() 
        int Run(char*);
 
