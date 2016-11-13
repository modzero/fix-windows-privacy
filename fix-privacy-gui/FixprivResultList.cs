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
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.ComponentModel;
using System.Data;
using System.Drawing;

namespace fix_privacy_gui
{
    class FixprivResultList
    {
        public ListView listView1;
        public 
        Boolean initialized;
        UInt32 listCount;

        public FixprivResultList(ListView lv)
        {
            this.initialized = false;
            this.listView1 = lv;
            this.listView1.View = View.Details;
            this.listView1.GridLines = true;
            this.listView1.FullRowSelect = true;
            this.listView1.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
            this.listCount = 0;
        }

        public void reset()
        {
            this.listCount = 0;
            this.listView1.Items.Clear();
        }

        // TODO: change to public void result_add_row(color-enum-dings color, string s)
        public void result_add_row(string[] row)
        {
            string[] r = new string[] { this.listCount.ToString(), row[1], row[2], "" };
            var item1 = new ListViewItem(r);

            item1.ToolTipText = row[2];
            row[2] = "";

            this.initialized = true;

            item1.SubItems.Add("Color");
            if (row[0].StartsWith("GREEN"))
            {
                item1.SubItems[0].BackColor = Color.FromArgb(0x66ffb2);
                item1.SubItems[1].BackColor = Color.FromArgb(0x66ffb2);
                item1.SubItems[2].BackColor = Color.FromArgb(0x66ffb2);
                item1.SubItems[3].BackColor = Color.FromArgb(0x66ffb2);
            }
            else if (row[0].StartsWith("YELLOW"))
            {
                item1.SubItems[0].BackColor = Color.FromArgb(0xffff99);
                item1.SubItems[1].BackColor = Color.FromArgb(0xffff99);
                item1.SubItems[2].BackColor = Color.FromArgb(0xffff99);
                item1.SubItems[3].BackColor = Color.FromArgb(0xffff99);
            }
            else if (row[0].StartsWith("RED"))
            {
                item1.SubItems[0].BackColor = Color.FromArgb(0xff9999);
                item1.SubItems[1].BackColor = Color.FromArgb(0xff9999);
                item1.SubItems[2].BackColor = Color.FromArgb(0xff9999);
                item1.SubItems[3].BackColor = Color.FromArgb(0xff9999);
            }
            else
            {
                item1.SubItems[0].BackColor = Color.FromArgb(0xccffff);
                item1.SubItems[1].BackColor = Color.FromArgb(0xccffff);
                item1.SubItems[2].BackColor = Color.FromArgb(0xccffff);
                item1.SubItems[3].BackColor = Color.FromArgb(0xccffff);
            }

            item1.UseItemStyleForSubItems = false;
            this.listView1.Items.Add(item1);
            this.listCount++;
        }
    }
}
