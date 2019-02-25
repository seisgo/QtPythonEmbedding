/**
  Description: Perform python embedding in C++ project, including five methods
  Date: 201902
  Author: Zhenyu Yuan
  Reference: Embedding Python in Your C Programs
             (https://www.linuxjournal.com/article/8497)
  */

#ifndef PYRUN_H
#define PYRUN_H

#include <Python.h>
#include <QString>

class PyRun
{
public:
    PyRun();
    //Used for statical compiling
    PyRun(const QString &exeFile);
    //For embedded interpreter
    PyRun(int argc, char *argv[]);
    ~PyRun();

    /**
     * @brief runString: Run simple python strings
     * @param string
     */
    void runString(const char* string);
    /**
     * @brief runFile:  Run python script
     * @param fileName: python file name, such as "test.py"
     */
    void runFile(const QString &fileName);
    void runFileFunction(const QString &fileName, const QString &funcName);
    /**
     * @brief runModuleFunction: Run certain function in python module
     * @param mName:    Module name
     * @param fName:    Function name
     */
    void runModuleFunction(const QString &mName, const QString &fName);
    /**
     * @brief runEmbInterpreter
     * @note: This didn't work, now replaced with PyRun(int argc, char* argv[])
     * @param argc
     * @param argv
     */
    void runEmbInterpreter(int argc, char* argv[]);

private:
    void initPython();
    PyObject *importModule(const QString &moduleName);
    void runFunction(PyObject *obj, const QString &fName);
    bool hasError();
    wchar_t **c2wc(int argc, char **argv);
};

#endif // PYRUN_H
