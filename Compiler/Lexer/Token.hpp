#pragma once
enum Token
{
    keywordPin,      //pin
    keywordTable,    //table
    num,             // 0-9
    var,             //
    equal,           // =
    end,             // ;
    parentheses,     // ()
    extraFunction,   // .fill(), count
    logicalOperator, // &|!?
    arrow,           // =>
    boolean,         // 0,1
    none             //
};