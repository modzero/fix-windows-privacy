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
using System.Runtime.Serialization;
using System.Runtime.InteropServices;
using System.Xml.Serialization;
using System.Threading;
using System.Windows.Forms;
using System.Collections.Concurrent;
using NDesk.Options;


namespace fix_privacy
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

    enum fixpriv_backupstatus_t
    {
        READREG_SUCCESS,
        READREG_NOTFOUND,
        READREG_DISABLED,
        READREG_FAIL
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
    }

    class Program
    {
        static string pol_xmlfile;
        static string svc_xmlfile;

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_special_modify();

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_modify_regkey_user(fixpriv_privpol_t pol);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_modify_gpo_regkey_user(fixpriv_privpol_t pol);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_modify_gpo_regkey_machine(fixpriv_privpol_t pol);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_svc_modify(fixpriv_privsvc_t pol);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_modify_policy(fixpriv_privpol_t privpol);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void fixpriv_elevate();

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern void fixpriv_elevate_withargs(StringBuilder av);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern fixpriv_status_t fixpriv_check_regkey(fixpriv_privpol_t privpol);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern fixpriv_status_t fixpriv_svc_check(fixpriv_privsvc_t privpol);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern UInt32 fixpriv_svc_read(ref fixpriv_privsvc_t pol);

        [DllImport("fix-privacy-dll.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public unsafe static extern UInt32 fixpriv_read_regkey(ref fixpriv_privpol_t privpol);

        static ConcurrentQueue<fixpriv_result_t> returnValueQueue = new ConcurrentQueue<fixpriv_result_t>();
        static AutoResetEvent signalQueue = new AutoResetEvent(false);
        static public Boolean shouldRun = true;
        static Boolean read_only = true; // default
        static Boolean no_interaction = false;
        static int verbosity = 0;
        static int progress_count = 0;

        static string[] colors = {
                "WHITE ",
                "GREEN ",
                "YELLOW",
                "RED   "
            };

        public static void usage(OptionSet p)
        {
            Console.WriteLine("[*] Fix Windows 10 Privacy -- version {0}", Application.ProductVersion);
            Console.WriteLine("[*] Copyright 2016, modzero GmbH");
            Console.WriteLine("[*] Information and updates at http://www.modzero.ch/software/fixwinprivacy/");

            Console.WriteLine("[*] Usage: {0}\n", System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName.Split('\\').Last());
            p.WriteOptionDescriptions(Console.Out);
            Environment.Exit(0);
        }


        //[STAThread]
        static void Main(string[] args)
        {
            FileStream fs;
            String dllpath = "C:\\Users\\ths\\Dev\\mod0-winX-priv\\fix-privacy\\x64\\Debug;."; // XXX
            Environment.SetEnvironmentVariable("PATH", Environment.GetEnvironmentVariable("PATH") + ";" + dllpath);
            List<string> cpath = new List<string>(Application.ExecutablePath.Split('\\'));
            cpath.RemoveRange(cpath.Count() - 1, 1);
            String exepath = string.Join("\\", cpath.ToArray());

            bool show_help = false;
            List<string> mozpaths = new List<string>();

            var p = new OptionSet() {
                { "f|fix",          "fix privacy settings (default is check-only)",     v => { if (v != null) read_only = false; } },
                { "b|batch",        "batch-mode - no interaction",            v => { if (v != null) no_interaction = true; } },
                { "p|pxml=",        "path to policy rules",                   v => pol_xmlfile = v },
                { "s|sxml=",        "path to service rules",                  v => svc_xmlfile = v },
                { "v", "increase debug message verbosity",                    v => { if (v != null) ++verbosity; } },
                { "h|help",  "show this message and exit",                    v => show_help = v != null },
            };

            List<string> extra;
            try
            {
                extra = p.Parse(args);
            }
            catch (OptionException)
            {
                Console.WriteLine("Try '--help' for more information.");
                return;
            }

            if (show_help)
                usage(p);

            if (pol_xmlfile == null)
                pol_xmlfile = exepath + "\\FixprivPolicyRules.xml";

            if (svc_xmlfile == null)
                svc_xmlfile = exepath + "\\FixprivServiceRules.xml";

            FixprivPolicies fpol = new FixprivPolicies();
            FixprivServices fsvc = new FixprivServices();
            FixprivServices bsvc = new FixprivServices(); // backup services
            FixprivBackup backup = new FixprivBackup();

            XmlSerializer sp = new XmlSerializer(typeof(FixprivPolicies));
            XmlSerializer ss = new XmlSerializer(typeof(FixprivServices));

            string arguments = String.Join(" ", args);
            StringBuilder av = new StringBuilder(arguments);

            fixpriv_elevate_withargs(av);

            try
            {
                fixpriv_status_t result;
                shouldRun = true;

                fs = new FileStream(pol_xmlfile, FileMode.Open);

                fpol = (FixprivPolicies)sp.Deserialize(fs);

                FixprivWorker w = new FixprivWorker(fpol, backup, read_only); // if read_only = true, only read and compare values

                Thread t = new Thread(new ThreadStart(w.go));
                t.SetApartmentState(ApartmentState.STA);
                t.Start();

                while (shouldRun == true)
                {
                    signalQueue.WaitOne(1000);
                    fixpriv_result_t r;
                    while (returnValueQueue.TryDequeue(out r))
                    {
                        Console.WriteLine(" [Policy " + progress_count + "] [" + colors[(int)r.state] + "] " 
                                            +        r.policy.section_key
                                            + "\\" + r.policy.pol_key 
                                            + "\\" + r.policy.pol_value_name);
                        progress_count++;


                    }
                }

                fs.Close();

                fs = new FileStream(svc_xmlfile, FileMode.Open);
                fsvc = (FixprivServices)ss.Deserialize(fs);

                foreach (FixprivService svc in fsvc.rules)
                {
                    fixpriv_privsvc_t pi_svc = new fixpriv_privsvc_t();
                    fixpriv_privsvc_t backup_pi_svc = new fixpriv_privsvc_t();
                    FixprivService backup_svc = new FixprivService();

                    pi_svc.service_name = backup_svc.name = svc.name;
                    pi_svc.service_path = backup_svc.servicePath = svc.servicePath;
                    pi_svc.service_params = backup_svc.serviceParams = svc.serviceParams;

                    backup_pi_svc.service_name = svc.name;
                    backup_pi_svc.service_path = svc.servicePath;
                    backup_pi_svc.service_params = svc.serviceParams;

                    backup_svc.serviceState = "WS_STATUS_UNCHANGED";
                    backup_svc.serviceDescription = svc.serviceDescription;
                    backup_svc.id = svc.id;

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

                    fixpriv_svc_read(ref backup_pi_svc);

                    switch (backup_pi_svc.service_startup)
                    {
                        case ws_startup_t.WS_STARTUP_AUTOMATIC_DELAYED:
                            backup_svc.serviceCommand = "WS_STARTUP_AUTOMATIC_DELAYED";
                            break;
                        case ws_startup_t.WS_STARTUP_AUTOMATIC:
                            backup_svc.serviceCommand = "WS_STARTUP_AUTOMATIC";
                            break;
                        case ws_startup_t.WS_STARTUP_MANUAL:
                            backup_svc.serviceCommand = "WS_STARTUP_MANUAL";
                            break;
                        case ws_startup_t.WS_STARTUP_DISABLED:
                            backup_svc.serviceCommand = "WS_STARTUP_DISABLED";
                            break;
                        case ws_startup_t.WS_STARTUP_DELETE:
                            backup_svc.serviceCommand = "WS_STARTUP_DELETE";
                            break;
                        case ws_startup_t.WS_STARTUP_UNCHANGED:
                        default:
                            backup_svc.serviceCommand = "WS_STARTUP_UNCHANGED";
                            break;
                    }

                    bsvc.rules.Add(backup_svc);

                    if (false == read_only)
                    {
                        fixpriv_svc_modify(pi_svc);
                    }

                    result = fixpriv_svc_check(pi_svc);

                    if ((int)result == -2)
                        Console.WriteLine("[Windows Services " + progress_count + "] [" 
                                + colors[(int)fixpriv_status_t.FIXPRIV_NEUTRAL] + "] " 
                                + pi_svc.service_name + ": Permission Denied");
                    else
                        Console.WriteLine("[Windows Services " 
                                + progress_count + "] [" + colors[(int)result] + "] " 
                                + pi_svc.service_name + ": " 
                                + pi_svc.service_startup);

                    progress_count++;

                } // foreach svc

                if (false == read_only)
                    backup.store(bsvc);

            }
            catch (Exception e)
            {
                Console.WriteLine("[e] error in main: " + e.Message);
                if (false == read_only)
                    backup.store(bsvc);
            }

            if (no_interaction == false)
            {
                Console.Write("\nPress any key to continue... ");
                Console.ReadLine();
            }

        } // Main

        public class FixprivWorker
        {
            string[] colors = {
                "WHITE ",
                "GREEN ",
                "YELLOW",
                "RED   "
            };

            public FixprivPolicies fpol;
            FixprivBackup backup;

            public Boolean exec_check_only = false;
            fixpriv_status_t check_result = fixpriv_status_t.FIXPRIV_NEUTRAL;

            //
            public FixprivWorker(FixprivPolicies p, FixprivBackup bak, Boolean check_only)
            {
                this.backup = bak;
                this.fpol = p;
                this.exec_check_only = check_only;
                check_result = fixpriv_status_t.FIXPRIV_NEUTRAL;

            }

            public FixprivWorker(FixprivPolicies p, Boolean check_only)
            {
                this.fpol = p;
                this.backup = new FixprivBackup();
                this.exec_check_only = check_only;
                check_result = fixpriv_status_t.FIXPRIV_NEUTRAL;
            }

            public void go()
            {
                fixpriv_privpol_t pi_pol;
                fixpriv_privpol_t backup_pi_pol;
                fixpriv_result_t s = new fixpriv_result_t();
                FixprivPolicies bpol = new FixprivPolicies();
                fixpriv_backupstatus_t backupStatus;

                if (this.exec_check_only == false)
                    fixpriv_special_modify();

                foreach (FixprivPolicy pol in this.fpol.rules)
                {
                    FixprivPolicy backup_pol = new FixprivPolicy();
                    pi_pol = new fixpriv_privpol_t();
                    backup_pi_pol = new fixpriv_privpol_t();

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

                    backup_pol.key.keyRoot = pol.key.keyRoot;
                    backup_pi_pol.section_key = pi_pol.section_key;

                    pi_pol.pol_key = pol.key.keyName;
                    pi_pol.pol_value_name = pol.key.keyValue.valueName;

                    backup_pi_pol.pol_key = pol.key.keyName;
                    backup_pi_pol.pol_value_name = pol.key.keyValue.valueName;
                    backup_pol.key.keyName = pol.key.keyName;

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

                    backup_pi_pol.pol_datatype = pi_pol.pol_datatype;
                    backup_pi_pol.pol_mode = pi_pol.pol_mode;

                    backup_pol.key.keyValue.valueType = pol.key.keyValue.valueType;
                    backup_pol.id = pol.id;
                    backup_pol.key.keyValue.valueDescription = pol.key.keyValue.valueDescription;

                    if (this.exec_check_only == true)
                    {
                        check_result = fixpriv_check_regkey(pi_pol);

                        s = new fixpriv_result_t();
                        s.state = check_result;
                        s.policy = pi_pol;

                        returnValueQueue.Enqueue(s);
                        signalQueue.Set();
                        Thread.Sleep(50);
                    }
                    else
                    {
                        try
                        {
                            // backup functions

                            backupStatus = (fixpriv_backupstatus_t)fixpriv_read_regkey(ref backup_pi_pol);

                            backup_pol.key.keyValue.valueName = backup_pi_pol.pol_value_name;
                            backup_pol.key.keyValue.valueData = backup_pi_pol.pol_value_data;

                            if (backupStatus == fixpriv_backupstatus_t.READREG_SUCCESS)
                            {
                                backup_pol.key.keyValue.valueMode = "POL_ENABLED";
                                backup_pol.key.keyValue.valueData = backup_pi_pol.pol_value_data;

                            }
                            else if (backupStatus == fixpriv_backupstatus_t.READREG_NOTFOUND)
                            {
                                backup_pol.key.keyValue.valueMode = "POL_DELETE";
                                backup_pol.key.keyValue.valueType = "REG_DELETE";
                                backup_pol.key.keyValue.valueData = "0";
                            }
                            else // fail
                            {
                                backup_pol.key.keyValue.valueType = "REG_DELETE";
                                backup_pol.key.keyValue.valueMode = "POL_NOTCONFIGURED";
                                backup_pol.key.keyValue.valueData = "0";
                            }

                            bpol.rules.Add(backup_pol);

                            // backup functions

                            fixpriv_modify_policy(pi_pol);

                            if (pi_pol.section_key == ws_key_t.WS_KEY_GPOM)
                                Thread.Sleep(300); // wait for changes to sync. 500ms works

                            check_result = fixpriv_check_regkey(pi_pol);

                            s = new fixpriv_result_t();
                            s.state = check_result;
                            s.policy = pi_pol;

                            returnValueQueue.Enqueue(s);
                            signalQueue.Set();
                            Thread.Sleep(5);
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine("[e] error in FixprivWorker.go: " + e.Message);
                            
                            // make sure, backups are written to disk
                            if (false == this.exec_check_only)
                                this.backup.store(bpol);
                        }
                    }
                } // foreach

                if (false == this.exec_check_only)
                    this.backup.store(bpol);

                shouldRun = false;
            } // go()
        } // worker class 
    } // class program
}
