#include "ToolsFControl.h"

ToolsFControl::ToolsFControl()
{

}

long ToolsFControl::ToolsFControlInit()
{
//    time(&actualTimeValue);
//    time(&lastTimeValue);
    return 0;
}

long ToolsFControl::SetSamplingTime(double new_dts)
{

    dts= long(new_dts*1000*1000*1000); //dts nanoseconds
    dtsWait = chrono::nanoseconds(dts);

    return 0;
}

double ToolsFControl::WaitSamplingTime()
{
    actualTimeValue = chrono::system_clock::now();

//    time(&actualTimeValue); // here time has been all way around.
//    cout <<std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch(lastTimeValue)).count() << endl;
    tWaited = actualTimeValue.time_since_epoch() - lastTimeValue.time_since_epoch();
//    tWaited = actualTimeValue-lastTimeValue;//chrono::nanoseconds( long(difftime(lastTimeValue,actualTimeValue)*1000*1000) );

    if(dtsWait > tWaited)
    {
        this_thread::sleep_for(dtsWait - tWaited);
    }
    else
    {
        cerr << "dtsWait Exceeded " << endl;
        cout << "dtsWait: " << dec <<dtsWait.count() << ", tWaited: " <<  tWaited.count() << endl;
        cout << "Total time: " << actualTimeValue.time_since_epoch().count() << endl;
    }


    lastTimeValue = chrono::system_clock::now();

    return (dtsWait - tWaited).count()/1000000;
}

TableInterpolation::TableInterpolation(string new_table)
{

    getData(new_table);
}


/*
* Parses through csv file line by line and returns the data
* in vector of vector of strings.
*/
long TableInterpolation::getData(string fileName)
{
    fstream file(fileName);
    string line = "";
    vector<double> dline;
    double value;

    lookupTable.resize(0);

    // Iterate through each line and split the content using delimeter
    while (getline(file, line))
    {
        istringstream ss(line);
        dline.resize(0);
        while (ss >> value)
        {
            dline.push_back(value);
        }
        lookupTable.push_back(dline);

    }
    // Close the File
    file.close();

    return 0;
}
