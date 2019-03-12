# QtPythonEmbedding
Simple demonstrations about Python embedding in C++ project, implemented with Qt

It includes five different implementations of embedding:
- Execuate simple string
- Execuate simple file
- Execuate certain function by set global path
- Execuate certain function by module importing
- Call embedded python interpreter

## Test of simple python script file
- The test python script file is *runtest.py*.
- This implementation is stored in master branch.

**NOTE**: For rerunning, abosulte path of python script file should be modified.

## Test of complex python project
- To run some complex python project, I have tested a python project for video and image super-resolution processing, which is named as *VideoSuperResolution*.
- I have made some modifications in main.cpp to execute main function in python project.
- For complex python project, directories of imported non-Python-standard-library modules and sefl-defined modules should be added into search path.
- What's more, if there is **relative directory** used in python project, we should make sure python script executing in its real path, not that of exectubale file in Qt project.

**NOTE**:
- The implementation of complex python project is just a demonstration, to show the process and some tips about this type of implementation.
- Since I have only uploaded main python script of *VideoSuperResolution* project, and it depends on more relative python scripts and configuration files, this implementation can't be rerun successfully.
- This implementation of running complex python project is forked in a branch repository, to avoid the rerunning failure.

