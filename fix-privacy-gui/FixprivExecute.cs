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
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE DDK PROJECT BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Xml.Serialization;
using System.Threading;
using fix_privacy;
using System.IO;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Concurrent;

namespace fix_privacy_gui
{
    enum value_data_type_t { POL_DWORD, POL_WSTRING, POL_ASTRING, POL_BOOL };
    enum m0_polregmode_t { POL_NOTCONFIGURED, POL_ENABLED, POL_DISABLED, POL_DELETE };
    enum ws_key_t { WS_KEY_HKCU, WS_KEY_HKLM, WS_KEY_GPOU, WS_KEY_GPOM };

    enum ws_startup_t
    {
        WS_STARTUP_UNCHANGED,
        WS_STARTUP_AUTOMATIC_DELAYED,
        WS_STARTUP_AUTOMATIC,
        WS_STARTUP_MANUAL,
        WS_STARTUP_DISABLED,
        WS_STARTUP_DELETE
    };

    enum ws_status_t
    {
        WS_STATUS_UNCHANGED,
        WS_STATUS_START,
        WS_STATUS_STOP,
        WS_STATUS_PAUSE,
        WS_STATUS_RESUME
    };

    enum fixpriv_status_t
    {
        FIXPRIV_NEUTRAL,
        FIXPRIV_GREEN,
        FIXPRIV_YELLOW,
        FIXPRIV_RED
    };

    // m0_privpol_t *
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    struct fixpriv_privpol_t
    {
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string pol_key;

        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string pol_value_name;

        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string pol_value_data;

        public value_data_type_t pol_datatype;
        public m0_polregmode_t pol_mode;
        public ws_key_t section_key;
    }

    // m0_privsvc_t *
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    struct fixpriv_privsvc_t
    {
        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 64)]
        public string service_name;

        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string service_path;

        [MarshalAsAttribute(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string service_params;

        public ws_startup_t service_startup;
        public ws_status_t service_status;
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    struct fixpriv_result_t
    {
        public fixpriv_privpol_t policy;
        public fixpriv_status_t state;
        public string tooltip;
    }

    class FixprivExecute : Form
    {
        static string pol_xmlfile; //= Application.ExecutablePath + "\\FixprivPolicyRules.xml";
        static string svc_xmlfile; // = Application.ExecutablePath  + "\\FixprivServiceRules.xml";

        List<fixpriv_result_t> result;

        //extern HRESULT fixpriv_special_modify(void)
        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_special_modify();

        //extern HRESULT fixpriv_modify_regkey_user(m0_privpol_t privpol)
        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_modify_regkey_user(fixpriv_privpol_t pol);

        //extern HRESULT fixpriv_modify_gpo_regkey_user(m0_privpol_t privpol)
        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_modify_gpo_regkey_user(fixpriv_privpol_t pol);

        //extern HRESULT fixpriv_modify_gpo_regkey_machine(m0_privpol_t privpol)
        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_modify_gpo_regkey_machine(fixpriv_privpol_t pol);

        //extern HRESULT fixpriv_svc_modify(m0_privsvc_t privsvc)
        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_svc_modify(fixpriv_privsvc_t pol);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_modify_policy(fixpriv_privpol_t privpol);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void fixpriv_elevate();

        // fixpriv_status_t fixpriv_check_regkey(m0_privpol_t privpol)
        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern fixpriv_status_t fixpriv_check_regkey(fixpriv_privpol_t privpol);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern fixpriv_status_t fixpriv_svc_check(fixpriv_privsvc_t privpol);

        Thread t;

        public ConcurrentQueue<fixpriv_result_t> returnValueQueue = new ConcurrentQueue<fixpriv_result_t>();
        public AutoResetEvent signalQueue = new AutoResetEvent(false);
        public Boolean shouldRun = true;

        public string[] colors = {
                    "WHITE ",
                    "GREEN ",
                    "YELLOW",
                    "RED   "
                };

        public FixprivPolicies fpol;
        public Boolean exec_check_only = false;
        fixpriv_status_t check_result = fixpriv_status_t.FIXPRIV_NEUTRAL;
        static FixprivResultList resultview;
        public ToolStripStatusLabel status_label;

        public delegate void FpeOnResultUpdate(string[] row);
        public delegate void FpeOnStatusUpdate(string status);
        public delegate void FpeOnProgressUpdate(Int32 current, Int32 final);

        FpeOnStatusUpdate status_update;
        FpeOnProgressUpdate progress_update;
        FpeOnResultUpdate result_update;

        public void set_status_handler(FpeOnStatusUpdate h) {
            this.status_update = h;
        }

        public void set_progress_handler(FpeOnProgressUpdate h)
        {
            this.progress_update = h;
        }

        public void set_result_handler(FpeOnResultUpdate h)
        {
            this.result_update = h;
        }

        public FixprivExecute(FixprivResultList r, Boolean check_only)
        {
            this.result = new List<fixpriv_result_t>();
            resultview = r;

            this.exec_check_only = check_only;
            check_result = fixpriv_status_t.FIXPRIV_NEUTRAL;
        }

        public void go()
        {
            fixpriv_privpol_t pi_pol;
            fixpriv_result_t s = new fixpriv_result_t();

            foreach (FixprivPolicy pol in this.fpol.rules)
            {
                pi_pol = new fixpriv_privpol_t();

                if (pol.key.keyRoot.Equals("HKCU"))
                    pi_pol.section_key = ws_key_t.WS_KEY_HKCU;
                else if (pol.key.keyRoot.Equals("HKLM"))
                    pi_pol.section_key = ws_key_t.WS_KEY_HKLM;
                else if (pol.key.keyRoot.Equals("GPOU"))
                    pi_pol.section_key = ws_key_t.WS_KEY_GPOU;
                else if (pol.key.keyRoot.Equals("GPOM"))
                {
                    pi_pol.section_key = ws_key_t.WS_KEY_GPOM;
                }

                pi_pol.pol_key = pol.key.keyName;
                pi_pol.pol_value_name = pol.key.keyValue.valueName;

                if (pol.key.keyValue.valueType.Equals("REG_DWORD"))
                {
                    pi_pol.pol_datatype = value_data_type_t.POL_DWORD;
                    pi_pol.pol_value_data = pol.key.keyValue.valueData;
                    pi_pol.pol_mode = m0_polregmode_t.POL_ENABLED;
                }
                else if (pol.key.keyValue.valueType.Equals("REG_SZ"))
                {
                    pi_pol.pol_datatype = value_data_type_t.POL_WSTRING;
                    pi_pol.pol_mode = m0_polregmode_t.POL_ENABLED;
                    pi_pol.pol_value_data = pol.key.keyValue.valueData;
                }
                else if (pol.key.keyValue.valueType.Equals("REG_NONE"))
                {
                    pi_pol.pol_datatype = value_data_type_t.POL_DWORD;
                    pi_pol.pol_mode = m0_polregmode_t.POL_NOTCONFIGURED;
                }
                else if (pol.key.keyValue.valueType.Equals("REG_BINARY"))
                {
                    pi_pol.pol_datatype = value_data_type_t.POL_DWORD;
                    pi_pol.pol_mode = m0_polregmode_t.POL_ENABLED;
                }
                else if (pol.key.keyValue.valueType.Equals("REG_DELETE"))
                {
                    pi_pol.pol_datatype = value_data_type_t.POL_WSTRING;
                    pi_pol.pol_mode = m0_polregmode_t.POL_DELETE;
                }
                else if (pol.key.keyValue.valueType.Equals("REG_DISABLE"))
                {
                    pi_pol.pol_datatype = value_data_type_t.POL_WSTRING;
                    pi_pol.pol_mode = m0_polregmode_t.POL_DISABLED;
                }

                if (this.exec_check_only == true)
                {
                    check_result = fixpriv_check_regkey(pi_pol);

                    s = new fixpriv_result_t();
                    s.state = check_result;
                    s.policy = pi_pol;
                    s.tooltip = pol.key.keyValue.valueDescription; //  "XXX reg tooltip";

                    returnValueQueue.Enqueue(s);
                    signalQueue.Set();
                    Thread.Sleep(50);
                }
                else
                {
                    fixpriv_special_modify();
                    fixpriv_modify_policy(pi_pol);

                    if (pi_pol.section_key == ws_key_t.WS_KEY_GPOM)
                        Thread.Sleep(300); // wait for changes to sync. 500ms works

                    check_result = fixpriv_check_regkey(pi_pol);

                    s = new fixpriv_result_t();
                    s.state = check_result;
                    s.policy = pi_pol;
                    s.tooltip = pol.key.keyValue.valueDescription;

                    returnValueQueue.Enqueue(s);
                    signalQueue.Set();
                    Thread.Sleep(5);
                }
            } // foreach
            this.shouldRun = false;
        } // go()


        public void start()
        {
            this.start(this.exec_check_only);
        }

        public void start(Boolean read_only)
        {
            FileStream fs;
            String dllpath = "C:\\Users\\ths\\Dev\\mod0-winX-priv\\fix-privacy\\x64\\Release;."; // XXX
            Environment.SetEnvironmentVariable("PATH", Environment.GetEnvironmentVariable("PATH") + ";" + dllpath);
            List<string> cpath = new List<string>(Application.ExecutablePath.Split('\\'));
            cpath.RemoveRange(cpath.Count() - 1, 1);
            String exepath = string.Join("\\", cpath.ToArray());
            
            this.exec_check_only = read_only;
            this.shouldRun = true;

            pol_xmlfile = exepath + "\\FixprivPolicyRules.xml";
            svc_xmlfile = exepath + "\\FixprivServiceRules.xml";

            FixprivPolicies fpol = new FixprivPolicies();
            FixprivServices fsvc = new FixprivServices();
            XmlSerializer sp = new XmlSerializer(typeof(FixprivPolicies));
            XmlSerializer ss = new XmlSerializer(typeof(FixprivServices));

            //fixpriv_elevate();

            try
            {
                fs = new FileStream(pol_xmlfile, FileMode.Open);
                this.fpol = (FixprivPolicies)sp.Deserialize(fs);

                this.t = new Thread(new ThreadStart(this.go));
                this.t.SetApartmentState(ApartmentState.STA);
                this.t.Start();

                resultview.listView1.Columns[1].Width = 1000;
                resultview.listView1.Columns[2].Width = 0;

                while (this.shouldRun == true)
                {
                    this.signalQueue.WaitOne(1000);
                    fixpriv_result_t r;
                    while (this.returnValueQueue.TryDequeue(out r))
                    {
                        this.result_update(new[] {
                            colors[(int)r.state],
                            r.policy.section_key + "\\" + r.policy.pol_key + "\\" + r.policy.pol_value_name,
                            r.tooltip
                        });

                        this.status_update(r.policy.pol_value_name);
                        this.progress_update(resultview.listView1.Items.Count, this.fpol.rules.Count);
                    }
                }

                if (resultview.listView1.Items.Count > 0)
                {
                    resultview.listView1.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
                }

                fs.Close();
                fs = new FileStream(svc_xmlfile, FileMode.Open);
                fsvc = (FixprivServices)ss.Deserialize(fs);

                Debug.WriteLine("[*] processing {0} services", fsvc.rules.Count);

                foreach (FixprivService svc in fsvc.rules)
                {
                    fixpriv_status_t result;
                    fixpriv_privsvc_t pi_svc = new fixpriv_privsvc_t();

                    pi_svc.service_name = svc.name;
                    pi_svc.service_path = svc.servicePath;
                    pi_svc.service_params = svc.serviceParams;

                    if (svc.serviceCommand.Equals("WS_STARTUP_AUTOMATIC_DELAYED"))
                        pi_svc.service_startup = ws_startup_t.WS_STARTUP_AUTOMATIC_DELAYED;
                    else if (svc.serviceCommand.Equals("WS_STARTUP_AUTOMATIC"))
                        pi_svc.service_startup = ws_startup_t.WS_STARTUP_AUTOMATIC;
                    else if (svc.serviceCommand.Equals("WS_STARTUP_MANUAL"))
                        pi_svc.service_startup = ws_startup_t.WS_STARTUP_MANUAL;
                    else if (svc.serviceCommand.Equals("WS_STARTUP_DISABLED"))
                        pi_svc.service_startup = ws_startup_t.WS_STARTUP_DISABLED;
                    else if (svc.serviceCommand.Equals("WS_STARTUP_DELETE"))
                        pi_svc.service_startup = ws_startup_t.WS_STARTUP_DELETE;
                    else
                        pi_svc.service_startup = ws_startup_t.WS_STARTUP_UNCHANGED;

                    if (svc.serviceState.Equals("WS_STATUS_START"))
                        pi_svc.service_status = ws_status_t.WS_STATUS_START;
                    else if (svc.serviceState.Equals("WS_STATUS_STOP"))
                        pi_svc.service_status = ws_status_t.WS_STATUS_STOP;
                    else if (svc.serviceState.Equals("WS_STATUS_PAUSE"))
                        pi_svc.service_status = ws_status_t.WS_STATUS_PAUSE;
                    else if (svc.serviceState.Equals("WS_STATUS_RESUME"))
                        pi_svc.service_status = ws_status_t.WS_STATUS_RESUME;
                    else
                        pi_svc.service_status = ws_status_t.WS_STATUS_UNCHANGED;

                    if (false == this.exec_check_only)
                    {
                        fixpriv_svc_modify(pi_svc);
                    } 

                    result = fixpriv_svc_check(pi_svc);

                    if ((int)result == -2)
                        this.result_update(new[] {
                            colors[(int)fixpriv_status_t.FIXPRIV_NEUTRAL],
                            "[Windows Services] " + pi_svc.service_name + ": Permission Denied",
                            svc.serviceDescription
                        });
                    else
                        this.result_update(new[] {
                            colors[(int)result],
                            "[Windows Services] " + pi_svc.service_name + ": " + pi_svc.service_startup,
                            svc.serviceDescription
                        });

                    this.status_update(pi_svc.service_name);
                }
            }
            catch (Exception e)
            {
                Debug.WriteLine("[e] error in main: " + e.Message);
            }
            this.status_update("Done");
        }

        private void set_status(string s)
        {
            if (this.status_label != null)
            {
                this.status_label.Text = s;
            }
        }
    }
}
