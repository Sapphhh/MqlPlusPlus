#pragma once

#include <iostream>
#include <vector>
#include <inttypes.h>

#include "Python.h"
#include "numpy/arrayobject.h"

#include "mql_types.h"

#pragma pack(1)

#define MINUTE 60
#define HOUR (MINUTE*60)
#define DAY (HOUR*24)
#define WEEK (DAY*7)

#define MAX_DATETIME INT_MAX
#define WHOLE_ARRAY LONG_MAX

#define PY_ASSERT_VALID(x) if(x.first==nullptr or x.second == nullptr) { PyErr_Print(); return false; }
#define PY_INIT_FUNC(fn,idx) PY_FUNC_TABLE[idx].first = MQL5::Utils::GetAttr(mt5_mod, fn); \
							PY_FUNC_TABLE[idx].second = (PyCFunctionWithKeywords)PyCFunction_GetFunction(PY_FUNC_TABLE[idx].first); \
							PY_ASSERT_VALID(PY_FUNC_TABLE[idx]);

#define DEL_STRING(x) if(x!=nullptr) { delete[] x; }
#define ZERO_MEM(x) MQL5::Utils::ZeroMemory(&x, sizeof(x))
#define METH_STATIC static
#define MEM_STATIC inline static

#define PyLong_AsInt(x) (int)PyLong_AsLong(x)
#define PyCpyStr(buf_to, size) buf_to = new char[size + 1]; \
								memcpy(buf_to, tmp_str, tmp_size); \
								buf_to[tmp_size] = 0;



static inline std::pair<PyObject*, PyCFunctionWithKeywords> PY_FUNC_TABLE[64];

static uint64_t operator"" _dt(const char* chr, std::size_t sz)
{
	std::string_view sv(chr);

	std::tm now{};

	if (sv.size() == 10)
	{
		sscanf_s(chr, "%d.%d.%d", &now.tm_mday, &now.tm_mon, &now.tm_year);
	}
	else if (sv.size() == 16)
	{
		sscanf_s(chr, "%d.%d.%d %d:%d", &now.tm_mday, &now.tm_mon, &now.tm_year, &now.tm_hour, &now.tm_min);
	}
	else if (sv.size() == 19)
	{
		sscanf_s(chr, "%d.%d.%d %d:%d:%d", &now.tm_mday, &now.tm_mon, &now.tm_year, &now.tm_hour, &now.tm_min, &now.tm_sec);
	}
	else
	{
		throw "Invalid datetime format.";
		return 0;
	}
	now.tm_year -= 1900;
	now.tm_mon -= 1;

	std::time_t now_time = std::mktime(&now);

	return (uint64_t)(now_time - mql_epoch_time);
}
static std::string operator"" _dt(uint64_t time)
{
	char buffer[64];

	std::time_t conv_time = time;

	std::tm conv{};
	gmtime_s(&conv, &conv_time);

	std::strftime(buffer, 64, "%d.%m.%Y %H:%M:%S", &conv);

	return std::string(buffer);
}

namespace MQL5
{ 
	/*Misc functions*/
	namespace Utils
	{
		EXPORT_API datetime GetCurrentTime();

		/*Python related functions*/
		PyObject* GetAttr(PyObject* mod, const std::string& fn_name);
		PyObject* GetNumPyArrItem(PyObject* nparr, int arr_size, int bytes_size, int index);

		/*Memory related functions*/
		void ZeroMemory(void* ptr, size_t size);

	};

	class Metatrader5
	{
	public:
		/*Imports the metatrader module.*/
		EXPORT_API METH_STATIC bool ImportModule();
		EXPORT_API METH_STATIC bool ImportFunctions();

		/*Lists the attributes of the python module.*/
		EXPORT_API METH_STATIC void ListAttr();

		/*Initializes the python environment.
		This function must be called before any other.*/
		EXPORT_API METH_STATIC bool InitPyEnv();

		/*Estabilishes a connection to the terminal.
		If there's no connection, all other functions have no effect.*/
		EXPORT_API METH_STATIC bool Init();
		bool Init(const char*& path);
		bool Init(const char* path, size_t login, const char* password, const char* server_name, size_t timeout = 15000, bool portable = false);

		/*Sends a login request to the terminal.
		If the terminal is not connected to any trading server,
		this function will likely fail.*/
		EXPORT_API METH_STATIC bool Login(size_t login, const char* password = nullptr, const char* server_name = nullptr, size_t timeout = 15000);

		/*Retrieves the current build, version and date*/
		EXPORT_API METH_STATIC bool VersionInfo(MqlVersionInfo& version);

		/*Retrieves account information*/
		EXPORT_API METH_STATIC bool AccountInfo(MqlAccountInfo& account_info);

		/*Gets the last error set after a function failure*/
		EXPORT_API METH_STATIC bool GetLastError(MqlErrorInfo& error_info);

		/*Symbols related functions*/
		/*Fetches the total available symbols provided by the current broker.*/
		EXPORT_API METH_STATIC long SymbolsTotal();
		/*Fetches all symbols that matches the 'group' parameter.*/
		EXPORT_API METH_STATIC long SymbolsGet(const char* group, MqlSymbolInfoContainer& symbols);
		/*Retrieves the data of the symbol and stores .*/
		EXPORT_API METH_STATIC bool SymbolInfo(const char* symbol, MqlSymbolInfo& symbol_info_obj);
		/*Retrieves the last tick data of the symbol.*/
		EXPORT_API METH_STATIC bool SymbolInfoTick(const char* symbol, MqlTick& tick);
		/*Selects the symbol into the MarketWatch.
		This is needed to allow trading operations on the symbol.*/
		EXPORT_API  METH_STATIC bool SymbolSelect(const char* symbol, bool enable = true);
		EXPORT_API  METH_STATIC double Bid(const char* symbol);
		EXPORT_API  METH_STATIC double Ask(const char* symbol);

		/*Rates related functions*/
		/*Copies the data of N bars, starting from the specified date.
		The data is copied from the oldest to the most recent bar.*/
		EXPORT_API  METH_STATIC long CopyRatesFrom(const char* symbol, ENUM_TIMEFRAMES timeframe, datetime date_from, ulong count, MqlRatesContainer& buffer);
		/*Copies the data of N bars, starting from the specified position.
		The data is copied from the oldest to the most recent bar.*/
		EXPORT_API  METH_STATIC long CopyRatesFromPos(const char* symbol, ENUM_TIMEFRAMES timeframe, int bar_from, ulong count, MqlRatesContainer& rates);
		/*Copies the data from the bar at 'date_from' up to the bar at 'date_to'.
		The data is copied from the oldest to the most recent bar.*/
		EXPORT_API  METH_STATIC long CopyRatesRange(const char* symbol, ENUM_TIMEFRAMES timeframe, datetime date_from, datetime date_to, MqlRatesContainer& rates);

		EXPORT_API  METH_STATIC long CopyTicksFrom(const char* symbol, datetime date_from, ulong count, long flags, MqlTickContainer& ticks);
		EXPORT_API  METH_STATIC long CopyTicksRange(const char* symbol, datetime date_from, datetime date_to, long flags, MqlTickContainer& ticks);

		/*Sends an order request to the trading server and gets its result.
		The terminal must have 'algo trading' enabled.*/
		EXPORT_API  METH_STATIC bool OrderSend(const MqlTradeRequest& request, MqlTradeResult& result);

		EXPORT_API  METH_STATIC bool MarketBookAdd(const char* symbol);
		EXPORT_API  METH_STATIC bool MarketBookGet(const char* symbol, MqlBookInfo*& book_info);
		EXPORT_API  METH_STATIC bool MarketBookRelease(const char* symbol);


		EXPORT_API  METH_STATIC long OrdersTotal();
		EXPORT_API  METH_STATIC long OrdersGet(MqlOrderInfoContainer& orders_info);
		EXPORT_API  METH_STATIC long OrdersGetBySymbol(const char* symbol, MqlOrderInfoContainer& orders_info);
		EXPORT_API  METH_STATIC long OrderGetByTicket(ulong ticket, MqlOrderInfo& orders_info);
		EXPORT_API  METH_STATIC long OrdersGetTickets(const char* symbol, ulong*& orders);
		EXPORT_API  METH_STATIC long OrdersGetTickets(ulong*& orders);



		EXPORT_API  METH_STATIC long PositionsTotal();
		EXPORT_API  METH_STATIC long PositionsGet(MqlPositionInfoContainer& positions_info);
		EXPORT_API  METH_STATIC long PositionsGetBySymbol(const char* symbol, MqlPositionInfoContainer& positions_info);
		EXPORT_API  METH_STATIC long PositionsGetByTicket(ulong ticket, MqlPositionInfo& position_info);

		EXPORT_API  METH_STATIC long HistoryOrdersTotal(datetime date_from, datetime date_to);
		EXPORT_API  METH_STATIC long HistoryOrdersGet(datetime date_from, datetime date_to, MqlOrderInfoContainer& orders_info);
		EXPORT_API  METH_STATIC long HistoryOrdersGetBySymbol(datetime date_from, datetime date_to, const char* symbol, MqlOrderInfoContainer& orders_info);
		EXPORT_API  METH_STATIC long HistoryOrdersGetByOrderTicket(datetime date_from, datetime date_to, ulong ticket, MqlOrderInfo& orders_info);
		EXPORT_API  METH_STATIC long HistoryOrdersGetByPositionTicket(datetime date_from, datetime date_to, ulong ticket, MqlOrderInfoContainer& orders_info);

		EXPORT_API  METH_STATIC long HistoryDealsTotal(datetime date_from, datetime date_to);
		EXPORT_API  METH_STATIC long HistoryDealsGet(datetime date_from, datetime date_to, MqlDealInfoContainer& deals_info);
		EXPORT_API  METH_STATIC long HistoryDealsGetBySymbol(datetime date_from, datetime date_to, const char* symbol, MqlDealInfoContainer& deals_info);
		EXPORT_API  METH_STATIC long HistoryDealsGetByOrderTicket(datetime date_from, datetime date_to, ulong ticket, MqlDealInfoContainer& deals_info);
		EXPORT_API  METH_STATIC long HistoryDealsGetByPositionTicket(datetime date_from, datetime date_to, ulong ticket, MqlDealInfoContainer& deals_info);

		EXPORT_API  METH_STATIC void Release(MqlObject& obj);
		EXPORT_API  METH_STATIC void Release(MqlErrorInfo& error_info);
		EXPORT_API  METH_STATIC void Release(MqlVersionInfo& version_info);
		EXPORT_API  METH_STATIC void Release(MqlAccountInfo& account_info);
		EXPORT_API  METH_STATIC void Release(MqlSymbolInfo& symbol_info);
		EXPORT_API  METH_STATIC void Release(MqlTick& tick);
		EXPORT_API  METH_STATIC void Release(MqlRates& rates);
		EXPORT_API  METH_STATIC void Release(MqlTradeRequest& request);
		EXPORT_API  METH_STATIC void Release(MqlTradeResult& result);
		EXPORT_API  METH_STATIC void Release(MqlBookInfo& book_info);
		EXPORT_API  METH_STATIC void Release(MqlOrderInfo& order_info);
		EXPORT_API  METH_STATIC void Release(MqlPositionInfo& position_info);
		EXPORT_API  METH_STATIC void Release(MqlTickContainer& ticks);
		EXPORT_API  METH_STATIC void Release(MqlRatesContainer& rates);

		/*Shutdown the connection to the terminal.*/
		EXPORT_API  METH_STATIC bool Shutdown();

		EXPORT_API  METH_STATIC void MemFree(void* ptr);

		/*Trading related functions*/
		class CTrade
		{
		public:
			CTrade();
			CTrade(std::string symbol);

			bool Buy(double tp, double sl, double volume, ulong deviation, const std::string& comment);
			bool Sell(double tp, double sl, double volume, ulong deviation, const std::string& comment);
			bool BuyLimit(double price, double tp, double sl, double volume, ulong deviation = 0, const std::string& comment = "");
			bool SellLimit(double price, double tp, double sl, double volume, ulong deviation = 0, const std::string& comment = "");
			bool BuyStop(double trigger_price, double tp, double sl, double volume, ulong deviation = 0, const std::string& comment = "");
			bool SellStop(double trigger_price, double tp, double sl, double volume, ulong deviation = 0, const std::string& comment = "");
			bool BuyStopLimit(double trigger_price, double limit_price, double tp, double sl, double volume, ulong deviation = 0, const std::string& comment = "");
			bool SellStopLimit(double trigger_price, double limit_price, double tp, double sl, double volume, ulong deviation = 0, const std::string& comment = "");

			bool CancelPendingOrders(MqlTradeResult& res);
			bool CancelPendingOrders(const char* symbol, MqlTradeResult& res);

			/*Modifies the position.
			The TP and SL must be valid prices of the symbol the position is.*/
			bool ModifyPosition(ulong position_ticket, double tp, double sl);

			/*Closes the position*/
			bool ClosePosition(ulong position_ticket, double volume=0);
			/*Closes all positions*/
			bool CloseAllPositions();
			/*Closes all positions of a symbol*/
			bool ClosePositionsBySymbol(const std::string& symbol);


			/*Sets the symbol*/
			void SetSymbol(std::string symbol);
			/*Gets the current selected symbol*/
			const std::string& GetSymbol();
			//void SetSymbol(const char*&& symbol);
			/*Sets the magic for the current trading strategy.*/
			void SetMagic(ulong magic);
			void SetTypeFilling(ENUM_ORDER_TYPE_FILLING type_filling);

			uint ResultRetCode();
			std::string ResultRetCodeAsStr();
			ulong ResultOrder();
			ulong ResultDeal();
			double ResultBid();
			double ResultAsk();
			double ResultVolume();
			double ResultPrice();
			std::string ResultComment();
			uint ResultRequestId();
			int ResultRetCodeExternal();
			const MqlTradeResult& Result();

		protected:

			std::string mComment;
			std::string mSymbol;

			MqlTradeRequest mRequest;
			MqlTradeResult mResult;

			void pZeroRequest();
			void pZeroResult();

			void pZeroResultComment();
		};

		

	private:

		MEM_STATIC PyObject* mt5_mod = nullptr;
		MEM_STATIC MqlErrorInfo last_error;

	};
}
