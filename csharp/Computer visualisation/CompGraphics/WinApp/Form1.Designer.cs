namespace WinApp
{
    partial class CompGraphicsForm
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
            this.imageControl = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.imageControl)).BeginInit();
            this.SuspendLayout();
            // 
            // imageControl
            // 
            this.imageControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.imageControl.Location = new System.Drawing.Point(0, 0);
            this.imageControl.Name = "imageControl";
            this.imageControl.Size = new System.Drawing.Size(791, 450);
            this.imageControl.TabIndex = 0;
            this.imageControl.TabStop = false;
            this.imageControl.Paint += new System.Windows.Forms.PaintEventHandler(this.imageControl_Paint);
            // 
            // CompGraphicsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(791, 450);
            this.Controls.Add(this.imageControl);
            this.Name = "CompGraphicsForm";
            this.Text = "CompGraphics";
            this.SizeChanged += new System.EventHandler(this.CompGraphicsForm_SizeChanged);
            ((System.ComponentModel.ISupportInitialize)(this.imageControl)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox imageControl;
    }
}

