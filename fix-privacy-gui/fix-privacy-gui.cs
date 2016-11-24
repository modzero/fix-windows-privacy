/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Copyright (c) 2016, Thorsten Schroeder, modzero GmbH
*
* All rights reserved.
*
* This file is part of fix-windows-privacy.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
*  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*  The views and conclusions contained in the software and documentation are those
*  of the authors and should not be interpreted as representing official policies,
*  either expressed or implied, of the fix-windows-privacy Project, modzero or
*  Thorsten Schroeder.
*
* NON-MILITARY-USAGE CLAUSE
* Redistribution and use in source and binary form for military use and
* military research is not permitted. Infringement of these clauses may
* result in publishing the source code of the utilizing applications and
* libraries to the public. As this software is developed, tested and
* reviewed by *international* volunteers, this clause shall not be refused
* due to the matter of *national* security concerns.
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Xml.Serialization;
using System.Threading;
using fix_privacy;
using System.IO;
using static fix_privacy_gui.FixprivExecute;

namespace fix_privacy_gui
{
    public partial class FixWindows10Privacy : Form
    {
        static FixprivResultList resultList;
        static FixprivExecute fpe;
        Boolean run_completed = false;
        Thread t;

        string backup_path;
        string backup_restore_dir;


        public FixWindows10Privacy()
        {
            this.backup_path = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData)
                    + "\\modzero\\fix-windows-privacy\\backup\\";
            this.backup_restore_dir = "";

            InitializeComponent();
            resultList = new FixprivResultList(listView1);
            fpe = new FixprivExecute(resultList, true);
            fpe.status_label = toolStripStatusLabel1;
            this.run_completed = false;
            create_main_menu();
        }

        private void reset()
        {
            resultList.reset();
            toolStripStatusLabel1.Text = "";
            toolStripProgressBar1.Value = 0;

            this.run_completed = false;
        }

        public string[] colors = {
                    "WHITE ",
                    "GREEN ",
                    "YELLOW",
                    "RED   "
                };

        void set_progress_bar(Int32 progress, Int32 total)
        {
            toolStripProgressBar1.Maximum = 100;
            toolStripProgressBar1.Value = ((progress * 100)/total);
        }
        
        public void set_status_bar(string message)
        {
            toolStripStatusLabel1.Text = message;
        }

        public void set_result(string[] row)
        {
            resultList.result_add_row(row);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (this.run_completed == true)
                this.reset();

            fpe.set_result_handler(set_result);
            fpe.set_status_handler(set_status_bar);
            fpe.set_progress_handler(set_progress_bar);

            fpe.exec_check_only = true;

            this.t = new Thread(new ThreadStart(fpe.start));
            this.t.SetApartmentState(ApartmentState.STA);
            this.t.Start();

            this.run_completed = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (this.run_completed == true)
                this.reset();

            fpe.set_result_handler(set_result);
            fpe.set_status_handler(set_status_bar);
            fpe.set_progress_handler(set_progress_bar);

            fpe.exec_check_only = false;

            this.t = new Thread(new ThreadStart(fpe.start));
            this.t.SetApartmentState(ApartmentState.STA);
            this.t.Start();

            this.run_completed = true;
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {
        }


        private void button3_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        public void create_main_menu()
        {
            MainMenu mainMenu1 = new MainMenu();

            MenuItem menuItem1 = new MenuItem();
            MenuItem menuItem2 = new MenuItem();

            menuItem1.Text = "File";
            menuItem2.Text = "Help";

            MenuItem subMenuItemFile1 = new MenuItem("&Exit", new System.EventHandler(this.OnExit_Click));
            MenuItem subMenuItemHelp1 = new MenuItem("&About", new System.EventHandler(this.OnAbout_Click));
            MenuItem subMenuItemHelp2 = new MenuItem("&Updates", new System.EventHandler(this.OnUpdate_Click));


            menuItem1.MenuItems.Add(subMenuItemFile1);
            menuItem2.MenuItems.Add(subMenuItemHelp1);
            menuItem2.MenuItems.Add(subMenuItemHelp2);

            // Add two MenuItem objects to the MainMenu.
            mainMenu1.MenuItems.Add(menuItem1);
            mainMenu1.MenuItems.Add(menuItem2);

            // Bind the MainMenu to Form1.
            Menu = mainMenu1;
        }

        private void OnExit_Click(Object sender, System.EventArgs e)
        {
            // Code goes here that handles the Click event.
            Application.Exit();
        }

        private void OnAbout_Click(Object sender, System.EventArgs e)
        {
            string about_text = "Fix Windows 10 Privacy\n\n"
                + "   Version: " + Application.ProductVersion + "\n"
                + "   Author: Thorsten Schroeder\n"
                + "   Copyright 2016, modzero GmbH\n\n"
                + "Contact: \n"
                + "   modzero GmbH\n"
                + "   Friedrichstr. 95\n"
                + "   10117 Berlin\n"
                + "   Germany\n"
                + "   Web: http://www.modzero.de/\n"
                + "   Mail: contact@modzero.ch\n\n"
                + "This program is free software. It comes without any warranty.\n"
                + "Use at your own risk!";

            MessageBox.Show(about_text, "About Fix Windows 10 Privacy");
        }

        private void OnUpdate_Click(Object sender, System.EventArgs e)
        {
            DialogResult sw_update_result = MessageBox.Show("Do you want to check for updates?",
                "Fix Win 10 Privacy Update",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question,
                MessageBoxDefaultButton.Button1);

            if (sw_update_result == DialogResult.Yes)
            {
                // trigger update (T.B.D.)
            }
            else if (sw_update_result == DialogResult.No)
            {
                return;
            }
        }

        private void listView1_ItemMouseHover(object sender, ListViewItemMouseHoverEventArgs e)
        {
            ToolTip myTT = new ToolTip();
            myTT.Show(e.Item.ToolTipText, listView1);
        }

        private void listView1_DoubleClick(object sender, EventArgs e)
        {
            //
        }

        private void restore_Click(object sender, EventArgs e)
        {
            if (this.folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                this.backup_restore_dir = this.folderBrowserDialog1.SelectedPath;
            }

            string msgbox_text = "Do you want to restore the backup from "
                + Path.GetFileName(this.backup_restore_dir) + "?";
            string msgbox_caption = "Restore Backup?";

            var result = MessageBox.Show(msgbox_text, msgbox_caption,
                                 MessageBoxButtons.OKCancel,
                                 MessageBoxIcon.Question);

            if (result == DialogResult.OK)
            {
                Debug.WriteLine("Restore Backups from " + this.backup_restore_dir);

                fpe.restore(this.backup_restore_dir);

                if (this.run_completed == true)
                    this.reset();

                fpe.set_result_handler(set_result);
                fpe.set_status_handler(set_status_bar);
                fpe.set_progress_handler(set_progress_bar);

                fpe.exec_check_only = false;

                this.t = new Thread(new ThreadStart(fpe.start));
                this.t.SetApartmentState(ApartmentState.STA);
                this.t.Start();

                this.run_completed = true;
            }
        }
    }
}
