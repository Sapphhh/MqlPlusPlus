                       
 
# MQL++

[![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/navendu-pottekkat/awesome-readme?include_prereleases)](https://img.shields.io/github/v/release/navendu-pottekkat/awesome-readme?include_prereleases)
[![GitHub last commit](https://img.shields.io/github/last-commit/navendu-pottekkat/awesome-readme)](https://img.shields.io/github/last-commit/navendu-pottekkat/awesome-readme)
[![GitHub issues](https://img.shields.io/github/issues-raw/navendu-pottekkat/awesome-readme)](https://img.shields.io/github/issues-raw/navendu-pottekkat/awesome-readme)
[![GitHub pull requests](https://img.shields.io/github/issues-pr/navendu-pottekkat/awesome-readme)](https://img.shields.io/github/issues-pr/navendu-pottekkat/awesome-readme)
[![GitHub](https://img.shields.io/github/license/navendu-pottekkat/awesome-readme)](https://img.shields.io/github/license/navendu-pottekkat/awesome-readme)

C++ has been my favorite language for a while now. Despite its popularity due to its speed and capabilities of memory management, MetaQuotes  has never released an official API so the users could work with it.

Well, if it was a problem for someone, it is no longer.

MQL++ allows the user fetch the data from the Metatrader5 terminal to work with it directly with it, aswell as to send orders to the trade server via C++ code.

In simple terms, the MQL++ library calls the functions exposed by the Python API provided by MetaQuotes, which are just a bunch of C functions under the hood.
 
# Quick Start Demo

To run the sample project, you must have installed Visual Studio 2022 or later (it's not guaranteed that the project will run on older versions of MSVC) and build the solution 'MQL++'.

The demo shows how to initialize the python and metatrader environments, aswell as how to fetch the rates of a certain timeframe in a 'date_from' to a 'date_to' date range, printing each bar data to the screen.

At the same time, it provides an example of how to send market orders to the trade server.
 
# Examples

Almost every function exposed by the [Python API provided by MetaQuotes](https://www.mql5.com/en/docs/python_metatrader5) can be called from MQL++ using the same arguments (in the future, the remaining functions will be added). Here are examples on how to call some available functions and how to use their data:

### Metatrader5::CopyRatesRange

Copies the rates (bars) of a certain symbol in the specified timeframe from the range "date_from" to "date_to" and saves it in the **MqlRatesContainer** variable. Notice the use of string as date in the format "DD.MM.YYYY" or "DD.MM.YYYY HH:MM:SS", followed by the user-defined literal '_dt' to convert it to a **datetime** type. 

```cpp
void PrintRates()
{
 MqlRatesContainer rates;

    long total = Mt5::CopyRatesRange(symbol.c_str(), TIMEFRAME_H1, "26.07.2023"_dt, "27.07.2024"_dt, rates);

    for (long i = 0; i < total; ++i)
    {
        std::cout << rates[i] << '\n';
    }
}
```

 
# License

[MIT license](./LICENSE)


