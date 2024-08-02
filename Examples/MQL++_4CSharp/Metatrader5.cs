using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Runtime;
using System.Runtime.InteropServices;


namespace MQL
{
    using datetime = UInt64;

    unsafe public class MqlString
    {
        /*private sbyte* mStringBytes = null;
        private UInt64 mStringLen = 0;

        private MqlString()
        {

        }

        public MqlString(sbyte* chars)
        {
            mStringBytes = chars;
            mStringLen = pStrLen();
        }

        static public MqlString FromPtr(IntPtr ptr)
        {
            MqlString tmp_str = new MqlString();
            tmp_str.mStringBytes = (sbyte*)ptr;
            tmp_str.pStrLen();

            return tmp_str;
        }

        static public MqlString FromString(string str)
        {
            MqlString tmp_str = new MqlString();

            

            return tmp_str;
        }

        public sbyte this[UInt64 idx]
        {
            get
            {
                if (idx >= this.mStringLen)
                {
                    return -1;
                }

                return this.mStringBytes[idx];
            }
        }

        public override string ToString()
        {
            return new string(mStringBytes);
        }

        private UInt64 pStrLen()
        {
            UInt64 count = 0;
            for (int i = 0; ; i++)
            {
                sbyte b = *(mStringBytes + i);
                if (*(mStringBytes + i) == 0)
                {
                    return count;
                }

                ++count;
            }

            return 0;
        }*/

        static public string FromBytePtr(IntPtr ptr)
        {
            return new string((sbyte*)ptr);
        }

        static public string FromWCharPtr(IntPtr ptr)
        {
            return new string((char*)ptr);
        }

        static public sbyte* ToCStr(string str)
        {
            sbyte* ptr = (sbyte*)Marshal.AllocHGlobal(Marshal.SizeOf<sbyte>()*(str.Length + 1));

            for(int i = 0; i < str.Length; ++i)
                {
                ptr[i] = (sbyte)str[i];
                }

            ptr[str.Length] = 0;

            return ptr;
        }

        static public void Release(void* ptr)
        {
            Marshal.FreeHGlobal((IntPtr)ptr);
        }
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlObject
    {
        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr obj;

        [MarshalAs(UnmanagedType.I8)]
        public long size;
    };

    public enum ENUM_TIMEFRAMES
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

    public enum ENUM_ERROR_CODE
    {
        RES_E_INVALID_SYMBOL = 0x10000,
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

    public enum ENUM_ACCOUNT_TRADE_MODE
    {
        ACCOUNT_TRADE_MODE_DEMO,
        ACCOUNT_TRADE_MODE_CONTEST,
        ACCOUNT_TRADE_MODE_REAL
    };

    public enum ENUM_ACCOUNT_STOPOUT_MODE
    {
        ACCOUNT_STOPOUT_MODE_PERCENT,
        ACCOUNT_STOPOUT_MODE_MONEY
    };

    public enum ENUM_ACCOUNT_MARGIN_MODE
    {
        ACCOUNT_MARGIN_MODE_RETAIL_NETTING,
        ACCOUNT_MARGIN_MODE_EXCHANGE,
        ACCOUNT_MARGIN_MODE_RETAIL_HEDGING
    };

    public enum ENUM_SYMBOL_CHART_MODE
    {
        SYMBOL_CHART_MODE_BID,
        SYMBOL_CHART_MODE_LAST
    };

    public enum ENUM_SYMBOL_CALC_MODE
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

    public enum ENUM_SYMBOL_TRADE_MODE
    {
        SYMBOL_TRADE_MODE_DISABLED,
        SYMBOL_TRADE_MODE_LONGONLY,
        SYMBOL_TRADE_MODE_SHORTONLY,
        SYMBOL_TRADE_MODE_CLOSEONLY,
        SYMBOL_TRADE_MODE_FULL
    };

    public enum ENUM_SYMBOL_TRADE_EXECUTION
    {
        SYMBOL_TRADE_EXECUTION_REQUEST,
        SYMBOL_TRADE_EXECUTION_INSTANT,
        SYMBOL_TRADE_EXECUTION_MARKET,
        SYMBOL_TRADE_EXECUTION_EXCHANGE
    };

    public enum ENUM_SYMBOL_SWAP_MODE
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

    public enum ENUM_DAY_OF_WEEK
    {
        SUNDAY,
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY
    };

    public enum ENUM_SYMBOL_EXPIRATION

    {
        SYMBOL_EXPIRATION_GTC = 0x01,
        SYMBOL_EXPIRATION_DAY = 0x02,
        SYMBOL_EXPIRATION_SPECIFIED = 0x04,
        SYMBOL_EXPIRATION_SPECIFIED_DAY = 0x08
    };

    public enum ENUM_SYMBOL_FILLING

    {
        SYMBOL_FILLING_FOK = 0x01,
        SYMBOL_FILLING_IOC = 0x02,
        SYMBOL_FILLING_BOC = 0x04,
        SYMBOL_FILLING_NOIDENTIFIER = 0x08,
    };

    public enum ENUM_SYMBOL_ORDER

    {
        SYMBOL_ORDER_MARKET = 0x01,
        SYMBOL_ORDER_LIMIT = 0x02,
        SYMBOL_ORDER_STOP = 0x04,
        SYMBOL_ORDER_STOP_LIMIT = 0x08,
        SYMBOL_ORDER_SL = 0x10,
        SYMBOL_ORDER_TP = 0x20,
        SYMBOL_ORDER_CLOSEBY = 0x40,
    };

    public enum ENUM_SYMBOL_ORDER_GTC_MODE
    {
        SYMBOL_ORDERS_GTC,
        SYMBOL_ORDERS_DAILY,
        SYMBOL_ORDERS_DAILY_EXCLUDING_STOPS
    };

    public enum ENUM_SYMBOL_OPTION_MODE
    {
        SYMBOL_OPTION_MODE_EUROPEAN,
        SYMBOL_OPTION_MODE_AMERICAN
    };

    public enum ENUM_SYMBOL_OPTION_RIGHT
    {
        SYMBOL_OPTION_RIGHT_CALL,
        SYMBOL_OPTION_RIGHT_PUT
    };

    public enum ENUM_TICK_FLAG

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

    public enum ENUM_TRADE_REQUEST_ACTION
    {
        TRADE_ACTION_DEAL = 1,
        TRADE_ACTION_PENDING = 5,
        TRADE_ACTION_SLTP = 6,
        TRADE_ACTION_MODIFY = 7,
        TRADE_ACTION_REMOVE = 8,
        TRADE_ACTION_CLOSE_BY = 10
    };

    public enum ENUM_ORDER_TYPE
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

    public enum ENUM_ORDER_TYPE_FILLING
    {
        ORDER_FILLING_FOK,
        ORDER_FILLING_IOC,
        ORDER_FILLING_RETURN
    };

    public enum ENUM_ORDER_TYPE_TIME
    {
        ORDER_TIME_GTC,
        ORDER_TIME_DAY,
        ORDER_TIME_SPECIFIED,
        ORDER_TIME_SPECIFIED_DAY
    };

    public enum ENUM_ORDER_STATE
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

    public enum ENUM_POSITION_TYPE
    {
        POSITION_TYPE_BUY,
        POSITION_TYPE_SELL,
    };

    public enum ENUM_POSITION_REASON
    {
        POSITION_REASON_CLIENT,
        POSITION_REASON_MOBILE,
        POSITION_REASON_WEB,
        POSITION_REASON_EXPERT
    };

    public enum ENUM_BOOK_TYPE
    {
        BOOK_TYPE_SELL = 1,
        BOOK_TYPE_BUY = 2,
        BOOK_TYPE_SELL_MARKET = 3,
        BOOK_TYPE_BUY_MARKET = 4
    };

    public enum ENUM_ORDER_REASON
    {
        ORDER_REASON_CLIENT,
        ORDER_REASON_MOBILE,
        ORDER_REASON_WEB,
        ORDER_REASON_EXPERT,
        ORDER_REASON_SL,
        ORDER_REASON_TP,
        ORDER_REASON_SO,
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlVersionInfo
    {
        [MarshalAs(UnmanagedType.I8)]
        Int64 version;

        [MarshalAs(UnmanagedType.I8)]
        Int64 build;
        string date;

        public enum ENUM_INDEX

        {
            INDEX_VERSION,
            INDEX_BUILD,
            INDEX_DATE
        };
    };

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct MqlAccountInfo
    {
        [MarshalAs(UnmanagedType.U8)]
        public ulong login;

        [MarshalAs(UnmanagedType.I4)]
        public int trade_mode;

        [MarshalAs(UnmanagedType.I8)]
        public Int64 leverage;

        [MarshalAs(UnmanagedType.I4)]
        public int limit_orders;

        [MarshalAs(UnmanagedType.I4)]
        public int margin_so_mode;

        [MarshalAs(UnmanagedType.I1)]
        public bool trade_allowed;

        [MarshalAs(UnmanagedType.I1)]
        public bool trade_expert;

        [MarshalAs(UnmanagedType.I4)]
        public int margin_mode;

        [MarshalAs(UnmanagedType.I4)]
        public int currency_digits;

        [MarshalAs(UnmanagedType.I1)]
        public bool fifo_close;

        [MarshalAs(UnmanagedType.R8)]
        public double balance;

        [MarshalAs(UnmanagedType.R8)]
        public double credit;

        [MarshalAs(UnmanagedType.R8)]
        public double profit;

        [MarshalAs(UnmanagedType.R8)]
        public double equity;

        [MarshalAs(UnmanagedType.R8)]
        public double margin;

        [MarshalAs(UnmanagedType.R8)]
        public double margin_free;

        [MarshalAs(UnmanagedType.R8)]
        public double margin_level;

        [MarshalAs(UnmanagedType.R8)]
        public double margin_so_call;

        [MarshalAs(UnmanagedType.R8)]
        public double margin_so_so;

        [MarshalAs(UnmanagedType.R8)]
        public double margin_initial;

        [MarshalAs(UnmanagedType.R8)]
        public double margin_maintenance;

        [MarshalAs(UnmanagedType.R8)]
        public double assets;

        [MarshalAs(UnmanagedType.R8)]
        public double liabilities;

        [MarshalAs(UnmanagedType.R8)]
        public double commission_blocked;

        [MarshalAs(UnmanagedType.SysUInt)] // pointers are platform dependent, thus SysUInt
        public IntPtr name;

        [MarshalAs(UnmanagedType.SysUInt)] // pointers are platform dependent, thus SysUInt
        public IntPtr server;

        [MarshalAs(UnmanagedType.SysUInt)] // pointers are platform dependent, thus SysUInt
        public IntPtr currency;

        [MarshalAs(UnmanagedType.SysUInt)] // pointers are platform dependent, thus SysUInt
        public IntPtr company;

        public override string ToString()
        {
            return "[login: " + login + ", trade_mode: " + trade_mode + ", leverage: " + leverage + ", limit: " + limit_orders + ", margin_so_mode: " + margin_so_mode
                + ", trade_allowed: " + trade_allowed + ", trade_expert: " + trade_expert + ", margin_mode: " + margin_mode + ", currency_digits: " + currency_digits
                + ", fifo_close: " + fifo_close + ", balance: " + balance + ", credit: " + credit + ", profit: " + profit + ", equity: " + equity + ", margin: " + margin
                + ", margin_free: " + margin_free + ", margin_level: " + margin_level + ", margin_so_call: " + margin_so_call + ", margin_so_so: " + margin_so_so
                + ", margin_initial: " + margin_initial + ", margin_maintenance: " + margin_maintenance + ", assets: " + assets + ", liabilities: " + liabilities
                + ", comission_blocked: " + commission_blocked + ", + name: " + name + ", server: " + server + ", currency: " + currency + ", company: " + company + "]";
        }
    }
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlErrorInfo
    {
        [MarshalAs(UnmanagedType.I4)]
        ENUM_ERROR_CODE error;

        [MarshalAs(UnmanagedType.LPStr)]
        string desc;

        public enum ENUM_INDEX

        {
            INDEX_ERROR,
            INDEX_DESC
        };
    };

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    unsafe public struct MqlSymbolInfo
    {
        [MarshalAs(UnmanagedType.I1)]
        public bool custom;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_SYMBOL_CHART_MODE chart_mode;

        [MarshalAs(UnmanagedType.I1)]
        public bool select;

        [MarshalAs(UnmanagedType.I1)]
        public bool visible;

        [MarshalAs(UnmanagedType.I8)]
        public Int64 session_deals;

        [MarshalAs(UnmanagedType.I8)]
        public Int64 session_buy_orders;

        [MarshalAs(UnmanagedType.I8)]
        public Int64 session_sell_orders;

        [MarshalAs(UnmanagedType.I8)]
        public Int64 volume;

        [MarshalAs(UnmanagedType.I8)]
        public Int64 volumehigh;

        [MarshalAs(UnmanagedType.I8)]
        public Int64 volumelow;

        [MarshalAs(UnmanagedType.I8)]
        public Int64 time;

        [MarshalAs(UnmanagedType.I4)]
        public int digits;

        [MarshalAs(UnmanagedType.I4)]
        public int spread;

        [MarshalAs(UnmanagedType.I1)]
        public bool spread_float;

        [MarshalAs(UnmanagedType.I4)]
        public int ticks_bookdepth;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_SYMBOL_CALC_MODE trade_calc_mode;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_SYMBOL_TRADE_MODE trade_mode;

        [MarshalAs(UnmanagedType.U8)]
        public datetime start_time;

        [MarshalAs(UnmanagedType.U8)]
        public datetime expiration_time;

        [MarshalAs(UnmanagedType.I4)]
        public int trade_stops_level;

        [MarshalAs(UnmanagedType.I4)]
        public int trade_freeze_level;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_SYMBOL_TRADE_EXECUTION trade_exemode;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_SYMBOL_SWAP_MODE swap_mode;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_DAY_OF_WEEK swap_rollover3days;

        [MarshalAs(UnmanagedType.I1)]
        public bool margin_hedged_use_leg;

        [MarshalAs(UnmanagedType.I4)]
        public int expiration_mode;

        [MarshalAs(UnmanagedType.I4)]
        public int filling_mode;

        [MarshalAs(UnmanagedType.I4)]
        public int order_mode;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_SYMBOL_ORDER_GTC_MODE order_gtc_mode;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_SYMBOL_OPTION_MODE option_mode;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_SYMBOL_OPTION_RIGHT option_right;

        [MarshalAs(UnmanagedType.R8)]
        public double bid;

        [MarshalAs(UnmanagedType.R8)]
        public double bidhigh;

        [MarshalAs(UnmanagedType.R8)]
        public double bidlow;

        [MarshalAs(UnmanagedType.R8)]
        public double ask;

        [MarshalAs(UnmanagedType.R8)]
        public double askhigh;

        [MarshalAs(UnmanagedType.R8)]
        public double asklow;

        [MarshalAs(UnmanagedType.R8)]
        public double last;

        [MarshalAs(UnmanagedType.R8)]
        public double lasthigh;

        [MarshalAs(UnmanagedType.R8)]
        public double lastlow;

        [MarshalAs(UnmanagedType.R8)]
        public double volume_real;

        [MarshalAs(UnmanagedType.R8)]
        public double volumehigh_real;

        [MarshalAs(UnmanagedType.R8)]
        public double volumelow_real;

        [MarshalAs(UnmanagedType.R8)]
        public double option_strike;

        [MarshalAs(UnmanagedType.R8)]
        public double point;

        [MarshalAs(UnmanagedType.R8)]
        public double trade_tick_value;

        [MarshalAs(UnmanagedType.R8)]
        public double trade_tick_value_profit;

        [MarshalAs(UnmanagedType.R8)]
        public double trade_tick_value_loss;

        [MarshalAs(UnmanagedType.R8)]
        public double trade_tick_size;

        [MarshalAs(UnmanagedType.R8)]
        public double trade_contract_size;

        [MarshalAs(UnmanagedType.R8)]
        public double trade_accrued_interest;

        [MarshalAs(UnmanagedType.R8)]
        public double trade_face_value;

        [MarshalAs(UnmanagedType.R8)]
        public double trade_liquidity_rate;

        [MarshalAs(UnmanagedType.R8)]
        public double volume_min;

        [MarshalAs(UnmanagedType.R8)]
        public double volume_max;

        [MarshalAs(UnmanagedType.R8)]
        public double volume_step;

        [MarshalAs(UnmanagedType.R8)]
        public double volume_limit;

        [MarshalAs(UnmanagedType.R8)]
        public double swap_long;

        [MarshalAs(UnmanagedType.R8)]
        public double swap_short;

        [MarshalAs(UnmanagedType.R8)]
        public double margin_initial;

        [MarshalAs(UnmanagedType.R8)]
        public double margin_maintenance;

        [MarshalAs(UnmanagedType.R8)]
        public double session_volume;

        [MarshalAs(UnmanagedType.R8)]
        public double session_turnover;

        [MarshalAs(UnmanagedType.R8)]
        public double session_interest;

        [MarshalAs(UnmanagedType.R8)]
        public double session_buy_orders_volume;

        [MarshalAs(UnmanagedType.R8)]
        public double session_sell_orders_volume;

        [MarshalAs(UnmanagedType.R8)]
        public double session_open;

        [MarshalAs(UnmanagedType.R8)]
        public double session_close;

        [MarshalAs(UnmanagedType.R8)]
        public double session_aw;

        [MarshalAs(UnmanagedType.R8)]
        public double session_price_settlement;

        [MarshalAs(UnmanagedType.R8)]
        public double session_price_limit_min;

        [MarshalAs(UnmanagedType.R8)]
        public double session_price_limit_max;

        [MarshalAs(UnmanagedType.R8)]
        public double margin_hedged;

        [MarshalAs(UnmanagedType.R8)]
        public double price_change;

        [MarshalAs(UnmanagedType.R8)]
        public double price_volatility;

        [MarshalAs(UnmanagedType.R8)]
        public double price_theoretical;

        [MarshalAs(UnmanagedType.R8)]
        public double price_greeks_delta;

        [MarshalAs(UnmanagedType.R8)]
        public double price_greeks_theta;

        [MarshalAs(UnmanagedType.R8)]
        public double price_greeks_gamma;

        [MarshalAs(UnmanagedType.R8)]
        public double price_greeks_vega;

        [MarshalAs(UnmanagedType.R8)]
        public double price_greeks_rho;

        [MarshalAs(UnmanagedType.R8)]
        public double price_greeks_omega;

        [MarshalAs(UnmanagedType.R8)]
        public double price_sensitivity;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr basis;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr category;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr currency_base;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr currency_profit;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr currency_margin;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr bank;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr description;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr exchange;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr formula;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr isin;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr name;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr page;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr path;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    unsafe public struct MqlSymbolInfoContainer
    {
        public MqlSymbolInfo this[Int64 idx]
        {
            get => mql_symbols[idx];
        }

        private MqlSymbolInfo* mql_symbols;
        [MarshalAs(UnmanagedType.I8)] private Int64 elem_count;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlTick
    {
        [MarshalAs(UnmanagedType.U8)]
        public datetime time;          // Time of the last prices update

        [MarshalAs(UnmanagedType.R8)]
        public double bid;           // Current Bid price

        [MarshalAs(UnmanagedType.R8)]
        public double ask;           // Current Ask price

        [MarshalAs(UnmanagedType.R8)]
        public double last;          // Price of the last deal (Last)

        [MarshalAs(UnmanagedType.U8)]
        public ulong volume;        // Volume for the current Last price

        [MarshalAs(UnmanagedType.I8)]
        public Int64 time_msc;      // Time of a price last update in milliseconds

        [MarshalAs(UnmanagedType.U4)]
        public uint flags;         // Tick flags

        [MarshalAs(UnmanagedType.R8)]
        public double volume_real;   // Volume for the current Last price with greater accuracy

        public enum ENUM_INDEX

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

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlTickContainer
    {
        unsafe public MqlTick* mql_ticks;
        private MqlObject mql_object;

        unsafe public MqlTick this[Int64 idx]
        {
            get => mql_ticks[idx];
        }

        public long Size()
        {
            return mql_object.size;
        }

    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlRates
    {
        [MarshalAs(UnmanagedType.U8)]
        public datetime time;         // Period start time

        [MarshalAs(UnmanagedType.R8)]
        public double open;         // Open price 

        [MarshalAs(UnmanagedType.R8)]
        public double high;         // The highest price of the period 

        [MarshalAs(UnmanagedType.R8)]
        public double low;          // The lowest price of the period 

        [MarshalAs(UnmanagedType.R8)]
        public double close;        // Close price 

        [MarshalAs(UnmanagedType.I8)]
        public Int64 tick_volume;  // Tick volume 

        [MarshalAs(UnmanagedType.I4)]
        public int spread;       // Spread 

        [MarshalAs(UnmanagedType.I8)]
        public Int64 real_volume;  // Trade volume 

        public enum ENUM_INDEX

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

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public class MqlRatesContainer
    {
        unsafe public MqlRates* mql_rates;
        protected MqlObject mql_object;

        unsafe public MqlRates this[Int64 idx]
        {
            get => mql_rates[idx];
        }


    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlTradeRequest
    {
        [MarshalAs(UnmanagedType.I4)]
        public ENUM_TRADE_REQUEST_ACTION action;

        [MarshalAs(UnmanagedType.U8)]
        public ulong magic;

        [MarshalAs(UnmanagedType.U8)]
        public ulong order;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr symbol;

        [MarshalAs(UnmanagedType.R8)]
        public double volume;

        [MarshalAs(UnmanagedType.R8)]
        public double price;

        [MarshalAs(UnmanagedType.R8)]
        public double stoplimit;

        [MarshalAs(UnmanagedType.R8)]
        public double sl;

        [MarshalAs(UnmanagedType.R8)]
        public double tp;

        [MarshalAs(UnmanagedType.U8)]
        public ulong deviation;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_ORDER_TYPE type;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_ORDER_TYPE_FILLING type_filling;

        [MarshalAs(UnmanagedType.I4)]
        public ENUM_ORDER_TYPE_TIME type_time;

        [MarshalAs(UnmanagedType.U8)]
        public ulong expiration;

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr comment;

        [MarshalAs(UnmanagedType.U8)]
        public ulong position;

        [MarshalAs(UnmanagedType.U8)]
        public ulong position_by;

        public enum ENUM_INDEX

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

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlTradeResult
    {
        [MarshalAs(UnmanagedType.U4)]
        public uint retcode;          // Operation return code

        [MarshalAs(UnmanagedType.U8)]
        public ulong deal;             // Deal ticket, if it is performed

        [MarshalAs(UnmanagedType.U8)]
        public ulong order;            // Order ticket, if it is placed

        [MarshalAs(UnmanagedType.R8)]
        public double volume;           // Deal volume, confirmed by broker

        [MarshalAs(UnmanagedType.R8)]
        public double price;            // Deal price, confirmed by broker

        [MarshalAs(UnmanagedType.R8)]
        public double bid;              // Current Bid price

        [MarshalAs(UnmanagedType.R8)]
        public double ask;              // Current Ask price

        [MarshalAs(UnmanagedType.SysUInt)]
        public IntPtr comment;          // Broker comment to operation (by default it is filled by description of trade server return code)

        [MarshalAs(UnmanagedType.U4)]
        public uint request_id;       // Request ID set by the terminal during the dispatch 

        [MarshalAs(UnmanagedType.I4)]
        public int retcode_external; // Return code of an external trading system



        public enum ENUM_INDEX

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

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    struct MqlBookInfo
    {
        [MarshalAs(UnmanagedType.I4)]
        ENUM_BOOK_TYPE type;            // Order type from ENUM_BOOK_TYPE enumeration

        [MarshalAs(UnmanagedType.R8)]
        double price;           // Price

        [MarshalAs(UnmanagedType.I8)]
        Int64 volume;          // Volume

        [MarshalAs(UnmanagedType.R8)]
        double volume_real;     // Volume with greater accuracy

        public enum ENUM_INDEX

        {
            INDEX_TYPE,
            INDEX_PRICE,
            INDEX_VOLUME,
            INDEX_VOLUME_REAL
        };
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    struct MqlOrderInfo
    {
        [MarshalAs(UnmanagedType.U8)]
        ulong ticket;

        [MarshalAs(UnmanagedType.U8)]
        ulong time_setup;

        [MarshalAs(UnmanagedType.U8)]
        ulong time_setup_msc;

        [MarshalAs(UnmanagedType.U8)]
        ulong time_done;

        [MarshalAs(UnmanagedType.U8)]
        ulong time_done_msc;

        [MarshalAs(UnmanagedType.U8)]
        ulong time_expiration;

        [MarshalAs(UnmanagedType.I4)]
        ENUM_ORDER_TYPE type;

        [MarshalAs(UnmanagedType.I4)]
        ENUM_ORDER_TYPE_TIME type_time;

        [MarshalAs(UnmanagedType.I4)]
        ENUM_ORDER_TYPE_FILLING type_filling;

        [MarshalAs(UnmanagedType.I4)]
        ENUM_ORDER_STATE state;

        [MarshalAs(UnmanagedType.U8)]
        ulong magic;

        [MarshalAs(UnmanagedType.U8)]
        ulong position_id;

        [MarshalAs(UnmanagedType.U8)]
        ulong position_by_id;

        [MarshalAs(UnmanagedType.I4)]
        ENUM_ORDER_REASON reason;

        [MarshalAs(UnmanagedType.R8)]
        double volume_initial;

        [MarshalAs(UnmanagedType.R8)]
        double volume_current;

        [MarshalAs(UnmanagedType.R8)]
        double price_open;

        [MarshalAs(UnmanagedType.R8)]
        double sl;

        [MarshalAs(UnmanagedType.R8)]
        double tp;

        [MarshalAs(UnmanagedType.R8)]
        double price_current;

        [MarshalAs(UnmanagedType.R8)]
        double price_stoplimit;

        [MarshalAs(UnmanagedType.LPStr)]
        string symbol;

        [MarshalAs(UnmanagedType.LPStr)]
        string comment;

        [MarshalAs(UnmanagedType.LPStr)]
        string external_id;


        public enum ENUM_INDEX
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

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    struct MqlPositionInfo
    {
        [MarshalAs(UnmanagedType.U8)]
        ulong ticket;

        [MarshalAs(UnmanagedType.U8)]
        ulong time;

        [MarshalAs(UnmanagedType.U8)]
        ulong time_msc;

        [MarshalAs(UnmanagedType.U8)]
        ulong time_update;

        [MarshalAs(UnmanagedType.U8)]
        ulong time_update_msc;

        [MarshalAs(UnmanagedType.I4)]
        ENUM_POSITION_TYPE type;

        [MarshalAs(UnmanagedType.U8)]
        ulong magic;

        [MarshalAs(UnmanagedType.U8)]
        ulong identifier;

        [MarshalAs(UnmanagedType.I4)]
        ENUM_POSITION_REASON reason;

        [MarshalAs(UnmanagedType.R8)]
        double volume;

        [MarshalAs(UnmanagedType.R8)]
        double price_open;

        [MarshalAs(UnmanagedType.R8)]
        double sl;

        [MarshalAs(UnmanagedType.R8)]
        double tp;

        [MarshalAs(UnmanagedType.R8)]
        double price_current;

        [MarshalAs(UnmanagedType.R8)]
        double swap;

        [MarshalAs(UnmanagedType.R8)]
        double profit;

        [MarshalAs(UnmanagedType.LPStr)]
        string symbol;

        [MarshalAs(UnmanagedType.LPStr)]
        string comment;

        [MarshalAs(UnmanagedType.LPStr)]
        string external_id;



        public enum ENUM_INDEX
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
        }
    };

    public partial class Methods
    {
        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?InitPyEnv@Metatrader5@MQL5@@SA_NXZ")]
        public static extern bool InitPyEnv();

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?Init@Metatrader5@MQL5@@SA_NXZ")]
        public static extern bool Init();

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", CharSet = CharSet.Ansi, EntryPoint = "?Login@Metatrader5@MQL5@@SA_N_KPEBD10@Z")]
        public static extern bool Login(UInt64 login, string password, string server_name, UInt64 timeout = 5000, bool portable = false);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", CallingConvention = CallingConvention.Cdecl, EntryPoint = "?AccountInfo@Metatrader5@MQL5@@SA_NAEAUMqlAccountInfo@2@@Z")]
        unsafe public static extern bool AccountInfo(ref MqlAccountInfo acc_info);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?SymbolsTotal@Metatrader5@MQL5@@SAJXZ")]
        public static extern long SymbolsTotal();

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?SymbolInfo@Metatrader5@MQL5@@SA_NPEBDAEAUMqlSymbolInfo@2@@Z")]
        public static extern bool SymbolInfo(string symbol, ref MqlSymbolInfo symbol_info);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?SymbolInfoTick@Metatrader5@MQL5@@SA_NPEBDAEAUMqlTick@2@@Z")]
        public static extern bool SymbolInfoTick(string symbol, ref MqlTick symbol_info);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", CharSet = CharSet.Ansi, EntryPoint = "?SymbolsGet@Metatrader5@MQL5@@SAJPEBDAEAUMqlSymbolInfoContainer@2@@Z")]
        public static extern long SymbolsGet(string symbols, ref MqlSymbolInfoContainer symbol_info);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?CopyTicksFrom@Metatrader5@MQL5@@SAJPEBD_K1JAEAUMqlTickContainer@2@@Z")]
        public static extern long CopyTicksFrom(string symbol, ulong date_from, ulong count, ENUM_TICK_FLAG flags, ref MqlTickContainer buffer);
        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?CopyTicksRange@Metatrader5@MQL5@@SAJPEBD_K1JAEAUMqlTickContainer@2@@Z")]
        public static extern long CopyTicksRange(string symbol, ulong date_from, ulong date_to, ENUM_TICK_FLAG flags, ref MqlTickContainer buffer);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?CopyRatesFrom@Metatrader5@MQL5@@SAJPEBDW4ENUM_TIMEFRAMES@2@_K2AEAUMqlRatesContainer@2@@Z")]
        public static extern long CopyRatesFrom(string symbol, ENUM_TIMEFRAMES timeframe, UInt64 date_from, ulong count, ref MqlRatesContainer buffer);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release-DLL@Metatrader5@MQL5@@SAXAEAUMqlErrorInfo@2@@Z")]
        public static extern void Release(ref MqlErrorInfo error_info);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release-DLL@Metatrader5@MQL5@@SAXAEAUMqlVersionInfo@2@@Z")]
        public static extern void Release(ref MqlVersionInfo version_info);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release-DLL@Metatrader5@MQL5@@SAXAEAUMqlAccountInfo@2@@Z")]
        public static extern void Release(ref MqlAccountInfo account_info);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release-DLL@Metatrader5@MQL5@@SAXAEAUMqlSymbolInfo@2@@Z")]
        public static extern void Release(ref MqlSymbolInfo symbol_info);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release-DLL@Metatrader5@MQL5@@SAXAEAUMqlTick@2@@Z")]
        public static extern void Release(ref MqlTick tick);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release-DLL@Metatrader5@MQL5@@SAXAEAUMqlRates@2@@Z")]
        public static extern void Release(ref MqlRates tick);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlTradeRequest@2@@Z")]
        public static extern void Release(ref MqlTradeRequest request);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlTradeResult@2@@Z")]
        public static extern void Release(ref MqlTradeResult result);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlSymbolInfoContainer@2@@Z")]
        public static extern bool Release(ref MqlSymbolInfoContainer symbols);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?OrderSend@Metatrader5@MQL5@@SA_NAEBUMqlTradeRequest@2@AEAUMqlTradeResult@2@@Z")]
        public static extern bool OrderSend(ref MqlTradeRequest request, ref MqlTradeResult result);

        [DllImport(@"D:\Prj\MQL++\x64\Release-DLL\MQL++.dll", EntryPoint = "?GetCurrentTime@Utils@MQL5@@YA_KD@Z")]
        public static extern UInt64 GetCurrentTime(sbyte timezone_offset);
    }
}
