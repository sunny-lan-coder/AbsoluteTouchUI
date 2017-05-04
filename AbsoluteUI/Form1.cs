using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AbsoluteUI
{
    public partial class Form1 : Form
    {
        KeyboardHook hk;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            hk = new KeyboardHook();
            hk.KeyPressed += hotKeyPressed;
            txtCmb.GotFocus += txtFocused;
            txtCmb.LostFocus += txtLostFocus;
        }

        private bool registered = false;

        private void txtLostFocus(object sender, EventArgs e)
        {
            register();
        }

        private void register()
        {
            if (t != null && !registered)
            {
                hk.RegisterHotKey(mod, t ?? default(Keys));
                registered = true;
            }
        }

        private void txtFocused(object sender, EventArgs e)
        {
            hk.ClearHotkeys();
            registered = false;
        }

        private void hotKeyPressed(object sender, KeyPressedEventArgs e)
        {
            toggle();
        }

        private bool runnning = false;

        private Process absProc;

        private void start()
        {
            if (runnning)
                return;
            absProc = new Process();
            absProc.StartInfo.RedirectStandardOutput = true;
            absProc.StartInfo.UseShellExecute = false;
            absProc.StartInfo.CreateNoWindow = true;
            absProc.StartInfo.FileName = "AbsoluteTouch.exe";
            absProc.StartInfo.Arguments = string.Format(" -t {0},{1},{2},{3}", tX.Value, tY.Value, tX.Value + tW.Value, tY.Value + tH.Value);
            absProc.StartInfo.Arguments += string.Format(" -s {0},{1},{2},{3}", sX.Value, sY.Value, sX.Value + sW.Value, sY.Value + sH.Value);
            absProc.StartInfo.Arguments += string.Format(" -w {0}", w.Value);
            if (chkL.Checked)
                absProc.StartInfo.Arguments += " -c";
            absProc.Start();
            btnToggle.Text = "Stop";
            runnning = true;
        }

        private void stop()
        {
            if (!runnning)
                return;
            absProc.Kill();
            btnToggle.Text = "Start";
            runnning = false;
        }

        private void btnToggle_Click(object sender, EventArgs e)
        {
            toggle();
        }

        private void toggle()
        {
            if (runnning)
                stop();
            else
                start();
        }

        private ModifierKeys mod;
        private Keys? t = null;

        private void txtCmb_KeyDown(object sender, KeyEventArgs e)
        {
            hk.ClearHotkeys();
            registered = false;
            mod = 0;
            txtCmb.Text = "";
            if (e.Control)
            {
                mod |= AbsoluteUI.ModifierKeys.Control;
                txtCmb.Text += "CTRL ";
            }

            if (e.Alt)
            {
                mod |= AbsoluteUI.ModifierKeys.Alt;
                txtCmb.Text += "ALT ";
            }

            if (e.Shift)
            {
                mod |= AbsoluteUI.ModifierKeys.Shift;
                txtCmb.Text += "SHIFT ";
            }

            t = e.KeyCode;

            txtCmb.Text += t.ToString();

        }

        private void btnExit_Click(object sender, EventArgs e)
        {
            this.Close();
            Application.Exit();
            Environment.Exit(0);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
            hk.ClearHotkeys();
            registered = false;
            stop();
        }

        private void notifyIcon1_DoubleClick(object sender, EventArgs e)
        {
            this.Show();
        }

        private void txtCmb_KeyUp(object sender, KeyEventArgs e)
        {
            register();
            btnToggle.Focus();
        }
    }
}
