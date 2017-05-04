namespace AbsoluteUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
            this.btnToggle = new System.Windows.Forms.Button();
            this.btnExit = new System.Windows.Forms.Button();
            this.txtCmb = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.tX = new System.Windows.Forms.NumericUpDown();
            this.tY = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.tW = new System.Windows.Forms.NumericUpDown();
            this.label5 = new System.Windows.Forms.Label();
            this.tH = new System.Windows.Forms.NumericUpDown();
            this.label6 = new System.Windows.Forms.Label();
            this.sH = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.sW = new System.Windows.Forms.NumericUpDown();
            this.label8 = new System.Windows.Forms.Label();
            this.sY = new System.Windows.Forms.NumericUpDown();
            this.label9 = new System.Windows.Forms.Label();
            this.sX = new System.Windows.Forms.NumericUpDown();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.w = new System.Windows.Forms.NumericUpDown();
            this.label12 = new System.Windows.Forms.Label();
            this.chkL = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.tX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.tH)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.sH)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.sW)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.sY)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.sX)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.w)).BeginInit();
            this.SuspendLayout();
            // 
            // notifyIcon1
            // 
            this.notifyIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon1.Icon")));
            this.notifyIcon1.Text = "notifyIcon1";
            this.notifyIcon1.Visible = true;
            this.notifyIcon1.DoubleClick += new System.EventHandler(this.notifyIcon1_DoubleClick);
            // 
            // btnToggle
            // 
            this.btnToggle.Location = new System.Drawing.Point(12, 12);
            this.btnToggle.Name = "btnToggle";
            this.btnToggle.Size = new System.Drawing.Size(377, 99);
            this.btnToggle.TabIndex = 0;
            this.btnToggle.Text = "Start";
            this.btnToggle.UseVisualStyleBackColor = true;
            this.btnToggle.Click += new System.EventHandler(this.btnToggle_Click);
            // 
            // btnExit
            // 
            this.btnExit.Location = new System.Drawing.Point(15, 340);
            this.btnExit.Name = "btnExit";
            this.btnExit.Size = new System.Drawing.Size(377, 50);
            this.btnExit.TabIndex = 1;
            this.btnExit.Text = "Exit";
            this.btnExit.UseVisualStyleBackColor = true;
            this.btnExit.Click += new System.EventHandler(this.btnExit_Click);
            // 
            // txtCmb
            // 
            this.txtCmb.Location = new System.Drawing.Point(15, 143);
            this.txtCmb.Name = "txtCmb";
            this.txtCmb.Size = new System.Drawing.Size(374, 20);
            this.txtCmb.TabIndex = 3;
            this.txtCmb.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtCmb_KeyDown);
            this.txtCmb.KeyUp += new System.Windows.Forms.KeyEventHandler(this.txtCmb_KeyUp);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 125);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(143, 15);
            this.label1.TabIndex = 4;
            this.label1.Text = "Toggle key combination: ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 184);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(145, 15);
            this.label2.TabIndex = 5;
            this.label2.Text = "Mapped touchpad region";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 206);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(18, 15);
            this.label3.TabIndex = 6;
            this.label3.Text = "X:";
            // 
            // tX
            // 
            this.tX.Location = new System.Drawing.Point(36, 204);
            this.tX.Name = "tX";
            this.tX.Size = new System.Drawing.Size(54, 20);
            this.tX.TabIndex = 7;
            // 
            // tY
            // 
            this.tY.Location = new System.Drawing.Point(126, 204);
            this.tY.Name = "tY";
            this.tY.Size = new System.Drawing.Size(54, 20);
            this.tY.TabIndex = 9;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(102, 206);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(17, 15);
            this.label4.TabIndex = 8;
            this.label4.Text = "Y:";
            // 
            // tW
            // 
            this.tW.Location = new System.Drawing.Point(220, 204);
            this.tW.Name = "tW";
            this.tW.Size = new System.Drawing.Size(54, 20);
            this.tW.TabIndex = 11;
            this.tW.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(196, 206);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(21, 15);
            this.label5.TabIndex = 10;
            this.label5.Text = "W:";
            // 
            // tH
            // 
            this.tH.Location = new System.Drawing.Point(319, 204);
            this.tH.Name = "tH";
            this.tH.Size = new System.Drawing.Size(54, 20);
            this.tH.TabIndex = 13;
            this.tH.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(295, 206);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(19, 15);
            this.label6.TabIndex = 12;
            this.label6.Text = "H:";
            // 
            // sH
            // 
            this.sH.Location = new System.Drawing.Point(319, 259);
            this.sH.Name = "sH";
            this.sH.Size = new System.Drawing.Size(54, 20);
            this.sH.TabIndex = 22;
            this.sH.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(295, 261);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(19, 15);
            this.label7.TabIndex = 21;
            this.label7.Text = "H:";
            // 
            // sW
            // 
            this.sW.Location = new System.Drawing.Point(220, 259);
            this.sW.Name = "sW";
            this.sW.Size = new System.Drawing.Size(54, 20);
            this.sW.TabIndex = 20;
            this.sW.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(196, 261);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(21, 15);
            this.label8.TabIndex = 19;
            this.label8.Text = "W:";
            // 
            // sY
            // 
            this.sY.Location = new System.Drawing.Point(126, 259);
            this.sY.Name = "sY";
            this.sY.Size = new System.Drawing.Size(54, 20);
            this.sY.TabIndex = 18;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(102, 261);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(17, 15);
            this.label9.TabIndex = 17;
            this.label9.Text = "Y:";
            // 
            // sX
            // 
            this.sX.Location = new System.Drawing.Point(36, 259);
            this.sX.Name = "sX";
            this.sX.Size = new System.Drawing.Size(54, 20);
            this.sX.TabIndex = 16;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(12, 261);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(18, 15);
            this.label10.TabIndex = 15;
            this.label10.Text = "X:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(12, 239);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(131, 15);
            this.label11.TabIndex = 14;
            this.label11.Text = "Mapped screen region";
            // 
            // w
            // 
            this.w.Location = new System.Drawing.Point(126, 304);
            this.w.Name = "w";
            this.w.Size = new System.Drawing.Size(54, 20);
            this.w.TabIndex = 24;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(12, 306);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(103, 15);
            this.label12.TabIndex = 23;
            this.label12.Text = "Smoothing factor:";
            // 
            // chkL
            // 
            this.chkL.AutoSize = true;
            this.chkL.Location = new System.Drawing.Point(199, 304);
            this.chkL.Name = "chkL";
            this.chkL.Size = new System.Drawing.Size(161, 19);
            this.chkL.TabIndex = 25;
            this.chkL.Text = "Enable left click on touch";
            this.chkL.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.White;
            this.ClientSize = new System.Drawing.Size(401, 402);
            this.Controls.Add(this.chkL);
            this.Controls.Add(this.w);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.sH);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.sW);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.sY);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.sX);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.tH);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.tW);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.tY);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.tX);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtCmb);
            this.Controls.Add(this.btnExit);
            this.Controls.Add(this.btnToggle);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "AbsoluteTouch control";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.tX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.tH)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.sH)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.sW)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.sY)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.sX)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.w)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.Button btnToggle;
        private System.Windows.Forms.Button btnExit;
        private System.Windows.Forms.TextBox txtCmb;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown tX;
        private System.Windows.Forms.NumericUpDown tY;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown tW;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.NumericUpDown tH;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.NumericUpDown sH;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown sW;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.NumericUpDown sY;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.NumericUpDown sX;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.NumericUpDown w;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.CheckBox chkL;
    }
}

