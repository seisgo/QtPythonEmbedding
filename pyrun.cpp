#include "pyrun.h"

#include <QDebug>
#include <QFile>

PyRun::PyRun()
{
    initPython();
}

PyRun::PyRun(const QString &exeFile)
{
    Py_SetProgramName((wchar_t*) exeFile.toStdWString().c_str());
    initPython();
}

PyRun::PyRun(int argc, char *argv[])
{
    Py_Initialize();
    Py_Main(argc, c2wc(argc, argv));
}

PyRun::~PyRun()
{
    Py_Finalize();
}

void PyRun::runString(const char *string)
{
    PyRun_SimpleString(string);
}

void PyRun::runFile(const QString &fileName)
{
    // Open the file
    char *fName = fileName.toUtf8().data();
    FILE* exp_file = fopen(fName, "r");

    // Execute the file
    PyRun_SimpleFile(exp_file, fName);
}

void PyRun::runFileFunction(const QString &fileName, const QString &funcName)
{
    //Open and execute file
    runFile(fileName);

    //Get a reference to the main module and global dictionary
    PyObject *mainModule = PyImport_AddModule("__main__");
    PyObject *globalDict = PyModule_GetDict(mainModule);

    //Extract a reference to input function from the global dictionary
    PyObject *poFunc = PyDict_GetItemString(globalDict, funcName.toUtf8().data());

    //Make a call to extracted function reference
    PyObject_CallObject(poFunc, NULL);
}

void PyRun::runModuleFunction(const QString &mName, const QString &fName)
{
    //Import module object
    PyObject *poModule = importModule(mName);

    //Run function object
    runFunction(poModule, fName);
}

void PyRun::runEmbInterpreter(int argc, char *argv[])
{
    Py_Main(argc, c2wc(argc, argv));
}

void PyRun::initPython()
{
    Py_NoSiteFlag = 1;
    Py_InitializeEx(0);

    qDebug() << "Python interpreter version:" << QString(Py_GetVersion());
    qDebug() << "Python standard library path:" << QString::fromWCharArray(Py_GetPath());

    /** Add non python standard library modules to search path, then numpy or
     *  other packages like tensorflow can be imported and called.
     *  Here I provide three methods.
     */
//    //Method 1, python code implementation
//    PyRun_SimpleString("import sys");
//    PyRun_SimpleString("sys.path.append('/usr/local/anaconda3/lib/python3.6/site-packages')");
//    PyRun_SimpleString("print('Python search path %s' % sys.path)");

    //Method 2: C code implementation, pay attention to called functions
    PyObject *sysPath = PySys_GetObject("path");
    QString mdlPath = "/usr/local/anaconda3/lib/python3.6/site-packages";
    PyList_Append(sysPath, PyUnicode_FromString(mdlPath.toUtf8().data()));
    qDebug() << "Python search path:" << PyUnicode_AsUTF8(PyObject_Str(sysPath));

    //Method 3: Set PYTHONPATH variable, PYTHONPATH should be set as:
    // '/usr/local/anaconda3/lib/python3.6/site-packages'
    /** End *******************************************************************/
}

PyObject *PyRun::importModule(const QString &moduleName)
{
    PyObject *poModule = NULL;

    // Depending absolute path is needed
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/yzy/Desktop/qtTest/qtPythonTest')");

    poModule = PyImport_ImportModule(moduleName.toUtf8().data());
    if(!poModule){
        qDebug()<<"Open python file failure!";
        return NULL;
    }

    //NOTE: The following operation doesn't influence the function performance
    if(!hasError()){
        // Get reference to main module
        PyObject *mainModule = PyImport_AddModule("__main__");
        PyModule_AddObject(mainModule, moduleName.toUtf8().data(), poModule);
    }

    return poModule;
}

void PyRun::runFunction(PyObject *obj, const QString &fName)
{
    PyObject *poFunc = PyObject_GetAttrString(obj, fName.toUtf8().data());
    if(!hasError()){
        PyObject_CallObject(poFunc, NULL);
    }
    Py_XDECREF(poFunc);
}

bool PyRun::hasError()
{
    bool error = false;

    if(PyErr_Occurred())
    {
        // Output error to stderr and clear error indicator
        PyErr_Print();
        error = true;
    }

    return error;
}

wchar_t **PyRun::c2wc(int argc, char **argv)
{
    //Initialize args
    wchar_t *args[8];   //'8' is set according to sizeof(argv[0]

    //Convert char** to wchar_t**
    for(int i=0; i<argc; ++i){
        mbstowcs(args[i], argv[i], sizeof(argv[i]));
    }

    return args;
}
