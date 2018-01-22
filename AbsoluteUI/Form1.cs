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

        bool doHide = false;

        private void Form1_Load(object sender, EventArgs e)
        {
            hk = new KeyboardHook();
            hk.KeyPressed += hotKeyPressed;
            txtCmb.GotFocus += txtFocused;
            txtCmb.LostFocus += txtLostFocus;

            try
            {
                Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
                mod = (ModifierKeys)Convert.ToUInt32(exampleRegistryKey.GetValue("Modifier"));
                t = (Keys)Convert.ToInt32(exampleRegistryKey.GetValue("Keys"));
                tX.Value =Convert.ToDecimal( exampleRegistryKey.GetValue("tX"));
                tY.Value = Convert.ToDecimal(exampleRegistryKey.GetValue("tY"));
                tW.Value = Convert.ToDecimal(exampleRegistryKey.GetValue("tW"));
                tH.Value = Convert.ToDecimal(exampleRegistryKey.GetValue("tH"));
                sX.Value = Convert.ToDecimal(exampleRegistryKey.GetValue("sX"));
                sY.Value = Convert.ToDecimal(exampleRegistryKey.GetValue("sY"));
                sW.Value = Convert.ToDecimal(exampleRegistryKey.GetValue("sW"));
                sH.Value = Convert.ToDecimal(exampleRegistryKey.GetValue("sH"));
                w.Value = Convert.ToDecimal(exampleRegistryKey.GetValue("w"));
                chkL.Checked = Convert.ToBoolean(exampleRegistryKey.GetValue("chkL"));
                register();
                doHide = true;
            }
            catch (Exception ex)
            {
                Console.WriteLine("Could not load keys");
            }
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
                Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
                exampleRegistryKey.SetValue("Modifier", (uint)mod);
                exampleRegistryKey.SetValue("Keys", (int)t);

                hk.RegisterHotKey(mod, t ?? default(Keys));
                exampleRegistryKey.Close();
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
            stop();
            hk.ClearHotkeys();
            registered = false;
            this.Close();
            Application.Exit();
            Environment.Exit(0);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Hide();
            e.Cancel = true;
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

        private void Form1_Shown(object sender, EventArgs e)
        {
            if (doHide)
                Hide();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Rectangle r = RegionSelector.showDialog(tX.Value,tY.Value, tW.Value, tH.Value);
            tX.Value = r.X;
            tY.Value = r.Y;
            tW.Value = r.Width;
            tH.Value = r.Height;
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Rectangle r = RegionSelector.showDialog(sX.Value, sY.Value, sW.Value, sH.Value);
            sX.Value = r.X;
            sY.Value = r.Y;
            sW.Value = r.Width;
            sH.Value = r.Height;
        }

        private void tX_ValueChanged(object sender, EventArgs e)
        {
            Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
            exampleRegistryKey.SetValue("tX", tX.Value);
            exampleRegistryKey.Close();
        }

        private void tY_ValueChanged(object sender, EventArgs e)
        {
            Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
            exampleRegistryKey.SetValue("tY", tY.Value);
            exampleRegistryKey.Close();
        }

        private void tW_ValueChanged(object sender, EventArgs e)
        {
            Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
            exampleRegistryKey.SetValue("tW", tW.Value);
            exampleRegistryKey.Close();
        }

        private void tH_ValueChanged(object sender, EventArgs e)
        {
            Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
            exampleRegistryKey.SetValue("tH", tH.Value);
            exampleRegistryKey.Close();
        }

        private void sX_ValueChanged(object sender, EventArgs e)
        {
            Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
            exampleRegistryKey.SetValue("sX", sX.Value);
            exampleRegistryKey.Close();
        }

        private void sY_ValueChanged(object sender, EventArgs e)
        {

            Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
            exampleRegistryKey.SetValue("sY", sY.Value);
            exampleRegistryKey.Close();
        }

        private void sW_ValueChanged(object sender, EventArgs e)
        {
            Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
            exampleRegistryKey.SetValue("sW", sW.Value);
            exampleRegistryKey.Close();

        }

        private void sH_ValueChanged(object sender, EventArgs e)
        {
            Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
            exampleRegistryKey.SetValue("sH", sH.Value);
            exampleRegistryKey.Close();
        }

        private void w_ValueChanged(object sender, EventArgs e)
        {
            Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
            exampleRegistryKey.SetValue("w", w.Value);
            exampleRegistryKey.Close();
        }

        private void chkL_CheckedChanged(object sender, EventArgs e)
        {
            Microsoft.Win32.RegistryKey exampleRegistryKey = Microsoft.Win32.Registry.CurrentUser.CreateSubKey("AbsoluteTouch");
            exampleRegistryKey.SetValue("chkL", chkL.Checked);
            exampleRegistryKey.Close();
        }
    }
}
