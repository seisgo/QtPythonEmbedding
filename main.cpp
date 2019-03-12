#include <QApplication>
#include "pyrun.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /** PART I *********************************************************/
    PyRun *pyRun = new PyRun();

    /** Test for running from string */
    qDebug("\nRun from string...");
    char* string = "from time import time, ctime\n"
                   "print('Today is', ctime(time()))\n";
    pyRun->runString(string);

    /** Test for running from python file, for '__main__' */
    qDebug("\nRun from file...");
    //Abosulte path is needed
    QString fName = "/home/yzy/myStudy/PythonTest/VideoSuperResolution/Train/run.py";
    pyRun->runFile(fName);

    /** Test for running from python file, and run certain function
     *  This implementation is similar with that calling pyRun->runModuleFunction(),
     *  the difference is that in this implementation, the whole python script
     *  firstly executes.
     */
//    qDebug("\nRun certain function from python file...");
//    pyRun->runFileFunction(fName, "test");

    /** Test for importing module, for certain function
     *  NOTE: path of imported module should set in inner function, which should
     *  be improved further.
     */
//    qDebug("\nRun certain function through module importing...");
//    pyRun->runModuleFunction("runtest", "main");
    /** End of PART I *********************************************************/

    /** PART III *********************************************************/
    /** Test for embedded interpreter
     *  NOTE: There may some problems with this implementation, to make the
     *  following construction success, "PyRun *pyRun = new PyRun();" should be
     *  firstly execuated. @20190226
     */
//    PyRun *pyRunMain = new PyRun(argc, argv);
//    //If calling following function, it fails...
//    pyRun->runEmbInterpreter(argc, argv);
    /** End of PART III *******************************************************/

    return a.exec();
}
