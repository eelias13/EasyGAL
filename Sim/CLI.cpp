/*
 * CLI.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: elias
 */

#include "CLI.h"

CLI::CLI(Gal gal) { this->gal = gal; }

void CLI::run()
{
    while (true)
    {
        cout << "EasySim > ";

        cin >> next;

        if (next == "show")
        {
            show();
            continue;
        }

        if (next == "set")
        {
            set();
            continue;
        }

        if (next == "exit" || next == "quit" || next == "q" || next == "end")
        {
            cout << "ending simulation" << endl;
            return;
        }

        if (next == "help" || next == "h")
        {
            help();
            continue;
        }

        if (next == "add")
        {
            add();
            continue;
        }

        cerr << "this is not a valid command" << endl;
    }
}

void CLI::help()
{
    cout << "valid commands are: " << endl;

    cout << '\t' << "show table data" << endl;
    cout << '\t' << "show all output pins" << endl;
    cout << '\t' << "show all input pins" << endl;
    cout << '\t' << "show pin [pin]" << endl;

    cout << '\t' << "set pin [pin] [value]" << endl;
}

void CLI::add()
{
    cin >> next;
    if (next == "table")
    {
        cin >> next;
        if (next == "data")
        {
            return;
        }
        cerr << "this is not a valid command" << endl;
    }
    cerr << "this is not a valid command" << endl;
}

void CLI::set()
{
    cin >> next;
    if (next == "pin")
    {
        uint32_t pin;
        cin >> pin;
        if (!inOutput(pin))
        {
            cerr << "pin " << pin << " is not a output pin" << endl;
            return;
        }
        bool value;
        cin >> value;
        gal.setOutputPin(pin, value);
    }
}

void CLI::show()
{
    cin >> next;

    if (next == "all")
    {
        cin >> next;
        if (next == "output")
        {
            cin >> next;
            if (next == "pins")
            {
                for (uint32_t pin : gal.getOutputPins())
                    cout << pin << ":" << gal.getOutputPin(pin) << ", ";
                cout << endl;
                return;
            }
            cerr << "this is not a valid command" << endl;
        }
        if (next == "input")
        {
            cin >> next;
            if (next == "pins")
            {
                for (uint32_t pin : gal.getInputPins())
                    cout << pin << ":" << gal.getInputPin(pin) << ", ";
                cout << endl;
                return;
            }
            cerr << "this is not a valid command" << endl;
        }
    }

    if (next == "pin")
    {
        uint32_t pin;
        cin >> pin;
        if (inInput(pin))
        {
            cout << gal.getInputPin(pin) << endl;
            return;
        }

        if (inOutput(pin))
        {
            cout << gal.getOutputPin(pin) << endl;
            return;
        }

        cerr << "pin " << pin << " is not a valid pin" << endl;
        return;
    }

    if (next == "table")
    {
        cin >> next;
        if (next == "data")
        {
            for (TableData t : gal.getTabels())
            {
                printTableData(t);
                cout << endl;
            }
            return;
        }
        cerr << "this is not a valid command" << endl;
    }

    cerr << "this is not a valid command" << endl;
    return;
}

bool CLI::inOutput(uint32_t pin)
{
    for (uint32_t currentPin : gal.getOutputPins())
        if (currentPin == pin)
            return true;
    return false;
}

bool CLI::inInput(uint32_t pin)
{
    for (uint32_t currentPin : gal.getInputPins())
        if (currentPin == pin)
            return true;
    return false;
}

void CLI::printTableData(TableData tableData)
{
    cout << "output pin: " << tableData.m_OutputPin << endl;

    cout << "input pins:";
    for (uint32_t pin : tableData.m_InputPins)
        cout << " " << pin;
    cout << endl;

    cout << "table:\t    ";
    for (bool b : tableData.m_Table)
        cout << b;
    cout << endl;

    cout << "is dff:\t    " << tableData.m_EnableFlipFlop << endl;
}