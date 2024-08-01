// SimplePy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Metatrader5/Metatrader5.h"
#include <thread>
#include <chrono>
#include <string_view>
#include <time.h>
#include "Timer/Timer.h"
#include "Timeit/Timeit.h"
#include "windows.h"

#include "BacktestApp.h"
#include "CMovingAverage.h"
#include "CStdDev.h"

using Mt5 = MQL5::Metatrader5;
using namespace MQL5;
using namespace std::chrono_literals;

ulong acc_rico = 3008292493;
std::string pw_rico = "N6gvM46@";
std::string sv_rico = "Rico-DEMO";

ulong acc_zero = 135015537;
std::string pw_zero = "Emanax11.";
std::string sv_zero = "ZeroMarkets-Demo-1";
std::string symbol = "WIN@N";

ulong acc = 123456789; // place your account number here
std::string pw = "Password"; // place your password here
std::string sv = "ServerName"; // place your server name here
std::string symbol = "Symbol"; // place the symbol to trade here.

#ifdef MQLPP_EXE
int main(int argc, char** argv)
{
    if (Mt5::InitPyEnv()==false)
    {
        std::cin.get();
        return 0;
    }
    
    if (Mt5::Init()==false)
    {
        MqlErrorInfo err;
        Mt5::GetLastError(err);

        std::cout << err.desc;
        std::cin.get();
        return 0;
    }

    if (Mt5::Login(acc_zero, pw_zero.c_str(), sv_zero.c_str(), 3000) == false)
    {
        std::cout << "Login failed.\n";
        
        MqlErrorInfo err;
        Mt5::GetLastError(err);

        std::cout << err.desc;

        std::cin.get();
        return 0;
    }

    std::string symbol = "EURUSD.r";
    MqlSymbolInfo symbol_info;
    Mt5::CTrade ctrade(symbol);

    Mt5::SymbolInfo(symbol.c_str(), symbol_info);

    while (true)
    {
        std::string cmd;
        std::getline(std::cin, cmd);

        double bid = Mt5::Bid(symbol.c_str());
        double ask = Mt5::Ask(symbol.c_str());

        if (cmd == "buy")
        {
            for (int i = 0; i < 6; ++i)
            {
                if (ctrade.BuyLimit(bid - (25000 + (25000 * symbol_info.trade_tick_size)), 0, 0, 0.01) == false)
                {
                    MqlErrorInfo err;
                    Mt5::GetLastError(err);
                    std::cout << err << '\n';
                }
                else
                {
                    std::cout << ctrade.Result() << "\n";
                }
            }
        }
        else if (cmd == "sell")
        {
            ctrade.SellLimit(ask + (5000 * symbol_info.trade_tick_size), 0, 0, 0.01);
        }
        else if (cmd == "break")
        {
            break;
        }
        else if (cmd == "cancel")
        {
            MqlTradeResult res{};

            Timeit timeit;
            
            timeit.Start();
            ctrade.CancelPendingOrders(res);
            timeit.End();

            std::cout << timeit << "ms\n";
        }
        else if (cmd == "orders")
        {
            ulong* orders=nullptr;
            long total = Mt5::OrdersGetTickets(symbol.c_str(), orders);

            std::cout << "[Orders tickets: ";
            for (long i = 0; i < total-1; ++i)
            {
                std::cout << orders[i] << ", ";
            }
            std::cout << orders[total - 1] << "]\n";
        }
        else if (cmd == "modify")
        {
            MqlPositionInfoContainer pos;
            long total = Mt5::PositionsGetBySymbol(symbol.c_str(), pos);

            if (total == -1)
            {
                MqlErrorInfo err;
                Mt5::GetLastError(err);

                std::cout << err << "\n";
                continue;
            }

            for (long i = 0; i < total; ++i)
            {
                if (pos[i].type == POSITION_TYPE_BUY)
                {
                    if (ctrade.ModifyPosition(pos[i].ticket, pos[i].price_open + (symbol_info.trade_tick_size * 1000), pos[i].price_open - (symbol_info.trade_tick_size * 1000)) == false)
                    {
                        MqlErrorInfo err;
                        Mt5::GetLastError(err);

                        std::cout << err << "\n";
                    }
                }
                else
                {
                    if (ctrade.ModifyPosition(pos[i].ticket, pos[i].price_open - (symbol_info.trade_tick_size * 1000), pos[i].price_open + (symbol_info.trade_tick_size * 1000)) == false)
                    {
                        MqlErrorInfo err;
                        Mt5::GetLastError(err);

                        std::cout << err << "\n";
                    }
                }
            }
        }
        else if (cmd == "close")
        {
            MqlPositionInfoContainer pos;
            long total = Mt5::PositionsGetBySymbol(symbol.c_str(), pos);

            if (total == -1)
            {
                MqlErrorInfo err;
                Mt5::GetLastError(err);

                std::cout << err << "\n";
                continue;
            }

            for (int i = 0; i < total; ++i)
            {
                ctrade.ClosePosition(pos[i].ticket, 0.01);
            }
        }
    }

    Mt5::Shutdown();

    std::cin.get();
    return 0;
}
#endif

#ifdef MQLPP_DLL

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

#endif
