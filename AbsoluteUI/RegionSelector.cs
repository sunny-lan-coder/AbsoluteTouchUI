using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AbsoluteUI
{

    public partial class RegionSelector : Form
    {
        public static Rectangle showDialog(decimal x, decimal y, decimal w, decimal h)
        {
            RegionSelector s = new RegionSelector();
            Rectangle d = s.GetScreen();
            s.KeyPress += (sender, e) =>
            {
                if (e.KeyChar == 's')
                    s.Close();
                if (e.KeyChar == 'c')
                    s.Location = new Point(d.Width / 2 - s.Width / 2, d.Height/2 - s.Height / 2);

            };
            s.Shown += (sender, e) =>
            {
                s.Location = new Point((int)((double)x / 100.0 * d.Width), (int)((double)y / 100.0 * d.Height));
                s.Width = (int)((double)w / 100.0 * d.Width);
            };
            s.Height = (int)((double)h / 100.0 * d.Height);

            s.ShowDialog();

            Rectangle t = s.ClientRectangle;
            Rectangle res = new Rectangle(s.Location.X * 100 / d.Width, s.Location.Y * 100 / d.Height, t.Width * 100 / d.Width, t.Height * 100 / d.Height);
            return res;
        }

        public RegionSelector()
        {
            InitializeComponent();
            this.FormBorderStyle = FormBorderStyle.None;
            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.ResizeRedraw, true);
            sf = new StringFormat();
            sf.LineAlignment = StringAlignment.Center;
            sf.Alignment = StringAlignment.Center;


        }
        private StringFormat sf;
        private const int cGrip = 16;
        private const int pw = 5;

        private Font f = new Font(FontFamily.GenericSansSerif, 70);

        public Rectangle GetScreen()
        {
            return Screen.FromControl(this).Bounds;
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Rectangle rc = new Rectangle(this.ClientSize.Width - cGrip, this.ClientSize.Height - cGrip, cGrip, cGrip);
            Pen p = new Pen(Brushes.Blue, pw);
            e.Graphics.DrawString("'s' to finish\n'c' to center", f, Brushes.Blue, ClientRectangle, sf);
            e.Graphics.DrawRectangle(p, new Rectangle(this.ClientRectangle.X, this.ClientRectangle.Y, this.ClientSize.Width - pw / 2, this.ClientSize.Height - pw / 2));
            ControlPaint.DrawSizeGrip(e.Graphics, this.BackColor, rc);
        }

        protected override void WndProc(ref Message m)
        {
            if (m.Msg == 0x216)
            { // Trap WM_MOVING
                RECT rc = (RECT)Marshal.PtrToStructure(m.LParam, typeof(RECT));
                Screen scr = Screen.FromControl(this);
                if (rc.left < scr.WorkingArea.Left) { rc.left = scr.WorkingArea.Left; rc.right = rc.left + this.Width; }
                if (rc.top < scr.WorkingArea.Top) { rc.top = scr.WorkingArea.Top; rc.bottom = rc.top + this.Height; }
                if (rc.right > scr.WorkingArea.Right) { rc.right = scr.WorkingArea.Right; rc.left = rc.right - this.Width; }
                if (rc.bottom > scr.WorkingArea.Bottom) { rc.bottom = scr.WorkingArea.Bottom; rc.top = rc.bottom - this.Height; }
                Marshal.StructureToPtr(rc, m.LParam, false);
            }
            if (m.Msg == 0x84)
            {  // Trap WM_NCHITTEST
                Point pos = new Point(m.LParam.ToInt32() & 0xffff, m.LParam.ToInt32() >> 16);
                pos = this.PointToClient(pos);

                if (pos.X >= this.ClientSize.Width - cGrip && pos.Y >= this.ClientSize.Height - cGrip)
                {
                    m.Result = (IntPtr)17; // HTBOTTOMRIGHT
                    return;
                }
                m.Result = (IntPtr)2;  // HTCAPTION
                return;
            }
            base.WndProc(ref m);
        }
        private struct RECT
        {
            public int left;
            public int top;
            public int right;
            public int bottom;
        }
    }
}
