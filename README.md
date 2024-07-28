                       
 
# MQL++

C++ has been my favorite language for a while now. Despite its popularity due to its speed and capabilities of memory management, MetaQuotes  has never released an official API so the users could work with it.

Well, if it was a problem for someone, it is no longer.

MQL++ allows the user fetch the data from the MQL5::Metatrader5 terminal to work with it directly with it, aswell as to send orders to the trade server via C++ code.

In simple terms, the MQL++ library calls the functions exposed by the Python API provided by MetaQuotes, which are just a bunch of C functions under the hood.
 
# Quick Start

To use the library, all you need to do is copy the **Metatrader5** folder to your project/includes folder, include the **Metatrader5.h** and you're ready to go. 
 
# Examples

Almost every function exposed by the [Python API provided by MetaQuotes](https://www.mql5.com/en/docs/python_MQL5::Metatrader5) can be called from MQL++ using the same arguments (in the future, the remaining functions will be added). Here are examples on how to call some available functions and how to use their data:

### MQL5::Metatrader5::InitPyEnv

Initializes the python environment. Must be called before any other function.
Errors are immediately printed to the console. **This behavior is subject to change in future versions.**

```cpp

using namespace MQL5;
using Mt5 = MQL5::Metatrader5;

int main(int argc, char** argv)
{
    if(Mt5::InitPyEnv() == false)
    {
      return 0;
    }
}
```

### MQL5::Metatrader5::Init

Estabilishes a connection with the open MQL5::Metatrader5 terminal.
In case of an error, the function returns 'false' and the **last_error** variable is set. If this occurs, a description of the error can be retrieved using the function LastError.

```cpp

using namespace MQL5;
using Mt5 = MQL5::Metatrader5;

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

### MQL5::Metatrader5::Login

Sends a login request to the terminal.
In case of an error, the function returns 'false' and the **last_error** variable is set. If this occurs, a description of the error can be retrieved using the function LastError.

```cpp

using namespace MQL5;
using Mt5 = MQL5::Metatrader5;

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

### MQL5::Metatrader5::GetLastError

Gets the last error.
If the program continues and the error was already handled, the user must call **MQL5::Metatrader5::Release** on the MqlLastError object to clean it up.

```cpp

using namespace MQL5;
using Mt5 = MQL5::Metatrader5;

int main(int argc, char** argv)
{
    // Python environment already initialized...
    // Connection to the terminal already estabilished
    
    if(Mt5::Login(login, pwd.c_str(), sv_name.c_str())==false)
    {
        std::cout << "Login failed.\n";
        
        MqlErrorInfo err;
        Mt5::GetLastError(err);

        std::cout << err.desc;
        Mt5::Release(err);
    }
    // do something after the error occurred, but does not end the program.
}
```

### MQL5::Metatrader5::CopyRatesRange

Copies the rates (bars) of a certain symbol in the specified timeframe from the range "date_from" to "date_to" and saves it in the **MqlRatesContainer** variable. Notice the use of string as date in the format "DD.MM.YYYY" or "DD.MM.YYYY HH:MM:SS", followed by the user-defined literal '_dt' to convert it to a **datetime** type. 
Finally, the prints the **MqlRatesContainer** to the console.

The data is copied from the oldest bar (index 0) to the newest bar (index 'size-1').

After the container is not necessary anymore, call **MQL5::Metatrader5::Release** to clean it up.
```cpp
using namespace MQL5;
using Mt5 = MQL5::Metatrader5;

void PrintRates(std::string symbol)
{
    MqlRatesContainer rates;

    long total = Mt5::CopyRatesRange(symbol.c_str(), TIMEFRAME_H1, "26.07.2023"_dt, "27.07.2024"_dt, rates);

    for (long i = 0; i < total; ++i)
    {
        std::cout << rates[i] << '\n';
    }

    MQL5::Metatrader5::Release(rates);
}
```

### MQL5::Metatrader5::CopyTicksRange

Similar to MQL5::Metatrader5::CopyRatesRange, but copies the ticks in the range 'date_from' to 'date_to'.

After the container is not necessary anymore, call **MQL5::Metatrader5::Release** to clean it up.
```cpp
using namespace MQL5;
using Mt5 = MQL5::Metatrader5;

void PrintTicks(std::string symbol)
{
    MqlTickContainer ticks;

    long total = Mt5::CopyTicksRange(symbol.c_str(), TIMEFRAME_H1, "26.07.2023"_dt, "27.07.2024"_dt, ticks);

    for (long i = 0; i < total; ++i)
    {
        std::cout << ticks[i] << '\n';
    }

    MQL5::Metatrader5::Release(ticks);
}
```

### MQL5::Metatrader5::SymbolInfoTick

Copies the last tick data received by the MQL5::Metatrader5 terminal.
Returns false in case of an error, which is either directly printed to the console (in the case of a Python error) or stored in the last_error variable.

```cpp
using namespace MQL5;
using Mt5 = MQL5::Metatrader5;

void PrintLastTick(std::string symbol)
{
    MqlTick tick;

    Mt5::SymbolInfoTick(symbol.c_str(), tick);

    std::cout << tick << "\n";
}
```

### MQL5::Metatrader5::OrderSend

Sends an order request to the trade server. As a result, it returns a **MqlTradeResult** structure that contains the result of the trade order.

The **MqlTradeRequest** must be filled as the [documentation](https://www.mql5.com/en/docs/constants/structures/mqltraderequest) shows.

Returns false in case of a failure. Check the **MqlTradeResult::retcode** member for more details about the failure.

Whenever **MqlTradeRequest** and **MqlTradeResult** structures are not necessary anymore, you should call **MQL5::Metatrader5::Release** to clean them up.
The only exception is to calling **Release** on a **MqlTradeRequest** that has its **const char*** members (**symbol** and **comment**) set by a pointer that was not directly allocated by **new**. In this case, **Release** either should not be called on **MqlTradeRequest**, as in the example below, or should have its **const char*** members deallocated and set to nullptr beforehand.


```cpp
using namespace MQL5;
using Mt5 = MQL5::Metatrader5;

void Buy(std::string symbol)
{
    MqlTradeRequest req{};
    MqlTradeResult res{};

    req.action = TRADE_ACTION_DEAL;
    req.magic = 1337;
    req.symbol = symbol.data(); // safe to use like this, as the 'symbol' object is only deleted at the end of the scope
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

    //Mt5::Release(req); // in this case, the 'comment' member was not set, and 'symbol' was a pointer already managed by the std::string. Release should not be called.
    Mt5::Release(res);
}
```

### MQL5::Metatrader5::HistoryDealsGet
Gets all deals in a certain date range and returns it in a **MqlDealInfoContainer**.
The user can specify **0** for the **date_from** parameter and **MAX_DATETIME** for the **date_to** parameter to retrieve the entire deals list.

Returns -1 in case of an error.

```cpp
using namespace MQL5;
using Mt5 = MQL5::Metatrader5;

int main(int argc, char** argv[])
{
    // initialization functions...

    MqlDealInfoContainer deals;
    if (Mt5::HistoryDealsGet(0, MAX_DATETIME, deals) <= 0)
    {
        MqlErrorInfo err;
        Mt5::GetLastError(err);

        std::cout << err << '\n';

        return 0;
    }

    std::cout << deals[deals.Size()-1] << '\n';
}
```

### MQL5::Metatrader5::PositionsGet
Gets all open positions and stores the value in a **MqlPositionInfoContainer**.
Returns the number of open positions on success and -1 in case of an error.

```cpp
using namespace MQL5;
using Mt5 = MQL5::Metatrader5;

int main(int argc, char** argv[])
{
    // initialization functions...

    MqlPositionInfoContainer positions;
    if (Mt5::PositionsGet(positions) <= 0)
    {
        MqlErrorInfo err;
        Mt5::GetLastError(err);

        std::cout << err << '\n';

        return 0;
    }

    std::cout << positions[positions.Size()-1] << '\n';
}
```

### MQL5::Metatrader5::OrdersGet
Gets all open positions and stores the value in a **MqlOrderInfoContainer**.
Returns the number of open positions on success and -1 in case of an error.

```cpp
using namespace MQL5;
using Mt5 = MQL5::Metatrader5;

int main(int argc, char** argv[])
{
    // initialization functions...

    MqlOrderInfoContainer orders;
    if (Mt5::OrdersGet(orders) <= 0)
    {
        MqlErrorInfo err;
        Mt5::GetLastError(err);

        std::cout << err << '\n';

        return 0;
    }

    std::cout << orders[orders.Size()-1] << '\n';
}
```

### More to come

MQL5 is a rich and complete language to develop financial analysis and trading tools.
The goal of MQL++ is to come as close as possible to MQL5 in terms of how to interact with Metatrader5 terminal, aswell as to become a complete library to analyze data and develop trading strategies.

### Support this project

If you're willing to contribute to this project, please get in touch with me.
If you want to support its development, please check out my Expert Advisor [Emerald EA Builder](https://www.mql5.com/en/market/product/118373), available in the MetaQuotes market.
 
### License

[MIT license](./LICENSE)


