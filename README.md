                       
 
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
 
# Usage
[(Back to top)](#table-of-contents)

```cpp
void Fn()
{
 int i = 0;
}
```

 
# License
[(Back to top)](#table-of-contents)

[MIT license](./LICENSE)


