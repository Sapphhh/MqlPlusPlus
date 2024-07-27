                       
 
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

### Metatrader5::InitPyEnv

Initializes the python environment. Must be called before any other function.
Errors are immediately printed to the console. **This behavior is subject to change in future versions.**

```cpp

using Mt5 = Metatrader5;

int main(int argc, char** argv)
{
    if(Mt5::InitPyEnv() == false)
    {
      return 0;
    }
}
```

### Metatrader5::Init

Estabilishes a connection with the open Metatrader5 terminal.
In case of an error, the function returns 'false' and the **last_error** variable is set. If this occurs, a description of the error can be retrieved using the function LastError.

```cpp

using Mt5 = Metatrader5;

int main(int argc, char** argv)
{
    // Python environment already initialized...
    if(Mt5::Init()==false)
    {
        MqlErrorInfo err;
        Mt5::LastError(err);

        std::cout << err.desc;
        std::cin.get();
        return 0;
    }  
}
```

### Metatrader5::Login

Sends a login request to the terminal.
In case of an error, the function returns 'false' and the **last_error** variable is set. If this occurs, a description of the error can be retrieved using the function LastError.

```cpp

using Mt5 = Metatrader5;

int main(int argc, char** argv)
{
    // Python environment already initialized...
    // Connection to the terminal already estabilished

    ulong login = 123456789;
    std::string pwd = "MyPwd";
    std::string sv_name = "MetaQuotes-Demo";
    
    if(Mt5::Login(login, pwd.c_str(), sv_name.c_str())==false)
    {
        std::cout << "Login failed.\n";
        
        MqlErrorInfo err;
        Mt5::LastError(err);

        std::cout << err.desc;

        std::cin.get();
        return 0;
    }  
}
```

### Metatrader5::LastError

Gets the last error.
If the program continues and the error was already handled, the user must call **Metatrader5::Release** on the MqlLastError object to clean it up.

```cpp

using Mt5 = Metatrader5;

int main(int argc, char** argv)
{
    // Python environment already initialized...
    // Connection to the terminal already estabilished
    
    if(Mt5::Login(login, pwd.c_str(), sv_name.c_str())==false)
    {
        std::cout << "Login failed.\n";
        
        MqlErrorInfo err;
        Mt5::LastError(err);

        std::cout << err.desc;
        Mt5::Release(err);
    }
    // do something after the error occurred, but does not end the program.
}
```

### Metatrader5::CopyRatesRange

Copies the rates (bars) of a certain symbol in the specified timeframe from the range "date_from" to "date_to" and saves it in the **MqlRatesContainer** variable. Notice the use of string as date in the format "DD.MM.YYYY" or "DD.MM.YYYY HH:MM:SS", followed by the user-defined literal '_dt' to convert it to a **datetime** type. 
Finally, the prints the **MqlRatesContainer** to the console.

The data is copied from the oldest bar (index 0) to the newest bar (index 'size-1').

After the container is not necessary anymore, call **Metatrader5::Release** to clean it up.
```cpp
using Mt5 = Metatrader5;

void PrintRates(std::string symbol)
{
    MqlRatesContainer rates;

    long total = Mt5::CopyRatesRange(symbol.c_str(), TIMEFRAME_H1, "26.07.2023"_dt, "27.07.2024"_dt, rates);

    for (long i = 0; i < total; ++i)
    {
        std::cout << rates[i] << '\n';
    }

    Metatrader5::Release(rates);
}
```

### Metatrader5::CopyTicksRange

Similar to Metatrader5::CopyRatesRange, but copies the ticks in the range 'date_from' to 'date_to'.

After the container is not necessary anymore, call **Metatrader5::Release** to clean it up.
```cpp
using Mt5 = Metatrader5;

void PrintTicks(std::string symbol)
{
    MqlTickContainer ticks;

    long total = Mt5::CopyTicksRange(symbol.c_str(), TIMEFRAME_H1, "26.07.2023"_dt, "27.07.2024"_dt, ticks);

    for (long i = 0; i < total; ++i)
    {
        std::cout << ticks[i] << '\n';
    }

    Metatrader5::Release(ticks);
}
```

### Metatrader5::SymbolInfoTick

Copies the last tick data received by the Metatrader5 terminal.
Returns false in case of an error, which is either directly printed to the console (in the case of a Python error) or stored in the last_error variable.

```cpp

using Mt5 = Metatrader5;

void PrintLastTick(std::string symbol)
{
    MqlTick tick;

    Mt5::SymbolInfoTick(symbol.c_str(), tick);

    std::cout << tick << "\n";
}
```

### Metatrader5::OrderSend

Sends an order request to the trade server. As a result, it returns a **MqlTradeResult** structure that contains the result of the trade order.
Returns false in case of a failure. Check the **MqlTradeResult::retcode** member for more details about the failure.

```cpp

using Mt5 = Metatrader5;

void Buy(std::string symbol)
{
    MqlTradeRequest req{};
    MqlTradeResult res{};

    req.action = TRADE_ACTION_DEAL;
    req.magic = 1337;
    req.symbol = symbol.data(); // safe to use like this, as the 'symbol' object is never deleted
    req.type = ORDER_TYPE_BUY;
    req.volume = 0.01;
    req.type_filling = ORDER_FILLING_IOC;

    Mt5::OrderSend(req, res);

    if(res.retcode == 10009)
    {
        std::cout << "Successful.\n";
    }
    else
    {
        std::cout << "Error: " << res.retcode << '\n';
    }
}
```

 
# License

[MIT license](./LICENSE)


