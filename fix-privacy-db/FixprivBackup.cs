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
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;
using System.Diagnostics;

namespace fix_privacy
{
    public class FixprivBackup
    {
        string current_backup;
        string backup_main;
        string backup_dir;

        public FixprivBackup() {

            int i = 0;
            string dirname = DateTime.Now.ToString("yyyyMMddHHmmssfff");

            this.backup_main = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData) 
                    + "\\modzero\\fix-windows-privacy\\backup";

            // find a non-existing directory for a new backup
            for (i = 0; i < 10; i++) {
                if (Directory.Exists(this.backup_main + "\\" + dirname))
                {
                    dirname = DateTime.Now.ToString("yyyyMMddHHmmssfff");
                }
                else {
                    this.current_backup = dirname;
                    break;
                }
                this.current_backup = null;
            }
            this.backup_dir = this.backup_main + "\\" + this.current_backup;
            
        } // ctor

        private void mk_backup_dir() {

            if (false == Directory.Exists(this.backup_dir))
            {
                try
                {
                    Directory.CreateDirectory(this.backup_dir);
                }
                catch (Exception e)
                {
                    Debug.WriteLine("[e] backup/store: " + e.Message);
                }
            }
        }

        public void store(FixprivPolicies pol)
        {
            this.mk_backup_dir();
            this.store_policies(pol);
        }

        public void store(FixprivServices svc)
        {
            this.mk_backup_dir();
            this.store_services(svc);
        }

        void store_policies(FixprivPolicies p)
        {
            string pol_xmlfile = this.backup_dir + "\\FixprivPolicyRules.xml";
            XmlSerializer sp = new XmlSerializer(typeof(FixprivPolicies));

            try
            {
                TextWriter fs;
                fs = new StreamWriter(pol_xmlfile);
                sp.Serialize(fs, p);
                fs.Close();
            }
            catch (Exception e)
            {
                Debug.WriteLine("[e] serialize policies: " + e.Message);
            }

        }

        void store_services(FixprivServices s)
        {
            string svc_xmlfile = this.backup_dir + "\\FixprivServiceRules.xml";
            XmlSerializer ss = new XmlSerializer(typeof(FixprivServices));

            try
            {
                TextWriter fs;
                fs = new StreamWriter(svc_xmlfile);
                ss.Serialize(fs, s);
                fs.Close();

            }
            catch (Exception e)
            {
                Debug.WriteLine("[e] serialize policies: " + e.Message);
            }
        }

        // XXX next TODO
        void restore_policies(string fileName)
        {

        }

        // return list of available backups (most recent files first)
        public List<String> list()
        {
            List<String> backups = new List<string>();
            return backups;
        }
    }
}
