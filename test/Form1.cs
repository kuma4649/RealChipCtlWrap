using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NScci;
using Nc86ctl;

namespace test
{
    public partial class Form1 : Form
    {
        private NScci.NScci scci = null;
        private Nc86ctl.Nc86ctl c86 = null;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            for (int i = 0; i < 1; i++)
            {
                try
                {
                    MsgDisp("SCCI:処理開始");

                    MsgDisp("SCCI:コンストラクタ開始");
                    scci = new NScci.NScci();
                    MsgDisp("SCCI:コンストラクタ終了");

                    MsgDisp("SCCI:getInterfaceCount開始");
                    int n = scci.NSoundInterfaceManager_.getInterfaceCount();
                    MsgDisp("SCCI:getInterfaceCount完了");
                    if (n == 0)
                    {
                        MsgDisp("SCCI:SCCI見つからず");
                        scci.Dispose();
                        scci = null;
                    }
                    else
                    {
                        for (int j = 0; j < n; j++)
                        {
                            MsgDisp(string.Format("SCCI:====================== Interface {0}", j));
                            MsgDisp("SCCI:getInterface 開始");
                            NSoundInterface nsif = scci.NSoundInterfaceManager_.getInterface(j);
                            MsgDisp("SCCI:getInterface 完了");

                            MsgDisp("SCCI:getSoundChipCount 開始");
                            int c = nsif.getSoundChipCount();
                            MsgDisp("SCCI:getSoundChipCount 完了");

                            for (int k = 0; k < c; k++)
                            {
                                MsgDisp("SCCI:------------------- Chip Information");

                                MsgDisp("SCCI:getSoundChip 開始");
                                NSoundChip nsc = nsif.getSoundChip(k);
                                MsgDisp("SCCI:getSoundChip 完了");

                                MsgDisp("SCCI:getSoundChipInfo 開始");
                                NSCCI_SOUND_CHIP_INFO nssci = nsc.getSoundChipInfo();
                                MsgDisp("SCCI:getSoundChipInfo 完了");

                                MsgDisp(string.Format("SCCI:cSoundChipName {0}", nssci.cSoundChipName));
                                MsgDisp(string.Format("SCCI:dClock {0}", nssci.dClock));
                                MsgDisp(string.Format("SCCI:iSoundChip {0}", nssci.iSoundChip));
                                MsgDisp(string.Format("SCCI:bIsUsed {0}", nssci.bIsUsed));
                            }
                        }

                        if (scci != null)
                        {
                            scci.Dispose();
                            scci = null;
                        }

                    }
                }
                catch (Exception escci)
                {
                    MsgDisp("SCCI:Exception発生");
                    MsgDisp(string.Format("SCCI:Message:{0}", escci.Message));
                    MsgDisp(string.Format("SCCI:StackTrace:{0}", escci.StackTrace));
                }

                try
                {
                    MsgDisp("c86ctl:処理開始");

                    MsgDisp("c86ctl:Nc86ctl 開始");
                    c86 = new Nc86ctl.Nc86ctl();
                    MsgDisp("c86ctl:Nc86ctl 完了");

                    MsgDisp("c86ctl:initialize 開始");
                    c86.initialize();
                    MsgDisp("c86ctl:initialize 完了");

                    MsgDisp("c86ctl:getNumberOfChip 開始");
                    int nc = c86.getNumberOfChip();
                    MsgDisp("c86ctl:getNumberOfChip 完了");
                    if (nc == 0)
                    {
                        MsgDisp("c86ctl:deinitialize 開始");
                        c86.deinitialize();
                        MsgDisp("c86ctl:deinitialize 完了");
                        MsgDisp("c86ctl:c86ctl見つからず");
                        c86.Dispose();
                        c86 = null;
                    }
                    else
                    {
                        MsgDisp("c86ctl:getChipInterface 開始");
                        NIRealChip nirc = c86.getChipInterface(0);
                        MsgDisp("c86ctl:getChipInterface 完了");

                        MsgDisp("c86ctl:reset 開始");
                        nirc.reset();
                        MsgDisp("c86ctl:reset 完了");

                        MsgDisp("c86ctl:QueryInterface 開始");
                        NIGimic2 nig = nirc.QueryInterface();
                        MsgDisp("c86ctl:QueryInterface 完了");

                        UInt16 aa = 0;
                        UInt16 bb = 0;
                        UInt16 cc = 0;
                        UInt16 dd = 0;
                        MsgDisp("c86ctl:getFWVer 開始");
                        nig.getFWVer(ref aa, ref bb, ref cc, ref dd);
                        MsgDisp(string.Format("c86ctl:getFWVer 完了({0}.{1}.{2}.{3})", aa, bb, cc, dd));

                        MsgDisp("c86ctl:getMBInfo 開始");
                        Devinfo dv = nig.getMBInfo();
                        MsgDisp(string.Format("c86ctl:getMBInfo 完了 {0}", dv.Devname));

                        MsgDisp("c86ctl:getModuleType 開始");
                        ChipType tp = nig.getModuleType();
                        MsgDisp(string.Format("c86ctl:getModuleType 完了 {0}", tp));

                        MsgDisp("c86ctl:getModuleInfo 開始");
                        Devinfo di = nig.getModuleInfo();
                        MsgDisp(string.Format("c86ctl:getModuleInfo 完了 {0}", di.Devname));

                        MsgDisp("c86ctl:getSSGVolume 開始");
                        byte vol = nig.getSSGVolume();
                        MsgDisp(string.Format("c86ctl:getSSGVolume 完了 {0}", vol));

                        MsgDisp("c86ctl:getPLLClock 開始");
                        uint clock = nig.getPLLClock();
                        MsgDisp(string.Format("c86ctl:getPLLClock 完了 {0}", clock));
                    }

                }
                catch (Exception ec86)
                {
                    MsgDisp("c86ctl:Exception発生");
                    MsgDisp(string.Format("c86ctl:Message:{0}", ec86.Message));
                    MsgDisp(string.Format("c86ctl:StackTrace:{0}", ec86.StackTrace));
                }
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (scci != null)
            {
                scci.Dispose();
                scci = null;
            }

            if (c86 != null)
            {
                c86.deinitialize();
                c86 = null;
            }

        }

        private void MsgDisp(string msg)
        {
            textBox1.AppendText(msg + "\r\n");
        }

    }
}
