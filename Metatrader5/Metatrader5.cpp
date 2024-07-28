#include <chrono>

#include "Metatrader5.h"
#include "Python.h"
#include "inttypes.h"

using namespace MQL5;

bool MQL5::Metatrader5::ImportModule()
{
	mt5_mod = PyImport_ImportModule("MetaTrader5");

	if (mt5_mod == nullptr)
	{
		std::cout << ">>> Couldn't import the module 'MetaTrader5'.\n";
		PyErr_Print();
		return false;
	}

	return true;
}

bool MQL5::Metatrader5::ImportFunctions()
{
	PY_INIT_FUNC("initialize", 0);
	PY_INIT_FUNC("login", 1);
	PY_INIT_FUNC("shutdown", 2);
	PY_INIT_FUNC("version", 3);
	PY_INIT_FUNC("last_error", 4);
	PY_INIT_FUNC("account_info", 5);
	PY_INIT_FUNC("terminal_info", 6);
	PY_INIT_FUNC("symbols_total", 7);
	PY_INIT_FUNC("symbols_get", 8);
	PY_INIT_FUNC("symbol_info", 9);
	PY_INIT_FUNC("symbol_info_tick", 10);
	PY_INIT_FUNC("symbol_select", 11);
	PY_INIT_FUNC("market_book_add", 12);
	PY_INIT_FUNC("market_book_get", 13);
	PY_INIT_FUNC("market_book_release", 14);
	PY_INIT_FUNC("copy_rates_from", 15);
	PY_INIT_FUNC("copy_rates_from_pos", 16);
	PY_INIT_FUNC("copy_rates_range", 17);
	PY_INIT_FUNC("copy_ticks_from", 18);
	PY_INIT_FUNC("copy_ticks_range", 19);
	PY_INIT_FUNC("orders_total", 20);
	PY_INIT_FUNC("orders_get", 21);
	PY_INIT_FUNC("order_calc_margin", 22);
	PY_INIT_FUNC("order_calc_profit", 23);
	PY_INIT_FUNC("order_check", 24);
	PY_INIT_FUNC("order_send", 25);
	PY_INIT_FUNC("positions_total", 26);
	PY_INIT_FUNC("positions_get", 27);
	PY_INIT_FUNC("history_orders_total", 28);
	PY_INIT_FUNC("history_orders_get", 29);
	PY_INIT_FUNC("history_deals_total", 30);
	PY_INIT_FUNC("history_deals_get", 31);

	return true;
}


void MQL5::Metatrader5::ListAttr()
{
	PyObject* py_methods = PyObject_Dir(mt5_mod);

	if (py_methods == nullptr)
	{
		PyErr_Print();
		return;
	}

	PyObject* py_str = PyObject_Str(py_methods);
	const char* str = PyUnicode_AsUTF8(py_str);

	Py_XDECREF(py_str);

	std::cout << str << "\n";
}

bool MQL5::Metatrader5::InitPyEnv()
{
	if (Py_IsInitialized() != 0)
	{
		std::cout << ">>> Python environment already initialized.\n";
		return true;
	}

	Py_Initialize();

	if (Py_IsInitialized() == 0)
	{
		PyErr_Print();
		return false;
	}

	if (ImportModule() == false)
		return false;
	
	if (ImportFunctions() == false)
		return false;

	import_array();

	return true;
}

bool MQL5::Metatrader5::Init()
{
	
	static PyObject*& py_fn = PY_FUNC_TABLE[0].first;
	static PyCFunctionWithKeywords fn = (PyCFunctionWithKeywords)PY_FUNC_TABLE[0].second;

	PyObject* py_args = PyTuple_New(0);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'initialize'\n";

		PyErr_Print(); 
		PyErr_Clear();

		Py_XDECREF(py_ret_value);

		return false;
	}

	bool ret_value = (bool)PyLong_AsLongLong(py_ret_value);

	Py_DECREF(py_ret_value);

	return ret_value;
}

bool MQL5::Metatrader5::Login(size_t login, const char* password, const char* server_name, size_t timeout)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[1].first;
	static PyCFunctionWithKeywords& fn = (PyCFunctionWithKeywords&)PY_FUNC_TABLE[1].second;

	PyObject* py_args = PyTuple_New(1);
	PyObject* py_value = PyLong_FromSize_t(login);
	PyTuple_SetItem(py_args, 0, py_value);

	PyObject* py_kwargs = PyDict_New();
	PyObject* py_key = nullptr;
	
	if(password)
	{ 
		py_key = PyUnicode_FromString("password");
		py_value = PyUnicode_FromString(password);
		PyDict_SetItem(py_kwargs, py_key, py_value);

		Py_XDECREF(py_key);
		Py_XDECREF(py_value);
	}
	
	if (server_name)
	{
		py_key = PyUnicode_FromString("server");
		py_value = PyUnicode_FromString(server_name);
		PyDict_SetItem(py_kwargs, py_key, py_value);

		Py_XDECREF(py_key);
		Py_XDECREF(py_value);
	}

	if (timeout != 0)
	{
		py_key = PyUnicode_FromString("timeout");
		py_value = PyLong_FromLong(timeout);
		PyDict_SetItem(py_kwargs, py_key, py_value);

		Py_XDECREF(py_key);
		Py_XDECREF(py_value);
	}

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'version'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_ret_value);
		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);

		return false;
	}

	bool ret = (bool)PyLong_AsLongLong(py_ret_value);

	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return ret;
}

bool MQL5::Metatrader5::VersionInfo(MqlVersionInfo& version)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[3].first;
	static PyCFunctionWithKeywords fn = PY_FUNC_TABLE[3].second;

	PyObject* py_ret_value = fn(py_fn, NULL, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'version'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_ret_value);

		return false;
	}

	PyObject* ret0 = PyTuple_GetItem(py_ret_value, 0);
	PyObject* ret1 = PyTuple_GetItem(py_ret_value, 1);
	PyObject* ret2 = PyTuple_GetItem(py_ret_value, 2);

	version.version = PyLong_AsLongLong(ret0);
	version.build = PyLong_AsLongLong(ret1);

	Py_ssize_t size;
	const char* ret_buffer = PyUnicode_AsUTF8AndSize(ret2, &size);
	version.date = new char[++size];
	memcpy(version.date, ret_buffer, size);

	Py_DECREF(py_ret_value);

	return true;
}

bool MQL5::Metatrader5::AccountInfo(MqlAccountInfo& account_info)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[5].first;
	static PyCFunctionWithKeywords fn = PY_FUNC_TABLE[5].second;

	PyObject* py_ret_value = fn(py_fn, NULL, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'account_info'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_ret_value);

		return false;
	}

	Py_ssize_t tmp_size;
	const char* tmp_str;

	PyObject* ret = PyTuple_GetItem(py_ret_value, 0);
	account_info.login = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 1);
	account_info.trade_mode = (ENUM_ACCOUNT_TRADE_MODE)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 2);
	account_info.leverage = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 3);
	account_info.limit_orders = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 4);
	account_info.margin_so_mode = (ENUM_ACCOUNT_STOPOUT_MODE)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 5);
	account_info.trade_allowed = (bool)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 6);
	account_info.trade_expert = (bool)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 7);
	account_info.margin_mode = (ENUM_ACCOUNT_MARGIN_MODE)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 8);
	account_info.currency_digits = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 9);
	account_info.fifo_close = (bool)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 10);
	account_info.balance = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 11);
	account_info.credit = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 12);
	account_info.profit = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 13);
	account_info.equity = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 14);
	account_info.margin = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 15);
	account_info.margin_free = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 16);
	account_info.margin_level = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 17);
	account_info.margin_so_call = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 18);
	account_info.margin_so_so = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 19);
	account_info.margin_initial = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 20);
	account_info.margin_maintenance = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 21);
	account_info.assets = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 22);
	account_info.liabilities = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 23);
	account_info.commission_blocked = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 24);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	account_info.name = new char[++tmp_size];
	memcpy(account_info.name, tmp_str, tmp_size);

	ret = PyTuple_GetItem(py_ret_value, 25);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	account_info.server = new char[++tmp_size];
	memcpy(account_info.server, tmp_str, tmp_size);

	ret = PyTuple_GetItem(py_ret_value, 26);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	account_info.currency = new char[++tmp_size];
	memcpy(account_info.currency, tmp_str, tmp_size);

	ret = PyTuple_GetItem(py_ret_value, 27);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	account_info.company = new char[++tmp_size];
	memcpy(account_info.company, tmp_str, tmp_size);

	Py_DECREF(py_ret_value);

	return true;
}

bool MQL5::Metatrader5::GetLastError(MqlErrorInfo& error_info)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[4].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[4].second;

	PyObject* py_ret_value = fn(py_fn, NULL, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'last_error'\n";
		
		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_ret_value);

		return false;
	}

	const char* tmp_str;
	Py_ssize_t tmp_size;

	PyObject* item = PyTuple_GetItem(py_ret_value, 0);
	error_info.error = (ENUM_ERROR_CODE)PyLong_AsLongLong(item);

	item = PyTuple_GetItem(py_ret_value, 1);
	tmp_str = PyUnicode_AsUTF8AndSize(item, &tmp_size);
	error_info.desc = new char[++tmp_size];
	memcpy(error_info.desc, tmp_str, tmp_size);

	Py_DECREF(py_ret_value);

	return true;
}

long MQL5::Metatrader5::SymbolsTotal()
{
	static PyObject*& py_fn = PY_FUNC_TABLE[7].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[7].second;

	PyObject* py_ret_value = fn(py_fn, NULL, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'symbols_total'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_ret_value);

		return -1;
	}

	long ret = PyLong_AsLongLong(py_ret_value);

	Py_DECREF(py_ret_value);

	return ret;
}

long MQL5::Metatrader5::SymbolsGet(const char* group, MqlSymbolInfoContainer& symbols)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[8].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[8].second;

	PyObject* py_args = PyTuple_New(1);
	PyObject* py_value = PyUnicode_FromString(group);

	PyTuple_SET_ITEM(py_args, 0, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'symbols_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return -1;
	}

	symbols.mql_object.object = py_ret_value;
	symbols.mql_object.elem_count = PyTuple_GET_SIZE(py_ret_value);

	symbols.mql_symbols = new MqlSymbolInfo[symbols.mql_object.elem_count];

	const char* tmp_str;
	Py_ssize_t tmp_size;

	Py_ssize_t py_ret_len = PyTuple_GET_SIZE(py_ret_value);

	for (Py_ssize_t i = 0; i < py_ret_len; ++i)
	{
		MqlSymbolInfo& symbol_info = symbols.mql_symbols[i];

		PyObject* ret_tuple = PyTuple_GetItem(py_ret_value, 0);
		PyObject* ret = PyTuple_GetItem(ret_tuple, 0);
		symbol_info.custom = (bool)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 1);
		symbol_info.chart_mode = (ENUM_SYMBOL_CHART_MODE)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 2);
		symbol_info.select = (bool)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 3);
		symbol_info.visible = (bool)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 4);
		symbol_info.session_deals = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 5);
		symbol_info.session_buy_orders = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 6);
		symbol_info.session_sell_orders = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 7);
		symbol_info.volume = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 8);
		symbol_info.volumehigh = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 9);
		symbol_info.volumelow = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 10);
		symbol_info.time = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 11);
		symbol_info.digits = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 12);
		symbol_info.spread = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 13);
		symbol_info.spread_float = (bool)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 14);
		symbol_info.ticks_bookdepth = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 15);
		symbol_info.trade_calc_mode = (ENUM_SYMBOL_CALC_MODE)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 16);
		symbol_info.trade_mode = (ENUM_SYMBOL_TRADE_MODE)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 17);
		symbol_info.start_time = (datetime)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 18);
		symbol_info.expiration_time = (datetime)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 19);
		symbol_info.trade_stops_level = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 20);
		symbol_info.trade_freeze_level = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 21);
		symbol_info.trade_exemode = (ENUM_SYMBOL_TRADE_EXECUTION)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 22);
		symbol_info.swap_mode = (ENUM_SYMBOL_SWAP_MODE)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 23);
		symbol_info.swap_rollover3days = (ENUM_DAY_OF_WEEK)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 24);
		symbol_info.margin_hedged_use_leg = (bool)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 25);
		symbol_info.expiration_mode = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 26);
		symbol_info.filling_mode = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 27);
		symbol_info.order_mode = PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 28);
		symbol_info.order_gtc_mode = (ENUM_SYMBOL_ORDER_GTC_MODE)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 29);
		symbol_info.option_mode = (ENUM_SYMBOL_OPTION_MODE)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 30);
		symbol_info.option_right = (ENUM_SYMBOL_OPTION_RIGHT)PyLong_AsLongLong(ret);

		ret = PyTuple_GetItem(ret_tuple, 31);
		symbol_info.bid = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 32);
		symbol_info.bidhigh = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 33);
		symbol_info.bidlow = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 34);
		symbol_info.ask = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 35);
		symbol_info.askhigh = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 36);
		symbol_info.asklow = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 37);
		symbol_info.last = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 38);
		symbol_info.lasthigh = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 39);
		symbol_info.lastlow = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 40);
		symbol_info.volume_real = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 41);
		symbol_info.volumehigh_real = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 42);
		symbol_info.volumelow_real = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 43);
		symbol_info.option_strike = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 44);
		symbol_info.point = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 45);
		symbol_info.trade_tick_value = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 46);
		symbol_info.trade_tick_value_profit = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 47);
		symbol_info.trade_tick_value_loss = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 48);
		symbol_info.trade_tick_size = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 49);
		symbol_info.trade_contract_size = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 50);
		symbol_info.trade_accrued_interest = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 51);
		symbol_info.trade_face_value = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 52);
		symbol_info.trade_liquidity_rate = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 53);
		symbol_info.volume_min = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 54);
		symbol_info.volume_max = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 55);
		symbol_info.volume_step = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 56);
		symbol_info.volume_limit = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 57);
		symbol_info.swap_long = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 58);
		symbol_info.swap_short = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 59);
		symbol_info.margin_initial = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 60);
		symbol_info.margin_maintenance = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 61);
		symbol_info.session_volume = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 62);
		symbol_info.session_turnover = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 63);
		symbol_info.session_interest = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 64);
		symbol_info.session_buy_orders_volume = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 65);
		symbol_info.session_sell_orders_volume = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 66);
		symbol_info.session_open = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 67);
		symbol_info.session_close = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 68);
		symbol_info.session_aw = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 69);
		symbol_info.session_price_settlement = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 70);
		symbol_info.session_price_limit_min = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 71);
		symbol_info.session_price_limit_max = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 72);
		symbol_info.margin_hedged = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 73);
		symbol_info.price_change = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 74);
		symbol_info.price_volatility = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 75);
		symbol_info.price_theoretical = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 76);
		symbol_info.price_greeks_delta = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 77);
		symbol_info.price_greeks_theta = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 78);
		symbol_info.price_greeks_gamma = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 79);
		symbol_info.price_greeks_vega = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 80);
		symbol_info.price_greeks_rho = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 81);
		symbol_info.price_greeks_omega = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 82);
		symbol_info.price_sensitivity = PyFloat_AsDouble(ret);

		ret = PyTuple_GetItem(ret_tuple, 83);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.basis = new char[tmp_size+1];
		memcpy(symbol_info.basis, tmp_str, ++tmp_size);

		ret = PyTuple_GetItem(ret_tuple, 84);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.category = new char[tmp_size+1];
		memcpy(symbol_info.category, tmp_str, ++tmp_size);

		ret = PyTuple_GetItem(ret_tuple, 85);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.currency_base = new char[tmp_size+1];
		memcpy(symbol_info.currency_base, tmp_str, ++tmp_size);

		ret = PyTuple_GetItem(ret_tuple, 86);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.currency_profit = new char[tmp_size+1];
		memcpy(symbol_info.currency_profit, tmp_str, ++tmp_size);


		ret = PyTuple_GetItem(ret_tuple, 87);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.currency_margin = new char[tmp_size+1];
		memcpy(symbol_info.currency_margin, tmp_str, ++tmp_size);


		ret = PyTuple_GetItem(ret_tuple, 88);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.bank = new char[tmp_size+1];
		memcpy(symbol_info.bank, tmp_str, ++tmp_size);

		ret = PyTuple_GetItem(ret_tuple, 89);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.description = new char[tmp_size+1];
		memcpy(symbol_info.description, tmp_str, ++tmp_size);

		ret = PyTuple_GetItem(ret_tuple, 90);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.exchange = new char[tmp_size+1];
		memcpy(symbol_info.exchange, tmp_str, ++tmp_size);

		ret = PyTuple_GetItem(ret_tuple, 91);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.formula = new char[tmp_size+1];
		memcpy(symbol_info.formula, tmp_str, ++tmp_size);

		ret = PyTuple_GetItem(ret_tuple, 92);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.isin = new char[tmp_size+1];
		memcpy(symbol_info.isin, tmp_str, ++tmp_size);

		ret = PyTuple_GetItem(ret_tuple, 93);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.name = new char[tmp_size+1];
		memcpy(symbol_info.name, tmp_str, ++tmp_size);

		ret = PyTuple_GetItem(ret_tuple, 94);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.page = new char[tmp_size+1];
		memcpy(symbol_info.page, tmp_str, ++tmp_size);

		ret = PyTuple_GetItem(ret_tuple, 95);
		tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
		symbol_info.path = new char[tmp_size+1];
		memcpy(symbol_info.path, tmp_str, ++tmp_size);
	}

	Py_DECREF(py_args);

	return symbols.mql_object.elem_count;
}

bool MQL5::Metatrader5::SymbolInfo(const char* symbol, MqlSymbolInfo& symbol_info)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[9].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[9].second;

	PyObject* py_args = PyTuple_New(1);
	PyObject* py_value = PyUnicode_FromString(symbol);

	PyTuple_SET_ITEM(py_args, 0, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'symbol_info'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return false;
	}
	else if (py_ret_value == Py_None)
	{
		return false;
	}

	const char* tmp_str = nullptr;
	Py_ssize_t tmp_size = 0;

	PyObject*& ret_tuple = py_ret_value;
	PyObject* ret = PyTuple_GetItem(ret_tuple, 0);
	symbol_info.custom = (bool)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 1);
	symbol_info.chart_mode = (ENUM_SYMBOL_CHART_MODE)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 2);
	symbol_info.select = (bool)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 3);
	symbol_info.visible = (bool)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 4);
	symbol_info.session_deals = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 5);
	symbol_info.session_buy_orders = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 6);
	symbol_info.session_sell_orders = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 7);
	symbol_info.volume = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 8);
	symbol_info.volumehigh = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 9);
	symbol_info.volumelow = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 10);
	symbol_info.time = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 11);
	symbol_info.digits = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 12);
	symbol_info.spread = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 13);
	symbol_info.spread_float = (bool)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 14);
	symbol_info.ticks_bookdepth = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 15);
	symbol_info.trade_calc_mode = (ENUM_SYMBOL_CALC_MODE)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 16);
	symbol_info.trade_mode = (ENUM_SYMBOL_TRADE_MODE)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 17);
	symbol_info.start_time = (datetime)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 18);
	symbol_info.expiration_time = (datetime)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 19);
	symbol_info.trade_stops_level = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 20);
	symbol_info.trade_freeze_level = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 21);
	symbol_info.trade_exemode = (ENUM_SYMBOL_TRADE_EXECUTION)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 22);
	symbol_info.swap_mode = (ENUM_SYMBOL_SWAP_MODE)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 23);
	symbol_info.swap_rollover3days = (ENUM_DAY_OF_WEEK)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 24);
	symbol_info.margin_hedged_use_leg = (bool)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 25);
	symbol_info.expiration_mode = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 26);
	symbol_info.filling_mode = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 27);
	symbol_info.order_mode = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 28);
	symbol_info.order_gtc_mode = (ENUM_SYMBOL_ORDER_GTC_MODE)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 29);
	symbol_info.option_mode = (ENUM_SYMBOL_OPTION_MODE)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 30);
	symbol_info.option_right = (ENUM_SYMBOL_OPTION_RIGHT)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(ret_tuple, 31);
	symbol_info.bid = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 32);
	symbol_info.bidhigh = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 33);
	symbol_info.bidlow = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 34);
	symbol_info.ask = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 35);
	symbol_info.askhigh = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 36);
	symbol_info.asklow = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 37);
	symbol_info.last = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 38);
	symbol_info.lasthigh = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 39);
	symbol_info.lastlow = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 40);
	symbol_info.volume_real = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 41);
	symbol_info.volumehigh_real = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 42);
	symbol_info.volumelow_real = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 43);
	symbol_info.option_strike = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 44);
	symbol_info.point = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 45);
	symbol_info.trade_tick_value = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 46);
	symbol_info.trade_tick_value_profit = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 47);
	symbol_info.trade_tick_value_loss = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 48);
	symbol_info.trade_tick_size = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 49);
	symbol_info.trade_contract_size = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 50);
	symbol_info.trade_accrued_interest = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 51);
	symbol_info.trade_face_value = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 52);
	symbol_info.trade_liquidity_rate = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 53);
	symbol_info.volume_min = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 54);
	symbol_info.volume_max = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 55);
	symbol_info.volume_step = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 56);
	symbol_info.volume_limit = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 57);
	symbol_info.swap_long = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 58);
	symbol_info.swap_short = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 59);
	symbol_info.margin_initial = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 60);
	symbol_info.margin_maintenance = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 61);
	symbol_info.session_volume = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 62);
	symbol_info.session_turnover = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 63);
	symbol_info.session_interest = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 64);
	symbol_info.session_buy_orders_volume = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 65);
	symbol_info.session_sell_orders_volume = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 66);
	symbol_info.session_open = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 67);
	symbol_info.session_close = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 68);
	symbol_info.session_aw = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 69);
	symbol_info.session_price_settlement = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 70);
	symbol_info.session_price_limit_min = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 71);
	symbol_info.session_price_limit_max = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 72);
	symbol_info.margin_hedged = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 73);
	symbol_info.price_change = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 74);
	symbol_info.price_volatility = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 75);
	symbol_info.price_theoretical = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 76);
	symbol_info.price_greeks_delta = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 77);
	symbol_info.price_greeks_theta = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 78);
	symbol_info.price_greeks_gamma = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 79);
	symbol_info.price_greeks_vega = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 80);
	symbol_info.price_greeks_rho = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 81);
	symbol_info.price_greeks_omega = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 82);
	symbol_info.price_sensitivity = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(ret_tuple, 83);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.basis = new char[++tmp_size];
	memcpy(symbol_info.basis, tmp_str, tmp_size);

	ret = PyTuple_GetItem(ret_tuple, 84);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.category = new char[++tmp_size];
	memcpy(symbol_info.category, tmp_str, tmp_size);

	ret = PyTuple_GetItem(ret_tuple, 85);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.currency_base = new char[++tmp_size];
	memcpy(symbol_info.currency_base, tmp_str, tmp_size);

	ret = PyTuple_GetItem(ret_tuple, 86);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.currency_profit = new char[++tmp_size];
	memcpy(symbol_info.currency_profit, tmp_str, tmp_size);


	ret = PyTuple_GetItem(ret_tuple, 87);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.currency_margin = new char[++tmp_size];
	memcpy(symbol_info.currency_margin, tmp_str, tmp_size);


	ret = PyTuple_GetItem(ret_tuple, 88);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.bank = new char[++tmp_size];
	memcpy(symbol_info.bank, tmp_str, tmp_size);

	ret = PyTuple_GetItem(ret_tuple, 89);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.description = new char[++tmp_size];
	memcpy(symbol_info.description, tmp_str, tmp_size);

	ret = PyTuple_GetItem(ret_tuple, 90);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.exchange = new char[++tmp_size];
	memcpy(symbol_info.exchange, tmp_str, tmp_size);

	ret = PyTuple_GetItem(ret_tuple, 91);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.formula = new char[++tmp_size];
	memcpy(symbol_info.formula, tmp_str, tmp_size);

	ret = PyTuple_GetItem(ret_tuple, 92);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.isin = new char[++tmp_size];
	memcpy(symbol_info.isin, tmp_str, tmp_size);

	ret = PyTuple_GetItem(ret_tuple, 93);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.name = new char[++tmp_size];
	memcpy(symbol_info.name, tmp_str, tmp_size);

	ret = PyTuple_GetItem(ret_tuple, 94);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.page = new char[++tmp_size];
	memcpy(symbol_info.page, tmp_str, tmp_size);

	ret = PyTuple_GetItem(ret_tuple, 95);
	tmp_str = PyUnicode_AsUTF8AndSize(ret, &tmp_size);
	symbol_info.path = new char[++tmp_size];
	memcpy(symbol_info.path, tmp_str, tmp_size);

	return true;
}

bool MQL5::Metatrader5::SymbolInfoTick(const char* symbol, MqlTick& tick)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[10].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[10].second;

	PyObject* py_args = PyTuple_New(1);
	PyObject* py_value = PyUnicode_FromString(symbol);

	PyTuple_SetItem(py_args, 0, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'symbol_info_tick'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return false;
	}
	else if (py_ret_value == Py_None)
	{
		return false;
	}

	PyObject* ret = PyTuple_GetItem(py_ret_value, 0);
	tick.time = (datetime)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 1);
	tick.bid = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 2);
	tick.ask = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 3);
	tick.last = PyFloat_AsDouble(ret);

	ret = PyTuple_GetItem(py_ret_value, 4);
	tick.volume = (uint64_t)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 5);
	tick.time_msc = PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 6);
	tick.flags = (uint32_t)PyLong_AsLongLong(ret);

	ret = PyTuple_GetItem(py_ret_value, 7);
	tick.volume_real = PyFloat_AsDouble(ret);
	
	Py_DECREF(py_args);
	Py_DECREF(py_ret_value);

	return true;
}

bool MQL5::Metatrader5::SymbolSelect(const char* symbol, bool enable)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[11].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[11].second;

	PyObject* py_args = PyTuple_New(2);
	PyObject* py_value = PyUnicode_FromString(symbol);

	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(enable);

	PyTuple_SetItem(py_args, 1, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'symbol_select'\n";
		
		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_ret_value);
		Py_XDECREF(py_args);

		return false;
	}
	else if (py_ret_value == Py_None)
	{
		return false;
	}

	long ret_value = PyLong_AsLong(py_ret_value);

	Py_DECREF(py_ret_value);
	Py_DECREF(py_args);

	return (bool)ret_value;
}

double MQL5::Metatrader5::Bid(const char* symbol)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[10].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[10].second;

	PyObject* py_args = PyTuple_New(1);
	PyObject* py_value = PyUnicode_FromString(symbol);

	PyTuple_SetItem(py_args, 0, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'symbol_info_tick'\n";
		
		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_ret_value);
		Py_XDECREF(py_args);

		return false;
	}
	else if (py_ret_value == Py_None)
	{
		return false;
	}

	PyObject* ret = PyTuple_GetItem(py_ret_value, 1);
	double bid = PyFloat_AsDouble(ret);


	Py_DECREF(py_ret_value);
	Py_DECREF(py_args);

	return bid;
}

double MQL5::Metatrader5::Ask(const char* symbol)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[10].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[10].second;

	PyObject* py_args = PyTuple_New(1);
	PyObject* py_value = PyUnicode_FromString(symbol);

	PyTuple_SetItem(py_args, 0, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'symbol_info_tick'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return false;
	}
	else if (py_ret_value == Py_None)
	{
		return false;
	}

	PyObject* ret = PyTuple_GetItem(py_ret_value, 2);
	double ask = PyFloat_AsDouble(ret);

	Py_DECREF(py_ret_value);
	Py_DECREF(py_args);

	return ask;
}

long MQL5::Metatrader5::CopyRatesFrom(const char* symbol, ENUM_TIMEFRAMES timeframe, datetime date_from, ulong count, MqlObject& rates)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[15].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[15].second;

	PyObject* py_args = PyTuple_New(4);
	PyObject* py_value = PyUnicode_FromString(symbol);

	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(timeframe);

	PyTuple_SetItem(py_args, 1, py_value);

	py_value = PyLong_FromLongLong(date_from);

	PyTuple_SetItem(py_args, 2, py_value);

	py_value = PyLong_FromLongLong(count);

	PyTuple_SetItem(py_args, 3, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'copy_rates_from'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return 0;
	}
	
	rates.object = py_ret_value;
	rates.elem_count = PyArray_SIZE(py_ret_value);

	Py_DECREF(py_args);

	return rates.elem_count;
}

long MQL5::Metatrader5::CopyRatesFromPos(const char* symbol, ENUM_TIMEFRAMES timeframe, int bar_from, ulong count, MqlRatesContainer& rates)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[16].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[16].second;

	PyObject* py_args = PyTuple_New(4);
	PyObject* py_value = PyUnicode_FromString(symbol);

	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(timeframe);

	PyTuple_SetItem(py_args, 1, py_value);

	py_value = PyLong_FromLong(bar_from);

	PyTuple_SetItem(py_args, 2, py_value);

	py_value = PyLong_FromLong(count);

	PyTuple_SetItem(py_args, 3, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'copy_rates_from_pos'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return -1;
	}

	rates.mql_object.object = py_ret_value;
	rates.mql_object.elem_count = PyArray_SIZE(py_ret_value);

	rates.mql_rates = (MqlRates*)PyArray_BYTES(rates.mql_object.object);

	Py_DECREF(py_args);

	return rates.mql_object.elem_count;
}

long MQL5::Metatrader5::CopyRatesRange(const char* symbol, ENUM_TIMEFRAMES timeframe, datetime date_from, datetime date_to, MqlRatesContainer& rates)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[17].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[17].second;

	PyObject* py_args = PyTuple_New(4);
	PyObject* py_value = PyUnicode_FromString(symbol);
	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(timeframe);
	PyTuple_SetItem(py_args, 1, py_value);

	py_value = PyLong_FromLong(date_from);
	PyTuple_SetItem(py_args, 2, py_value);

	py_value = PyLong_FromLong(date_to);
	PyTuple_SetItem(py_args, 3, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'copy_rates_range'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_ret_value);
		Py_XDECREF(py_args);

		return -1;
	}

	rates.mql_object.object = py_ret_value;
	rates.mql_object.elem_count = PyArray_SIZE(py_ret_value);

	rates.mql_rates = (MqlRates*)PyArray_BYTES(rates.mql_object.object);

	Py_DECREF(py_args);

	return rates.mql_object.elem_count;
}

long MQL5::Metatrader5::CopyTicksFrom(const char* symbol, datetime date_from, ulong count, long flags, MqlTickContainer& ticks)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[18].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[18].second;

	PyObject* py_args = PyTuple_New(4);
	PyObject* py_value = PyUnicode_FromString(symbol);
	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(date_from);
	PyTuple_SetItem(py_args, 1, py_value);

	py_value = PyLong_FromLong(count);
	PyTuple_SetItem(py_args, 2, py_value);

	py_value = PyLong_FromLong(flags);
	PyTuple_SetItem(py_args, 3, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'copy_ticks_from'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		return -1;
	}


	ticks.mql_object.object = py_ret_value;
	ticks.mql_object.elem_count = PyArray_SIZE(py_ret_value);

	ticks.mql_ticks = (MqlTick*)PyArray_BYTES(ticks.mql_object.object);

	Py_DECREF(py_args);


	return ticks.mql_object.elem_count;
}

long MQL5::Metatrader5::CopyTicksRange(const char* symbol, datetime date_from, datetime date_to, long flags, MqlTickContainer& ticks)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[19].first;
	static PyCFunctionWithKeywords& fn = (PyCFunctionWithKeywords&)PY_FUNC_TABLE[19].second;

	PyObject* py_arg0 = PyUnicode_FromString(symbol);
	PyObject* py_arg1 = PyLong_FromUnsignedLongLong(date_from);
	PyObject* py_arg2 = PyLong_FromUnsignedLongLong(date_to);
	PyObject* py_arg3 = PyLong_FromLong(flags);

	PyObject* py_args = PyTuple_New(4);;
	
	PyTuple_SetItem(py_args, 0, py_arg0);
	PyTuple_SetItem(py_args, 1, py_arg1);
	PyTuple_SetItem(py_args, 2, py_arg2);
	PyTuple_SetItem(py_args, 3, py_arg3);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'copy_ticks_range'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_ret_value);
		Py_XDECREF(py_args);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		return -1;
	}

	ticks.mql_object.object = py_ret_value;
	ticks.mql_object.elem_count = PyArray_SIZE(py_ret_value);

	ticks.mql_ticks = (MqlTick*)PyArray_BYTES(ticks.mql_object.object);

	Py_DECREF(py_args);

	return ticks.mql_object.elem_count;
}

bool MQL5::Metatrader5::OrderSend(const MqlTradeRequest& request, MqlTradeResult& result)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[25].first;
	static PyCFunctionWithKeywords& fn = (PyCFunctionWithKeywords&)PY_FUNC_TABLE[25].second;

	PyObject* py_args = PyTuple_New(1);
	PyObject* py_value = nullptr;
	PyObject* py_dict = PyDict_New();

	if (request.symbol == nullptr)
	{
		result.retcode = 10013;
		
		std::cout << "The symbol was 'nullptr' for the request.\n";

		return false;
	}

	py_value = PyUnicode_FromString(request.symbol);
	PyDict_SetItemString(py_dict, "symbol", py_value);
	Py_XDECREF(py_value);

	py_value = PyLong_FromLong(request.action);
	PyDict_SetItemString(py_dict, "action", py_value);
	Py_XDECREF(py_value);

	py_value = PyLong_FromSize_t(request.magic);
	PyDict_SetItemString(py_dict, "magic", py_value);
	Py_XDECREF(py_value);

	py_value = PyLong_FromLong(request.type);
	PyDict_SetItemString(py_dict, "type", py_value);
	Py_XDECREF(py_value);

	py_value = PyFloat_FromDouble(request.price);
	PyDict_SetItemString(py_dict, "price", py_value);
	Py_XDECREF(py_value);

	py_value = PyFloat_FromDouble(request.tp);
	PyDict_SetItemString(py_dict, "tp", py_value);
	Py_XDECREF(py_value);

	py_value = PyFloat_FromDouble(request.sl);
	PyDict_SetItemString(py_dict, "sl", py_value);
	Py_XDECREF(py_value);

	py_value = PyFloat_FromDouble(request.volume);
	PyDict_SetItemString(py_dict, "volume", py_value);
	Py_XDECREF(py_value);

	py_value = PyLong_FromLong(request.type_filling);
	PyDict_SetItemString(py_dict, "type_filling", py_value);
	Py_XDECREF(py_value);

	if (request.comment != nullptr)
	{
		py_value = PyUnicode_FromString(request.comment);
		PyDict_SetItemString(py_dict, "comment", py_value);
		Py_XDECREF(py_value);
	}

	py_value = PyLong_FromLong(request.deviation);
	PyDict_SetItemString(py_dict, "deviation", py_value);
	Py_XDECREF(py_value);

	py_value = PyLong_FromLong(request.order);
	PyDict_SetItemString(py_dict, "order", py_value);
	Py_XDECREF(py_value);

	py_value = PyLong_FromLong(request.position);
	PyDict_SetItemString(py_dict, "position", py_value);
	Py_XDECREF(py_value);

	py_value = PyLong_FromLong(request.position_by);
	PyDict_SetItemString(py_dict, "position_by", py_value);
	Py_XDECREF(py_value);

	py_value = PyLong_FromLong(request.type_time);
	PyDict_SetItemString(py_dict, "type_time", py_value);
	Py_XDECREF(py_value);

	PyTuple_SetItem(py_args, 0, py_dict);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'order_send'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_DECREF(py_ret_value);
		Py_DECREF(py_args);

		return false;
	}

	PyObject* py_item = PyTuple_GetItem(py_ret_value, 0);
	result.retcode = PyLong_AsLongLong(py_item);

	py_item = PyTuple_GetItem(py_ret_value, 1);
	result.deal = PyLong_AsLongLong(py_item);

	py_item = PyTuple_GetItem(py_ret_value, 2);
	result.order = PyLong_AsLongLong(py_item);

	py_item = PyTuple_GetItem(py_ret_value, 3);
	result.volume = PyFloat_AsDouble(py_item);

	py_item = PyTuple_GetItem(py_ret_value, 4);
	result.price = PyFloat_AsDouble(py_item);

	py_item = PyTuple_GetItem(py_ret_value, 5);
	result.bid = PyFloat_AsDouble(py_item);

	py_item = PyTuple_GetItem(py_ret_value, 6);
	result.ask = PyFloat_AsDouble(py_item);

	py_item = PyTuple_GetItem(py_ret_value, 7);
	Py_ssize_t tmp_size;
	const char* tmp_str = PyUnicode_AsUTF8AndSize(py_item, &tmp_size);
	result.comment = new char[++tmp_size];
	memcpy(result.comment, tmp_str, tmp_size);

	py_item = PyTuple_GetItem(py_ret_value, 8);
	result.request_id = PyLong_AsUnsignedLong(py_item);

	py_item = PyTuple_GetItem(py_ret_value, 9);
	result.retcode_external = PyLong_AsLong(py_item);


	Py_DECREF(py_ret_value);
	Py_DECREF(py_args);

	return true;
}

bool MQL5::Metatrader5::MarketBookAdd(const char* symbol)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[12].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[12].second;

	PyObject* py_args = PyTuple_New(1);
	PyObject* py_value = PyUnicode_FromString(symbol);

	PyTuple_SetItem(py_args, 0, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'market_book_add'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return false;
	}
	
	bool ret_value = (bool)PyLong_AsLongLong(py_ret_value);

	Py_DECREF(py_args);
	Py_DECREF(py_ret_value);

	return ret_value;
}

bool MQL5::Metatrader5::MarketBookGet(const char* symbol, MqlBookInfo*& book_info)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[13].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[13].second;

	PyObject* py_args = PyTuple_New(1);
	PyObject* py_value = PyUnicode_FromString(symbol);

	PyTuple_SetItem(py_args, 0, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'market_book_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return false;
	}
	else if (py_ret_value == Py_None)
	{
		std::cout << "The symbol has no market book.\n";

		Py_DECREF(py_args);

		return false;
	}
	PyObject* py_str = PyObject_Str(py_ret_value);
	const char* str = PyUnicode_AsUTF8(py_str);
	std::cout << "Market book: " << str << '\n';

	Py_DECREF(py_args);
	Py_DECREF(py_ret_value);

	return true;
}

bool MQL5::Metatrader5::MarketBookRelease(const char* symbol)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[14].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[14].second;

	PyObject* py_args = PyTuple_New(1);
	PyObject* py_value = PyUnicode_FromString(symbol);

	PyTuple_SetItem(py_args, 0, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'market_book_release'\n";
		 
		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return false;
	}

	bool ret_value = (bool)PyLong_AsLongLong(py_ret_value);

	Py_DECREF(py_args);
	Py_DECREF(py_ret_value);

	return ret_value;
}

long MQL5::Metatrader5::OrdersTotal()
{
	static PyObject*& py_fn = PY_FUNC_TABLE[20].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[20].second;

	PyObject* py_ret_value = fn(py_fn, NULL, NULL);

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'market_book_release'\n";
		
		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_ret_value);

		return false;
	}

	long ret_value = PyLong_AsLongLong(py_ret_value);

	Py_DECREF(py_ret_value);

	return ret_value;
}

long MQL5::Metatrader5::OrdersGet(MqlOrderInfoContainer& orders)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[21].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[21].second;

	PyObject* py_args = PyTuple_New(0);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);
	Py_ssize_t orders_count;

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'orders_get'\n";
		
		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		Py_XDECREF(py_args);

		return -1;
	}
	else if ((orders_count = PyTuple_GET_SIZE(py_ret_value)) == 0)
	{
		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);
		return 0;
	}

	orders.order_info = new MqlOrderInfo[orders_count];
	orders.size = orders_count;

	Py_ssize_t tmp_size;
	const char* tmp_str;

	for (int i = 0; i < orders_count; ++i)
	{
		MqlOrderInfo& info = orders[i];
		PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, i);
		info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));

		info.time_setup = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
		info.time_setup_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
		info.time_done = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
		info.time_done_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
		info.time_expiration = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
		info.type = (ENUM_ORDER_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
		info.type_time = (ENUM_ORDER_TYPE_TIME)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
		info.type_filling = (ENUM_ORDER_TYPE_FILLING)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
		info.state = (ENUM_ORDER_STATE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 9));
		info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 10));
		info.position_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 11));
		info.position_by_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 12));
		info.reason = (ENUM_ORDER_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 13));
		info.volume_initial = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));
		info.volume_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 15));
		info.price_open = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 16));
		info.sl = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 17));
		info.tp = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 18));
		info.price_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 19));
		info.price_stoplimit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 20));

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 21), &tmp_size);;
		info.symbol = new char[tmp_size + 1];
		memcpy(info.symbol, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 22), &tmp_size);;
		info.comment = new char[tmp_size + 1];
		memcpy(info.comment, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 23), &tmp_size);;
		info.external_id = new char[tmp_size + 1];
		memcpy(info.external_id, tmp_str, tmp_size);
	}


	Py_DECREF(py_ret_value);

	return orders_count;
}

long MQL5::Metatrader5::OrdersGetBySymbol(const char* symbol, MqlOrderInfoContainer& orders)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[21].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[21].second;

	PyObject* py_args = PyTuple_New(0);
	PyObject* py_kwargs = PyDict_New();

	PyObject * py_value = PyUnicode_FromString(symbol);
	PyDict_SetItemString(py_kwargs, "symbol", py_value);

	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);
	Py_ssize_t orders_count;

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'orders_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return -1;
	}

	else if (py_ret_value == Py_None)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);

		return -1;
	}
	else if ((orders_count = PyTuple_GET_SIZE(py_ret_value)) == 0)
	{
		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return 0;
	}

	orders.order_info = new MqlOrderInfo[orders_count];
	orders.size = orders_count;

	Py_ssize_t tmp_size;
	const char* tmp_str;

	for (int i = 0; i < orders_count; ++i)
	{
		MqlOrderInfo& info = orders[i];
		PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, i);
		info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));

		info.time_setup = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
		info.time_setup_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
		info.time_done = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
		info.time_done_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
		info.time_expiration = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
		info.type = (ENUM_ORDER_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
		info.type_time = (ENUM_ORDER_TYPE_TIME)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
		info.type_filling = (ENUM_ORDER_TYPE_FILLING)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
		info.state = (ENUM_ORDER_STATE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 9));
		info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 10));
		info.position_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 11));
		info.position_by_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 12));
		info.reason = (ENUM_ORDER_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 13));
		info.volume_initial = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));
		info.volume_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 15));
		info.price_open = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 16));
		info.sl = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 17));
		info.tp = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 18));
		info.price_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 19));
		info.price_stoplimit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 20));

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 21), &tmp_size);;
		info.symbol = new char[tmp_size + 1];
		memcpy(info.symbol, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 22), &tmp_size);;
		info.comment = new char[tmp_size + 1];
		memcpy(info.comment, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 23), &tmp_size);;
		info.external_id = new char[tmp_size + 1];
		memcpy(info.external_id, tmp_str, tmp_size);
	}

	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return orders_count;
}

long MQL5::Metatrader5::OrderGetByTicket(ulong ticket, MqlOrderInfo& order)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[21].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[21].second;

	PyObject* py_args = PyTuple_New(0);
	PyObject* py_kwargs = PyDict_New();

	PyObject* py_value = PyLong_FromLongLong(ticket);

	PyDict_SetItemString(py_kwargs, "ticket", py_value);
	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'orders_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);


		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);

		return -1;
	}
	else if (PyTuple_GET_SIZE(py_ret_value) == 0)
	{
		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return 0;
	}

	Py_ssize_t tmp_size;
	const char* tmp_str;

	MqlOrderInfo& info = order;
	PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, 0);
	info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));

	info.time_setup = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
	info.time_setup_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
	info.time_done = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
	info.time_done_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
	info.time_expiration = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
	info.type = (ENUM_ORDER_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
	info.type_time = (ENUM_ORDER_TYPE_TIME)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
	info.type_filling = (ENUM_ORDER_TYPE_FILLING)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
	info.state = (ENUM_ORDER_STATE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 9));
	info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 10));
	info.position_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 11));
	info.position_by_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 12));
	info.reason = (ENUM_ORDER_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 13));
	info.volume_initial = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));
	info.volume_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 15));
	info.price_open = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 16));
	info.sl = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 17));
	info.tp = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 18));
	info.price_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 19));
	info.price_stoplimit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 20));

	tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 21), &tmp_size);;
	info.symbol = new char[tmp_size + 1];
	memcpy(info.symbol, tmp_str, tmp_size);

	tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 22), &tmp_size);;
	info.comment = new char[tmp_size + 1];
	memcpy(info.comment, tmp_str, tmp_size);

	tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 23), &tmp_size);;
	info.external_id = new char[tmp_size + 1];
	memcpy(info.external_id, tmp_str, tmp_size);
	

	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return 1;
}

long MQL5::Metatrader5::PositionsTotal()
{
	static PyObject*& py_fn = PY_FUNC_TABLE[26].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[26].second;

	PyObject* py_args = PyTuple_New(0);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'positions_total'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return -1;
	}

	long ret_value = PyLong_AsLongLong(py_ret_value);

	Py_DECREF(py_args);
	Py_DECREF(py_ret_value);

	return ret_value;
}

long MQL5::Metatrader5::PositionsGet(MqlPositionInfoContainer& positions_info)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[21].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[21].second;

	PyObject* py_args = PyTuple_New(0);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'orders_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		return -1;
	}

	Py_ssize_t positions_count = PyTuple_GET_SIZE(py_ret_value);
	positions_info.pos_info = new MqlPositionInfo[positions_count];
	positions_info.size = positions_count;

	Py_ssize_t tmp_size;
	const char* tmp_str;

	for (int i = 0; i < positions_count; ++i)
	{
		MqlPositionInfo& info = positions_info[i];
		PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, i);
		info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));

		info.time = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
		info.time_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
		info.time_update = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
		info.time_update_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
		info.type = (ENUM_POSITION_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
		info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
		info.identifier = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
		info.reason = (ENUM_POSITION_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
		info.volume = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 9));
		info.price_open = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 10));
		info.sl = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 11));
		info.tp = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 12));
		info.price_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 13));
		info.swap = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));
		info.profit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 15));

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 16), &tmp_size);;
		info.symbol = new char[tmp_size + 1];
		memcpy(info.symbol, tmp_str, ++tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 17), &tmp_size);;
		info.comment = new char[tmp_size + 1];
		memcpy(info.comment, tmp_str, ++tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 18), &tmp_size);;
		info.external_id = new char[tmp_size + 1];
		memcpy(info.external_id, tmp_str, ++tmp_size);
	}


	Py_DECREF(py_ret_value);

	return positions_count;
}

long MQL5::Metatrader5::PositionsGetBySymbol(const char* symbol, MqlPositionInfoContainer& positions_info)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[27].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[27].second;

	PyObject* py_args = PyTuple_New(0);
	PyObject* py_kwargs = PyDict_New();

	PyObject* py_value = PyUnicode_FromString(symbol);
	PyDict_SetItemString(py_kwargs, "symbol", py_value);
	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'positions_get'\n";
		
		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		return -1;
	}

	Py_ssize_t positions_count = PyTuple_GET_SIZE(py_ret_value);
	positions_info.pos_info = new MqlPositionInfo[positions_count];
	positions_info.size = positions_count;

	Py_ssize_t tmp_size;
	const char* tmp_str;

	for (int i = 0; i < positions_count; ++i)
	{
		MqlPositionInfo& info = positions_info[i];
		PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, i);
		info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));

		info.time = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
		info.time_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
		info.time_update = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
		info.time_update_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
		info.type = (ENUM_POSITION_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
		info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
		info.identifier = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
		info.reason = (ENUM_POSITION_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
		info.volume = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 9));
		info.price_open = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 10));
		info.sl = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 11));
		info.tp = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 12));
		info.price_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 13));
		info.swap = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));
		info.profit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 15));

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 16), &tmp_size);;
		info.symbol = new char[tmp_size + 1];
		memcpy(info.symbol, tmp_str, ++tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 17), &tmp_size);;
		info.comment = new char[tmp_size + 1];
		memcpy(info.comment, tmp_str, ++tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 18), &tmp_size);;
		info.external_id = new char[tmp_size + 1];
		memcpy(info.external_id, tmp_str, ++tmp_size);
	}


	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return positions_count;
}

long MQL5::Metatrader5::PositionsGetByTicket(ulong ticket, MqlPositionInfo& position_info)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[27].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[27].second;

	PyObject* py_args = PyTuple_New(0);
	PyObject* py_kwargs = PyDict_New();

	PyObject* py_value = PyLong_FromLongLong(ticket);

	PyDict_SetItemString(py_kwargs, "ticket", py_value);
	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'positions_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);

		return -1;
	}
	else if (PyTuple_GET_SIZE(py_ret_value) == 0)
	{
		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return 0;
	}

	Py_ssize_t tmp_size;
	const char* tmp_str;

	MqlPositionInfo& info = position_info;
	PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, 0);
	info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));

	info.time = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
	info.time_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
	info.time_update = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
	info.time_update_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
	info.type = (ENUM_POSITION_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
	info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
	info.identifier = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
	info.reason = (ENUM_POSITION_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
	info.volume = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 9));
	info.price_open = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 10));
	info.sl = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 11));
	info.tp = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 12));
	info.price_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 13));
	info.swap = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));
	info.profit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 15));

	tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 16), &tmp_size);;
	info.symbol = new char[++tmp_size];
	memcpy(info.symbol, tmp_str, tmp_size);

	tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 17), &tmp_size);;
	info.comment = new char[++tmp_size];
	memcpy(info.comment, tmp_str, tmp_size);

	tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 18), &tmp_size);;
	info.external_id = new char[++tmp_size];
	memcpy(info.external_id, tmp_str, tmp_size);


	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return 1;
}

long MQL5::Metatrader5::HistoryOrdersTotal(datetime date_from, datetime date_to)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[28].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[28].second;

	PyObject* py_args = PyTuple_New(2);
	PyObject* py_value = PyLong_FromLongLong(date_from);
	PyTuple_SetItem(py_value, 0, py_value);
	
	py_value = PyLong_FromLongLong(date_to);
	PyTuple_SetItem(py_value, 1, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'history_orders_total'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return -1;
	}

	long ret_value = PyLong_AsLongLong(py_ret_value);

	Py_DECREF(py_args);
	Py_DECREF(py_ret_value);

	return ret_value;
}

long MQL5::Metatrader5::HistoryOrdersGet(datetime date_from, datetime date_to, MqlOrderInfoContainer& orders)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[29].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[29].second;

	PyObject* py_args = PyTuple_New(2);
	PyObject* py_value = PyLong_FromLong(date_from);
	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(date_to);
	PyTuple_SetItem(py_args, 1, py_value);

	PyObject* py_kwargs = PyDict_New();
	py_value = PyUnicode_FromString("*");
	PyDict_SetItemString(py_kwargs, "group", py_value);
	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);
	Py_ssize_t orders_count;

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'history_orders_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);

		return -1;
	}
	else if ((orders_count = PyTuple_GET_SIZE(py_ret_value)) == 0)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);
		Py_DECREF(py_ret_value);

		return 0;
	}
	 
	orders.order_info = new MqlOrderInfo[orders_count];
	orders.size = orders_count;

	Py_ssize_t tmp_size;
	const char* tmp_str;

	for (int i = 0; i < orders_count; ++i)
	{
		MqlOrderInfo& info = orders[i];
		PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, i);
		info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));

		info.time_setup = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
		info.time_setup_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
		info.time_done = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
		info.time_done_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
		info.time_expiration = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
		info.type = (ENUM_ORDER_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
		info.type_time = (ENUM_ORDER_TYPE_TIME)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
		info.type_filling = (ENUM_ORDER_TYPE_FILLING)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
		info.state = (ENUM_ORDER_STATE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 9));
		info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 10));
		info.position_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 11));
		info.position_by_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 12));
		info.reason = (ENUM_ORDER_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 13));
		info.volume_initial = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));
		info.volume_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 15));
		info.price_open = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 16));
		info.sl = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 17));
		info.tp = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 18));
		info.price_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 19));
		info.price_stoplimit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 20));

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 21), &tmp_size);;
		info.symbol = new char[++tmp_size];
		memcpy(info.symbol, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 22), &tmp_size);;
		info.comment = new char[++tmp_size];
		memcpy(info.comment, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 23), &tmp_size);;
		info.external_id = new char[++tmp_size];
		memcpy(info.external_id, tmp_str, tmp_size);
	}

	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return orders_count;
}

long MQL5::Metatrader5::HistoryOrdersGetBySymbol(datetime date_from, datetime date_to, const char* symbol, MqlOrderInfoContainer& orders)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[29].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[29].second;

	PyObject* py_args = PyTuple_New(2);
	PyObject* py_value = PyLong_FromLong(date_from);
	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(date_to);
	PyTuple_SetItem(py_args, 1, py_value);

	PyObject* py_kwargs = PyDict_New();
	py_value = PyUnicode_FromString(symbol);
	PyDict_SetItemString(py_kwargs, "group", py_value);
	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);
	Py_ssize_t orders_count;

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'history_orders_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_DECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);

		return -1;
	}
	else if ((orders_count = PyTuple_GET_SIZE(py_ret_value)) == 0)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);
		Py_DECREF(py_ret_value);

		return 0;
	}

	orders.order_info = new MqlOrderInfo[orders_count];
	orders.size = orders_count;

	Py_ssize_t tmp_size;
	const char* tmp_str;
	
	for (int i = 0; i < orders_count; ++i)
	{
		MqlOrderInfo& info = orders[i];
		PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, i);
		info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));

		info.time_setup = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
		info.time_setup_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
		info.time_done = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
		info.time_done_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
		info.time_expiration = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
		info.type = (ENUM_ORDER_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
		info.type_time = (ENUM_ORDER_TYPE_TIME)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
		info.type_filling = (ENUM_ORDER_TYPE_FILLING)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
		info.state = (ENUM_ORDER_STATE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 9));
		info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 10));
		info.position_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 11));
		info.position_by_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 12));
		info.reason = (ENUM_ORDER_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 13));
		info.volume_initial = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));
		info.volume_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 15));
		info.price_open = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 16));
		info.sl = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 17));
		info.tp = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 18));
		info.price_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 19));
		info.price_stoplimit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 20));

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 21), &tmp_size);;
		info.symbol = new char[++tmp_size];
		memcpy(info.symbol, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 22), &tmp_size);;
		info.comment = new char[++tmp_size];
		memcpy(info.comment, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 23), &tmp_size);;
		info.external_id = new char[++tmp_size];
		memcpy(info.external_id, tmp_str, tmp_size);
	}

	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return orders_count;
}

long MQL5::Metatrader5::HistoryOrdersGetByOrderTicket(datetime date_from, datetime date_to, ulong ticket, MqlOrderInfo& orders)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[29].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[29].second;

	PyObject* py_args = PyTuple_New(2);
	PyObject* py_value = PyLong_FromLong(date_from);
	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(date_to);
	PyTuple_SetItem(py_args, 1, py_value);

	PyObject* py_kwargs = PyDict_New();
	py_value = PyLong_FromLong(ticket);
	PyDict_SetItemString(py_kwargs, "ticket", py_value);
	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);
	Py_ssize_t orders_count;
	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'history_orders_get'\n";
		PyErr_Print();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);
		return -1;
	}
	else if ((orders_count = PyTuple_GET_SIZE(py_ret_value)) == 0)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);
		Py_DECREF(py_ret_value);
		return 0;
	}

	Py_ssize_t tmp_size;
	const char* tmp_str;

	MqlOrderInfo& info = orders;
	PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, 0);
	info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));

	info.time_setup = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
	info.time_setup_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
	info.time_done = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
	info.time_done_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
	info.time_expiration = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
	info.type = (ENUM_ORDER_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
	info.type_time = (ENUM_ORDER_TYPE_TIME)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
	info.type_filling = (ENUM_ORDER_TYPE_FILLING)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
	info.state = (ENUM_ORDER_STATE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 9));
	info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 10));
	info.position_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 11));
	info.position_by_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 12));
	info.reason = (ENUM_ORDER_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 13));
	info.volume_initial = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));
	info.volume_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 15));
	info.price_open = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 16));
	info.sl = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 17));
	info.tp = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 18));
	info.price_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 19));
	info.price_stoplimit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 20));

	tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 21), &tmp_size);;
	info.symbol = new char[++tmp_size];
	memcpy(info.symbol, tmp_str, tmp_size);

	tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 22), &tmp_size);;
	info.comment = new char[++tmp_size];
	memcpy(info.comment, tmp_str, tmp_size);

	tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 23), &tmp_size);;
	info.external_id = new char[++tmp_size];
	memcpy(info.external_id, tmp_str, tmp_size);


	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return orders_count;
}

long MQL5::Metatrader5::HistoryOrdersGetByPositionTicket(datetime date_from, datetime date_to, ulong ticket, MqlOrderInfoContainer& orders)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[29].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[29].second;

	PyObject* py_args = PyTuple_New(2);
	PyObject* py_value = PyLong_FromLong(date_from);
	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(date_to);
	PyTuple_SetItem(py_args, 1, py_value);

	PyObject* py_kwargs = PyDict_New();
	py_value = PyLong_FromLong(ticket);
	PyDict_SetItemString(py_kwargs, "position", py_value);
	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);
	Py_ssize_t orders_count;

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'history_orders_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_DECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);
		
		return -1;
	}
	else if ((orders_count = PyTuple_GET_SIZE(py_ret_value)) == 0)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);
		Py_DECREF(py_ret_value);
		return 0;
	}

	orders.order_info = new MqlOrderInfo[orders_count];
	orders.size = orders_count;

	Py_ssize_t tmp_size;
	const char* tmp_str;

	for (int i = 0; i < orders_count; ++i)
	{
		MqlOrderInfo& info = orders[i];
		PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, i);
		info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));

		info.time_setup = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
		info.time_setup_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
		info.time_done = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
		info.time_done_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
		info.time_expiration = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
		info.type = (ENUM_ORDER_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
		info.type_time = (ENUM_ORDER_TYPE_TIME)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
		info.type_filling = (ENUM_ORDER_TYPE_FILLING)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
		info.state = (ENUM_ORDER_STATE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 9));
		info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 10));
		info.position_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 11));
		info.position_by_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 12));
		info.reason = (ENUM_ORDER_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 13));
		info.volume_initial = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));
		info.volume_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 15));
		info.price_open = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 16));
		info.sl = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 17));
		info.tp = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 18));
		info.price_current = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 19));
		info.price_stoplimit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 20));

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 21), &tmp_size);
		info.symbol = new char[++tmp_size];
		memcpy(info.symbol, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 22), &tmp_size);
		info.comment = new char[++tmp_size];
		memcpy(info.comment, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 23), &tmp_size);
		info.external_id = new char[++tmp_size];
		memcpy(info.external_id, tmp_str, tmp_size);
	}

	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return orders_count;
}

long MQL5::Metatrader5::HistoryDealsTotal(datetime date_from, datetime date_to)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[30].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[30].second;

	PyObject* py_args = PyTuple_New(2);
	PyObject* py_value = PyLong_FromLongLong(date_from);
	PyTuple_SetItem(py_value, 0, py_value);

	py_value = PyLong_FromLongLong(date_to);
	PyTuple_SetItem(py_value, 1, py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'history_deals_total'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return -1;
	}

	long ret_value = PyLong_AsLongLong(py_ret_value);

	Py_DECREF(py_args);
	Py_DECREF(py_ret_value);

	return ret_value;
}

long MQL5::Metatrader5::HistoryDealsGet(datetime date_from, datetime date_to, MqlDealInfoContainer& deals_info)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[31].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[31].second;

	PyObject* py_args = PyTuple_New(2);
	PyObject* py_value = PyLong_FromLong(date_from);
	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(date_to);
	PyTuple_SetItem(py_args, 1, py_value);

	PyObject* py_kwargs = PyDict_New();
	py_value = PyUnicode_FromString("*");
	PyDict_SetItemString(py_kwargs, "group", py_value);
	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);
	Py_ssize_t deals_count;

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'history_orders_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);

		return -1;
	}
	else if ((deals_count = PyTuple_GET_SIZE(py_ret_value)) == 0)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);
		Py_DECREF(py_ret_value);

		return 0;
	}

	deals_info.deal_info = new MqlDealInfo[deals_count];
	deals_info.size = deals_count;

	Py_ssize_t tmp_size;
	const char* tmp_str;

	for (int i = 0; i < deals_count; ++i)
	{
		MqlDealInfo& info = deals_info[i];
		PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, i);

		info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));
		info.order_ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
		info.time = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
		info.time_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
		info.type = (ENUM_DEAL_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
		info.entry = (ENUM_DEAL_ENTRY)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
		info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
		info.position_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
		info.reason = (ENUM_DEAL_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
		info.volume = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 9));
		info.price = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 10));
		info.commission = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 11));
		info.swap = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 12));
		info.profit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 13));
		info.fee = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 15), &tmp_size);;
		info.symbol = new char[++tmp_size];
		memcpy(info.symbol, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 16), &tmp_size);;
		info.comment = new char[++tmp_size];
		memcpy(info.comment, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 17), &tmp_size);;
		info.external_id = new char[++tmp_size];
		memcpy(info.external_id, tmp_str, tmp_size);
	}

	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return deals_count;
}

long MQL5::Metatrader5::HistoryDealsGetBySymbol(datetime date_from, datetime date_to, const char* symbol, MqlDealInfoContainer& deals_info)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[31].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[31].second;

	PyObject* py_args = PyTuple_New(2);
	PyObject* py_value = PyLong_FromLong(date_from);
	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(date_to);
	PyTuple_SetItem(py_args, 1, py_value);

	PyObject* py_kwargs = PyDict_New();
	py_value = PyUnicode_FromString(symbol);
	PyDict_SetItemString(py_kwargs, "group", py_value);
	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);
	Py_ssize_t deals_count;

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'history_orders_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);

		return -1;
	}
	else if ((deals_count = PyTuple_GET_SIZE(py_ret_value)) == 0)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);
		Py_DECREF(py_ret_value);

		return 0;
	}

	deals_info.deal_info = new MqlDealInfo[deals_count];
	deals_info.size = deals_count;

	Py_ssize_t tmp_size;
	const char* tmp_str;

	for (int i = 0; i < deals_count; ++i)
	{
		MqlDealInfo& info = deals_info[i];
		PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, i);

		info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));
		info.order_ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
		info.time = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
		info.time_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
		info.type = (ENUM_DEAL_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
		info.entry = (ENUM_DEAL_ENTRY)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
		info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
		info.position_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
		info.reason = (ENUM_DEAL_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
		info.volume = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 9));
		info.price = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 10));
		info.commission = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 11));
		info.swap = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 12));
		info.profit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 13));
		info.fee = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 15), &tmp_size);;
		info.symbol = new char[++tmp_size];
		memcpy(info.symbol, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 16), &tmp_size);;
		info.comment = new char[++tmp_size];
		memcpy(info.comment, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 17), &tmp_size);;
		info.external_id = new char[++tmp_size];
		memcpy(info.external_id, tmp_str, tmp_size);
	}

	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return deals_count;
}

long MQL5::Metatrader5::HistoryDealsGetByOrderTicket(datetime date_from, datetime date_to, ulong ticket, MqlDealInfoContainer& deals_info)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[31].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[31].second;

	PyObject* py_args = PyTuple_New(2);
	PyObject* py_value = PyLong_FromLong(date_from);
	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(date_to);
	PyTuple_SetItem(py_args, 1, py_value);

	PyObject* py_kwargs = PyDict_New();
	py_value =  PyLong_FromUnsignedLongLong(ticket);
	PyDict_SetItemString(py_kwargs, "group", py_value);
	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);
	Py_ssize_t deals_count;

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'history_orders_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);

		return -1;
	}
	else if ((deals_count = PyTuple_GET_SIZE(py_ret_value)) == 0)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);
		Py_DECREF(py_ret_value);

		return 0;
	}

	deals_info.deal_info = new MqlDealInfo[deals_count];
	deals_info.size = deals_count;

	Py_ssize_t tmp_size;
	const char* tmp_str;

	for (int i = 0; i < deals_count; ++i)
	{
		MqlDealInfo& info = deals_info[i];
		PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, i);

		info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));
		info.order_ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
		info.time = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
		info.time_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
		info.type = (ENUM_DEAL_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
		info.entry = (ENUM_DEAL_ENTRY)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
		info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
		info.position_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
		info.reason = (ENUM_DEAL_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
		info.volume = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 9));
		info.price = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 10));
		info.commission = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 11));
		info.swap = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 12));
		info.profit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 13));
		info.fee = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 15), &tmp_size);;
		info.symbol = new char[++tmp_size];
		memcpy(info.symbol, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 16), &tmp_size);;
		info.comment = new char[++tmp_size];
		memcpy(info.comment, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 17), &tmp_size);;
		info.external_id = new char[++tmp_size];
		memcpy(info.external_id, tmp_str, tmp_size);
	}

	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return deals_count;
}

long MQL5::Metatrader5::HistoryDealsGetByPositionTicket(datetime date_from, datetime date_to, ulong ticket, MqlDealInfoContainer& deals_info)
{
	static PyObject*& py_fn = PY_FUNC_TABLE[31].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[31].second;

	PyObject* py_args = PyTuple_New(2);
	PyObject* py_value = PyLong_FromLong(date_from);
	PyTuple_SetItem(py_args, 0, py_value);

	py_value = PyLong_FromLong(date_to);
	PyTuple_SetItem(py_args, 1, py_value);

	PyObject* py_kwargs = PyDict_New();
	py_value = PyLong_FromUnsignedLongLong(ticket);
	PyDict_SetItemString(py_kwargs, "position", py_value);
	Py_XDECREF(py_value);

	PyObject* py_ret_value = fn(py_fn, py_args, py_kwargs);
	Py_ssize_t deals_count;

	if (PyErr_Occurred())
	{
		std::cout << "Couldn't call the function 'history_orders_get'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_kwargs);
		Py_XDECREF(py_ret_value);

		return -1;
	}
	else if (py_ret_value == Py_None)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);

		return -1;
	}
	else if ((deals_count = PyTuple_GET_SIZE(py_ret_value)) == 0)
	{
		Py_DECREF(py_args);
		Py_DECREF(py_kwargs);
		Py_DECREF(py_ret_value);

		return 0;
	}

	deals_info.deal_info = new MqlDealInfo[deals_count];
	deals_info.size = deals_count;

	Py_ssize_t tmp_size;
	const char* tmp_str;

	for (int i = 0; i < deals_count; ++i)
	{
		MqlDealInfo& info = deals_info[i];
		PyObject* py_order_tuple = PyTuple_GetItem(py_ret_value, i);

		info.ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 0));
		info.order_ticket = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 1));
		info.time = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 2));
		info.time_msc = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 3));
		info.type = (ENUM_DEAL_TYPE)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 4));
		info.entry = (ENUM_DEAL_ENTRY)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 5));
		info.magic = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 6));
		info.position_id = PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 7));
		info.reason = (ENUM_DEAL_REASON)PyLong_AsLongLong(PyTuple_GetItem(py_order_tuple, 8));
		info.volume = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 9));
		info.price = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 10));
		info.commission = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 11));
		info.swap = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 12));
		info.profit = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 13));
		info.fee = PyFloat_AsDouble(PyTuple_GetItem(py_order_tuple, 14));

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 15), &tmp_size);;
		info.symbol = new char[++tmp_size];
		memcpy(info.symbol, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 16), &tmp_size);;
		info.comment = new char[++tmp_size];
		memcpy(info.comment, tmp_str, tmp_size);

		tmp_str = PyUnicode_AsUTF8AndSize(PyTuple_GetItem(py_order_tuple, 17), &tmp_size);;
		info.external_id = new char[++tmp_size];
		memcpy(info.external_id, tmp_str, tmp_size);
	}

	Py_DECREF(py_args);
	Py_DECREF(py_kwargs);
	Py_DECREF(py_ret_value);

	return deals_count;
}

void MQL5::Metatrader5::Release(MqlObject& obj)
{
	Py_XDECREF(obj.object);
	obj.object = nullptr;
	obj.elem_count = 0;
}

void MQL5::Metatrader5::Release(MqlErrorInfo& error_info)
{
	DEL_STRING(error_info.desc);
	ZERO_MEM(error_info);
}

void MQL5::Metatrader5::Release(MqlVersionInfo& version_info)
{
	DEL_STRING(version_info.date);
	ZERO_MEM(version_info);
}

void MQL5::Metatrader5::Release(MqlAccountInfo& account_info)
{
	DEL_STRING(account_info.name);
	DEL_STRING(account_info.server);
	DEL_STRING(account_info.currency);
	DEL_STRING(account_info.company);
	ZERO_MEM(account_info);
}

void MQL5::Metatrader5::Release(MqlSymbolInfo& symbol_info)
{
	DEL_STRING(symbol_info.basis);
	DEL_STRING(symbol_info.category);
	DEL_STRING(symbol_info.currency_base);
	DEL_STRING(symbol_info.currency_profit);
	DEL_STRING(symbol_info.currency_margin);
	DEL_STRING(symbol_info.bank);
	DEL_STRING(symbol_info.description);
	DEL_STRING(symbol_info.exchange);
	DEL_STRING(symbol_info.formula);
	DEL_STRING(symbol_info.isin);
	DEL_STRING(symbol_info.name);
	DEL_STRING(symbol_info.page);
	DEL_STRING(symbol_info.path);
	ZERO_MEM(symbol_info);
}

void MQL5::Metatrader5::Release(MqlTick& tick)
{
	ZERO_MEM(tick);
}

void MQL5::Metatrader5::Release(MqlRates& rates)
{
	ZERO_MEM(rates);
}

void MQL5::Metatrader5::Release(MqlTradeRequest& request)
{
	DEL_STRING(request.symbol);
	DEL_STRING(request.comment);
	ZERO_MEM(request);
}

void MQL5::Metatrader5::Release(MqlTradeResult& result)
{
	DEL_STRING(result.comment);
	ZERO_MEM(result);
}

void MQL5::Metatrader5::Release(MqlBookInfo& book_info)
{
	ZERO_MEM(book_info);
}

void MQL5::Metatrader5::Release(MqlOrderInfo& order_info)
{
	DEL_STRING(order_info.symbol);
	DEL_STRING(order_info.comment);
	DEL_STRING(order_info.external_id);
	ZERO_MEM(order_info);
}

void MQL5::Metatrader5::Release(MqlPositionInfo& position_info)
{
	DEL_STRING(position_info.symbol);
	DEL_STRING(position_info.comment);
	DEL_STRING(position_info.external_id);
	ZERO_MEM(position_info);
}

void MQL5::Metatrader5::Release(MqlTickContainer& ticks)
{
	Release(ticks.mql_object);
}

void MQL5::Metatrader5::Release(MqlRatesContainer& rates)
{
	Release(rates.mql_object);
}

bool MQL5::Metatrader5::Shutdown()
{
	static PyObject*& py_fn = PY_FUNC_TABLE[2].first;
	static PyCFunctionWithKeywords& fn = PY_FUNC_TABLE[2].second;

	PyObject* py_args = PyTuple_New(0);

	PyObject* py_ret_value = fn(py_fn, py_args, NULL);

	if (PyErr_Occurred())
	{
		std::cout << ">>> Couldn't call the function 'shutdown'\n";

		PyErr_Print();
		PyErr_Clear();

		Py_XDECREF(py_args);
		Py_XDECREF(py_ret_value);

		return false;
	}

	Py_DECREF(py_args);
	Py_DECREF(py_ret_value);

	if (Py_FinalizeEx() < 0) {
		return false;
	}

	return true;
}

void MQL5::Metatrader5::MemFree(void* ptr)
{
	delete[] ptr;
}

void MQL5::Metatrader5::CTrade::SetSymbol(std::string symbol)
{
	mSymbol = std::move(symbol);
	mRequest.symbol = mSymbol.data();
}

void MQL5::Metatrader5::CTrade::SetMagic(ulong magic)
{
	mRequest.magic = magic;
}

void MQL5::Metatrader5::CTrade::SetFillingType(ENUM_ORDER_TYPE_FILLING type_filling)
{
	mRequest.type_filling = type_filling;
}

MQL5::Metatrader5::CTrade::CTrade()
{
	pZeroRequest();
	pZeroResult();
}

MQL5::Metatrader5::CTrade::CTrade(std::string symbol)
{
	pZeroRequest();
	pZeroResult();

	mSymbol = std::move(symbol);
	mRequest.symbol = mSymbol.data();

}

bool MQL5::Metatrader5::CTrade::Buy(double tp, double sl, double volume, ulong deviation, const std::string& comment)
{
	mRequest.action = TRADE_ACTION_DEAL;
	mRequest.type = ORDER_TYPE_BUY;
	mRequest.deviation = deviation;
	mRequest.tp = tp;
	mRequest.sl = sl;
	mRequest.volume = volume;

	mRequest.price = 0;
	mRequest.expiration = 0;
	mRequest.order = 0;
	mRequest.position = 0;
	mRequest.position_by = 0;
	mRequest.stoplimit = 0;

	mComment = comment;
	mRequest.comment = mComment.data();

	return OrderSend(mRequest, mResult);
}

bool MQL5::Metatrader5::CTrade::Sell(double tp, double sl, double volume, ulong deviation, const std::string& comment)
{
	mRequest.action = TRADE_ACTION_DEAL;
	mRequest.type = ORDER_TYPE_SELL;
	mRequest.deviation = deviation;
	mRequest.tp = tp;
	mRequest.sl = sl;
	mRequest.volume = volume;

	mRequest.price = 0;
	mRequest.expiration = 0;
	mRequest.order = 0;
	mRequest.position = 0;
	mRequest.position_by = 0;
	mRequest.stoplimit = 0;

	mComment = comment;
	mRequest.comment = mComment.data();

	return OrderSend(mRequest, mResult);
}

bool MQL5::Metatrader5::CTrade::BuyLimit(double price, double tp, double sl, double volume, ulong deviation, const std::string& comment)
{
	mRequest.action = TRADE_ACTION_PENDING;
	mRequest.type = ORDER_TYPE_BUY_LIMIT;
	mRequest.deviation = deviation;
	mRequest.tp = tp;
	mRequest.sl = sl;
	mRequest.volume = volume;
	mRequest.price = price;

	mRequest.expiration = 0;
	mRequest.order = 0;
	mRequest.position = 0;
	mRequest.position_by = 0;
	mRequest.stoplimit = 0;

	mComment = comment;
	mRequest.comment = mComment.data();

	return OrderSend(mRequest, mResult);
}

bool MQL5::Metatrader5::CTrade::SellLimit(double price, double tp, double sl, double volume, ulong deviation, const std::string& comment)
{
	mRequest.action = TRADE_ACTION_PENDING;
	mRequest.type = ORDER_TYPE_SELL_LIMIT;
	mRequest.deviation = deviation;
	mRequest.tp = tp;
	mRequest.sl = sl;
	mRequest.volume = volume;
	mRequest.price = price;

	mRequest.expiration = 0;
	mRequest.order = 0;
	mRequest.position = 0;
	mRequest.position_by = 0;
	mRequest.stoplimit = 0;

	mComment = comment;
	mRequest.comment = mComment.data();

	return OrderSend(mRequest, mResult);
}

bool MQL5::Metatrader5::CTrade::BuyStop(double trigger_price, double tp, double sl, double volume, ulong deviation, const std::string& comment)
{
	mRequest.action = TRADE_ACTION_PENDING;
	mRequest.type = ORDER_TYPE_BUY_STOP;
	mRequest.deviation = deviation;
	mRequest.tp = tp;
	mRequest.sl = sl;
	mRequest.volume = volume;
	mRequest.price = 0;
	mRequest.stoplimit = trigger_price;

	mRequest.expiration = 0;
	mRequest.order = 0;
	mRequest.position = 0;
	mRequest.position_by = 0;
	mRequest.stoplimit = 0;

	mComment = comment;
	mRequest.comment = mComment.data();

	return OrderSend(mRequest, mResult);
}

bool MQL5::Metatrader5::CTrade::SellStop(double trigger_price, double tp, double sl, double volume, ulong deviation, const std::string& comment)
{
	mRequest.action = TRADE_ACTION_PENDING;
	mRequest.type = ORDER_TYPE_SELL_STOP;
	mRequest.deviation = deviation;
	mRequest.tp = tp;
	mRequest.sl = sl;
	mRequest.volume = volume;
	mRequest.price = 0;
	mRequest.stoplimit = trigger_price;

	mRequest.expiration = 0;
	mRequest.order = 0;
	mRequest.position = 0;
	mRequest.position_by = 0;
	mRequest.stoplimit = 0;

	mComment = comment;
	mRequest.comment = mComment.data();

	return OrderSend(mRequest, mResult);
}

uint MQL5::Metatrader5::CTrade::ResultRetCode()
{
	return mResult.retcode;
}

ulong MQL5::Metatrader5::CTrade::ResultOrder()
{
	return mResult.order;
}

ulong MQL5::Metatrader5::CTrade::ResultDeal()
{
	return mResult.deal;
}

void MQL5::Metatrader5::CTrade::pZeroRequest()
{
	mRequest.action = TRADE_ACTION_DEAL;
	mRequest.deviation = 0;
	mRequest.expiration = 0;
	mRequest.magic = 0;
	mRequest.order = 0;
	mRequest.position = 0;
	mRequest.position_by = 0;
	mRequest.price = 0;
	mRequest.sl = 0;
	mRequest.stoplimit = 0;
	mRequest.tp = 0;
	mRequest.type = ORDER_TYPE_BUY;
	mRequest.type_filling = ORDER_FILLING_RETURN;
	mRequest.type_time = ORDER_TIME_GTC;
	mRequest.volume = 0;
}

void MQL5::Metatrader5::CTrade::pZeroResult()
{
	mResult.ask = 0;
	mResult.bid = 0;
	mResult.deal = 0;
	mResult.order = 0;
	mResult.price = 0;
	mResult.request_id = 0;
	mResult.retcode = 0;
	mResult.retcode_external = 0;
	mResult.volume = 0;
}

std::string MQL5::Utils::TimeToString(uint64_t time)
{
	char buffer[64];

	std::time_t conv_time = time;

	std::tm conv{};
	gmtime_s(&conv, &conv_time);

	std::strftime(buffer, 64, "%d.%m.%Y %H:%M:%S", &conv);

	return std::string(buffer);
}

uint64_t MQL5::Utils::CStrToDatetime(const char* chr)
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

	return now_time - mql_epoch_time;
}

datetime MQL5::Utils::GetCurrentTime()
{
	static const auto p0 = std::chrono::system_clock::from_time_t(mql_epoch_time);
	const auto p1 = std::chrono::system_clock::now();

	const auto p2 = p1 - p0;

	return (datetime)std::chrono::duration_cast<std::chrono::seconds>(p2).count();
}

PyObject* MQL5::Utils::GetAttr(PyObject* mod, const std::string& fn_name)
{
	PyObject* fn = PyObject_GetAttrString(mod, fn_name.c_str());

	if (fn == nullptr)
	{
		PyErr_Print();
		PyErr_Clear();
		return nullptr;
	}

	return fn;
}

PyObject* MQL5::Utils::GetNumPyArrItem(PyObject* nparr, int arr_size, int bytes_size, int index)
{
	char*& array_start = PyArray_BYTES(nparr);

	return PyArray_GETITEM(nparr, array_start + (bytes_size / arr_size * index));
}

void MQL5::Utils::ZeroMemory(void* ptr, size_t size)
{
	memset(ptr, 0, size);
}
