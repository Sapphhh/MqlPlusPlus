using MQL;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Reflection.Emit;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SharpMQ_UI
{
    /*This form is used to send a buy order to the symbol selected in the combobox*/
    public partial class Form2 : Form
    {

        public Form2()
        {
            InitializeComponent();
        }

        unsafe private void button2_Click(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex == -1)
            {
                return;
            }

            MqlTradeRequest req = new MqlTradeRequest();
            req.action = ENUM_TRADE_REQUEST_ACTION.TRADE_ACTION_DEAL;
            req.type = ENUM_ORDER_TYPE.ORDER_TYPE_BUY;
            req.magic = 123;
            req.type_filling = ENUM_ORDER_TYPE_FILLING.ORDER_FILLING_IOC;
            req.volume = 0.01;
            req.symbol = (IntPtr)MqlString.ToCStr(comboBox1.SelectedItem.ToString());

            MqlTradeResult res = new MqlTradeResult();

            Methods.OrderSend(ref req, ref res);

            MqlString.Release((void*)req.symbol);

            MqlTick tick = new MqlTick();

            Methods.SymbolInfoTick(comboBox1.SelectedItem.ToString(), ref tick);

            label4.Text = "Bid: " + tick.bid;
            label5.Text = "Ask: " + tick.ask;
            label6.Text = "Time: " + tick.time;
        }

        private void Form2_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            MqlSymbolInfoContainer symbols = new MqlSymbolInfoContainer();

            long total = Methods.SymbolsGet("*", ref symbols);

            if (total < 0)
            {
                return;
            }

            for (long i = 0; i < total; ++i)
            {
                //MqlString str = MqlString.FromPtr(symbols[i].name);
                comboBox1.Items.Add(MqlString.FromBytePtr(symbols[i].name));
            }

            Methods.Release(ref symbols);
        }
    }
}
