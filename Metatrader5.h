#pragma once
#include <iostream>
#include <vector>
#include <inttypes.h>

#include "Python.h"
#include "numpy/arrayobject.h"

#pragma pack(8)

#define MtChar MtString::value_type
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

#define EXPORT_API __declspec(dllexport) 
#define METH_STATIC static
#define MEM_STATIC inline static

static inline std::pair<PyObject*, PyCFunctionWithKeywords> PY_FUNC_TABLE[64];

//class Metatrader5;

namespace MQL5
{
	class Metatrader5;

	/*Misc functions*/
	namespace Utils
	{
		/*Time related functions*/
		EXPORT_API std::string TimeToString(uint64_t time);
		EXPORT_API uint64_t CStrToDatetime(const char* chr);

		/*Python related functions*/
		PyObject* GetAttr(PyObject* mod, const std::string& fn_name);
		PyObject* GetNumPyArrItem(PyObject* nparr, int arr_size, int bytes_size, int index);

		/*Memory related functions*/
		void ZeroMemory(void* ptr, size_t size);
	};

	using uchar = uint8_t;
	using ulong = uint64_t;
	using uint = uint32_t;
	using datetime = uint64_t;

	struct MqlObject
	{
		PyObject* object = nullptr;
		ulong elem_count = 0;
	};

	enum ENUM_TIMEFRAMES
	{
		TIMEFRAME_M1 = 1,
		TIMEFRAME_M2,
		TIMEFRAME_M3,
		TIMEFRAME_M4,
		TIMEFRAME_M5,
		TIMEFRAME_M6,
		TIMEFRAME_M10 = 10,
		TIMEFRAME_M12 = 12,
		TIMEFRAME_M15 = 15,
		TIMEFRAME_M20 = 20,
		TIMEFRAME_M30 = 30,
		TIMEFRAME_H1 = 16385,
		TIMEFRAME_H2 = 16386,
		TIMEFRAME_H4 = 16388,
		TIMEFRAME_H6 = 16390,
		TIMEFRAME_H8 = 16392,
		TIMEFRAME_H12 = 16396,
		TIMEFRAME_D1 = 16408,
		TIMEFRAME_W1 = 32769,
		TIMEFRAME_MN1 = 49153
	};

	enum ENUM_ERROR_CODE
	{
		RES_E_EXTERNAL = 0x10000,
		RES_E_INTERNAL_FAIL_TIMEOUT = -10005,
		RES_E_INTERNAL_FAIL_CONNECT,
		RES_E_INTERNAL_FAIL_INIT,
		RES_E_INTERNAL_FAIL_RECEIVE,
		RES_E_INTERNAL_FAIL_SEND,
		RES_E_INTERNAL_FAIL,
		RES_E_AUTO_TRADING_DISABLED = -8,
		RES_E_UNSUPPORTED,
		RES_E_AUTH_FAILED,
		RES_E_INVALID_VERSION,
		RES_E_NOT_FOUND,
		RES_E_NO_MEMORY,
		RES_E_INVALID_PARAMS,
		RES_E_FAIL,
		RES_S_OK = 1,
	};

	enum ENUM_ACCOUNT_TRADE_MODE
	{
		ACCOUNT_TRADE_MODE_DEMO,
		ACCOUNT_TRADE_MODE_CONTEST,
		ACCOUNT_TRADE_MODE_REAL
	};

	enum ENUM_ACCOUNT_STOPOUT_MODE
	{
		ACCOUNT_STOPOUT_MODE_PERCENT,
		ACCOUNT_STOPOUT_MODE_MONEY
	};

	enum ENUM_ACCOUNT_MARGIN_MODE
	{
		ACCOUNT_MARGIN_MODE_RETAIL_NETTING,
		ACCOUNT_MARGIN_MODE_EXCHANGE,
		ACCOUNT_MARGIN_MODE_RETAIL_HEDGING
	};

	enum ENUM_SYMBOL_CHART_MODE
	{
		SYMBOL_CHART_MODE_BID,
		SYMBOL_CHART_MODE_LAST
	};

	enum ENUM_SYMBOL_CALC_MODE
	{
		SYMBOL_CALC_MODE_FOREX,
		SYMBOL_CALC_MODE_FOREX_NO_LEVERAGE,
		SYMBOL_CALC_MODE_FUTURES,
		SYMBOL_CALC_MODE_CFD,
		SYMBOL_CALC_MODE_CFDINDEX,
		SYMBOL_CALC_MODE_CFDLEVERAGE,
		SYMBOL_CALC_MODE_EXCH_STOCKS,
		SYMBOL_CALC_MODE_EXCH_FUTURES,
		SYMBOL_CALC_MODE_EXCH_FUTURES_FORTS,
		SYMBOL_CALC_MODE_EXCH_BONDS,
		SYMBOL_CALC_MODE_EXCH_STOCKS_MOEX,
		SYMBOL_CALC_MODE_EXCH_BONDS_MOEX,
		SYMBOL_CALC_MODE_SERV_COLLATERAL,
	};

	enum ENUM_SYMBOL_TRADE_MODE
	{
		SYMBOL_TRADE_MODE_DISABLED,
		SYMBOL_TRADE_MODE_LONGONLY,
		SYMBOL_TRADE_MODE_SHORTONLY,
		SYMBOL_TRADE_MODE_CLOSEONLY,
		SYMBOL_TRADE_MODE_FULL
	};

	enum ENUM_SYMBOL_TRADE_EXECUTION
	{
		SYMBOL_TRADE_EXECUTION_REQUEST,
		SYMBOL_TRADE_EXECUTION_INSTANT,
		SYMBOL_TRADE_EXECUTION_MARKET,
		SYMBOL_TRADE_EXECUTION_EXCHANGE
	};

	enum ENUM_SYMBOL_SWAP_MODE
	{
		SYMBOL_SWAP_MODE_DISABLED,
		SYMBOL_SWAP_MODE_POINTS,
		SYMBOL_SWAP_MODE_CURRENCY_SYMBOL,
		SYMBOL_SWAP_MODE_CURRENCY_MARGIN,
		SYMBOL_SWAP_MODE_CURRENCY_DEPOSIT,
		SYMBOL_SWAP_MODE_INTEREST_CURRENT,
		SYMBOL_SWAP_MODE_INTEREST_OPEN,
		SYMBOL_SWAP_MODE_REOPEN_CURRENT,
		SYMBOL_SWAP_MODE_REOPEN_BID
	};

	enum ENUM_DAY_OF_WEEK
	{
		SUNDAY,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY
	};

	enum
	{
		SYMBOL_EXPIRATION_GTC = 0x01,
		SYMBOL_EXPIRATION_DAY = 0x02,
		SYMBOL_EXPIRATION_SPECIFIED = 0x04,
		SYMBOL_EXPIRATION_SPECIFIED_DAY = 0x08
	};

	enum
	{
		SYMBOL_FILLING_FOK = 0x01,
		SYMBOL_FILLING_IOC = 0x02,
		SYMBOL_FILLING_BOC = 0x04,
		SYMBOL_FILLING_NOIDENTIFIER = 0x08,
	};

	enum
	{
		SYMBOL_ORDER_MARKET = 0x01,
		SYMBOL_ORDER_LIMIT = 0x02,
		SYMBOL_ORDER_STOP = 0x04,
		SYMBOL_ORDER_STOP_LIMIT = 0x08,
		SYMBOL_ORDER_SL = 0x10,
		SYMBOL_ORDER_TP = 0x20,
		SYMBOL_ORDER_CLOSEBY = 0x40,
	};

	enum ENUM_SYMBOL_ORDER_GTC_MODE
	{
		SYMBOL_ORDERS_GTC,
		SYMBOL_ORDERS_DAILY,
		SYMBOL_ORDERS_DAILY_EXCLUDING_STOPS
	};

	enum ENUM_SYMBOL_OPTION_MODE
	{
		SYMBOL_OPTION_MODE_EUROPEAN,
		SYMBOL_OPTION_MODE_AMERICAN
	};

	enum ENUM_SYMBOL_OPTION_RIGHT
	{
		SYMBOL_OPTION_RIGHT_CALL,
		SYMBOL_OPTION_RIGHT_PUT
	};

	enum
	{
		TICK_FLAG_BID = 0x02,
		TICK_FLAG_ASK = 0x04,
		TICK_FLAG_LAST = 0x08,
		TICK_FLAG_VOLUME = 0x10,
		TICK_FLAG_BUY = 0x20,
		TICK_FLAG_SELL = 0x40,

		COPY_TICKS_ALL = -1,
		COPY_TICKS_INFO = 1,
		COPY_TICKS_TRADE = 2,
	};

	enum ENUM_TRADE_REQUEST_ACTION
	{
		TRADE_ACTION_DEAL = 1,
		TRADE_ACTION_PENDING = 5,
		TRADE_ACTION_SLTP = 6,
		TRADE_ACTION_MODIFY = 7,
		TRADE_ACTION_REMOVE = 8,
		TRADE_ACTION_CLOSE_BY = 10
	};

	enum ENUM_ORDER_TYPE
	{
		ORDER_TYPE_BUY,
		ORDER_TYPE_SELL,
		ORDER_TYPE_BUY_LIMIT,
		ORDER_TYPE_SELL_LIMIT,
		ORDER_TYPE_BUY_STOP,
		ORDER_TYPE_SELL_STOP,
		ORDER_TYPE_BUY_STOP_LIMIT,
		ORDER_TYPE_SELL_STOP_LIMIT,
		ORDER_TYPE_CLOSE_BY
	};

	enum ENUM_ORDER_TYPE_FILLING
	{
		ORDER_FILLING_FOK,
		ORDER_FILLING_IOC,
		ORDER_FILLING_RETURN
	};

	enum ENUM_ORDER_TYPE_TIME
	{
		ORDER_TIME_GTC,
		ORDER_TIME_DAY,
		ORDER_TIME_SPECIFIED,
		ORDER_TIME_SPECIFIED_DAY
	};

	enum ENUM_ORDER_STATE
	{
		ORDER_STATE_STARTED,
		ORDER_STATE_PLACED,
		ORDER_STATE_CANCELED,
		ORDER_STATE_PARTIAL,
		ORDER_STATE_FILLED,
		ORDER_STATE_REJECTED,
		ORDER_STATE_EXPIRED,
		ORDER_STATE_REQUEST_ADD,
		ORDER_STATE_REQUEST_MODIFY,
		ORDER_STATE_REQUEST_CANCEL
	};

	enum ENUM_POSITION_TYPE
	{
		POSITION_TYPE_BUY,
		POSITION_TYPE_SELL,
	};

	enum ENUM_POSITION_REASON
	{
		POSITION_REASON_CLIENT,
		POSITION_REASON_MOBILE,
		POSITION_REASON_WEB,
		POSITION_REASON_EXPERT
	};

	enum ENUM_BOOK_TYPE
	{
		BOOK_TYPE_SELL = 1,
		BOOK_TYPE_BUY = 2,
		BOOK_TYPE_SELL_MARKET = 3,
		BOOK_TYPE_BUY_MARKET = 4
	};

	enum ENUM_ORDER_REASON
	{
		ORDER_REASON_CLIENT,
		ORDER_REASON_MOBILE,
		ORDER_REASON_WEB,
		ORDER_REASON_EXPERT,
		ORDER_REASON_SL,
		ORDER_REASON_TP,
		ORDER_REASON_SO,
	};

	enum ENUM_DEAL_TYPE
	{
		DEAL_TYPE_BUY,
		DEAL_TYPE_SELL,
		DEAL_TYPE_BALANCE,
		DEAL_TYPE_CREDIT,
		DEAL_TYPE_CHARGE,
		DEAL_TYPE_CORRECTION,
		DEAL_TYPE_BONUS,
		DEAL_TYPE_COMMISSION,
		DEAL_TYPE_COMMISSION_DAILY,
		DEAL_TYPE_COMMISSION_MONTHLY,
		DEAL_TYPE_COMMISSION_AGENT_DAILY,
		DEAL_TYPE_COMMISSION_AGENT_MONTHLY,
		DEAL_TYPE_INTEREST,
		DEAL_TYPE_BUY_CANCELED,
		DEAL_TYPE_SELL_CANCELED,
		DEAL_DIVIDEND,
		DEAL_DIVIDEND_FRANKED,
		DEAL_TAX
	};

	enum ENUM_DEAL_ENTRY
	{
		DEAL_ENTRY_IN,
		DEAL_ENTRY_OUT,
		DEAL_ENTRY_INOUT,
		DEAL_ENTRY_OUT_BY
	};

	enum ENUM_DEAL_REASON
	{
		DEAL_REASON_CLIENT,
		DEAL_REASON_MOBILE,
		DEAL_REASON_WEB,
		DEAL_REASON_EXPERT,
		DEAL_REASON_SL,
		DEAL_REASON_TP,
		DEAL_REASON_SO,
		DEAL_REASON_ROLLOVER,
		DEAL_REASON_VMARGIN,
		DEAL_REASON_SPLIT,
		DEAL_REASON_CORPORATE_ACTION
	};

	struct MqlVersionInfo
	{
		long long version;
		long long build;
		char* date;

		enum
		{
			INDEX_VERSION,
			INDEX_BUILD,
			INDEX_DATE
		};
	};

	struct MqlAccountInfo
	{
		ulong login;
		ENUM_ACCOUNT_TRADE_MODE trade_mode;
		long long leverage;
		int limit_orders;
		ENUM_ACCOUNT_STOPOUT_MODE margin_so_mode;
		bool trade_allowed;
		bool trade_expert;
		ENUM_ACCOUNT_MARGIN_MODE margin_mode;
		int currency_digits;
		bool fifo_close;
		double balance;
		double credit;
		double profit;
		double equity;
		double margin;
		double margin_free;
		double margin_level;
		double margin_so_call;
		double margin_so_so;
		double margin_initial;
		double margin_maintenance;
		double assets;
		double liabilities;
		double commission_blocked;
		char* name;
		char* server;
		char* currency;
		char* company;
	};

	struct MqlErrorInfo
	{

		friend class Metatrader5;

		ENUM_ERROR_CODE error;
		char* desc;

		friend std::ostream& operator<<(std::ostream& os, MqlErrorInfo& err)
		{
			return os << "[Code: " << err.error << ", Description: " << err.desc << "]";
		}

		enum
		{
			INDEX_ERROR,
			INDEX_DESC
		};
	};

	struct MqlSymbolInfo
	{
		bool custom;
		ENUM_SYMBOL_CHART_MODE chart_mode;
		bool select;
		bool visible;
		long long session_deals;
		long long session_buy_orders;
		long long session_sell_orders;
		long long volume;
		long long volumehigh;
		long long volumelow;
		long long time;
		int digits;
		int spread;
		bool spread_float;
		int ticks_bookdepth;
		ENUM_SYMBOL_CALC_MODE trade_calc_mode;
		ENUM_SYMBOL_TRADE_MODE trade_mode;
		datetime start_time;
		datetime expiration_time;
		int trade_stops_level;
		int trade_freeze_level;
		ENUM_SYMBOL_TRADE_EXECUTION trade_exemode;
		ENUM_SYMBOL_SWAP_MODE swap_mode;
		ENUM_DAY_OF_WEEK swap_rollover3days;
		bool margin_hedged_use_leg;
		int expiration_mode;
		int filling_mode;
		int order_mode;
		ENUM_SYMBOL_ORDER_GTC_MODE order_gtc_mode;
		ENUM_SYMBOL_OPTION_MODE option_mode;
		ENUM_SYMBOL_OPTION_RIGHT option_right;
		double bid;
		double bidhigh;
		double bidlow;
		double ask;
		double askhigh;
		double asklow;
		double last;
		double lasthigh;
		double lastlow;
		double volume_real;
		double volumehigh_real;
		double volumelow_real;
		double option_strike;
		double point;
		double trade_tick_value;
		double trade_tick_value_profit;
		double trade_tick_value_loss;
		double trade_tick_size;
		double trade_contract_size;
		double trade_accrued_interest;
		double trade_face_value;
		double trade_liquidity_rate;
		double volume_min;
		double volume_max;
		double volume_step;
		double volume_limit;
		double swap_long;
		double swap_short;
		double margin_initial;
		double margin_maintenance;
		double session_volume;
		double session_turnover;
		double session_interest;
		double session_buy_orders_volume;
		double session_sell_orders_volume;
		double session_open;
		double session_close;
		double session_aw;
		double session_price_settlement;
		double session_price_limit_min;
		double session_price_limit_max;
		double margin_hedged;
		double price_change;
		double price_volatility;
		double price_theoretical;
		double price_greeks_delta;
		double price_greeks_theta;
		double price_greeks_gamma;
		double price_greeks_vega;
		double price_greeks_rho;
		double price_greeks_omega;
		double price_sensitivity;
		char* basis;
		char* category;
		char* currency_base;
		char* currency_profit;
		char* currency_margin;
		char* bank;
		char* description;
		char* exchange;
		char* formula;
		char* isin;
		char* name;
		char* page;
		char* path;

		enum
		{
			INDEX_CUSTOM,
			INDEX_CHART_MODE,
			INDEX_SELECT,
			INDEX_VISIBLE,
			INDEX_SESSION_DEALS,
			INDEX_SESSION_BUY_ORDERS,
			INDEX_SESSION_SELL_ORDERS,
			INDEX_VOLUME,
			INDEX_VOLUMEHIGH,
			INDEX_VOLUMELOW,
			INDEX_TIME,
			INDEX_DIGITS,
			INDEX_SPREAD,
			INDEX_SPREAD_FLOAT,
			INDEX_TICKS_BOOKDEPTH,
			INDEX_TRADE_CALC_MODE,
			INDEX_TRADE_MODE,
			INDEX_START_TIME,
			INDEX_EXPIRATION_TIME,
			INDEX_TRADE_STOPS_LEVEL,
			INDEX_TRADE_FREEZE_LEVEL,
			INDEX_TRADE_EXEMODE,
			INDEX_SWAP_MODE,
			INDEX_SWAP_ROLLOVER3DAYS,
			INDEX_MARGIN_HEDGED_USE_LEG,
			INDEX_EXPIRATION_MODE,
			INDEX_FILLING_MODE,
			INDEX_ORDER_MODE,
			INDEX_ORDER_GTC_MODE,
			INDEX_OPTION_MODE,
			INDEX_OPTION_RIGHT,
			INDEX_BID,
			INDEX_BIDHIGH,
			INDEX_BIDLOW,
			INDEX_ASK,
			INDEX_ASKHIGH,
			INDEX_ASKLOW,
			INDEX_LAST,
			INDEX_LASTHIGH,
			INDEX_LASTLOW,
			INDEX_VOLUME_REAL,
			INDEX_VOLUMEHIGH_REAL,
			INDEX_VOLUMELOW_REAL,
			INDEX_OPTION_STRIKE,
			INDEX_POINT,
			INDEX_TRADE_TICK_VALUE,
			INDEX_TRADE_TICK_VALUE_PROFIT,
			INDEX_TRADE_TICK_VALUE_LOSS,
			INDEX_TRADE_TICK_SIZE,
			INDEX_TRADE_CONTRACT_SIZE,
			INDEX_ACCRUED_INTEREST,
			INDEX_FACE_VALUE,
			INDEX_LIQUIDITY_RATE,
			INDEX_VOLUME_MIN,
			INDEX_VOLUME_MAX,
			INDEX_VOLUME_STEP,
			INDEX_VOLUME_LIMIT,
			INDEX_SWAP_LONG,
			INDEX_SWAP_SHORT,
			INDEX_MARGIN_INITIAL,
			INDEX_MARGIN_MAINTENANCE,
			INDEX_SESSION_VOLUME,
			INDEX_SESSION_TURNOVER,
			INDEX_SESSION_INTEREST,
			INDEX_SESSION_BUY_ORDERS_VOLUME,
			INDEX_SESSION_SELL_ORDERS_VOLUME,
			INDEX_SESSION_OPEN,
			INDEX_SESSION_CLOSE,
			INDEX_SESSION_AW,
			INDEX_SESSION_PRICE_SETTLEMENT,
			INDEX_SESSION_PRICE_LIMIT_MIN,
			INDEX_SESSION_PRICE_LIMIT_MAX,
			INDEX_MARGIN_HEDGED,
			INDEX_PRICE_CHANGE,
			INDEX_PRICE_VOLATILITY,
			INDEX_PRICE_THEORETICAL,
			INDEX_PRICE_GREEKS_DELTA,
			INDEX_PRICE_GREEKS_THETA,
			INDEX_PRICE_GREEKS_GAMMA,
			INDEX_PRICE_GREEKS_VEGA,
			INDEX_PRICE_GREEKS_RHO,
			INDEX_PRICE_GREEKS_OMEGA,
			INDEX_PRICE_SENSITIVITY,
			INDEX_BASIS,
			INDEX_CATEGORY,
			INDEX_CURRENCY_BASE,
			INDEX_CURRENCY_PROFIT,
			INDEX_CURRENCY_MARGIN,
			INDEX_BANK,
			INDEX_DESCRIPTION,
			INDEX_EXCHANGE,
			INDEX_FORMULA,
			INDEX_ISIN,
			INDEX_NAME,
			INDEX_PAGE,
			INDEX_PATH,
		};
	};

	struct MqlSymbolInfoContainer
	{
		friend class Metatrader5;

		MqlSymbolInfo& operator[](long long idx)
		{
			if (idx < 0)
			{
				if (mql_object.elem_count + idx < 0)
				{
					throw std::out_of_range("Reversed index out of range.");
				}
				idx = mql_object.elem_count + idx;
			}
			else if (idx >= mql_object.elem_count)
			{
				throw std::out_of_range("Index out of range.");
			}

			return mql_symbols[idx];
		}

	protected:

		MqlSymbolInfo* mql_symbols = nullptr;
		MqlObject mql_object;
	};

	struct MqlTick
	{
	public:
		datetime     time;          // Time of the last prices update
		double       bid;           // Current Bid price
		double       ask;           // Current Ask price
		double       last;          // Price of the last deal (Last)
		ulong        volume;        // Volume for the current Last price
		long long    time_msc;      // Time of a price last update in milliseconds
		uint         flags;         // Tick flags
		double       volume_real;   // Volume for the current Last price with greater accuracy

	public:

		friend std::ostream& operator<<(std::ostream& os, const MqlTick& tick)
		{
			os << "[" << "Date: " << MQL5::Utils::TimeToString(tick.time) << ", bid: " << tick.bid << ", ask: " << tick.ask << ", last: " << tick.last << ", volume: " << tick.volume
				<< ", time_msc: " << tick.time_msc << ", flags: " << tick.flags << ", volume_real: " << tick.volume_real << ']';

			return os;
		}

		enum
		{
			INDEX_TIME,
			INDEX_BID,
			INDEX_ASK,
			INDEX_LAST,
			INDEX_VOLUME,
			INDEX_TIME_MSC,
			INDEX_FLAGS,
			INDEX_VOLUME_REAL
		};

	};

	struct MqlTickContainer
	{
		friend class Metatrader5;

		MqlTick& operator[](long long idx)
		{
			if (idx < 0)
			{
				if (mql_object.elem_count + idx < 0)
				{
					throw std::out_of_range("Reversed index out of range.");
				}
				idx = mql_object.elem_count + idx;
			}
			else if (idx >= mql_object.elem_count)
			{
				throw std::out_of_range("Index out of range.");
			}

			return mql_ticks[idx];
		}

		long Size()
		{
			return mql_object.elem_count;
		}

	protected:

		MqlTick* mql_ticks = nullptr;
		MqlObject mql_object;

	};

	struct MqlRates
	{
		datetime time;         // Period start time 
		double   open;         // Open price 
		double   high;         // The highest price of the period 
		double   low;          // The lowest price of the period 
		double   close;        // Close price 
		long long     tick_volume;  // Tick volume 
		int      spread;       // Spread 
		long long     real_volume;  // Trade volume 

		friend std::ostream& operator<<(std::ostream& os, const MqlRates& rates)
		{
			os << "[" << "Date: " << MQL5::Utils::TimeToString(rates.time) << ", open: " << rates.open << ", high: " << rates.high << ", low: " << rates.low << ", close: " << rates.close
				<< ", tick_volume: " << rates.tick_volume << ", spread: " << rates.spread << ", real_volume: " << rates.real_volume << ']';

			return os;
		}

		enum
		{
			INDEX_TIME,
			INDEX_OPEN,
			INDEX_HIGH,
			INDEX_LOW,
			INDEX_CLOSE,
			INDEX_TICK_VOLUME,
			INDEX_SPREAD,
			INDEX_REAL_VOLUME
		};
	};
	struct MqlRatesContainer
	{
		friend class Metatrader5;

		MqlRates& operator[](long long idx)
		{
			if (idx < 0)
			{
				if (mql_object.elem_count + idx < 0)
				{
					throw std::out_of_range("Reversed index out of range.");
				}

				idx = mql_object.elem_count + idx;
			}
			else if (idx >= mql_object.elem_count)
			{
				throw std::out_of_range("Index out of range.");
			}

			return mql_rates[idx];
		}

		long Size() const
		{
			return mql_object.elem_count;
		}

	protected:
		MqlRates* mql_rates = nullptr;
		MqlObject mql_object;
	};

	struct MqlTradeRequest
	{
		ENUM_TRADE_REQUEST_ACTION action;
		ulong magic;
		ulong order;
		char* symbol;
		double volume;
		double price;
		double stoplimit;
		double sl;
		double tp;
		ulong deviation;
		ENUM_ORDER_TYPE type;
		ENUM_ORDER_TYPE_FILLING type_filling;
		ENUM_ORDER_TYPE_TIME type_time;
		ulong expiration;
		char* comment;
		ulong position;
		ulong position_by;

		enum
		{
			INDEX_ACTION,
			INDEX_MAGIC,
			INDEX_ORDER,
			INDEX_SYMBOL,
			INDEX_VOLUME,
			INDEX_PRICE,
			INDEX_STOPLIMIT,
			INDEX_SL,
			INDEX_TP,
			INDEX_DEVIATION,
			INDEX_TYPE,
			INDEX_TYPE_FILLING,
			INDEX_TYPE_TIME,
			INDEX_EXPIRATION,
			INDEX_COMMENT,
			INDEX_POSITION,
			INDEX_POSITION_BY
		};
	};

	struct MqlTradeResult
	{
		uint     retcode;          // Operation return code
		ulong    deal;             // Deal ticket, if it is performed
		ulong    order;            // Order ticket, if it is placed
		double   volume;           // Deal volume, confirmed by broker
		double   price;            // Deal price, confirmed by broker
		double   bid;              // Current Bid price
		double   ask;              // Current Ask price
		char* comment;          // Broker comment to operation (by default it is filled by description of trade server return code)
		uint     request_id;       // Request ID set by the terminal during the dispatch 
		int      retcode_external; // Return code of an external trading system

		enum
		{
			INDEX_RETCODE,
			INDEX_DEAL,
			INDEX_ORDER,
			INDEX_VOLUME,
			INDEX_PRICE,
			INDEX_BID,
			INDEX_ASK,
			INDEX_COMMENT,
			INDEX_REQUEST_ID,
			INDEX_RETCODE_EXTERNAL
		};
	};

	struct MqlBookInfo
	{
		ENUM_BOOK_TYPE   type;            // Order type from ENUM_BOOK_TYPE enumeration
		double           price;           // Price
		long long             volume;          // Volume
		double           volume_real;     // Volume with greater accuracy

		enum
		{
			INDEX_TYPE,
			INDEX_PRICE,
			INDEX_VOLUME,
			INDEX_VOLUME_REAL
		};
	};

	struct MqlBookInfoContainer
	{
		friend class Metatrader5;

		MqlBookInfo& operator[](long idx)
		{
			if (idx < 0)
			{
				if (size + idx < 0)
				{
					throw std::out_of_range("Reversed index out of range.");
				}

				idx = size + idx;
			}
			else if (idx >= size)
			{
				throw std::out_of_range("Index out of range.");
			}

			return book_info[idx];
		}

		long Size() const
		{
			return size;
		}

	protected:

		MqlBookInfo* book_info;
		long size = 0;
	};

	struct MqlOrderInfo
	{
		ulong ticket;
		datetime time_setup;
		ulong time_setup_msc;
		datetime time_done;
		ulong time_done_msc;
		ulong time_expiration;
		ENUM_ORDER_TYPE type;
		ENUM_ORDER_TYPE_TIME type_time;
		ENUM_ORDER_TYPE_FILLING type_filling;
		ENUM_ORDER_STATE state;
		ulong magic;
		ulong position_id;
		ulong position_by_id;
		ENUM_ORDER_REASON reason;
		double volume_initial;
		double volume_current;
		double price_open;
		double sl;
		double tp;
		double price_current;
		double price_stoplimit;
		char* symbol;
		char* comment;
		char* external_id;

		friend std::ostream& operator<<(std::ostream& os, const MqlOrderInfo& order)
		{
			os << "[" << "Ticket: " << order.ticket << ", time_setup: " << MQL5::Utils::TimeToString(order.time_setup) << ", time_setup_msc: " << order.time_setup_msc
				<< ", time_done: " << MQL5::Utils::TimeToString(order.time_done) << ", time_done_msc: " << order.time_done_msc << ", time_expiration: " << order.time_expiration
				<< ", type: " << order.type << ", type_time: " << order.type_time << ", type_filling: " << order.type_filling << ", state: " << order.state << ", magic: " << order.magic
				<< ", position_id: " << order.position_id << ", position_by_id: " << order.position_by_id << ", reason: " << order.reason << ", volume_initial: " << order.volume_initial
				<< ", volume_current: " << order.volume_current << ", price_open: " << order.price_open << ", sl: " << order.sl << ", tp:" << order.tp << ", price_current: " << order.price_current
				<< ", price_stoplimit: " << order.price_stoplimit << ", symbol: " << order.symbol << ", comment: " << order.comment << ", external_id: " << order.external_id << ']';

			return os;
		}

		enum
		{
			INDEX_TICKET,
			INDEX_TIME_SETUP,
			INDEX_TIME_SETUP_MSC,
			INDEX_TIME_DONE,
			INDEX_TIME_DONE_MSC,
			INDEX_EXPIRATION,
			INDEX_TYPE,
			INDEX_TYPE_TIME,
			INDEX_TYPE_FILLING,
			INDEX_STATE,
			INDEX_MAGIC,
			INDEX_POSITION_ID,
			INDEX_POSITION_BY_ID,
			INDEX_REASON,
			INDEX_VOLUME_INITIAL,
			INDEX_VOLUME_CURRENT,
			INDEX_PRICE_OPEN,
			INDEX_SL,
			INDEX_TP,
			INDEX_PRICE_CURRENT,
			INDEX_PRICE_STOPLIMIT,
			INDEX_SYMBOL,
			INDEX_COMMENT,
			INDEX_EXTERNAL_ID
		};
	};
	struct MqlOrderInfoContainer
	{
		friend class Metatrader5;

		MqlOrderInfo& operator[](long idx)
		{
			if (idx < 0)
			{
				if (size + idx < 0)
				{
					throw std::out_of_range("Reversed index out of range.");
				}

				idx = size + idx;
			}
			else if (idx >= size)
			{
				throw std::out_of_range("Index out of range.");
			}

			return order_info[idx];
		}

		long Size() const
		{
			return size;
		}

	protected:
		MqlOrderInfo* order_info = nullptr;
		long size = 0;
	};

	struct MqlPositionInfo
	{
		ulong ticket;
		ulong time;
		ulong time_msc;
		ulong time_update;
		ulong time_update_msc;
		ENUM_POSITION_TYPE type;
		ulong magic;
		ulong identifier;
		ENUM_POSITION_REASON reason;
		double volume;
		double price_open;
		double sl;
		double tp;
		double price_current;
		double swap;
		double profit;
		char* symbol;
		char* comment;
		char* external_id;

		friend std::ostream& operator<<(std::ostream& os, const MqlPositionInfo& pos)
		{
			os << "[" << "Ticket: " << pos.ticket << ", time: " << MQL5::Utils::TimeToString(pos.time) << ", time_msc: " << pos.time_msc
				<< ", time_update: " << MQL5::Utils::TimeToString(pos.time_update) << ", time_update_msc: " << pos.time_update_msc << ", type: " << pos.type
				<< ", type: " << pos.type << ", magic: " << pos.magic << ", identifier: " << pos.identifier << ", reason: " << pos.reason << ", volume: " << pos.volume
				<< ", price_open: " << pos.price_open << ", sl: " << pos.sl << ", tp: " << pos.tp << ", price_current: " << pos.price_current
				<< ", swap: " << pos.swap << ", profit: " << pos.profit << ", symbol: " << pos.symbol << ", comment: " << pos.comment << ", external_id: " << pos.external_id << ']';

			return os;
		}

		enum
		{
			INDEX_TICKET,
			INDEX_TIME,
			INDEX_TIME_MSC,
			INDEX_TIME_UPDATE,
			INDEX_TIME_UPDATE_MSC,
			INDEX_TYPE,
			INDEX_MAGIC,
			INDEX_IDENTIFIER,
			INDEX_REASON,
			INDEX_VOLUME,
			INDEX_PRICE_OPEN,
			INDEX_SL,
			INDEX_TP,
			INDEX_PRICE_CURRENT,
			INDEX_SWAP,
			INDEX_PROFIT,
			INDEX_SYMBOL,
			INDEX_COMMENT,
			INDEX_EXTERNAL_ID
		};
	};
	struct MqlPositionInfoContainer
	{
		friend class Metatrader5;

		MqlPositionInfo& operator[](long idx)
		{
			if (idx < 0)
			{
				if (size + idx < 0)
				{
					throw std::out_of_range("Reversed index out of range.");
				}

				idx = size + idx;
			}
			else if (idx >= size)
			{
				throw std::out_of_range("Index out of range.");
			}

			return pos_info[idx];
		}

		long Size() const
		{
			return size;
		}

	protected:
		MqlPositionInfo* pos_info = nullptr;
		long size = 0;
	};

	struct MqlDealInfo
	{
		ulong ticket = 0;
		ulong order_ticket = 0;
		datetime time = 0;
		ulong time_msc = 0;
		ENUM_DEAL_TYPE type = DEAL_TYPE_BUY;
		ENUM_DEAL_ENTRY entry = DEAL_ENTRY_IN;
		ulong magic = 0;
		long position_id = 0;
		ENUM_DEAL_REASON reason = DEAL_REASON_CLIENT;
		double volume = 0;
		double price = 0;
		double commission = 0;
		double swap = 0;
		double profit = 0;
		double fee = 0;
		char* symbol = nullptr;
		char* comment = nullptr;
		char* external_id = nullptr;

		friend std::ostream& operator<<(std::ostream& os, MqlDealInfo& deal)
		{
			os << "[" << "Ticket: " << deal.ticket << ", order_ticket: " << deal.order_ticket << ", time: " << MQL5::Utils::TimeToString(deal.time) << ", time_msc: " << deal.time_msc
				<< ", type: " << deal.type << ", entry: " << deal.entry << ", magic: " << deal.magic << ", position_id: " << deal.position_id << ", reason: " << deal.reason
				<< ", position_id: " << deal.position_id << ", reason: " << deal.reason << ", volume: " << deal.volume << ", price: " 
				<< deal.price << ", commission: " << deal.commission << ", swap:" << deal.swap << ", profit: " << deal.profit
				<< ", fee: " << deal.fee << ", symbol: " << deal.symbol << ", comment: " << deal.comment << ", external_id: " << deal.external_id << ']';

			return os;
		
		}

		enum
		{
			INDEX_TICKET,
			INDEX_ORDER_TICKET,
			INDEX_TIME,
			INDEX_TIME_MSC,
			INDEX_TYPE,
			INDEX_ENTRY,
			INDEX_MAGIC,
			INDEX_POSITION_ID,
			INDEX_REASON,
			INDEX_VOLUME,
			INDEX_PRICE,
			INDEX_COMMISSION,
			INDEX_SWAP,
			INDEX_PROFIT,
			INDEX_FEE,
			INDEX_SYMBOL,
			INDEX_COMMENT,
			INDEX_EXTERNAL_ID
		};
	};
	struct MqlDealInfoContainer
	{
		friend class Metatrader5;

		MqlDealInfo& operator[](long idx)
		{
			if (idx < 0)
			{
				if (size + idx < 0)
				{
					throw std::out_of_range("Reversed index out of range.");
				}

				idx = size + idx;
			}
			else if (idx >= size)
			{
				throw std::out_of_range("Index out of range.");
			}

			return deal_info[idx];
		}

		long Size() const
		{
			return size;
		}

	protected:
		MqlDealInfo* deal_info = nullptr;
		long size = 0;
	};

	EXPORT_API class Metatrader5
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
		EXPORT_API  METH_STATIC long CopyRatesFrom(const char* symbol, ENUM_TIMEFRAMES timeframe, datetime date_from, ulong count, MqlObject& buffer);
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

			/*Sets the symbol*/
			void SetSymbol(std::string symbol);
			//void SetSymbol(const char*&& symbol);
			/*Sets the magic for the current trading strategy.*/
			void SetMagic(ulong magic);
			void SetFillingType(ENUM_ORDER_TYPE_FILLING type_filling);

			uint ResultRetCode();
			ulong ResultOrder();
			ulong ResultDeal();

		protected:

			std::string mComment;
			std::string mSymbol;

			MqlTradeRequest mRequest;
			MqlTradeResult mResult;

			void pZeroRequest();
			void pZeroResult();
		};

		

	private:

		MEM_STATIC PyObject* mt5_mod = nullptr;
		MEM_STATIC MqlErrorInfo last_error;
	};
}
