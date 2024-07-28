using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Metatrader5
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlObject
    {

        public IntPtr obj;
        public ulong size;
        public IntPtr start;
        public ulong total_bytes;
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
        Int64 version;
        Int64 build;
        string date;

        public enum ENUM_INDEX

        {
            INDEX_VERSION,
            INDEX_BUILD,
            INDEX_DATE
        };
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlAccountInfo
    {
        ulong login;
        ENUM_ACCOUNT_TRADE_MODE trade_mode;
        Int64 leverage;
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
        string name;
        string server;
        string currency;
        string company;
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlErrorInfo
    {
        ENUM_ERROR_CODE error;
        string desc;

        public enum ENUM_INDEX

        {
            INDEX_ERROR,
            INDEX_DESC
        };
    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlSymbolInfo
    {
        public MqlSymbolInfo()
        {
            custom = false;
            chart_mode = ENUM_SYMBOL_CHART_MODE.SYMBOL_CHART_MODE_LAST;
            select = false;
            visible = false;
            session_deals = 0;
            session_buy_orders = 0;
            session_sell_orders = 0;
            volume = 0;
            volumehigh = 0;
            volumelow = 0;
            time = 0;
            digits = 0;
            spread = 0;
            spread_float = false;
            ticks_bookdepth = 0;
            trade_calc_mode = ENUM_SYMBOL_CALC_MODE.SYMBOL_CALC_MODE_CFD;
            trade_mode = ENUM_SYMBOL_TRADE_MODE.SYMBOL_TRADE_MODE_DISABLED;
            start_time = 0;
            expiration_time = 0;
            trade_stops_level = 0;
            trade_freeze_level = 0;
            trade_exemode = ENUM_SYMBOL_TRADE_EXECUTION.SYMBOL_TRADE_EXECUTION_EXCHANGE;
            swap_mode = ENUM_SYMBOL_SWAP_MODE.SYMBOL_SWAP_MODE_DISABLED;
            swap_rollover3days = ENUM_DAY_OF_WEEK.SUNDAY;
            margin_hedged_use_leg = false;
            expiration_mode = 0;
            filling_mode = 0;
            order_mode = 0;
            order_gtc_mode = 0;
            option_mode = 0;
            option_right = 0;
            bid = 0;
            bidhigh = 0;
            bidlow = 0;
            ask = 0;
            askhigh = 0;
            asklow = 0;
            last = 0;
            lasthigh = 0;
            lastlow = 0;
            volume_real = 0;
            volumehigh_real = 0;
            volumelow_real = 0;
            option_strike = 0;
            point = 0;
            trade_tick_value = 0;
            trade_tick_value_profit = 0;
            trade_tick_value_loss = 0;
            trade_tick_size = 0;
            trade_contract_size = 0;
            trade_accrued_interest = 0;
            trade_face_value = 0;
            trade_liquidity_rate = 0;
            volume_min = 0;
            volume_max = 0;
            volume_step = 0;
            volume_limit = 0;
            swap_long = 0;
            swap_short = 0;
            margin_initial = 0;
            margin_maintenance = 0;

            session_volume = 0;
            session_turnover = 0;
            session_interest = 0;
            session_buy_orders_volume = 0;
            session_sell_orders_volume = 0;
            session_open = 0;
            session_close = 0;
            session_aw = 0;
            session_price_settlement = 0;
            session_price_limit_min = 0;
            session_price_limit_max = 0;

            margin_hedged = 0;
            price_change = 0;
            price_volatility = 0;
            price_theoretical = 0;
            price_greeks_delta = 0;
            price_greeks_theta = 0;
            price_greeks_gamma = 0;
            price_greeks_vega = 0;
            price_greeks_rho = 0;
            price_greeks_omega = 0;
            price_sensitivity = 0;
            basis = "";
            category = "";
            currency_base = "";
            currency_profit = "";
            currency_margin = "";
            bank = "";
            description = "";
            exchange = "";
            formula = "";
            isin = "";
            name = "";
            page = "";
            path = "";
        }

        public bool custom;
        public ENUM_SYMBOL_CHART_MODE chart_mode;
        public bool select;
        public bool visible;
        public Int64 session_deals;
        public Int64 session_buy_orders;
        public Int64 session_sell_orders;
        public Int64 volume;
        public Int64 volumehigh;
        public Int64 volumelow;
        public Int64 time;
        public int digits;
        public int spread;
        public bool spread_float;
        public int ticks_bookdepth;
        public ENUM_SYMBOL_CALC_MODE trade_calc_mode;
        public ENUM_SYMBOL_TRADE_MODE trade_mode;
        public datetime start_time;
        public datetime expiration_time;
        public int trade_stops_level;
        public int trade_freeze_level;
        public ENUM_SYMBOL_TRADE_EXECUTION trade_exemode;
        public ENUM_SYMBOL_SWAP_MODE swap_mode;
        public ENUM_DAY_OF_WEEK swap_rollover3days;
        public bool margin_hedged_use_leg;
        public int expiration_mode;
        public int filling_mode;
        public int order_mode;
        public ENUM_SYMBOL_ORDER_GTC_MODE order_gtc_mode;
        public ENUM_SYMBOL_OPTION_MODE option_mode;
        public ENUM_SYMBOL_OPTION_RIGHT option_right;
        public double bid;
        public double bidhigh;
        public double bidlow;
        public double ask;
        public double askhigh;
        public double asklow;
        public double last;
        public double lasthigh;
        public double lastlow;
        public double volume_real;
        public double volumehigh_real;
        public double volumelow_real;
        public double option_strike;
        public double point;
        public double trade_tick_value;
        public double trade_tick_value_profit;
        public double trade_tick_value_loss;
        public double trade_tick_size;
        public double trade_contract_size;
        public double trade_accrued_interest;
        public double trade_face_value;
        public double trade_liquidity_rate;
        public double volume_min;
        public double volume_max;
        public double volume_step;
        public double volume_limit;
        public double swap_long;
        public double swap_short;
        public double margin_initial;
        public double margin_maintenance;
        public double session_volume;
        public double session_turnover;
        public double session_interest;
        public double session_buy_orders_volume;
        public double session_sell_orders_volume;
        public double session_open;
        public double session_close;
        public double session_aw;
        public double session_price_settlement;
        public double session_price_limit_min;
        public double session_price_limit_max;
        public double margin_hedged;
        public double price_change;
        public double price_volatility;
        public double price_theoretical;
        public double price_greeks_delta;
        public double price_greeks_theta;
        public double price_greeks_gamma;
        public double price_greeks_vega;
        public double price_greeks_rho;
        public double price_greeks_omega;
        public double price_sensitivity;
        public string basis;
        public string category;
        public string currency_base;
        public string currency_profit;
        public string currency_margin;
        public string bank;
        public string description;
        public string exchange;
        public string formula;
        public string isin;
        public string name;
        public string page;
        public string path;

        public enum ENUM_INDEX

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

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlTick
    {
        public datetime time;          // Time of the last prices update
        public double bid;           // Current Bid price
        public double ask;           // Current Ask price
        public double last;          // Price of the last deal (Last)
        public ulong volume;        // Volume for the current Last price
        public Int64 time_msc;      // Time of a price last update in milliseconds
        public uint flags;         // Tick flags
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
            set => mql_ticks[idx] = value;
        }


    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlRates
    {
        public MqlRates()
        {
            time = 0;
            open = 0;
            high = 0;
            low = 0;
            close = 0;
            tick_volume = 0;
            spread = 0;
            real_volume = 0;
        }

        public datetime time;         // Period start time 
        public double open;         // Open price 
        public double high;         // The highest price of the period 
        public double low;          // The lowest price of the period 
        public double close;        // Close price 
        public Int64 tick_volume;  // Tick volume 
        public int spread;       // Spread 
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
            set => mql_rates[idx] = value;
        }


    };

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct MqlTradeRequest
    {
        public ENUM_TRADE_REQUEST_ACTION action;
        public ulong magic;
        public ulong order;
        public string symbol;
        public double volume;
        public double price;
        public double stoplimit;
        public double sl;
        public double tp;
        public ulong deviation;
        public ENUM_ORDER_TYPE type;
        public ENUM_ORDER_TYPE_FILLING type_filling;
        public ENUM_ORDER_TYPE_TIME type_time;
        public ulong expiration;
        public string comment;
        public ulong position;
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
        public uint retcode;          // Operation return code
        public ulong deal;             // Deal ticket, if it is performed
        public ulong order;            // Order ticket, if it is placed
        public double volume;           // Deal volume, confirmed by broker
        public double price;            // Deal price, confirmed by broker
        public double bid;              // Current Bid price
        public double ask;              // Current Ask price
        public string comment;          // Broker comment to operation (by default it is filled by description of trade server return code)
        public uint request_id;       // Request ID set by the terminal during the dispatch 
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
        ENUM_BOOK_TYPE type;            // Order type from ENUM_BOOK_TYPE enumeration
        double price;           // Price
        Int64 volume;          // Volume
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
        ulong ticket;
        ulong time_setup;
        ulong time_setup_msc;
        ulong time_done;
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
        string symbol;
        string comment;
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
        string symbol;
        string comment;
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
    //}

    public partial class Methods
    {
        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?InitPyEnv@Metatrader5@MQL5@@SA_NXZ")]
        public static extern bool InitPyEnv();

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Init@Metatrader5@MQL5@@SA_NXZ")]
        public static extern bool Init();

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Login@Metatrader5@MQL5@@SA_N_KPEBD10@Z")]
        public static extern bool Login(UInt64 login, string password, string server_name, UInt64 timeout = 5000);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?SymbolsTotal@Metatrader5@MQL5@@SAJXZ")]
        public static extern long SymbolsTotal();

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?SymbolData@Metatrader5@MQL5@@SA_NPEBDAEAUMqlObject@2@@Z")]
        public static extern bool SymbolInfo(string symbol, ref MqlSymbolInfo symbol_info);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?CopyTicksFrom@Metatrader5@MQL5@@SAJPEBD_K1JAEAUMqlTickContainer@2@@Z")]
        public static extern long CopyTicksFrom(string symbol, ulong date_from, ulong count, ENUM_TICK_FLAG flags, ref MqlTickContainer buffer);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?CopyTicksRange@Metatrader5@MQL5@@SAJPEBD_K1JAEAUMqlTickContainer@2@@Z")]
        public static extern long CopyTicksRange(string symbol, ulong date_from, ulong date_to, ENUM_TICK_FLAG flags, ref MqlTickContainer buffer);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?CopyRatesFrom@Metatrader5@MQL5@@SAJPEBDW4ENUM_TIMEFRAMES@2@_K2AEAUMqlObject@2@@Z")]
        public static extern long CopyRatesFrom(string symbol, ENUM_TIMEFRAMES timeframe, UInt64 date_from, ulong count, ref MqlRatesContainer buffer);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?CStrToDatetime@Utils@MQL5@@YA_KPEBD@Z")]
        public static extern UInt64 CStrToDatetime(string date);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlObject@2@@Z")]
        public static extern void Release(ref MqlObject obj);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlErrorInfo@2@@Z")]
        public static extern void Release(ref MqlErrorInfo error_info);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlVersionInfo@2@@Z")]
        public static extern void Release(ref MqlVersionInfo version_info);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlAccountInfo@2@@Z")]
        public static extern void Release(ref MqlAccountInfo account_info);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlSymbolInfo@2@@Z")]
        public static extern void Release(ref MqlSymbolInfo symbol_info);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlTick@2@@Z")]
        public static extern void Release(ref MqlTick tick);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlRates@2@@Z")]
        public static extern void Release(ref MqlRates tick);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlTradeRequest@2@@Z")]
        public static extern void Release(ref MqlTradeRequest request);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlTradeResult@2@@Z")]
        public static extern void Release(ref MqlTradeResult result);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlTickContainer@2@@Z")]
        public static extern void Release(ref MqlTickContainer request);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?Release@Metatrader5@MQL5@@SAXAEAUMqlRatesContainer@2@@Z")]
        public static extern void Release(ref MqlRatesContainer result);

        [DllImport(@"D:\Prj\SimplePy\x64\Release-DLL\MQL++.dll", EntryPoint = "?OrderSend@Metatrader5@MQL5@@SA_NAEBUMqlTradeRequest@2@AEAUMqlTradeResult@2@@Z")]
        public static extern bool OrderSend(ref MqlTradeRequest request, ref MqlTradeResult result);
    }
}
